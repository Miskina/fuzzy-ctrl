#include "inputs.h"

std::istream& operator>>(std::istream& is, inputs& input)
{
	is >> input.L >> input.D >> input.LK >> input.DK >> input.V >> input.S;
	return is;
}
