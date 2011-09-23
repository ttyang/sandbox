#include <boost/utility/trace_scope.hpp>
#include <boost/array_stepper/stepper_offset_print.hpp>
#include <boost/array_stepper/mk_iota.hpp>
#include <boost/array_stepper/vector_print.hpp>
#include <algorithm>

using namespace boost::array_stepper;

int main()
{
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
    typedef stepper_offset<> sto_t;  
    typedef sto_t::lengths_t lengths_t;
    lengths_t lengths_v({-2,3,4});
    unsigned rank=lengths_v.size();
    sto_t::axes_permutation_t permut_v=mk_iota<sto_t::axis_t>( 0, rank);
    std::cout<<"lengths_v="<<lengths_v<<"\n";
    {
        ::boost::trace_scope ts("***permut CTOR");
        unsigned count=0;
        do
        {
            std::cout<<":count="<<count<<"\n";
            std::cout<<":permut_v="<<permut_v<<"\n";
            sto_t const sto_v( lengths_v, permut_v);
            std::cout<<"stepper_ones=\n"<<sto_v.stepper_ones();
            std::cout<<"offset="<<sto_v.offset()<<"\n";
        }while 
          (  ++count< 10
          && std::next_permutation
             ( permut_v.begin()
             , permut_v.end()
             )
          );
        std::cout<<":permut_v="<<permut_v<<"\n";
    }
    //=========================
    {
        ::boost::trace_scope ts("***permut VALU");
        sto_t::axes_permutation_t const permut_c=permut_v;
        unsigned count=0;
        do
        {
            std::cout<<":count="<<count<<"\n";
            std::cout<<":permut_c="<<permut_c<<"\n";
            sto_t sto_v( lengths_v, permut_c);
            sto_v.permute_axes(permut_v);
            std::cout<<"stepper_ones=\n"<<static_cast<sto_t const&>(sto_v).stepper_ones();
            std::cout<<"offset="<<sto_v.offset()<<"\n";
        }while 
          (  ++count< 10
          && std::next_permutation
             ( permut_v.begin()
             , permut_v.end()
             )
          );
    }
    //=========================
    {
        ::boost::trace_scope ts("***rotate VALU");
        unsigned count=0;
        unsigned axis=1;
        unsigned limit=rank-axis;
        sto_t sto_v( lengths_v, permut_v);
        std::cout<<":permut_v="<<permut_v<<"\n";
        std::cout<<":count="<<count<<"\n";
        std::cout<<":axis="<<axis<<"\n";
        std::cout<<"stepper_ones=\n"<<static_cast<sto_t const&>(sto_v).stepper_ones();
        std::cout<<"offset="<<sto_v.offset()<<"\n";
        do
        {
            sto_v.rotate_axes(axis);
            std::cout<<":count="<<++count<<"\n";
            std::cout<<"stepper_ones=\n"<<static_cast<sto_t const&>(sto_v).stepper_ones();
            std::cout<<"offset="<<sto_v.offset()<<"\n";
        }while 
          (  count< limit
          );
    }
    //=========================
    return 0;
}    
