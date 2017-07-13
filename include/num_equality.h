/*****************************************************************************
 *
 * AM testing facilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_TEST_EQUALITY_H_
#define AMLIB_TEST_EQUALITY_H_


#include <cstdlib>
#include <limits>


namespace am {
namespace seq_detail {


/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class T>
struct tolerance {
    static constexpr T value() noexcept {
        return (T(100) * std::numeric_limits<T>::epsilon());
    }
};

//-------------------------------------------------------------------
template<class T>
constexpr T eps = tolerance<T>::value();



/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class T1, class T2>
inline constexpr bool
approx_equal(const T1& a, const T2& b)
{
    return ((eps<T1> < eps<T2>)
            ? ((a >= (b - eps<T2>)) && (a <= (b + eps<T2>)) )
            : ((b >= (a - eps<T1>)) && (b <= (a + eps<T1>)) )   );
}

//---------------------------------------------------------
template<class T1, class T2, class T3>
inline constexpr bool
approx_equal(const T1& a, const T2& b, const T3& tolerance)
{
    return ((a >= (b - tolerance)) &&
            (a <= (b + tolerance)) );
}


/*****************************************************************************
 *
 *
 *****************************************************************************/
template<class T1, class T2>
inline constexpr bool
abs_approx_equal(const T1& a, const T2& b)
{
    using std::abs;
    return approx_equal(abs(a), abs(b));
}

//---------------------------------------------------------
template<class T1, class T2, class T3>
inline constexpr bool
abs_approx_equal(const T1& a, const T2& b, const T3& tolerance)
{
    using std::abs;
    return approx_equal(abs(a), abs(b), tolerance);
}


}  // namespace seq_detail
}  // namespace am


#endif
