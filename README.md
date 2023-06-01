# CN_CHomeworks_3
**Maryam Jafarabadi Ashtiani : 810199549**  
**Sana Sari Navaei : 810199435**  

# Project Description
In this project, we are going to implement 3 routing algorithms in a network. The routing algorithms are:
- Border Gateway(BGP)
- Link State(LSRP)
- Distance Vector(DVRP)

We will explain each of them in the following sections.  

# Code Description  
Now we explain each part of code. We start with the main function.

## Main Function
In the `main` function, we create an object of the Command class and call the `read_command` function.  

```c++
#include "../include/main.hpp"

int main()
{
    Command command;
    command.read_command();
}
```
## Command Class
In this class, we read the command from the user and call the related function. The function `read_command()` calls the function corresponding to each command based on the type of user command.  

```c++
#include "../include/command.hpp"

void Command::read_command()
{
    std::string command;

    while(getline(std::cin, command))
    {
        std::stringstream ss(command);
        std::string args;

        //get the command and the arguments
        getline(ss,command,' ');
        getline(ss,args);

        if(command == "topology")
        {
            graph.create_graph(args);
        }
        else if(command == "show")
        {
            graph.show();
        }
        else if(command == "modify")
        {
            graph.modify(args);
        }
        else if(command == "remove")
        {
            graph.remove(args);
        }
        else if(command == "dvrp")
        {
            graph.handler_dvrp(args);
        }
    }
}
```

Now we explain every command in detail and check their functions.  

## Topology Command
The `create_graph(std::string args)` function is a member function of the Graph class. In this function, we call the `split_string(args, false)` function to seperate the edges and determine each node's neighbors and the cost of the edge between them. After a topology created, we print `OK` to the console to show that the topology is created successfully. The source and second node should not be the same. If something like this happens, we print `ERROR` to the console.  

```c++
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
```

## Show Command
The `show()` function is a member function of the Graph class. In this function, we print the topology in a spcific format to the console.  when the first and second node are the same, we print 0 and when there is no edge between two nodes, we print -1.  

```c++
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
    {
        std::cout << "-";
    }

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
                for (int j = 0; j < space_size / 2; j++)
                {
                    std::cout << " ";
                }
                std::cout << 0;
                for (int j = 0; j < space_size / 2; j++)
                {
                    std::cout << " ";
                }
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
            if(!found)
            {
                //print -1
                int findNumDigit = countDigits(-1);
                int space_size = max_size - findNumDigit;

                std::cout << " " << -1 << "  ";
            }
        }
        std::cout << std::endl;
    }

}
```
