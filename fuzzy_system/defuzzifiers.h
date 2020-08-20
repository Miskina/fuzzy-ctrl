#ifndef DEFUZZIFIERS_H
#define DEFUZZIFIERS_H

#include <array>
#include "../fuzzy_set/fuzzy_set.h"


namespace defuzzifiers
{

    template<typename Domain>
	double center_of_area(const fuzzy_set<Domain>& fs)
    {
	    double result = 0.0;
	    double sum = 0.0;
	    for(auto elem : fs.domain())
        {
	        double val = fs.value_at(elem);
	        result += val * elem;
	        sum += val;
        }
	    if(sum == 0.0) return 0.0;
	    return result / sum;
    }


};

#endif
