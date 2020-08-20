#ifndef MUTABLE_FUZZY_SET_H
#define MUTABLE_FUZZY_SET_H

#include <vector>
#include <ostream>
#include "fuzzy_set.h"

template<typename Domain>
struct mutable_fuzzy_set : public fuzzy_set_base<Domain>
{
	using DomainType = Domain;
	
	mutable_fuzzy_set(const Domain& domain) : fuzzy_set_base<Domain>(domain)
	{
		values = std::vector<double>(domain.cardinality());
	}
	
	double value_at(const typename Domain::ElemType& e) const noexcept
	{
		auto index = this->d.index_of_element(e);
		if(index == -1) return 0.0;
		return values[index];
	}
	
	mutable_fuzzy_set& set(const typename Domain::ElemType& e, double val) {
        values[this->d.index_of_element(e)] = val;
        return *this;
    }
	
	private:
		std::vector<double> values;
		
};

template<typename Domain>
mutable_fuzzy_set<Domain> make_mutable_fset(const Domain& d)
{
	return mutable_fuzzy_set<Domain>(d);
}

#endif
