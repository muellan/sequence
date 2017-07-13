/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_NUMERIC_GEOEMETRIC_SEQUENCE_H_
#define AMLIB_NUMERIC_GEOEMETRIC_SEQUENCE_H_

#include <cmath>
#include <iterator>
#include <type_traits>
#include <limits>

#include "num_equality.h"


namespace am {


/*****************************************************************************
 *
 * v(n) = scale * ratio^n,  for scale > 1, n with v(n) <= bound
 * v(n) = scale * ratio^n,  for scale < 1, n with v(n) >= bound
 *
 *
 *****************************************************************************/
template<class T>
class geometric_sequence
{
public:
    //---------------------------------------------------------------
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    //-----------------------------------------------------
    using value_type = T;
    using reference = const value_type&;
    using pointer = value_type*;


    //---------------------------------------------------------------
    constexpr explicit
    geometric_sequence(value_type initial = value_type(0),
                       value_type ratio = value_type(1),
                       value_type bound = std::numeric_limits<value_type>::max())
    :
        cur_{std::move(initial)},
        ratio_{std::move(ratio)},
        bound_{std::move(bound)}
    {}


    //---------------------------------------------------------------
    const value_type&
    operator * () const noexcept {
        return cur_;
    }
    //-----------------------------------------------------
    const value_type*
    operator -> () const noexcept {
        return std::addressof(cur_);
    }
    //-----------------------------------------------------
    value_type
    operator [] (size_type offset) const {
       using std::pow;
       return cur_ * pow(ratio_,offset);
    }


    //---------------------------------------------------------------
    geometric_sequence&
    operator ++ () {
        cur_ *= ratio_;
        return *this;
    }
    //-----------------------------------------------------
    geometric_sequence&
    operator += (size_type offset) {
        using std::pow;
        cur_ *= pow(ratio_,offset);
        return *this;
    }
    //-----------------------------------------------------
    geometric_sequence
    operator + (size_type offset) const {
        auto res = *this;
        res += offset;
        return res;
    }


    //---------------------------------------------------------------
    const value_type&
    ratio() const noexcept {
        return ratio_;
    }


    //---------------------------------------------------------------
    const value_type&
    front() const noexcept {
        return cur_;
    }
    //-----------------------------------------------------
    value_type
    back() const {
        return (*this)[size()-1];
    }
    //-----------------------------------------------------
    size_type
    size() const {
        using std::log;

        return (1 + static_cast<size_type>(
            0.5 + (log(bound_/cur_) / log(ratio_)) ) );
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return
            (cur_ >= 0 && bound_ >= 0)
            ? (ratio_ > 1) ? (cur_ > bound_) : (cur_ < bound_)
            : (ratio_ > 1) ? (cur_ < bound_) : (cur_ > bound_);
    }
    //-----------------------------------------------------
    explicit operator
    bool() const noexcept {
        return !empty();
    }


    //---------------------------------------------------------------
    const geometric_sequence&
    begin() const noexcept {
        return *this;
    }
    //-----------------------------------------------------
    geometric_sequence
    end() const {
        return geometric_sequence{(*this)[size()], ratio_, bound_};
    }


    //---------------------------------------------------------------
    friend difference_type
    distance(const geometric_sequence& a, const geometric_sequence& b)
    {
        using std::log;

        return (static_cast<difference_type>(
            0.5 + (log(b.cur_/a.cur_) / log(a.ratio_)) ) );
    }


    //---------------------------------------------------------------
    bool
    operator == (const geometric_sequence& o) const noexcept {
        return
            seq_detail::approx_equal(cur_, o.cur_) &&
            seq_detail::approx_equal(ratio_, o.ratio_) &&
            seq_detail::approx_equal(bound_, o.bound_);
    }
    //-----------------------------------------------------
    bool
    operator != (const geometric_sequence& o) const noexcept {
        return !(*this == o);
    }


private:
    value_type cur_;
    value_type ratio_;
    value_type bound_;
};








/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T>
inline decltype(auto)
begin(const geometric_sequence<T>& s) {
    return s.begin();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cbegin(const geometric_sequence<T>& s) {
    return s.begin();
}

//-----------------------------------------------------
template<class T>
inline decltype(auto)
end(const geometric_sequence<T>& s) {
    return s.end();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cend(const geometric_sequence<T>& s) {
    return s.end();
}








/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class Initial, class Ratio, class Bound>
inline constexpr auto
make_geometric_sequence(Initial&& initial, Ratio&& ratio, Bound&& bound)
{
    using num_t = std::common_type_t<std::decay_t<Initial>,
                                     std::decay_t<Bound>,
                                     std::decay_t<Ratio>>;

    return geometric_sequence<num_t>{std::forward<Initial>(initial),
                                     std::forward<Ratio>(ratio),
                                     std::forward<Bound>(bound)};
}


}  // namespace am

#endif
