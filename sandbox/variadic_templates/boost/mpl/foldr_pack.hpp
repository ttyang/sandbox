#ifndef BOOST_MPL_FOLDR_PACK_HPP_VARIADIC_TEMPLATES
#define BOOST_MPL_FOLDR_PACK_HPP_VARIADIC_TEMPLATES

namespace boost { namespace mpl {

  template
  < typename State0 //initial State
  , template<typename Value,typename State>class OpValueState_State //Operator: (Value,State) -> State
  , typename... Values
  >
  struct
foldr_pack
/**@brief
 *  Apply OpValueState_State to each element in Values...
 *  starting with intial State, State0.  Associate the applications
 *  to the right.
 *
 *  For example, the analogous operation on run-time-value's is:
 *
 *    Assuming:
 *       z == the run-time-value analogue of State0.
 *       xI == the analogue of I-th element in Values...
 *       F == the analogue of OpValueState_State.
 *    Then the analogue of result would be:
 *      F(x1,F(x2,F(x3,z)))
 *
 *  This template is similar to the haskell foldr described on p. 117 of:
 *
 *    http://haskell.org/definition/haskell98-report.pdf
 *
 *  where:
 *     haskell these_comments
 *     ------- --------------
 *     f       F
 *     a       typename
 *     b       State
 *     z       initial State
 */
;
  template
  < typename State0 //initial State
  , template<typename Value,typename State>class OpValueState_State
  , typename Head
  , typename... Tail
  >
  struct
foldr_pack
  < State0
  , OpValueState_State
  , Head
  , Tail...
  >
: OpValueState_State
  < Head
  , typename foldr_pack
    < State0
    , OpValueState_State
    , Tail...
    >::type
  >
{
};
  template
  < typename State0
  , template<typename Value,typename State>class OpValueState_State
  >
  struct
foldr_pack
  < State0
  , OpValueState_State
  >
{
        typedef 
      State0 
    type
    ;
};

}}//exit boost::mpl namespace

#endif //include guard
