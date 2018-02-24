#ifndef INTERACTIVE_GRAPH_STORE_H
#define INTERACTIVE_GRAPH_STORE_H

#include "GraphStore.h"
#include <fstream>

class InteractiveGraphStore
{
	enum Command
	{
		QUIT,
		CREATE_GRAPH,
		USE_GRAPH,
		DELETE_GRAPH,
		CREATE_NODE,
		DELETE_NODE,
		CREATE_ARC,
		DELETE_ARC,
		SEARCH,
		SAVE,
		PRINT
	};

	enum Algorithm
	{
		DIJKSTRA,
		BFS
	};

public:
	InteractiveGraphStore();
	bool parseAndExecuteCommand();
	void load(const char* path);

private:
	Command getCommand(const char*&, const char*&);
	void parseIDs(const char*, const char*);
	void parseAll();
	Algorithm parseAlg(const char*, const char*);
	

	Command create_h(const char*&, const char*&);
	Command delete_h(const char*&, const char*&);
	Command sthElse_h(const char*&, const char*&);

private:
	GraphStore gStore;

	char pth[_MAX_PATH];
	char buff[256];
	Command command;
	Algorithm algorithm;
	const char* id1;
	const char* id2;
	bool isDirected;
	int weight;
};

#endif // !INTERACTIVE_GRAPH_STORE_H