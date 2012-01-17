
#ifndef PROXY_HPP_
#define PROXY_HPP_

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

namespace proxy { namespace aux {

template<class Proxy, typename Ptr>
struct accessor {
    BOOST_MPL_ASSERT_MSG(false, ERROR_expected_member_pointer, (Ptr));
};

template<class Proxy, typename D, class C>
struct accessor<Proxy, D C::*> {
    typedef C class_type;
    typedef D C::* data_ptr;
    explicit accessor(Proxy& proxy, C* obj, data_ptr data)
        : proxy_(proxy), obj_(obj), data_(data) {}

    D const& operator=(D const& value)
        { return proxy_.template set<D, C>(obj_, data_, value); }
    D& operator=(D& value)
        { return proxy_.template set<D, C>(obj_, data_, value); }

    operator D const&() const
        { return proxy_.template get<D, C>(obj_, data_); }
    operator D&()
        { return proxy_.template get<D, C>(obj_, data_); }
private:
    Proxy& proxy_;
    C* obj_;
    data_ptr data_;
};

template<class Proxy, typename R, class C, typename A0>
struct accessor<Proxy, R (C::*)(A0)> {
    typedef C class_type;
    typedef R (C::* func_ptr)(A0);
    explicit accessor(Proxy& proxy, C* obj, func_ptr func)
        : proxy_(proxy), obj_(obj), func_(func) {}

    R operator()(A0 a0) const
        { return proxy_.template call<R, C, A0>(obj_, func_, a0); }
    R operator()(A0 a0)
        { return proxy_.template call<R, C, A0>(obj_, func_, a0); }
private:
    Proxy& proxy_;
    C* obj_;
    func_ptr func_;
};

}} // namespace

template<class Class, class Proxy>
struct proxy_ptr {
    /* implicit */ proxy_ptr(Class* obj) : proxy_(), obj_(obj) {}
    virtual ~proxy_ptr() { delete obj_; }

    template<typename F>
    proxy::aux::accessor<Proxy, F> operator->*(F func) {
        typedef typename proxy::aux::accessor<Proxy, F>::class_type f_class;
        BOOST_MPL_ASSERT_MSG((boost::is_same<Class, f_class>::value),
                ERROR_expected_member_pointer_of_class, (Class));
        // f_class* cast used to reduce verbosity of compiler errors (always
        // safe because of static assertion above).
        return proxy::aux::accessor<Proxy, F>(proxy_, (f_class*)obj_, func);
    }

private:
    Proxy proxy_;
    Class* obj_;
};

#endif // #include guard

