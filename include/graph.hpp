#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

#define SPACE ' '
#define DELIMITER '-'

#define ERR_SAMENODES "Error: u and v are the same."

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

    bool handle_same_nodes(int u, int v);

    std::vector<graphs> split_string(std::string inputString, bool just_split);
};

#endif
