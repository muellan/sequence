/*****************************************************************************
 *
 * AM numeric facilities
 *
 * released under MIT license
 *
 *2008-2014  André Müller
 *
 *****************************************************************************/

#ifndef AMLIB_NUMERIC_COMBINED_SEQUENCE_H_
#define AMLIB_NUMERIC_COMBINED_SEQUENCE_H_


#include <cstdint>
#include <type_traits>
#include <cmath>


namespace am {

/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<
    class Sequence1,
    class Sequence2 = Sequence1
>
class combined_sequence
{
public:
    //---------------------------------------------------------------
    using first_sequence_type = Sequence1;
    using second_sequence_type = Sequence2;
    //-----------------------------------------------------
    using iterator_category = std::input_iterator_tag;
    //-----------------------------------------------------
    using difference_type = std::common_type_t<
        typename first_sequence_type::difference_type,
        typename second_sequence_type::difference_type>;
    //-----------------------------------------------------
    using size_type = std::common_type_t<
        typename first_sequence_type::size_type,
        typename second_sequence_type::size_type>;
    //-----------------------------------------------------
    using value_type = std::common_type_t<
        typename first_sequence_type::value_type,
        typename second_sequence_type::value_type>;
    //-----------------------------------------------------
    using reference = const value_type&;
    using pointer = value_type*;


    //---------------------------------------------------------------
    combined_sequence() = default;

    //---------------------------------------------------------------
    constexpr explicit
    combined_sequence(first_sequence_type fst, second_sequence_type snd) :
        fstSequ_{std::move(fst)}, sndSequ_{std::move(snd)}
    {}


    //---------------------------------------------------------------
    value_type
    operator * () const
    {
        return fstSequ_.empty() ? *sndSequ_ : *fstSequ_;
    }
    //-----------------------------------------------------
    auto
    operator -> () const {
        return fstSequ_.emtpy() ?
            std::addressof(*sndSequ_) :
            std::addressof(*fstSequ_);
    }
    //-----------------------------------------------------
    value_type
    operator [] (size_type offset) const
    {
        const auto nfst = fstSequ_.size();
        if(offset >= nfst) {
            return sndSequ_[offset-nfst];
        }
        return fstSequ_[offset];
    }


    //---------------------------------------------------------------
    combined_sequence&
    operator ++ ()
    {
        if(!fstSequ_.empty()) {
            ++fstSequ_;
        }
        else if(!sndSequ_.empty()){
            ++sndSequ_;
        }
        return *this;
    }
    //-----------------------------------------------------
    combined_sequence&
    operator += (size_type offset)
    {
        if(!fstSequ_.empty()) {
            const auto nfst = fstSequ_.size();

            if(offset < nfst) {
                fstSequ_ += offset;
            }
            else {
                fstSequ_ += nfst;
                sndSequ_ += offset - nfst;
            }
        }
        else if(!sndSequ_.empty()){
            sndSequ_ += offset;
        }
        return *this;
    }
    //-----------------------------------------------------
    combined_sequence
    operator + (size_type offset) const {
        auto res = *this;
        res += offset;
        return res;
    }


    //---------------------------------------------------------------
    value_type
    front() const {
        return fstSequ_.emtpy() ? sndSequ_.front() : fstSequ_.front();
    }
    //-----------------------------------------------------
    value_type
    back() const {
        return sndSequ_.back();
    }
    //-----------------------------------------------------
    size_type
    size() const {
        return fstSequ_.size() + sndSequ_.size();
    }
    //-----------------------------------------------------
    bool
    empty() const {
        return fstSequ_.empty() && sndSequ_.empty();
    }
    //-----------------------------------------------------
    explicit operator
    bool() const {
        return !empty();
    }


    //---------------------------------------------------------------
    const combined_sequence&
    begin() const {
        return *this;
    }
    //-----------------------------------------------------
    combined_sequence
    end() const {
        return combined_sequence{fstSequ_.end(), sndSequ_.end()};
    }


    //---------------------------------------------------------------
    bool
    operator == (const combined_sequence& o) const {
        return (fstSequ_ == o.fstSequ_) &&
               (sndSequ_ == o.sndSequ_);
    }
    //-----------------------------------------------------
    bool
    operator != (const combined_sequence& o) const {
        return !(*this == o);
    }


private:
    //---------------------------------------------------------------
    first_sequence_type fstSequ_;
    second_sequence_type sndSequ_;
};








/*****************************************************************************
 *
 *
 * NON-MEMBER BEGIN/END
 *
 *
 *****************************************************************************/
template<class S1, class S2>
inline decltype(auto)
begin(const combined_sequence<S1,S2>& s) {
    return s.begin();
}
//-----------------------------------------------------
template<class S1, class S2>
inline decltype(auto)
cbegin(const combined_sequence<S1,S2>& s) {
    return s.begin();
}

//-----------------------------------------------------
template<class S1, class S2>
inline decltype(auto)
end(const combined_sequence<S1,S2>& s) {
    return s.end();
}
//-----------------------------------------------------
template<class S1, class S2>
inline decltype(auto)
cend(const combined_sequence<S1,S2>& s) {
    return s.end();
}








/*****************************************************************************
 *
 * 
 *
 *****************************************************************************/
template<class S1, class S2> 
//requires Sequence<S1> && Sequence<S2>
inline constexpr auto
make_combined_sequence(S1&& s1, S2&& s2)
{
    return combined_sequence<std::decay_t<S1>,std::decay_t<S2>> 
                {std::forward<S1>(s1), std::forward<S2>(s2)};
}


} //namespace am

#endif
