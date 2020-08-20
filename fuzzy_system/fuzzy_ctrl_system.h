#ifndef FUZZY_CTRL_SYSTEM_H
#define FUZZY_CTRL_SYSTEM_H

#include <utility>

template<typename Input, typename DeductionPolicy, typename RuleBase, typename Defuzzifier>
struct fuzzy_ctrl_system
{
	using DeductionOp = typename DeductionPolicy::DeductionOperator;
	constexpr fuzzy_ctrl_system(Defuzzifier * defuzzifier,
								RuleBase&& rules,
								DeductionOp * deduction) : def(defuzzifier),
														   policy(DeductionPolicy(std::forward<RuleBase>(rules), deduction)) {}

	constexpr fuzzy_ctrl_system(Defuzzifier * defuzzifier,
	                            DeductionPolicy&& policy) : def(defuzzifier), policy(std::forward<DeductionPolicy>(policy)) {}

	double deduce(const Input& input) noexcept
	{
		return def(policy.deduce(input));
	}
	
	private:
		Defuzzifier * def;
		DeductionPolicy policy;
};

template<typename Input, typename DeductionPolicy, typename RuleBase, typename Defuzzifier>
constexpr fuzzy_ctrl_system<DeductionPolicy, Input, RuleBase, Defuzzifier> make_fuzzy_ctrl_sys(Defuzzifier&& defuzzifier, RuleBase&& rules)
{
	return fuzzy_ctrl_system<DeductionPolicy, Input, RuleBase, Defuzzifier>(std::forward<Defuzzifier>(defuzzifier),
																			std::forward<RuleBase>(rules));
}

//template<typename Input, typename DeductionPolicy, typename RuleBuilder, typename Defuzzifier>
//constexpr fuzzy_ctrl_system<DeductionPolicy, Input, RuleBase, Defuzzifier> make_fuzzy_ctrl_sys(Defuzzifier&& defuzzifier, RuleBase&& rules)
//{
//	return fuzzy_ctrl_system<DeductionPolicy, Input, RuleBase, Defuzzifier>(std::forward<Defuzzifier>(defuzzifier),
//																			std::forward<RuleBase>(rules));
//}

#endif
