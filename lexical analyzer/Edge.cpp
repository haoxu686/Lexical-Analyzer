#include "StdAfx.h"
#include "Edge.h"

Edge::Edge(void)
{
	pEdgeNext = NULL;
}

Edge::~Edge(void)
{
	if (pEdgeNext != NULL)
	{
		delete pEdgeNext;
	}
}

int Edge::getStateId()
{
	return stateId;
}

int Edge::getIdentifiedCharIndex()
{
	return indexIdentifiedChar;
}

Edge * Edge::next()
{
	return pEdgeNext;
}

void Edge::setStateId(int id)
{
	stateId = id;
}

void Edge::setIdentifiedCharIndex(int index)
{
	indexIdentifiedChar = index;
}

void Edge::setNext(Edge * next)
{
	pEdgeNext = next;
}