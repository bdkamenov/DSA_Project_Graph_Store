#define _CRT_SECURE_NO_WARNINGS
#include "GraphStoreWithInterface.h"

InteractiveGraphStore::Command InteractiveGraphStore::getCommand(const char*& tok, const char*& delim)
{
	std::cin.getline(buff, 256);

	tok = strtok(buff, delim);

	if (!strcmp(tok, "CREATE"))
	{
		tok = strtok(nullptr, delim);
		return create_h(tok, delim);
	}
	else if (!strcmp(tok, "DELETE"))
	{
		tok = strtok(nullptr, delim);
		return delete_h(tok, delim);
	}
	else if (!strcmp(tok, "USE"))
	{
		tok = strtok(nullptr, delim);
		return sthElse_h(tok, delim);
	}
	else if (!strcmp(tok, "SEARCH"))
	{
		return SEARCH;
	}
	else if (!strcmp(tok, "PRINT"))
	{
		return PRINT;
	}
	else if (!strcmp(tok, "SAVE"))
	{
		return SAVE;
	}
}

void InteractiveGraphStore::parseIDs(const char* tok, const char* delim)
{
	id1 = tok;
	tok = strtok(nullptr, delim);
	const char* isDir = nullptr;

	switch (command)
	{
	case InteractiveGraphStore::CREATE_GRAPH:
		isDir = tok;
		if (isDir)
			isDirected = true;
		else
			isDirected = false;
		break;

	case InteractiveGraphStore::CREATE_ARC:
		id2 = tok;
		tok = strtok(nullptr, delim);
		if (tok)
			weight = atoi(tok);
		else
			weight = 1;
		break;

	case InteractiveGraphStore::DELETE_ARC:
		id2 = tok;
		break;

	case InteractiveGraphStore::SEARCH:
		id2 = tok;
		tok = strtok(nullptr, delim);
		algorithm = parseAlg(tok, delim);
		break;

	case InteractiveGraphStore::PRINT:
		break;

	default:
		break;
	}
}

InteractiveGraphStore::InteractiveGraphStore() :id1(nullptr), id2(nullptr), isDirected(true), weight(1)
{
}

bool InteractiveGraphStore::parseAndExecuteCommand()
{
	parseAll();

	switch (command)
	{
	default:
		return false;
		break;

	case InteractiveGraphStore::QUIT:
		return false;
		break;
	case InteractiveGraphStore::CREATE_GRAPH:
		gStore.createGraph(id1, isDirected);
		break;

	case InteractiveGraphStore::USE_GRAPH:
		gStore.setCurr(id1);
		return true;
		break;

	case InteractiveGraphStore::DELETE_GRAPH:
		gStore.removeGraph(id1);
		return true;
		break;

	case InteractiveGraphStore::CREATE_NODE:
		gStore.useCurrGraph().addNode(id1);
		return true;
		break;

	case InteractiveGraphStore::DELETE_NODE:
		gStore.useCurrGraph().removeNode(id1);
		return true;
		break;

	case InteractiveGraphStore::CREATE_ARC:
		gStore.useCurrGraph().addEdge(id1, id2, weight);
		return true;
		break;

	case InteractiveGraphStore::DELETE_ARC:
		gStore.useCurrGraph().removeEdge(id1, id2);
		return true;
		break;

	case InteractiveGraphStore::SEARCH:
		if (algorithm == DIJKSTRA)
		{
			gStore.useCurrGraph().dijkstra(id1, id2);
		}
		else if (algorithm == BFS)
		{
			gStore.useCurrGraph().BFS(id1, id2);
		}
		return true;
		break;

	case InteractiveGraphStore::PRINT:
		gStore.useCurrGraph().print(std::cout);
		return true;
		break;

	case InteractiveGraphStore::SAVE:
		std::ofstream file(pth);
		if (file)
		{
			gStore.save(file);
		}
		file.close();

		return true;
		break;
	}
}

void InteractiveGraphStore::load(const char* path)
{
	strcpy(pth, path);

	std::ifstream file(path);

	if (file.good())
		gStore.load(file);
	else
		std::cerr << "File couldn't open!\n";

	file.close();
}


void InteractiveGraphStore::parseAll()
{
	const char* tok;
	const char* delim = " ";
	command = getCommand(tok, delim);

	tok = strtok(nullptr, delim);
	parseIDs(tok, delim);
}

InteractiveGraphStore::Algorithm InteractiveGraphStore::parseAlg(const char* tok, const char* delim)
{
	if (!strcmp(tok, "bfs"))
		return BFS;
	else if (!strcmp(tok, "dijkstra"))
		return DIJKSTRA;
}

InteractiveGraphStore::Command InteractiveGraphStore::create_h(const char*& tok, const char*& delim)
{
	if (!strcmp(tok, "GRAPH"))
	{
		return CREATE_GRAPH;
	}
	else if (!strcmp(tok, "NODE"))
	{
		return CREATE_NODE;
	}
	else if (!strcmp(tok, "ARC"))
	{
		return CREATE_ARC;
	}
}

InteractiveGraphStore::Command InteractiveGraphStore::delete_h(const char*& tok, const char*& delim)
{
	if (!strcmp(tok, "GRAPH"))
	{
		return DELETE_GRAPH;
	}
	else if (!strcmp(tok, "NODE"))
	{
		return DELETE_NODE;
	}
	else if (!strcmp(tok, "ARC"))
	{
		return DELETE_ARC;
	}
}

InteractiveGraphStore::Command InteractiveGraphStore::sthElse_h(const char*& tok, const char*& delim)
{
	if (!strcmp(tok, "SEARCH"))
	{
		return SEARCH;
	}
	else if (!strcmp(tok, "GRAPH"))
	{
		return USE_GRAPH;
	}
}