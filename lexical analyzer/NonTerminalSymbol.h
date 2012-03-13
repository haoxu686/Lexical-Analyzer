#pragma once

class NonTerminalSymbol
{
private:
	int hash;
	string * strValue;
public:
	NonTerminalSymbol(string *);
	~NonTerminalSymbol(void);
	string * getValue();
	int hashCode();
};
