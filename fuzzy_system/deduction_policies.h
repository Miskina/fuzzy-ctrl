#ifndef DEDUCTION_POLICIES_H
#define DEDUCTION_POLICIES_H

#include "../relations/fuzzy_relation.h"

#include <algorithm>

namespace deduction_policies
{
	template<typename RuleBase, typename Input, typename DeductionOp, typename Output>
	struct individual_rule
	{
		using DeductionOperator = DeductionOp;
		
		constexpr individual_rule(RuleBase&& rule_base, DeductionOp * deduction_operator) : base(std::forward<RuleBase>(rule_base)),
		                                                                                    op(deduction_operator) {}
		
		virtual Output deduce(const Input& input) = 0;
		
		protected:
			RuleBase base;
			DeductionOp * op;
	};
	
	template<typename RuleBase, typename Input, typename CompositionOp, typename FuzzyRelation, typename Output>
	struct composition
	{
		
		constexpr composition(RuleBase&& rule_base, CompositionOp&& op) : relation(rule_base.rules() | op) {}
		
		virtual Output deduce(const Input& input) = 0;
		
		private:
			FuzzyRelation relation;
	};
	
};

#endif
