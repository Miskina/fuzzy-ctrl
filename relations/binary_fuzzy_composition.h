#ifndef BINARY_FUZZY_COMPOSITION_H
#define BINARY_FUZZY_COMPOSITION_H

#include "../domain/domain.h"
#include "../fuzzy_set/fuzzy_set.h"


template<unsigned int Start, size_t ... I, typename D>
static inline double value_at_impl(std::index_sequence<I...>, const fuzzy_set<D>& relation, const typename D::ElemType& e, int y_elem)
{
    if constexpr (!sizeof...(I)) return relation.value_at(y_elem);

	if constexpr (!Start) return relation.value_at({e[I]..., y_elem});

    return relation.value_at({y_elem, e[Start + I]...});
}

template<size_t ... I1, size_t ... I2, typename D1, typename D2>
static constexpr composite_domain<sizeof...(I1) + sizeof...(I2)> construct_domain(std::index_sequence<I1...>,
                                                                                  std::index_sequence<I2...>,
                                                                                  const D1& l_domain,
                                                                                  const D2& r_domain)
{
	return domain::combine(l_domain.component(I1)..., r_domain.component(I2 + 1)...);
}

template<typename Domain1, typename Domain2>
struct binary_fuzzy_composition : public fuzzy_set<composite_domain<domain::domain_size<Domain1>::value + domain::domain_size<Domain2>::value - 2>>
{
	static_assert(!std::is_same<Domain1, simple_domain>::value || !std::is_same<Domain2, simple_domain>::value,
				  "Cannot make a composition of relations defined on simple(single element) domains. The composition would be an empty set");
	
	static constexpr unsigned int N1 = domain::domain_size<Domain1>::value;
	static constexpr unsigned int N2 = domain::domain_size<Domain2>::value;
	using DomainType = typename domain::domain_for_size<N1 + N2 - 2>::type;

    binary_fuzzy_composition(const fuzzy_set<Domain1>& relation1,
                             const fuzzy_set<Domain2>& relation2) : r1(relation1),
                                                                    r2(relation2),
                                                                    d(construct_domain(std::make_index_sequence<N1 - 1>(),
                                                                                       std::make_index_sequence<N2 - 1>(),
                                                                                       relation1.domain(),
                                                                                       relation2.domain())) {}
	
	
	using DomainElem = typename DomainType::ElemType;
	
	const DomainType& domain() const noexcept override
	{
		return d;
	}
	
	double value_at(const DomainElem& e) const noexcept override
	{
		int index = d.index_of_element(e);
		if(index == -1) return 0.0;
		
		const auto & domain_y = r2.domain().component(0);
		
		double max = 0.0;
		for(auto y_it = domain_y.begin(); y_it != domain_y.end(); ++y_it)
		{
            double val = value_at_impl<0>(std::make_index_sequence<N1 - 1>(),
                                    	  r1,
                                          e,
                                          (*y_it));

            double r_val = value_at_impl<N1 - 1>(std::make_index_sequence<N2 - 1>(),
	                                             r2,
	                                             e,
	                                             (*y_it));
			
			val = val < r_val ? val : r_val;
			
			max = max < val ? val : max;
		}
		
		return max;
	}
	
	private:
		const fuzzy_set<Domain1>& r1;
		const fuzzy_set<Domain2>& r2;
		DomainType d;

//    template<RelationPosition Position, size_t ... I, typename D>
//    static double value_at_impl(std::index_sequence<I...>, const fuzzy_set<D>& relation, const typename D::ElemType& e, int y_elem)
//    {
//        if constexpr (!sizeof...(I)) return relation.value_at(y_elem);
//
//    	if constexpr (Position == RelationPosition::Left) return relation.value_at({e[I]..., y_elem});
//
//        return relation.value_at({y_elem, e[N1 - 1 + I]...});
//    }
};


#endif
