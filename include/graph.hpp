#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <cstring>

#define SPACE ' '
#define DELIMITER '-'

#define ERR_SAMENODES "Error: u and v are the same."
#define EMPTY_GRAPH "The Adjacency Matrix is empty."
#define ERROR "Error"

struct graphs{
    int u, v, w;
};

class Graph
{
private:
    std::vector<graphs> edges;
    std::set<int> nodes;

public:
    void create_graph(std::string args);
    void show();
    void modify(std::string args);
    void remove(std::string args);

    bool handle_same_nodes(int u, int v);

    std::vector<graphs> split_string(std::string inputString, bool just_split);
    int check_if_exist(int s, int d);
};

#endif
