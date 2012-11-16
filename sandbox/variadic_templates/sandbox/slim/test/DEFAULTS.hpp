#ifndef DEFAULTS_HPP_INCLUDED
#define DEFAULTS_HPP_INCLUDED
//ChangeLog:
//  2012-10-27.1005CST
//    WHAT:
//      Copied following code from parts of the code in
//      https://github.com/ericniebler/home/blob/master/src/tuple/tuple.cpp
//    WHY:
//      To enable reuse in other code using #include's.
//
//=====================================================

// For adding defaulted default, copy and move constructors, and move/copy assign.
#define DEFAULTS(CLASS)                                                                             \
    CLASS() = default; /*required for the type to be trivial!*/                                     \
    CLASS(CLASS const &) = default; /* memberwise copy */                                           \
    CLASS(CLASS &&) = default; /* member-wise move */                                               \
    /* These would otherwise be deleted because we */                                               \
    /* declared a move constructor! */                                                              \
    CLASS &operator=(CLASS const &) = default; /* memberwise copy assign */                         \
    CLASS &operator=(CLASS &&) = default; /* memberwise move assign */                              \
    /**/

#endif
