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
    }
}
