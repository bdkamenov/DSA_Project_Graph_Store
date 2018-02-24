#ifndef GRAPH_STORE_H
#define GRAPH_STORE_H

#include <unordered_map>
#include "Graph.h"

class GraphStore
{
	enum Error
	{
		GRAPH_EXIST,
		GRAPH_DOESNT_EXIST,
		NO_CHOSEN_GRAPH
	};

public:
	GraphStore();

	void createGraph(const std::string&, bool);
	void addGraph(const std::string& id, const Graph&);
	void removeGraph(const std::string&);
	void setCurr(const std::string&);
	void save(std::ofstream&);
	void load(std::ifstream&);

	Graph& useCurrGraph();
private:
	void logError(const Error, std::ostream& = std::cerr) const;


private:
	std::unordered_map<std::string, Graph> store;
	std::string curr;
	
};

#endif // !GRAPH_STORE_H