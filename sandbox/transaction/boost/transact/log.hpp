//          Copyright Stefan Strasser 2009 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



//TODO: rolling log files are always started at .1 currently.
//is persistent needs a header in the log file the old logs can't be deleted
//until a new one is created, so the log needs to start at .<old+1>
//better solution is to don't use a header for this purpose but safe this info in
//an extra file by persistent

#ifndef BOOST_TRANSACT_LOG_HEADER_HPP
#define BOOST_TRANSACT_LOG_HEADER_HPP

#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/integer.hpp>
#include <boost/optional/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/transact/detail/sectorizing_file.hpp>
#include <boost/transact/detail/aligning_file.hpp>
#include <boost/transact/detail/buffering_file.hpp>
#include <boost/transact/detail/syncing_file.hpp>
#include <boost/transact/detail/filebuf_file.hpp>
#include <boost/transact/detail/file.hpp>
#include <boost/transact/detail/file_iterator.hpp>
#include <boost/transact/archive.hpp>

namespace boost{
namespace transact{


namespace detail{

template<class OutputIterator>
static void get_existing_log_ids(OutputIterator out,std::string const &name){
    namespace fs=boost::filesystem;
    try{
        std::string filename=fs::path(name).filename().native();
        fs::path dir=fs::path(name).parent_path();
        fs::directory_iterator it;
        if(dir.empty()) it=fs::directory_iterator(".");
        else it=fs::directory_iterator(dir);
        for(;it != fs::directory_iterator();++it){
            std::string foundfilename=it->path().filename().native();
            if(foundfilename.substr(0,filename.length()+1) != filename+".") continue;
            std::string nrstring=foundfilename.substr(filename.length()+1);
            unsigned int nr=0;
            try{ nr=lexical_cast<unsigned int>(nrstring); } catch(...){ continue; }
            *out++=nr;
        }
    }catch(...){
        throw io_failure();
    }
}

/*
static unsigned int get_next_log_id(std::string const &name){
    std::vector<unsigned int> ids;
    get_existing_log_ids(std::back_inserter(ids),name);
    return ids.empty() ? 1 : *std::max_element(ids.begin(),ids.end())+1;
}

static std::string get_log_filename(std::string const &name,unsigned int l){
    return name+'.'+lexical_cast<std::string>(l);
}*/

}


namespace detail{

template<class Entries>
struct log_id_type{
    typedef typename boost::uint_value_t<mpl::size<Entries>::value>::least type;
};
  
template<class Iterator,class Entry,class Id>
struct log_entry_id_iterator{
    typedef typename mpl::eval_if<
        is_same<typename mpl::deref<Iterator>::type,Entry>,
        Id,
	log_entry_id_iterator<
	    typename mpl::next<Iterator>::type,
	    Entry,
	    mpl::integral_c<typename Id::value_type,Id::value+1>
	>
    >::type type;
};

//don't use mpl::distance, so Entries can be a ForwardSequence
template<class Entries,class Entry>
struct log_entry_id : log_entry_id_iterator<
        typename mpl::begin<Entries>::type,
	Entry,
	mpl::integral_c<typename log_id_type<Entries>::type,1>
    >::type{};
}

template<class Entries,class File>
class olog{
public:
    typedef typename detail::log_id_type<Entries>::type id_type;
    explicit olog(File &file) : file(file){}
    template<class T>
    olog &operator<<(T const &t){
        typedef detail::file_output_iterator<File> it_type;
        it_type it(this->file);
        char_oarchive<it_type> archive(it);
        archive << detail::log_entry_id<Entries,T>::type::value;
	archive << t;
        return *this;
    }
protected:
    File &file;
};

namespace detail{
 
template<class Archive,class Entries,class F>
class ilog_dispatcher{
    typedef typename detail::log_id_type<Entries>::type id_type;
public:
    ilog_dispatcher(){
        this->init<0>(mpl::false_());
    }
    void operator()(id_type id,Archive &ar,F const &f) const{
        if(id <= 0 || id > mpl::size<Entries>::value) throw io_failure();
        (*this->functions[id-1])(ar,f);
    }
private:
    template<id_type Id>
    void init(mpl::false_){
        this->functions[Id]=&dispatch<typename mpl::at_c<Entries,Id>::type>;
        this->init<Id+1>(mpl::bool_<(Id+1 == mpl::size<Entries>::value)>());
    }
    template<id_type Id>
    void init(mpl::true_){}
    template<class T>
    static void dispatch(Archive &ar,F const &f){
        T t; //FIXME requires log entries to be default constructible
	ar >> t;
	f(t);
    }
    typedef void (*function_type)(Archive &,F const &f);
    function_type functions[mpl::size<Entries>::value];
};
  
  
}

template<class Entries,class File>
class ilog{
public:
    typedef typename detail::log_id_type<Entries>::type id_type;
    explicit ilog(File &file) : file(file){}
    template<class F>
    ilog &operator>>(F const &f){
        typedef detail::file_input_iterator<File> it_type;
        typedef char_iarchive<it_type> archive_type;
        static detail::ilog_dispatcher<archive_type,Entries,F> const dispatch;
        
	it_type it(this->file);
	archive_type archive(it,it_type());
	id_type id=0;
        archive >> id;
	dispatch(id,archive,f);
	return *this;
    }
private:
    File &file;
};

template<class Entries,class RollingLogfile,class Id=unsigned int>
class transaction_olog
    : public olog<Entries,RollingLogfile>{
    typedef olog<Entries,RollingLogfile> base_type;
    struct detail{
        struct null_header{};
    };
public:
    typedef Id id_type;
    transaction_olog(RollingLogfile &file,std::size_t max_log_size=100*1024*1024)
        : base_type(file)
        , max_log_size(max_log_size)
	, next_tx(1)
	, open_txs(0)
	, rolled_txs(0)
	, roll_cutoff(0){
      
    }
    Id begin_transaction(){
        return this->begin_transaction(detail::null_header()); 
    }
    template<class Header>
    Id begin_transaction(Header const &header){
        Id tx=this->next_tx++;
	if(!this->rolling() && this->file.position() >= this->max_log_size){
	    //don't roll a second time until all transactions started in the old log
	    //are closed, RollingLogfile only guarantees a minimum of 2 existing files
	    this->file.roll();
	    this->roll_cutoff=tx;
	    BOOST_ASSERT(this->rolled_txs==0);
	    this->rolled_txs=this->open_txs;
	    this->open_txs=0;
	    this->write_header(header);
	}
	BOOST_ASSERT(!this->rolling() || tx >= this->roll_cutoff);
	++this->open_txs;
	return tx;
    }
    void end_transaction(Id tx){
        if(this->rolling() && tx < this->roll_cutoff){
	    BOOST_ASSERT(this->rolled_txs > 0);
	    --this->rolled_txs;
	    //if rolled_txs is now 0 all transactions started in the old, rolled, log have
	    //successfully ended. rolling() now returns false, removing the old log file
	    //and thus another log roll is safe from now on
	}else{
	    BOOST_ASSERT(this->open_txs > 0);
	    --this->open_txs;
	}
    }
    bool rolling() const{ return this->rolled_txs > 0; }
private:
    void write_header(detail::null_header const &){}
    template<class Header>
    void write_header(Header const &header){
        typedef detail::file_output_iterator<RollingLogfile> it_type;
        it_type it(this->file);
        char_oarchive<it_type> archive(it);
        archive << detail::log_entry_id<Entries,Header>::type::value;
        archive << header;
    }
  
    std::size_t const max_log_size;
    Id next_tx;
    std::size_t open_txs, rolled_txs;
    Id roll_cutoff;
};

namespace detail{
  
  
template<bool Sync>
struct ologfile_type{
    typedef typename mpl::if_c<
      Sync,
      detail::sectorizing_seq_ofile<
	  detail::aligning_seq_ofile<
	      detail::buffering_seq_ofile<
		  detail::syncing_seq_ofile<
		      detail::ofile<false> //FIXME argument. why is this a parameter?
		  >,
		  8192
	      >
	  >
      >,
      detail::buffering_seq_ofile<
	  detail::filebuf_seq_ofile,
	  8192
      >
    >::type type;
};

template<bool Sync>
struct ilogfile_type{
    typedef typename mpl::if_c<
      Sync,
      detail::sectorizing_seq_ifile<
	  detail::filebuf_seq_ifile
      >,
      detail::filebuf_seq_ifile
    >::type type;
};
  
  
}

template<bool Sync>
class ologfile : public detail::ologfile_type<Sync>::type{
    typedef typename detail::ologfile_type<Sync>::type base_type;
public:
    explicit ologfile(std::string const &name) : base_type(name){}
};

template<bool Sync>
class ilogfile : public detail::ilogfile_type<Sync>::type{
    typedef typename detail::ilogfile_type<Sync>::type base_type;
public:
    explicit ilogfile(std::string const &name) : base_type(name){}  
};

namespace detail{

template<class File>
class rolling_ologfile_base{
public:
    typedef typename File::size_type size_type;
    explicit rolling_ologfile_base(std::string const &name)
        : name(name)
	, logid(1){
        this->files[0]=in_place(this->name+".1");
	this->active_=&this->files[0];
    }
    template<class Size>
    void write(void const *data,Size s){
        this->active()->write(data,s);
    }
    void flush(){
        this->active()->flush();
    }
    void sync(){
        this->active()->sync();
    }
    typename File::size_type position() const{ return this->active()->position(); }
protected:
    optional<File> &active(){
        return *this->active_;
    }
    optional<File> const &active() const{
        return *this->active_;
    }
    optional<File> &inactive(){
        return this->active_ == &this->files[0] ? this->files[1] : this->files[0];
    }
  
    std::string const name;
    unsigned int logid;
    optional<File> files[2];
    optional<File> *active_;
};

}

template<class File>
class rolling_ologfile
    : public detail::rolling_ologfile_base<File>{
    typedef detail::rolling_ologfile_base<File> base_type;
public:
    explicit rolling_ologfile(std::string const &name)
        : base_type(name){}
    void roll(){
        //close old log to cause write exceptions, which would be ignored when destructing:
        //TODO optimization close() flushes/syncs the old logfile. one could also keep the old
        //log open until an explicit request to flush/sync the log causes all log files
        //to flush/sync
        this->active()->close();
	//use 2 optional<>s because the new file must be fully constructed to replace the old one.
        //if construction fails there must be a valid old log file in this->active, and files
        //are not swap()able:
        optional<File> &newlog=this->inactive();
	BOOST_ASSERT(!newlog);
	newlog=in_place(this->name+'.'+lexical_cast<std::string>(this->logid+1));
	this->active_=&newlog; ++this->logid;
	this->inactive().reset();
    }
};

template<class File>
class alternating_ologfile
    : public detail::rolling_ologfile_base<File>{
    typedef detail::rolling_ologfile_base<File> base_type;
public:
    explicit alternating_ologfile(std::string const &name)
        : base_type(name){}
    void roll(){
        this->active()->close();
        optional<File> &newlog=this->inactive();
	std::string const newname=this->name+'.'+lexical_cast<std::string>(this->logid+1);
	if(!newlog) newlog=in_place(newname);
	else newlog->reopen(newname);
	this->active_=&newlog; ++this->logid;
    }
};

template<class File>
class rolling_ilogfile{
public:
    typedef typename File::size_type size_type;
    explicit rolling_ilogfile(std::string const &name)
        : name(name){
        detail::get_existing_log_ids(std::back_inserter(this->ids),this->name);
	std::sort(this->ids.begin(),this->ids.end());
	
	//must be a contiguous sequence of files:
        for(ids_type::const_iterator next=this->ids.begin();next!=this->ids.end();){
            ids_type::const_iterator it=next++;
            if(next != this->log_ids.end() && (*it != *next-1)) throw io_failure();
        }
    	
	this->current=this->ids.begin();
	this->open();
    }
    template<class Size>
    void read(void *data,Size s){
        if(!this->file) throw eof_exception();
        try{
            this->file->read(data,s);
	}catch(eof_exception &){
	    //eof means nothing was read, otherwise io_exception is thrown. retry in next file
	    ++this->current;
	    this->open();
	    this->read(data,s);
	}
    }
    void remove(){
        for(ids_type::const_iterator it=this->ids.begin();it!=this->ids.end();++it){
	    filesystem::remove(this->name+'.'+lexical_cast<std::string>(*it));
	}
    }
private:
    void open(){
        this->file.reset();
	if(this->current != this->ids.end()){
    	    this->file=in_place(this->name+'.'+lexical_cast<std::string>(*this->current));
	}
    }
    std::string const name;
    optional<File> file;
    typedef std::vector<unsigned int> ids_type;
    ids_type ids;
    ids_type::const_iterator current;
};




/*
 * 
 * old class (needs rewrite) that buffers log writes so the log itself only needs to be locked
 * on flush. useful only when 2 logs are interlaced into the same file?

template<class Log,class Lockable,std::size_t Size>
class olog_buffer{
public:
    typedef typename Log::id_type id_type;
    olog_buffer(Log &log,Lockable &lockable)
        : log(log), lockable(lockable){}
    template<class T>
    olog_buffer &operator<<(T const &t){
        static std::size_t const size=sizeof(id_type) + sizeof(T);
        BOOST_STATIC_ASSERT(size <= Size);
        id_type const id=this->log.template id<T>();    

        if(this->buffer.size() + size > this->buffer.max_size()) this->flush();
        this->buffer.push_back(reinterpret_cast<char const *>(&id),mpl::size_t<sizeof(id_type)>());
        this->buffer.push_back(reinterpret_cast<char const *>(&t),mpl::size_t<sizeof(T)>());
        return *this;
    }
    struct archive{
        explicit archive(olog_buffer &log) : log(log){}
        template<class T>
        archive &operator<<(T const &t){
            this->save_binary(&t,mpl::size_t<sizeof(T)>());
            return *this;
        }
        template<class T>
        archive &operator&(T const &t){ return this->operator<<(t); }
        template<class S>
        void save_binary(void const *data,S size){
            if(this->log.buffer.size() + size > this->log.buffer.max_size()){
                if(size > Size){
                    this->log.flush_and_write(data,size);
                    return;
                }else{
                    this->log.flush();
                }
            }
            this->log.buffer.push_back(static_cast<char const *>(data),size);
        }
        typedef mpl::true_ is_saving;
        typedef mpl::false_ is_loading;
    private:
        olog_buffer &log;
    };
private:
    friend struct archive;

    void flush(){
        if(!this->buffer.empty()){
            typename Log::archive ar(this->log);
            {
                lock_guard<Lockable> l(this->lockable);
                ar.save_binary(&this->buffer[0],this->buffer.size());
            }
            this->buffer.clear();
        }
    }
    template<class S>
    void flush_and_write(void const *data,S size){
        typename Log::archive ar(this->log);
        lock_guard<Lockable> l(this->lockable);
        if(!this->buffer.empty()){
            ar.save_binary(&this->buffer[0],this->buffer.size());
            this->buffer.clear();
        }
        ar.save_binary(data,size);
    }


    Log &log;
    Lockable &lockable;
    detail::embedded_vector<char,Size,false> buffer;
};

*/

  
}
}

#endif

