
#ifndef SEPARATE_HPP_
#define SEPARATE_HPP_

#include <proxy.hpp>
#include <boost/preprocessor/cat.hpp>
#include <iostream>

namespace separate_ptr_aux {

struct locker {
    /** @todo IF R is non-void OR any Ai is a ref OR a ptr THEN lock, etc */

    template<typename D, class C>
    D const& set(C* obj, D C::* data, D const& value)
        { return obj->*data = value; }
    template<typename D, class C>
    D& set(C* obj, D C::* data, D& value)
        { return obj->*data = value; }
    
    template<typename D, class C>
    D const& get(C const* obj, D C::* data) { return obj->*data; }
    template<typename D, class C>
    D& get(C* obj, D C::* data) { return obj->*data; }

    template<typename R, class C, typename A0>
    R call(C const* obj, R (C::* func)(A0), A0 a0)
        { return (obj->*func)(a0); }
    template<typename R, class C, typename A0>
    R call(C* obj, R (C::* func)(A0), A0 a0)
        { return (obj->*func)(a0); }
};

} // namespace

template<class Class>
struct separate_ptr : proxy_ptr<Class, separate_ptr_aux::locker> {
    /* implicit */ separate_ptr(Class* obj)
            : proxy_ptr<Class, separate_ptr_aux::locker>(obj) {}
};

#define SEPARATE_TYPEOF(obj) \
    BOOST_PP_CAT(obj, Xtype)

#define SEPARATE(type, obj) \
    typedef type SEPARATE_TYPEOF(obj); \
    ::separate_ptr< SEPARATE_TYPEOF(obj) > obj \
    /* = new ... */

#define SEPARATED(obj) \
    obj->*&SEPARATE_TYPEOF(obj)

#endif // #include guard

