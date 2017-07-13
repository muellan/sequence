/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/


#include "repeated.h"
#include "linear.h"

#include <vector>
#include <iostream>


//-------------------------------------------------------------------
void repeated_sequence_generation()
{
    using namespace am;
    using seq_detail::approx_equal;

    {
        auto v = std::vector<double>{};

        auto g = repeated_sequence<linear_sequence<int>> {
            make_linear_sequence(8, -1, 1)};

        for(auto x : g) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),8) || !approx_equal(v.back(),1) ||
            v.size() != 8)
        {
            throw std::logic_error("repeated_sequence");
        }
    }

    {
        auto v = std::vector<double>{};

        auto g = repeated_sequence<linear_sequence<int>> {
            make_linear_sequence(8, -1, 1), 2};

        for(auto x : g) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),8) || !approx_equal(v.back(),1) ||
            v.size() != 24)
        {
            throw std::logic_error("repeated_sequence");
        }
    }

    {
        auto v = std::vector<double>{};

        auto g = repeated_sequence<linear_sequence<int>> {
            make_linear_sequence(8, -1, 1),
            make_linear_sequence(5, -1, 1), 2};

        for(auto x : g) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),8) || !approx_equal(v.back(),1) ||
            v.size() != 18)
        {
            throw std::logic_error("repeated_sequence");
        }
    }

}



//-------------------------------------------------------------------
int main()
{
    try {
        repeated_sequence_generation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}


