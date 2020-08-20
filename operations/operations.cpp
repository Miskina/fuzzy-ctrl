#include "operations.h"

#include <algorithm>
#include <numeric>

namespace operations
{
	
	double zadeh_not(double x)
	{
		return 1.0 - x;
	}

    double zadeh_and(std::initializer_list<double> l)
	{
		return std::min(l);
	}

    double zadeh_or(std::initializer_list<double> l)
	{
		return std::max(l);
	}
	
	double product(std::initializer_list<double> l)
	{
		return std::accumulate(l.begin(), l.end(), 1.0, [](double prod, double x) { return prod * x; });
	}
	
	BinaryFunction hamacher_t_norm(double param)
	{
		if(param < 0.0) return [](double x, double y) { return 0.0; };
		
		return [param](double x, double y) 
						{ 
							return (x * y) / (param + (1.0 - param) * (x + y - x * y)); 
						};
	}
	
	BinaryFunction hamacher_s_norm(double param)
	{
		if(param < 0.0) return [](double x, double y) {return 0.0; };
		
		return [param](double x, double y) 
						{
							return (x + y - (2.0 - param) * x * y) / (1.0 - (1.0 - param) * x * y); 
						};
	}
	
};
