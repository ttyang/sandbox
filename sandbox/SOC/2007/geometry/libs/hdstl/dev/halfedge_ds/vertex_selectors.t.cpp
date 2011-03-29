//vertex_selectors.hpp   -*- C++ -*-
//
//@OVERVIEW:  The components under test are the stored_vertex and vertex_gen 
//classes.  We must make sure that all selectors are suitably defined and 
//that the selection is done properly.
//
//@TEST_PLAN: First create an instance of all the selectors (to make sure they
// exist, and verify that there are no more than tested).  Then instantiate the
// 'vertex_gen' for all selector values, with base vertex classes and without 
// base vertex classes and verify that each combination compiles and works.

#include <boost/hdstl/halfedge_ds/vertex_selectors.hpp>

#include <boost/test/minimal.hpp>

#include <set>
#include <string>
#include <vector>

using namespace boost::hdstl;
using namespace std;

// ===========================================================================
//                              SELECTION CLASSES
// ===========================================================================

template <typename VertexS>
bool selection_requirements(VertexS const&) {
    return false;
}

bool selection_requirements(noVertexS const&) {
    return true;
}

template <typename Selector>
bool selection_requirements(vertexS<Selector, false, sourceS> const&) {
    return true;
}

template <typename Selector>
bool selection_requirements(vertexS<Selector, false, targetS> const&) {
    return true;
}

template <typename Selector>
bool selection_requirements(vertexS<Selector, true, sourceS> const&) {
    return true;
}

template <typename Selector>
bool selection_requirements(vertexS<Selector, true, targetS> const&) {
    return true;
}

// ===========================================================================
//                              CLASS VERTEX_GEN
// ===========================================================================

template<typename VertexGen>
bool vertex_gen_requirements_void_noVertexLink() {
    
    // Types must exist.
    typedef typename VertexGen::vertex_selector   vertex_selector;
    typedef typename VertexGen::vertex_descriptor vertex_descriptor;
    typedef typename VertexGen::vertex_iterator   vertex_iterator;
    typedef typename VertexGen::vertex_type       vertex_type;
    typedef typename VertexGen::container_type   container_type;
    typedef typename VertexGen::ContainerGen     container_gen;

    vertex_type fa;
    vertex_type fb;
    vertex_type fc;
    vertex_type fd;
    vertex_type array[] = { fa, fb, fc, fd };  
    
    // Construct a vertex_gen object whose container contains array.
    // Verify that vertices_begin(), vertices_end(), and num_vertices() work.
    // Access the vertices and, if the has_vertex_links is set, check that the
    // halfedge() works.
    container_type temp_con(array,array+4);
    VertexGen vertexGen;
    vertexGen.m_container = temp_con;
    
    BOOST_CHECK(( vertexGen.m_container.size() == 4 ));
    
    vertex_iterator   vertexs_begin     = container_gen::container_begin(vertexGen.m_container); 
    vertex_descriptor first_vertex      = *vertexs_begin;
    vertex_type&      first_vertex_ref  = container_gen::value(first_vertex, vertexGen.m_container);
    
    BOOST_CHECK(( &first_vertex_ref == &(*vertexGen.m_container.begin())));
    return true;
}

template <typename VertexGen>
bool vertex_gen_requirements_void() {
    
    // Types must exist.
    typedef typename VertexGen::vertex_selector   vertex_selector;
    typedef typename VertexGen::vertex_descriptor vertex_descriptor;
    typedef typename VertexGen::vertex_iterator   vertex_iterator;
    typedef typename VertexGen::vertex_type       vertex_type;
    typedef typename VertexGen::container_type   container_type;
    typedef typename VertexGen::ContainerGen     container_gen;

    vertex_type fa(1);
    vertex_type fb(2);
    vertex_type fc(3);
    vertex_type fd(4);
    vertex_type array[] = { fa, fb, fc, fd };  
    
    // Construct a vertex_gen object whose container contains array.
    // Verify that vertices_begin(), vertices_end(), and num_vertices() work.
    // Access the vertices and, if the has_vertex_links is set, check that the
    // halfedge() works.
    container_type temp_con(array,array+4);
    VertexGen vertexGen;
    vertexGen.m_container = temp_con;
    
    BOOST_CHECK(( vertexGen.m_container.size() == 4 ));

    vertex_iterator   vertices_begin     = container_gen::container_begin(vertexGen.m_container); 
    vertex_iterator   vertices_end       = --container_gen::container_end(vertexGen.m_container); 
    vertex_descriptor first_vertex      = *vertices_begin;
    vertex_type&      first_vertex_ref  = container_gen::value(first_vertex, vertexGen.m_container);
    
    BOOST_CHECK(( &first_vertex_ref == &(*vertexGen.m_container.begin())));
    BOOST_CHECK(( vertices_begin->m_vertexLink == 1 ));
    BOOST_CHECK(( vertices_end->m_vertexLink == 4 ));
    
    return true;
}

template <typename VertexGen, typename Base>
bool vertex_gen_requirements_noVertexLink() {
    
    typedef typename VertexGen::vertex_selector   vertex_selector;
    typedef typename VertexGen::vertex_descriptor vertex_descriptor;
    typedef typename VertexGen::vertex_iterator   vertex_iterator;
    typedef typename VertexGen::vertex_type       vertex_type;
    typedef typename VertexGen::container_type   container_type;
    typedef typename VertexGen::ContainerGen     container_gen;

    vertex_type fa(Base(1));
    vertex_type fb(Base(2));
    vertex_type fc(Base(3));
    vertex_type fd(Base(4));
    vertex_type array[] = { fa, fb, fc, fd };  (void) array;
    
    // Same checks as before:
    //BOOST_CHECK(( vertex_gen_requirements_void_noVertexLink<VertexGen>() ));
    container_type temp_con(array,array+4);
    VertexGen vertexGen;
    vertexGen.m_container = temp_con;
    
    BOOST_CHECK(( vertexGen.m_container.size() == 4 ));

    vertex_iterator   vertices_begin     = container_gen::container_begin(vertexGen.m_container); 
    vertex_iterator   vertices_end       = --container_gen::container_end(vertexGen.m_container); 
    vertex_descriptor first_vertex      = *vertices_begin;
    vertex_type&      first_vertex_ref  = container_gen::value(first_vertex, vertexGen.m_container);
    
    BOOST_CHECK(( &first_vertex_ref == &(*vertexGen.m_container.begin())));
    
    // Plus: get the base back from the vertices and making sure it matches.
    BOOST_CHECK(( vertices_begin->base() == 1 ));
    BOOST_CHECK(( vertices_end->base() == 4 ));

    return true;
}

template <typename VertexGen, typename Base>
bool vertex_gen_requirements() {
    
    typedef typename VertexGen::vertex_selector   vertex_selector;
    typedef typename VertexGen::vertex_descriptor vertex_descriptor;
    typedef typename VertexGen::vertex_iterator   vertex_iterator;
    typedef typename VertexGen::vertex_type       vertex_type;
    typedef typename VertexGen::container_type   container_type;
    typedef typename VertexGen::ContainerGen     container_gen;

    vertex_type fa(1, Base(1));
    vertex_type fb(2, Base(2));
    vertex_type fc(3, Base(3));
    vertex_type fd(4, Base(4));
    vertex_type array[] = { fa, fb, fc, fd };  (void) array;
    
    // Same checks as before:
    container_type temp_con(array,array+4);
    VertexGen vertexGen;
    vertexGen.m_container = temp_con;
    
    BOOST_CHECK(( vertexGen.m_container.size() == 4 ));

    vertex_iterator   vertices_begin     = container_gen::container_begin(vertexGen.m_container); 
    vertex_iterator   vertices_end       = --container_gen::container_end(vertexGen.m_container); 
    vertex_descriptor first_vertex      = *vertices_begin;
    vertex_type&      first_vertex_ref  = container_gen::value(first_vertex, vertexGen.m_container);
    
    BOOST_CHECK(( &first_vertex_ref == &(*vertexGen.m_container.begin())));
    BOOST_CHECK(( vertices_begin->m_vertexLink == 1 ));
    BOOST_CHECK(( vertices_end->m_vertexLink == 4 ));
    
    // Plus: get the base back from the vertices and making sure it matches.
    BOOST_CHECK(( vertices_begin->base() == 1 ));
    BOOST_CHECK(( vertices_end->base() == 4 ));

    return true;
}

// ===========================================================================
//                              USAGE EXAMPLE
// ===========================================================================

// The usage example is the component itself.

// ===========================================================================
//                              BOOST TEST APPARATUS
// ===========================================================================

int test_main(int, char **)
{
    BOOST_CHECK(( selection_requirements(noVertexS()) ));

    BOOST_CHECK(( selection_requirements(vertexS<listS,true, sourceS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<listS,false, sourceS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<listS,true, targetS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<listS,false, targetS>()) ));
    
    BOOST_CHECK(( vertex_gen_requirements_void_noVertexLink<
                   vertex_gen<vertexS<listS,false, sourceS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void_noVertexLink<
                   vertex_gen<vertexS<listS,false, targetS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void<
                   vertex_gen<vertexS<listS,true, sourceS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void<
                   vertex_gen<vertexS<listS,true, targetS>, int, void> >() ));

    BOOST_CHECK(( vertex_gen_requirements_noVertexLink<
               vertex_gen<vertexS<listS,false, sourceS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements_noVertexLink<
               vertex_gen<vertexS<listS,false, targetS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements<
               vertex_gen<vertexS<listS,true, sourceS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements<
               vertex_gen<vertexS<listS,true, targetS>, int, int>, int >() ));
   
    // BOOST_CHECK(( vertex_gen_requirements<
    //        vertex_gen<vertexS<listS,false>, int, custom_vertex_base> >() ));

    // BOOST_CHECK(( vertex_gen_requirements<
    //        vertex_gen<vertexS<listS,true>, int, custom_vertex_base> >() ));
    
    BOOST_CHECK(( selection_requirements(vertexS<vecS,true, sourceS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<vecS,false, sourceS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<vecS,true, targetS>()) ));
    BOOST_CHECK(( selection_requirements(vertexS<vecS,false, targetS>()) ));
    
    BOOST_CHECK(( vertex_gen_requirements_void_noVertexLink<
                   vertex_gen<vertexS<vecS,false, sourceS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void_noVertexLink<
                   vertex_gen<vertexS<vecS,false, targetS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void<
                   vertex_gen<vertexS<vecS,true, sourceS>, int, void> >() ));
    BOOST_CHECK(( vertex_gen_requirements_void<
                   vertex_gen<vertexS<vecS,true, targetS>, int, void> >() ));

    BOOST_CHECK(( vertex_gen_requirements_noVertexLink<
               vertex_gen<vertexS<vecS,false, sourceS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements_noVertexLink<
               vertex_gen<vertexS<vecS,false, targetS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements<
               vertex_gen<vertexS<vecS,true, sourceS>, int, int>, int >() ));
    BOOST_CHECK(( vertex_gen_requirements<
               vertex_gen<vertexS<vecS,true, targetS>, int, int>, int >() ));
   
    // BOOST_CHECK(( vertex_gen_requirements<
    //        vertex_gen<vertexS<vecS,false>, int, custom_vertex_base> >() ));

    // BOOST_CHECK(( vertex_gen_requirements<
    //        vertex_gen<vertexS<vecS,true>, int, custom_vertex_base> >() ));
    //BOOST_CHECK(( usageExample() ));
    
    return 0;
}
