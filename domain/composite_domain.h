#ifndef COMPOSITE_DOMAIN_H
#define COMPOSITE_DOMAIN_H

#include <stdexcept>
#include <vector>
#include <array>
#include <sstream>

#include "simple_domain.h"

template<unsigned int N>
struct composite_domain
{
	using ElemType = std::array<int, N>;
	
//	composite_domain(std::initializer_list<const simple_domain *> domains)
//	{
//		_domains = std::vector<const simple_domain *>(domains);
//	}
	
	constexpr composite_domain(std::array<const simple_domain *, N>&&  domains) : _domains(std::move(domains)) {}
	
	constexpr int cardinality() const noexcept
	{
		int cardinality = 1;
	    for(const auto & domain : _domains)
	    {
	        cardinality *= domain->cardinality();
	    }
	    return cardinality;
	}
	
	const simple_domain& component(int at) const noexcept
	{
		return *(_domains[at]);
	}
	
	constexpr int num_of_components() const noexcept
	{
		return N;
	}
	
	
	int index_of_element(const ElemType& elem) const noexcept
	{
		
		int index = 0;
		int multiplier = 1;
		int in_domain_index = -1;
		
		for(int i = _domains.size() - 1; i >= 0; --i)
		{
			in_domain_index = _domains[i]->index_of_element(elem[i]);
			if(in_domain_index == -1) return -1;
			
			index += in_domain_index * multiplier;
			multiplier *= _domains[i]->cardinality();
		}
		
		return index;
	}

	ElemType element_for_index(int index) const
	{
	    ElemType elem{};
	    for(int i = N - 1; i >= 0; --i)
	    {
	        int cardinality = _domains[i]->cardinality();
	        elem[i] = _domains[i]->element_for_index(index % cardinality);
	        index /= cardinality;
	    }
	    return elem;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const composite_domain& d)
	{
		for(const auto& e : d)
		{
			os << "Element domene je: (";
			int n = N - 1;
			for(int i = 0; i < n; ++i)
			{
				os << e[i] << ',';
			}
			os << e[n] << ")\n";
		}
		os << "Kardinalitet domene je: " << d.cardinality() << "\n\n";
		return os;
	}
	
//	ElemType first_element() const noexcept;
//	
//	ElemType last_element() const noexcept;
	
	struct const_iterator
	{
		typedef const_iterator self_type;
        typedef ElemType value_type;
        typedef ElemType& reference;
        typedef ElemType* pointer;
        typedef int difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        const_iterator(int start, const composite_domain& domain) : d(domain)
		{
			curr = domain.element_for_index(start);
		}
		
		const_iterator(const composite_domain& domain) : curr({}), d(domain)
		{
			
			curr[0] = domain.component(0).last_element() + 1;
			for(int i = 1, n = curr.size(); i < n; ++i)
            {
			    curr[i] = domain.component(i).element_for_index(0);
            }
		}
        self_type operator++() 
		{
			self_type i = *this;
			increment();
			return i; 
		}
        self_type operator++(int junk) 
		{
			increment();
			return *this;
		}
        self_type operator--() 
		{
			self_type i = *this;
			decrement();
			return i; 
		}
        self_type operator--(int junk)
		{
			decrement();
			return *this;
		}
        const reference operator*() { return curr; }
        const pointer operator->() { return &curr; }
        bool operator==(const self_type& rhs) { return curr == rhs.curr; }
        bool operator!=(const self_type& rhs) { return curr != rhs.curr; }
            
		private:
			value_type curr;
			const composite_domain& d;
			
			void increment() noexcept
			{
				
				for(int i = curr.size() - 1; i >= 0; --i)
				{
					int index = d._domains[i]->index_of_element(curr[i]);
					if(index == d._domains[i]->cardinality() - 1 && i != 0)
					{
						curr[i] = d._domains[i]->element_for_index(0);
					}
					else
					{
						curr[i]++;
						break;
					}
				}
			}
			
			void decrement() noexcept
			{
				for(int i = curr.size() - 1; i >= 0; --i)
				{
					int index = d._domains[i]->index_of_element(curr[i]);
					if(index == 0)
					{
						curr[i] = d._domains[i]->element_for_index(d._domains[i]->cardinality() - 1);
					} else
					{
						curr[i]--;
						break;
					}
				}
			}
	};
	
	const_iterator begin() const noexcept
	{
		return const_iterator(0, *this);
	}
	
	const_iterator end() const noexcept
	{
		return const_iterator(*this);
	}

	std::string to_str(const_iterator& it) const
	{
		std::ostringstream ss;
		auto arr = *it;
		int n = N - 1;
		for(int i = 0; i < n; ++i)
		{
			ss << arr[i] << ',';
		}
		ss << arr[n];
		return ss.str();
	}
	
	private:
		std::array<const simple_domain *, N> _domains;
		
};

#endif
