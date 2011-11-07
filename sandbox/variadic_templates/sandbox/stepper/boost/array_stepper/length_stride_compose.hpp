#ifndef BOOST_ARRAY_STEPPER_LENGTH_STRIDE_COMPOSE_HPP_INCLUDED
#define BOOST_ARRAY_STEPPER_LENGTH_STRIDE_COMPOSE_HPP_INCLUDED
#include <cstdlib>
namespace boost
{
namespace array_stepper
{
  enum
sign_val
{ less0=-1
, is0
, more0
};

  template
  < typename LengthStride
  , typename Offset=std::size_t
  >
  struct
length_stride_compose
  /**@brief
   *  Used as 1st arg to scan_first_iter to
   *  create LengthStride's from 
   *  sequence of LengthStride::length_t's.
   */
{
        typedef
      LengthStride
    length_stride_t
    ;
        typedef
      typename length_stride_t::length_t
    length_t
    ;
        typedef
      typename length_stride_t::stride_t
    stride_t
    ;
        typedef
      stride_t
    length_dir_t
     /**@brief
      *  axis length which is signed in order
      *  to indicate forward (>0) or reverse(<0)
      *  order of indices.
      */
    ;
        typedef
      Offset
    offset_t
    ;
 private:    
      offset_t&
    my_offset
      /**@brief
       *  Modified by negative length_t arguments.
       *  A negative length_t indicates that the
       *  elements are stored in reverse order.
       *  In other words, the element stored
       *  at index, i, is stored after the 
       *  element stored at index, (i+1).
       *  Here, index means the index argument
       *  to the subscript operator.
       *
       **@reference:
       *  _An APL Compiler_
       *  Timothy Budd
       *  Springer-Verlag, 1988
       */
    ;
 public:    
    length_stride_compose( offset_t&a_offset)
    : my_offset(a_offset)
    {
    }
      offset_t
    offset()const
    {
        return my_offset;
    }        
    
        static
      sign_val
    isign( length_dir_t a_length)
      /**@brief
       *  Returns one of {less0,is0,more0}
       *  depending on sign of a_length.
       */
    {
        sign_val r=(a_length<0)?less0:((a_length==0)?is0:more0);
        return r;
    }    

      length_stride_t
    operator()
      ( length_dir_t a_length //The first length in the length sequence.
      )
    {
        sign_val sv=isign(a_length);
        length_t ex=std::abs(a_length);
        /**
         *  The comment preceding the similar statment
         *  in binary operator() applies here also.
         */
        length_t sp=1;
        if(sv==less0) my_offset =(ex-1)*sp;
        stride_t st=sv*sp;
        length_stride_t  result( ex, st);
        return result;
    }
    
      length_stride_t
    operator()
      ( length_stride_t a_length_stride //previous length stride
      , length_dir_t a_length //current length (not first)
      )
      /**@brief
       *  Returns current length_stride_t.
       */
    {
        sign_val sv=isign(a_length);
        length_t ex=std::abs(a_length);
        /**
         * The following 3 statements, when applied to all
         * the axes, do, essentially, what's done by the:
         * equations:
         *   t_i' = s_i - t_i - 1
         *   d_i' = -d_i
         * in section:
         *   6.1.4 Reversal
         * and the alpha equation:
         *   alpha = t_1*e_1 + ... t_n*e_n
         * in section:
         *   6.2 The Accessor
         * of @reference (see comments to my_offset declaration).
         *
         * In summary, alpha in the above section 6.2 equation
         * of @reference is my_offset here.
         */
        length_t sp=a_length_stride.space();
        if(sv==less0) my_offset+=(ex-1)*sp;
        stride_t st=sv*sp;
        length_stride_t  result( ex, st);
        return result;
    }
    
};

}//exit array_stepper namespace
}//exit boost namespace
#endif
