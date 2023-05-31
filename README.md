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
In the main function, we create an object of the Command class and call the read_command function.  

```c++
#include "../include/main.hpp"

int main()
{
    Command command;
    command.read_command();
}
```
