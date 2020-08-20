#include "composite_domain.h"

//int composite_domain::cardinality() const noexcept
//{
//    int cardinality = 1;
//    for(const auto & domain : _domains)
//    {
//        cardinality *= domain->cardinality();
//    }
//    return cardinality;
//}

//template<unsigned int N>
//const simple_domain& composite_domain<N>::component(int at) const noexcept
//{
//    return *(_domains[at]);
//}


//int composite_domain::num_of_components() const noexcept
//{
//    return this-_domains.size();
//}

//std::vector<int> composite_domain::element_for_index(int index) const
//{
//    int n = _domains.size();
//    std::vector<int> elem(n);
//    for(int i = n - 1; i >= 0; --i)
//    {
//        int cardinality = _domains[i]->cardinality();
//        elem[i] = _domains[i]->element_for_index(index % cardinality);
//        index /= cardinality;
//    }
//    return elem;
//}
