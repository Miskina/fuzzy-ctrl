#ifndef STANDARD_FUZZY_SETS_H
#define STANDARD_FUZZY_SETS_H

#include <functional>

using IntUnaryFunction = std::function<double(int)>;

namespace standard_fuzzy_sets
{
	
	IntUnaryFunction l_function(int alfa, int beta);
	
	IntUnaryFunction gamma_function(int alfa, int beta);
	
	IntUnaryFunction lambda_function(int alfa, int beta, int gamma);

};


#endif
