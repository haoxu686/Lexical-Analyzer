#pragma once
#include <vector>

#include "HashMapNode.h"

using namespace std;

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
