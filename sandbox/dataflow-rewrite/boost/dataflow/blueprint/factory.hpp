/*=================================---------------------------------------------
    Copyright 2007,2008 Stjepan Rajko
  
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
-----------------------------------------------===============================*/

#ifndef BOOST__DATAFLOW__BLUEPRINT__FACTORY_HPP
#define BOOST__DATAFLOW__BLUEPRINT__FACTORY_HPP


#include <boost/dataflow/blueprint/port_adapter.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/functional/factory.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <map>
#include <memory>

namespace boost { namespace dataflow { namespace blueprint {

template<typename Map>
class key_iterator
    : public boost::iterator_adaptor<
        key_iterator<Map>                    // Derived
      , typename Map::const_iterator
      , const typename Map::key_type              // Value
      , boost::use_default
    >
{
public:
    key_iterator()
      : key_iterator::iterator_adaptor_() {}

    explicit key_iterator(typename Map::const_iterator it)
      : key_iterator::iterator_adaptor_(it) {}

    typename key_iterator::reference dereference() const
    {
        return key_iterator::base_reference()->first;
    }

 private:
    friend class boost::iterator_core_access;
};

template<typename BlueprintFramework>
class factory
{
    typedef typename BlueprintFramework::framework_type framework_type;
    typedef framework_entity<BlueprintFramework> entity_type;
    typedef boost::function<entity_type * (framework_object<BlueprintFramework> &)> function_type;
    typedef std::map<std::string, function_type> map_type;
public:
    typedef key_iterator<map_type> iterator;
    
    std::auto_ptr<entity_type> make(const std::string &key)
    {
        std::auto_ptr<entity_type> ret(m_components[key]());
        return ret;
    }
    key_iterator<map_type> begin()
    {   return key_iterator<map_type>(m_components.begin()); }
    key_iterator<map_type> end()
    {   return key_iterator<map_type>(m_components.end()); }
    function_type operator[](const std::string& k)
    {   return m_components[k]; }

    template<typename T>
    void add_port(const std::string &s)
    {
        m_components[s] = boost::bind(boost::factory<port_adapter<BlueprintFramework, T> *>(), _1);
    }
    template<typename T, typename T0>
    void add_port(const std::string &s, const T0 &t0)
    {
        m_components[s] = boost::bind(boost::factory<port_adapter<BlueprintFramework, T> *>(), _1, t0);
    }

protected:
    map_type m_components;
};


} } } // namespace boost::dataflow::blueprint

#endif // BOOST_DATAFLOW_BLUEPRINT_COMPONENT_BANK_HPP

