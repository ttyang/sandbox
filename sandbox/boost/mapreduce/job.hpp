// Boost.MapReduce library
//
//  Copyright (C) 2009 Craig Henderson.
//  cdm.henderson@googlemail.com
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/mapreduce/
//

#ifndef BOOST_MAPREDUCE_JOB_HPP
#define BOOST_MAPREDUCE_JOB_HPP

namespace boost {

namespace mapreduce {

template<typename T> size_t length(T const &str);

template<typename MapKey, typename MapValue>
class map_task
{
  public:
    typedef MapKey   key_type;
    typedef MapValue value_type;             
};

template<typename ReduceKey, typename ReduceValue>
class reduce_task
{
  public:
    typedef ReduceKey   key_type;
    typedef ReduceValue value_type;
};

template<typename MapTask,
         typename ReduceTask,
         typename Combiner=null_combiner,
         typename Datasource=datasource::directory_iterator<MapTask>,
         typename IntermediateStore=intermediates::in_memory<MapTask, ReduceTask>,
         typename StoreResult=typename IntermediateStore::store_result_type>
class job : private boost::noncopyable
{
  public:
    typedef MapTask                 map_task_type;
    typedef ReduceTask              reduce_task_type;
    typedef Datasource              datasource_type;
    typedef IntermediateStore       intermediate_store_type;
    typedef Combiner                combiner_type;

    typedef
    typename intermediate_store_type::const_result_iterator
    const_result_iterator;

    typedef
    typename intermediate_store_type::keyvalue_t
    keyvalue_t;

  public:
    class map_task_runner : boost::noncopyable
    {
      public:
        map_task_runner(job &j)
          : job_(j),
            intermediate_store_(job_.number_of_partitions())
        {
        }

        // 'value' parameter is not a reference to const to enable streams to be passed
        map_task_runner &operator()(typename map_task_type::key_type const &key,
                                    typename map_task_type::value_type     &value)
        {
            map_task_type::map(*this, key, value);

            // consolidating map intermediate results can save network time by
            // aggregating the mapped valued at mapper
            combiner_type::run(intermediate_store_);

            return *this;
        }

        bool const emit_intermediate(typename reduce_task_type::key_type   const &key,
                                     typename reduce_task_type::value_type const &value)
        {
            return intermediate_store_.insert(key, value);
        }

        intermediate_store_type &intermediate_store(void)
        {
            return intermediate_store_;
        }

      private:
        job                     &job_;
        intermediate_store_type  intermediate_store_;
    };

    class reduce_task_runner : boost::noncopyable
    {
      public:
        reduce_task_runner(
            std::string       const &output_filespec,
            unsigned          const &partition,
            unsigned          const  num_partitions,
            intermediate_store_type &intermediate_store,
            results                 &result)
          : partition_(partition),
            result_(result),
            intermediate_store_(intermediate_store),
            store_result_(output_filespec, partition, num_partitions)
        {
        }

        void reduce(void)
        {
            intermediate_store_.reduce(partition_, *this);
        }

        void emit(typename reduce_task_type::key_type   const &key,
                  typename reduce_task_type::value_type const &value)
        {
            intermediate_store_.insert(key, value, store_result_);
        }

        template<typename It>
        void operator()(typename reduce_task_type::key_type const &key, It it, It ite)
        {
            ++result_.counters.reduce_keys_executed;
            reduce_task_type::reduce(*this, key, it, ite);
            ++result_.counters.reduce_keys_completed;
        }

      private:
        unsigned const          &partition_;
        results                 &result_;
        intermediate_store_type &intermediate_store_;
        StoreResult              store_result_;
    };

    job(datasource_type &datasource, specification const &spec)
      : datasource_(datasource),
        specification_(spec),
        intermediate_store_(specification_.reduce_tasks)
     {
     }

    const_result_iterator begin_results(void) const
    {
        return intermediate_store_.begin_results();
    }

    const_result_iterator end_results(void) const
    {
        return intermediate_store_.end_results();
    }

    bool const get_next_map_key(void *&key)
    {
        std::auto_ptr<typename map_task_type::key_type> next_key(new typename map_task_type::key_type);
        if (!datasource_.setup_key(*next_key))
            return false;
        key = next_key.release();
        return true;
    }

    template<typename SchedulePolicy>
    void run(results &result)
    {
        SchedulePolicy schedule;
        this->run(schedule, result);
    }

    template<typename SchedulePolicy>
    void run(SchedulePolicy &schedule, results &result)
    {
        using namespace boost::posix_time;
        ptime start_time(microsec_clock::universal_time());
        schedule(*this, result);
        result.job_runtime = microsec_clock::universal_time() - start_time;
    }

    template<typename Sync>
    bool const run_map_task(void *key, results &result, Sync &sync)
    {
        using namespace boost::posix_time;
        ptime start_time(microsec_clock::universal_time());

        bool success = true;
        try
        {
            ++result.counters.map_keys_executed;

            std::auto_ptr<typename map_task_type::key_type>
                map_key_ptr(
                    reinterpret_cast<
                        typename map_task_type::key_type *>(key));

            typename map_task_type::key_type &map_key = *map_key_ptr;

            // get the data
            typename map_task_type::value_type value;
            if (!datasource_.get_data(map_key, value))
            {
                ++result.counters.map_key_errors;
                return false;
            }

            // Map Task
            if (map_key == typename map_task_type::key_type()
            ||  value == typename map_task_type::value_type())
            {
                BOOST_ASSERT(map_key != typename map_task_type::key_type());
                BOOST_ASSERT(value != typename map_task_type::value_type());
                ++result.counters.map_key_errors;
                return false;
            }

            map_task_runner runner(*this);
            runner(map_key, value);

            // merge the map task intermediate results into the job
            sync.lock();
            intermediate_store_.merge_from(runner.intermediate_store());
            sync.unlock();

            ++result.counters.map_keys_completed;
        }
        catch (std::exception &)
        {
            ++result.counters.map_key_errors;
            success = false;
        }
        result.map_times.push_back(microsec_clock::universal_time() - start_time);

        return success;
    }

    unsigned const number_of_partitions(void) const
    {
        return specification_.reduce_tasks;
    }

    unsigned const number_of_map_tasks(void) const
    {
        return specification_.map_tasks;
    }

    bool const run_reduce_task(unsigned const partition, results &result)
    {
        bool success = true;

        using namespace boost::posix_time;
        ptime start_time(microsec_clock::universal_time());
        try
        {
            reduce_task_runner runner(
                specification_.output_filespec,
                partition,
                number_of_partitions(),
                intermediate_store_,
                result);
            runner.reduce();
        }
        catch (std::exception &e)
        {
            std::cerr << "\nError: " << e.what() << "\n";
            ++result.counters.reduce_key_errors;
            success = false;
        }
        
        result.reduce_times.push_back(microsec_clock::universal_time()-start_time);

        return success;
    }

  private:
    datasource_type         &datasource_;
    specification     const &specification_;
    intermediate_store_type  intermediate_store_;
};

template<>
inline size_t length(std::string const &str)
{
    return str.length();
}

}   // namespace mapreduce

}   // namespace boost

#endif  // BOOST_MAPREDUCE_JOB_HPP
