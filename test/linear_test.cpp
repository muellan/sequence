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

#include <vector>
#include <iostream>



//-------------------------------------------------------------------
void linear_sequence_generation()
{
    using am::linear_sequence;
    using am::seq_detail::approx_equal;

    {
        auto v = std::vector<int>{};
        for(auto x : linear_sequence<int>{0,1,0}) {
            v.push_back(x);
        }
        if(v.front() != 0 || v.back() != 0 || v.size() != 1) {
            throw std::logic_error("linear_sequence");
        }
    }

    {
        auto v = std::vector<int>{};
        for(auto x : linear_sequence<int>{0,2,20}) {
            v.push_back(x);
        }
        if(v.front() != 0 || v.back() != 20 || v.size() != 11) {
            throw std::logic_error("linear_sequence");
        }
    }

    {
        auto v = std::vector<int>{};
        for(auto x : linear_sequence<int>{20,-2,0}) {
            v.push_back(x);
        }
        if(v.front() != 20 || v.back() != 0 || v.size() != 11) {
            throw std::logic_error("linear_sequence");
        }
    }

    {
        auto g = linear_sequence<double>{0,2,20};

        if(g.size() != 11u) {
            throw std::logic_error("linear_sequence");
        }
    }
}


//-------------------------------------------------------------------
int main()
{
    try {
        linear_sequence_generation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}


