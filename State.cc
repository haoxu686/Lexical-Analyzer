#include <cstdlib>

#include "State.h"

State::State(void)
{
	pEdgeNext = NULL;
	sComment = NULL;
}

State::~State(void)
{
	if (this->pEdgeNext != NULL)
	{
		delete this->pEdgeNext;
	}
	if (sComment != NULL)
	{
		delete sComment;
	}
}

int State::getId()
{
	return this->id;
}

Edge * State::nextEdge()
{
	return this->pEdgeNext;
}


bool State::isTerminalState()
{
	return this->isTermState;
}

void State::setEdgeNext(Edge * edgeInstance)
{
	this->pEdgeNext = edgeInstance;
}

void State::setId(int id)
{
	this->id = id;
}

void State::setType(bool isTerminal)
{
	this->isTermState = isTerminal;
}

void State::addAdjacent(Edge * edgeInstance)
{
	Edge * pEdge;
	if (this->pEdgeNext == NULL)
	{
		this->pEdgeNext = edgeInstance;
	}
	else
	{
		pEdge = this->pEdgeNext;
		while (pEdge->next() != NULL)
		{
			pEdge = pEdge->next();
		}
		pEdge->setNext(edgeInstance);
	}
}

void State::setComment(string * sCommnet)
{
	this->sComment = sComment;
}
