#pragma once
#include "Production.h"
#include "FiniteAutomata.h"
using namespace std;

class Grammar
{
private:
	vector<Production *> * pvProductions;
	vector<char> * pvTermSym;
	int startState;
public:
	Grammar(void);
	~Grammar(void);
	void addProduction(Production *);
	void setTerminalSymbolSet(vector<char> *);
	FiniteAutomata * toFiniteAutomata();
};
