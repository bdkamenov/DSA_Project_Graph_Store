#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Graph.h"
#include "GraphStore.h"
#include "GraphStoreWithInterface.h"

void execute(const char* path)
{
	InteractiveGraphStore graphStore;

	graphStore.load(path);

	while (graphStore.parseAndExecuteCommand());
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return 1;
	}

	std::cout << "Searching " << argv[1] << " for graphs.txt\n";

	char path[_MAX_PATH];
	strcpy(path, argv[1]);
	strcat(path, "\\graphs.txt");

	execute(path);
}