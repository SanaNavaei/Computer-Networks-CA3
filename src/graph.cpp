#include "../include/graph.hpp"

bool Graph::handle_same_nodes(int u, int v)
{
    if(u == v)
    {
        std::cout << ERR_SAMENODES << std::endl;
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
    int a = countDigits(-3);
    std::cout << a << std::endl;
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

        if(space_size % 2 == 0)
        {
            for (int j = 0; j < space_size / 2; j++)
            {
                std::cout << " ";
            }
            std::cout << node;
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
            std::cout << node;
            for (int j = 0; j < space_size / 2 + 1; j++)
            {
                std::cout << " ";
            }
        }
    }

    std::cout << std::endl;
    int delim_count = (nodes.size() + 2) * max_size;
    for (int i = 0; i < delim_count; i++)
    {
        std::cout << "-";
    }

    std::cout << std::endl;
    for(auto node: nodes)
    {
        int findNumDigit = countDigits(node);
        int space_size = max_size - findNumDigit;

        if(space_size % 2 == 0)
        {
            for (int j = 0; j < space_size / 2; j++)
            {
                std::cout << " ";
            }
            std::cout << node;
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
            std::cout << node;
            for (int j = 0; j < space_size / 2 + 1; j++)
            {
                std::cout << " ";
            }
        }
        std::cout << "|";

        for(auto node2: nodes)
        {
            bool found = false;
            for (int i = 0; i < edges.size(); i++)
            {
                
                if(edges[i].u == node && edges[i].v == node2)
                {
                    int findNumDigit = countDigits(edges[i].w);
                    int space_size = max_size - findNumDigit;
                    found = true;

                    if(space_size % 2 == 0)
                    {
                        for (int j = 0; j < space_size / 2; j++)
                        {
                            std::cout << " ";
                        }
                        std::cout << edges[i].w;
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
                        std::cout << edges[i].w;
                        for (int j = 0; j < space_size / 2 + 1; j++)
                        {
                            std::cout << " ";
                        }
                    }
                    break;
                }
            }
            if(!found)
            {
                //print 0
                int findNumDigit = countDigits(0);
                int space_size = max_size - findNumDigit;
                for (int j = 0; j < space_size / 2; j++)
                {
                    std::cout << " ";
                }
                std::cout << 0;
                for (int j = 0; j < space_size / 2; j++)
                {
                    std::cout << " ";
                }
            }
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

void Graph::modify(std::string args)
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

bool check_format(std::string args)
{
    int size = args.size();
    bool error_flag = false;
    if(size != 3 || args[1] != '-')
        error_flag = true;
    
    else if(!isdigit(args[0]) || !isdigit(args[2]))
        error_flag = true;
    if(error_flag)
    {
        std::cout << ERROR << std::endl;
        return false;
    }
    return true;
}

void Graph::remove(std::string args)
{
    if(check_format(args))
    {
        std::string ss = args.substr(0,1);
        std::string dd = args.substr(2,1);
        int s = stoi(ss);//std::strtol(args[0].c_str(), nullptr, 10);
        int d = stoi(dd);
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
}
