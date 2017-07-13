/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "fibonacci.h"

#include <vector>
#include <iostream>


//-------------------------------------------------------------------
void fibonacci_sequence_generation()
{
    {
        auto v = std::vector<double>{};
        for(auto x : am::fibonacci_sequence<int>{15}) {
            v.push_back(x);
        }
        if( v.size() != 15 ||
            v[0] != 0 || v[1] != 1 || v[2] != 1 || v[3] != 2 ||
            v[4] != 3 || v[5] != 5 || v[6] != 8 || v[7] != 13 ||
            v[8] != 21 || v[9] != 34 || v[10] != 55 || v[11] != 89 ||
            v[12] != 144 || v[13] != 233 || v[14] != 377)
        {
            throw std::logic_error("fibonacci_sequence");
        }

    }

}



//-------------------------------------------------------------------
int main()
{
    try {
        fibonacci_sequence_generation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}


