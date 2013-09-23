#include <math.h>
#include <cstring>

#include "NonTerminalSymbol.h"

NonTerminalSymbol::NonTerminalSymbol(string * strValue)
{
	this->strValue = strValue;
	hash = 0;
	const char * p = strValue->data();
	int length = strlen(p);
	for (int i = 0; i < length; i++)
	{
		hash += (int)p[i]*pow(31.0, length-i-1);
	}
	hash = hash&0x7FFFFFFF;
}

NonTerminalSymbol::~NonTerminalSymbol(void)
{
	delete this->strValue;
}

string * NonTerminalSymbol::getValue()
{
	return this->strValue;
}

int NonTerminalSymbol::hashCode()
{
	return this->hash;
}
