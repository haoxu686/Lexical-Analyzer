// lexical analyzer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include "DFiniteAutomata.h"
#include "FiniteAutomata.h"
#include "Grammar.h"

class NonTerminalSymbol;

int main() {
	ifstream infile("1.txt", ios::in);
	if (!infile)
	{
		cout << "can not open file 1.txt" << endl;
		return 1;
	}

	Grammar * pGrammar = new Grammar();
	Production * pProduction = NULL;
	NonTerminalSymbol * pNonTermSymLeft = NULL;
	NonTerminalSymbol * pNonTermSymRight = NULL;
	map<char, int> * pMap = new map<char, int>;
	map<char, int>::iterator it;
	vector<char> * pvTermSym = new vector<char>;
	pMap->clear();
	pvTermSym->clear();
	pMap->insert(pair<char, int>(NULL, 0));
	pvTermSym->push_back(NULL);

	string production;
	string * strNonTermLeft;
	string * strNonTermRight;
	char cTermChar;
	int indexSeperator;
	char buffer[3000];
	while (infile.getline(buffer, 3000))
	{
		production.assign(buffer);
		indexSeperator = production.find("->");
		strNonTermLeft = new string();
		*strNonTermLeft = production.substr(0, indexSeperator);
		indexSeperator += 2;
		cTermChar = production[indexSeperator];
		if (cTermChar == NULL)
		{
			indexSeperator--;
		}
		else
		{
			it = pMap->find(cTermChar);
			if (it == pMap->end())
			{
				pMap->insert(pair<char, int>(cTermChar, pvTermSym->size()));
				pvTermSym->push_back(cTermChar);
			}
		}
		indexSeperator ++;
		strNonTermRight = new string();
		*strNonTermRight = production.substr(indexSeperator);

		pNonTermSymLeft = new NonTerminalSymbol(strNonTermLeft);
		pNonTermSymRight = new NonTerminalSymbol(strNonTermRight);

		pProduction = new Production(pNonTermSymLeft, pNonTermSymRight, pMap->find(cTermChar)->second);
		pGrammar->addProduction(pProduction);

	}
	delete pMap;
	pGrammar->setTerminalSymbolSet(pvTermSym);
	infile.close();
	FiniteAutomata * pFiniteAutomata = pGrammar->toFiniteAutomata();
	DFiniteAutomata * pDFiniteAutomata = pFiniteAutomata->toDFA();
	DFiniteAutomata * pDFiniteAutomataMin = pDFiniteAutomata->mimimize();
	pDFiniteAutomataMin->test();
	string * sentence = new string();
	while (getline(cin, *sentence))
	{
		if (sentence->compare("exit") == 0)
		{
			break;
		}
		pDFiniteAutomata->analyse(sentence);
	}
	delete sentence;
	delete pDFiniteAutomataMin;
	delete pDFiniteAutomata;
	delete pFiniteAutomata;
	delete pGrammar;
	return 0;
}
