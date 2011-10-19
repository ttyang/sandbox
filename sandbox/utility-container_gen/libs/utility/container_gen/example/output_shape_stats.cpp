//=======================================================================
// Copyright (C) 2011 Cromwell D. Enage
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <iostream>
#include <string>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <boost/range/numeric.hpp>
#include <boost/utility/ptr_container_gen.hpp>

//[example__output_shape_stats__type_definitions
struct my_shape
{
    virtual ~my_shape()
    {
    }

    virtual double compute_perimeter() const = 0;

    virtual double compute_area() const = 0;
};

class your_square : public my_shape
{
    double length;

 public:
    explicit your_square(double s = 1.0) : length(s)
    {
    }

    double compute_perimeter() const
    {
        return length * 4.0;
    }

    double compute_area() const
    {
        return length * length;
    }
};

class your_circle : public my_shape
{
    double radius;

 public:
    explicit your_circle(double r = 1.0) : radius(r)
    {
    }

    double compute_perimeter() const
    {
        return boost::math::constants::pi<double>() * radius * 2.0;
    }

    double compute_area() const
    {
        return boost::math::constants::pi<double>() * radius * radius;
    }
};

class some_right_triangle : public my_shape
{
    double base;
    double height;

 public:
    some_right_triangle(double b, double h) : base(b), height(h)
    {
    }

    some_right_triangle() : base(1.0), height(1.0)
    {
    }

    double compute_perimeter() const
    {
        using namespace std;
        return sqrt(base * base + height * height) + base + height;
    }

    double compute_area() const
    {
        return boost::math::constants::half<double>() * base * height;
    }
};
//]

//[example__output_shape_stats__functions
double add_perimeter(double value, my_shape const& shape)
{
    return shape.compute_perimeter() + value;
}

double add_area(double value, my_shape const& shape)
{
    return shape.compute_area() + value;
}

template <typename Shapes>
void output_shape_stats(Shapes const& shapes)
{
    std::cout << "Total perimeter length = " << boost::accumulate(
        shapes
      , 0.0
      , add_perimeter
    ) << std::endl;
    std::cout << "Total area = " << boost::accumulate(
        shapes
      , 0.0
      , add_area
    ) << std::endl;
}
//]

//[example__output_shape_stats__usage
int main(int, char**)
{
    boost::ptr_container_gen<boost::listS,my_shape>::type shapes;

    shapes.push_back(new your_square());
    shapes.push_back(new your_circle());
    shapes.push_back(new some_right_triangle());

    output_shape_stats(shapes);
    return 0;
}
//]

