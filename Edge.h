#pragma once

class Edge
{
private:
	int stateId;
	int indexIdentifiedChar;
	Edge * pEdgeNext;
public:
	Edge(void);
	~Edge(void);
	int getStateId();
	int getIdentifiedCharIndex();
	Edge * next();
	void setStateId(int);
	void setIdentifiedCharIndex(int);
	void setNext(Edge *);
};
