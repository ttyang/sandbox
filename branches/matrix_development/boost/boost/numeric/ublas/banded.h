//  
//  Copyright (c) 2000-2001
//  Joerg Walter, Mathias Koch
//  
//  Permission to use, copy, modify, distribute and sell this software
//  and its documentation for any purpose is hereby granted without fee,
//  provided that the above copyright notice appear in all copies and
//  that both that copyright notice and this permission notice appear
//  in supporting documentation.  The authors make no representations
//  about the suitability of this software for any purpose.  
//  It is provided "as is" without express or implied warranty.
//  
//  The authors gratefully acknowledge the support of 
//	GeNeSys mbH & Co. KG in producing this work.
//

#ifndef NUMERICS_BANDED_H
#define NUMERICS_BANDED_H

#include "config.h"
#include "storage.h"
#include "vector_et.h"
#include "matrix_et.h"

// Iterators based on ideas of Jeremy Siek

namespace numerics {

    // Array based band matrix class 
    template<class T, class F, class A>
    class banded_matrix: 
        public matrix_expression<banded_matrix<T, F, A> > {
    public:      
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T &const_reference_type;
        typedef T &reference_type;
        typedef F functor_type;
        typedef A array_type;
        typedef const banded_matrix<T, F, A> const_self_type;
        typedef banded_matrix<T, F, A> self_type;
        typedef const matrix_const_reference<const_self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef const matrix_row<const_self_type> const_matrix_row_type;
        typedef matrix_row<self_type> matrix_row_type;
        typedef const matrix_column<const_self_type> const_matrix_column_type;
        typedef matrix_column<self_type> matrix_column_type;
        typedef const matrix_range<const_self_type> const_matrix_range_type;
        typedef matrix_range<self_type> matrix_range_type;
        typedef struct sparse_tag storage_category;
        typedef typename F::orientation_category orientation_category;

        // Construction and destruction
        NUMERICS_INLINE
        banded_matrix (): 
            size1_ (0), size2_ (0),
            lower_ (0), upper_ (0), data_ (0) {}
        NUMERICS_INLINE
        banded_matrix (size_type size1, size_type size2, size_type lower, size_type upper): 
            size1_ (size1), size2_ (size2),
            lower_ (lower), upper_ (upper),
            data_ (std::min (size1, size2) * (lower + 1 + upper)) {}
        NUMERICS_INLINE
        banded_matrix (const banded_matrix &m): 
            size1_ (m.size1_), size2_ (m.size2_),       
            lower_ (m.lower_), upper_ (m.upper_),
            data_ (m.data_) {}
        template<class AE>
        NUMERICS_EXPLICIT NUMERICS_INLINE
        banded_matrix (size_type lower, size_type upper, const matrix_expression<AE> &ae): 
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()),
            lower_ (lower), upper_ (upper),
            data_ (std::min (ae ().size1 (), ae ().size2 ()) * (lower + 1 + upper)) {
            matrix_assign<scalar_assign<value_type, NUMERICS_TYPENAME AE::value_type> > () (*this, ae); 
        }

        // Resizing
        NUMERICS_INLINE
        void resize (size_type size1, size_type size2, size_type lower, size_type upper) {
            size1_ = size1;
            size2_ = size2;
            lower_ = lower;
            upper_ = upper;
            data_.resize (std::min (size1, size2) * (lower + 1 + upper));
        }

        NUMERICS_INLINE
        size_type size1 () const { 
            return size1_;
        }
        NUMERICS_INLINE
        size_type size2 () const { 
            return size2_;
        }
        NUMERICS_INLINE
        size_type lower () const {
            return lower_;
        }
        NUMERICS_INLINE
        size_type upper () const {
            return upper_;
        }

        // Element access
        NUMERICS_INLINE
        value_type operator () (size_type i, size_type j) const {
            check<bad_index>::precondition (i < size1_);
            check<bad_index>::precondition (j < size2_);
            size_type k = std::min (i, j);
            size_type l = lower_ + j - i;
            if (k < std::min (size1_, size2_) &&
                l < lower_ + 1 + upper_) 
                return data_ [functor_type::element (k, std::min (size1_, size2_),
                                                     l, lower_ + 1 + upper_)]; 
            return value_type ();
        }
        NUMERICS_INLINE
        reference_type operator () (size_type i, size_type j) {
            check<bad_index>::precondition (i < size1_);
            check<bad_index>::precondition (j < size2_);
            size_type k = std::min (i, j);
            size_type l = lower_ + j - i;
            return data_ [functor_type::element (k, std::min (size1_, size2_),
                                                 l, lower_ + 1 + upper_)]; 
        }

        NUMERICS_INLINE
        const_matrix_row_type operator [] (size_type i) const {
            return const_matrix_row_type (*this, i);
        }
        NUMERICS_INLINE
        matrix_row_type operator [] (size_type i) {
            return matrix_row_type (*this, i);
        }
        NUMERICS_INLINE
        const_matrix_row_type row (size_type i) const {
            return const_matrix_row_type (*this, i);
        }
        NUMERICS_INLINE
        matrix_row_type row (size_type i) {
            return matrix_row_type (*this, i);
        }
        NUMERICS_INLINE
        const_matrix_column_type column (size_type j) const {
            return const_matrix_column_type (*this, j);
        }
        NUMERICS_INLINE
        matrix_column_type column (size_type j) {
            return matrix_column_type (*this, j);
        }

        NUMERICS_INLINE
        const_matrix_range_type project (size_type start1, size_type stop1, size_type start2, size_type stop2) const {
            return const_matrix_range_type (*this, start1, stop1, start2, stop2);
        }
        NUMERICS_INLINE
        const_matrix_range_type project (const range &r1, const range &r2) const {
            return const_matrix_range_type (*this, r1, r2);
        }
        NUMERICS_INLINE
        matrix_range_type project (size_type start1, size_type stop1, size_type start2, size_type stop2) {
            return matrix_range_type (*this, start1, stop1, start2, stop2);
        }
        NUMERICS_INLINE
        matrix_range_type project (const range &r1, const range &r2) {
            return matrix_range_type (*this, r1, r2);
        }

        // Assignment
        NUMERICS_INLINE
        banded_matrix &operator = (const banded_matrix &m) { 
            check<bad_size>::precondition (size1_ == m.size1_);
            check<bad_size>::precondition (size2_ == m.size2_);
            check<bad_size>::precondition (lower_ == m.lower_);
            check<bad_size>::precondition (upper_ == m.upper_);
            data_ = m.data_;
            return *this;
        }
        NUMERICS_INLINE
        banded_matrix &assign_temporary (banded_matrix &m) { 
            swap (m);
            return *this;
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix &operator = (const matrix_expression<AE> &ae) { 
#ifndef USE_GCC
            return assign_temporary (self_type (lower_, upper_, ae));
#else
            return assign (self_type (lower_, upper_, ae));
#endif
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix &assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_assign<value_type, NUMERICS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix& operator += (const matrix_expression<AE> &ae) {
#ifndef USE_GCC
            return assign_temporary (self_type (lower_, upper_, *this + ae));
#else
            return assign (self_type (lower_, upper_, *this + ae));
#endif
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign<value_type, NUMERICS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix& operator -= (const matrix_expression<AE> &ae) {
#ifndef USE_GCC
            return assign_temporary (self_type (lower_, upper_, *this - ae));
#else
            return assign (self_type (lower_, upper_, *this - ae));
#endif
        }
        template<class AE>
        NUMERICS_INLINE
        banded_matrix &minus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_minus_assign<value_type, NUMERICS_TYPENAME AE::value_type> > () (*this, ae); 
            return *this;
        }
        template<class AT>
        NUMERICS_INLINE
        banded_matrix& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign<value_type, AT> > () (*this, at);
            return *this;
        }

        // Swapping
        NUMERICS_INLINE
	    void swap (banded_matrix &m) {
            check<external_logic>::precondition (this != &m);
            check<bad_size>::precondition (size1_ == m.size1_);
            check<bad_size>::precondition (size2_ == m.size2_);
            check<bad_size>::precondition (lower_ == m.lower_);
            check<bad_size>::precondition (upper_ == m.upper_);
            std::swap (size1_, m.size1_);
            std::swap (size2_, m.size2_);
            std::swap (lower_, m.lower_);
            std::swap (upper_, m.upper_);
            data_.swap (m.data_);
        }
#ifndef USE_GCC
        NUMERICS_INLINE
	    friend void swap (banded_matrix &m1, banded_matrix &m2) {
            m1.swap (m2);
        }
#endif

        // Element insertion
        NUMERICS_INLINE
        void clear () {
            data_.fill (0);
        }
        NUMERICS_INLINE
        void insert (size_type i, size_type j, const_reference_type t) {
            check<bad_index>::precondition (i < size1_);
            check<bad_index>::precondition (j < size2_);
#ifndef NUMERICS_USE_ET
            if (t == value_type ()) 
                return;
#endif
            size_type k = std::min (i, j);
            size_type l = lower_ + j - i;
            data_.insert (data_.begin () + functor_type::element (k, std::min (size1_, size2_), 
                                                                  l, lower_ + 1 + upper_), t);
        }

        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;

        // Element lookup
        NUMERICS_INLINE
        const_iterator1 find1 (size_type i, size_type j) const {
            if (i < size1_ && j < size2_) {
                size_type lower_i = std::max (difference_type (j - lower_), difference_type (0));
                i = std::max (i, lower_i);
                size_type upper_i = std::min (j + 1 + upper_, size1_);
                i = std::min (i, upper_i);
            }
            return const_iterator1 (*this, i, j);
        }
        NUMERICS_INLINE
        iterator1 find1 (size_type i, size_type j) {
            if (i < size1_ && j < size2_) {
                size_type lower_i = std::max (difference_type (j - lower_), difference_type (0));
                i = std::max (i, lower_i);
                size_type upper_i = std::min (j + 1 + upper_, size1_);
                i = std::min (i, upper_i);
            }
            return iterator1 (*this, i, j);
        }
        NUMERICS_INLINE
        const_iterator2 find2 (size_type i, size_type j) const {
            if (i < size1_ && j < size2_) {
                size_type lower_j = std::max (difference_type (i - lower_), difference_type (0));
                j = std::max (j, lower_j);
                size_type upper_j = std::min (i + 1 + upper_, size2_);
                j = std::min (j, upper_j);
            }
            return const_iterator2 (*this, i, j);
        }
        NUMERICS_INLINE
        iterator2 find2 (size_type i, size_type j) {
            if (i < size1_ && j < size2_) {
                size_type lower_j = std::max (difference_type (i - lower_), difference_type (0));
                j = std::max (j, lower_j);
                size_type upper_j = std::min (i + 1 + upper_, size2_);
                j = std::min (j, upper_j);
            }
            return iterator2 (*this, i, j);
        }

        // Iterators simply are indices.

        class const_iterator1:
            public container_const_reference<banded_matrix>,
            public random_access_iterator_base<const_iterator1, value_type> {
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
#ifdef USE_GCC
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::value_type value_type;
#endif

            // Construction and destruction
            NUMERICS_INLINE
            const_iterator1 ():
                container_const_reference<banded_matrix> (), it1_ (), it2_ () {}
            NUMERICS_INLINE
            const_iterator1 (const banded_matrix &m, size_type it1, size_type it2):
                container_const_reference<banded_matrix> (m), it1_ (it1), it2_ (it2) {}
            NUMERICS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<banded_matrix> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            NUMERICS_INLINE
            const_iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            NUMERICS_INLINE
            difference_type operator - (const const_iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            NUMERICS_INLINE
            value_type operator * () const {
                return (*this) () (it1_, it2_); 
            }

            NUMERICS_INLINE
            const_iterator2 begin () const {
                return (*this) ().find2 (it1_, 0);
            }
            NUMERICS_INLINE
            const_iterator2 end () const {
                return (*this) ().find2 (it1_, (*this) ().size2 ());
            }

            // Indices
            NUMERICS_INLINE
            size_type index1 () const {
                return it1_;
            }
            NUMERICS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Comparison
            NUMERICS_INLINE
            bool operator == (const const_iterator1 &it) const {
                check<external_logic>::precondition (&(*this) () == &it ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;
        };

        NUMERICS_INLINE
        const_iterator1 begin1 () const {
            return find1 (0, 0);
        }
        NUMERICS_INLINE
        const_iterator1 end1 () const {
            return find1 (size1_, 0);
        }

        class iterator1:
            public container_reference<banded_matrix>,
            public random_access_iterator_base<iterator1, value_type> {
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
#ifdef USE_GCC
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::value_type value_type;
#endif

            // Construction and destruction
            NUMERICS_INLINE
            iterator1 ():
                container_reference<banded_matrix> (), it1_ (), it2_ () {}
            NUMERICS_INLINE
            iterator1 (banded_matrix &m, size_type it1, size_type it2):
                container_reference<banded_matrix> (m), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            NUMERICS_INLINE
            iterator1 &operator ++ () {
                ++ it1_;
                return *this;
            }
            NUMERICS_INLINE
            iterator1 &operator -- () {
                -- it1_;
                return *this;
            }
            NUMERICS_INLINE
            iterator1 &operator += (difference_type n) {
                it1_ += n;
                return *this;
            }
            NUMERICS_INLINE
            iterator1 &operator -= (difference_type n) {
                it1_ -= n;
                return *this;
            }
            NUMERICS_INLINE
            difference_type operator - (const iterator1 &it) const {
                return it1_ - it.it1_;
            }

            // Dereference
            NUMERICS_INLINE
            reference_type operator * () {
                return (*this) () (it1_, it2_); 
            }

            NUMERICS_INLINE
            iterator2 begin () const {
                return (*this) ().find2 (it1_, 0);
            }
            NUMERICS_INLINE
            iterator2 end () const {
                return (*this) ().find2 (it1_, (*this) ().size2 ());
            }

            // Indices
            NUMERICS_INLINE
            size_type index1 () const {
                return it1_;
            }
            NUMERICS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Comparison
            NUMERICS_INLINE
            bool operator == (const iterator1 &it) const {
                check<external_logic>::precondition (&(*this) () == &it ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;

            friend class const_iterator1;
        };

        NUMERICS_INLINE
        iterator1 begin1 () {
            return find1 (0, 0);
        }
        NUMERICS_INLINE
        iterator1 end1 () {
            return find1 (size1_, 0);
        }

        class const_iterator2:
            public container_const_reference<banded_matrix>,
            public random_access_iterator_base<const_iterator2, value_type> {
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
#ifdef USE_GCC
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::value_type value_type;
#endif

            // Construction and destruction
            NUMERICS_INLINE
            const_iterator2 ():
                container_const_reference<banded_matrix> (), it1_ (), it2_ () {}
            NUMERICS_INLINE
            const_iterator2 (const banded_matrix &m, size_type it1, size_type it2):
                container_const_reference<banded_matrix> (m), it1_ (it1), it2_ (it2) {}
            NUMERICS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<banded_matrix> (it ()), it1_ (it.it1_), it2_ (it.it2_) {}

            // Arithmetic
            NUMERICS_INLINE
            const_iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            NUMERICS_INLINE
            const_iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            NUMERICS_INLINE
            difference_type operator - (const const_iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            NUMERICS_INLINE
            value_type operator * () const {
                return (*this) () (it1_, it2_); 
            }

            NUMERICS_INLINE
            const_iterator1 begin () const {
                return (*this) ().find1 (0, it2_);
            }
            NUMERICS_INLINE
            const_iterator1 end () const {
                return (*this) ().find1 ((*this) ().size1 (), it2_);
            }

            // Indices
            NUMERICS_INLINE
            size_type index1 () const {
                return it1_;
            }
            NUMERICS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Comparison
            NUMERICS_INLINE
            bool operator == (const const_iterator2 &it) const {
                check<external_logic>::precondition (&(*this) () == &it ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;
        };

        NUMERICS_INLINE
        const_iterator2 begin2 () const {
            return find2 (0, 0);
        }
        NUMERICS_INLINE
        const_iterator2 end2 () const {
            return find2 (0, size2_);
        }

        class iterator2:
            public container_reference<banded_matrix>,
            public random_access_iterator_base<iterator2, value_type> {
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
#ifdef USE_GCC
            typedef typename banded_matrix::difference_type difference_type;
            typedef typename banded_matrix::value_type value_type;
#endif

            // Construction and destruction
            NUMERICS_INLINE
            iterator2 ():
                container_reference<banded_matrix> (), it1_ (), it2_ () {}
            NUMERICS_INLINE
            iterator2 (banded_matrix &m, size_type it1, size_type it2):
                container_reference<banded_matrix> (m), it1_ (it1), it2_ (it2) {}

            // Arithmetic
            NUMERICS_INLINE
            iterator2 &operator ++ () {
                ++ it2_;
                return *this;
            }
            NUMERICS_INLINE
            iterator2 &operator -- () {
                -- it2_;
                return *this;
            }
            NUMERICS_INLINE
            iterator2 &operator += (difference_type n) {
                it2_ += n;
                return *this;
            }
            NUMERICS_INLINE
            iterator2 &operator -= (difference_type n) {
                it2_ -= n;
                return *this;
            }
            NUMERICS_INLINE
            difference_type operator - (const iterator2 &it) const {
                return it2_ - it.it2_;
            }

            // Dereference
            NUMERICS_INLINE
            reference_type operator * () {
                return (*this) () (it1_, it2_); 
            }

            NUMERICS_INLINE
            iterator1 begin () const {
                return (*this) ().find1 (0, it2_);
            }
            NUMERICS_INLINE
            iterator1 end () const {
                return (*this) ().find1 ((*this) ().size1 (), it2_);
            }

            // Indices
            NUMERICS_INLINE
            size_type index1 () const {
                return it1_;
            }
            NUMERICS_INLINE
            size_type index2 () const {
                return it2_;
            }

            // Comparison
            NUMERICS_INLINE
            bool operator == (const iterator2 &it) const {
                check<external_logic>::precondition (&(*this) () == &it ());
                return it1_ == it.it1_ && it2_ == it.it2_;
            }

        private:
            size_type it1_;
            size_type it2_;

            friend class const_iterator2;
        };

        NUMERICS_INLINE
        iterator2 begin2 () {
            return find2 (0, 0);
        }
        NUMERICS_INLINE
        iterator2 end2 () {
            return find2 (0, size2_);
        }

        // Reverse iterators

#ifndef USE_GCC

#ifndef USE_BCC
        typedef std::reverse_iterator<const_iterator1, value_type, const_reference_type> const_reverse_iterator1;
#else
        typedef std::reverse_iterator<const_iterator1> const_reverse_iterator1;
#endif

        NUMERICS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        NUMERICS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }

#ifndef USE_BCC
        typedef std::reverse_iterator<iterator1, value_type, reference_type> reverse_iterator1;
#else
        typedef std::reverse_iterator<iterator1> reverse_iterator1;
#endif

        NUMERICS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        NUMERICS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

#ifndef USE_BCC
        typedef std::reverse_iterator<const_iterator2, value_type, const_reference_type> const_reverse_iterator2;
#else
        typedef std::reverse_iterator<const_iterator2> const_reverse_iterator2;
#endif

        NUMERICS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        NUMERICS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }

#ifndef USE_BCC
        typedef std::reverse_iterator<iterator2, value_type, reference_type> reverse_iterator2;
#else
        typedef std::reverse_iterator<iterator2> reverse_iterator2;
#endif

        NUMERICS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        NUMERICS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

#endif

    private:
        size_type size1_;
        size_type size2_;
        size_type lower_;
        size_type upper_;
        array_type data_;
    };

}

#endif 


