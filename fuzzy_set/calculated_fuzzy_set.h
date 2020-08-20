#ifndef CALCULATED_FUZZY_SET_H
#define CALCULATED_FUZZY_SET_H

#include <initializer_list>
#include <vector>
#include <functional>
#include <ostream>
#include "fuzzy_set.h"

//using IntUnaryFunction = std::function<double(int)>;


template<typename Domain, typename IntUnaryFunction>
struct calculated_fuzzy_set : public fuzzy_set_base<Domain>
{
	using DomainType = Domain;
	
	calculated_fuzzy_set(const Domain& domain, IntUnaryFunction&& unary_function) : fuzzy_set_base<Domain>(domain), f(std::forward<IntUnaryFunction>(unary_function)){ }
	
//	const Domain& domain() const noexcept override
//	{
//		return d;
//	}
	
	double value_at(const typename Domain::ElemType& e) const noexcept
	{
		auto index = this->d.index_of_element(e);
		if(index == -1) return 0.0;
		
		return f(index);
	}
		
	private:
		IntUnaryFunction f;
//		Domain d;
};

template<typename Domain, typename Function>
calculated_fuzzy_set<Domain, Function> make_calculated_fuzzy_set(const Domain& d, Function&& f)
{
	return calculated_fuzzy_set<Domain, Function>(d, std::forward<Function>(f));
}

#endif
