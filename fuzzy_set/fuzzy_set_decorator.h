#ifndef FUZZY_SET_DECORATOR_H
#define FUZZY_SET_DECORATOR_H

#include <tuple>
#include <initializer_list>
#include <ostream>
#include "../domain/domain.h"
#include "fuzzy_set.h"

template<typename Func, typename FuzzySet, typename ... FuzzySets>
struct fuzzy_set_decorator : public fuzzy_set_base<typename FuzzySet::DomainType>
{
	using DomainType = typename FuzzySet::DomainType;
	fuzzy_set_decorator(Func * func, FuzzySet& set, FuzzySets&... sets) : fuzzy_set_base<DomainType>(set.domain()),
																		_sets(std::forward_as_tuple(set, sets...)),
																		f(func) {}
	
	fuzzy_set_decorator(Func *  func, std::tuple<FuzzySet&, FuzzySets&...>&& sets) : fuzzy_set_base<DomainType>(std::get<0>(sets).domain()),
																				  _sets(std::forward<std::tuple<FuzzySet&, FuzzySets&...>>(sets)),
																				  f(func) {}
	
	double value_at(const typename DomainType::ElemType& v) const noexcept
	{	
		return value_at_impl(sequence, v);
	}
	
	
	private:
		std::tuple<FuzzySet&, FuzzySets&...> _sets;
		Func * f;
		static constexpr auto sequence = std::make_index_sequence<sizeof...(FuzzySets) + 1>();
		
		template<unsigned int ... I>
		double value_at_impl(const std::index_sequence<I...>&, const typename DomainType::ElemType& v) const noexcept
		{
			return f(std::initializer_list<double>{std::get<I>(_sets).value_at(v)...});
		}
};

template<typename Func, typename FuzzySet>
struct fuzzy_set_decorator<Func, FuzzySet> : public fuzzy_set_base<typename FuzzySet::DomainType>
{
	using DomainType = typename FuzzySet::DomainType;
	
	fuzzy_set_decorator(Func&& func, FuzzySet&& set) : fuzzy_set_base<DomainType>(set.domain()), s(std::forward<FuzzySet>(set)), f(std::forward<Func>(func)) { }
	
	double value_at(const typename DomainType::ElemType& v) const noexcept
	{
		return f(s.value_at(v));
	}
	
	private:
		FuzzySet s;
		Func f;
};

template<typename Func, typename ... FuzzySets>
fuzzy_set_decorator<Func, FuzzySets...> operator|(std::tuple<FuzzySets&...>&& sets, Func&& f)
{
	return fuzzy_set_decorator<Func, FuzzySets...>(std::forward<Func>(f), std::forward<std::tuple<FuzzySets&...>>(sets));
}

template<typename Func, typename FuzzySet>
fuzzy_set_decorator<Func, FuzzySet> operator|(FuzzySet&& s, Func&& f)
{

	return fuzzy_set_decorator<Func, FuzzySet>(std::forward<Func>(f), std::forward<FuzzySet>(s));
}

template<typename Func, typename ... FuzzySets>
fuzzy_set_decorator<Func, FuzzySets...> make_fs_decorator(FuzzySets&... sets, Func&& f)
{
	return fuzzy_set_decorator<Func, FuzzySets...>(std::forward<Func>(f), sets...);
}

template<unsigned int ... I, typename Func, typename ... FuzzySets>
static fuzzy_set_decorator<Func, FuzzySets...> make_fs_decorator(Func&& f, std::tuple<FuzzySets&...>&& sets)
{
	return fuzzy_set_decorator<Func, FuzzySets...>(std::forward<Func>(f), std::forward<std::tuple<FuzzySets&...>>(sets));
}


#endif
