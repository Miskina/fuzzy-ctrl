#ifndef KORMILO_RULE_BASE_H
#define KORMILO_RULE_BASE_H

#include <functional>

#include "../operations/modifiers.h"
#include "../fuzzy_system/rule_builder.h"
#include "../operations/operations.h"
#include "../operations/implications.h"
#include "../fuzzy_set/calculated_fuzzy_set.h"
#include "../rule_sets.h"

namespace stdfs = standard_fuzzy_sets;

template<typename Op>
using FS = calculated_fuzzy_set<simple_domain, Op>;

using L = typename std::invoke_result<decltype(stdfs::l_function), int, int>::type;
using Gamma = typename std::invoke_result<decltype(stdfs::gamma_function), int, int>::type;

using LFS = FS<L>;

using Modification = std::function<double(double)>;

template<typename StandardFuzzySetType>
using DecoratedFS = fuzzy_set_decorator<Modification, FS<StandardFuzzySetType>>;

template<typename FS1, typename FS2, typename Op>
using FR = fuzzy_relation<FS1, FS2, Op>;

template<typename RuleBuilder>
struct kormilo_rule_base
{
	constexpr kormilo_rule_base(RuleBuilder&& builder) : domain_x(domain::int_range(0, 1301)),
														 domain_y(domain::int_range(-90, 91)),
														 turn_right_rule(builder.imply(
														 			rule_sets::blizu(domain_x),
																	rule_sets::skreni_desno(domain_y)				
																					  )),
														 turn_left_rule(builder.imply(
														 			rule_sets::blizu(domain_x),
														 			rule_sets::skreni_lijevo(domain_y)
														 							 )) {}

	constexpr auto rules() noexcept
    {
	    return std::array<fuzzy_set<simple_domain> *, 2>{&turn_right_rule, &turn_left_rule};
    }
	
	using SNorm = typename RuleBuilder::SNorm;
	using TNorm = typename RuleBuilder::TNorm;
	using Implication = typename RuleBuilder::Implication;
	
	simple_domain domain_x;
	simple_domain domain_y;
	FR<FS<L>, FS<L>, Implication> turn_right_rule;
	FR<FS<L>, FS<Gamma>, Implication> turn_left_rule;
		
};

#endif
