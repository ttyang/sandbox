/*
 boost header: numeric/odeint/stepper_rk78_fehlberg.hpp

 Copyright 2009 Karsten Ahnert
 Copyright 2009 Mario Mulansky
 Copyright 2009 Andre Bergner

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RK78_FEHLBERG_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RK78_FEHLBERG_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

    template<
        class Container ,
        class Time = double ,
        class Resizer = resizer< Container >
        >
    class stepper_rk78_fehlberg
    {
        // provide basic typedefs
    public:

        typedef Container container_type;
        typedef Resizer resizer_type;
        typedef Time time_type;
        typedef const unsigned short order_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::iterator iterator;





        // private members
    private:

        container_type m_dxdt;
        container_type m_xt;
        container_type m_k02 , m_k03 , m_k04 , m_k05 , m_k06 , m_k07 ,
            m_k08 , m_k09 , m_k10 , m_k11 , m_k12 , m_k13;

        resizer_type m_resizer;

        // the times at which system is called
        time_type m_t02 , m_t03 , m_t04 , m_t05 , m_t06 , m_t07 , m_t08 ,
            m_t09 , m_t10 , m_t11 , m_t12 , m_t13;




        // public interface
    public:

        order_type order() const { return 7; }

        template< class DynamicalSystem >
        void do_step( DynamicalSystem &system ,
                        container_type &x ,
                        container_type &dxdt ,
                        time_type t ,
                        time_type dt )
        {
            // the time constant
            const time_type a02 = static_cast<time_type>( 2.0 / 27.0 );
            const time_type a03 = static_cast<time_type>( 1.0 / 9.0 );
            const time_type a04 = static_cast<time_type>( 1.0 / 6.0 );
            const time_type a05 = static_cast<time_type>( 5.0 / 12.0 );
            const time_type a06 = static_cast<time_type>( 0.50 );
            const time_type a07 = static_cast<time_type>( 5.0 / 6.0 );
            const time_type a08 = static_cast<time_type>( 1.0 / 6.0 );
            const time_type a09 = static_cast<time_type>( 2.0 / 3.0 );
            const time_type a10 = static_cast<time_type>( 1.0 / 3.0 );

            // the weights for each step
            const time_type c06 = static_cast<time_type>( 34.0 / 105.0 );
            const time_type c07 = static_cast<time_type>( 9.0 / 35.0 );
            const time_type c08 = static_cast<time_type>( c07 );
            const time_type c09 = static_cast<time_type>( 9.0 / 280.0 );
            const time_type c10 = static_cast<time_type>( c09 );
            const time_type c12 = static_cast<time_type>( 41.0 / 840.0 );
            const time_type c13 = static_cast<time_type>( c12 );

            // the coefficients for each step
            const time_type b02_01 = static_cast<time_type>( 2.0 / 27.0 );

            const time_type b03_01 = static_cast<time_type>( 1.0 / 36.0 );
            const time_type b03_02 = static_cast<time_type>( 1.0 / 12.0 );

            const time_type b04_01 = static_cast<time_type>( 1.0 / 24.0 );
            const time_type b04_03 = static_cast<time_type>( 1.0 / 8.0 );

            const time_type b05_01 = static_cast<time_type>( 5.0 / 12.0 );
            const time_type b05_03 = static_cast<time_type>( -25.0 / 16.0 );
            const time_type b05_04 = static_cast<time_type>( -b05_03 );

            const time_type b06_01 = static_cast<time_type>( 0.050 );
            const time_type b06_04 = static_cast<time_type>( 0.250 );
            const time_type b06_05 = static_cast<time_type>( 0.20 );

            const time_type b07_01 = static_cast<time_type>( -25.0 / 108.0 );
            const time_type b07_04 = static_cast<time_type>( 125.0 / 108.0 );
            const time_type b07_05 = static_cast<time_type>( -65.0 / 27.0 );
            const time_type b07_06 = static_cast<time_type>( 125.0 / 54.0 );

            const time_type b08_01 = static_cast<time_type>( 31.0 / 300.0 );
            const time_type b08_05 = static_cast<time_type>( 61.0 / 225.0 );
            const time_type b08_06 = static_cast<time_type>( -2.0 / 9.0 );
            const time_type b08_07 = static_cast<time_type>( 13.0 / 900.0 );

            const time_type b09_01 = static_cast<time_type>( 2.0 );
            const time_type b09_04 = static_cast<time_type>( -53.0 / 6.0 );
            const time_type b09_05 = static_cast<time_type>( 704.0 / 45.0 );
            const time_type b09_06 = static_cast<time_type>( -107.0 / 9.0 );
            const time_type b09_07 = static_cast<time_type>( 67.0 / 90.0 );
            const time_type b09_08 = static_cast<time_type>( 3.0 );

            const time_type b10_01 = static_cast<time_type>( -91.0 / 108.0 );
            const time_type b10_04 = static_cast<time_type>( 23.0 / 108.0 );
            const time_type b10_05 = static_cast<time_type>( -976.0 / 135.0 );
            const time_type b10_06 = static_cast<time_type>( 311.0 / 54.0 );
            const time_type b10_07 = static_cast<time_type>( -19.0 / 60.0 );
            const time_type b10_08 = static_cast<time_type>( 17.0 / 6.0 );
            const time_type b10_09 = static_cast<time_type>( -1.0 / 12.0 );

            const time_type b11_01 = static_cast<time_type>( 2383.0 / 4100.0 );
            const time_type b11_04 = static_cast<time_type>( -341.0 / 164.0 );
            const time_type b11_05 = static_cast<time_type>( 4496.0 / 1025.0 );
            const time_type b11_06 = static_cast<time_type>( -301.0 / 82.0 );
            const time_type b11_07 = static_cast<time_type>( 2133.0 / 4100.0 );
            const time_type b11_08 = static_cast<time_type>( 45.0 / 82.0 );
            const time_type b11_09 = static_cast<time_type>( 45.0 / 164.0 );
            const time_type b11_10 = static_cast<time_type>( 18.0 / 41.0 );

            const time_type b12_01 = static_cast<time_type>( 3.0 / 205.0 );
            const time_type b12_06 = static_cast<time_type>( -6.0 / 41.0 );
            const time_type b12_07 = static_cast<time_type>( -3.0 / 205.0 );
            const time_type b12_08 = static_cast<time_type>( -3.0 / 41.0 );
            const time_type b12_09 = static_cast<time_type>( 3.0 / 41.0 );
            const time_type b12_10 = static_cast<time_type>( 6.0 / 41.0 );

            const time_type b13_01 = static_cast<time_type>( -1777.0 / 4100.0 );
            const time_type b13_04 = static_cast<time_type>( b11_04 );
            const time_type b13_05 = static_cast<time_type>( b11_05 );
            const time_type b13_06 = static_cast<time_type>( -289.0 / 82.0 );
            const time_type b13_07 = static_cast<time_type>( 2193.0 / 4100.0 );
            const time_type b13_08 = static_cast<time_type>( 51.0 / 82.0 );
            const time_type b13_09 = static_cast<time_type>( 33.0 / 164.0 );
            const time_type b13_10 = static_cast<time_type>( 12.0 / 41.0 );
            const time_type b13_12 = static_cast<time_type>( 1.0 );

            const time_type val1 = static_cast<time_type>( 1.0 );

            using namespace detail::it_algebra;

            // compute the times at which system is evaluated
            m_t02 = t + a02 * dt;
            m_t03 = t + a03 * dt;
            m_t04 = t + a04 * dt;
            m_t05 = t + a05 * dt;
            m_t06 = t + a06 * dt;
            m_t07 = t + a07 * dt;
            m_t08 = t + a08 * dt;
            m_t09 = t + a09 * dt;
            m_t10 = t + a10 * dt;
            m_t11 = t + dt;
            m_t12 = t;
            m_t13 = t + dt;

            // resize
            m_resizer.adjust_size( x , m_xt );
            m_resizer.adjust_size( x , m_k02 );
            m_resizer.adjust_size( x , m_k03 );
            m_resizer.adjust_size( x , m_k04 );
            m_resizer.adjust_size( x , m_k05 );
            m_resizer.adjust_size( x , m_k06 );
            m_resizer.adjust_size( x , m_k07 );
            m_resizer.adjust_size( x , m_k08 );
            m_resizer.adjust_size( x , m_k09 );
            m_resizer.adjust_size( x , m_k10 );
            m_resizer.adjust_size( x , m_k11 );
            m_resizer.adjust_size( x , m_k12 );
            m_resizer.adjust_size( x , m_k13 );


            // k1, the first system call has allready been evaluated

            // k2 step
            scale_sum( m_xt.begin() , m_xt.end() , 
                       val1 , x.begin() , 
                       dt * b02_01 , dxdt.begin() );
            system( m_xt , m_k02 , m_t02 );

            // k3 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b03_01 , dxdt.begin() ,
                       dt * b03_02 , m_k02.begin() );
            system( m_xt , m_k03 , m_t03 );


            // k4 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b04_01 , dxdt.begin() ,
                       dt * b04_03 , m_k03.begin() );
            system( m_xt , m_k04 , m_t04 );


            // k5 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b05_01 , dxdt.begin() ,
                       dt * b05_03 , m_k03.begin() ,
                       dt * b05_04 , m_k04.begin() );
            system( m_xt , m_k05 , m_t05 );


            // k6 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b06_01 , dxdt.begin() ,
                       dt * b06_04 , m_k04.begin() ,
                       dt * b06_05 , m_k05.begin() );
            system( m_xt , m_k06 , m_t06 );


            // k7 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b07_01 , dxdt.begin() ,
                       dt * b07_04 , m_k04.begin() ,
                       dt * b07_05 , m_k05.begin() ,
                       dt * b07_06 , m_k06.begin() );
            system( m_xt , m_k07 , m_t07 );


            // k8 step 
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b08_01 , dxdt.begin() ,
                       dt * b08_05 , m_k05.begin() ,
                       dt * b08_06 , m_k06.begin() ,
                       dt * b08_07 , m_k07.begin() );
            system( m_xt , m_k08 , m_t08 );


            // k9 step 
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b09_01 , dxdt.begin() ,
                       dt * b09_04 , m_k04.begin() ,
                       dt * b09_05 , m_k05.begin() ,
                       dt * b09_06 , m_k06.begin() ,
                       dt * b09_07 , m_k07.begin() ,
                       dt * b09_08 , m_k08.begin() );
            system( m_xt , m_k09 , m_t09 );

            
            // k10 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b10_01 , dxdt.begin() ,
                       dt * b10_04 , m_k04.begin() ,
                       dt * b10_05 , m_k05.begin() ,
                       dt * b10_06 , m_k06.begin() ,
                       dt * b10_07 , m_k07.begin() ,
                       dt * b10_08 , m_k08.begin() ,
                       dt * b10_09 , m_k09.begin() );
            system( m_xt , m_k10 , m_t10 );


            // k11 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b11_01 , dxdt.begin() ,
                       dt * b11_04 , m_k04.begin()  ,
                       dt * b11_05 , m_k05.begin() ,
                       dt * b11_06 , m_k06.begin() ,
                       dt * b11_07 , m_k07.begin() ,
                       dt * b11_08 , m_k08.begin() ,
                       dt * b11_09 , m_k09.begin() ,
                       dt * b11_10 , m_k10.begin() );
            system( m_xt , m_k11 , m_t11 );


            // k12 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b12_01 , dxdt.begin() ,
                       dt * b12_06 , m_k06.begin() ,
                       dt * b12_07 , m_k07.begin() ,
                       dt * b12_08 , m_k08.begin() ,
                       dt * b12_09 , m_k09.begin() ,
                       dt * b12_10 , m_k10.begin() );
            system( m_xt , m_k12 , m_t12 );


            // k13 step
            scale_sum( m_xt.begin() , m_xt.end() ,
                       val1 , x.begin() ,
                       dt * b13_01 , dxdt.begin() ,
                       dt * b13_04 , m_k04.begin() ,
                       dt * b13_05 , m_k05.begin() ,
                       dt * b13_06 , m_k06.begin() ,
                       dt * b13_07 , m_k07.begin() ,
                       dt * b13_08 , m_k08.begin() ,
                       dt * b13_09 , m_k09.begin() ,
                       dt * b13_10 , m_k10.begin() ,
                       dt * b13_12 , m_k12.begin() );
            system( m_xt , m_k13 , m_t13 );

            scale_sum( x.begin() , x.end() ,
                       val1 , x.begin() ,
                       dt * c06 , m_k06.begin() ,
                       dt * c07 , m_k07.begin() ,
                       dt * c08 , m_k08.begin() ,
                       dt * c09 , m_k09.begin() ,
                       dt * c10 , m_k10.begin() ,
                       dt * c12 , m_k12.begin() ,
                       dt * c13 , m_k13.begin() );
        }


        template< class DynamicalSystem >
        void do_step( DynamicalSystem &system ,
                      container_type &x ,
                      time_type t ,
                      time_type dt )
        {
            m_resizer.adjust_size( x , m_dxdt );
            system( x , m_dxdt , t );
            do_step( system , x , m_dxdt , t , dt );
        }


/*

        template< class DynamicalSystem >
        void do_step( DynamicalSystem &system ,
                      container_type &x ,
                      container_type &dxdt ,
                      time_type t ,
                      time_type dt ,
                      container_type &xerr )
        {
            const time_type cc01 = static_cast<time_type>( 41.0 / 840.0 );
            const time_type cc06 = static_cast<time_type>( 34.0 / 105.0 );
            const time_type cc07 = static_cast<time_type>( 9.0 / 35.0 );
            const time_type cc08 = static_cast<time_type>( cc08 );
            const time_type cc09 = static_cast<time_type>( 9.0 / 280.0 );
            const time_type cc10 = static_cast<time_type>( cc09 );
            const time_type cc11 = static_cast<time_type>( cc01 );

            xerr = x;
            do_step( system , xerr , dxdt , t , dt );

            // now, k1-k13 are calculated and stored in m_k01 - m_k13
            scale_sum( x.begin() , x.end() ,
                       static_cast<time_type>(1.0) , x.begin(),
                       dt * cc01 , dxdt ,
                       dt * cc06 , m_k06 ,
                       dt * cc07 , m_k07 ,
                       dt * cc08 , m_k08 ,
                       dt * cc09 , m_k09 ,
                       dt * cc10 , m_k10 ,
                       dt * cc11 , m_k11 );

            increment( xerr.begin() , xerr.end() , x.begin() , static_cast<time_type>(-1.0) );
        }

        template< class DynamicalSystem >
        void do_step( DynamicalSystem &system ,
                      container_type &x ,
                      time_type t ,
                      time_type dt ,
                      container_type &xerr )
        {
            m_resizer.adjust_size( x , m_dxdt );
            system( x , m_dxdt , t );
            do_step( system , x , m_dxdt , t , dt , xerr );
        }
*/
    };

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif //BOOST_NUMERIC_ODEINT_STEPPER_RK78_FEHLBERG_HPP_INCLUDED
