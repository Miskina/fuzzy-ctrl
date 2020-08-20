#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <functional>
#include "../fuzzy_set/fuzzy_set_decorator.h"

using UnaryFunction = std::function<double(double)>;
using BinaryFunction = std::function<double(double, double)>;

namespace operations
{
	
	
	template<typename FuzzySet, typename UnaryFunction>
	fuzzy_set_decorator<UnaryFunction, FuzzySet> unary_operation(FuzzySet& set, UnaryFunction&& f)
	{
		
		return set | std::move(f);

	}
	
	template<typename FuzzySet1, typename FuzzySet2>
	fuzzy_set_decorator<BinaryFunction, FuzzySet1, FuzzySet2> binary_operation(FuzzySet1& s1, FuzzySet2& s2, BinaryFunction&& f)
	{
		return std::tie(s1, s2) | std::move(f);
	}
	
	double zadeh_not(double x);
	
	double zadeh_and(std::initializer_list<double>);
	
	double product(std::initializer_list<double>);

    double zadeh_or(std::initializer_list<double>);
	
	BinaryFunction hamacher_t_norm(double param);
	
	BinaryFunction hamacher_s_norm(double param);
};

#endif
