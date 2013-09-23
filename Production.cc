#include <cstdlib>

#include "Production.h"

Production::Production(NonTerminalSymbol * pNonTermLeft, NonTerminalSymbol * pNonTermRight, int indexTerm)
{
	this->pNonTermLeft = pNonTermLeft;
	this->pNonTermRight = pNonTermRight;
	this->indexTerm = indexTerm;
}

Production::~Production(void)
{
	if (this->pNonTermLeft != NULL)
	{
		delete this->pNonTermLeft;
	}
	if (this->pNonTermRight != NULL)
	{
		delete this->pNonTermRight;
	}
}

NonTerminalSymbol * Production::getNonTerminalSymbolOnLeft()
{
	return this->pNonTermLeft;
}

NonTerminalSymbol * Production::getNonTerminalSymbolOnRight()
{
	return this->pNonTermRight;
}

int Production::getTerminalCharIndex()
{
	return this->indexTerm;
}
