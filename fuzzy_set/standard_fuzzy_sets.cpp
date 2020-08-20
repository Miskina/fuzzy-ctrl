#include "standard_fuzzy_sets.h"

namespace standard_fuzzy_sets
{
	
	IntUnaryFunction l_function(int alfa, int beta)
	{
		return [=](int x) -> double
				{
					if(x < alfa) return 1;
					if(x >= beta) return 0;
					return (double)(beta - x) / (beta - alfa);	
				};
	}
	
	IntUnaryFunction gamma_function(int alfa, int beta)
	{
		return [=](int x) -> double
				{
					if(x < alfa) return 0;
					if(x >= beta) return 1;
					return (double)(x - alfa) / (beta - alfa);
				};
	}
	
	IntUnaryFunction lambda_function(int alfa, int beta, int gamma)
	{
		return [=](int x) -> double
				{
					if(x < alfa) return 0;
					if(x >= gamma) return 0;
					
					if(alfa <= x && x < beta) return (double)(x - alfa) / (beta - alfa);
					
					return (double)(gamma - x) / (gamma - beta);
				};
	}
};
