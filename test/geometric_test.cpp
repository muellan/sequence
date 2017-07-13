/*****************************************************************************
 *
 * AM utilities
 *
 * released under MIT license
 *
 * 2008-2016 André Müller
 *
 *****************************************************************************/

#include "geometric.h"

#include <vector>
#include <iostream>


//-------------------------------------------------------------------
void geometric_sequence_generation()
{
    using am::geometric_sequence;
    using am::seq_detail::approx_equal;

    {
        auto v = std::vector<double>{};
        for(auto x : geometric_sequence<double>{1.0, 0.0, 1.0}) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),1) || !approx_equal(v.back(),1) ||
            v.size() != 1)
        {
            throw std::logic_error("geometric_sequence");
        }
    }

    {
        auto v = std::vector<double>{};
        for(auto x : geometric_sequence<double>{128.0, 0.5, 1.0}) {
            v.push_back(x);
        }
        if(!approx_equal(v.front(),128) || !approx_equal(v.back(),1) ||
            v.size() != 8)
        {
            throw std::logic_error("geometric_sequence");
        }

    }

    {
        auto g = geometric_sequence<double>{128.0, 0.5, 1.0};

        if(g.size() != 8u) {
            throw std::logic_error("geometric_sequence");
        }
    }

}



//-------------------------------------------------------------------
int main()
{
    try {
        geometric_sequence_generation();
    }
    catch(std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}


