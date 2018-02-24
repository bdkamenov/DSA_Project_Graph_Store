#include "Graph.h"

Graph::Graph(bool directed) : isDirected(directed)
{
}

void Graph::addNode(const std::string& id)
{
	std::vector<Edge> empty;

	auto a = graph.insert({ id,empty });		/// returns pair of iterator and bool

	if (a.second == false)
	{
		logError(NODE_EXIST);
	}
}

void Graph::addEdge(const std::string& from, const std::string& to, int weight)
{
	if (isDirected)
	{
		addEdge_h(from, to, weight);
	}
	else
	{
		addEdge_h(from, to, weight);
		addEdge_h(to, from, weight);
	}
}

void Graph::removeNode(const std::string& id)
{
	std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.find(id);	/// or we can simply use auto

	if (it == graph.end())
	{
		throw std::logic_error("The node doesn't exist!\n");
	}
	else
	{
		graph.erase(it);
	}
}

void Graph::removeEdge(const std::string& from, const std::string& to)
{
	if (isDirected)
	{
		removeEdge_h(from, to);
	}
	else
	{
		removeEdge_h(from, to);
		removeEdge_h(to, from);
	}
}

void Graph::print(std::ostream& out) const
{
	for (std::unordered_map<std::string, std::vector<Edge>>::const_iterator it = graph.begin(); it != graph.end(); it++)
	{
		out << "Node ID: " << it->first << "\nEdges ID/weight: ";

		for (std::vector<Edge>::const_iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			out << it1->id << "/" << it1->weigth << " ";
		}

		out << std::endl;
	}
}

void Graph::save(std::ofstream& file) const
{
	file << (isDirected ? " directed\n" : " undirected\n");

	file << graph.size() << "\n";


	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		file << it->first << " " << it->second.size();

		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			file << " " << *it1;
		}

		file << std::endl;
	}
}

void Graph::load(std::ifstream& file)
{
	std::string directed;
	std::string id;
	Edge ed;
	size_t cntOfNodes = 0;
	size_t cntOfEdges = 0;

	file >> directed;

	isDirected = (directed == "directed") ? true : false;

	file >> cntOfNodes;
	for (size_t i = 0; i < cntOfNodes; i++)
	{
		file >> id;
		file >> cntOfEdges;
		graph[id];
		for (size_t j = 0; j < cntOfEdges; j++)
		{
			file >> ed;
			graph[id].push_back(ed);
		}
	}
}

void Graph::logError(const Error error, std::ostream& log) const
{
	switch (error)
	{
	case Graph::NODE_EXIST:
		log << "The node already exist!\n";
		break;

	case Graph::NODE_DOESNT_EXIST:
		log << "The node doesn't exist!\n";
		break;

	case Graph::EDGE_EXIST:
		log << "The edge already exist!\n";
		break;

	case Graph::EDGE_DOESNT_EXIST:
		log << "The edge doesn't exist!\n";
		break;

	default:
		break;

	}
}

void Graph::addEdge_h(const std::string& from, const std::string& to, int weight)
{
	std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.find(from);	/// or we can simply use auto

	if (it == graph.end())
	{
		logError(NODE_DOESNT_EXIST);
	}
	else
	{
		it->second.push_back({ to, weight });
	}
}

void Graph::removeEdge_h(const std::string& from, const std::string& to)
{
	std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.find(from);	/// or we can simply use auto

	if (it == graph.end())
	{
		logError(NODE_DOESNT_EXIST);
	}
	else
	{
		for (std::vector<Edge>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (it1->id == to)
			{
				it->second.erase(it1);
				return;
			}
		}
		logError(EDGE_DOESNT_EXIST);
	}
}

void printPath(std::unordered_map<std::string, algorithms_node_info>& nodes_info, const std::string& prev)
{
	if (prev == "?")
		return;

	printPath(nodes_info, nodes_info[prev].parent);
	std::cout << prev << "->";
}

void Graph::BFS(const std::string& from, const std::string& to)
{
	std::unordered_map<std::string, algorithms_node_info> nodes_info;
	for (std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		nodes_info[it->first] = { NO_PARENT, 0, false };
	}

	std::queue<std::string> wave;
	wave.push(from);

	while (!wave.empty())
	{
		std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.find(wave.front());

		if (it == graph.end())
		{
			wave.pop();
			continue;
		}

		for (std::vector<Edge>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (!nodes_info[it1->id].visited)
			{
				nodes_info[it1->id].visited = true;
				nodes_info[it1->id].parent = wave.front();
				wave.push(it1->id);
			}
		}

		wave.pop();

		if (!wave.empty() && wave.front() == to)
		{
			break;
		}
	}

	if (nodes_info[to].parent == NO_PARENT)
	{
		logError(PATH_DOESNT_EXIST);
		return;
	}
	else
	{
		printPath(nodes_info, to);
		std::cout << std::endl;
	}
}

void Graph::dijkstra(const std::string& from, const std::string& to)
{

	std::unordered_map<std::string, algorithms_node_info> nodes_info;
	for (std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		nodes_info[it->first] = { NO_PARENT, MY_INFINITY, false };
	}

	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> Q;

	nodes_info[from].distance = 0;
	Q.push({ from, nodes_info[from].distance });

	while (!Q.empty())
	{
		Edge cur = Q.top();
		Q.pop();

		nodes_info[cur.id].visited = true;

		std::unordered_map<std::string, std::vector<Edge>>::iterator it = graph.find(cur.id);
		if (it == graph.end())
			continue;

		for (std::vector<Edge>::iterator it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (!nodes_info[it1->id].visited)
			{
				if (nodes_info[it1->id].distance > nodes_info[cur.id].distance + it1->weigth)
				{
					nodes_info[it1->id].parent = cur.id;
					nodes_info[it1->id].distance = nodes_info[cur.id].distance + it1->weigth;
					Q.push({ it1->id, nodes_info[it1->id].distance });
				}

			}
		}

		if (cur.id == to)
			break;
	}

	if (nodes_info[to].parent == NO_PARENT)
	{
		logError(PATH_DOESNT_EXIST);
		return;
	}
	else
	{
		printPath(nodes_info, to);
		std::cout << nodes_info[to].distance << std::endl;
	}
}