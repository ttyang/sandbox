// Boost.Pinhole library

// Copyright Jared McIntyre 2007. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_TEST_MODULE PinholeLib

#include <boost/pinhole/property_group.hpp>
#include <boost/pinhole/property_manager.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost;
using namespace boost::pinhole;

// I can hide these two line if I don't do everything in headers
boost::shared_ptr<property_manager> property_manager::m_instance(new property_manager);
event_source* event_source::m_instance = 0;

class TestGroup : public property_group
{
public:
#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning( disable: 4355 )
#endif
	TestGroup() : property_group( "PropertyGroupName", NULL )
	{
        m_int_Func = 0;
	    m_int_Var  = 0;

		add_property("Int_Func", "Int1 description", BOOST_SETTER(&TestGroup::SetInt), BOOST_GETTER(&TestGroup::GetInt), NULL );
		add_property("Int_Var",  "Int2 description", BOOST_SETTER_VAR(m_int_Var),      BOOST_GETTER_VAR(m_int_Var),     NULL );
	}
#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif

	void SetInt( int x ){ m_int_Func = x; }
	int GetInt(){ return( m_int_Func ); }

private:
	int m_int_Func;
	int m_int_Var;
};

BOOST_AUTO_TEST_CASE( TestIntegerSetGet_Func )
{
    TestGroup testGroup;

	testGroup.set( "Int_Func", 1 );
	BOOST_CHECK( 1 == testGroup.get<int>( "Int_Func") );
    
	testGroup.set_as_string( "Int_Func", "2" );
	BOOST_CHECK( "2" == testGroup.get_as_string( "Int_Func") );
}

BOOST_AUTO_TEST_CASE( TestIntegerSetGet_Var )
{
    TestGroup testGroup;

	testGroup.set( "Int_Var", 1 );
	BOOST_CHECK( 1 == testGroup.get<int>( "Int_Var") );
    
	testGroup.set_as_string( "Int_Var", "2" );
	BOOST_CHECK( "2" == testGroup.get_as_string( "Int_Var") );
}

BOOST_AUTO_TEST_CASE( TestIntegerEditorType )
{
    TestGroup testGroup;
    
    BOOST_CHECK( typeid(bool) != testGroup.get_type_info("Int_Func") );
    BOOST_CHECK( typeid(int) == testGroup.get_type_info("Int_Func") );
    BOOST_CHECK( typeid(float) != testGroup.get_type_info("Int_Func") );
    BOOST_CHECK( typeid(double) != testGroup.get_type_info("Int_Func") );
    BOOST_CHECK( typeid(std::string) != testGroup.get_type_info("Int_Func") );
}

BOOST_AUTO_TEST_CASE( TestInvalidSet )
{
    TestGroup testGroup;
    
	BOOST_CHECK_THROW( testGroup.set_as_string( "Int_Func", "Foo" ), std::invalid_argument );
}
