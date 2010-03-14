//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Justin E. Gottchlich 2009.
// (C) Copyright Vicente J. Botet Escriba 2009.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/stm for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_SYNCHRO_SYNCHRONIZED__HPP
#define BOOST_SYNCHRO_SYNCHRONIZED__HPP

namespace boost { namespace synchro { namespace detail {
    inline bool no_opt_false() {return false;}
}}}

#define BOOST_SYNCHRO_SYNCHRONIZE_EXT(VAR_DECL) \
    if (bool __stop = boost::synchro::detail::no_opt_false()) {} else   \
    for (VAR_DECL;!__stop; __stop= true)

#define BOOST_SYNCHRO_SYNCHRONIZE_TYPE(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE))

#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_TYPE(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::adopt_lock))
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE_TYPE(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::defer_lock))
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::try_to_lock))
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_UNTIL(TYPE, VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, ABS_TIME))
#define BOOST_SYNCHRO_SYNCHRONIZE_TYPE_UNTIL(TYPE, VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(ABS_TIME, LOCKABLE))

#define BOOST_SYNCHRO_SYNCHRONIZE_VAR(VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_TYPE(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR(VAR, LOCKABLE) \
    BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_TYPE(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR(VAR, LOCKABLE) \
    BOOST_SYNCHRO_DEFER_SYNCHRONIZE_TYPE(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR(VAR, LOCKABLE) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL(VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_TYPE_UNTIL(boost::mutex, VAR, LOCKABLE, ABS_TIME)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL(VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_UNTIL(boost::mutex, VAR, LOCKABLE, ABS_TIME)

#define BOOST_SYNCHRO_SYNCHRONIZE(LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_VAR(_, LOCKABLE)
#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE(LOCKABLE) \
    BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR(_, LOCKABLE)
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE(LOCKABLE) \
    BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR(_, LOCKABLE)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE(LOCKABLE) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR(_, LOCKABLE)
#define BOOST_SYNCHRO_SYNCHRONIZE_UNTIL(LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL(_, LOCKABLE, ABS_TIME)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_UNTIL(LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL(_, LOCKABLE, ABS_TIME)

#define synchronize(LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE(LOCKABLE)
#define adopt_synchronize(LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE(LOCKABLE)
#define defer_synchronize(LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE(LOCKABLE)
#define try_to_synchronize(LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE(LOCKABLE)
#define try_to_synchronize_until(LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_UNTIL(LOCKABLE, ABS_TIME)
#define synchronize_until(LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_UNTIL(LOCKABLE, ABS_TIME)

#define synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE_VAR(VAR, LOCKABLE)
#define adopt_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR(VAR, LOCKABLE)
#define defer_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR(VAR, LOCKABLE)
#define try_to_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR(VAR, LOCKABLE)
#define try_to_synchronize_var_until(VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL(VAR, LOCKABLE, ABS_TIME)
#define synchronize_var_until(VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL(VAR, ABS_TIME, LOCKABLE)

#define synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE_TYPE(TYPE, VAR, LOCKABLE)
#define adopt_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR(TYPE, VAR, LOCKABLE)
#define defer_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR(TYPE, VAR, LOCKABLE)
#define try_to_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR(TYPE, VAR, LOCKABLE)
#define try_to_synchronize_type_until(TYPE, VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL(TYPE, VAR, LOCKABLE, ABS_TIME)
#define synchronize_type_until(TYPE, VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL(TYPE, VAR, ABS_TIME, LOCKABLE)


#define BOOST_SYNCHRO_SYNCHRONIZE_TYPE_NAMED(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, __call_context, ##LOCKABLE))

#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_TYPE_NAMED(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT_NAMED(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::adopt_lock, __call_context, ##LOCKABLE))
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE_TYPE_NAMED(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT_NAMED(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::defer_lock, __call_context, ##LOCKABLE))
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_NAMED(TYPE, VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT_NAMED(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, boost::synchro::try_to_lock, __call_context, ##LOCKABLE))
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_UNTIL_NAMED(TYPE, VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT_NAMED(boost::synchro::unique_lock<TYPE> VAR(LOCKABLE, ABS_TIME, __call_context, ##LOCKABLE))
#define BOOST_SYNCHRO_SYNCHRONIZE_TYPE_UNTIL_NAMED(TYPE, VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_EXT_NAMED(boost::synchro::unique_lock<TYPE> VAR(ABS_TIME, LOCKABLE, __call_context, ##LOCKABLE))

#define BOOST_SYNCHRO_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_TYPE_NAMED(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE) \
    BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_TYPE_NAMED(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE) \
    BOOST_SYNCHRO_DEFER_SYNCHRONIZE_TYPE_NAMED(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_NAMED(boost::mutex, VAR, LOCKABLE)
#define BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL_NAMED(VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_TYPE_UNTIL_NAMED(boost::mutex, VAR, LOCKABLE, ABS_TIME)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL_NAMED(VAR, LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_TYPE_UNTIL_NAMED(boost::mutex, VAR, LOCKABLE, ABS_TIME)

#define BOOST_SYNCHRO_SYNCHRONIZE_NAMED(LOCKABLE) \
    BOOST_SYNCHRO_SYNCHRONIZE_VAR_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE)
#define BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_NAMED(LOCKABLE) \
    BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE)
#define BOOST_SYNCHRO_DEFER_SYNCHRONIZE_NAMED(LOCKABLE) \
    BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_NAMED(LOCKABLE) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE)
#define BOOST_SYNCHRO_SYNCHRONIZE_UNTIL_NAMED(LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE, ABS_TIME)
#define BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_UNTIL_NAMED(LOCKABLE, ABS_TIME) \
    BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL_NAMED(BOOST_JOIN(_,__LINE__), LOCKABLE, ABS_TIME)

#define named_synchronize(LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE_NAMED(LOCKABLE)
#define named_adopt_synchronize(LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_NAMED(LOCKABLE)
#define named_defer_synchronize(LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE_NAMED(LOCKABLE)
#define named_try_to_synchronize(LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_NAMED(LOCKABLE)
#define named_try_to_synchronize_until(LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_UNTIL_NAMED(LOCKABLE, ABS_TIME)
#define named_synchronize_until(LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_UNTIL_NAMED(LOCKABLE, ABS_TIME)

#define named_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE)
#define named_adopt_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE)
#define named_defer_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE)
#define named_try_to_synchronize_var(VAR, LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_NAMED(VAR, LOCKABLE)
#define named_try_to_synchronize_var_until(VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL_NAMED(VAR, LOCKABLE, ABS_TIME)
#define named_synchronize_var_until(VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL_NAMED(VAR, ABS_TIME, LOCKABLE)

#define named_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_SYNCHRONIZE_TYPE_NAMED(TYPE, VAR, LOCKABLE)
#define named_adopt_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_ADOPT_SYNCHRONIZE_VAR_NAMED(TYPE, VAR, LOCKABLE)
#define named_defer_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_DEFER_SYNCHRONIZE_VAR_NAMED(TYPE, VAR, LOCKABLE)
#define named_try_to_synchronize_type(TYPE, VAR, LOCKABLE) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_NAMED(TYPE, VAR, LOCKABLE)
#define named_try_to_synchronize_type_until(TYPE, VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_TRY_TO_SYNCHRONIZE_VAR_UNTIL_NAMED(TYPE, VAR, LOCKABLE, ABS_TIME)
#define named_synchronize_type_until(TYPE, VAR, LOCKABLE, ABS_TIME) BOOST_SYNCHRO_SYNCHRONIZE_VAR_UNTIL_NAMED(TYPE, VAR, ABS_TIME, LOCKABLE)


#endif
