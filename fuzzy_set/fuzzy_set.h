#ifndef FUZZY_SET_H
#define FUZZY_SET_H

#include <ostream>
#include <type_traits>
#include "standard_fuzzy_sets.h"

template<typename Domain>
struct fuzzy_set
{
	virtual const Domain& domain() const noexcept = 0;
	virtual double value_at(const typename Domain::ElemType& e) const noexcept = 0;
};

template<typename Domain>
struct fuzzy_set_base : public fuzzy_set<Domain>
{
	fuzzy_set_base(const Domain& domain) : d(domain) {}
	
	fuzzy_set_base(const fuzzy_set_base<Domain>& s) : d(s.d) {}

	const Domain& domain() const noexcept override
	{
		return d;
	}
	
	protected:
		const Domain& d;
};


template<typename Domain>
std::ostream& operator<<(std::ostream& os, const fuzzy_set<Domain>& s)
{
	auto d = s.domain();
	for(auto it = d.begin(); it != d.end(); ++it)
	{
		os << "d(" << decltype(d)::to_str(it) << ")=" << s.value_at(*it) << '\n';
	}
	os << std::endl;
	return os;
}

#endif
