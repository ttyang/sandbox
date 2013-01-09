// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//
#ifndef DOXYGEN_XML_PARSER_HPP
#define DOXYGEN_XML_PARSER_HPP


#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include <rapidxml_util.hpp>
#include <doxygen_elements.hpp>
#include <parameter_predicates.hpp>
#include <configuration.hpp>


inline std::string keep_after(std::string const& input, std::string const& sig)
{
    std::size_t pos = input.rfind(sig);
    if (pos != std::string::npos)
    {
        std::string copy = input.substr(pos + sig.length());
        return copy;
    }
    return input;
}


static inline void add_or_set(std::vector<parameter>& parameters, parameter const& p)
{
    std::vector<parameter>::iterator it = std::find_if(parameters.begin(), parameters.end(), par_by_name(p.name));
    if (it != parameters.end())
    {
        if (it->brief_description.empty()) it->brief_description = p.brief_description;
        if (it->type.empty()) it->type = p.type;
        if (it->fulltype.empty()) it->fulltype = p.fulltype;
        if (it->default_value.empty()) it->default_value = p.default_value;
    }
    else
    {
        parameters.push_back(p);
    }
}




/// Parses a "para" element 
/*
This is used for different purposes within Doxygen. 
- Either a detailed description, possibly containing several sections (para's)
  -> so parse next siblings
- Or a detailed description also containing qbk records

So we have to list explicitly either where to recurse, or where not to...

*/
static void parse_para(rapidxml::xml_node<>* node, std::string& contents, bool& skip, bool first = true)
{
    if (node != NULL)
    {
        if (node->type() == rapidxml::node_element)
        {
            //std::cout << "ELEMENT: " << node->name() << "=" << node->value() << std::endl;
            std::string name = node->name();
            if (boost::equals(name, "qbk.skip"))
            {
                skip = true;
                return;
            }
            else if ( boost::equals(name, "itemizedlist") )
            {
                contents += "\n\n";
                parse_para(node->first_node(), contents, skip);
                contents += "\n[/]";
                parse_para(node->next_sibling(), contents, skip);
                return;
            }
            else if ( boost::equals(name, "listitem") )
            {
                contents += "* ";
                rapidxml::xml_node<>* li = node->first_node("para");
                contents += li ? li->value() : "";
                contents += "\n";
                parse_para(node->next_sibling(), contents, skip);                
                return;
            }
            else if (! (
                (boost::equals(name, "para") && first)
                || boost::equals(name, "ref")
                || boost::equals(name, "defval")
                || boost::equals(name, "verbatim")
                || boost::equals(name, "bold")
                || boost::equals(name, "emphasis")
                || boost::equals(name, "linebreak")
                ))
            {
                return;
            }
        }
        else if (node->type() == rapidxml::node_data)
        {
            contents += node->value();
            //std::cout << "DATA: " << node->name() << "=" << node->value() << std::endl;
        }
        else
        {
            //std::cout << "OTHER: " << node->name() << "=" << node->value() << std::endl;
        }

        parse_para(node->first_node(), contents, skip, false);
        parse_para(node->next_sibling(), contents, skip, false);
    }
}


static void parse_parameter(rapidxml::xml_node<>* node, parameter& p)
{
    // #define: <param><defname>Point</defname></param>
    // template: <param><type>typename</type><declname>CoordinateType</declname><defname>CoordinateType</defname></param>
    // template with default: <param><type>typename</type><declname>CoordinateSystem</declname><defname>CoordinateSystem</defname><defval><ref ....>cs::cartesian</ref></defval></param>
    // with enum: <type><ref refid="group__enum_1ga7d33eca9a5389952bdf719972eb802b6" kindref="member">closure_selector</ref></type>
    if (node != NULL)
    {
        std::string name = node->name();
        if (name == "type")
        {
            get_contents(node->first_node(), p.fulltype);
            p.type = p.fulltype;
            boost::replace_all(p.type, " const", "");
            boost::trim(p.type);
            boost::replace_all(p.type, "&", "");
            boost::replace_all(p.type, "*", "");
            boost::trim(p.type);
        }
        else if (name == "declname") p.name = node->value();
        else if (name == "parametername") p.name = node->value();
        else if (name == "defname") p.name = node->value(); 
        else if (name == "defval") 
        {
             parse_para(node, p.default_value, p.skip);
        }
        else if (name == "para")
        {
             parse_para(node, p.brief_description, p.skip);
        }

        parse_parameter(node->first_node(), p);
        parse_parameter(node->next_sibling(), p);
    }
}

static void parse_enumeration_value(rapidxml::xml_node<>* node, enumeration_value& value)
{
    // <enumvalue><name>green</name><initializer> 2</initializer>
    //    <briefdescription><para>...</para></briefdescription>
    //    <detaileddescription><para>...</para></detaileddescription>
    // </enumvalue>
    if (node != NULL)
    {
        std::string node_name = node->name();

        if (node_name == "name") value.name = node->value();
        else if (node_name == "para")
        {
            // Parses both brief AND detailed into this description
            parse_para(node, value.brief_description, value.skip);
        }
        else if (node_name == "initializer")
        {
            value.initializer = node->value();
        }

        parse_enumeration_value(node->first_node(), value);
        parse_enumeration_value(node->next_sibling(), value);
    }
}

// Definition is a function or a class/struct
template <typename Parameters>
static void parse_parameter_list(rapidxml::xml_node<>* node, Parameters& parameters)
{
    if (node != NULL)
    {
        std::string name = node->name();

        if (name == "parameteritem")
        {
            parameter p;
            parse_parameter(node->first_node(), p);
            if (! p.name.empty())
            {
                // Copy its description
                std::vector<parameter>::iterator it = std::find_if(parameters.begin(),
                    parameters.end(), par_by_name(p.name));
                if (it != parameters.end())
                {
                    it->brief_description = p.brief_description;
                }
                else
                {
                    parameters.push_back(p);
                }
            }
        }
        else if (name == "param")
        {
            // Element of 'templateparamlist.param (.type,.declname,.defname)'
            parameter p;
            parse_parameter(node->first_node(), p);

            // Doxygen handles templateparamlist param's differently:
            //
            // Case 1:
            // <param><type>typename T</type></param>
            // -> no name, assign type to name, replace typename
            //
            // Case 2:
            // <type>typename</type><declname>T</declname><defname>T</defname>
            // -> set full type
            if (p.name.empty())
            {
                // Case 1
                p.name = p.type;
                boost::replace_all(p.name, "typename", "");
                boost::trim(p.name);
            }
            else
            {
                // Case 2
                p.fulltype = p.type + " " + p.name;
            }

            add_or_set(parameters, p);
        }

        parse_parameter_list(node->first_node(), parameters);
        parse_parameter_list(node->next_sibling(), parameters);
    }
}

static void copy_string_property(std::string const& source, std::string& target)
{
    if (target.empty())
    {
        target = source;
    }
}


template <typename Parameters>
static void copy_parameter_properties(parameter const& source, Parameters& target)
{
    BOOST_FOREACH(parameter& t, target)
    {
        if (source.name == t.name)
        {
            t.skip = source.skip;
            copy_string_property(source.brief_description, t.brief_description);
            copy_string_property(source.type, t.type);
            copy_string_property(source.default_value, t.default_value);
            copy_string_property(source.fulltype, t.fulltype);

            return;
        }
    }
    // If not found, write a warning
    std::cerr << "Parameter not found: " << source.name << std::endl;
}


template <typename Parameters>
static void copy_parameters_properties(Parameters const& source, Parameters& target)
{
    BOOST_FOREACH(parameter const& s, source)
    {
        copy_parameter_properties(s, target);
    }
}



template <typename Element>
static void parse_element(rapidxml::xml_node<>* node, configuration const& config, std::string const& parent, Element& el)
{
    if (node != NULL)
    {
        std::string name = node->name();
        std::string full = parent + "." + name;

        if (full == ".briefdescription.para")
        {
            parse_para(node, el.brief_description, el.skip);
        }
        else if (full == ".detaileddescription.para")
        {
            std::string para;
            parse_para(node, para, el.skip);
            if (!para.empty() && !el.detailed_description.empty())
            {
                el.detailed_description += "\n\n";
            }
            el.detailed_description += para;
        }
        else if (full == ".location")
        {
            std::string loc = get_attribute(node, "file");
            // Location of (header)file. It is a FULL path, so find the start
            // and strip the rest
            std::size_t pos = loc.rfind(config.start_include);
            if (pos != std::string::npos)
            {
                loc = loc.substr(pos);
            }
            el.location = loc;
            el.line = atol(get_attribute(node, "line").c_str());
        }
        else if (full == ".detaileddescription.para.qbk")
        {
            el.qbk_markup.push_back(markup(node->value()));
        }
        else if (full == ".detaileddescription.para.qbk.after.synopsis")
        {
            el.qbk_markup.push_back(markup(markup_after, markup_synopsis, node->value()));
        }
        else if (full == ".detaileddescription.para.qbk.before.synopsis")
        {
            el.qbk_markup.push_back(markup(markup_before, markup_synopsis, node->value()));
        }
        else if (full == ".detaileddescription.para.qbk.distinguish")
        {
            el.additional_description = node->value();
            boost::trim(el.additional_description);
        }
        else if (full == ".templateparamlist")
        {
            parse_parameter_list(node->first_node(), el.template_parameters);
        }
        else if (full == ".detaileddescription.para.parameterlist")
        {
            std::string kind = get_attribute(node, "kind");
            if (kind == "param")
            {
                // Parse parameters and their descriptions.
                // NOTE: they are listed here, but the order might not be the order in the function call
                std::vector<parameter> parameters;
                parse_parameter_list(node->first_node(), parameters);
                copy_parameters_properties(parameters, el.parameters);
            }
            else if (kind == "templateparam")
            {
                parse_parameter_list(node->first_node(), el.template_parameters);
            }
        }
        else if (full == ".detaileddescription.para.simplesect")
        {
            std::string kind = get_attribute(node, "kind");
            if (kind == "par")
            {
                rapidxml::xml_node<> * title_node = node->first_node("title");
                std::string title = title_node ? title_node->value() : "";
                
                std::string m;
                if ( title_node )
                    m = std::string("[heading ") + title + "]\n";
                else
                    m = "\n\n";

                parse_para(node->first_node("para"), m, el.skip);
                m += "\n";
                    
                el.qbk_markup.push_back(markup(m));
            }
            else if (kind == "pre")
            {
                std::string para;
                parse_para(node->first_node("para"), para, el.skip);
                
                el.qbk_markup.push_back(markup(std::string("[heading Precondition]\n") + para));
            }
        }
        else if (full == ".param")
        {
            // Parse one parameter, and add it to el.parameters
            parameter p;
            parse_parameter(node->first_node(), p);
            el.parameters.push_back(p);
        }


        parse_element(node->first_node(), config, full, el);
        parse_element(node->next_sibling(), config, parent, el);
    }
}

static void parse_function(rapidxml::xml_node<>* node, configuration const& config, std::string const& parent, function& f)
{
    if (node != NULL)
    {
        std::string name = node->name();
        std::string full = parent + "." + name;

        if (full == ".name") f.name = node->value();
        else if (full == ".argsstring") f.argsstring = node->value();
        else if (full == ".definition")
        {
            f.definition = node->value();
            if (! config.skip_namespace.empty())
            {
                boost::replace_all(f.definition, config.skip_namespace, "");
            }
        }
        else if (full == ".param")
        {
            parameter p;
            parse_parameter(node->first_node(), p);
            add_or_set(f.parameters, p);
        }
        else if (full == ".type")
        {
            get_contents(node->first_node(), f.return_type);
        }
        else if (full == ".detaileddescription.para.simplesect")
        {
            std::string kind = get_attribute(node, "kind");
            if (kind == "return")
            {
                get_contents(node->first_node(), f.return_description);
            }
            /*else if (kind == "param")
            {
                get_contents(node->first_node(), f.paragraphs);
            }*/
        }
        else if (full == ".detaileddescription.para.image")
        {
        }

        parse_function(node->first_node(), config, full, f);
        parse_function(node->next_sibling(), config, parent, f);
    }
}

static void parse_enumeration(rapidxml::xml_node<>* node, configuration const& config, std::string const& parent, enumeration& e)
{
    if (node != NULL)
    {
        std::string name = node->name();
        std::string full = parent + "." + name;

        if (full == ".name") e.name = node->value();
        else if (full == ".enumvalue")
        {
            enumeration_value value;
            parse_enumeration_value(node->first_node(), value);
            e.enumeration_values.push_back(value);
        }

        parse_enumeration(node->first_node(), config, full, e);
        parse_enumeration(node->next_sibling(), config, parent, e);
    }
}


static std::string parse_named_node(rapidxml::xml_node<>* node, std::string const& look_for_name)
{
    if (node != NULL)
    {
        std::string node_name = node->name();
        std::string contents;

        if (boost::equals(node_name, look_for_name))
        {
            contents = node->value();
        }

        return contents
            + parse_named_node(node->first_node(), look_for_name)
            + parse_named_node(node->next_sibling(), look_for_name);
    }
    return "";
}




static void parse(rapidxml::xml_node<>* node, configuration const& config, documentation& doc, bool member = false)
{
    if (node != NULL)
    {
        bool recurse = false;
        bool is_member = member;

        std::string nodename = node->name();

        if (nodename == "doxygen")
        {
            recurse = true;
        }
        else if (nodename == "sectiondef")
        {
            std::string kind = get_attribute(node, "kind");

            if (kind == "func"
                || kind == "define"
                || kind == "enum"
                )
            {
                recurse = true;
            }
            else if (boost::starts_with(kind, "public"))
            {
                recurse = true;
                is_member = true;
            }
        }
        else if (nodename == "compounddef")
        {
            std::string kind = get_attribute(node, "kind");
            if (kind == "group")
            {
                recurse = true;
                doc.group_id = get_attribute(node, "id");
                rapidxml::xml_node<> * n = node->first_node("title");
                if ( n )
                    doc.group_title = n->value();
            }
            else if (kind == "struct")
            {
                recurse = true;
                doc.cos.is_class = false;
                parse_element(node->first_node(), config, "", doc.cos);
            }
            else if (kind == "class")
            {
                recurse = true;
                doc.cos.is_class = true;
                parse_element(node->first_node(), config, "", doc.cos);
            }
        }
        else if (nodename == "memberdef")
        {
            std::string kind = get_attribute(node, "kind");
            if (kind == "function")
            {
                function f;
                parse_element(node->first_node(), config, "", f);
                parse_function(node->first_node(), config, "", f);
                if (member)
                {
                    bool c_or_d = boost::equals(f.name, doc.cos.name) ||
                        boost::equals(f.name, std::string("~") + doc.cos.name);

                    f.type = c_or_d
                        ? function_constructor_destructor 
                        : function_member;
                    doc.cos.functions.push_back(f);
                }
                else
                {
                    f.type = function_free;
                    doc.functions.push_back(f);
                }
            }
            else if (kind == "define")
            {
                function f;
                f.type = function_define;
                parse_element(node->first_node(), config, "", f);
                parse_function(node->first_node(), config, "", f);
                doc.functions.push_back(f);
            }
            else if (kind == "enum")
            {
                enumeration e;
                parse_element(node->first_node(), config, "", e);
                parse_enumeration(node->first_node(), config, "", e);
                doc.enumerations.push_back(e);
            }
            else if (kind == "typedef")
            {
                if (boost::equals(get_attribute(node, "prot"), "public"))
                {
                    std::string name = parse_named_node(node->first_node(), "name");
                    doc.cos.typedefs.push_back(base_element(name));
                    element dummy;
                    parse_element(node->first_node(), config, "", dummy);
                    doc.cos.typedefs.back().brief_description = dummy.brief_description;
                }
            }
            else if (kind == "variable")
            {
                if (boost::equals(get_attribute(node, "static"), "yes")
                    && boost::equals(get_attribute(node, "mutable"), "no")
                    && boost::equals(get_attribute(node, "prot"), "public"))
                {
                    std::string name = parse_named_node(node->first_node(), "name");
                    doc.cos.variables.push_back(base_element(name));
                }
            }

        }
        else if (nodename == "compoundname")
        {
            std::string name = node->value();
            if (name.find("::") != std::string::npos)
            {
                doc.cos.fullname = name;

                // For a class, it should have "boost::something::" before
                // set its name without namespace
                doc.cos.name = keep_after(name, "::");
            }
        }
        else if (nodename == "basecompoundref")
        {
            base_class bc;
            bc.name = node->value();
            bc.derivation = get_attribute(node, "prot");
            bc.virtuality = get_attribute(node, "virt");
            doc.cos.base_classes.push_back(bc);
        }
        else
        {
            //std::cout << nodename << " ignored." << std::endl;
        }


        if (recurse)
        {
            // First recurse into childnodes, then handle next siblings
            parse(node->first_node(), config, doc, is_member);
        }
        parse(node->next_sibling(), config, doc, is_member);
    }
}

#endif // DOXYGEN_XML_PARSER_HPP
