// Boost.Geometry Index
//
// R-tree implementation
//
// Copyright (c) 2008 Federico J. Fernandez.
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_RTREE_HPP
#define BOOST_GEOMETRY_INDEX_RTREE_HPP

#include <algorithm>

#include <boost/tuple/tuple.hpp>
#include <boost/move/move.hpp>

#include <boost/geometry/geometry.hpp>

#include <boost/geometry/index/detail/assert.hpp>
#include <boost/geometry/index/detail/nonassignable.hpp>

#include <boost/geometry/index/translator/translator.hpp>
#include <boost/geometry/index/detail/rtree/options.hpp>

#include <boost/geometry/index/predicates.hpp>
#include <boost/geometry/index/distance_predicates.hpp>
#include <boost/geometry/index/detail/rtree/adaptors.hpp>

#include <boost/geometry/index/detail/rtree/node/node.hpp>

#include <boost/geometry/index/detail/algorithms/is_valid.hpp>

#include <boost/geometry/index/detail/rtree/visitors/insert.hpp>
#include <boost/geometry/index/detail/rtree/visitors/remove.hpp>
#include <boost/geometry/index/detail/rtree/visitors/copy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/destroy.hpp>
#include <boost/geometry/index/detail/rtree/visitors/spatial_query.hpp>
#include <boost/geometry/index/detail/rtree/visitors/nearest_query.hpp>
#include <boost/geometry/index/detail/rtree/visitors/count.hpp>

#include <boost/geometry/index/detail/rtree/linear/linear.hpp>
#include <boost/geometry/index/detail/rtree/quadratic/quadratic.hpp>
#include <boost/geometry/index/detail/rtree/rstar/rstar.hpp>
//#include <boost/geometry/extensions/index/detail/rtree/kmeans/kmeans.hpp>

#include <boost/geometry/index/inserter.hpp>

// TODO change the name to bounding_tree

/*!
\defgroup rtree_functions Functions related to the rtree
*/

namespace boost { namespace geometry { namespace index {

/*!
\brief The R-tree spatial index.

This is self-balancing spatial index capable to store various types of Values and balancing algorithms.

\par Parameters
The user must pass a type defining the Parameters which will
be used in rtree creation process. This type is used e.g. to specify balancing algorithm
with specific parameters like min and max number of elements in node.

\par
Predefined algorithms with compile-time parameters are:
\li <tt>boost::geometry::index::linear</tt>,
 \li <tt>boost::geometry::index::quadratic</tt>,
 \li <tt>boost::geometry::index::rstar</tt>.

\par
Predefined algorithms with run-time parameters are:
 \li \c boost::geometry::index::runtime::linear,
 \li \c boost::geometry::index::runtime::quadratic,
 \li \c boost::geometry::index::runtime::rstar.

\par Translator
The Translator translates from Value to Indexable each time r-tree requires it. Which means that this
operation is done for each Value access. Therefore the Translator should return the Indexable by
const reference instead of a value. Default translator can translate all types adapted to Point
or Box concepts (called Indexables). It also handles <tt>std::pair<Indexable, T></tt> and
<tt>boost::tuple<Indexable, ...></tt>. For example, if <tt>std::pair<Box, int></tt> is stored in the
container, the default translator translates from <tt>std::pair<Box, int> const&</tt> to <tt>Box const&</tt>.

\tparam Value       The type of objects stored in the container.
\tparam Parameters  Compile-time parameters.
\tparam Translator  The type of the translator which translates from Value to Indexable.
\tparam Allocator   The allocator used to allocate/deallocate memory, construct/destroy nodes and Values.
*/
template <
    typename Value,
    typename Parameters,
    typename Translator = translator::def<Value>,
    typename Allocator = std::allocator<Value>
>
class rtree
{
    BOOST_COPYABLE_AND_MOVABLE(rtree)

public:
    /*! \brief The type of Value stored in the container. */
    typedef Value value_type;
    /*! \brief R-tree parameters type. */
    typedef Parameters parameters_type;
    /*! \brief Value to Indexable Translator type. */
    typedef Translator translator_type;
    /*! \brief The type of allocator used by the container. */
    typedef Allocator allocator_type;
    /*! \brief Unsigned integral type used by the container. */
    typedef typename allocator_type::size_type size_type;

    /*! \brief The Indexable type to which Value is translated. */
    typedef typename translator::indexable_type<Translator>::type indexable_type;
    /*! \brief The Box type used by the R-tree. */
    typedef typename index::detail::default_box_type<indexable_type>::type envelope_type;

#if !defined(BOOST_GEOMETRY_INDEX_ENABLE_DEBUG_INTERFACE)
private:
#endif
    typedef envelope_type box_type;
    typedef typename detail::rtree::options_type<Parameters>::type options_type;
    typedef typename options_type::node_tag node_tag;
    typedef detail::rtree::allocators<allocator_type, value_type, typename options_type::parameters_type, box_type, node_tag> allocators_type;

    typedef typename detail::rtree::node<value_type, typename options_type::parameters_type, box_type, allocators_type, node_tag>::type node;
    typedef typename detail::rtree::internal_node<value_type, typename options_type::parameters_type, box_type, allocators_type, node_tag>::type internal_node;
    typedef typename detail::rtree::leaf<value_type, typename options_type::parameters_type, box_type, allocators_type, node_tag>::type leaf;

public:
    /*!
    \brief The constructor.

    \param parameters   The parameters object.
    \param translator   The translator object.

    \par Throws
    If allocator default constructor throws.
    */
    inline explicit rtree(parameters_type parameters = parameters_type(),
                          translator_type const& translator = translator_type())
        : m_translator(translator)                                          // SHOULDN'T THROW
        , m_parameters(parameters)
        , m_allocators()
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
    {
        geometry::assign_inverse(m_box);
    }

    /*!
    \brief The constructor.

    \param parameters   The parameters object.
    \param translator   The translator object.
    \param allocator    The allocator object.

    \par Throws
    If allocator copy constructor throws.
    */
    inline rtree(parameters_type parameters,
                 translator_type const& translator,
                 allocator_type allocator)
        : m_translator(translator)                                          // SHOULDN'T THROW
        , m_parameters(parameters)
        , m_allocators(allocator)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
    {
        geometry::assign_inverse(m_box);
    }

    /*!
    \brief The constructor.

    \param first        The beginning of the range of Values.
    \param last         The end of the range of Values.
    \param parameters   The parameters object.
    \param translator   The translator object.
    \param allocator    The allocator object.

    \par Throws
    \li If allocator copy constructor throws.
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When memory allocation for Node fails.
    */
    template<typename Iterator>
    inline rtree(Iterator first, Iterator last,
                 parameters_type parameters = parameters_type(),
                 translator_type const& translator = translator_type(),
                 allocator_type allocator = allocator_type())
        : m_translator(translator)                                          // SHOULDN'T THROW
        , m_parameters(parameters)
        , m_allocators(allocator)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
    {
        geometry::assign_inverse(m_box);

        try
        {
            this->insert(first, last);
        }
        catch(...)
        {
            this->raw_destroy(*this);
            throw;
        }
    }

    /*!
    \brief The constructor.

    \param rng          The range of Values.
    \param parameters   The parameters object.
    \param translator   The translator object.
    \param allocator    The allocator object.

    \par Throws
    \li If allocator copy constructor throws.
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When memory allocation for Node fails.
    */
    template<typename Range>
    inline explicit rtree(Range const& rng,
                          parameters_type parameters = parameters_type(),
                          translator_type const& translator = translator_type(),
                          allocator_type allocator = allocator_type())
        : m_translator(translator)                                          // SHOULDN'T THROW
        , m_parameters(parameters)
        , m_allocators(allocator)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
    {
        geometry::assign_inverse(m_box);

        try
        {
            this->insert(rng);
        }
        catch(...)
        {
            this->raw_destroy(*this);
            throw;
        }
    }

    /*!
    \brief The destructor.

    \par Throws
    Nothing.
    */
    inline ~rtree()
    {
        this->raw_destroy(*this);
    }

    /*!
    \brief  The copy constructor.

    It uses parameters, translator and allocator from the source tree.

    \param src          The rtree which content will be copied.

    \par Throws
    \li If allocator copy constructor throws.
    \li If Value copy constructor throws.
    \li If allocation throws.
    \li When memory allocation for Node fails.
    */
    inline rtree(rtree const& src)
        : m_translator(src.m_translator)                                          // SHOULDN'T THROW
        , m_parameters(src.m_parameters)
        , m_allocators(src.m_allocators)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
        , m_box(src.m_box)
    {
        //TODO use Boost.Container allocator_traits_type::select_on_container_copy_construction()
        this->raw_copy(src, *this, false);
    }

    /*!
    \brief The copy constructor.

    It uses Parameters and translator from the source tree.

    \param src          The rtree which content will be copied.
    \param allocator    The allocator which will be used.

    \par Throws
    \li If allocator copy constructor throws.
    \li If Value copy constructor throws.
    \li If allocation throws.
    \li When memory allocation for Node fails.
    */
    inline rtree(rtree const& src, allocator_type const& allocator)
        : m_translator(src.m_translator)                                          // SHOULDN'T THROW
        , m_parameters(src.m_parameters)
        , m_allocators(allocator)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
        , m_box(src.m_box)
    {
        this->raw_copy(src, *this, false);
    }

    /*!
    \brief The moving constructor.

    It uses parameters, translator and allocator from the source tree.

    \param src          The rtree which content will be moved.

    \par Throws
    Nothing.
    */
    inline rtree(BOOST_RV_REF(rtree) src)
// TODO - use boost::move()
        : m_translator(src.m_translator)                                    // SHOULDN'T THROW
        , m_parameters(src.m_parameters)
        , m_allocators(src.m_allocators)
        , m_values_count(src.m_values_count)
        , m_leafs_level(src.m_leafs_level)
        , m_root(src.m_root)
        , m_box(src.m_box)
    {
        src.m_values_count = 0;
        src.m_leafs_level = 0;
        src.m_root = 0;
    }

    /*!
    \brief The moving constructor.

    It uses parameters and translator from the source tree.

    \param src          The rtree which content will be moved.
    \param allocator    The allocator.

    \par Throws
    \li If allocator copy constructor throws.
    \li If Value copy constructor throws (only if allocators aren't equal).
    \li If allocation throws (only if allocators aren't equal).
    \li When memory allocation for Node fails (only if allocators aren't equal).
    */
    inline rtree(BOOST_RV_REF(rtree) src, allocator_type const& allocator)
// TODO - use boost::move()
        : m_translator(src.m_translator)                                    // SHOULDN'T THROW
        , m_parameters(src.m_parameters)
        , m_allocators(allocator)
        , m_values_count(0)
        , m_leafs_level(0)
        , m_root(0)
        , m_box(src.m_box)
    {
        if ( src.m_allocators.allocator == allocator )
        {
            boost::swap(m_values_count, src.m_values_count);
            boost::swap(m_leafs_level, src.m_leafs_level);
            boost::swap(m_root, src.m_root);
        }
        else
        {
            this->raw_copy(src, *this, false);
        }
    }

    /*!
    \brief The assignment operator.

    It uses parameters and translator from the source tree.

    \param src          The rtree which content will be copied.

    \par Throws
    \li If Value copy constructor throws.
    \li If allocation throws.
    \li When nodes allocation fails.
    */
    inline rtree & operator=(BOOST_COPY_ASSIGN_REF(rtree) src)
    {
        if ( this == &src )
            return *this;

        //TODO use Boost.Container allocator_traits_type::propagate_on_container_move_assignment

        // It uses m_allocators
        this->raw_copy(src, *this, true);

        m_box = src.m_box;

        return *this;
    }

    /*!
    \brief The moving assignment.

    It uses parameters and translator from the source tree.

    \param src          The rtree which content will be moved.

    \par Throws
    Only if allocators aren't equal.
    \li If Value copy constructor throws.
    \li If allocation throws.
    \li When nodes allocation fails.
    */
    inline rtree & operator=(BOOST_RV_REF(rtree) src)
    {
        if ( this == &src )
            return *this;

//TODO use Boost.Container allocator_traits_type::propagate_on_container_move_assignment

        if ( m_allocators.allocator == src.m_allocators.allocator )
        {
// TODO - use boost::move()
            m_translator = src.m_translator;                                          // SHOULDN'T THROW
            m_parameters = src.m_parameters;
            //m_allocators = src.m_allocators;

            m_values_count = src.m_values_count;
            m_leafs_level = src.m_leafs_level;
            m_root = src.m_root;

            src.m_values_count = 0;
            src.m_leafs_level = 0;
            src.m_root = 0;
        }
        else
        {
            // It uses m_allocators
            this->raw_copy(src, *this, true);
        }

        m_box = src.m_box;

        return *this;
    }

    /*!
    \brief Swaps contents of two rtrees.

    Parameters, translator and allocators are swapped as well.

    \param other    The rtree which content will be swapped with this rtree content.

    \par Throws
    If allocators swap throws.
    */
    void swap(rtree & other)
    {
        boost::swap(m_translator, other.m_translator);                               // SHOULDN'T THROW
        boost::swap(m_parameters, other.m_parameters);
        m_allocators.swap(other.m_allocators);

        boost::swap(m_values_count, other.m_values_count);
        boost::swap(m_leafs_level, other.m_leafs_level);
        boost::swap(m_root, other.m_root);
        boost::swap(m_box, other.m_box);
    }

    /*!
    \brief Insert a value to the index.

    \param value    The value which will be stored in the container.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    inline void insert(value_type const& value)
    {
        if ( !m_root )
            this->raw_create();

        this->raw_insert(value);
    }

    /*!
    \brief Insert a range of values to the index.

    \param first    The beginning of the range of values.
    \param last     The end of the range of values.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    template <typename Iterator>
    inline void insert(Iterator first, Iterator last)
    {
        if ( !m_root )
            this->raw_create();

        for ( ; first != last ; ++first )
            this->raw_insert(*first);
    }

    /*!
    \brief Insert a range of values to the index.

    \param rng      The range of values.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    template <typename Range>
    inline void insert(Range const& rng)
    {
        if ( !m_root )
            this->raw_create();

        typedef typename boost::range_const_iterator<Range>::type It;
        for ( It it = boost::const_begin(rng); it != boost::const_end(rng) ; ++it )
            this->raw_insert(*it);
    }

    /*!
    \brief Remove a value from the container.

    In contrast to the \c std::set or <tt>std::map erase()</tt> method
    this method removes only one value from the container.

    \param value    The value which will be removed from the container.

    \return         1 if the value was removed, 0 otherwise.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    inline size_type remove(value_type const& value)
    {
        return this->raw_remove(value);
    }

    /*!
    \brief Remove a range of values from the container.

    In contrast to the \c std::set or <tt>std::map erase()</tt> method
    it doesn't take iterators pointing to values stored in this container. It removes values equal
    to these passed as a range. Furthermore this method removes only one value for each one passed
    in the range, not all equal values.

    \param first    The beginning of the range of values.
    \param last     The end of the range of values.

    \return         The number of removed values.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    template <typename Iterator>
    inline size_type remove(Iterator first, Iterator last)
    {
        size_type result = 0;
        for ( ; first != last ; ++first )
            result += this->raw_remove(*first);
        return result;
    }

    /*!
    \brief Remove a range of values from the container.

    In contrast to the \c std::set or <tt>std::map erase()</tt> method
    it removes values equal to these passed as a range. Furthermore, this method removes only
    one value for each one passed in the range, not all equal values.

    \param rng      The range of values.

    \return         The number of removed values.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If allocation throws.
    \li When nodes allocation fails.

    \warning
    This operation is not thread safe. If it throws, the R-tree may be left in an inconsistent state,
    elements must not be inserted or removed, methods may return invalid data.
    */
    template <typename Range>
    inline size_type remove(Range const& rng)
    {
        size_type result = 0;
        typedef typename boost::range_const_iterator<Range>::type It;
        for ( It it = boost::const_begin(rng); it != boost::const_end(rng) ; ++it )
            result += this->raw_remove(*it);
        return result;
    }

    /*!
    \brief Finds values meeting passed predicates e.g. nearest to some Point and/or intersecting some Box.

    This query function performs spatial and k-nearest neighbor searches. It allows to pass a set of predicates.
    Values will be returned only if all predicates are met.

    <b>Spatial predicates</b>
    
    The simplest form of spatial predicate is a \c Geometry. In this case Values intersecting the \c Geometry are returned.
    More spatial predicates may be generated by one of the functions listed below:
    \li \c boost::geometry::index::covered_by(),
    \li \c boost::geometry::index::disjoint(),
    \li \c boost::geometry::index::intersects() - default,
    \li \c boost::geometry::index::overlaps(),
    \li \c boost::geometry::index::within(),

    It is possible to negate spatial predicates:
    \li <tt>! boost::geometry::index::covered_by()</tt>,
    \li <tt>! boost::geometry::index::disjoint()</tt>,
    \li <tt>! boost::geometry::index::intersects()</tt>,
    \li <tt>! boost::geometry::index::overlaps()</tt>,
    \li <tt>! boost::geometry::index::within()</tt>

    <b>Value predicate</b>
    
    This is a special kind of predicate which allows to pass a user-defined functor which checks
    if Value should be returned by the query. It's generated by:
    \li \c boost::geometry::index::value().

    <b>Nearest predicate</b>

    If the nearest predicate is passed a k-nearest neighbor search will be performed. It has two variants.
    Passing the first one will result in returning k number of values, the second one will result in returning
    only one, closest value. In both cases values will be returned to the output iterator. Only one nearest
    predicate may be passed to the query. It may be generated by:
    \li \c boost::geometry::index::nearest().
        
    <b>Connecting predicates</b>

    A set of predicates may be generated by:
    \li \c std::make_pair()
    \li \c boost::make_tuple()
    \li \c operator&&()

    \par Example
    \verbatim
    tree.query(box1, std::back_inserter(result));
    tree.query(std::make_pair(bgi::intersects(poly), !bgi::within(box)), std::back_inserter(result));
    tree.query(bgi::intersects(poly) && !bgi::within(box), std::back_inserter(result));
    tree.query(bgi::overlaps(box) && bgi::value(my_fun), std::back_inserter(result));
    tree.query(bgi::nearest(pt, 5) && bgi::intersects(box), std::back_inserter(result));
    \endverbatim

    \warning
    Only one \c nearest() perdicate may be passed to the query.

    \param predicates   Predicates.
    \param out_it       The output iterator, e.g. generated by std::back_inserter().

    \return             The number of values found.

    \par Throws
    If Value copy constructor or copy assignment throws.
    */
    template <typename Predicates, typename OutIter>
    size_type query(Predicates const& predicates, OutIter out_it) const
    {
        static const unsigned nearest_count = detail::predicates_count_nearest<Predicates>::value;
        static const bool is_nearest = 0 < nearest_count;
        BOOST_MPL_ASSERT_MSG((nearest_count <= 1), PASS_ONLY_ONE_NEAREST_PREDICATE, (Predicates));

        return query_dispatch(predicates, out_it, boost::mpl::bool_<is_nearest>());
    }

    /*!
    \brief Finds value meeting passed predicates e.g. nearest to some Point and intersecting some Box.

    This query function performs k-nearest neighbor searches. It allows to pass a set of predicates.
    The value will be returned only if all predicates are met. This query requires that one of the
    predicates must be one-value \c nearest() predicate.

    <b>Spatial predicates</b>
    
    The simplest form of spatial predicate is a \c Geometry. In this case Values intersecting the \c Geometry are returned.
    More spatial predicates may be generated by one of the functions listed below:
    \li \c boost::geometry::index::covered_by(),
    \li \c boost::geometry::index::disjoint(),
    \li \c boost::geometry::index::intersects() - default,
    \li \c boost::geometry::index::overlaps(),
    \li \c boost::geometry::index::within(),

    It is possible to negate spatial predicates:
    \li <tt>! boost::geometry::index::covered_by()</tt>,
    \li <tt>! boost::geometry::index::disjoint()</tt>,
    \li <tt>! boost::geometry::index::intersects()</tt>,
    \li <tt>! boost::geometry::index::overlaps()</tt>,
    \li <tt>! boost::geometry::index::within()</tt>

    <b>Value predicate</b>
    
    This is a special kind of predicate which allows to pass a user-defined functor which checks
    if Value should be returned by the query. It's generated by:
    \li \c boost::geometry::index::value().

    <b>Nearest predicate</b>

    This query requires that one of the predicates must be one-value \c nearest() predicate.
    It may be generated by \c nearest() taking only one parameter - distance predicates.
    \li \c boost::geometry::index::nearest().
        
    <b>Connecting predicates</b>

    A set of predicates may be generated by:
    \li \c std::make_pair()
    \li \c boost::make_tuple()
    \li \c operator&&()

    \par Example
    \verbatim
    tree.query(std::make_pair(bgi::nearest(pt), bgi::within(box)), value);
    tree.query(bgi::nearest(pt) && bgi::intersects(poly), value);
    \endverbatim

    \warning
    This query requires that one of the predicates must be one-value \c nearest() predicate.

    \param predicates   Predicates.
    \param value        The reference to value which will hold the result of the query.

    \return             The number of values found (1 if value was found, 0 otherwise).

    \par Throws
    If Value copy constructor or copy assignment throws.
    */
    template <typename Predicates>
    size_type query(Predicates const& predicates, value_type & value) const
    {
        static const unsigned nearest_count = detail::predicates_count_nearest<Predicates>::value;
        BOOST_MPL_ASSERT_MSG((nearest_count == 1), PASS_ONE_VALUE_NEAREST_PREDICATE_TO_GET_VALUE_AS_RESULT, (Predicates));

        return query_dispatch(predicates, value, boost::mpl::bool_<true>());
    }

private:

    template <typename Predicates, typename OutIter>
    size_type query_dispatch(Predicates const& predicates, OutIter out_it, boost::mpl::bool_<false> const& /*is_nearest*/) const
    {
        return spatial_query(predicates, out_it);
    }

    template <typename Predicates, typename OutIter>
    size_type query_dispatch(Predicates const& predicates, OutIter out_it, boost::mpl::bool_<true> const& /*is_nearest*/) const
    {
        static const unsigned nearest_index = detail::predicates_find_nearest<Predicates>::value;
        static const bool is_one = detail::predicates_element<nearest_index, Predicates>::type::is_one;

        return query_dispatch_nearest(predicates, out_it, boost::mpl::bool_<is_one>());
    }

    template <typename Predicates>
    size_type query_dispatch(Predicates const& predicates, value_type & v, boost::mpl::bool_<true> const& /*is_nearest*/) const
    {
        static const unsigned nearest_index = detail::predicates_find_nearest<Predicates>::value;
        static const bool is_one = detail::predicates_element<nearest_index, Predicates>::type::is_one;
        BOOST_MPL_ASSERT_MSG((is_one == 1), PASS_ONE_VALUE_NEAREST_PREDICATE_TO_GET_VALUE_AS_RESULT, (Predicates));

        typedef detail::predicates_element<nearest_index, Predicates> element_access;
        typename element_access::type const& nearest_pred = element_access::get(predicates);

        return this->raw_nearest_one(nearest_pred.distance_predicates, predicates, v);
    }

    template <typename Predicates, typename OutIter>
    size_type query_dispatch_nearest(Predicates const& predicates, OutIter out_it, boost::mpl::bool_<false> const& /*is_one*/) const
    {
        static const unsigned nearest_index = detail::predicates_find_nearest<Predicates>::value;
        typedef detail::predicates_element<nearest_index, Predicates> element_access;
        typename element_access::type const& nearest_pred = element_access::get(predicates);
        return this->raw_nearest_k(nearest_pred.distance_predicates, nearest_pred.count, predicates, out_it);
    }

    template <typename Predicates, typename OutIter>
    size_type query_dispatch_nearest(Predicates const& predicates, OutIter out_it, boost::mpl::bool_<true> const& /*is_one*/) const
    {
        static const unsigned nearest_index = detail::predicates_find_nearest<Predicates>::value;
        typedef detail::predicates_element<nearest_index, Predicates> element_access;
        typename element_access::type const& nearest_pred = element_access::get(predicates);
        return this->raw_nearest_k(nearest_pred.distance_predicates, 1, predicates, out_it);
    }

public:

    /*!
    \brief Finds values meeting spatial predicates, e.g. intersecting some Box.

    <b>Spatial predicates</b> may be a \c Geometry. In this case Values intersecting the \c Geometry are returned.

    It may be generated by one of the functions listed below:
    \li \c boost::geometry::index::covered_by(),
    \li \c boost::geometry::index::disjoint(),
    \li \c boost::geometry::index::intersects() - default,
    \li \c boost::geometry::index::overlaps(),
    \li \c boost::geometry::index::within(),
    \li <tt>! boost::geometry::index::covered_by()</tt>,
    \li <tt>! boost::geometry::index::disjoint()</tt>,
    \li <tt>! boost::geometry::index::intersects()</tt>,
    \li <tt>! boost::geometry::index::overlaps()</tt>,
    \li <tt>! boost::geometry::index::within()</tt>
    \li \c boost::geometry::index::value().

    Those predicates may be passed together in
    \c std::pair or \c boost::tuple.

    \param pred     The spatial predicates or a Geometry.
    \param out_it   The output iterator of the result range. E.g. an iterator generated by
                    std::back_inserter(container)

    \return         The number of values found.

    \par Throws
    \li If Value copy constructor or copy assignment throws.
    \li If OutIter dereference or increment throws.
    */
    template <typename Predicates, typename OutIter> inline
    size_type spatial_query(Predicates const& pred, OutIter out_it) const
    {
        if ( !m_root )
            return 0;

        detail::rtree::visitors::spatial_query<value_type, options_type, translator_type, box_type, allocators_type, Predicates, OutIter>
            find_v(m_translator, pred, out_it);

        detail::rtree::apply_visitor(find_v, *m_root);

        return find_v.found_count;
    }

    /*!
    \brief Finds one value meeting distances predicates, e.g. nearest to some Point.

    <b>Distances predicates</b> may be a \c Point. In this the case the Value closest to \c Point is returned.

    It is possible to define how distance to Value is calculated. This is done by passing PointRelation.
    It can be generated by following functions:
    \li \c boost::geometry::index::to_nearest() - default,
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    It is possible to define define distances bounds, for example that some distance must be between
    min_distance and max_distance. This is done by passing DistancesPredicates which can be generated
    by following functions:
    \li \c boost::geometry::index::unbounded() - default,
    \li \c boost::geometry::index::min_bounded(),
    \li \c boost::geometry::index::max_bounded(),
    \li \c boost::geometry::index::bounded().

    MinRelation and MaxRelation describes bounds and can be generated by following functions:
    \li \c boost::geometry::index::to_nearest(),
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    \param dpred    The distances predicates or a Point.

    \param v        The reference to the object which will contain the result.

    \return         The number of values found.

    \par Throws
    If Value copy constructor or copy assignment throws.
    */
    template <typename DistancesPredicates>
    inline size_type nearest_query(DistancesPredicates const& dpred, value_type & v) const
    {
        return raw_nearest_one(dpred, detail::empty(), v);
    }

    /*!
    \brief Finds one value meeting distances predicates and spatial predicates,
    e.g. nearest to some Point and intersecting some Box.

    <b>Distances predicates</b> may be a \c Point. In this the case the Value closest to \c Point is returned.

    It is possible to define how distance to Value is calculated. This is done by passing PointRelation.
    It can be generated by following functions:
    \li \c boost::geometry::index::to_nearest() - default,
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    It is possible to define define distances bounds, for example that some distance must be between
    min_distance and max_distance. This is done by passing DistancesPredicates which can be generated
    by following functions:
    \li \c boost::geometry::index::unbounded() - default,
    \li \c boost::geometry::index::min_bounded(),
    \li \c boost::geometry::index::max_bounded(),
    \li \c boost::geometry::index::bounded().

    MinRelation and MaxRelation describes bounds and can be generated by following functions:
    \li \c boost::geometry::index::to_nearest(),
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    <b>Spatial predicates</b> may be a \c Geometry. In this case Values intersecting the \c Geometry are returned.

    It may be generated by one of the functions listed below:
    \li \c boost::geometry::index::covered_by(),
    \li \c boost::geometry::index::disjoint(),
    \li \c boost::geometry::index::intersects() - default,
    \li \c boost::geometry::index::overlaps(),
    \li \c boost::geometry::index::within(),
    \li <tt>! boost::geometry::index::covered_by()</tt>,
    \li <tt>! boost::geometry::index::disjoint()</tt>,
    \li <tt>! boost::geometry::index::intersects()</tt>,
    \li <tt>! boost::geometry::index::overlaps()</tt>,
    \li <tt>! boost::geometry::index::within()</tt>
    \li \c boost::geometry::index::value().

    Those predicates may be passed together in
    \c std::pair or \c boost::tuple.

    \param dpred    The distances predicates or a Point.
    \param pred     The spatial predicates or a Geometry
    \param v        The reference to the object which will contain the result.

    \return         The number of values found.

    \par Throws
    If Value copy constructor or copy assignment throws.
    */
    template <typename DistancesPredicates, typename Predicates>
    inline size_type nearest_query(DistancesPredicates const& dpred, Predicates const& pred, value_type & v) const
    {
        return raw_nearest_one(dpred, pred, v);
    }

    /*!
    \brief Finds k values meeting distances predicates, e.g. k nearest values to some Point.

    <b>Distances predicates</b> may be a \c Point. In this the case the Value closest to \c Point is returned.

    It is possible to define how distance to Value is calculated. This is done by passing PointRelation.
    It can be generated by following functions:
    \li \c boost::geometry::index::to_nearest() - default,
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    It is possible to define define distances bounds, for example that some distance must be between
    min_distance and max_distance. This is done by passing DistancesPredicates which can be generated
    by following functions:
    \li \c boost::geometry::index::unbounded() - default,
    \li \c boost::geometry::index::min_bounded(),
    \li \c boost::geometry::index::max_bounded(),
    \li \c boost::geometry::index::bounded().

    MinRelation and MaxRelation describes bounds and can be generated by following functions:
    \li \c boost::geometry::index::to_nearest(),
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    \param dpred    The distances predicates or a Point.
    \param k        The max number of values.
    \param out_it   The output iterator of the result range. E.g. a back_insert_iterator.

    \return         The number of values found.

    \par Throws
    If Value copy constructor or copy assignment throws. If OutIter dereference or increment throws.
    */
    template <typename DistancesPredicates, typename OutIter>
    inline size_type nearest_query(DistancesPredicates const& dpred, size_type k, OutIter out_it) const
    {
        return raw_nearest_k(dpred, k, detail::empty(), out_it);
    }

    /*!
    \brief Finds k values meeting distances predicates and spatial predicates,
    e.g. k nearest values to some Point and intersecting some Box.

    <b>Distances predicates</b> may be a \c Point. In this the case the Value closest to \c Point is returned.

    It is possible to define how distance to Value is calculated. This is done by passing PointRelation.
    It can be generated by following functions:
    \li \c boost::geometry::index::to_nearest() - default,
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    It is possible to define define distances bounds, for example that some distance must be between
    min_distance and max_distance. This is done by passing DistancesPredicates which can be generated
    by following functions:
    \li \c boost::geometry::index::unbounded() - default,
    \li \c boost::geometry::index::min_bounded(),
    \li \c boost::geometry::index::max_bounded(),
    \li \c boost::geometry::index::bounded().

    MinRelation and MaxRelation describes bounds and can be generated by following functions:
    \li \c boost::geometry::index::to_nearest(),
    \li \c boost::geometry::index::to_centroid(),
    \li \c boost::geometry::index::to_furthest().

    <b>Spatial predicates</b> may be a \c Geometry. In this case Values intersecting the \c Geometry are returned.

    It may be generated by one of the functions listed below:
    \li \c boost::geometry::index::covered_by(),
    \li \c boost::geometry::index::disjoint(),
    \li \c boost::geometry::index::intersects() - default,
    \li \c boost::geometry::index::overlaps(),
    \li \c boost::geometry::index::within(),
    \li <tt>! boost::geometry::index::covered_by()</tt>,
    \li <tt>! boost::geometry::index::disjoint()</tt>,
    \li <tt>! boost::geometry::index::intersects()</tt>,
    \li <tt>! boost::geometry::index::overlaps()</tt>,
    \li <tt>! boost::geometry::index::within()</tt>
    \li \c boost::geometry::index::value().

    Those predicates may be passed together in
    \c std::pair or \c boost::tuple.

    \param dpred    The distances predicates or a Point
    \param k        The max number of values.
    \param pred     The spatial predicates or a Geometry.
    \param out_it   The output iterator of the result range. E.g. a back_insert_iterator.

    \return         The number of values found.

    \par Throws
    If Value copy constructor or copy assignment throws. If OutIter dereference or increment throws.
    */
    template <typename DistancesPredicates, typename Predicates, typename OutIter>
    inline size_type nearest_query(DistancesPredicates const& dpred, size_type k, Predicates const& pred, OutIter out_it) const
    {
        return raw_nearest_k(dpred, k, pred, out_it);
    }

    /*!
    \brief Returns the number of stored values.

    \return         The number of stored values.

    \par Throws
    Nothing.
    */
    inline size_type size() const
    {
        return m_values_count;
    }

    /*!
    \brief Query if the container is empty.

    \return         true if the container is empty.

    \par Throws
    Nothing.
    */
    inline bool empty() const
    {
        return 0 == m_values_count;
    }

    /*!
    \brief Removes all values stored in the container.

    \par Throws
    Nothing.
    */
    inline void clear()
    {
        this->raw_destroy(*this);
        geometry::assign_inverse(m_box);
    }

    /*!
    \brief Returns the box able to contain all values stored in the container.

    Returns the box able to contain all values stored in the container.
    If the container is empty the result of \c geometry::assign_inverse() is returned.

    \return     The box able to contain all values stored in the container or an invalid box if
                there are no values in the container.

    \par Throws
    Nothing.
    */
    inline envelope_type const& envelope() const
    {
        return m_box;
    }

    /*!
    \brief Count Values or Indexables stored in the container.
    
    For indexable_type it returns the number of values which indexables equals the parameter.
    For value_type it returns the number of values which equals the parameter.

    \param vori The value or indexable which will be counted.

    \return     The number of values found.

    \par Throws
    Nothing.
    */
    template <typename ValueOrIndexable>
    size_type count(ValueOrIndexable const& vori) const
    {
        if ( !m_root )
            return 0;

        detail::rtree::visitors::count<ValueOrIndexable, value_type, options_type, translator_type, box_type, allocators_type>
            count_v(vori, m_translator);

        detail::rtree::apply_visitor(count_v, *m_root);

        return count_v.found_count;
    }

    /*!
    \brief Returns parameters.

    \return     The parameters object.

    \par Throws
    Nothing.
    */
    inline parameters_type const& parameters() const
    {
        return m_parameters;
    }

    /*!
    \brief Returns the translator object.

    \return     The translator object.

    \par Throws
    Nothing.
    */
    inline translator_type const& translator() const
    {
        return m_translator;
    }

    /*!
    \brief Returns allocator used by the rtree.

    \return     The allocator.

    \par Throws
    If allocator copy constructor throws.
    */
    allocator_type get_allocator() const
    {
        return m_allocators.allocator;
    }

#if !defined(BOOST_GEOMETRY_INDEX_ENABLE_DEBUG_INTERFACE)
private:
#endif
    /*!
    \brief Apply a visitor to the nodes structure in order to perform some operator.

    This function is not a part of the 'official' interface. However it makes
    possible e.g. to pass a visitor drawing the tree structure.

    \param visitor  The visitor object.

    \par Throws
    If Visitor::operator() throws.
    */
    template <typename Visitor>
    inline void apply_visitor(Visitor & visitor) const
    {
        if ( m_root )
            detail::rtree::apply_visitor(visitor, *m_root);
    }

    /*!
    \brief Returns the number of stored objects. Same as size().

    This function is not a part of the 'official' interface.

    \return     The number of stored objects.

    \par Throws
    Nothing.
    */
    inline size_type values_count() const
    {
        return m_values_count;
    }

    /*!
    \brief Returns the depth of the R-tree.

    This function is not a part of the 'official' interface.

    \return     The depth of the R-tree.

    \par Throws
    Nothing.
    */
    inline size_type depth() const
    {
        return m_leafs_level;
    }

private:
    /*!
    \pre Root node must exist - m_root != 0.

    \brief Insert a value to the index.

    \param value    The value which will be stored in the container.

    \par Exception-safety
    basic
    */
    inline void raw_insert(value_type const& value)
    {
        BOOST_GEOMETRY_INDEX_ASSERT(m_root, "The root must exist");
        BOOST_GEOMETRY_INDEX_ASSERT(detail::is_valid(m_translator(value)), "Indexable is invalid");

        geometry::expand(m_box, m_translator(value));

        detail::rtree::visitors::insert<
            value_type,
            value_type, options_type, translator_type, box_type, allocators_type,
            typename options_type::insert_tag
        > insert_v(m_root, m_leafs_level, value, m_parameters, m_translator, m_allocators);

        detail::rtree::apply_visitor(insert_v, *m_root);

// TODO
// Think about this: If exception is thrown, may the root be removed?
// Or it is just cleared?

// TODO
// If exception is thrown, m_values_count may be invalid
        ++m_values_count;
    }

    /*!
    \brief Remove the value from the container.

    \param value    The value which will be removed from the container.

    \par Exception-safety
    basic
    */
    inline size_type raw_remove(value_type const& value)
    {
        // TODO: awulkiew - assert for correct value (indexable) ?
        BOOST_GEOMETRY_INDEX_ASSERT(m_root, "The root must exist");

        detail::rtree::visitors::remove<
            value_type, options_type, translator_type, box_type, allocators_type
        > remove_v(m_root, m_leafs_level, m_box, value, m_parameters, m_translator, m_allocators);

        detail::rtree::apply_visitor(remove_v, *m_root);

        // If exception is thrown, m_values_count may be invalid

        if ( remove_v.is_value_removed() )
        {
            BOOST_GEOMETRY_INDEX_ASSERT(0 < m_values_count, "unexpected state");

            --m_values_count;

            return 1;
        }

        return 0;
    }

    /*!
    \brief Create an empty R-tree i.e. new empty root node and clear other attributes.

    \par Exception-safety
    strong
    */
    inline void raw_create()
    {
        BOOST_GEOMETRY_INDEX_ASSERT(0 == m_root, "the tree is already created");

        m_root = detail::rtree::create_node<allocators_type, leaf>::apply(m_allocators);                            // MAY THROW (N: alloc)
        m_values_count = 0;
        m_leafs_level = 0;
    }

    /*!
    \brief Destroy the R-tree i.e. all nodes and clear attributes.

    \param t    The container which is going to be destroyed.

    \par Exception-safety
    nothrow
    */
    inline void raw_destroy(rtree & t)
    {
        if ( t.m_root )
        {
            detail::rtree::visitors::destroy<value_type, options_type, translator_type, box_type, allocators_type> del_v(t.m_root, t.m_allocators);
            detail::rtree::apply_visitor(del_v, *t.m_root);

            t.m_root = 0;
        }
        t.m_values_count = 0;
        t.m_leafs_level = 0;
    }

    /*!
    \brief Copy the R-tree i.e. whole nodes structure, values and other attributes.
    It uses destination's allocators to create the new structure.

    \param src    The source R-tree.
    \param dst    The destination R-tree.

    \par Exception-safety
    strong
    */
    inline void raw_copy(rtree const& src, rtree & dst, bool copy_all_internals) const
    {
        detail::rtree::visitors::copy<value_type, options_type, translator_type, box_type, allocators_type> copy_v(dst.m_allocators);

        if ( src.m_root )
            detail::rtree::apply_visitor(copy_v, *src.m_root);                              // MAY THROW (V, E: alloc, copy, N: alloc)

        if ( copy_all_internals )
        {
            dst.m_translator = src.m_translator;                                            // SHOULDN'T THROW

            dst.m_parameters = src.m_parameters;
            //dst.m_allocators = dst.m_allocators;
        }

        if ( dst.m_root )
        {
            detail::rtree::visitors::destroy<value_type, options_type, translator_type, box_type, allocators_type> del_v(dst.m_root, dst.m_allocators);
            detail::rtree::apply_visitor(del_v, *dst.m_root);
            dst.m_root = 0;
        }

        dst.m_root = copy_v.result;
        dst.m_values_count = src.m_values_count;
        dst.m_leafs_level = src.m_leafs_level;
    }

    /*!
    \brief Find one value meeting distances and spatial predicates.

    \par Exception-safety
    strong
    */
    template <typename DistancesPredicates, typename Predicates>
    inline size_type raw_nearest_one(DistancesPredicates const& dpred, Predicates const& pred, value_type & v) const
    {
        if ( !m_root )
            return 0;

        typedef typename detail::point_relation<DistancesPredicates>::type point_relation;
        typedef typename detail::relation<point_relation>::value_type point_type;

        typedef detail::rtree::visitors::nearest_query_result_one<
            value_type,
            translator_type,
            point_type
        > result_type;

        result_type result(v);

        detail::rtree::visitors::nearest_query<
            value_type,
            options_type,
            translator_type,
            box_type,
            allocators_type,
            DistancesPredicates,
            Predicates,
            result_type
        > nearest_v(m_parameters, m_translator, dpred, pred, result);

        detail::rtree::apply_visitor(nearest_v, *m_root);

        return result.finish();
    }

    /*!
    \brief Find k values meeting distances and spatial predicates.

    \par Exception-safety
    strong
    */
    template <typename DistancesPredicates, typename Predicates, typename OutIter>
    inline size_type raw_nearest_k(DistancesPredicates const& dpred, size_t k, Predicates const& pred, OutIter out_it) const
    {
        if ( !m_root )
            return 0;

        typedef typename detail::point_relation<DistancesPredicates>::type point_relation;
        typedef typename detail::relation<point_relation>::value_type point_type;

        typedef detail::rtree::visitors::nearest_query_result_k<
            value_type,
            translator_type,
            point_type,
            OutIter
        > result_type;

        result_type result(k, out_it);

        detail::rtree::visitors::nearest_query<
            value_type,
            options_type,
            translator_type,
            box_type,
            allocators_type,
            DistancesPredicates,
            Predicates,
            result_type
        > nearest_v(m_parameters, m_translator, dpred, pred, result);

        detail::rtree::apply_visitor(nearest_v, *m_root);

        return result.finish();
    }

    translator_type m_translator;
    Parameters m_parameters;
    allocators_type m_allocators;

    size_type m_values_count;
    size_type m_leafs_level;
    node * m_root;

    box_type m_box;
};

/*!
\brief Insert a value to the index.

It calls <tt>rtree::insert(value_type const&)</tt>.

\ingroup rtree_functions

\param tree The spatial index.
\param v    The value which will be stored in the index.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline void insert(rtree<Value, Options, Translator, Allocator> & tree, Value const& v)
{
    tree.insert(v);
}

/*!
\brief Insert a range of values to the index.

It calls <tt>rtree::insert(Iterator, Iterator)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param first    The beginning of the range of values.
\param last     The end of the range of values.
*/
template<typename Value, typename Options, typename Translator, typename Allocator, typename Iterator>
inline void insert(rtree<Value, Options, Translator, Allocator> & tree, Iterator first, Iterator last)
{
    tree.insert(first, last);
}

/*!
\brief Insert a range of values to the index.

It calls <tt>rtree::insert(Range const&)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param rng      The range of values.
*/
template<typename Value, typename Options, typename Translator, typename Allocator, typename Range>
inline void insert(rtree<Value, Options, Translator, Allocator> & tree, Range const& rng)
{
    tree.insert(rng);
}

/*!
\brief Remove a value from the container.

Remove a value from the container. In contrast to the \c std::set or <tt>std::map erase()</tt> method
this function removes only one value from the container.

It calls <tt>rtree::remove(value_type const&)</tt>.

\ingroup rtree_functions

\param tree The spatial index.
\param v    The value which will be removed from the index.

\return     1 if value was removed, 0 otherwise.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline typename rtree<Value, Options, Translator, Allocator>::size_type
remove(rtree<Value, Options, Translator, Allocator> & tree, Value const& v)
{
    return tree.remove(v);
}

/*!
\brief Remove a range of values from the container.

Remove a range of values from the container. In contrast to the \c std::set or <tt>std::map erase()</tt> method
it doesn't take iterators pointing to values stored in this container. It removes values equal
to these passed as a range. Furthermore this function removes only one value for each one passed
in the range, not all equal values.

It calls <tt>rtree::remove(Iterator, Iterator)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param first    The beginning of the range of values.
\param last     The end of the range of values.

\return         The number of removed values.
*/
template<typename Value, typename Options, typename Translator, typename Allocator, typename Iterator>
inline typename rtree<Value, Options, Translator, Allocator>::size_type
remove(rtree<Value, Options, Translator, Allocator> & tree, Iterator first, Iterator last)
{
    return tree.remove(first, last);
}

/*!
\brief Remove a range of values from the container.

Remove a range of values from the container. In contrast to the \c std::set or <tt>std::map erase()</tt> method
it removes values equal to these passed as a range. Furthermore this method removes only
one value for each one passed in the range, not all equal values.

It calls <tt>rtree::remove(Range const&)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param rng      The range of values.

\return         The number of removed values.
*/
template<typename Value, typename Options, typename Translator, typename Allocator, typename Range>
inline typename rtree<Value, Options, Translator, Allocator>::size_type
remove(rtree<Value, Options, Translator, Allocator> & tree, Range const& rng)
{
    return tree.remove(rng);
}

/*!
\brief Finds values meeting passed predicates e.g. nearest to some Point and/or intersecting some Box.

This query function performs spatial and k-nearest neighbor searches. It allows to pass a set of predicates.
Values will be returned only if all predicates are met.

<b>Spatial predicates</b>
    
The simplest form of spatial predicate is a \c Geometry. In this case Values intersecting the \c Geometry are returned.
More spatial predicates may be generated by one of the functions listed below:
\li \c boost::geometry::index::covered_by(),
\li \c boost::geometry::index::disjoint(),
\li \c boost::geometry::index::intersects() - default,
\li \c boost::geometry::index::overlaps(),
\li \c boost::geometry::index::within(),

It is possible to negate spatial predicates:
\li <tt>! boost::geometry::index::covered_by()</tt>,
\li <tt>! boost::geometry::index::disjoint()</tt>,
\li <tt>! boost::geometry::index::intersects()</tt>,
\li <tt>! boost::geometry::index::overlaps()</tt>,
\li <tt>! boost::geometry::index::within()</tt>

<b>Value predicate</b>
    
This is a special kind of predicate which allows to pass a user-defined functor which checks
if Value should be returned by the query. It's generated by:
\li \c boost::geometry::index::value().

<b>Nearest predicate</b>

If the nearest predicate is passed a k-nearest neighbor search will be performed. It has two variants.
Passing the first one will result in returning k number of values, the second one will result in returning
only one, closest value. In both cases values will be returned to the output iterator. Only one nearest
predicate may be passed to the query. It may be generated by:
\li \c boost::geometry::index::nearest().
        
<b>Connecting predicates</b>

A set of predicates may be generated by:
\li \c std::make_pair()
\li \c boost::make_tuple()
\li \c operator&&()

\par Example
\verbatim
bgi::query(tree, box1, std::back_inserter(result));
bgi::query(tree, std::make_pair(bgi::intersects(poly), !bgi::within(box)), std::back_inserter(result));
bgi::query(tree, bgi::intersects(poly) && !bgi::within(box), std::back_inserter(result));
bgi::query(tree, bgi::overlaps(box) && bgi::value(my_fun), std::back_inserter(result));
bgi::query(tree, bgi::nearest(pt, 5) && bgi::intersects(box), std::back_inserter(result));
\endverbatim

\warning
Only one \c nearest() perdicate may be passed to the query.

\ingroup rtree_functions

\param tree         The spatial index.
\param predicates   Predicates.
\param out_it       The output iterator, e.g. generated by std::back_inserter().

\return             The number of values found.

\par Throws
If Value copy constructor or copy assignment throws.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename Predicates, typename OutIter> inline
typename rtree<Value, Options, Translator, Allocator>::size_type
query(rtree<Value, Options, Translator, Allocator> const& tree,
      Predicates const& predicates,
      OutIter out_it)
{
    return tree.query(predicates, out_it);
}

/*!
\brief Finds value meeting passed predicates e.g. nearest to some Point and intersecting some Box.

This query function performs k-nearest neighbor searches. It allows to pass a set of predicates.
The value will be returned only if all predicates are met. This query requires that one of the
predicates must be one-value \c nearest() predicate.

<b>Spatial predicates</b>
    
The simplest form of spatial predicate is a \c Geometry. In this case Values intersecting the \c Geometry are returned.
More spatial predicates may be generated by one of the functions listed below:
\li \c boost::geometry::index::covered_by(),
\li \c boost::geometry::index::disjoint(),
\li \c boost::geometry::index::intersects() - default,
\li \c boost::geometry::index::overlaps(),
\li \c boost::geometry::index::within(),

It is possible to negate spatial predicates:
\li <tt>! boost::geometry::index::covered_by()</tt>,
\li <tt>! boost::geometry::index::disjoint()</tt>,
\li <tt>! boost::geometry::index::intersects()</tt>,
\li <tt>! boost::geometry::index::overlaps()</tt>,
\li <tt>! boost::geometry::index::within()</tt>

<b>Value predicate</b>
    
This is a special kind of predicate which allows to pass a user-defined functor which checks
if Value should be returned by the query. It's generated by:
\li \c boost::geometry::index::value().

<b>Nearest predicate</b>

This query requires that one of the predicates must be one-value \c nearest() predicate.
It may be generated by \c nearest() taking only one parameter - distance predicates.
\li \c boost::geometry::index::nearest().
        
<b>Connecting predicates</b>

A set of predicates may be generated by:
\li \c std::make_pair()
\li \c boost::make_tuple()
\li \c operator&&()

\par Example
\verbatim
bgi::query(tree, std::make_pair(bgi::nearest(pt), bgi::within(box)), value);
bgi::query(tree, bgi::nearest(pt) && bgi::intersects(poly), value);
\endverbatim

\warning
This query requires that one of the predicates must be one-value \c nearest() predicate.

\ingroup rtree_functions

\param tree         The spatial index.
\param predicates   Predicates.
\param value        The reference to value which will hold the result of the query.

\return             The number of values found (1 if value was found, 0 otherwise).

\par Throws
If Value copy constructor or copy assignment throws.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename Predicates> inline
typename rtree<Value, Options, Translator, Allocator>::size_type
query(rtree<Value, Options, Translator, Allocator> const& tree,
      Predicates const& predicates,
      typename rtree<Value, Options, Translator, Allocator>::value_type & value)
{
    return tree.query(predicates, value);
}

/*!
\brief Find values meeting spatial predicates.

It calls \c rtree::spatial_query with parameters <tt>(Predicates const&, OutIter)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param pred     The spatial predicates.
\param out_it   The output iterator of the result range.

\return         The number of found values.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename Predicates, typename OutIter>
inline size_t spatial_query(rtree<Value, Options, Translator, Allocator> const& tree, Predicates const& pred, OutIter out_it)
{
    return tree.spatial_query(pred, out_it);
}

/*!
\brief Find the value meeting distances predicates.

It calls \c rtree::nearest_query with parameters <tt>(DistancesPredicates const& dpred, value_type & v)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param dpred    The distances predicates.
\param v        The result.

\return         The number of found values.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename DistancesPredicates>
inline size_t nearest_query(rtree<Value, Options, Translator, Allocator> const& tree, DistancesPredicates const& dpred, Value & v)
{
    return tree.nearest_query(dpred, v);
}

/*!
\brief Find the value meeting distances and spatial predicates.

It calls \c rtree::nearest_query with parameters <tt>(DistancesPredicates const& dpred, Predicates const& pred, value_type & v)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param dpred    The distances predicates.
\param pred     The spatial predicates.
\param v        The result.

\return         The number of found values.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename DistancesPredicates, typename Predicates>
inline size_t nearest_query(rtree<Value, Options, Translator, Allocator> const& tree, DistancesPredicates const& dpred, Predicates const& pred, Value & v)
{
    return tree.nearest_query(dpred, pred, v);
}

/*!
\brief Find k values meeting distances predicates.

It calls \c rtree::nearest_query with parameters <tt>(DistancesPredicates const & dpred, size_type k, OutIter out_it)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param dpred    The distances predicates.
\param k        The max number of values.
\param out_it   The output iterator of the result range.

\return         The number of found values.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename DistancesPredicates, typename OutIter>
inline size_t nearest_query(rtree<Value, Options, Translator, Allocator> const& tree, DistancesPredicates const& dpred, typename rtree<Value, Options, Translator, Allocator>::size_type k, OutIter out_it)
{
    return tree.nearest_query(dpred, k, out_it);
}

/*!
\brief Find k values meeting distances and spatial predicates.

It calls \c rtree::nearest_query with parameters <tt>(DistancesPredicates const & dpred, size_type k, Predicates const & pred, OutIter out_it)</tt>.

\ingroup rtree_functions

\param tree     The spatial index.
\param dpred    The distances predicates.
\param k        The max number of values.
\param pred     The spatial predicates.
\param out_it   The output iterator of the result range.

\return         The number of found values.
*/
template <typename Value, typename Options, typename Translator, typename Allocator, typename DistancesPredicates, typename Predicates, typename OutIter>
inline size_t nearest_query(rtree<Value, Options, Translator, Allocator> const& tree, DistancesPredicates const& dpred, typename rtree<Value, Options, Translator, Allocator>::size_type k, Predicates const& pred, OutIter out_it)
{
    return tree.nearest_query(dpred, k, pred, out_it);
}

/*!
\brief Remove all values from the index.

It calls \c rtree::clear().

\ingroup rtree_functions

\param tree     The spatial index.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline void clear(rtree<Value, Options, Translator, Allocator> & tree)
{
    return tree.clear();
}

/*!
\brief Get the number of values stored in the index.

It calls \c rtree::size().

\ingroup rtree_functions

\param tree     The spatial index.

\return         The number of values stored in the index.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline size_t size(rtree<Value, Options, Translator, Allocator> const& tree)
{
    return tree.size();
}

/*!
\brief Query if there are no values stored in the index.

It calls \c rtree::empty().

\ingroup rtree_functions

\param tree     The spatial index.

\return         true if there are no values in the index.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline bool empty(rtree<Value, Options, Translator, Allocator> const& tree)
{
    return tree.empty();
}

/*!
\brief Get the box containing all stored values or an invalid box if the index has no values.

It calls \c rtree::envelope().

\ingroup rtree_functions

\param tree     The spatial index.

\return         The box containing all stored values or an invalid box.
*/
template <typename Value, typename Options, typename Translator, typename Allocator>
inline typename rtree<Value, Options, Translator, Allocator>::box_type const&
envelope(rtree<Value, Options, Translator, Allocator> const& tree)
{
    return tree.envelope();
}

}}} // namespace boost::geometry::index

// Rtree adaptation to Box concept

namespace boost { namespace geometry {

// Traits specializations for box above
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Value, typename Parameters, typename Translator, typename Allocator>
struct tag< index::rtree<Value, Parameters, Translator, Allocator> >
{
    typedef box_tag type;
};

template <typename Value, typename Parameters, typename Translator, typename Allocator>
struct point_type< index::rtree<Value, Parameters, Translator, Allocator> >
{
    typedef typename geometry::point_type<
        typename index::rtree<Value, Parameters, Translator, Allocator>::box_type
    >::type type;
};

template <typename Value, typename Parameters, typename Translator, typename Allocator, std::size_t Dimension>
struct indexed_access<index::rtree<Value, Parameters, Translator, Allocator>, min_corner, Dimension>
{
    typedef typename geometry::coordinate_type<
        typename geometry::point_type<
            index::rtree<Value, Parameters, Translator, Allocator>
        >::type
    >::type coordinate_type;

    static inline coordinate_type get(index::rtree<Value, Parameters, Translator, Allocator> const& tree)
    {
        return geometry::get<min_corner, Dimension>(tree.envelope());
    }

    static inline void set(index::rtree<Value, Parameters, Translator, Allocator> & tree,
                           coordinate_type const& value)
    {
        return geometry::set<min_corner, Dimension>(tree.envelope(), value);
    }
};

template <typename Value, typename Parameters, typename Translator, typename Allocator, std::size_t Dimension>
struct indexed_access<index::rtree<Value, Parameters, Translator, Allocator>, max_corner, Dimension>
{
    typedef typename geometry::coordinate_type<
        typename geometry::point_type<
            index::rtree<Value, Parameters, Translator, Allocator>
        >::type
    >::type coordinate_type;

    static inline coordinate_type get(index::rtree<Value, Parameters, Translator, Allocator> const& tree)
    {
        return geometry::get<max_corner, Dimension>(tree.envelope());
    }

    static inline void set(index::rtree<Value, Parameters, Translator, Allocator> & tree,
                           coordinate_type const& value)
    {
        return geometry::set<max_corner, Dimension>(tree.envelope(), value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} //namespace boost::geometry

#endif // BOOST_GEOMETRY_INDEX_RTREE_HPP
