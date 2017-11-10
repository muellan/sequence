/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2017 André Müller
 *
 *****************************************************************************/
#include "interleaved_bits.h"

#include <iostream>



//-------------------------------------------------------------------
template<class PatternGen>
std::int_least64_t
true_count(PatternGen gen, std::uint_least64_t maxSteps = 100000000)
{
    const auto orig = gen;

    std::uint_fast64_t count = 0;

//    std::cout << "-----------------" << std::endl;
//    std::cout << "s " << gen.size() << std::endl;
//    std::cout << "? " << bool(gen) << std::endl;
//    std::cout << "e " << gen.empty() << std::endl;
//    std::cout << "t " << gen.trues() << std::endl;

    for(std::uint_fast64_t i = 0; (i < maxSteps) && gen; ++i, ++gen) {
        if(*gen) ++count;
        if(*gen != orig[i]) return -1;
        if(*gen != *(orig + i)) return -1;
    }

//    std::cout << "# " << count << std::endl;

    return (count == orig.count() ? count : -1);
}


//-------------------------------------------------------------------
void test_true_count()
{
    using am::offset_interleaved_bit_sequence;

    if((true_count(offset_interleaved_bit_sequence{1,0,0}) != 1) ||
       (true_count(offset_interleaved_bit_sequence{1,100,0}) != 1) ||
       (true_count(offset_interleaved_bit_sequence{1,100,10000}) != 1) ||
       (true_count(offset_interleaved_bit_sequence{1,0,10000}) != 1) ||

       (true_count(offset_interleaved_bit_sequence{2,0,0}) != 2) ||
       (true_count(offset_interleaved_bit_sequence{2,98,0}) != 2) ||
       (true_count(offset_interleaved_bit_sequence{2,98,10000}) != 2) ||
       (true_count(offset_interleaved_bit_sequence{2,0,10000}) != 2) ||

       (true_count(offset_interleaved_bit_sequence{10,0,0}) != 10) ||
       (true_count(offset_interleaved_bit_sequence{10,98,0}) != 10) ||
       (true_count(offset_interleaved_bit_sequence{10,98,10000}) != 10) ||
       (true_count(offset_interleaved_bit_sequence{10,0,10000}) != 10) ||

       (true_count(offset_interleaved_bit_sequence{99,0,0}) != 99) ||
       (true_count(offset_interleaved_bit_sequence{99,18,0}) != 99) ||
       (true_count(offset_interleaved_bit_sequence{99,18,123}) != 99) ||
       (true_count(offset_interleaved_bit_sequence{99,0,123}) != 99) )
    {
        throw std::logic_error(
            "offset_interleaved_bit_sequence: wrong true count");
    }

}



//-------------------------------------------------------------------
int main()
{
    try {
        test_true_count();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}
