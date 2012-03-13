#pragma once
#include "NonTerminalSymbol.h"

class Production
{
private:
	NonTerminalSymbol * pNonTermLeft;
	NonTerminalSymbol * pNonTermRight;
	int indexTerm;
public:
	Production(NonTerminalSymbol *, NonTerminalSymbol *, int);
	~Production(void);
	NonTerminalSymbol * getNonTerminalSymbolOnLeft();
	NonTerminalSymbol * getNonTerminalSymbolOnRight();
	int getTerminalCharIndex();
};
