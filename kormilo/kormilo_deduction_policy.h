#ifndef KORMILO_DEDUCTION_POLICY_H
#define KORMILO_DEDUCTION_POLICY_H

#include "../fuzzy_system/deduction_policies.h"
#include "kormilo_rule_base.h"
#include "../operations/operations.h"
#include "../fuzzy_set/mutable_fuzzy_set.h"
#include "../fuzzy_system/inputs.h"


template<typename RuleBuilder, typename DeductionOp>
using IRDP = deduction_policies::individual_rule<kormilo_rule_base<RuleBuilder>,
												 inputs,
												 DeductionOp,
												 mutable_fuzzy_set<simple_domain>>;

template<typename DeductionOp, typename RuleBuilder>
struct kormilo_deduction_policy : public IRDP<RuleBuilder, DeductionOp>
{
	constexpr kormilo_deduction_policy(kormilo_rule_base<RuleBuilder>&& rule_base, DeductionOp * deduction) : IRDP<RuleBuilder, DeductionOp>(std::forward<kormilo_rule_base<RuleBuilder>>(rule_base), deduction) {}
	
	using Input = inputs;

    mutable_fuzzy_set<simple_domain> deduce(const Input& input) override
	{
		mutable_fuzzy_set<simple_domain> result(this->base.domain_y);

		for(auto y : this->base.domain_y)
		{

            result.set(y, this->op({this->base.turn_left_rule.value_at({input.DK, y}),
                                    this->base.turn_right_rule.value_at({input.LK, y})}));
		}

		return result;
	}
};

#endif
