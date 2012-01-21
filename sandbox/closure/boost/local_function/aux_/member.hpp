
#ifndef BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunctions to manipulate data members.

template<typename T> struct member_type {
    typedef T& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T*> {
    typedef T& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T const*> {
    typedef T const& reference;
    typedef T const* pointer;
};

template<typename T> T* member_addr(T& data) { return &data; }
template<typename T> T const* member_addr(T const& data) { return &data; }
template<typename T> T* member_addr(T* data) { return data; }
template<typename T> T const* member_addr(T const* data) { return data; }

template<typename T> T& member_deref(T& data) { return data; }
template<typename T> T const& member_deref(T const& data) { return data; }
template<typename T> T& member_deref(T* data) { return *data; }
template<typename T> T const& member_deref(T const* data) { return *data; }

} } } // namespace

#endif // #include guard

