#ifndef MAKE_INDEXES_HPP_INCLUDED
#define MAKE_INDEXES_HPP_INCLUDED
  template<int Max,int... Indices>
  struct make_indexes:
  	make_indexes<Max-1,Max-1,Indices...>
  /**@brief
   *  Starting from:
   *    max_indexes<5>
   *  this produces:
   *    max_indexes<5>
   *      : max_indexes<4,4>
   *        : max_indexes<3,3,4>
   *          : max_indexes<2,2,3,4>
   *            : max_indexes<1,1,2,3,4>
   *              : max_indexes<0,0,1,2,3,4>
   *                //using the specialization below
   *              {
   *                  typedef int_indexes<0,1,2,3,4> type;
   *              };
   */        
  {};
  template<int...>
  struct int_indexes
  {};
  template<int... Indices>
  struct make_indexes<0,Indices...>
  {
  	typedef int_indexes<Indices...> type;
  };
#endif
