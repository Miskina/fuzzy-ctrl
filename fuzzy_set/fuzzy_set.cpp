#include "fuzzy_set.h"

//template<typename FuzzySet>
//std::ostream& operator<<(std::ostream& os, const typename std::enable_if<std::is_base_of<fuzzy_set, FuzzySet>::value, FuzzySet>::type& s)
//{
//	auto d = s.domain();
//	for(auto it = d.begin(); it != d.end(); ++it)
//	{
//		os << "d(" << decltype(d)::to_str(it) << ")=" << s.value_at(*it) << '\n';
//	}
//	os << std::endl;
//	return os;
//}
