#ifdef USE_MSVC

#pragma warning (disable: 4355)
#pragma warning (disable: 4503)
#pragma warning (disable: 4786)

#endif

#include <cstddef>

#include "config.h"
#include "vector.h"
#include "matrix.h"

#ifdef NUMERICS_USE_INSTANT 

namespace numerics {

    namespace detail {

        NUMERICS_INLINE
        float real (const float &t) {
            return t;
        }
        NUMERICS_INLINE
        double real (const double &t) {
            return t;
        }

        NUMERICS_INLINE
        float imag (const float &t) {
            return 0;
        }
        NUMERICS_INLINE
        double imag (const double &t) {
            return 0;
        }

        NUMERICS_INLINE
        float conj (const float &t) {
            return t;
        }
        NUMERICS_INLINE
        double conj (const double &t) {
            return t;
        }

        NUMERICS_INLINE
        float sqrt (const float &t) {
#ifdef USE_MSVC
            return ::sqrt (t);
#else 
            return std::sqrt (t);
#endif 
        }
        NUMERICS_INLINE
        double sqrt (const double &t) {
#ifdef USE_MSVC
            return ::sqrt (t);
#else 
            return std::sqrt (t);
#endif 
        }

        NUMERICS_INLINE
        type_traits<float>::real_type abs (const float &t) {
#ifdef USE_MSVC
            return ::fabsf (t);
#else // USE_MSVC
            return std::fabs (t);
#endif // USE_MSVC
        }
        NUMERICS_INLINE
        type_traits<double>::real_type abs (const double &t) {
#ifdef USE_MSVC
            return ::fabs (t);
#else // USE_MSVC
            return std::fabs (t);
#endif // USE_MSVC
        }

        NUMERICS_INLINE
        type_traits<float>::real_type norm_1 (const float &t) {
            return abs (t);
        }
        NUMERICS_INLINE
        type_traits<double>::real_type norm_1 (const double &t) {
            return abs (t);
        }

        NUMERICS_INLINE
        type_traits<float>::real_type norm_2 (const float &t) {
            return abs (t);
        }
        NUMERICS_INLINE
        type_traits<double>::real_type norm_2 (const double &t) {
            return abs (t);
        }

        NUMERICS_INLINE
        type_traits<float>::real_type norm_inf (const float &t) {
            return abs (t);
        }
        NUMERICS_INLINE
        type_traits<double>::real_type norm_inf (const double &t) {
            return abs (t);
        }

    }

}

#endif // NUMERICS_USE_INSTANT
