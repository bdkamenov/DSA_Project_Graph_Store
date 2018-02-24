#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <functional>


struct algorithms_node_info
{
	std::string parent;
	int distance;
	bool visited;
};



class Graph
{
	enum Error
	{
		NODE_EXIST,
		NODE_DOESNT_EXIST,
		EDGE_EXIST,
		EDGE_DOESNT_EXIST,
		PATH_DOESNT_EXIST
	};

	struct Edge
	{
		std::string id;
		int weigth;

		Edge(const std::string& id = "", int weigth = 1) :id(id), weigth(weigth) {}

		bool operator>(const Edge& rhs) const
		{
			return weigth > rhs.weigth;
		}

		friend std::ostream& operator<<(std::ostream& out, const Edge& elem)
		{
			out << "( " << elem.id << " " << elem.weigth << " )";
			return out;
		}

		friend std::istream& operator>>(std::istream& in, Edge& elem)
		{
			char br;
			in >> br;
			in >> elem.id;
			in >> elem.weigth >> br;
			return in;
		}
	};

public:
	Graph(bool = true);

	void addNode(const std::string&);
	void addEdge(const std::string&, const std::string&, int = 1);

	void removeNode(const std::string&);
	void removeEdge(const std::string&, const std::string&);

	void print(std::ostream&) const;
	void save(std::ofstream&) const;
	void load(std::ifstream&);

	///	A L G O R I T H M S
	void BFS(const std::string&, const std::string&);
	void dijkstra(const std::string&, const std::string&);

private:
	void logError(const Error, std::ostream& = std::cerr) const;
	void addEdge_h(const std::string&, const std::string&, int);
	void removeEdge_h(const std::string&, const std::string&);


	const char* NO_PARENT = "?";
	const int MY_INFINITY = INT_MAX;

private:
	std::unordered_map<std::string, std::vector<Edge>> graph;
	bool isDirected;
};
#endif // !GRAPH_H