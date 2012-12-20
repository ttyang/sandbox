#include<boost/container/static_vector.hpp>

#include <boost/timer.hpp>
#include <fstream>
#include <iostream>

using namespace boost::container;

template <typename T>
class value
{
public:
    explicit value(T a = 0) : aa(a) {}
    value(value const& v) : aa(v.aa) {}
    value & operator=(value const& v) { aa = v.aa; return *this; }
    ~value() {}
    bool operator==(value const& v) const { return aa == v.aa; }
    operator T () { return aa; }
private:
    T aa;
};

template <typename T>
class value2
{
public:
    explicit value2(T a = 0) : aa(a) {}
    bool operator==(value2 const& v) const { return aa == v.aa; }
    operator T () { return aa; }
private:
    T aa;
};

template <typename V, size_t N>
size_t test(size_t count)
{
    static_vector<V, N> sv;
    for ( size_t i = 0 ; i < sv.capacity() ; ++i)
        sv.push_back(V(i));

    size_t dummy = 0;
    for ( size_t i = 0 ; i < count ; ++i )
    {
        static_vector<V, N> sv2(sv);
        sv2.assign(sv.begin(), sv.end());
        dummy += sv2[0];
    }

    return dummy;
};

int main()
{
    size_t count = 2000000;

    std::fstream f("foobar.txt", std::ios::in | std::ios::out);
    f >> count;

    for(;;)
    {
        {
            boost::timer tim;
            size_t dummy = test<size_t, 1000>(count);
            double t = tim.elapsed();
            std::cout << t << "    " << dummy << std::endl;
        }
        {
            boost::timer tim;
            size_t dummy = test<value<size_t>, 1000>(count);
            double t = tim.elapsed();
            std::cout << t << "    " << dummy << std::endl;
        }
        {
            boost::timer tim;
            size_t dummy = test<value2<size_t>, 1000>(count);
            double t = tim.elapsed();
            std::cout << t << "    " << dummy << std::endl;
        }
    }
    
}
