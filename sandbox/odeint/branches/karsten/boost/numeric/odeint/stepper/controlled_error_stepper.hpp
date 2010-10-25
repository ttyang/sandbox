/*
 boost header: NUMERIC_ODEINT_STEPPER/controlled_error_stepper.hpp

 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky
 Copyright 2009 Andre Bergner

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_ERROR_STEPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_ERROR_STEPPER_HPP_INCLUDED

#include <cmath>

#include <boost/noncopyable.hpp>

#include <boost/numeric/odeint/stepper/adjust_size.hpp>
#include <boost/numeric/odeint/stepper/error_checker.hpp>
#include <boost/numeric/odeint/stepper/base/stepper_categories.hpp>

namespace boost {
namespace numeric {
namespace odeint {

typedef enum
{
    success_step_size_unchanged ,
    step_size_decreased ,
    success_step_size_increased
} controlled_step_result;


/* error stepper category dispatcher */
template<
    class ErrorStepper ,
    class ErrorChecker = error_checker_standard< typename ErrorStepper::state_type ,
                                                   typename ErrorStepper::time_type ,
                                                   typename ErrorStepper::algebra_type ,
                                                   typename ErrorStepper::operations_type > ,
    class ErrorStepperCategory = typename ErrorStepper::stepper_category
>
class controlled_error_stepper { };



/****************************/
/* explicit stepper version */

template<
	class ErrorStepper ,
	class ErrorChecker
	>
class controlled_error_stepper< ErrorStepper , ErrorChecker , explicit_error_stepper_tag > : boost::noncopyable
{
public:

	typedef ErrorStepper stepper_type;
	typedef typename stepper_type::state_type state_type;
	typedef typename stepper_type::time_type time_type;
	typedef typename stepper_type::order_type order_type;
	typedef typename stepper_type::adjust_size_policy adjust_size_policy;
	typedef ErrorChecker error_checker_type;


	// ToDo : check if stepper could be constructed by the controlled stepper
	controlled_error_stepper(
			stepper_type &stepper ,
			const error_checker_type &error_checker = error_checker_type()
			)
	: m_stepper( stepper ) , m_error_checker( error_checker ) ,
	  m_dxdt_size_adjuster() , m_xerr_size_adjuster() ,
	  m_dxdt() , m_x_old() , m_x_err()
	{
		boost::numeric::odeint::construct( m_dxdt );
		boost::numeric::odeint::construct( m_x_err );
		boost::numeric::odeint::construct( m_x_old );
		m_dxdt_size_adjuster.register_state( 0 , m_dxdt );
		m_xerr_size_adjuster.register_state( 0 , m_x_err );
	}

	~controlled_error_stepper( void )
	{
		boost::numeric::odeint::destruct( m_dxdt );
		boost::numeric::odeint::destruct( m_x_err );
		boost::numeric::odeint::destruct( m_x_old );
	}



	template< class System >
	controlled_step_result try_step( System &sys , state_type &x , const state_type &dxdt ,
                                      time_type &t , time_type &dt )
	{
		using std::max;
		using std::min;
		using std::pow;

		m_xerr_size_adjuster.adjust_size_by_policy( x , adjust_size_policy() );
		boost::numeric::odeint::copy( x , m_x_old );

		m_stepper.do_step( sys , x , dxdt , t , dt , m_x_err );

		// this potentially overwrites m_x_err! (standard_error_checker does, at least)
		time_type max_rel_err = m_error_checker.error( m_x_old , dxdt , m_x_err , dt );

		if( max_rel_err > 1.1 )
		{
			// error too large - decrease dt ,limit scaling factor to 0.2 and reset state
		    /* ToDo: for fsal steppers we have to do some resetting of dxdt */
			dt *= max( 0.9 * pow( max_rel_err , -1.0 / ( m_stepper.error_order() - 1.0 ) ) , 0.2 );
			boost::numeric::odeint::copy( m_x_old , x );
			return step_size_decreased;
		}
		else
		{
			if( max_rel_err < 0.5 )
			{
				//error too small - increase dt and keep the evolution and limit scaling factor to 5.0
				t += dt;
				dt *= min( 0.9 * pow( max_rel_err , -1.0 / m_stepper.stepper_order() ) , 5.0 );
				return success_step_size_increased;
			}
			else
			{
				t += dt;
				return success_step_size_unchanged;
			}
		}
	}

	template< class System >
	controlled_step_result try_step( System &sys , state_type &x , time_type &t , time_type &dt )
	{
		m_dxdt_size_adjuster.adjust_size_by_policy( x , adjust_size_policy() );
        sys( x , m_dxdt ,t );
        return try_step( sys , x , m_dxdt , t , dt );
	}

	void adjust_size( const state_type &x )
	{
        m_dxdt_size_adjuster.adjust_size( x );
        m_xerr_size_adjuster.adjust_size( x );
        m_stepper.adjust_size( x );
	}

	stepper_type& stepper( void )
	{
		return m_stepper;
	}

	const stepper_type& stepper( void ) const
	{
		return m_stepper;
	}


private:

	stepper_type &m_stepper;
	error_checker_type m_error_checker;

	size_adjuster< state_type , 1 > m_dxdt_size_adjuster;
	size_adjuster< state_type , 1 > m_xerr_size_adjuster;

	state_type m_dxdt;
	state_type m_x_old;
	state_type m_x_err;
};











/*********************************/
/* explicit stepper fsal version */

template<
    class ErrorStepper ,
    class ErrorChecker
    >
class controlled_error_stepper< ErrorStepper , ErrorChecker , explicit_error_stepper_fsal_tag > : boost::noncopyable
{
public:

    typedef ErrorStepper stepper_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::order_type order_type;
    typedef typename stepper_type::adjust_size_policy adjust_size_policy;
    typedef ErrorChecker error_checker_type;

    // ToDo : check if stepper could be constructed by the controlled stepper
    controlled_error_stepper(
            stepper_type &stepper ,
            const error_checker_type &error_checker = error_checker_type()
            )
    : m_stepper( stepper ) , m_error_checker( error_checker ) ,
      m_dxdt_size_adjuster() , m_xerr_size_adjuster() ,
      m_dxdt() , m_x_old() , m_x_err() ,
      m_first_call( true )
    {
        boost::numeric::odeint::construct( m_dxdt );
        boost::numeric::odeint::construct( m_x_err );
        boost::numeric::odeint::construct( m_x_old );
        m_dxdt_size_adjuster.register_state( 0 , m_dxdt );
        m_xerr_size_adjuster.register_state( 0 , m_x_err );
    }

    ~controlled_error_stepper( void )
    {
        boost::numeric::odeint::destruct( m_dxdt );
        boost::numeric::odeint::destruct( m_x_err );
        boost::numeric::odeint::destruct( m_x_old );
    }



    template< class System >
    controlled_step_result try_step( System &sys , state_type &x , state_type &dxdt ,
                                      time_type &t , time_type &dt )
    {
        using std::max;
        using std::min;
        using std::pow;

        m_xerr_size_adjuster.adjust_size_by_policy( x , adjust_size_policy() );
        boost::numeric::odeint::copy( x , m_x_old );
        //fsal: m_stepper.get_dxdt( dxdt );
        //fsal: m_stepper.do_step( sys , x , dxdt , t , dt , m_x_err );
        m_stepper.do_step( sys , x , dxdt , t , dt , m_x_err );

        // this potentially overwrites m_x_err! (standard_error_checker does, at least)
        time_type max_rel_err = m_error_checker.error( m_x_old , dxdt , m_x_err , dt );

        if( max_rel_err > 1.1 )
        {
            // error too large - decrease dt ,limit scaling factor to 0.2 and reset state
            /* ToDo: for fsal steppers we have to do some resetting of dxdt */
            dt *= max( 0.9 * pow( max_rel_err , -1.0 / ( m_stepper.error_order() - 1.0 ) ) , 0.2 );
            boost::numeric::odeint::copy( m_x_old , x );
            m_stepper.reset_step( dxdt );
            return step_size_decreased;
        }
        else
        {
            if( max_rel_err < 0.5 )
            {
                //error too small - increase dt and keep the evolution and limit scaling factor to 5.0
                t += dt;
                dt *= min( 0.9 * pow( max_rel_err , -1.0 / m_stepper.stepper_order() ) , 5.0 );
                return success_step_size_increased;
            }
            else
            {
                t += dt;
                return success_step_size_unchanged;
            }
        }
    }

    template< class System >
    controlled_step_result try_step( System &sys , state_type &x , time_type &t , time_type &dt )
    {
        if( m_dxdt_size_adjuster.adjust_size_by_policy( x , adjust_size_policy() ) || m_first_call )
        {
            sys( x , m_dxdt ,t );
            m_first_call = false;
        }
        return try_step( sys , x , m_dxdt , t , dt );
    }

    void adjust_size( const state_type &x )
    {
        bool changed = false;
        changed |= m_dxdt_size_adjuster.adjust_size( x );
        changed |= m_xerr_size_adjuster.adjust_size( x );
        changed |= m_stepper.adjust_size( x );
        if( changed )
            m_first_call = true;
    }

	stepper_type& stepper( void )
	{
		return m_stepper;
	}

	const stepper_type& stepper( void ) const
	{
		return m_stepper;
	}



private:

    stepper_type &m_stepper;
    error_checker_type m_error_checker;

    size_adjuster< state_type , 1 > m_dxdt_size_adjuster;
    size_adjuster< state_type , 1 > m_xerr_size_adjuster;

    state_type m_dxdt;
    state_type m_x_old;
    state_type m_x_err;
    bool m_first_call;
};




} // odeint
} // numeric
} // boost


#endif //BOOST_NUMERIC_ODEINT_STEPPER_CONTROLLED_ERROR_STEPPER_HPP_INCLUDED
