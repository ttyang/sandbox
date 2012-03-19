/*=============================================================
    Boost Overload
    Example - make_overload utility
==============================================================*/

//[ make_overload_cpp
#include <boost/detail/lightweight_test.hpp>
#include <boost/functional/hash.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

// You need this header file for the make_overload utility
#include <boost/overload/make_overload.hpp>


using std::size_t;


// A sample struct
struct Person
{
    std::string name;
    int age;
    bool student;
};

// Make the Person struct a Boost.Fusion sequence
BOOST_FUSION_ADAPT_STRUCT(
        Person,
        (std::string, name)
        (int, age)
        (bool, student)
)

// Creates a hash value by combining hash values
class hash_combine
{
  public:
    hash_combine(size_t& _seed)
        : m_seed(_seed)
    {}

    void operator()( size_t hv ) const
    {
        m_seed ^= hv + 0x9e3779b9 + (m_seed << 6) + (m_seed >> 2);
    }

  private:
    // boost::fusion::for_each needs a const reference function object
    volatile size_t& m_seed;
};

// It will be used to generate a hash value for each field of a Person object
typedef boost::overload<size_t (const std::string & ),
                        size_t (int ),
                        size_t (bool )>
        person_field_hash_function_type;

// Returns a hash value for an object of Person type
size_t hash(const Person & person, const person_field_hash_function_type & hf)
{
    using namespace boost::fusion;

    size_t seed = 0;
    hash_combine hc(seed);
    for_each( transform(person, hf), hc );
    return seed;
}


int main()
{
    Person Anna = {"Anna Rossi", 25, false};

    // We utilize make_overload to create an overload object on the fly
    std::size_t hv =
            hash( Anna,
                  boost::make_overload( boost::hash<std::string>(),
                                        boost::hash<int>(),
                                        boost::hash<bool>() ) );

    std::cout << Anna.name << " hash value: " << hv << std::endl;
    return boost::report_errors();
}
//]
