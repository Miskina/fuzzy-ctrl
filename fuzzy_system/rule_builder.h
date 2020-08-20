#ifndef RULE_BUILDER_H
#define RULE_BUILDER_H

#include "../relations/fuzzy_relation.h"

template<typename T_Norm, typename S_Norm, typename ImplicationOp>
struct rule_builder
{
	using SNorm = S_Norm;
	using TNorm = T_Norm;
	using Implication = ImplicationOp;
	
	constexpr rule_builder(TNorm * tnorm, SNorm * snorm, Implication * implication_op) : t_norm(tnorm),
																						 s_norm(snorm),
																						 implication(implication_op)
																						 {}
	
	template<typename FS1, typename FS2>
	constexpr inline fuzzy_relation<FS1, FS2, TNorm> T(FS1&& fuzzy_set1, FS2&& fuzzy_set2)
	{
		return fuzzy_relation<FS1, FS2, TNorm>(std::forward<FS1>(fuzzy_set1), std::forward<FS2>(fuzzy_set2), t_norm);
	}
	
	template<typename FS1, typename FS2>
	constexpr inline fuzzy_relation<FS1, FS2, SNorm> S(FS1&& fuzzy_set1, FS2&& fuzzy_set2)
	{
		return fuzzy_relation<FS1, FS2, SNorm>(std::forward<FS1>(fuzzy_set1), std::forward<FS2>(fuzzy_set2), s_norm);
	}
	
	template<typename FS1, typename FS2>
	constexpr inline fuzzy_relation<FS1, FS2, Implication> imply(FS1&& fuzzy_set1, FS2&& fuzzy_set2)
	{
		return fuzzy_relation<FS1, FS2, Implication>(std::forward<FS1>(fuzzy_set1), std::forward<FS2>(fuzzy_set2), implication);
	}
	
	private:
		TNorm * t_norm;
		SNorm * s_norm;
		Implication * implication;
};

template<typename TNorm, typename SNorm, typename Implication>
constexpr rule_builder<TNorm, SNorm, Implication> make_rule_builder(TNorm * t_norm, SNorm * s_norm, Implication * implication)
{
	return rule_builder<TNorm, SNorm, Implication>(t_norm, s_norm, implication);
}

#endif
