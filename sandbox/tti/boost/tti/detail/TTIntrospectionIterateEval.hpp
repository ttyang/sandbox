    template
      <
      template
        <
        BOOST_PP_REPEAT(BOOST_PP_ITERATION(),TTI_DETAIL_PP_REPEAT_CLASS,class)
        > 
      class F,
      BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ADD(1,BOOST_PP_ITERATION()),class P)
      >
    struct eval<F<BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_ADD(1,BOOST_PP_ITERATION()),P)> > : 
      F
      <
      BOOST_PP_ENUM_SHIFTED(BOOST_PP_ADD(1,BOOST_PP_ITERATION()),TTI_DETAIL_PP_ENUM_SHIFTED_TYPENAME,pdata)
      > 
    {};
