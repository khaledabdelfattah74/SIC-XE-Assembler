#include "Literal.h"
#include <string>

using namespace std;

Literal::Literal(string v, int l, int a)
{
    this->value = v;
    this->length = l;
    this->address = a;
}

Literal::~Literal()
{
    //dtor
}
