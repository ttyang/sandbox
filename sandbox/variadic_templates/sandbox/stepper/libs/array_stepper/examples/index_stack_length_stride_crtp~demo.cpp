#include <boost/array_stepper/index_stack_length_stride_crtp.hpp>

#include <boost/utility/trace_scope.hpp>
#include <iomanip>
#include <boost/array_stepper/length_strides_offset_print.hpp>
#include <boost/array_stepper/vector_print.hpp>

using namespace boost::array_stepper;

typedef index_stack_length_stride_crtp_types<>::indices_bounds_strides ibs_t;

typedef index_stack_length_stride_crtp_indices<> lsos_t;

char const*id_names[dec_ator+1]={"inc_ator","dec_ator"};
template<inc_dec_enum ID>
void test_inc_dec(lsos_t& lsos_v)
{
    ::boost::trace_scope ts("test_inc_dec:");
    std::cout<<"ID="<<id_names[ID]<<"\n";
    unsigned space=lsos_v.space();
    {
        for(unsigned node=0; node<space; ++node, lsos_v.template inc_dec_ator<ID>())
        {
            std::cout<<"node["<<std::setw(2)<<node<<"]=";
            std::cout<<lsos_v;
            auto offset=lsos_v.offset_space_val();
            std::cout<<", indices_at_offset="<<lsos_v.indices_at_offset(offset);
            std::cout<<"\n";
        }
    }
}

int main()
{
    boost::iostreams::indent_scoped_ostreambuf<char> indent_outbuf(std::cout,2);
    typedef index_stack_length_stride_crtp_types<> types_t;
    typedef length_strides_offset<> lso_t;
    typedef std::vector<lso_t::length_dir_t> lengths_t;
    typedef types_t::index_t index_t;
    typedef long unsigned offset_t;
    lengths_t lengths_v={2,3,4};
    std::cout<<"lengths_v="<<lengths_v<<"\n";
    lso_t lso_v( lengths_v);
    std::cout<<"length_strides_offset=\n"<<lso_v<<"\n";
    lso_t::length_strides_t lss_v=lso_v.length_strides();
    lsos_t lsos_v( lss_v.begin(), lss_v.end());
    test_inc_dec<inc_ator>(lsos_v);
    test_inc_dec<dec_ator>(lsos_v);
    std::cout<<"rotatate:\n";
    unsigned rotate=2;
    unsigned rotation=lsos_v.rotate(rotate);
    std::cout<<":rotate("<<rotate<<")="<<rotation<<":rotation="<<lsos_v.rotation()<<"\n";
    test_inc_dec<inc_ator>(lsos_v);
  #if 1
    typedef types_t::axis_t axis_t;
    axis_t axis_v=2;
    index_t offset_v=1;
    lsos_v.axis_offsets_put(axis_v,offset_v,offset_v);
    std::cout<<"axis_offsets_put("<<axis_v<<","<<offset_v<<","<<offset_v<<"):\n";
    lsos_v.axis_index_put(axis_v,lsos_v[axis_v].get<index_bound_lower>());
    std::cout<<"axis_index_put("<<axis_v<<",index_bound_lower["<<axis_v<<"]):\n";
    test_inc_dec<inc_ator>(lsos_v);
    offset_v=0;
    lsos_v.axis_offsets_put(axis_v,offset_v,offset_v);
    std::cout<<"axis_offsets_put("<<axis_v<<","<<offset_v<<","<<offset_v<<"):\n";
    lsos_v.axis_index_put(axis_v,lsos_v[axis_v].get<index_bound_lower>());
    std::cout<<"axis_index_put("<<axis_v<<",index_bound_lower["<<axis_v<<"]):\n";
    test_inc_dec<inc_ator>(lsos_v);
    auto offset_l=lsos_v[axis_v].length_val()-1;
    lsos_v.axis_offsets_put(axis_v,offset_l,offset_v);
    std::cout<<"axis_offsets_put("<<axis_v<<","<<offset_l<<","<<offset_v<<"):\n";
    lsos_v.axis_index_put(axis_v,lsos_v[axis_v].get<index_bound_lower>());
    std::cout<<"axis_index_put("<<axis_v<<",index_bound_lower["<<axis_v<<"]):\n";
    test_inc_dec<inc_ator>(lsos_v);
  #endif
    return 0;
}    

