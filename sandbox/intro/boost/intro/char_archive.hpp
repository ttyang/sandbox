//          Copyright Stefan Strasser 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_INTRO_CHAR_ARCHIVE_HPP
#define BOOST_INTRO_CHAR_ARCHIVE_HPP


#include <boost/mpl/bool.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/static_assert.hpp>
#include <boost/intro/array_extension.hpp>
#include <algorithm>
#include <boost/mpl/size_t.hpp>
#include <iterator>
#include <boost/archive/archive_exception.hpp>
#include <cstring>

namespace boost{
namespace intro{

template<class OutputIterator>
class char_oarchive{
public:
    explicit char_oarchive(OutputIterator const &out) : out(out){}
    template<class Size>
    void save_binary(void const *vdata,Size size){
        this->save_binary(static_cast<char const *>(vdata),size,typename array_extension<OutputIterator>::type());
    }
    template<class T>
    char_oarchive &operator<<(T const &t){
        BOOST_STATIC_ASSERT(serialization::is_bitwise_serializable<T>::value);
        this->save_binary(&t,mpl::size_t<sizeof(T)>());
        return *this;
    }
private:
    template<class Size>
    void save_binary(char const *data,Size size,mpl::true_){
        this->out.assign(data,size);
    }
    template<class Size>
    void save_binary(char const *data,Size size,mpl::false_){
        std::copy(data,data+size,this->out);
    }

    OutputIterator out;
};

template<class InputIterator>
class char_iarchive{
public:
    char_iarchive(InputIterator const &begin,InputIterator const &end)
        : in(begin), end(end){}
    template<class Size>
    void load_binary(void *vdata,Size size){
        char *data=static_cast<char *>(vdata);
        this->load_binary(
            data,
            size,
            typename std::iterator_traits<InputIterator>::iterator_category(),
            typename continuous_values<InputIterator>::type()
        );
    }
    template<class T>
    char_iarchive &operator >>(T &t){
        BOOST_STATIC_ASSERT(serialization::is_bitwise_serializable<T>::value);
        this->load_binary(&t,mpl::size_t<sizeof(T)>());
        return *this;
    }
private:
    template<class Size>
    void load_binary(char *data,Size size,std::random_access_iterator_tag,mpl::true_ contvals){
        if(this->in + size > this->end) throw archive::archive_exception(archive::archive_exception::stream_error);
        std::memcpy(data,&*this->in,size);
        this->in+=size;
    }
    template<class Size>
    void load_binary(char *data,Size size,std::random_access_iterator_tag,mpl::false_ contvals){
        if(this->in + size > this->end) throw archive::archive_exception(archive::archive_exception::stream_error);
        std::copy(data,data+size,this->in);
    }
    template<class Size,class Category>
    void load_binary(char *data,Size size,Category,mpl::false_ contvals){
        for(std::size_t c=0;c<size;++c){
            if(this->in == this->end) throw archive::archive_exception(archive::archive_exception::stream_error);
            *data++=*this->in++;
        }
    }

    InputIterator in;
    InputIterator end;
};


}
}


#endif
