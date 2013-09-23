#include "HashMap.h"

HashMap::HashMap(void)
{
	pvHashMap = new vector<HashMapNode *>;
	HashMapNode * pNode;
	for (int i = 0; i < 1000; i++)
	{
		pNode = new HashMapNode();
		pNode->setStateId(-1);
		pNode->setNonTerminalSymbol(NULL);
		pNode->setNext(NULL);
		this->pvHashMap->push_back(pNode);
	}		
}

HashMap::~HashMap(void)
{
	for (int i = 0; i < pvHashMap->size(); i++)
	{
		delete pvHashMap->at(i);
	}
	delete pvHashMap;
}

void HashMap::put(NonTerminalSymbol * key, int value)
{
	int hash = key->hashCode();
	hash = hash % pvHashMap->size();
	HashMapNode * pNode = pvHashMap->at(hash);
	HashMapNode * pNodePre = pNode;
	pNode = pNode->next();
	while (pNode != NULL)
	{
		if (pNode->getNonTerminalSymbol()->getValue()->compare(*key->getValue()) == 0)
		{
			break;
		}
		pNodePre = pNode;
		pNode = pNode->next();
	}
	if (pNode == NULL)
	{
		pNode = new HashMapNode();
		pNode->setNonTerminalSymbol(key);
		pNode->setStateId(value);
		pNode->setNext(NULL);
		pNodePre->setNext(pNode);
	}
	else
	{
		pNode->setNonTerminalSymbol(key);
		pNode->setStateId(value);
	}
}

int HashMap::get(NonTerminalSymbol * key)
{
	int hash = key->hashCode();
	hash = hash % pvHashMap->size();
	HashMapNode * pNode = pvHashMap->at(hash);
	pNode = pNode->next();
	while (pNode != NULL)
	{
		if (pNode->getNonTerminalSymbol()->getValue()->compare(*key->getValue()) == 0)
		{
			break;
		}
		pNode = pNode->next();
	}
	if (pNode == NULL)
	{
		return -1;
	}
	else
	{
		return pNode->getStateId();
	}
}
