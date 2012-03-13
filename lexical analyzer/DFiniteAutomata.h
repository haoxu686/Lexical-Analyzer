#pragma once
#include "FiniteAutomata.h"

class DFiniteAutomata :
	public FiniteAutomata
{
public:
	DFiniteAutomata(vector<char> *);
	~DFiniteAutomata(void);
	DFiniteAutomata * mimimize();
	bool analyse(string *);
	void test();
};
