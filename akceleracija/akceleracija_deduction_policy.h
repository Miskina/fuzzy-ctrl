
#ifndef AKCELERACIJA_DEDUCTION_POLICY_H
#define AKCELERACIJA_DEDUCTION_POLICY_H

#include "../fuzzy_system/deduction_policies.h"
#include "../fuzzy_system/inputs.h"
#include "akceleracija_rule_base.h"
#include "../fuzzy_set/mutable_fuzzy_set.h"
#include "../domain/simple_domain.h"

template<typename RuleBuilder, typename DeductionOp>
using IRP = deduction_policies::individual_rule<akceleracija_rule_base<RuleBuilder>,
                                                    inputs,
                                                    DeductionOp,
                                                    mutable_fuzzy_set<simple_domain>>;

template<typename DeductionOp, typename RuleBuilder>
struct akceleracija_deduction_policy : public IRP<RuleBuilder, DeductionOp>
{
    constexpr akceleracija_deduction_policy(akceleracija_rule_base<RuleBuilder>&& rule_base, DeductionOp * deduction) : IRP<RuleBuilder, DeductionOp>(std::forward<akceleracija_rule_base<RuleBuilder>>(rule_base), deduction) {}

    using Input = inputs;

    mutable_fuzzy_set<simple_domain> deduce(const Input& input) override
    {
        mutable_fuzzy_set<simple_domain> result(this->base.domain_y);

        for(auto y : this->base.domain_y)
        {
            result.set(y, this->op({this->base.speed_up_rule.value_at({input.V, y}),
									this->base.everything_far_rule.value_at({input.L, input.D, input.LK, input.DK, y}),
									this->base.deaccelerate_close_rule.value_at({input.V, input.LK, input.DK, y})}));
									
        }

        return result;
    }
};


#endif
