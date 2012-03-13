#pragma once
#include "State.h"

class DFiniteAutomata;

class FiniteAutomata
{
protected:
	vector<State *> * pvStates;
	vector<char> * pvTermSym;
	string * toString(vector<int> *);
	int startState;
public:
	FiniteAutomata(vector<char> *);
	~FiniteAutomata(void);
	void addState(State *);
	void addEdge(int, Edge *);
	void setStartState(int);
	State * getState(int);
	int getStartState();
	DFiniteAutomata * toDFA();
	vector<int> * eClosure(vector<int> *);
	void test();
};
