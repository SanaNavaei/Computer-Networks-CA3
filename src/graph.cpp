#include "../include/graph.hpp"

void Graph::print_handler(std::string word, int space_size)
{
    if(space_size % 2 == 0)
    {
        for (int j = 0; j < space_size / 2; j++)
        {
            std::cout << " ";
        }
        std::cout << word;
        for (int j = 0; j < space_size / 2; j++)
        {
            std::cout << " ";
        }
    }
    else
    {
        for (int j = 0; j < space_size / 2; j++)
        {
            std::cout << " ";
        }
        std::cout << word;
        for (int j = 0; j < space_size / 2 + 1; j++)
        {
            std::cout << " ";
        }
    }
}

bool Graph::handle_same_nodes(int u, int v)
{
    if(u == v)
    {
        std::cout << ERROR << std::endl;
        return true;
    }
    return false;
}

std::vector<graphs> Graph::split_string(std::string inputString, bool just_split)
{
    std::vector<graphs> graphs_vec;
    std::stringstream ss(inputString);
    std::string word;

    while (std::getline(ss, word, SPACE))
    {
        std::stringstream row_ss(word);
        std::string row_word;
        
        int u, v, w, counter = 0;
        bool is_minus = false;
        while (std::getline(row_ss, row_word, DELIMITER))
        {
            if(row_word == "")
            {
                is_minus = true;
                continue;
            }
            if(counter == 0)
            {
                u = stoi(row_word);
                if(is_minus)
                {
                    u = -u;
                    is_minus = false;
                }
            }
            else if(counter == 1)
            {
                v = stoi(row_word);
                if(is_minus)
                {
                    v = -v;
                    is_minus = false;
                }
            }
            else if(counter == 2)
            {
                w = stoi(row_word);
                if(is_minus)
                {
                    w = -w;
                    is_minus = false;
                }
            }
            counter++;
        }

        //check if u and v are not the same
        if(!just_split)
        {
            if(!handle_same_nodes(u, v))
            {
                graphs g = {u, v, w};
                graphs rg = {v, u, w};
                graphs_vec.push_back(g);
                graphs_vec.push_back(rg);

                nodes.insert(u);
                nodes.insert(v);
            }
        }
        else
        {
            graphs g = {u, v, w};
            graphs_vec.push_back(g);
        }
    }
    return graphs_vec;
}

void Graph::create_graph(std::string args)
{
    edges = split_string(args, false);
    std::cout << "OK" << std::endl;
}

int countDigits(int num) {
    int count = 0;

    if (num < 0)
    {
        num = -num;
        count++;
    }

    if(num == 0)
    {
        return 1;
    }

    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

void Graph::show()
{
    if(edges.size() == 0)
    {
        std::cout << EMPTY_GRAPH << std::endl;
        return;
    }

    std::cout << "     |";
    int max_size = 5;
    for (auto node: nodes)
    {
        int findNumDigit = countDigits(node);
        int space_size = max_size - findNumDigit;
        print_handler(std::to_string(node), space_size);
    }

    std::cout << std::endl;
    int delim_count = (nodes.size() + 2) * max_size;
    for (int i = 0; i < delim_count; i++)
        std::cout << "-";

    std::cout << std::endl;
    for(auto node: nodes)
    {
        int findNumDigit = countDigits(node);
        int space_size = max_size - findNumDigit;
        print_handler(std::to_string(node), space_size);
        std::cout << "|";

        for(auto node2: nodes)
        {
            if(node == node2)
            {
                //print 0
                int findNumDigit = countDigits(0);
                int space_size = max_size - findNumDigit;
                print_handler(std::to_string(0), space_size);
                continue;
            }
            
            bool found = false;
            for (int i = 0; i < edges.size(); i++)
            {
                
                if(edges[i].u == node && edges[i].v == node2)
                {
                    int findNumDigit = countDigits(edges[i].w);
                    int space_size = max_size - findNumDigit;
                    found = true;
                    print_handler(std::to_string(edges[i].w), space_size);
                    break;
                }
            }
            if(!found) //print -1
                std::cout << " " << -1 << "  ";
        }
        std::cout << std::endl;
    }
}

int Graph::check_if_exist(int s, int d)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if((edges[i].u == s && edges[i].v == d) || (edges[i].v == s && edges[i].u == d))
        {
            return i + 1;
        }
    }
    return 0;
}

std::vector<std::string> check_format(std::string args)
{
    std::stringstream ss(args);
    std::string item;
    std::vector<std::string>items;
    while(std::getline(ss, item, DELIMITER))
    {
        items.push_back(item);
    }
    int size = items.size();
    bool error_flag = false;
    if(size != 2)
        error_flag = true;
    
    else if(!(strspn(items[0].c_str(), "0123456789" ) == items[0].size()) || 
            !(strspn(items[1].c_str(), "0123456789" ) == items[1].size()))
        error_flag = true;
    if(error_flag)
    {
        std::vector<std::string> not_ok;
        not_ok.push_back("");
        return not_ok;
    }
    return items;
}

bool check_extended_format(std::string args)
{
    std::stringstream ss(args);
    std::string item;
    std::vector<std::string>items;
    while(std::getline(ss, item, DELIMITER))
    {
        items.push_back(item);
    }
    bool error_flag = false;
    if(items.size() == 3)
    {
        if(!(strspn( items[0].c_str(), "0123456789" ) == items[0].size()) || 
           !(strspn( items[1].c_str(), "0123456789" ) == items[1].size()) ||
           !(strspn( items[2].c_str(), "0123456789" ) == items[2].size()))
           error_flag = true;
    }
    else if(items.size() == 4)
    {
        if(!(strspn( items[0].c_str(), "0123456789" ) == items[0].size()) || 
           !(strspn( items[1].c_str(), "0123456789" ) == items[1].size()) ||
           !(strspn( items[3].c_str(), "0123456789" ) == items[2].size()) ||
           !(strspn( items[2].c_str(), "" ) == items[2].size()))
           error_flag = true;        
    }
    else 
    {
        error_flag = true;
    }
    if(error_flag)
    {
        std::cout << ERROR << std::endl;
        return false;
    }
    return true;
}

void Graph::modify(std::string args)
{
    if(check_extended_format(args))
    {
        std::vector<graphs> this_edge = split_string(args, true);
        int s = this_edge[0].u;
        int d = this_edge[0].v;
        int c = this_edge[0].w;
        if (s == d)
        {
            std::cout << ERROR << std::endl;
        }
        else if(nodes.count(s) && nodes.count(d))
        {
            int index;
            if(index = check_if_exist(s, d))
            {
                edges[index - 1].w = c;
                edges[index].w = c;
            }
            else
            {
                graphs new_graph = {s, d, c};
                graphs new_graph2 = {d, s, c};
                edges.push_back(new_graph);
                edges.push_back(new_graph2);
            }
            std::cout << "OK" << std::endl;
        }
        else
        {
            std::cout << ERROR << std::endl;   
        }
    }
}

void Graph::remove(std::string args)
{

    std::vector<std::string> result = check_format(args);
    if(result[0] != "")
    {
        int s = stoi(result[0]);//std::strtol(args[0].c_str(), nullptr, 10);
        int d = stoi(result[1]);
        int index;
        if (nodes.count(s) && nodes.count(d))
        {
            if(index = check_if_exist(s, d))
            {
                edges.erase(edges.begin() + index);
                edges.erase(edges.begin() + index - 1);
                std::cout << "OK" << std::endl;
            }
            else
            {
                std::cout << ERROR << std::endl;
            }
        }
        else
        {
            std::cout << ERROR << std::endl;
        }
    }
    else
        std::cout << ERROR << std::endl; 
}

void Graph::print_lsrp2(int source, std::vector<int> &distance, std::vector<int> &parent)
{
    std::cout << "  Path  [s] -> [d]  | Min-Cost | Shortest-Path \n";
    for(auto node: nodes)
    {
        if(source == node)
            continue;

        //print path
        std::string path = std::to_string(source) + "->" + std::to_string(node);
        int size = path.size();
        int space_size = 20 - size;

        print_handler(path, space_size);
        std::cout << "|";

        //print min cost
        int distance_ = distance[node];
        if (distance[node] == INFINITY)
            distance_ = -1;
        int findNumDigit = countDigits(distance_);

        space_size = 10 - findNumDigit;
        print_handler(std::to_string(distance_), space_size);
        std::cout << "|";

        //print shortest paht
        std::string path_ = "";
        int par = node;
        while (parent[par] != -1)
        {
            path_ = " -> " + std::to_string(par) + path_;
            par = parent[par];
        }
        if(path_ != "")
            std::cout << " " << source << path_;
        else 
            std::cout << " No path!";
        std::cout << std::endl;
    }
}

void Graph::print_lsrp(std::vector<int> &distance)
{
    int max_size = 5;
    std::cout << "Dest";
    for(auto node:nodes)
    {
        int findNumDigit = countDigits(node);
        int space_size = max_size - findNumDigit;

        print_handler(std::to_string(node), space_size);
        std::cout << "|";
    }
    std::cout << std::endl;

    std::cout << "cost";
    for(auto node:nodes)
    {
        int findNumDigit;
        if(distance[node] == INFINITY)
        {
            findNumDigit = countDigits(-1);
            int space_size = max_size - findNumDigit;
            print_handler(std::to_string(-1), space_size);
        }
        else
        {
            findNumDigit = countDigits(distance[node]);
            int space_size = max_size - findNumDigit;
            print_handler(std::to_string(distance[node]), space_size);
        }
        std::cout << "|";
    }
    std::cout << std::endl;
    int node_size = nodes.size();
    for (int i = 0; i < 7 * nodes.size(); i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

int Graph::minDistance(std::vector<int> distance, std::vector<bool> visited)
{
    int min = INFINITY, min_index;
    for (int v = 0; v < nodes.size() + 1; v++)
        if (visited[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;
    return min_index;
}

void Graph::lsrp(int source)
{
    int nodes_size = nodes.size() + 1;
    std::vector<int> distance(nodes_size);
    std::vector<int> parent(nodes_size);
    std::vector<bool> visited(nodes_size);

    for (int i = 0; i < nodes_size; i++)
    {
        distance[i] = INFINITY;
        parent[i] = -1;
        visited[i] = false;
    }

    distance[source] = 0;

    for (int i = 0; i < nodes.size() - 1; i++)
    {
        int u1 = minDistance(distance, visited);
        visited[u1] = true;

        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if(u1 == u && visited[v] == false && distance[u] != INFINITY)
            {
                if(distance[u] + w < distance[v])
                {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                }
            }
        }
        std::cout << "Iter " << i + 1 << ":\n";
        print_lsrp(distance);
    }
    print_lsrp2(source, distance, parent);
}

void Graph::handler_lsrp(std::string args)
{
    auto start = high_resolution_clock::now();
    //check if we have source
    if(args.size() == 0)
    {
        for(auto node: nodes)
        {
            std::cout << "Iter " << node << ":\n";
            lsrp(node);
        }
    }
    else
    {
        int source = stoi(args);
        if(nodes.count(source))
        {
            lsrp(source);
        }
        else
        {
            std::cout << ERROR << std::endl;
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    std::cout << "Time taken by LSRP: "<< duration.count() << " nanoseconds" << std::endl;
}

void Graph::handler_dvrp(std::string args)
{
    auto start = high_resolution_clock::now();
    //check if we have source
    if(args.size() == 0)
    {
        for(auto node: nodes)
        {
            std::cout << "dvrp for node " << node << ":\n";
            dvrp(node);
        }
    }
    else
    {
        int source = stoi(args);
        if(nodes.count(source))
        {
            std::cout << "dvrp for node " << source << ":\n";
            dvrp(source);
        }
        else
        {
            std::cout << ERROR << std::endl;
        }
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    std::cout << "Time taken by DVRP: "<< duration.count() << " nanoseconds" << std::endl;
}

void Graph::dvrp(int source)
{
    int nodes_size = nodes.size() + 1;
    std::vector<int> distance(nodes_size);
    std::vector<int> parent(nodes_size);

    for (int i = 0; i < nodes_size; i++)
    {
        distance[i] = INFINITY;
        parent[i] = -1;
    }

    distance[source] = 0;
    for (int i = 1; i < nodes_size; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
    }

    print_dvrp(source, distance, parent);
}

void Graph::print_dvrp(int source,std::vector<int> &distance,  std::vector<int> &parent)
{
    std::cout << "   Dest   | Next Hop |   Dist   | Shortest-Path \n";
    std::cout << "---------------------------------------------------\n";

    int max_size = 10;
    int prev_par;
    for (auto node: nodes)
    {
        if(node == source)
        {
            //print dest node
            int findNumDigit = countDigits(node);
            int space_size = max_size - findNumDigit;

            print_handler(std::to_string(node), space_size);
            std::cout << "|";

            //print Next Hop
            findNumDigit = countDigits(node);
            space_size = max_size - findNumDigit;
            print_handler(std::to_string(node), space_size);
            std::cout << "|";

            //print distance
            findNumDigit = countDigits(0);
            space_size = max_size - findNumDigit;
            print_handler(std::to_string(0), space_size);
            std::cout << "|";

            //print path
            std::cout << " [" << node << "]" << std::endl;
            continue;
        }
        
        //print dest node
        int findNumDigit = countDigits(node);
        int space_size = max_size - findNumDigit;

        print_handler(std::to_string(node), space_size);
        std::cout << "|";

        //print Next Hop
        int par = node;
        std::string path = "";
        while (parent[par] != -1)
        {
            path = " -> " + std::to_string(par) + path;
            prev_par = par;
            par = parent[par];
        }
        findNumDigit = countDigits(prev_par);
        space_size = max_size - findNumDigit;
        print_handler(std::to_string(prev_par), space_size);
        std::cout << "|";

        //print distance
        findNumDigit = countDigits(distance[node]);
        space_size = max_size - findNumDigit;
        print_handler(std::to_string(distance[node]), space_size);
        std::cout << "|";

        //print path
        std::cout << " [" << source << path << "]";
        std::cout << std::endl;
    }
}
