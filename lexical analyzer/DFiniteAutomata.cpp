#include "StdAfx.h"
#include "DFiniteAutomata.h"

DFiniteAutomata::DFiniteAutomata(vector<char> * pvTermSym):FiniteAutomata(pvTermSym)
{
}

DFiniteAutomata::~DFiniteAutomata(void)
{
}

DFiniteAutomata * DFiniteAutomata::mimimize()
{
	int globalSetId;
	vector<set<int> * > * pvStateSets = new vector<set<int> *>;
	vector<int> * pvRes = new vector<int>;
	vector<int> * pvDic = new vector<int>;
	vector<int>::iterator vItDic;
	vector<int>::iterator vItRes;
	for (int i = 0; i < pvStates->size(); i++)
	{
		pvRes->push_back(0);
	}
	pvRes->push_back(pvStates->size());
	for (int i = 0; i < pvStates->size()+1; i++)
	{
		pvDic->push_back(-1);
	}
	set<int> * pSet = new set<int>;
	for (int i = 0; i < pvStates->size(); i++)
	{
		if (!pvStates->at(i)->isTerminalState())
		{
			pSet->insert(i);
		}
	}
	pvStateSets->push_back(pSet);
	pSet = new set<int>;
	for (int i = 0; i < pvStates->size(); i++)
	{
		if (pvStates->at(i)->isTerminalState())
		{
			pSet->insert(i);
			vItRes = pvRes->begin()+i;
			*vItRes = 1;
		}
	}
	pvStateSets->push_back(pSet);

	bool changed = false;
	set<int> * psTmp;
	set<int>::iterator sIt;
	int dstState;
	int dstSet;
	int changeSet;
	Edge * pEdge;
	for (int i = 1; i < pvTermSym->size(); i++)
	{
		changed = false;
		for (int j = 0; j < pvStateSets->size(); j++)
		{
			globalSetId = pvStateSets->size();
			for (int k = 0; k < pvDic->size(); k++)
			{
				vItDic = pvDic->begin()+k;
				*vItDic = -1;
			}
			psTmp = pvStateSets->at(j);
			sIt = psTmp->begin();
			dstState = pvStates->size();
			pEdge = pvStates->at(*sIt)->nextEdge();
			while (pEdge != NULL)
			{
				if (pEdge->getIdentifiedCharIndex() == i)
				{
					dstState = pEdge->getStateId();
					break;
				}
				pEdge = pEdge->next();
			}
			dstSet = pvRes->at(dstState);
			vItDic = pvDic->begin()+dstSet;
			*vItDic = j;
			sIt++;
			for (; sIt != psTmp->end(); sIt++)
			{
				dstState = pvStates->size();
				pEdge = pvStates->at(*sIt)->nextEdge();
				while (pEdge != NULL)
				{
					if (pEdge->getIdentifiedCharIndex() == i)
					{
						dstState = pEdge->getStateId();
						break;
					}
					pEdge = pEdge->next();
				}
				dstSet = pvRes->at(dstState);
				vItDic = pvDic->begin()+dstSet;
				changeSet = *vItDic;
				if (changeSet == j)
				{
					continue;
				}
				changed = true;
				if (changeSet == -1)
				{
					pSet = new set<int>;
					pSet->insert(*sIt);
					*vItDic = pvStateSets->size();
					pvStateSets->push_back(pSet);
				}

				else
				{
					pvStateSets->at(changeSet)->insert(*sIt);
				}

			}
			if(changed)
			{
				for (int k = globalSetId; k < pvStateSets->size(); k++)
				{
					for (sIt = pvStateSets->at(k)->begin(); sIt != pvStateSets->at(k)->end(); sIt++)
					{
						vItRes = pvRes->begin()+(*sIt);
						*vItRes = k;
						psTmp->erase(psTmp->find(*sIt));
					}
				}
				break;
			}
		}
		if (changed)
		{
			i = 0;
		}
	}

	DFiniteAutomata * pDFiniteAutomataMin = new DFiniteAutomata(this->pvTermSym);
	State * pState;
	Edge * pAddEdge;
	for (int i = 0; i < pvStateSets->size(); i++)
	{
		pState = new State();
		pState->setId(i);
		pState->setEdgeNext(NULL);
		sIt = pvStateSets->at(i)->begin();
		pState->setType(pvStates->at(*sIt)->isTerminalState());
		pState->setComment(NULL);
		pDFiniteAutomataMin->addState(pState);
	}
	for (int i = 0; i < pvStateSets->size(); i++)
	{
		sIt = pvStateSets->at(i)->find(startState);
		if (sIt != pvStateSets->at(i)->end())
		{
			pDFiniteAutomataMin->setStartState(i);
		}
		sIt = pvStateSets->at(i)->begin();
		pState = pvStates->at(*sIt);
		pEdge = pState->nextEdge();
		while (pEdge != NULL)
		{
			pAddEdge = new Edge();
			pAddEdge->setIdentifiedCharIndex(pEdge->getIdentifiedCharIndex());
			pAddEdge->setNext(NULL);
			pAddEdge->setStateId(pvRes->at(pEdge->getStateId()));
			pDFiniteAutomataMin->addEdge(i, pAddEdge);
			pEdge = pEdge->next();
		}
	}

	for (int i = 0; i < pvStateSets->size(); i++)
	{
		delete pvStateSets->at(i);
	}
	delete pvStateSets;
	delete pvDic;
	delete pvRes;
	return pDFiniteAutomataMin;
}

bool DFiniteAutomata::analyse(string * str)
{
	Edge * pEdge;
	int i;
	const char * sentence = str->data();
	int curState = startState;
	int previous = 0;
	int length = strlen(sentence);
	for (i = 0; i < length; i++)
	{
		pEdge = pvStates->at(curState)->nextEdge();
		while (pEdge != NULL)
		{
			if (pvTermSym->at(pEdge->getIdentifiedCharIndex()) == sentence[i])
			{
				curState = pEdge->getStateId();
				break;
			}
			pEdge = pEdge->next();
		}
		if (pEdge == NULL)
		{
			if (pvStates->at(curState)->isTerminalState())
			{
				cout << "recognized: ";
				for (int j = previous; j < i; j++)
				{
					cout << sentence[j];
				}
				cout << endl;
				previous = i;
				i--;
				curState = startState;
				continue;
			}
			else
			{
				cout << "error: ";
				for (int j = previous; j <= i; j++)
				{
					cout << sentence[j];
				}
				cout << endl;
				return false;
			}
		}
	}
	if (pvStates->at(curState)->isTerminalState())
	{
		cout << "recognized: ";
		for (int j = previous; j < i; j++)
		{
			cout << sentence[j];
		}
		cout << endl;
	}
	else
	{
		cout << "error: ";
		for (int j = previous; j < i; j++)
		{
			cout << sentence[j];
		}
		cout << endl;
		return false;
	} 
	return true;
}

void DFiniteAutomata::test()
{
	cout << "start state: " << startState << endl;
	for (int i = 0; i < this->pvStates->size(); i++)
	{
		cout<< pvStates->at(i)->getId() << ' ' << pvStates->at(i)->isTerminalState() << "    ";
		Edge * pEdge = pvStates->at(i)->nextEdge();
		while (pEdge != NULL)
		{
			cout << pEdge->getStateId() << ' ' << pvTermSym->at(pEdge->getIdentifiedCharIndex()) << "    ";
			pEdge = pEdge->next();
		}
		cout << endl;
	}
}