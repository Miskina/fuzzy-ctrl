#ifndef FUZZY_RELATION_H
#define FUZZY_RELATION_H

#include "../domain/domain.h"
#include "../fuzzy_set/fuzzy_set.h"

template<unsigned int Start, size_t N, size_t ... I, typename Domain>
static inline double value_at_impl(std::index_sequence<I...>, const fuzzy_set<Domain>& set, const std::array<int, N>& elem)
{
	if constexpr (std::is_same<Domain, simple_domain>::value)
	{
		if constexpr (!Start) return set.value_at(elem[0]);
		else return set.value_at(elem[Start]);
	}
	if constexpr (!Start) return set.value_at({elem[I]...});
	
	return set.value_at({elem[Start + I]...});
}

template<typename FuzzySet1, typename FuzzySet2, typename RelationOperator>
struct fuzzy_relation : public fuzzy_set<composite_domain<domain::domain_size<typename FuzzySet1::DomainType>::value + domain::domain_size<typename FuzzySet2::DomainType>::value>>
{
	static constexpr unsigned int N1 = domain::domain_size<typename FuzzySet1::DomainType>::value;
	static constexpr unsigned int N2 = domain::domain_size<typename FuzzySet2::DomainType>::value;
	
	using DomainType = composite_domain<N1 + N2>;

	constexpr fuzzy_relation(FuzzySet1&& f1,
							 FuzzySet2&& f2,
							 RelationOperator * relation_op) : fs1(std::forward<FuzzySet1>(f1)),
								 							   fs2(std::forward<FuzzySet2>(f2)),
								 							   d(domain::combine(f1.domain(), f2.domain())),
															   op(relation_op) {}
	
	const DomainType& domain() const noexcept override
	{
		return d;
	}
	
	using DomainElem = typename DomainType::ElemType;
	
	double value_at(const DomainElem& elem) const noexcept override
	{
		return op(std::initializer_list<double>{value_at_impl<0>(std::make_index_sequence<N1>(), fs1, elem),
                   								value_at_impl<N1>(std::make_index_sequence<N2>(), fs2, elem)});
	}
	
	private:
		FuzzySet1 fs1;
		FuzzySet2 fs2;
		composite_domain<N1 + N2> d;
		RelationOperator * op;
	
	
};


template<typename FS1, typename FS2, typename RelationOp>
fuzzy_relation<FS1, FS2, RelationOp> make_relation(FS1&& f1, FS2&& f2, RelationOp * op)
{
	return fuzzy_relation<FS1, FS2, RelationOp>(std::forward<FS1>(f1),
												std::forward<FS2>(f2),
												op);
}

#endif
