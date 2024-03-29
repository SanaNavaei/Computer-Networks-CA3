#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <cstring>
#include <climits>
#include <chrono>
using namespace std::chrono;

#define SPACE ' '
#define DELIMITER '-'
#define INFINITY 1e9

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
    void print_handler(std::string word, int space_size);
    void show();
    void modify(std::string args);
    void remove(std::string args);
    void handler_lsrp(std::string args);
    void lsrp(int source);
    void print_lsrp(std::vector<int> &distance);
    void print_lsrp2(int source, std::vector<int> &distance, std::vector<int> &parent);
    void handler_dvrp(std::string args);
    void dvrp(int source);
    void print_dvrp(int source, std::vector<int> &distance, std::vector<int> &parent);

    bool handle_same_nodes(int u, int v);
    
    int check_if_exist(int s, int d);
    int minDistance(std::vector<int> distance, std::vector<bool> visited);

    std::vector<graphs> split_string(std::string inputString, bool just_split);    
};

#endif
