#ifndef SIMPLE_DOMAIN_H
#define SIMPLE_DOMAIN_H

#include <stdexcept>
#include <ostream>
#include <string>

struct simple_domain
{
	using ElemType = int;
	constexpr simple_domain(int start, int end) : _start(start), _end(end) { }
	
	constexpr int cardinality() const noexcept
	{
		return _end - _start;
	}
	
	const simple_domain& component(int) noexcept;
	
	constexpr int num_of_components() const noexcept
	{
		return 1;
	}
	
	template<typename Iterable>
	constexpr int index_of_element(Iterable& elem) const noexcept
	{
		int e = *(elem.begin());
		if(e < _start || e >= _end) return -1;
		
		return e - _start;
	}
	
	constexpr int index_of_element(int e) const noexcept
	{
		if(e < _start || e >= _end) return -1;
		
		return e - _start;
	}
	
	int element_for_index(int) const;
	
	friend std::ostream& operator<<(std::ostream& os, const simple_domain& d)
	{
		for(const auto& e : d)
		{
			os << "Element domene je: " << e << '\n'; 
		}
		os << "Kardinalitet domene je: " << d.cardinality() << "\n\n";
		return os;
	}
	
	int first_element() const noexcept;
	
	int last_element() const noexcept;
	
	struct const_iterator
	{
		typedef const_iterator self_type;
        typedef int value_type;
        typedef int& reference;
        typedef int* pointer;
        typedef int difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        constexpr const_iterator(int start) : curr(start) { }
        self_type operator++() { self_type i = *this; curr++; return i; }
        self_type operator++(int junk) { curr++; return *this; }
        self_type operator--() { self_type i = *this; curr--; return i; }
        self_type operator--(int junk) { curr--; return *this; }
        const reference operator*() { return curr; }
        const pointer operator->() { return &curr; }
        bool operator==(const self_type& rhs) { return curr == rhs.curr; }
        bool operator!=(const self_type& rhs) { return curr != rhs.curr; }
            
		private:
			int curr;	
	};
	
	constexpr const_iterator begin() const noexcept
	{
		return const_iterator(_start);
	}
	
	constexpr const_iterator end() const noexcept
	{
		return const_iterator(_end);
	}
	
	std::string to_str(const_iterator& it) const
	{
		return std::to_string(*it);
	}
	
	friend bool operator==(const simple_domain& d1, const simple_domain& d2)
	{
		return d1._start == d2._start && d1._end == d2._end;
	}
	
	friend bool operator!=(const simple_domain& d1, const simple_domain& d2)
	{
		return d1._start != d2._start || d1._end != d2._end;
	}
	
	private:
		int _start;
		int _end;
};

#endif
