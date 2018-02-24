#include "GraphStore.h"

GraphStore::GraphStore():curr("?")
{
}

void GraphStore::createGraph(const std::string& id, bool isDirected)
{
	auto res = store.insert({ id, isDirected });

	if (res.second == false)
	{
		logError(GRAPH_EXIST);
	}
}

void GraphStore::addGraph(const std::string& id, const Graph& g)
{
	Graph a = g;
	store.insert({ id, a });
}

void GraphStore::removeGraph(const std::string& id)
{
	std::unordered_map<std::string, Graph>::iterator it = store.find(id);

	if (it == store.end())
	{
		logError(GRAPH_DOESNT_EXIST);
		return;
	}

	if (id == curr)
	{
		curr = "?";
	}

	store.erase(it);
}

void GraphStore::setCurr(const std::string& str)
{
	if (store.find(str) != store.end())
	{
		curr = str;
	}
	else
	{
		logError(GRAPH_DOESNT_EXIST);
	}
}

void GraphStore::save(std::ofstream& file)
{
	file << store.size() << std::endl;

	for (auto it = store.begin(); it != store.end(); it++)
	{
		file << it->first;
		it->second.save(file);
	}
}

void GraphStore::load(std::ifstream& file)
{
	size_t cntOfGraphs = 0;

	file >> cntOfGraphs;

	std::string id;
	for (size_t i = 0; i < cntOfGraphs; i++)
	{
		Graph g;
		file >> id;
		g.load(file);
		store.insert({ id,g });
	}
}

Graph& GraphStore::useCurrGraph()
{
	/*if (curr == "?")
	{
		logError(NO_CHOSEN_GRAPH);
		return;
	}*/
	return store.find(curr)->second;
}


void GraphStore::logError(const Error error, std::ostream& log) const
{
	switch (error)
	{
	case GraphStore::GRAPH_EXIST:
		log << "The graph already exist!\n";
		break;

	case GraphStore::GRAPH_DOESNT_EXIST:
		log << "The graph doesn't exist!\n";
		break;

	case GraphStore::NO_CHOSEN_GRAPH:
		log << "There is no chosen graph for work!\n";
		break;

	default:
		break;
	}
}
