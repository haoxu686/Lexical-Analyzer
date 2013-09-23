#include "HashMapNode.h"

HashMapNode::HashMapNode(void)
{
}

HashMapNode::~HashMapNode(void)
{
	if (this->pNodeNext == NULL)
	{
		return;
	}
	else
	{
		delete this->pNodeNext;
	}
}

int HashMapNode::getStateId()
{
	return this->stateId;
}

NonTerminalSymbol * HashMapNode::getNonTerminalSymbol()
{
	return this->pNonTermSym;
}

HashMapNode * HashMapNode::next()
{
	return this->pNodeNext;
}

void HashMapNode::setStateId(int id)
{
	this->stateId = id;
}

void HashMapNode::setNonTerminalSymbol(NonTerminalSymbol * pTermSymbol)
{
	this->pNonTermSym = pTermSymbol;
}

void HashMapNode::setNext(HashMapNode * next)
{
	this->pNodeNext = next;
}
