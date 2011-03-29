/*-----------------------------------------------------------------------------+    
Interval Container Library
Author: Joachim Faulhaber
Copyright (c) 2007-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#pragma once


#include <limits>
#include <boost/itl/detail/notate.hpp>
#include <boost/itl_xt/numbergentor.hpp>
#include <boost/itl_xt/bits_gentor.hpp>
#include <boost/itl_xt/setgentor.hpp>
#include <boost/itl_xt/mapgentor.hpp>
#include <boost/itl_xt/seqgentor.hpp>
#include <boost/itl_xt/itvgentor.hpp>
#include <boost/itl_xt/std/pair_gentor.hpp>
#include <boost/itl_xt/map_segment_gentor.hpp>

#ifdef LAW_BASED_TEST_BOOST_POLYGON
#include <libs/validate/example/labat_polygon_/point_gentor.hpp>
#include <libs/validate/example/labat_polygon_/polygon_gentor.hpp>
#endif //LAW_BASED_TEST_BOOST_POLYGON

#include <boost/itl/right_open_interval.hpp>
#include <boost/itl/interval_set.hpp>
#include <boost/itl/separate_interval_set.hpp>
#include <boost/itl/split_interval_set.hpp>
#include <boost/itl/interval_map.hpp>
#include <boost/itl/split_interval_map.hpp>
#include <boost/itl_xt/interval_bitset.hpp>
#ifdef USE_ICL_TREE
#include <boost/itl/tree/tree.hpp>
#endif
#include <boost/validate/gentor/gentorprofile.hpp>


namespace boost{namespace icl
{

    // -------------------------------------------------------------------------
    template <class ValueT> class RandomGentor;
    template <> class RandomGentor<int> : public NumberGentorT<int> {};
    template <> class RandomGentor<cnat> : public NumberGentorT<cnat> {};
    template <> class RandomGentor<double> : public NumberGentorT<double> {};

    // -------------------------------------------------------------------------
    template <class NaturalT> 
    class RandomGentor<icl::bits<NaturalT> > : 
        public bits_gentor<icl::bits<NaturalT> > {};

    // -------------------------------------------------------------------------
    template <class DomainT, ICL_COMPARE Compare>
    class RandomGentor<continuous_interval<DomainT,Compare> > :
        public ItvGentorT<DomainT, continuous_interval<DomainT,Compare> > {};

    template <class DomainT, ICL_COMPARE Compare>
    class RandomGentor<discrete_interval<DomainT,Compare> > :
        public ItvGentorT<DomainT, discrete_interval<DomainT,Compare> > {};

    // -------------------------------------------------------------------------
    template <class DomainT, class CodomainT>
    class RandomGentor< std::pair<DomainT,CodomainT> > :
        public std_pair_gentor<DomainT,CodomainT> {};


    template <class DomainT> 
    class RandomGentor<icl::list<DomainT> > :
        public SeqGentorT<icl::list<DomainT> > {};

#ifdef LAW_BASED_TEST_BOOST_POLYGON
    // -------------------------------------------------------------------------
    template <class DomainT> 
    class RandomGentor<icl::point<DomainT> > :
        public point_gentor<DomainT> {};

    template <class PointT> 
    class RandomGentor<icl::list<icl::list<PointT> > > :
        public polygon_set_gentor<icl::list<icl::list<PointT> > > {};
#endif //LAW_BASED_TEST_BOOST_POLYGON

    // ----- lists -------------------------------------------------------------
    template <class DomainT, class CodomainT, ICL_COMPARE Compare> 
    class RandomGentor<std::pair<discrete_interval<DomainT,Compare>, CodomainT> > :
        public map_segment_gentor<DomainT,CodomainT,discrete_interval<DomainT,Compare> > {};

    template <class DomainT, class CodomainT, ICL_COMPARE Compare> 
    class RandomGentor<std::pair<continuous_interval<DomainT,Compare>, CodomainT> > :
        public map_segment_gentor<DomainT,CodomainT,continuous_interval<DomainT,Compare> > {};

    template <class DomainT, class CodomainT, ICL_COMPARE Compare> 
    class RandomGentor<icl::list<std::pair<discrete_interval<DomainT,Compare>, CodomainT> > > :
        public SeqGentorT<icl::list<std::pair<discrete_interval<DomainT,Compare>, CodomainT> > > {};

    template <class DomainT, class CodomainT, ICL_COMPARE Compare> 
    class RandomGentor<icl::list<std::pair<continuous_interval<DomainT,Compare>, CodomainT> > > :
        public SeqGentorT<icl::list<std::pair<continuous_interval<DomainT,Compare>, CodomainT> > > {};

    template <class DomainT, class CodomainT> 
    class RandomGentor<icl::list<std::pair<DomainT,CodomainT> > > :
        public SeqGentorT<icl::list<std::pair<DomainT,CodomainT> > > {};

    template <class DomainT, ICL_COMPARE Compare>  
    class RandomGentor<icl::list<discrete_interval<DomainT,Compare> > > :
        public SeqGentorT<icl::list<discrete_interval<DomainT,Compare> > > {};

    template <class DomainT, ICL_COMPARE Compare>  
    class RandomGentor<icl::list<continuous_interval<DomainT,Compare> > > :
        public SeqGentorT<icl::list<continuous_interval<DomainT,Compare> > > {};

    // ----- sets --------------------------------------------------------------
    template <class DomainT> 
    class RandomGentor<icl::set<DomainT> > :
        public SetGentorT<icl::set<DomainT> > {};

    template <class DomainT> 
    class RandomGentor<std::set<DomainT> > :
        public SetGentorT<std::set<DomainT> > {};

    template <class DomainT> 
    class RandomGentor<icl::interval_set<DomainT> > :
        public SetGentorT<icl::interval_set<DomainT> > {};

    template <class DomainT> 
    class RandomGentor<icl::separate_interval_set<DomainT> > :
        public SetGentorT<icl::separate_interval_set<DomainT> > {};

    template <class DomainT> 
    class RandomGentor<icl::split_interval_set<DomainT> > :
        public SetGentorT<icl::split_interval_set<DomainT> > {};

    // ----- tree --------------------------------------------------------------
#ifdef USE_ICL_TREE
    template <class DomainT> 
    class RandomGentor<icl::tree<DomainT> > :
        public SetGentorT<icl::tree<DomainT> > {};
#endif

    // ----- maps --------------------------------------------------------------
    template <class DomainT, class Neutronizer> 
    class RandomGentor<icl::map<DomainT,icl::set<int>,Neutronizer> > : 
        public MapGentorT<icl::map<DomainT,icl::set<int>,Neutronizer> > {};

    template <class DomainT, class Neutronizer> 
    class RandomGentor<icl::map<DomainT,std::set<int>,Neutronizer> > : 
        public MapGentorT<icl::map<DomainT,std::set<int>,Neutronizer> > {};

    template <class DomainT, class BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section> 
    class RandomGentor<icl::map<DomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > : 
        public MapGentorT<icl::map<DomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > {};

    template <class DomainT, class CodomainT, class Neutronizer> 
    class RandomGentor<icl::map<DomainT,CodomainT,Neutronizer> > : 
        public MapGentorT<icl::map<DomainT,CodomainT,Neutronizer> > {};


    // ----- interval_map<D,C,N> -----------------------------------------------
    template <class DomainT, class Neutronizer> 
    class RandomGentor<interval_map<DomainT,icl::set<int>,Neutronizer> > : 
        public MapGentorT<interval_map<DomainT,icl::set<int>,Neutronizer> > {};

    template <class DomainT, class Neutronizer> 
    class RandomGentor<interval_map<DomainT,std::set<int>,Neutronizer> > : 
        public MapGentorT<interval_map<DomainT,std::set<int>,Neutronizer> > {};

    template <class DomainT, class CodomainT, class Neutronizer> 
    class RandomGentor<interval_map<DomainT,CodomainT,Neutronizer> > : 
        public MapGentorT<interval_map<DomainT,CodomainT,Neutronizer> > {};

    // ----- split_interval_map<D,C,N> ----------------------------------------
    template <class DomainT, class Neutronizer> 
    class RandomGentor<split_interval_map<DomainT,icl::set<int>,Neutronizer> > : 
        public MapGentorT<split_interval_map<DomainT,icl::set<int>,Neutronizer> > {};

    template <class DomainT, class Neutronizer> 
    class RandomGentor<split_interval_map<DomainT,std::set<int>,Neutronizer> > : 
        public MapGentorT<split_interval_map<DomainT,std::set<int>,Neutronizer> > {};

    template <class DomainT, class CodomainT, class Neutronizer> 
    class RandomGentor<split_interval_map<DomainT,CodomainT,Neutronizer> > : 
        public MapGentorT<split_interval_map<DomainT,CodomainT,Neutronizer> > {};

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    template <class NumericDomainT, class BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section> 
    class RandomGentor<split_interval_map<NumericDomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > : 
        public MapGentorT<split_interval_map<NumericDomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > {};

    template <class NumericDomainT, class BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section> 
    class RandomGentor<interval_map<NumericDomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > : 
        public MapGentorT<interval_map<NumericDomainT,icl::bits<BitsT>,Neutronizer,Compare,Combine,Section> > {};

    // ------------------------------------------------------------------------
    template <class NumericDomainT, class BitsT>
    class RandomGentor<interval_bitset<NumericDomainT,icl::bits<BitsT> > > : 
        public MapGentorT<interval_bitset<NumericDomainT,icl::bits<BitsT> > > {};
    // ------------------------------------------------------------------------

    //NOTE: All trials to reduce code replication for RandomGentor
    // and Calibrater by introducing a fancy 
    // template template IntervalMap shipwrecked due to compilers 
    // disability to resolve the resulting instantiations. Compilers
    // always see ambiguities where there seems to be a resolution.


    // ------------------------------------------------------------------------
    // class template SomeValue:
    // TargetT is a value tuple that fits to the value generator gentor
    // of type GentorT<TargetT>. The special kind of generator can be
    // passed by the user. The only requirement is that the generator
    // implements a function 'some' which is called to generate a tuple
    // of type TargetT
    template <class TargetT, template<class>class GentorT> struct SomeValue
    {
        static void apply(TargetT& value, GentorT<TargetT>& gentor); 
    };

    template <class TargetT> 
    struct SomeValue<TargetT, RandomGentor>
    {
        static void apply(TargetT& value, RandomGentor<TargetT>& gentor) 
        {
            gentor.some(value);
        }
    };
    // ------------------------------------------------------------------------


    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    template <class TargetT, template<class>class GentorT> struct Calibrater
    {
        static void apply(GentorT<TargetT>& gentor); 
    };

    template <> 
    struct Calibrater<int, RandomGentor>
    {
        static void apply(RandomGentor<int>& gentor)
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_int());
        }
    };

    template <> 
    struct Calibrater<cnat, RandomGentor>
    {
        static void apply(RandomGentor<cnat>& gentor)
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_nat());
        }
    };

    template <> 
    struct Calibrater<double, RandomGentor>
    {
        static void apply(RandomGentor<double>& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_double());
        }
    };

    template <class BitsT> 
    struct Calibrater<icl::bits<BitsT>, RandomGentor>
    {
        static void apply(RandomGentor<icl::bits<BitsT> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.set_range(icl::interval<BitsT>::right_open(0, sizeof(BitsT)));
        }
    };


    template <ICL_COMPARE Compare> 
    struct Calibrater<discrete_interval<int,Compare>, RandomGentor>
    {
        static void apply(RandomGentor<discrete_interval<int,Compare> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_int());
        }
    };


#ifdef LAW_BASED_TEST_BOOST_POLYGON
    //--------------------------------------------------------------------------
    // boost::polygon
    //--------------------------------------------------------------------------
    template <> 
    struct Calibrater<icl::point<int>, RandomGentor>
    {
        static void apply(RandomGentor<icl::point<int> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRange(GentorProfileSgl::it()->range_int());
        }
    };

    template <> 
    struct Calibrater<icl::list<point<int> >, RandomGentor>
    {
        static void apply(RandomGentor<icl::list<point<int> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());
            point_gentor<int>* pointGentor = new point_gentor<int>;
            pointGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(pointGentor);
            gentor.setUnique(true);
        }
    };

    template <> 
    struct Calibrater<icl::list<list<point<int> > >, RandomGentor>
    {
        static void apply(RandomGentor<icl::list<list<point<int> > > >& gentor) 
        {
            point_gentor<int>* pointGentor = new point_gentor<int>;
            pointGentor->setRange(GentorProfileSgl::it()->range_int());

            polygon_gentor<list<point<int> > >* polyGentor = new polygon_gentor<list<point<int> > >;
            polyGentor->setDomainGentor(pointGentor);
            polyGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());
            polyGentor->setUnique(true);

            gentor.setDomainGentor(polyGentor);
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
        }
    };

    //--------------------------------------------------------------------------
    // nogylop::tsoob
    //--------------------------------------------------------------------------
#endif // LAW_BASED_TEST_BOOST_POLYGON


    //--------------------------------------------------------------------------
    // lists
    //--------------------------------------------------------------------------
    template <> 
    struct Calibrater<std::pair<int,int>, RandomGentor>
    {
        static void apply(RandomGentor< std::pair<int,int> >& gentor)
        {
            // Set the range within which the sizes of the generated object varies.
            NumberGentorT<int>* int_gentor_1 = new NumberGentorT<int>;
            NumberGentorT<int>* int_gentor_2 = new NumberGentorT<int>;
            int_gentor_1->setRange(GentorProfileSgl::it()->range_int());
            int_gentor_2->setRange(GentorProfileSgl::it()->range_int());
            gentor.set_first_gentor(int_gentor_1);
            gentor.set_second_gentor(int_gentor_2);
        }
    };

    template <ICL_COMPARE Compare> 
    struct Calibrater<std::pair<discrete_interval<int,Compare>, int>, RandomGentor>
    {
        static void apply(RandomGentor< std::pair<discrete_interval<int,Compare>, int> >&){}
    };

    template <ICL_COMPARE Compare> 
    struct Calibrater<std::pair<continuous_interval<double,Compare>, int>, RandomGentor>
    {
        static void apply(RandomGentor< std::pair<continuous_interval<double,Compare>, int> >&){}
    };

    template <ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<icl::list<std::pair<Interval, int> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list<std::pair<Interval, int> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            map_segment_gentor<double,int,Interval >* segment_gentor  
                = new map_segment_gentor<double,int,Interval >;
            NumberGentorT<int>* int_gentor = new NumberGentorT<int>;
            int_gentor->setRange(GentorProfileSgl::it()->range_int());
            segment_gentor->setCodomainGentor(int_gentor);
            segment_gentor->set_range(GentorProfileSgl::it()->range_interval_double());
            segment_gentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            segment_gentor->set_corange(GentorProfileSgl::it()->range_int()); // sets range of codomain_values
            gentor.setDomainGentor(segment_gentor);
        }
    };

    template <class NumericT, ICL_COMPARE Compare> 
    struct Calibrater<icl::list< continuous_interval<NumericT,Compare> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list< continuous_interval<NumericT,Compare> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericT, continuous_interval<NumericT,Compare> >* itvGentor  
                = new ItvGentorT<NumericT, continuous_interval<NumericT,Compare> >;
            itvGentor->setRange(GentorProfileSgl_numeric_range<NumericT>::get());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <class NumericT, ICL_COMPARE Compare> 
    struct Calibrater<icl::list< discrete_interval<NumericT,Compare> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list< discrete_interval<NumericT,Compare> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericT, discrete_interval<NumericT,Compare> >* itvGentor  
                = new ItvGentorT<NumericT, discrete_interval<NumericT,Compare> >;
            itvGentor->setRange(GentorProfileSgl_numeric_range<NumericT>::get());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <class NumericT, ICL_COMPARE Compare> 
    struct Calibrater<icl::list< right_open_interval<NumericT,Compare> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list< right_open_interval<NumericT,Compare> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericT, right_open_interval<NumericT,Compare> >* itvGentor  
                = new ItvGentorT<NumericT, right_open_interval<NumericT,Compare> >;
            itvGentor->setRange(GentorProfileSgl_numeric_range<NumericT>::get());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(itvGentor);
        }
    };

    template <class NumericT> 
    struct Calibrater<icl::list<NumericT>, RandomGentor>
    {
        static void apply(RandomGentor< icl::list<NumericT> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            NumberGentorT<NumericT>* domainGentor = new NumberGentorT<NumericT>;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericT>::get());
            gentor.setDomainGentor(domainGentor);
        }
    };

    template <> 
    struct Calibrater<icl::list<std::pair<int, int> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list< std::pair<int, int> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            std_pair_gentor<int,int>* pair_gentor  = new std_pair_gentor<int,int>;
            NumberGentorT<int>* int_gentor_1 = new NumberGentorT<int>;
            NumberGentorT<int>* int_gentor_2 = new NumberGentorT<int>;
            int_gentor_1->setRange(GentorProfileSgl::it()->range_int());
            int_gentor_2->setRange(GentorProfileSgl::it()->range_int());
            pair_gentor->set_first_gentor(int_gentor_1);
            pair_gentor->set_second_gentor(int_gentor_2);
            gentor.setDomainGentor(pair_gentor);
        }
    };

    template <ICL_COMPARE Compare> 
    struct Calibrater<icl::list<std::pair<discrete_interval<int,Compare>, int> >, RandomGentor>
    {
        static void apply(RandomGentor< icl::list<std::pair<discrete_interval<int,Compare>, int> > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            map_segment_gentor<int,int,discrete_interval<int,Compare> >* segment_gentor  
                = new map_segment_gentor<int,int,discrete_interval<int,Compare> >;
            NumberGentorT<int>* int_gentor = new NumberGentorT<int>;
            int_gentor->setRange(GentorProfileSgl::it()->range_int());
            segment_gentor->setCodomainGentor(int_gentor);
            segment_gentor->set_range(GentorProfileSgl::it()->range_interval_int());
            segment_gentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            segment_gentor->set_corange(GentorProfileSgl::it()->range_int()); // sets range of codomain_values
            gentor.setDomainGentor(segment_gentor);
        }
    };

    //--------------------------------------------------------------------------
    // sets
    //--------------------------------------------------------------------------
    template <> 
    struct Calibrater<icl::set<int>, RandomGentor>
    {
        static void apply(RandomGentor<icl::set<int> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            NumberGentorT<int>* intGentor = new NumberGentorT<int>;
            intGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(intGentor);
        }
    };

    template <> 
    struct Calibrater<icl::set<double>, RandomGentor>
    {
        static void apply(RandomGentor<icl::set<double> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            NumberGentorT<double>* elemGentor = new NumberGentorT<double>;
            elemGentor->setRange(GentorProfileSgl::it()->range_double());
            gentor.setDomainGentor(elemGentor);
        }
    };

    //--------------------------------------------------------------------------
    template <> 
    struct Calibrater<std::set<int>, RandomGentor>
    {
        static void apply(RandomGentor<std::set<int> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            NumberGentorT<int>* intGentor = new NumberGentorT<int>;
            intGentor->setRange(GentorProfileSgl::it()->range_int());
            gentor.setDomainGentor(intGentor);
        }
    };

    template <> 
    struct Calibrater<std::set<double>, RandomGentor>
    {
        static void apply(RandomGentor<std::set<double> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            NumberGentorT<double>* elemGentor = new NumberGentorT<double>;
            elemGentor->setRange(GentorProfileSgl::it()->range_double());
            gentor.setDomainGentor(elemGentor);
        }
    };

    //----------------------------------------------------------------------------
    // icl::{,separate,split}_interval_set<NumericDomainT>
    //----------------------------------------------------------------------------
    template <class NumericDomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<interval_set<NumericDomainT,Compare,Interval>, RandomGentor>
    {
        static void apply(RandomGentor<interval_set<NumericDomainT,Compare,Interval> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* domainGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());
            domainGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(domainGentor);
        }
    };

    template <class NumericDomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<separate_interval_set<NumericDomainT,Compare,Interval>, RandomGentor>
    {
        static void apply(RandomGentor<separate_interval_set<NumericDomainT,Compare,Interval> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* domainGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());
            domainGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(domainGentor);
        }
    };

    template <class NumericDomainT, ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<split_interval_set<NumericDomainT,Compare,Interval>, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_set<NumericDomainT,Compare,Interval> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* domainGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());
            domainGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(domainGentor);
        }
    };

    //--------------------------------------------------------------------------
    // icl::tree
    //--------------------------------------------------------------------------
#ifdef USE_ICL_TREE
    template <> 
    struct Calibrater<icl::tree<int>, RandomGentor>
    {
        static void apply(RandomGentor<icl::tree<int> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());
            ItvGentorT<int, discrete_interval<int,Compare> >* itvGentor 
                = new ItvGentorT<int, discrete_interval<int,Compare> >;
            typename icl::interval<int>::type valRange = GentorProfileSgl::it()->range_interval_int();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());
            gentor.setDomainGentor(itvGentor);
        }
    };
#endif

    //----------------------------------------------------------------------------
    // icl::map<DomainT,CodomainT,Neutronizer>
    //----------------------------------------------------------------------------
    template <typename NumericDomainT, class Neutronizer> 
    struct Calibrater<icl::map<NumericDomainT,icl::set<int>,Neutronizer>, RandomGentor>
    {
        static void apply(RandomGentor<icl::map<NumericDomainT,icl::set<int>,Neutronizer> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<NumericDomainT>* domainGentor = new NumberGentorT<NumericDomainT>;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());

            SetGentorT<icl::set<int> >* codomainGentor = new SetGentorT<icl::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl_numeric_range<int>::get());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <typename NumericDomainT, class Neutronizer> 
    struct Calibrater<icl::map<NumericDomainT,std::set<int>,Neutronizer>, RandomGentor>
    {
        static void apply(RandomGentor<icl::map<NumericDomainT,std::set<int>,Neutronizer> >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<NumericDomainT>* domainGentor = new NumberGentorT<NumericDomainT>;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());

            SetGentorT<std::set<int> >* codomainGentor = new SetGentorT<std::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl_numeric_range<int>::get());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <typename NumericDomainT, typename NumericCodomainT, class Neutronizer> 
    struct Calibrater<icl::map<NumericDomainT,NumericCodomainT,Neutronizer>, RandomGentor>
    {
        static void apply(RandomGentor<icl::map<NumericDomainT,NumericCodomainT,Neutronizer> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<NumericDomainT>* domainGentor = new NumberGentorT<NumericDomainT>;
            NumberGentorT<NumericCodomainT>* codomainGentor = new NumberGentorT<NumericCodomainT>;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());
            codomainGentor->setRange(GentorProfileSgl_numeric_range<NumericCodomainT>::get());
            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <typename NumericDomainT, typename BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section> 
    struct Calibrater<icl::map<NumericDomainT,icl::bits<BitsT>,Neutronizer,
                               Compare,Combine,Section>, RandomGentor>
    {
        static void apply(RandomGentor<icl::map<NumericDomainT,icl::bits<BitsT>,Neutronizer,
                                                Compare,Combine,Section> >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            NumberGentorT<NumericDomainT>* domainGentor   = new NumberGentorT<NumericDomainT>;
            bits_gentor<BitsT>*            codomainGentor = new bits_gentor<BitsT>;
            domainGentor->setRange(GentorProfileSgl_numeric_range<NumericDomainT>::get());
            codomainGentor->set_range(icl::interval<BitsT>::closed(0, (std::numeric_limits<BitsT>::max)()));
            gentor.setDomainGentor(domainGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    //----------------------------------------------------------------------------
    // icl::interval_map<DomainT,CodomainT,Neutronizer>
    //----------------------------------------------------------------------------
    template <class NumericDomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<interval_map<NumericDomainT,icl::set<int>,
                                   Neutronizer,Compare,Combine,Section,
                                   Interval >, RandomGentor>
    {
        static void apply(RandomGentor<interval_map<NumericDomainT,icl::set<int>,
                                                    Neutronizer,Compare,Combine,Section,
                                                    Interval > >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            SetGentorT<icl::set<int> >* codomainGentor = new SetGentorT<icl::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl::it()->range_int());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <class NumericDomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<interval_map<NumericDomainT,std::set<int>,
                                   Neutronizer,Compare,Combine,Section,
                                   Interval >, RandomGentor>
    {
        static void apply(RandomGentor<interval_map<NumericDomainT,std::set<int>,
                                                    Neutronizer,Compare,Combine,Section,
                                                    Interval > >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            SetGentorT<std::set<int> >* codomainGentor = new SetGentorT<std::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl::it()->range_int());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <typename NumericDomainT, typename NumericCodomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<interval_map<NumericDomainT,NumericCodomainT,
                                   Neutronizer,Compare,Combine,Section,
                                   Interval >, RandomGentor>
    {
        static void apply(RandomGentor<interval_map<NumericDomainT,NumericCodomainT, 
                                                    Neutronizer,Compare,Combine,Section,
                                                    Interval > >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            NumberGentorT<NumericCodomainT>* codomainGentor = new NumberGentorT<NumericCodomainT>;
            codomainGentor->setRange(GentorProfileSgl_numeric_range<NumericCodomainT>::get());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    //----------------------------------------------------------------------------
    // icl::split_interval_map<DomainT,CodomainT,Neutronizer>
    //----------------------------------------------------------------------------
    template <class NumericDomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<split_interval_map<NumericDomainT,icl::set<int>,
                                         Neutronizer,Compare,Combine,Section,
                                         Interval >, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<NumericDomainT,icl::set<int>,
                                                          Neutronizer,Compare,Combine,Section,
                                                          Interval > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            SetGentorT<icl::set<int> >* codomainGentor = new SetGentorT<icl::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl::it()->range_int());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <class NumericDomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<split_interval_map<NumericDomainT,std::set<int>,
                                         Neutronizer,Compare,Combine,Section,
                                         Interval >, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<NumericDomainT,std::set<int>,
                                                          Neutronizer,Compare,Combine,Section,
                                                          Interval > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            SetGentorT<std::set<int> >* codomainGentor = new SetGentorT<std::set<int> >;
            NumberGentorT<int>* elementGentor = new NumberGentorT<int>;
            elementGentor->setRange(GentorProfileSgl::it()->range_int());

            codomainGentor->setDomainGentor(elementGentor);            
            codomainGentor->setRangeOfSampleSize(GentorProfileSgl::it()->range_codomain_ContainerSize());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };

    template <typename NumericDomainT, typename NumericCodomainT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<split_interval_map<NumericDomainT,NumericCodomainT,
                                         Neutronizer,Compare,Combine,Section,
                                         Interval >, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<NumericDomainT,NumericCodomainT,
                                       Neutronizer,Compare,Combine,Section,
                                       Interval > >& gentor) 
        {
            // Set the range within which the sizes of the generated object varies.
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            NumberGentorT<NumericCodomainT>* codomainGentor = new NumberGentorT<NumericCodomainT>;
            codomainGentor->setRange(GentorProfileSgl_numeric_range<NumericCodomainT>::get());

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };


    template <typename NumericDomainT, typename BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section,
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<interval_map<NumericDomainT,icl::bits<BitsT>,
                                   Neutronizer,Compare,Combine,Section,
                                   Interval >, RandomGentor>
    {
        static void apply(RandomGentor<interval_map<NumericDomainT,icl::bits<BitsT>,
                                                    Neutronizer,Compare,Combine,Section,
                                                    Interval > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            bits_gentor<BitsT>* codomainGentor = new bits_gentor<BitsT>;
            codomainGentor->set_range(icl::interval<BitsT>::closed(0, (std::numeric_limits<BitsT>::max)()));

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };


    template <typename NumericDomainT, typename BitsT, class Neutronizer,
              ICL_COMPARE Compare, ICL_COMBINE Combine, ICL_SECTION Section, 
              ICL_INTERVAL(ICL_COMPARE) Interval> 
    struct Calibrater<split_interval_map<NumericDomainT,icl::bits<BitsT>,
                                         Neutronizer,Compare,Combine,Section,
                                         Interval >, RandomGentor>
    {
        static void apply(RandomGentor<split_interval_map<NumericDomainT,icl::bits<BitsT>,
                                                          Neutronizer,Compare,Combine,Section,
                                                          Interval > >& gentor) 
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            bits_gentor<BitsT>* codomainGentor = new bits_gentor<BitsT>;
            codomainGentor->set_range(icl::interval<BitsT>::closed(0, (std::numeric_limits<BitsT>::max)()));

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };
    // ---------------------------------------------------------------------------

    template <typename NumericDomainT, typename BitsT,
              ICL_COMPARE Compare, ICL_INTERVAL(ICL_COMPARE) Interval>
    struct Calibrater<interval_bitset<NumericDomainT,icl::bits<BitsT>, 
                                      Compare, Interval >, RandomGentor>
    {
        static void apply(RandomGentor<interval_bitset<NumericDomainT,icl::bits<BitsT>,
                                                       Compare, Interval> >& gentor)
        {
            gentor.setRangeOfSampleSize(GentorProfileSgl::it()->range_ContainerSize());

            // If it is a container: (Create and) Pass the generator(s) for their contents
            // NumberGentorT<int> intGentor;
            ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >* itvGentor 
                = new ItvGentorT<NumericDomainT, ICL_INTERVAL_TYPE(Interval,NumericDomainT,Compare) >;
            typename icl::interval<NumericDomainT>::type valRange = GentorProfileSgl_numeric_range<NumericDomainT>::get();
            itvGentor->setValueRange(valRange.lower(), valRange.upper());
            itvGentor->setMaxIntervalLength(GentorProfileSgl::it()->maxIntervalLength());

            bits_gentor<BitsT>* codomainGentor = new bits_gentor<BitsT>;
            codomainGentor->set_range(icl::interval<BitsT>::closed(0, (std::numeric_limits<BitsT>::max)()));

            gentor.setDomainGentor(itvGentor);
            gentor.setCodomainGentor(codomainGentor);
        }
    };
    // ---------------------------------------------------------------------------


}} // namespace icl boost