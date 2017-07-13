/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_NUMERIC_LINEAR_SEQUENCE_H_
#define AMLIB_NUMERIC_LINEAR_SEQUENCE_H_


#include <cassert>
#include <iterator>
#include <limits>
#include <type_traits>

#include "num_equality.h"


namespace am {


/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T>
class ascending_sequence
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
    ascending_sequence(
        value_type first = value_type(0),
        value_type uBound = value_type(0))
    :
        cur_{std::move(first)}, uBound_{std::move(uBound)}
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
       return cur_ + offset;
    }


    //---------------------------------------------------------------
    ascending_sequence&
    operator ++ () {
        ++cur_;
        return *this;
    }
    //-----------------------------------------------------
    ascending_sequence&
    operator += (size_type offset) {
        cur_ += offset;
        return *this;
    }
    //-----------------------------------------------------
    ascending_sequence
    operator + (size_type offset) const {
        auto res = *this;
        res += offset;
        return res;
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

    //---------------------------------------------------------------
    size_type
    size() const {
        return (1 + static_cast<size_type>(0.5 + (uBound_ - cur_)));
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return (cur_ > uBound_);
    }
    //-----------------------------------------------------
    explicit operator
    bool() const noexcept {
        return !empty();
    }


    //---------------------------------------------------------------
    const ascending_sequence&
    begin() const noexcept {
        return *this;
    }
    //-----------------------------------------------------
    ascending_sequence
    end() const {
        return ascending_sequence{(*this)[size()], uBound_};
    }


    //---------------------------------------------------------------
    friend difference_type
    distance(const ascending_sequence& a, const ascending_sequence& b) {
        return static_cast<difference_type>(b.cur_ - a.cur_);
    }


    //---------------------------------------------------------------
    bool
    operator == (const ascending_sequence& o) const noexcept {
        return seq_detail::approx_equal(cur_, o.cur_) &&
               seq_detail::approx_equal(uBound_, o.uBound_);
    }
    //-----------------------------------------------------
    bool
    operator != (const ascending_sequence& o) const noexcept {
        return !(*this == o);
    }


private:
    value_type cur_;
    value_type uBound_;
};








/*****************************************************************************
 *
 *
 *
 *
 *****************************************************************************/
template<class T>
class descending_sequence
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
    descending_sequence(
        value_type first = value_type(0),
        value_type uBound = value_type(0))
    :
        cur_{std::move(first)}, lBound_{std::move(uBound)}
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
       return cur_ - offset;
    }


    //---------------------------------------------------------------
    descending_sequence&
    operator ++ () {
        --cur_;
        return *this;
    }
    //-----------------------------------------------------
    descending_sequence&
    operator += (size_type offset) {
        cur_ -= offset;
        return *this;
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

    //---------------------------------------------------------------
    size_type
    size() const {
        return (1 + static_cast<size_type>(0.5 + (cur_ - lBound_)));
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return (cur_ < lBound_);
    }
    //-----------------------------------------------------
    explicit operator
    bool() const noexcept {
        return !empty();
    }


    //---------------------------------------------------------------
    const descending_sequence&
    begin() const {
        return *this;
    }
    //-----------------------------------------------------
    descending_sequence
    end() const {
        return descending_sequence{(*this)[size()], lBound_};
    }


    //---------------------------------------------------------------
    friend difference_type
    distance(const descending_sequence& a, const descending_sequence& b) {
        return static_cast<difference_type>(a.cur_ - b.cur_);
    }


    //---------------------------------------------------------------
    bool
    operator == (const descending_sequence& o) const noexcept {
        return seq_detail::approx_equal(cur_, o.cur_) && 
               seq_detail::approx_equal(lBound_, o.lBound_);
    }
    //-----------------------------------------------------
    bool
    operator != (const descending_sequence& o) const noexcept {
        return !(*this == o);
    }


private:
    value_type cur_;
    value_type lBound_;
};








/*****************************************************************************
 *
 *
 *
 *
 *****************************************************************************/
template<class T>
class linear_sequence
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
    linear_sequence(
        value_type first = value_type(0),
        value_type stride = value_type(1),
        value_type uBound  = std::numeric_limits<value_type>::max())
    :
        cur_{std::move(first)}, stride_{std::move(stride)},
        uBound_{std::move(uBound)}
    {}


    //---------------------------------------------------------------
    value_type
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
       return cur_ + (stride_ * offset);
    }


    //---------------------------------------------------------------
    linear_sequence&
    operator ++ () {
        cur_ += stride_;
        return *this;
    }
    //-----------------------------------------------------
    linear_sequence&
    operator += (size_type offset) {
        cur_ += stride_ * offset;
        return *this;
    }


    //---------------------------------------------------------------
    const value_type&
    stride() const noexcept {
        return stride_;
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
        return (1 + static_cast<size_type>(
            0.5 + ((uBound_ - cur_) / stride_)));
    }
    //-----------------------------------------------------
    bool
    empty() const noexcept {
        return ((stride_> 0) ? (cur_ > uBound_) : (cur_ < uBound_));
    }
    //-----------------------------------------------------
    explicit operator
    bool() const noexcept {
        return !empty();
    }


    //---------------------------------------------------------------
    const linear_sequence&
    begin() const {
        return *this;
    }
    //-----------------------------------------------------
    linear_sequence
    end() const {
        return linear_sequence{(*this)[size()], stride_, uBound_};
    }


    //---------------------------------------------------------------
    friend difference_type
    distance(const linear_sequence& a, const linear_sequence& b) {
        return static_cast<difference_type>((b.cur_ - a.cur_) / a.stride_);
    }


    //---------------------------------------------------------------
    bool
    operator == (const linear_sequence& o) const noexcept {
        return seq_detail::approx_equal(cur_, o.cur_) &&
               seq_detail::approx_equal(stride_, o.stride_) &&
               seq_detail::approx_equal(uBound_, o.uBound_);
    }
    //-----------------------------------------------------
    bool
    operator != (const linear_sequence& o) const noexcept {
        return !(*this == o);
    }


private:
    value_type cur_;
    value_type stride_;
    value_type uBound_;
};








/*****************************************************************************
 *
 *
 * NON-MEMBER BEGIN/END
 *
 *
 *****************************************************************************/
template<class T>
inline decltype(auto)
begin(const ascending_sequence<T>& s) {
    return s.begin();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cbegin(const ascending_sequence<T>& s) {
    return s.begin();
}

//-----------------------------------------------------
template<class T>
inline decltype(auto)
end(const ascending_sequence<T>& s) {
    return s.end();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cend(const ascending_sequence<T>& s) {
    return s.end();
}



//---------------------------------------------------------------
template<class T>
inline decltype(auto)
begin(const descending_sequence<T>& s) {
    return s.begin();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cbegin(const descending_sequence<T>& s) {
    return s.begin();
}

//-----------------------------------------------------
template<class T>
inline decltype(auto)
end(const descending_sequence<T>& s) {
    return s.end();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cend(const descending_sequence<T>& s) {
    return s.end();
}



//---------------------------------------------------------------
template<class T>
inline decltype(auto)
begin(const linear_sequence<T>& s) {
    return s.begin();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cbegin(const linear_sequence<T>& s) {
    return s.begin();
}

//-----------------------------------------------------
template<class T>
inline decltype(auto)
end(const linear_sequence<T>& s) {
    return s.end();
}
//-----------------------------------------------------
template<class T>
inline decltype(auto)
cend(const linear_sequence<T>& s) {
    return s.end();
}






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class First>
inline constexpr auto
make_ascending_sequence(First&& first)
{
    return ascending_sequence<std::decay_t<First>>{std::forward<First>(first)};
}

//---------------------------------------------------------
template<class First, class UpperBound>
inline constexpr auto
make_ascending_sequence(First&& first, UpperBound&& uBound)
{
    using num_t = std::common_type_t<std::decay_t<First>,
                                    std::decay_t<UpperBound>>;

    return ascending_sequence<num_t>{std::forward<First>(first),
                                     std::forward<UpperBound>(uBound)};
}



//-------------------------------------------------------------------
template<class First>
inline constexpr auto
make_descending_sequence(First&& first)
{
    return descending_sequence<std::decay_t<First>>
        {std::forward<First>(first)};
}

//---------------------------------------------------------
template<class First, class UpperBound>
inline constexpr auto
make_descending_sequence(First&& first, UpperBound&& uBound)
{
    using num_t = std::common_type_t<std::decay_t<First>,
                                    std::decay_t<UpperBound>>;

    return descending_sequence<num_t>{std::forward<First>(first),
                                      std::forward<UpperBound>(uBound)};
}



//-------------------------------------------------------------------
template<class First>
inline constexpr auto
make_linear_sequence(First&& first)
{
    return linear_sequence<std::decay_t<First>>{std::forward<First>(first)};
}

//---------------------------------------------------------
template<class First, class Stride>
inline constexpr auto
make_linear_sequence(First&& first, Stride&& stride)
{
    using num_t = std::common_type_t<std::decay_t<First>,
                                     std::decay_t<Stride>>;

    return linear_sequence<num_t>{std::forward<First>(first),
                                  std::forward<Stride>(stride)};
}

//---------------------------------------------------------
template<class First, class Stride, class UpperBound>
inline constexpr auto
make_linear_sequence(First&& first, Stride&& stride, UpperBound&& uBound)
{
    using num_t = std::common_type_t<std::decay_t<First>,
                                     std::decay_t<Stride>,
                                     std::decay_t<UpperBound>>;

    return linear_sequence<num_t> {std::forward<First>(first),
                                   std::forward<Stride>(stride),
                                   std::forward<UpperBound>(uBound) };
}


}  // namespace am



#endif
