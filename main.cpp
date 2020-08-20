#include <iostream>
#include <string>
#include <sstream>

#include "domain/domain.h"
#include "fuzzy_set/standard_fuzzy_sets.h"
#include "fuzzy_set/calculated_fuzzy_set.h"
#include "operations/operations.h"
#include "operations/implications.h"
#include "relations/fuzzy_relation.h"
#include "fuzzy_system/defuzzifiers.h"
#include "fuzzy_system/rule_builder.h"
#include "fuzzy_system/fuzzy_ctrl_system.h"
#include "kormilo/kormilo_deduction_policy.h"
#include "kormilo/kormilo_rule_base.h"
#include "akceleracija/akceleracija_rule_base.h"
#include "akceleracija/akceleracija_deduction_policy.h"


// Using deklaracije za norme i funkcionalnosti opcenito
using SNorm = decltype(operations::zadeh_or);
using DeductionOp = SNorm;
using TNorm = decltype(operations::zadeh_and);
//using TNorm = decltype(operations::product);
using Implication = decltype(implications::mamdani);
using Defuzzifier = decltype(defuzzifiers::center_of_area<simple_domain>);

// Using deklaracije za neizraziti upravljacki sustav kormila
using KormiloRuleBuilder = rule_builder<TNorm, SNorm, Implication>;
using KormiloRuleBase = kormilo_rule_base<KormiloRuleBuilder>;
using KormiloDeductionPolicy = kormilo_deduction_policy<DeductionOp, KormiloRuleBuilder>;
using KormiloFuzzySystem = fuzzy_ctrl_system<inputs,
											 KormiloDeductionPolicy,
											 KormiloRuleBase,
											 Defuzzifier>;

// Using deklaracije za neizraziti upravljacki sustav akceleracije
using AkceleracijaRuleBuilder = rule_builder<TNorm, SNorm, Implication>;
using AkceleracijaRuleBase = akceleracija_rule_base<AkceleracijaRuleBuilder>;
using AkceleracijaDeductionPolicy = akceleracija_deduction_policy<DeductionOp, AkceleracijaRuleBuilder>;
using AkceleracijaFuzzySystem = fuzzy_ctrl_system<inputs,
												  AkceleracijaDeductionPolicy,
												  AkceleracijaRuleBase,
												  Defuzzifier>;
												  
void primjer_jedno_pravilo()
{
	AkceleracijaRuleBase akceleracija_rules(make_rule_builder(operations::zadeh_and, operations::zadeh_or, implications::mamdani));
	inputs input{};
	std::string line;
	
	std::cout << "Primjer za pravilo ako je \"Ako je V spor onda ubrzaj\"\n";
	std::cout << "\nUpisi L, D, LK, DK, V i S ili KRAJ za izlaz\n";
	while(getline(std::cin, line))
	{
		if('K' == line[0]) return;
		std::istringstream stream(line);
		stream >> input;
		mutable_fuzzy_set<simple_domain> result(akceleracija_rules.domain_y);

        for(auto y : akceleracija_rules.domain_y)
        {
            double val = akceleracija_rules.speed_up_rule.value_at({input.V, y});
            result.set(y, val);
            std::cout << y << '/' << val << ' ';

        }

        double izlaz = defuzzifiers::center_of_area(result);
        std::cout << "\nDefuzzifier izlaz: " << izlaz << ", int: " << (int)izlaz;
        std::cout << "\nUpisi L, D, LK, DK, V i S ili KRAJ za izlaz\n";
	}
}

void primjer_baza_kormila()
{
    inputs input{};
    std::string line;
    std::cout << "Primjer za bazu kormila...";
    KormiloRuleBase kormilo(make_rule_builder(operations::zadeh_and,
                                              operations::zadeh_or,
                                              implications::mamdani));

    std::cout << "\nUpisi L, D, LK, DK, V i S ili KRAJ za izlaz\n";
    while(getline(std::cin, line))
    {

        if('K' == line[0]) return;
        std::istringstream stream(line);
        stream >> input;

        mutable_fuzzy_set<simple_domain> result(kormilo.domain_y);

        for(auto y : kormilo.domain_y)
        {
            double val = operations::zadeh_or({kormilo.turn_left_rule.value_at({input.DK, y}),
                                               kormilo.turn_right_rule.value_at({input.LK, y})});
            result.set(y, val);
            std::cout << y << '/' << val << ' ';

        }

        double izlaz = defuzzifiers::center_of_area(result);
        std::cout << "\nDefuzzifier izlaz: " << izlaz << ", int: " << (int)izlaz;
        std::cout << "\nUpisi L, D, LK, DK, V i S ili KRAJ za izlaz\n";
    }
}


void glavni_program()
{
	KormiloFuzzySystem system_kormila(defuzzifiers::center_of_area,
									  KormiloRuleBase(make_rule_builder(operations::zadeh_and,
									  									operations::zadeh_or,
																		implications::mamdani)),
									  operations::zadeh_or);

	AkceleracijaFuzzySystem system_akceleracije(defuzzifiers::center_of_area,
												AkceleracijaRuleBase(make_rule_builder(operations::zadeh_and,
																					   operations::zadeh_or,
																					   implications::mamdani)),
												operations::zadeh_or);
	inputs input{};
	std::string line;
	
	while(getline(std::cin, line))
	{
		if('K' == line[0]) return;
		std::istringstream stream(line);
		stream >> input;
		double kormilo = system_kormila.deduce(input);
		double akceleracija = system_akceleracije.deduce(input);
		
		std::cout << (int)akceleracija << ' ' << (int)kormilo << std::endl;
	}
}


int main(int argc, char** argv)
{
	std::ios::sync_with_stdio(false);
	
//	primjer_jedno_pravilo();

//    primjer_baza_kormila();

	glavni_program();
	
	return 0;
}
