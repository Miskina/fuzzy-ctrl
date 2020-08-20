#include "modifiers.h"

#include <cmath>

//namespace modifiers
//{
//	double dilatation(double x)
//	{
//		return std::sqrt(x);
//	}
//	
//	double concentration(double x)
//	{
//		return x * x;
//	}
//};

namespace modifiers
{
	Modification dilatation()
	{
		return [](double x){ return std::sqrt(x); };
	}
	
	Modification concentration()
	{
		return [](double x){ return x * x; };
	}
};
