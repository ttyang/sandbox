/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename A0>
    struct dynamic<A0> : noncopyable
    {
        typedef
            fusion::vector1<A0>
            tuple_type;
        typedef
            dynamic<A0>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1>
    struct dynamic<A0 , A1> : noncopyable
    {
        typedef
            fusion::vector2<A0 , A1>
            tuple_type;
        typedef
            dynamic<A0 , A1>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2>
    struct dynamic<A0 , A1 , A2> : noncopyable
    {
        typedef
            fusion::vector3<A0 , A1 , A2>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3>
    struct dynamic<A0 , A1 , A2 , A3> : noncopyable
    {
        typedef
            fusion::vector4<A0 , A1 , A2 , A3>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct dynamic<A0 , A1 , A2 , A3 , A4> : noncopyable
    {
        typedef
            fusion::vector5<A0 , A1 , A2 , A3 , A4>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5> : noncopyable
    {
        typedef
            fusion::vector6<A0 , A1 , A2 , A3 , A4 , A5>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6> : noncopyable
    {
        typedef
            fusion::vector7<A0 , A1 , A2 , A3 , A4 , A5 , A6>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7> : noncopyable
    {
        typedef
            fusion::vector8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8> : noncopyable
    {
        typedef
            fusion::vector9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> : noncopyable
    {
        typedef
            fusion::vector10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10> : noncopyable
    {
        typedef
            fusion::vector11<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11> : noncopyable
    {
        typedef
            fusion::vector12<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12> : noncopyable
    {
        typedef
            fusion::vector13<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13> : noncopyable
    {
        typedef
            fusion::vector14<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14> : noncopyable
    {
        typedef
            fusion::vector15<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15> : noncopyable
    {
        typedef
            fusion::vector16<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16> : noncopyable
    {
        typedef
            fusion::vector17<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17> : noncopyable
    {
        typedef
            fusion::vector18<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18> : noncopyable
    {
        typedef
            fusion::vector19<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19> : noncopyable
    {
        typedef
            fusion::vector20<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20> : noncopyable
    {
        typedef
            fusion::vector21<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21> : noncopyable
    {
        typedef
            fusion::vector22<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22> : noncopyable
    {
        typedef
            fusion::vector23<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23> : noncopyable
    {
        typedef
            fusion::vector24<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24> : noncopyable
    {
        typedef
            fusion::vector25<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25> : noncopyable
    {
        typedef
            fusion::vector26<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26> : noncopyable
    {
        typedef
            fusion::vector27<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27> : noncopyable
    {
        typedef
            fusion::vector28<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28> : noncopyable
    {
        typedef
            fusion::vector29<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29> : noncopyable
    {
        typedef
            fusion::vector30<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30> : noncopyable
    {
        typedef
            fusion::vector31<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31> : noncopyable
    {
        typedef
            fusion::vector32<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32> : noncopyable
    {
        typedef
            fusion::vector33<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33> : noncopyable
    {
        typedef
            fusion::vector34<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34> : noncopyable
    {
        typedef
            fusion::vector35<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35> : noncopyable
    {
        typedef
            fusion::vector36<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36> : noncopyable
    {
        typedef
            fusion::vector37<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37> : noncopyable
    {
        typedef
            fusion::vector38<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38> : noncopyable
    {
        typedef
            fusion::vector39<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39> : noncopyable
    {
        typedef
            fusion::vector40<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40> : noncopyable
    {
        typedef
            fusion::vector41<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41> : noncopyable
    {
        typedef
            fusion::vector42<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42> : noncopyable
    {
        typedef
            fusion::vector43<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43> : noncopyable
    {
        typedef
            fusion::vector44<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44> : noncopyable
    {
        typedef
            fusion::vector45<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45> : noncopyable
    {
        typedef
            fusion::vector46<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45; typedef typename expression::dynamic_member< mpl::int_<45> , self_type * >::type member46;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46> : noncopyable
    {
        typedef
            fusion::vector47<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45; typedef typename expression::dynamic_member< mpl::int_<45> , self_type * >::type member46; typedef typename expression::dynamic_member< mpl::int_<46> , self_type * >::type member47;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47> : noncopyable
    {
        typedef
            fusion::vector48<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45; typedef typename expression::dynamic_member< mpl::int_<45> , self_type * >::type member46; typedef typename expression::dynamic_member< mpl::int_<46> , self_type * >::type member47; typedef typename expression::dynamic_member< mpl::int_<47> , self_type * >::type member48;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48> : noncopyable
    {
        typedef
            fusion::vector49<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45; typedef typename expression::dynamic_member< mpl::int_<45> , self_type * >::type member46; typedef typename expression::dynamic_member< mpl::int_<46> , self_type * >::type member47; typedef typename expression::dynamic_member< mpl::int_<47> , self_type * >::type member48; typedef typename expression::dynamic_member< mpl::int_<48> , self_type * >::type member49;
        mutable dynamic_frame_type* frame;
    };
    
    
    
    
    
    
    
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48 , typename A49>
    struct dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49> : noncopyable
    {
        typedef
            fusion::vector50<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49>
            tuple_type;
        typedef
            dynamic<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49>
            self_type;
        typedef
            dynamic_frame<self_type>
            dynamic_frame_type;
        dynamic()
            : frame(0) {}
        template <int N>
        static
        typename expression::dynamic_member<mpl::int_<N>, self_type *>::type
        init(self_type * scope)
        {
            return
                expression::
                    dynamic_member<mpl::int_<N>, self_type *>::
                        make(mpl::int_<N>(), scope);
        }
        typedef typename expression::dynamic_member< mpl::int_<0> , self_type * >::type member1; typedef typename expression::dynamic_member< mpl::int_<1> , self_type * >::type member2; typedef typename expression::dynamic_member< mpl::int_<2> , self_type * >::type member3; typedef typename expression::dynamic_member< mpl::int_<3> , self_type * >::type member4; typedef typename expression::dynamic_member< mpl::int_<4> , self_type * >::type member5; typedef typename expression::dynamic_member< mpl::int_<5> , self_type * >::type member6; typedef typename expression::dynamic_member< mpl::int_<6> , self_type * >::type member7; typedef typename expression::dynamic_member< mpl::int_<7> , self_type * >::type member8; typedef typename expression::dynamic_member< mpl::int_<8> , self_type * >::type member9; typedef typename expression::dynamic_member< mpl::int_<9> , self_type * >::type member10; typedef typename expression::dynamic_member< mpl::int_<10> , self_type * >::type member11; typedef typename expression::dynamic_member< mpl::int_<11> , self_type * >::type member12; typedef typename expression::dynamic_member< mpl::int_<12> , self_type * >::type member13; typedef typename expression::dynamic_member< mpl::int_<13> , self_type * >::type member14; typedef typename expression::dynamic_member< mpl::int_<14> , self_type * >::type member15; typedef typename expression::dynamic_member< mpl::int_<15> , self_type * >::type member16; typedef typename expression::dynamic_member< mpl::int_<16> , self_type * >::type member17; typedef typename expression::dynamic_member< mpl::int_<17> , self_type * >::type member18; typedef typename expression::dynamic_member< mpl::int_<18> , self_type * >::type member19; typedef typename expression::dynamic_member< mpl::int_<19> , self_type * >::type member20; typedef typename expression::dynamic_member< mpl::int_<20> , self_type * >::type member21; typedef typename expression::dynamic_member< mpl::int_<21> , self_type * >::type member22; typedef typename expression::dynamic_member< mpl::int_<22> , self_type * >::type member23; typedef typename expression::dynamic_member< mpl::int_<23> , self_type * >::type member24; typedef typename expression::dynamic_member< mpl::int_<24> , self_type * >::type member25; typedef typename expression::dynamic_member< mpl::int_<25> , self_type * >::type member26; typedef typename expression::dynamic_member< mpl::int_<26> , self_type * >::type member27; typedef typename expression::dynamic_member< mpl::int_<27> , self_type * >::type member28; typedef typename expression::dynamic_member< mpl::int_<28> , self_type * >::type member29; typedef typename expression::dynamic_member< mpl::int_<29> , self_type * >::type member30; typedef typename expression::dynamic_member< mpl::int_<30> , self_type * >::type member31; typedef typename expression::dynamic_member< mpl::int_<31> , self_type * >::type member32; typedef typename expression::dynamic_member< mpl::int_<32> , self_type * >::type member33; typedef typename expression::dynamic_member< mpl::int_<33> , self_type * >::type member34; typedef typename expression::dynamic_member< mpl::int_<34> , self_type * >::type member35; typedef typename expression::dynamic_member< mpl::int_<35> , self_type * >::type member36; typedef typename expression::dynamic_member< mpl::int_<36> , self_type * >::type member37; typedef typename expression::dynamic_member< mpl::int_<37> , self_type * >::type member38; typedef typename expression::dynamic_member< mpl::int_<38> , self_type * >::type member39; typedef typename expression::dynamic_member< mpl::int_<39> , self_type * >::type member40; typedef typename expression::dynamic_member< mpl::int_<40> , self_type * >::type member41; typedef typename expression::dynamic_member< mpl::int_<41> , self_type * >::type member42; typedef typename expression::dynamic_member< mpl::int_<42> , self_type * >::type member43; typedef typename expression::dynamic_member< mpl::int_<43> , self_type * >::type member44; typedef typename expression::dynamic_member< mpl::int_<44> , self_type * >::type member45; typedef typename expression::dynamic_member< mpl::int_<45> , self_type * >::type member46; typedef typename expression::dynamic_member< mpl::int_<46> , self_type * >::type member47; typedef typename expression::dynamic_member< mpl::int_<47> , self_type * >::type member48; typedef typename expression::dynamic_member< mpl::int_<48> , self_type * >::type member49; typedef typename expression::dynamic_member< mpl::int_<49> , self_type * >::type member50;
        mutable dynamic_frame_type* frame;
    };
