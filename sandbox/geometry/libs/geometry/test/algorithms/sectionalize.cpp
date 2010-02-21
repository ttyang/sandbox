// Boost.Geometry (aka GGL, Generic Geometry Library) test file
//
// Copyright Barend Gehrels 2007-2009, Geodan, Amsterdam, the Netherlands
// Copyright Bruno Lalande 2008, 2009
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>


#include <geometry_test_common.hpp>

#include <boost/geometry/algorithms/make.hpp>
#include <boost/geometry/algorithms/sectionalize.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/extensions/gis/io/wkt/read_wkt.hpp>
#include <boost/geometry/extensions/gis/io/wkt/write_wkt.hpp>

#include <test_common/test_point.hpp>

template <int DimensionCount, typename G>
void test_sectionalize(G const& g, std::size_t section_count,
        std::string const& index_check, std::string const& dir_check,
        bool sort = false)
{
    typedef typename boost::geometry::point_type<G>::type point;
    typedef boost::geometry::box<point> box;
    typedef boost::geometry::sections<box, DimensionCount> sections;

    sections s;
    boost::geometry::sectionalize(g, s);

    BOOST_CHECK_EQUAL(s.size(), section_count);

    // Output streams for sections, boxes, other
    std::ostringstream out_sections;
    std::ostringstream out_boxes;
    std::ostringstream out_dirs;

    if (sort)
    {
        //std::sort(boost::begin(s), boost::end(s)); NOW DONE WITH comparator
    }

    for (typename sections::size_type i = 0; i < s.size(); i++)
    {
        box const& b = s[i].bounding_box;

        if (i > 0)
        {
            out_sections << "|";
            out_dirs << "|";
            out_boxes << "|";
        }

        out_sections << s[i].begin_index << ".." << s[i].end_index;
        out_boxes << boost::geometry::get<0,0>(b) << " " << boost::geometry::get<0,1>(b)
            << ".." << boost::geometry::get<1,0>(b) << " " << boost::geometry::get<1,1>(b);
        for (int d = 0; d < DimensionCount; d++)
        {
            out_dirs << (d == 0 ? "" : " ");
            switch(s[i].directions[d])
            {
                case -99: out_dirs << "DUP"; break;
                case -1 : out_dirs << "-"; break;
                case  0 : out_dirs << "."; break;
                case +1 : out_dirs << "+"; break;
            }
        }
    }

    if (! index_check.empty())
    {
        BOOST_CHECK_EQUAL(out_sections.str(), index_check);
    }
    if (! dir_check.empty())
    {
        BOOST_CHECK_EQUAL(out_dirs.str(), dir_check);
    }
    else
    {
        if (out_sections.str().length() < 80)
        {
            std::cout << std::endl << boost::geometry::wkt(g) << std::endl;
            std::cout << out_sections.str() << std::endl;
            //std::cout << out_boxes.str() << std::endl;
        }
        std::cout << out_dirs.str() << std::endl;
    }
}

template <typename G>
void test_sectionalize(std::string const& wkt,
        std::size_t count2, std::string const& s2, std::string const d2,
        std::size_t count1, std::string const& s1, std::string const d1,
        bool sort = false)
{
    G g;
    boost::geometry::read_wkt(wkt, g);
    test_sectionalize<2>(g, count2, s2, d2, sort);
    test_sectionalize<1>(g, count1, s1, d1, sort);
}

template <typename P>
void test_all()
{
    test_sectionalize<boost::geometry::polygon<P> >(
        "POLYGON((0 0,0 380,400 380,400 0,0 0),(1 1,7 5,5 7,1 1),(1 11,7 15,5 17,1 11),(1 21,7 25,5 27,1 21),(1 31,7 35,5 37,1 31),(1 41,7 45,5 47,1 41),(1 51,7 55,5 57,1 51),(1 61,7 65,5 67,1 61),(1 71,7 75,5 77,1 71),(1 81,7 85,5 87,1 81),(1 91,7 95,5 97,1 91),(1 101,7 105,5 107,1 101),(1 111,7 115,5 117,1 111),(1 121,7 125,5 127,1 121),(1 131,7 135,5 137,1 131),(1 141,7 145,5 147,1 141),(1 151,7 155,5 157,1 151),(1 161,7 165,5 167,1 161),(1 171,7 175,5 177,1 171),(1 181,7 185,5 187,1 181),(11 1,17 5,15 7,11 1),(11 11,17 15,15 17,11 11),(11 21,17 25,15 27,11 21),(11 31,17 35,15 37,11 31),(11 41,17 45,15 47,11 41),(11 51,17 55,15 57,11 51),(11 61,17 65,15 67,11 61),(11 71,17 75,15 77,11 71),(11 81,17 85,15 87,11 81),(11 91,17 95,15 97,11 91),(11 101,17 105,15 107,11 101),(11 111,17 115,15 117,11 111),(11 121,17 125,15 127,11 121),(11 131,17 135,15 137,11 131),(11 141,17 145,15 147,11 141),(11 151,17 155,15 157,11 151),(11 161,17 165,15 167,11 161),(11 171,17 175,15 177,11 171),(11 181,17 185,15 187,11 181),(21 1,27 5,25 7,21 1),(21 11,27 15,25 17,21 11),(21 21,27 25,25 27,21 21),(21 31,27 35,25 37,21 31),(21 41,27 45,25 47,21 41),(21 51,27 55,25 57,21 51),(21 61,27 65,25 67,21 61),(21 71,27 75,25 77,21 71),(21 81,27 85,25 87,21 81),(21 91,27 95,25 97,21 91),(21 101,27 105,25 107,21 101),(21 111,27 115,25 117,21 111),(21 121,27 125,25 127,21 121),(21 131,27 135,25 137,21 131),(21 141,27 145,25 147,21 141),(21 151,27 155,25 157,21 151),(21 161,27 165,25 167,21 161),(21 171,27 175,25 177,21 171),(21 181,27 185,25 187,21 181),(31 1,37 5,35 7,31 1),(31 11,37 15,35 17,31 11),(31 21,37 25,35 27,31 21),(31 31,37 35,35 37,31 31),(31 41,37 45,35 47,31 41),(31 51,37 55,35 57,31 51),(31 61,37 65,35 67,31 61),(31 71,37 75,35 77,31 71),(31 81,37 85,35 87,31 81),(31 91,37 95,35 97,31 91),(31 101,37 105,35 107,31 101),(31 111,37 115,35 117,31 111),(31 121,37 125,35 127,31 121),(31 131,37 135,35 137,31 131),(31 141,37 145,35 147,31 141),(31 151,37 155,35 157,31 151),(31 161,37 165,35 167,31 161),(31 171,37 175,35 177,31 171),(31 181,37 185,35 187,31 181),(41 1,47 5,45 7,41 1),(41 11,47 15,45 17,41 11),(41 21,47 25,45 27,41 21),(41 31,47 35,45 37,41 31),(41 41,47 45,45 47,41 41),(41 51,47 55,45 57,41 51),(41 61,47 65,45 67,41 61),(41 71,47 75,45 77,41 71),(41 81,47 85,45 87,41 81),(41 91,47 95,45 97,41 91),(41 101,47 105,45 107,41 101),(41 111,47 115,45 117,41 111),(41 121,47 125,45 127,41 121),(41 131,47 135,45 137,41 131),(41 141,47 145,45 147,41 141),(41 151,47 155,45 157,41 151),(41 161,47 165,45 167,41 161),(41 171,47 175,45 177,41 171),(41 181,47 185,45 187,41 181),(51 1,57 5,55 7,51 1),(51 11,57 15,55 17,51 11),(51 21,57 25,55 27,51 21),(51 31,57 35,55 37,51 31),(51 41,57 45,55 47,51 41),(51 51,57 55,55 57,51 51),(51 61,57 65,55 67,51 61),(51 71,57 75,55 77,51 71),(51 81,57 85,55 87,51 81),(51 91,57 95,55 97,51 91),(51 101,57 105,55 107,51 101),(51 111,57 115,55 117,51 111),(51 121,57 125,55 127,51 121),(51 131,57 135,55 137,51 131),(51 141,57 145,55 147,51 141),(51 151,57 155,55 157,51 151),(51 161,57 165,55 167,51 161),(51 171,57 175,55 177,51 171),(51 181,57 185,55 187,51 181),(61 1,67 5,65 7,61 1),(61 11,67 15,65 17,61 11),(61 21,67 25,65 27,61 21),(61 31,67 35,65 37,61 31),(61 41,67 45,65 47,61 41),(61 51,67 55,65 57,61 51),(61 61,67 65,65 67,61 61),(61 71,67 75,65 77,61 71),(61 81,67 85,65 87,61 81),(61 91,67 95,65 97,61 91),(61 101,67 105,65 107,61 101),(61 111,67 115,65 117,61 111),(61 121,67 125,65 127,61 121),(61 131,67 135,65 137,61 131),(61 141,67 145,65 147,61 141),(61 151,67 155,65 157,61 151),(61 161,67 165,65 167,61 161),(61 171,67 175,65 177,61 171),(61 181,67 185,65 187,61 181),(71 1,77 5,75 7,71 1),(71 11,77 15,75 17,71 11),(71 21,77 25,75 27,71 21),(71 31,77 35,75 37,71 31),(71 41,77 45,75 47,71 41),(71 51,77 55,75 57,71 51),(71 61,77 65,75 67,71 61),(71 71,77 75,75 77,71 71),(71 81,77 85,75 87,71 81),(71 91,77 95,75 97,71 91),(71 101,77 105,75 107,71 101),(71 111,77 115,75 117,71 111),(71 121,77 125,75 127,71 121),(71 131,77 135,75 137,71 131),(71 141,77 145,75 147,71 141),(71 151,77 155,75 157,71 151),(71 161,77 165,75 167,71 161),(71 171,77 175,75 177,71 171),(71 181,77 185,75 187,71 181),(81 1,87 5,85 7,81 1),(81 11,87 15,85 17,81 11),(81 21,87 25,85 27,81 21),(81 31,87 35,85 37,81 31),(81 41,87 45,85 47,81 41),(81 51,87 55,85 57,81 51),(81 61,87 65,85 67,81 61),(81 71,87 75,85 77,81 71),(81 81,87 85,85 87,81 81),(81 91,87 95,85 97,81 91),(81 101,87 105,85 107,81 101),(81 111,87 115,85 117,81 111),(81 121,87 125,85 127,81 121),(81 131,87 135,85 137,81 131),(81 141,87 145,85 147,81 141),(81 151,87 155,85 157,81 151),(81 161,87 165,85 167,81 161),(81 171,87 175,85 177,81 171),(81 181,87 185,85 187,81 181),(91 1,97 5,95 7,91 1),(91 11,97 15,95 17,91 11),(91 21,97 25,95 27,91 21),(91 31,97 35,95 37,91 31),(91 41,97 45,95 47,91 41),(91 51,97 55,95 57,91 51),(91 61,97 65,95 67,91 61),(91 71,97 75,95 77,91 71),(91 81,97 85,95 87,91 81),(91 91,97 95,95 97,91 91),(91 101,97 105,95 107,91 101),(91 111,97 115,95 117,91 111),(91 121,97 125,95 127,91 121),(91 131,97 135,95 137,91 131),(91 141,97 145,95 147,91 141),(91 151,97 155,95 157,91 151),(91 161,97 165,95 167,91 161),(91 171,97 175,95 177,91 171),(91 181,97 185,95 187,91 181),(101 1,107 5,105 7,101 1),(101 11,107 15,105 17,101 11),(101 21,107 25,105 27,101 21),(101 31,107 35,105 37,101 31),(101 41,107 45,105 47,101 41),(101 51,107 55,105 57,101 51),(101 61,107 65,105 67,101 61),(101 71,107 75,105 77,101 71),(101 81,107 85,105 87,101 81),(101 91,107 95,105 97,101 91),(101 101,107 105,105 107,101 101),(101 111,107 115,105 117,101 111),(101 121,107 125,105 127,101 121),(101 131,107 135,105 137,101 131),(101 141,107 145,105 147,101 141),(101 151,107 155,105 157,101 151),(101 161,107 165,105 167,101 161),(101 171,107 175,105 177,101 171),(101 181,107 185,105 187,101 181),(111 1,117 5,115 7,111 1),(111 11,117 15,115 17,111 11),(111 21,117 25,115 27,111 21),(111 31,117 35,115 37,111 31),(111 41,117 45,115 47,111 41),(111 51,117 55,115 57,111 51),(111 61,117 65,115 67,111 61),(111 71,117 75,115 77,111 71),(111 81,117 85,115 87,111 81),(111 91,117 95,115 97,111 91),(111 101,117 105,115 107,111 101),(111 111,117 115,115 117,111 111),(111 121,117 125,115 127,111 121),(111 131,117 135,115 137,111 131),(111 141,117 145,115 147,111 141),(111 151,117 155,115 157,111 151),(111 161,117 165,115 167,111 161),(111 171,117 175,115 177,111 171),(111 181,117 185,115 187,111 181),(121 1,127 5,125 7,121 1),(121 11,127 15,125 17,121 11),(121 21,127 25,125 27,121 21),(121 31,127 35,125 37,121 31),(121 41,127 45,125 47,121 41),(121 51,127 55,125 57,121 51),(121 61,127 65,125 67,121 61),(121 71,127 75,125 77,121 71),(121 81,127 85,125 87,121 81),(121 91,127 95,125 97,121 91),(121 101,127 105,125 107,121 101),(121 111,127 115,125 117,121 111),(121 121,127 125,125 127,121 121),(121 131,127 135,125 137,121 131),(121 141,127 145,125 147,121 141),(121 151,127 155,125 157,121 151),(121 161,127 165,125 167,121 161),(121 171,127 175,125 177,121 171),(121 181,127 185,125 187,121 181),(131 1,137 5,135 7,131 1),(131 11,137 15,135 17,131 11),(131 21,137 25,135 27,131 21),(131 31,137 35,135 37,131 31),(131 41,137 45,135 47,131 41),(131 51,137 55,135 57,131 51),(131 61,137 65,135 67,131 61),(131 71,137 75,135 77,131 71),(131 81,137 85,135 87,131 81),(131 91,137 95,135 97,131 91),(131 101,137 105,135 107,131 101),(131 111,137 115,135 117,131 111),(131 121,137 125,135 127,131 121),(131 131,137 135,135 137,131 131),(131 141,137 145,135 147,131 141),(131 151,137 155,135 157,131 151),(131 161,137 165,135 167,131 161),(131 171,137 175,135 177,131 171),(131 181,137 185,135 187,131 181),(141 1,147 5,145 7,141 1),(141 11,147 15,145 17,141 11),(141 21,147 25,145 27,141 21),(141 31,147 35,145 37,141 31),(141 41,147 45,145 47,141 41),(141 51,147 55,145 57,141 51),(141 61,147 65,145 67,141 61),(141 71,147 75,145 77,141 71),(141 81,147 85,145 87,141 81),(141 91,147 95,145 97,141 91),(141 101,147 105,145 107,141 101),(141 111,147 115,145 117,141 111),(141 121,147 125,145 127,141 121),(141 131,147 135,145 137,141 131),(141 141,147 145,145 147,141 141),(141 151,147 155,145 157,141 151),(141 161,147 165,145 167,141 161),(141 171,147 175,145 177,141 171),(141 181,147 185,145 187,141 181),(151 1,157 5,155 7,151 1),(151 11,157 15,155 17,151 11),(151 21,157 25,155 27,151 21),(151 31,157 35,155 37,151 31),(151 41,157 45,155 47,151 41),(151 51,157 55,155 57,151 51),(151 61,157 65,155 67,151 61),(151 71,157 75,155 77,151 71),(151 81,157 85,155 87,151 81),(151 91,157 95,155 97,151 91),(151 101,157 105,155 107,151 101),(151 111,157 115,155 117,151 111),(151 121,157 125,155 127,151 121),(151 131,157 135,155 137,151 131),(151 141,157 145,155 147,151 141),(151 151,157 155,155 157,151 151),(151 161,157 165,155 167,151 161),(151 171,157 175,155 177,151 171),(151 181,157 185,155 187,151 181),(161 1,167 5,165 7,161 1),(161 11,167 15,165 17,161 11),(161 21,167 25,165 27,161 21),(161 31,167 35,165 37,161 31),(161 41,167 45,165 47,161 41),(161 51,167 55,165 57,161 51),(161 61,167 65,165 67,161 61),(161 71,167 75,165 77,161 71),(161 81,167 85,165 87,161 81),(161 91,167 95,165 97,161 91),(161 101,167 105,165 107,161 101),(161 111,167 115,165 117,161 111),(161 121,167 125,165 127,161 121),(161 131,167 135,165 137,161 131),(161 141,167 145,165 147,161 141),(161 151,167 155,165 157,161 151),(161 161,167 165,165 167,161 161),(161 171,167 175,165 177,161 171),(161 181,167 185,165 187,161 181),(171 1,177 5,175 7,171 1),(171 11,177 15,175 17,171 11),(171 21,177 25,175 27,171 21),(171 31,177 35,175 37,171 31),(171 41,177 45,175 47,171 41),(171 51,177 55,175 57,171 51),(171 61,177 65,175 67,171 61),(171 71,177 75,175 77,171 71),(171 81,177 85,175 87,171 81),(171 91,177 95,175 97,171 91),(171 101,177 105,175 107,171 101),(171 111,177 115,175 117,171 111),(171 121,177 125,175 127,171 121),(171 131,177 135,175 137,171 131),(171 141,177 145,175 147,171 141),(171 151,177 155,175 157,171 151),(171 161,177 165,175 167,171 161),(171 171,177 175,175 177,171 171),(171 181,177 185,175 187,171 181),(181 1,187 5,185 7,181 1),(181 11,187 15,185 17,181 11),(181 21,187 25,185 27,181 21),(181 31,187 35,185 37,181 31),(181 41,187 45,185 47,181 41),(181 51,187 55,185 57,181 51),(181 61,187 65,185 67,181 61),(181 71,187 75,185 77,181 71),(181 81,187 85,185 87,181 81),(181 91,187 95,185 97,181 91),(181 101,187 105,185 107,181 101),(181 111,187 115,185 117,181 111),(181 121,187 125,185 127,181 121),(181 131,187 135,185 137,181 131),(181 141,187 145,185 147,181 141),(181 151,187 155,185 157,181 151),(181 161,187 165,185 167,181 161),(181 171,187 175,185 177,181 171),(181 181,187 185,185 187,181 181),(191 1,197 5,195 7,191 1),(191 11,197 15,195 17,191 11),(191 21,197 25,195 27,191 21),(191 31,197 35,195 37,191 31),(191 41,197 45,195 47,191 41),(191 51,197 55,195 57,191 51),(191 61,197 65,195 67,191 61),(191 71,197 75,195 77,191 71),(191 81,197 85,195 87,191 81),(191 91,197 95,195 97,191 91),(191 101,197 105,195 107,191 101),(191 111,197 115,195 117,191 111),(191 121,197 125,195 127,191 121),(191 131,197 135,195 137,191 131),(191 141,197 145,195 147,191 141),(191 151,197 155,195 157,191 151),(191 161,197 165,195 167,191 161),(191 171,197 175,195 177,191 171),(191 181,197 185,195 187,191 181))",
        1144, "", "",
        764, "", "", true);


    test_sectionalize<boost::geometry::linestring<P> >(
        "LINESTRING(1 1,2 2,3 0,5 0,5 8)",
        4, "0..1|1..2|2..3|3..4", "+ +|+ -|+ .|. +",
        2, "0..3|3..4", "+|.");

    test_sectionalize<boost::geometry::polygon<P> >(
        "POLYGON((0 0,0 7,4 2,2 0,0 0))",
        4, "0..1|1..2|2..3|3..4", ". +|+ -|- -|- .",
        //            .   +   -   -   -> 3 sections
        3, "0..1|1..2|2..4", ".|+|-");

    test_sectionalize<boost::geometry::polygon<P> >
        ("polygon((2.0 1.3, 2.4 1.7, 2.8 1.8, 3.4 1.2, 3.7 1.6,3.4 2.0, 4.1 3.0, 5.3 2.6, 5.4 1.2, 4.9 0.8, 2.9 0.7,2.0 1.3))",
        8, "0..2|2..3|3..4|4..5|5..6|6..8|8..10|10..11", "+ +|+ -|+ +|- +|+ +|+ -|- -|- +",
        4, "0..4|4..5|5..8|8..11", "+|-|+|-");


    test_sectionalize<boost::geometry::polygon<P> >(
        "POLYGON((3 1,2 2,1 3,2 4,3 5,4 4,5 3,4 2,3 1))",
        4, "0..2|2..4|4..6|6..8", "- +|+ +|+ -|- -",
        //        -   -   -   +   +   +   +   -   - -> 3 sections
        3, "0..2|2..6|6..8", "-|+|-");

    // With holes
    test_sectionalize<boost::geometry::polygon<P> >(
        "POLYGON((3 1,2 2,1 3,2 4,3 5,4 4,5 3,4 2,3 1), (3 2,2 2,3 4,3 2))",
        7, "0..2|2..4|4..6|6..8|0..1|1..2|2..3", "- +|+ +|+ -|- -|- .|+ +|. -",
        //        -   -   -   +   +   +   +   -   -          -   +   . -> 6 sections
        6, "0..2|2..6|6..8|0..1|1..2|2..3", "-|+|-|-|+|.");

    // With duplicates
    test_sectionalize<boost::geometry::linestring<P> >(
        "LINESTRING(1 1,2 2,3 0,3 0,5 0,5 8)",
        5, "0..1|1..2|2..3|3..4|4..5", "+ +|+ -|DUP DUP|+ .|. +",
        4, "0..2|2..3|3..4|4..5", "+|DUP|+|.");
    // With two subsequent duplicate segments
    test_sectionalize<boost::geometry::linestring<P> >(
        "LINESTRING(1 1,2 2,3 0,3 0,3 0,5 0,5 0,5 0,5 0,5 8)",
        6, "0..1|1..2|2..4|4..5|5..8|8..9", "+ +|+ -|DUP DUP|+ .|DUP DUP|. +",
        5, "0..2|2..4|4..5|5..8|8..9", "+|DUP|+|DUP|.");


    typedef boost::geometry::box<P> B;
    test_sectionalize<2, B>(boost::geometry::make<B>(0,0,4,4),
            4, "0..1|1..2|2..3|3..4", ". +|+ .|. -|- .");
    test_sectionalize<1, B>(boost::geometry::make<B>(0,0,4,4),
            4, "0..1|1..2|2..3|3..4", ".|+|.|-");
}

int test_main(int, char* [])
{
    //test_all<boost::geometry::point_xy<float> >();
    test_all<boost::geometry::point_xy<double> >();

    return 0;
}
