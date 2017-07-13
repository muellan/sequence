/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/


#include "linear.h"
#include "combined.h"

#include <vector>
#include <iostream>

using namespace am;


//-------------------------------------------------------------------
void combined_sequence_generation()
{
    using seq_detail::approx_equal;

    {
        auto v = std::vector<double>{};

        auto g = combined_sequence<linear_sequence<int>,linear_sequence<double>> {
            make_linear_sequence(8, -1, 1),
            make_linear_sequence(1.0, 1.0, 8.0)};

        for(auto x : g) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),8) || !approx_equal(v.back(),8) ||
            v.size() != 16)
        {
            throw std::logic_error("combined_sequence");
        }
    }

    {
        auto v = std::vector<double>{};

        auto g = make_combined_sequence(
            make_linear_sequence(8, -1, 1),
            make_linear_sequence(1.0, 1.0, 8.0));

        for(auto x : g) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),8) || !approx_equal(v.back(),8) ||
            v.size() != 16)
        {
            throw std::logic_error("combined_sequence");
        }
    }


}



//-------------------------------------------------------------------
int main()
{
    try {
        combined_sequence_generation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}


