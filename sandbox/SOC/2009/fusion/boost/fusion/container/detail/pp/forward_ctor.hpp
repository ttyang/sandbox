// Copyright Christopher Schmidt 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING
#   ifndef BOOST_FUSION_SEQ_NAME
#       ifndef BOOST_FUSION_CONTAINER_DETAIL_PP_FORWARD_CTOR_HPP
#           include <boost/fusion/support/template.hpp>

#           include <boost/config.hpp>
#           include <boost/preprocessor/iterate.hpp>
#           include <boost/preprocessor/repetition/enum_params.hpp>
#           include <boost/preprocessor/repetition/enum_binary_params.hpp>
#       endif
#   else
#       define BOOST_PP_FILENAME_1 <boost/fusion/container/detail/pp/forward_ctor.hpp>
#       define BOOST_PP_ITERATION_LIMITS (1, BOOST_FUSION_MAX_SEQ_SIZE)
#       include BOOST_PP_ITERATE()

#       ifdef BOOST_NO_RVALUE_REFERENCES
    template<typename SeqAssign>
    BOOST_FUSION_SEQ_NAME(SeqAssign const& seq_assign)
#       ifdef BOOST_FUSION_USE_BASE_TYPE
      : base_type(seq_assign)
#       else
      : data(seq_assign)
#       endif
    {}
#       endif
#   endif

#else

#   define N BOOST_PP_ITERATION()

#   ifndef BOOST_NO_RVALUE_REFERENCES
    VARIADIC_TEMPLATE_A(N)
#   endif
#   if N == 1
    explicit
#   endif
#   ifdef BOOST_NO_RVALUE_REFERENCES
    BOOST_FUSION_SEQ_NAME(EXPAND_TEMPLATE_ARGUMENTS_CALL_PARAMS(N))
#       ifdef BOOST_FUSION_USE_BASE_TYPE
      : base_type(EXPAND_PARAMETERS(N))
#       else
      : data(EXPAND_PARAMETERS(N))
#       endif
    {}
#   else
    BOOST_FUSION_SEQ_NAME(EXPAND_TEMPLATE_ARGUMENTS_A(N))
#       ifdef BOOST_FUSION_USE_BASE_TYPE
      : base_type(EXPAND_PARAMETERS_A(N))
#       else
      : data(EXPAND_PARAMETERS_A(N))
#       endif
    {}
#   endif

#   undef N
#endif // defined(BOOST_PP_IS_ITERATING)
