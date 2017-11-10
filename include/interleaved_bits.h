#ifndef AMLIB_SEQUENCE_INTERLEAVED_BITS_H_
#define AMLIB_SEQUENCE_INTERLEAVED_BITS_H_

#include <cstdint>


namespace am {


/*************************************************************************//***
 *
 * @brief
 *
 *****************************************************************************/
class offset_interleaved_bit_sequence
{
public:
    //---------------------------------------------------------------
    using size_type  = std::uint_least64_t;
    //-----------------------------------------------------
    using value_type = bool;
    using reference = const value_type&;
    using pointer = value_type*;


    //---------------------------------------------------------------
    constexpr
    offset_interleaved_bit_sequence() noexcept :
        next_{0}, size_{0}, interleave_{1}
    {}
    //-----------------------------------------------------
    explicit constexpr
    offset_interleaved_bit_sequence(
        size_type trues,
        size_type interleave = 0,
        size_type offset = 0) noexcept
    :
        next_{ trues < 1 ? 0 : (1 + ((trues-1) * (interleave + 1))) }
        ,
        size_{(offset > 0 ? offset-1 : 0) +
              (trues < 1 ? 0 : (1 + ((trues-1) * (interleave + 1))))}
        ,
        interleave_{interleave + 1}
    {}


    //---------------------------------------------------------------
    constexpr size_type
    size() const noexcept {
        return size_;
    }

    //-----------------------------------------------------
    constexpr size_type
    count() const noexcept {
        return size_ > 1
            ? (next_ > 1
                ? size_type(interleave_ > 1 ? 1 : 0) + (next_ / interleave_)
                : size_type(1))
            : size_type(size_ == 1 ? 1 : 0);
    }

    //-----------------------------------------------------
    constexpr bool
    any() const noexcept {
        return (count() > size_type(0));
    }
    //-----------------------------------------------------
    constexpr bool
    none() const noexcept {
        return !any();
    }
    //-----------------------------------------------------
    constexpr bool
    all() const noexcept {
        return (size_ == next_) && (interleave_ == size_type(1));
    }

    //-----------------------------------------------------
    constexpr size_type
    next_after() const noexcept {
        return (size_ - next_);
    }
    //-----------------------------------------------------
    constexpr size_type
    interleave() const noexcept {
        return interleave_ - 1;
    }

    //-----------------------------------------------------
    constexpr explicit
    operator bool() const noexcept {
        return !empty();
    }
    //-----------------------------------------------------
    constexpr bool
    empty() const noexcept {
        return (size_ < size_type(1));
    }


    //---------------------------------------------------------------
    constexpr bool
    operator * () const noexcept {
        return !empty() && (size_ == next_);
    }

    //-----------------------------------------------------
    offset_interleaved_bit_sequence&
    operator ++ () noexcept {
        if(!empty()) {
            --size_;
            if(size_ < next_) {
                if(next_ > interleave_) next_ -= interleave_; else next_ = 0;
            }
        }
        return *this;
    }

    //-----------------------------------------------------
    offset_interleaved_bit_sequence&
    operator += (size_type offset) noexcept {
        const auto d = next_after();
        size_ -= offset;
        if(offset > d) {
            next_ = interleave_ * ((size_ - 1) / interleave_) + 1;
        }
        return *this;
    }

    //-----------------------------------------------------
    offset_interleaved_bit_sequence
    operator + (size_type offset) const noexcept {
        auto res = *this;
        res += offset;
        return res;
    }

    //-----------------------------------------------------
    constexpr bool
    operator [] (size_type offset) const noexcept {
        return (offset >= size_ || offset < next_after())
               ? false
               : !((size_ - offset - 1) % interleave_);
    }

    //-----------------------------------------------------
    constexpr bool
    front() const noexcept {
        return *(*this);
    }
    //-----------------------------------------------------
    bool
    back() const noexcept {
        return !empty();
    }


    //---------------------------------------------------------------
    constexpr const offset_interleaved_bit_sequence&
    begin() const noexcept {
        return *this;
    }
    //-----------------------------------------------------
    constexpr offset_interleaved_bit_sequence
    end() const noexcept {
        return offset_interleaved_bit_sequence
                   {size_type(0), size_type(0), interleave_};
    }


    //---------------------------------------------------------------
    inline friend bool
    operator == (const offset_interleaved_bit_sequence& a,
                 const offset_interleaved_bit_sequence& b)
    {
        return ((a.next_ == b.next_) &&
                (a.size_ == b.size_) &&
                (a.interleave_ == b.interleave_));
    }
    //-----------------------------------------------------
    inline friend bool
    operator != (const offset_interleaved_bit_sequence& a,
                 const offset_interleaved_bit_sequence& b)
    {
        return !(a == b);
    }


private:
    //---------------------------------------------------------------
    size_type next_;
    size_type size_;
    size_type interleave_;
};






/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
inline decltype(auto)
begin(const offset_interleaved_bit_sequence& s)
{
    return s.begin();
}

//---------------------------------------------------------
inline decltype(auto)
end(const offset_interleaved_bit_sequence& s)
{
    return s.end();
}


}  // namespace am


#endif
