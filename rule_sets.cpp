#include "rule_sets.h"

namespace rule_sets
{
	namespace stdfs = standard_fuzzy_sets;
    calculated_fuzzy_set<simple_domain, GammaF> iza_9_sela(const simple_domain& domain)
    {
        return make_calculated_fuzzy_set(domain, standard_fuzzy_sets::gamma_function(60, 70));
    }

    calculated_fuzzy_set<simple_domain, LF> blizu(const simple_domain& domain)
    {
        return make_calculated_fuzzy_set(domain, standard_fuzzy_sets::l_function(45, 50));
    }

    calculated_fuzzy_set<simple_domain, LF> spuraj(const simple_domain& domain)
    {
        return make_calculated_fuzzy_set(domain, standard_fuzzy_sets::gamma_function(40, 55));
    }

    calculated_fuzzy_set<simple_domain, LF> skreni_desno(const simple_domain& domain)
    {

        return make_calculated_fuzzy_set(domain, stdfs::l_function(0, 30));
    }

    calculated_fuzzy_set<simple_domain, GammaF> skreni_lijevo(const simple_domain& domain)
    {
//        (make_calculated_fuzzy_set(domain_y, stdfs::gamma_function(90, 175)) | modifiers::concentration())
        return make_calculated_fuzzy_set(domain, stdfs::gamma_function(150, 180));
    }
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> ostro_desno(const simple_domain& domain)
    {
//        make_calculated_fuzzy_set(domain_y, stdfs::l_function(5, 90)) | modifiers::concentration();
        return make_calculated_fuzzy_set(domain, stdfs::l_function(5, 35)) | modifiers::concentration();
    }

    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> ostro_lijevo(const simple_domain& domain)
    {
//        (make_calculated_fuzzy_set(domain_y, stdfs::gamma_function(90, 175)) | modifiers::concentration())
        return make_calculated_fuzzy_set(domain, stdfs::gamma_function(140, 170))  | modifiers::concentration();
    }

    calculated_fuzzy_set<simple_domain, LF> spor(const simple_domain& domain)
    {
        return make_calculated_fuzzy_set(domain, stdfs::l_function(20, 40));
    }

    calculated_fuzzy_set<simple_domain, GammaF> brz(const simple_domain& domain)
    {
		return make_calculated_fuzzy_set(domain, stdfs::gamma_function(55, 75));
    }
    
    fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> jako_brz(const simple_domain& domain)
    {
    	return brz(domain) | modifiers::concentration();
	}
    
    calculated_fuzzy_set<simple_domain, LF> uspori(const simple_domain& domain)
    {
    	return make_calculated_fuzzy_set(domain, stdfs::l_function(5, 25));
	}
	
	fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> naglo_koci(const simple_domain& domain)
    {
    	return uspori(domain) | modifiers::concentration();
	}
	
	fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, LF>> blago_koci(const simple_domain& domain)
    {
    	return uspori(domain) | modifiers::dilatation();
	}
	
	fuzzy_set_decorator<Modification, calculated_fuzzy_set<simple_domain, GammaF>> blago_ubrzaj(const simple_domain& domain)
	{
		return spuraj(domain) | modifiers::dilatation();
	}
};
