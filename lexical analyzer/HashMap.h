#pragma once
#include "HashMapNode.h"

class HashMap
{
private:
	vector<HashMapNode *> * pvHashMap;
public:
	HashMap(void);
	~HashMap(void);
	void put(NonTerminalSymbol *, int);
	int get(NonTerminalSymbol *);
};
