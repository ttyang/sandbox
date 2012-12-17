//Purpose:
//  Demo array whose dimensions and sizes are defined at runtime.
//
#include "array_dyn.hpp"

  template
  < typename T
  >
  std::ostream&
operator<<
  ( std::ostream&sout
  , std::vector<T>const&vec
  )
  {
      sout<<"{ ";
      for(unsigned i=0; i<vec.size(); ++i)
      {
          if(0<i) sout<<", ";
          sout<<vec[i];
      }
      sout<<"}";
      return sout;
  }
  
  template
  < typename Arr
  >
  typename Arr::data_t::value_type
assign_iota
  ( Arr&arr
  , typename Arr::data_t::value_type start=0
  )
  {
      unsigned n=arr.my_data.size();
      typedef typename Arr::data_t::value_type value_t;
      for( unsigned i=0; i<n; ++i)
      {
          arr.my_data[i]=start+value_t(i);
      }
      return start+value_t(n);
   }

int main(void)
{
    {
    #if 0
        std::cout<<"*********general demo****************\n";
        for(unsigned dir_op=dir_fwd; dir_op<unsigned(dir_rev+1); ++dir_op)
        {
            std::cout<<"*************************\n";
            std::cout<<"dir_op="<<dir_op<<"\n";
            array_dyn<int> ai(dirs(dir_op),{2,3,4});
            unsigned const size=ai.my_data.size();
            std::cout<<"my_data.size()="<<size<<"\n";
            unsigned const value0=1000;
            for( unsigned i=0; i<size; ++i)
            {
                ai.my_data[i]=value0+i;
            }
            unsigned const rank=ai.rank();
            std::cout<<"rank="<<rank<<"\n";
            std::cout<<"size()="<<ai.size()<<"\n";
            for(unsigned i=0;i<rank;++i)
            {
                std::cout<<"stride("<<i<<")="<<ai.stride(i)<<"\n";
                std::cout<<"  size("<<i<<")="<<ai.size(i)<<"\n";
            }
            std::cout<<"ai.offset_at_indices(1,0,0)="<<ai.offset_at_indices({1,0,0})<<"\n";
            std::cout<<"ai(1,0,0)="<<ai({1,0,0})<<"\n";
            std::cout<<"ai.offset_at_indices(0,1,0)="<<ai.offset_at_indices({0,1,0})<<"\n";
            std::cout<<"ai(0,1,0)="<<ai({0,1,0})<<"\n";
            std::cout<<"ai.offset_at_indices(0,0,1)="<<ai.offset_at_indices({0,0,1})<<"\n";
            std::cout<<"ai(0,0,1)="<<ai({0,0,1})<<"\n";
            std::cout<<"ai.ok_indices(1,2,3)="<<ai.ok_indices({1,2,3})<<"\n";
            typedef std::vector<unsigned> indices_t;
            std::cout<<"ai.ok_indices(indices_t({0,0,0}))="<<ai.ok_indices(indices_t({0,0,0}))<<"\n";
            std::cout<<"ai.ok_indices(1,2,4)="<<ai.ok_indices({1,2,4})<<"\n";
            std::cout<<"ai.ok_indices(1,2,3,0)="<<ai.ok_indices({1,2,3,0})<<"\n";
            unsigned offset=ai.offset_at_indices({1,2,3});
            std::cout<<"ai.offset_at_indices(1,2,3)="<<offset<<"\n";
            std::vector<unsigned> indices(ai.indices_at_offset(offset));
            std::cout<<"indices_at_offset("<<offset<<")=\n";
            for(unsigned i=0; i< indices.size(); ++i)
            {
                std::cout<<indices[i]<<" ";
            }
            std::cout<<"\n";
          #if 1
            std::cout<<"ai=\n";
            std::cout<<ai<<".\n";
          #endif
        }
    #endif
    }
    {
        unsigned dir_op=dir_fwd;
        std::cout<<"********reshape demo***********\n";
        std::cout<<"dir_op="<<dir_op<<"\n";
        std::vector<unsigned> shape({3,0});
        std::cout<<"shape="<<shape<<"\n";
        array_dyn<int> ai(dirs(dir_op),shape);
        unsigned const size=ai.my_data.size();
        std::cout<<"my_data.size()="<<size<<"\n";
        assign_iota(ai);
        std::cout<<"ai=\n";
        std::cout<<ai<<".\n";
        shape[1]=1;
        std::cout<<"shape="<<shape<<"\n";
        ai.reshape(shape);
        assign_iota(ai);
        std::cout<<"ai=\n";
        std::cout<<ai<<".\n";
        shape[1]=5;
        std::cout<<"shape="<<shape<<"\n";
        ai.reshape(shape);
        assign_iota(ai);
        std::cout<<"ai=\n";
        std::cout<<ai<<".\n";
        shape[0]=0;
        std::cout<<"shape="<<shape<<"\n";
        ai.reshape(shape);
        assign_iota(ai);
        std::cout<<"ai=\n";
        std::cout<<ai<<".\n";
    }
    return 0;
}    
