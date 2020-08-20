#include "simple_domain.h"

const simple_domain& simple_domain::component(int at) noexcept
{
	return *this;
}

int simple_domain::element_for_index(int index) const
{
	if(index > (this->_end - this->_start - 1)) throw std::out_of_range("out_of_range exception: accessed element not in range of domain");
	return this->_start + index;
}

int simple_domain::first_element() const noexcept
{
	return _start;
}
	
int simple_domain::last_element() const noexcept
{
	return _end - 1;
}

