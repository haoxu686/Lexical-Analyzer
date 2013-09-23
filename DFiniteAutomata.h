#pragma once

#include <vector>

#include "FiniteAutomata.h"

using namespace std;

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
