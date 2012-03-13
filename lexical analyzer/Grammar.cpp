#include "StdAfx.h"
#include "Grammar.h"
#include "HashMap.h"

Grammar::Grammar(void)
{
	startState = 0;
	pvProductions = new vector<Production *>;
}

Grammar::~Grammar(void)
{
	for (int i = 0; i < pvProductions->size(); i++)
	{
		delete pvProductions->at(i);
	}
	delete pvProductions;
	delete pvTermSym;
}

void Grammar::addProduction(Production * proInstance)
{
	pvProductions->push_back(proInstance);
}

void Grammar::setTerminalSymbolSet(vector<char> * pvTermSym)
{
	this->pvTermSym = pvTermSym;
}

FiniteAutomata * Grammar::toFiniteAutomata()
{
	HashMap * pHashMap = new HashMap();
	int globalStateId = 0;
	int stateId;
	FiniteAutomata * pFiniteAutomata = new FiniteAutomata(this->pvTermSym);
	State * pState;
	Edge * pEdge;
	Production * pProduction;
	NonTerminalSymbol * pNonTermSymLeft;
	NonTerminalSymbol * pNonTermSymRight;
	int indexIdentifiedChar;
	for (int i = 0; i < this->pvProductions->size(); i++)
	{
		pProduction = pvProductions->at(i);
		pNonTermSymLeft = pProduction->getNonTerminalSymbolOnLeft();
		stateId = pHashMap->get(pNonTermSymLeft);
		if (stateId < 0)
		{
			pHashMap->put(pNonTermSymLeft, globalStateId);
			stateId = globalStateId;
			globalStateId++;
			pState = new State();
			pState->setId(stateId);
			pState->setEdgeNext(NULL);
			pState->setType(false);
			pState->setComment(NULL);
			pFiniteAutomata->addState(pState);
		}
	}
	string * strBlank = new string("");
	NonTerminalSymbol * termSymbol = new NonTerminalSymbol(strBlank);
	pHashMap->put(termSymbol, globalStateId);
	stateId = globalStateId;
	globalStateId++;
	pState = new State();
	pState->setId(stateId);
	pState->setEdgeNext(NULL);
	pState->setType(true);
	pState->setComment(NULL);
	pFiniteAutomata->addState(pState);

	int dstStateId;
	for (int i = 0; i < this->pvProductions->size(); i++)
	{
		pProduction = pvProductions->at(i);
		pNonTermSymLeft = pProduction->getNonTerminalSymbolOnLeft();
		pNonTermSymRight = pProduction->getNonTerminalSymbolOnRight();
		indexIdentifiedChar = pProduction->getTerminalCharIndex();
		stateId = pHashMap->get(pNonTermSymLeft);
		dstStateId = pHashMap->get(pNonTermSymRight);
		pEdge = new Edge();
		pEdge->setStateId(dstStateId);
		pEdge->setNext(NULL);
		pEdge->setIdentifiedCharIndex(indexIdentifiedChar);
		pFiniteAutomata->addEdge(stateId, pEdge);
	}
	pFiniteAutomata->setStartState(startState);
	delete pHashMap;
	return pFiniteAutomata;
}