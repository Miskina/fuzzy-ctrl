#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <cmath>
#include <functional>
//namespace modifiers
//{
//	auto dilatation()
//	{
//		return [](double x){ return std::sqrt(x); };
//	}
//	
//	auto concentration()
//	{
//		return [](double x){ return x * x; };
//	}
//};

namespace modifiers
{
	using Modification = std::function<double(double)>;
	Modification dilatation();
	
	Modification concentration();
};

#endif
