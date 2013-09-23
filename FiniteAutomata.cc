#include <map>
#include <queue>
#include <algorithm>

#include "FiniteAutomata.h"
#include "DFiniteAutomata.h"
#include "HashMap.h"

FiniteAutomata::FiniteAutomata(vector<char> * pvTermSym)
{
	this->pvTermSym = pvTermSym;
	pvStates = new vector<State *>;
}

FiniteAutomata::~FiniteAutomata(void)
{
	for (int i = 0; i < pvStates->size(); i++)
	{
		delete pvStates->at(i);
	}
	delete pvStates;
}

string * FiniteAutomata::toString(vector<int> * pVector)
{
	string * tmpString = new string("");
	int value;
	char digit;
	for (int i = pVector->size()-1; i >= 0; i--)
	{
		value = pVector->at(i);
		if (value == 0)
		{
			tmpString->append("0,");
			continue;
		}
		while (value != 0)
		{
			digit = '0'+value%10;
			value /= 10;
			(*tmpString) += digit;
			(*tmpString) += ',';
		}
	}
	return tmpString;
}

vector<int> * FiniteAutomata::eClosure(vector<int> * pvState)
{
	map<int, int> * pmState = new map<int, int>;
	map<int, int>::iterator it;
	for (int i = 0; i < pvState->size(); i++)
	{
		it = pmState->find(pvState->at(i));
		if (it == pmState->end())
		{
			pmState->insert(pair<int, int>(pvState->at(i), pvState->at(i)));
		}
	}
	pvState->clear();
	for (it = pmState->begin(); it != pmState->end(); it++)
	{
		pvState->push_back(it->first);
	}
	State * pState;
	Edge * pEdge;
	for (int i = 0; i < pvState->size(); i++)
	{
		pState = pvStates->at(pvState->at(i));
		pEdge = pState->nextEdge();
		while (pEdge != NULL)
		{
			if (pEdge->getIdentifiedCharIndex() != 0)
			{
				pEdge = pEdge->next();
				continue;
			}
			int id = pEdge->getStateId();
			it = pmState->find(id);
			if (it == pmState->end())
			{
				pmState->insert(pair<int, int>(id, id));
				pvState->push_back(id);
			}
			pEdge = pEdge->next();
		}
	}
	sort(pvState->begin(), pvState->end());
	delete pmState;
	return pvState;
}

DFiniteAutomata * FiniteAutomata::toDFA()
{
	vector<void *> * pvTmpPointer = new vector<void *>;
	vector<vector<int> * > * pvTable = new vector<vector<int> * >;
	for (int i = 0; i < pvTermSym->size(); i++)
	{
		pvTable->push_back(new vector<int>);
	}
	queue<vector<int> *> * pqState = new queue<vector<int> *>;
	HashMap * pHashMap = new HashMap();
	State * pInsertState;
	State * pState;
	Edge * pEdge;
	int globalStateId = 0;
	int stateId;
	int dstStateId;
	DFiniteAutomata * pDFiniteAutomata = new DFiniteAutomata(pvTermSym);
	NonTerminalSymbol * pNonTermSym;
	vector<int> * pvPushState = new vector<int>;
	vector<int> * pvPopState;

	pvPushState->push_back(0);
	pvPushState = eClosure(pvPushState);
	pNonTermSym = new NonTerminalSymbol(toString(pvPushState));
	stateId = globalStateId;
	pHashMap->put(pNonTermSym, stateId);
	globalStateId++;
	pqState->push(pvPushState);
	pInsertState = new State();
	pInsertState->setId(stateId);
	pInsertState->setEdgeNext(NULL);
	pInsertState->setType(false);
	pInsertState->setComment(NULL);
	for (int i = 0; i < pvPushState->size(); i++)
	{
		if (pvStates->at(pvPushState->at(i))->isTerminalState())
		{
			pInsertState->setType(true);
		}
	}
	pDFiniteAutomata->addState(pInsertState);

	while (!pqState->empty())
	{
		for (int i = 0; i < pvTermSym->size(); i++)
		{
			pvTable->at(i)->clear();
		}
		pvPopState = pqState->front();
		pqState->pop();
		for (int i = 0; i < pvPopState->size(); i++)
		{
			pState = pvStates->at(pvPopState->at(i));
			pEdge = pState->nextEdge();
			while (pEdge != NULL)
			{
				pvTable->at(pEdge->getIdentifiedCharIndex())->push_back(pEdge->getStateId());
				pEdge = pEdge->next();
			}
		}

		for (int i = 1; i < pvTermSym->size(); i++)
		{
			pvPushState = new vector<int>;
			for (int j = 0; j < pvTable->at(i)->size(); j++)
			{
				pvPushState->push_back(pvTable->at(i)->at(j));
			}
			if (pvPushState->size() == 0)
			{
				delete pvPushState;
				continue;
			}

			pvPushState = eClosure(pvPushState);
			pNonTermSym = new NonTerminalSymbol(toString(pvPushState));
			pvTmpPointer->push_back(pNonTermSym);
			stateId = pHashMap->get(pNonTermSym);
			if (stateId < 0)
			{
				stateId = globalStateId;
				globalStateId ++;
				pqState->push(pvPushState);
				pHashMap->put(pNonTermSym, stateId);
				pInsertState = new State();
				pInsertState->setId(stateId);
				pInsertState->setEdgeNext(NULL);
				pInsertState->setType(false);
				pInsertState->setComment(NULL);
				for (int k = 0; k < pvPushState->size(); k++)
				{
					if (pvStates->at(pvPushState->at(k))->isTerminalState())
					{
						pInsertState->setType(true);
					}
				}
				pDFiniteAutomata->addState(pInsertState);
			}
			else
			{
				pvTmpPointer->push_back(pvPushState);
			}
			pEdge = new Edge();
			pEdge->setStateId(stateId);
			pEdge->setIdentifiedCharIndex(i);
			pEdge->setNext(NULL);
			pNonTermSym = new NonTerminalSymbol(toString(pvPopState));
			pvTmpPointer->push_back(pNonTermSym);
			dstStateId = pHashMap->get(pNonTermSym);
			pDFiniteAutomata->addEdge(dstStateId, pEdge);

		}
		delete pvPopState;
	}
	pDFiniteAutomata->setStartState(startState);
	
	for (int i = 0; i < pvTable->size(); i++)
	{
		delete pvTable->at(i);
	}
	delete pvTable;
	delete pqState;
	delete pHashMap;
	for (int i = 0; i < pvTmpPointer->size(); i++)
	{
		delete pvTmpPointer->at(i);
	}
	delete pvTmpPointer;
	return pDFiniteAutomata;
}

void FiniteAutomata::addState(State * stateInstance)
{
	pvStates->push_back(stateInstance);
}

void FiniteAutomata::addEdge(int stateIndex, Edge * edgeInstance)
{
	State * pState = pvStates->at(stateIndex);
	pState->addAdjacent(edgeInstance);
}

void FiniteAutomata::setStartState(int startState)
{
	this->startState = startState;
}

State * FiniteAutomata::getState(int index)
{
	return pvStates->at(index);
}

int FiniteAutomata::getStartState()
{
	return this->startState;
}
