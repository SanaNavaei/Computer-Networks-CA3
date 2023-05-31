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
