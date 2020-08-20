#ifndef INPUTS_H
#define INPUTS_H

#include <istream>

struct inputs
{
    int L, D, LK, DK, V, S;
};

std::istream& operator>>(std::istream&, inputs&);

#endif
