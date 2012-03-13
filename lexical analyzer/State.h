#pragma once
#include "Edge.h"

class State
{
private:
	int id;
	Edge * pEdgeNext;
	bool isTermState;
	string * sComment;
public:
	State(void);
	~State(void);
	Edge * nextEdge();
	int getId();
	bool isTerminalState();
	string * getComment();
	void setEdgeNext(Edge *);
	void setId(int);
	void setType(bool);
	void setComment(string *);
	void addAdjacent(Edge *);
};
