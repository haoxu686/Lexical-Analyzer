#pragma once
#include "NonTerminalSymbol.h"

class HashMapNode
{
private:
	int stateId;
	NonTerminalSymbol * pNonTermSym;
	HashMapNode * pNodeNext;
public:
	HashMapNode(void);
	~HashMapNode(void);
	int getStateId();
	NonTerminalSymbol * getNonTerminalSymbol();
	HashMapNode * next();
	void setStateId(int);
	void setNonTerminalSymbol(NonTerminalSymbol *);
	void setNext(HashMapNode *);
};
