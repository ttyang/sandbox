/*-----------------------------------------------------------------------------+    
Copyright (c) 2007-2009: Joachim Faulhaber
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef __tuple_computer_JOFA_040614_H__
#define __tuple_computer_JOFA_040614_H__

#include <sstream>
#include <boost/icl/map.hpp>
#include <boost/icl_xt/set.hpp>
#include <boost/icl_xt/var_tuple_order.hpp>
#include <boost/icl/split_interval_map.hpp>

namespace boost{namespace icl
{

    template <int VarCount>
    class tuple_computer_interface
    {
    public:
        typedef var_tuple<VarCount> var_tuple_type;
        typedef var_tuple_order<var_tuple_type> tuple_order_type;
        typedef icl::set<var_tuple_type, var_tuple_order> tuple_set_type;

    public:
        virtual ~tuple_computer_interface(){};

        //JODO Erg�nzung + Comments + Zerlegung
        virtual void domain(tuple_set_type&)const=0;

        /// Add keyset of *this computer to tupelset 'accu'
        virtual void addDomain(tuple_set_type& accu)const=0;

        /** Load Computer from src. If *this has a different TupelOrder
            *this is not a copy of 'src' but a recomputation according
            to the different TupelOrder */
        virtual void load(const tuple_computer_interface& src)=0;

        /** Align *this TupelsComputers for domain such that this->domain()==domain.
            Insert 0 or empty values for all tupels which are not in *this.    */
        virtual void alignFor(const tuple_set_type& domain)=0;

        virtual std::string as_string()const=0;
    };



    /// Base class template for tuple computers aggregating values associated to tuples
    /** On insertion of a (t1, ..., tn)->v tuple value pair, a value within
        the tuple computer is summed by v, if the tuple t is already contained in
        the tuple_computer_base.

        Template parameter VarCount defines the size of the tuples.

        Template parameter CounterT is the value type of the tuple_computer_base.
        Those are the values to aggregated.
    */
    template <int VarCount, class CounterT>
    class tuple_computer_base : public tuple_computer_interface<VarCount>
    {
    public:
        typedef tuple_computer_interface<VarCount> base_type;
        typedef typename base_type::tuple_set_type tuple_set_type;

    public:

    /** @name A: Type definitions for the template class 
    */
    //@{ 
        typedef var_tuple<VarCount> var_tuple_type;
        typedef var_tuple_order<var_tuple_type> tuple_order_type;
        /// Container type for the implementation 
        typedef icl::map<var_tuple_type, CounterT, partial_absorber, var_tuple_order> ImplMapTD;
        /// iterator
        typedef typename ImplMapTD::iterator iterator;
        /// const_iterator
        typedef typename ImplMapTD::const_iterator const_iterator;

        /// value type of the implementing container
        typedef typename ImplMapTD::value_type value_type;
        /// key type of the implementing container
        typedef typename ImplMapTD::key_type   key_type;
        /// data type of the implementing container
        typedef typename ImplMapTD::data_type  data_type;

        /// Type of strict weak ordering
        typedef typename ImplMapTD::key_compare key_compare;

        typedef CounterT counter_type;
    //@}

        // B: Constructors, destructors, assignment
        /// Default constructor for the empty map 
        tuple_computer_base(): m_map() {}
        /// Copy constructor
        tuple_computer_base(const tuple_computer_base& src): m_map(src.m_map) {}

        /// Construct from order
        tuple_computer_base(const key_compare& ord): m_map(ord) {}

        /// Virtual destructor
        virtual ~tuple_computer_base(){};


        /// Assignment operator
        tuple_computer_base& operator = (const tuple_computer_base& src) 
        {
            m_map.ImplMapTD::operator=(src.m_map);
            return *this;  
        }

        // ------------------------------------------------------------------------
        // Interface MapIT
        // C:
        
        /// Remove all elements from the map
        void clear() { m_map.clear(); }
        /// Is the map empty?
        bool empty()const { return m_map.empty(); }
        /// Does the map contain an element for key x
        bool contains(const var_tuple_type& x)const { return m_map.contains(x); }
        /// Does the map contain a valuepair (tupel, counter)
        bool contains(const value_type& x)const;

        /// Get the set of keys
        void domain(tuple_set_type& domain)const;
        /// 
        void addDomain(tuple_set_type& domain)const;


    /** @name F: Tester
    */
    //@{
        /// <tt>*this</tt> is subset of <tt>super</tt>
        bool isSubsetOf(const tuple_computer_base& super)const;
        /// <tt>*this</tt> is subset of <tt>super</tt>
        bool operator <= (const tuple_computer_base& super)const;

        /// Equality
        bool isEqual(const tuple_computer_base& x2)const
        { return isSubsetOf(x2) && x2.isSubsetOf(*this); }
        /// Equality operator
        bool operator == (const tuple_computer_base& x2)const { return isEqual(x2); }
        /// Inequality operator
        bool operator != (const tuple_computer_base& x2)const { return !isEqual(x2); }

    //@}


    /** @name G: Modificators
    */
    //@{ 
        /** Insertion of a (tupel, content) pair <tt>(t,x)</tt> */        
        void insert(const var_tuple_type& t, CounterT x) 
        { insert( value_type(t, x) ); }

        /** Insertion of a (tupel, content) pair as <tt>value_pair</tt> */        
        void insert(const value_type& vt); 
    //@}

    /** @name H: value search
    */
    //@{
        /** */
        iterator find(const var_tuple_type& tupel) { return m_map.find(tupel); }
        const_iterator find(const var_tuple_type& tupel)const { return m_map.find(tupel); }
        //@}



    /** @name I: Interval iterators
    */
    //@{
        ///
        iterator begin() { return m_map.begin(); }
        ///
        iterator end()   { return m_map.end(); }
        ///
        const_iterator begin()const { return m_map.begin(); }
        ///
        const_iterator end()const   { return m_map.end(); }
    //@}

    /** @name S: String representation
    */
    //@{
        ///
        std::string as_string()const 
        {
            std::stringstream str;
            str << m_map;
            return str.str();
        }
    //@}


    int size()const { return m_map.size(); }

    // NOTE! Die Ordnung, die ein TupelComputer verwendet ist fest, wir k�nnen zwar eine
    // Kopie dieses Ordnungs-Objektes bekommen, aber keine Referenz. Also sind alle
    // m�glichen Transformationen nur dadurch zu machen, dass wir einen neuen
    // Tupelcomputer mit entsprechendem Ordnungsobjekt (Funktor) kreieren und es
    // dann bef�llen. Der OrdnungsFunktor muss alle M�glichkeiten zur Verf�gung
    // stellen, also Umsortierung (Permutation), Projektion und Gruppierung.
    // Gruppierung beinhaltet auch bedingte �quivalenz. Dazu brauchen wir noch
    // Filter: Ausblenden von Wertemengen und bedingte Filter: Ausblenden von Werten
    // in Abh�ngigkeit von den Werten anderer UVs (oder UV-Gruppierungen)

    private:
        ImplMapTD m_map;
    };


    template <int VarCount, class CounterT>
    void tuple_computer_base<VarCount, CounterT>::domain(tuple_set_type& domain)const
    {
        domain.clear();
        addDomain(domain);
    }


    template <int VarCount, class CounterT>
    void tuple_computer_base<VarCount, CounterT>::addDomain(tuple_set_type& domain)const
    {
        ICL_const_FORALL_THIS(tupel_)
            domain.insert((*tupel_).first);
    }


    template <int VarCount, class CounterT>
    void tuple_computer_base<VarCount, CounterT>::insert(const value_type& val)
    {
        std::pair<typename ImplMapTD::iterator,bool> insertion = m_map.insert(val);

        if(!insertion.second)
            (*insertion.first).second += val.second;
    }


    // ------------------------------------------------------------------------
    // JODO THINK: Es ist fraglich, ob wir �berhaupt abgeleitete TupelComputer
    // brauchen. Vielleicht l�sst sich ja alles �ber entsprechende CounterT-
    // Instanzen regeln.
    // ------------------------------------------------------------------------

    /// An amount_tuple_computer aggregates values (amounts) associated to tuples. 
    /** amount_tuple_computer is a TupleComputer that aggregates amounts
        associated to tuples.

        Template parameter VarCount defines the size of the used tuples.

        CounteeT is the amount type, the type that is aggrgated.
        Usually this shall be a numeric type. Yet it can also be
        intantiated with any +=summable class type.
    */
    template <int VarCount, class CounteeT>
        class amount_tuple_computer : public tuple_computer_base<VarCount, CounteeT>
    {
    public:
        typedef tuple_computer_base<VarCount, CounteeT> base_type;
        typedef typename base_type::key_type var_tuple_type;
        typedef typename base_type::key_type key_type;
        typedef typename base_type::key_compare key_compare;
        typedef typename base_type::tuple_set_type tuple_set_type;

    public:
        // Default Ctor
        amount_tuple_computer(): base_type() {}
        // Copy Ctor
        amount_tuple_computer(const amount_tuple_computer& src): base_type(src) {}
        // Ctor from strict weak ordering
        amount_tuple_computer(const key_compare& order): base_type(order) {}

    public:
        // Special interface that can not be expressed by TupelComputerT

        void load(const tuple_computer_interface<VarCount>& srcI);

        void alignFor(const tuple_set_type& domain)
        {
            ICL_const_FORALL(typename tuple_set_type, it_, domain)
                this->insert(*it_, CounteeT());
        }

    };

    template <int VarCount, class CounterT>
    void amount_tuple_computer<VarCount, CounterT>::load(const tuple_computer_interface<VarCount>& srcI)
    {
        const amount_tuple_computer& src = dynamic_cast<const amount_tuple_computer&>(srcI);
        ICL_const_FORALL(typename amount_tuple_computer, it_, src)
            this->insert(*it_);
    }



    // ------------------------------------------------------------------------
    /// A date_tuple_computer aggregates points in time (dates) associated to tuples. 
    /** class date_tuple_computer: Merkmalskombinationsrechner (flavor: Zeitpunktrechner) 

        Jedem Tupel (Merkmalskombination) wird ein Map assoziiert, das Zeitpunkte
        (Dates) z�hlen kann. 
    */
    template <int VarCount, class TimeT, class CounteeT>
    class date_tuple_computer : 
        public tuple_computer_base<VarCount, icl::map<TimeT, CounteeT> >
    {
    public:
        typedef typename icl::map<TimeT, CounteeT> counter_type;
        typedef tuple_computer_base<VarCount, counter_type> base_type;
        typedef typename base_type::var_tuple_type var_tuple_type;
        typedef typename base_type::key_compare key_compare;
        typedef typename icl::set<var_tuple_type, var_tuple_order> tuple_set_type;

    public:
        // Default Ctor
        date_tuple_computer(): base_type() {}
        // Copy Ctor
        date_tuple_computer(const date_tuple_computer& src): base_type(src) {}
        // Ctor from strict weak ordering
        date_tuple_computer(const key_compare& order): base_type(order) {}

    public:
        // Special interface that can not be expressed by TupelComputerT
        
        void load(const tuple_computer_interface<VarCount>& srcI);

        void alignFor(const tuple_set_type& domain)
        {
            ICL_const_FORALL(typename tuple_set_type, it_, domain)
                insert(*it_, counter_type());
        }

    };

    template <int VarCount, class TimeT, class CounteeT>
    void date_tuple_computer<VarCount,TimeT,CounteeT>::load(const tuple_computer_interface<VarCount>& srcI)
    {
        const date_tuple_computer& src = dynamic_cast<const date_tuple_computer&>(srcI);
        ICL_const_FORALL(typename date_tuple_computer, it_, src)
            insert(*it_);
    }



    // ------------------------------------------------------------------------
    /// Aggregates intervals associated to tuples
    /** class interval_tuple_computer: Merkmalskombinationsrechner (flavor: 
        Zeitraumrechner). Jedem Tupel (Merkmalskombination) wird ein 
        split_interval_map assoziiert, das Zeitr�ume (Itv=Interval) z�hlen
        kann. Genauer gesagt werden Zust�nde gez�hlt, die f�r einen Zeitraum
        anhalten. Bei �berlappungen der Zeitr�ume m�ssen die die H�ufigkeiten
        im split_interval_map entsprechend aufaddiert werden.
    */
    template <int VarCount, class TimeT, class CounteeT>
    class interval_tuple_computer : 
        public tuple_computer_base<VarCount, 
                                   split_interval_map<TimeT, CounteeT> >
    {
    public:
        typedef split_interval_map<TimeT, CounteeT>          counter_type;
        typedef tuple_computer_base<VarCount, counter_type>  base_type;
        typedef typename base_type::var_tuple_type           var_tuple_type;
        typedef typename base_type::key_compare              key_compare;
        typedef icl::set<var_tuple_type, var_tuple_order>    tuple_set_type;
        typedef typename base_type::counter_type::interval_type interval_type;

    private:
        typedef icl::map<TimeT, CounteeT> DateMapTD;

    public:
        // Default Ctor
        interval_tuple_computer(): base_type() {}
        // Copy Ctor
        interval_tuple_computer(const interval_tuple_computer& src): base_type(src) {}
        // Ctor from strict weak ordering
        interval_tuple_computer(const key_compare& order): base_type(order) {}

    public:
        // Special interface that can not be expressed by TupelComputerT

        void load(const tuple_computer_interface<VarCount>& srcI);

        // Eine Menge von ZeitPUNKTEN einf�gen. Diese werden in Intervalle gewandelt
        void insertDateMap(const var_tuple_type tup, const DateMapTD& date);

        void alignFor(const tuple_set_type& domain)
        {
            ICL_const_FORALL(typename tuple_set_type, it_, domain)
                insert(*it_, counter_type());
        }
    };


    template <int VarCount, class TimeT, class CounteeT>
    void interval_tuple_computer<VarCount,TimeT,CounteeT>::load(const tuple_computer_interface<VarCount>& srcI)
    {
        const interval_tuple_computer& src = dynamic_cast<const interval_tuple_computer&>(srcI);
        ICL_const_FORALL(typename interval_tuple_computer, it_, src)
            insert(*it_);
    }

    template <int VarCount, class TimeT, class CounteeT>
    void interval_tuple_computer<VarCount,TimeT,CounteeT>::insertDateMap(const var_tuple_type tup, const DateMapTD& date)
    {
        counter_type itvCounter;
        ICL_const_FORALL(typename DateMapTD, date_, date)
        {
            itvCounter.insert(
                counter_type::value_type(
                    counter_type::interval_type((*date_).first, (*date_).first), 
                    (*date_).second
                    )
                );
        }

        insert(value_type(tup, itvCounter));
    }



    //JODO: Where to put this kind of functionality
    template <class SubType, class ItvDomTV, class CodomTV>
    void intervalize(interval_base_map<SubType, ItvDomTV, CodomTV>& itvMap, 
                     const icl::map<ItvDomTV, CodomTV>& dateMap)
    {
        typedef icl::map<ItvDomTV, CodomTV> DateMapTD;
        typedef interval_base_map<SubType, ItvDomTV, CodomTV> ItvMapTD;

        itvMap.clear();
        ICL_const_FORALL(typename DateMapTD, date_, dateMap)
        {
            itvMap.insert(
                ItvMapTD::value_type(
                    ItvMapTD::interval_type((*date_).first, (*date_).first), 
                    (*date_).second
                    )
                );
        }
    }

    //JODO Move this; 
    //JODO DESIGN: Memfunction of interval_base_set? destructive + constructive. Self-deviding

    //NOTE: ItvMap GridSum
    template <class SubType, class ItvDomTV, class CodomTV>
    void sumWithin(interval_base_map<SubType, ItvDomTV, CodomTV>& gridSums, 
                   interval_base_map<SubType, ItvDomTV, CodomTV>& interSection, 
                   const interval_base_map<SubType, ItvDomTV, CodomTV>& itvMap, 
                   const split_interval_set<ItvDomTV>& grid)
    {
        typedef interval_base_map<SubType, ItvDomTV, CodomTV> ItvMapTD;
        typedef split_interval_set<ItvDomTV> DiscItvSetTD;

        gridSums.clear();
        interSection.clear();
        if(itvMap.empty()) return;

        ItvMapTD* aux = itvMap.cons();
        //JODO OPTI: optimize using the ordering: if intervalls are beyond borders we can terminate
        ICL_const_FORALL(typename DiscItvSetTD, itv_, grid)
        {
            itvMap.intersect(*aux, *itv_);
            gridSums.insert(ItvMapTD::value_type(*itv_, (*aux).volume()));
            interSection += (*aux);
        }
        
    }

}} // namespace icl boost

#endif // __tuple_computer_JOFA_040614_H__



