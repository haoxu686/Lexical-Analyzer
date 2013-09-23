CC = g++
CFLAGS = -O3 -c
OBJS = DFiniteAutomata.o FiniteAutomata.o Edge.o Grammar.o HashMap.o HashMapNode.o NonTerminalSymbol.o Production.o State.o Main.o

all: lexical-analyzer

clean:
	rm *.o lexical-analyzer

lexical-analyzer: $(OBJS)
	$(CC) $(OBJS) -o lexical-analyzer

DFiniteAutomata.o: DFiniteAutomata.cc
	$(CC) $(CFLAGS) DFiniteAutomata.cc -o DFiniteAutomata.o

FiniteAutomata.o: FiniteAutomata.cc
	$(CC) $(CFLAGS) FiniteAutomata.cc -o FiniteAutomata.o

Edge.o: Edge.cc
	$(CC) $(CFLAGS) Edge.cc -o Edge.o

Grammar.o: Grammar.cc
	$(CC) $(CFLAGS) Grammar.cc -o Grammar.o

HashMap.o: HashMap.cc
	$(CC) $(CFLAGS) HashMap.cc -o HashMap.o

HashMapNode.o: HashMapNode.cc
	$(CC) $(CFLAGS) HashMapNode.cc -o HashMapNode.o

NonTerminalSymbol.o: NonTerminalSymbol.cc
	$(CC) $(CFLAGS) NonTerminalSymbol.cc -o NonTerminalSymbol.o

Production.o: Production.cc
	$(CC) $(CFLAGS) Production.cc -o Production.o

State.o: State.cc
	$(CC) $(CFLAGS) State.cc -o State.o

Main.o: Main.cc
	$(CC) $(CFLAGS) Main.cc -o Main.o
