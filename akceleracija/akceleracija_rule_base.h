#ifndef AKCELERACIJA_RULE_BASE_H
#define AKCELERACIJA_RULE_BASE_H


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
struct akceleracija_rule_base
{
    constexpr akceleracija_rule_base(RuleBuilder&& builder) : domain_x(domain::int_range(0, 1301)),
                                                              domain_y(domain::int_range(-30, 31)),
                                                              speed_up_rule(builder.imply(
                                                                              rule_sets::spor(domain_x),
                                                                              rule_sets::spuraj(domain_y)
                                                                      					 )
																		   ),
															  everything_far_rule(builder.imply(
															          builder.T(
															                  rule_sets::iza_9_sela(domain_x),
															                  builder.T(
															                          rule_sets::iza_9_sela(domain_x),
															                          builder.T(
															                                  rule_sets::iza_9_sela(domain_x),
															                                  rule_sets::iza_9_sela(domain_x)
															                                  )
															                          )
															                  ),
															           rule_sets::spuraj(domain_y)
															          )),
															  deaccelerate_close_rule(builder.imply(
															  			builder.T(
															  				rule_sets::jako_brz(domain_x),
																  			builder.S(
																			  	rule_sets::blizu(domain_x),
																				rule_sets::blizu(domain_x))),
																		rule_sets::naglo_koci(domain_y))) {}

    constexpr auto rules() noexcept
    {
		return std::array<fuzzy_set<simple_domain> *, 2>{&speed_up_rule, &everything_far_rule};
    }

    using SNorm = typename RuleBuilder::SNorm;
    using TNorm = typename RuleBuilder::TNorm;
    using Implication = typename RuleBuilder::Implication;
	
	template<typename FuzzySet1, typename FuzzySet2>
	using IMP = FR<FuzzySet1, FuzzySet2, Implication>;
	
	template<typename FS1, typename FS2>
	using TR = fuzzy_relation<FS1, FS2, TNorm>;
	
	template<typename FS1, typename FS2>
	using SR = fuzzy_relation<FS1, FS2, SNorm>;
	
    simple_domain domain_x;
    simple_domain domain_y;
    IMP<FS<L>, FS<Gamma>> speed_up_rule;
    IMP<TR<FS<Gamma>, TR<FS<Gamma>, TR<FS<Gamma>, FS<Gamma>>>>, FS<Gamma>> everything_far_rule;
	IMP<TR<DecoratedFS<Gamma>, SR<FS<L>, FS<L>>>, DecoratedFS<L>> deaccelerate_close_rule;
};


#endif
