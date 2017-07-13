#ifndef AMLIB_REPLICA_SEQUENCE_H_
#define AMLIB_REPLICA_SEQUENCE_H_

#include <type_traits>


namespace am {



/*****************************************************************************
 *
 *
 *
 *****************************************************************************/
template<class T>
class replica_sequence
{
public:
    //---------------------------------------------------------------
    using value_type = T;
    using reference = const value_type&;
    using pointer = value_type*;

    //---------------------------------------------------------------
    constexpr explicit
    replica_sequence(value_type value, std::size_t n):
        v_(std::move(value)), i_{n}
    {}


    //---------------------------------------------------------------
    const replica_sequence&
    begin() const noexcept {
        return *this;
    }
    //-----------------------------------------------------
    const replica_sequence&
    end() const noexcept {
        return *this;
    }

    //---------------------------------------------------------------
    bool operator != (const replica_sequence&) const noexcept {
        return (i_ > 0);
    }
    //-----------------------------------------------------
    replica_sequence&
    operator ++ () noexcept {
        --i_;
        return *this;
    }
    //-----------------------------------------------------
    const value_type& 
    operator * () const noexcept {
        return v_;
    }

private:
    value_type v_;
    std::size_t i_;
};




//-------------------------------------------------------------------
template<class T>
inline constexpr
replica_sequence<T>
replicas(T&& t, std::size_t n)
{
    return replica_sequence<typename std::decay<T>::type>
               {std::forward<T>(t), n};
}


}  // namespace am



#endif
