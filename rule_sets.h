#ifndef RULE_SETS_H
#define RULE_SETS_H

#include "fuzzy_set/calculated_fuzzy_set.h"
#include "fuzzy_set/standard_fuzzy_sets.h"
#include "fuzzy_set/fuzzy_set_decorator.h"
#include "domain/simple_domain.h"
#include "operations/modifiers.h"

#include <type_traits>


namespace rule_sets
{

    using LF = typename std::invoke_result<decltype(standard_fuzzy_sets::l_function), int, int>::type;
    using GammaF = typename std::invoke_result<decltype(standard_fuzzy_sets::gamma_function), int, int>::type;
    using LambdaF = typename std::invoke_result<decltype(standard_fuzzy_sets::lambda_function), int, int, int>::type;
	using Modification = std::function<double(double)>;

    calculated_fuzzy_set<simple_domain, GammaF> iza_9_sela(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, LF> blizu(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, GammaF> spuraj(const simple_domain& domain);
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> blago_ubrzaj(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, LF> skreni_desno(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, GammaF> skreni_lijevo(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, LF> spor(const simple_domain& domain);

    calculated_fuzzy_set<simple_domain, GammaF> brz(const simple_domain& domain);
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> jako_brz(const simple_domain& domain);
    
    calculated_fuzzy_set<simple_domain, LF> uspori(const simple_domain& domain);
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> ostro_desno(const simple_domain& domain);

    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> ostro_lijevo(const simple_domain& domain);
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> naglo_koci(const simple_domain& domain);
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> blago_koci(const simple_domain& domain);
    
};


#endif
