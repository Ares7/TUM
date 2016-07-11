#include <iostream>

#include <list>
#include <limits.h>
#include <cstring>

#include <stdlib.h>

#include <algorithm>
#include <map>
using namespace std;

class Graph
{
    int V;
    list<int>* adj;
    bool isCyclicUtil(int v, bool visited[], bool* rs);

public:
    Graph(int V);
    void addEdge(int v, int w);
    bool isCyclic();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
    if (visited[v] == false)
    {
        // Mark the current node as visited
        visited[v] = true;
        recStack[v] = true;

        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }
    }
    recStack[v] = false; // remove the vertex from recursion stack
    return false;
}

bool Graph::isCyclic()
{

    bool* visited = new bool[V];
    bool* recStack = new bool[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;

    return false;
}


int main()
{
    // I assume that the schedule will be short (relatively), so i can use
    // additional DS:

    std::map<string, string> mymap;
    std::map<string, string>::iterator it = mymap.begin();

    std::cout << "Enter a sequence of operations in the form of w 1 x r 2 x: ";
    string in_seq;
    getline(cin, in_seq);

    Graph test_graph(in_seq.length()); // n + 1 to avoid SEGFAULT

    int i = 0;
    int k = 0;
    while (i < in_seq.length())
    {
        string tnum, elem;
        char type;
        type = in_seq[i];
        elem = in_seq[i + 4];
        tnum = to_string(atoi(in_seq.substr(i + 2, 1).c_str()));

        string obj_param = type + tnum;

        std::pair<std::map<string, string>::iterator, bool> ret;
        ret = mymap.insert(std::pair<string, string>(type + elem, obj_param));


        int from_node = ret.first->second[1] - '0';
        int to_node = stoi(tnum);

        // std::cout << " 22 with a value of " << ret.first->second[1] << '\n';//1-1, 0 -w

        if (ret.second == false && type == 'w')
        {
            // cout << "adding: " << from_node << to_node ;

            test_graph.addEdge(from_node, to_node);
        }

        string search_key = "r" + elem;

        map<string, string>::iterator ptr = mymap.find(search_key);
        string b3;
        if (ptr != mymap.end())
        {
            // element found;
            b3 = ptr->second;
            // cout <<  "b3:" << b3;
            test_graph.addEdge(from_node, to_node);
        }

        search_key = "w" + elem;
        ptr = mymap.find(search_key);
        if (ptr != mymap.end())
        {
            // element found;
            b3 = ptr->second;
            // cout <<  "b3:" << b3;
            test_graph.addEdge(from_node, to_node);
        }


        i = i + 6;
    }
 /*
 std::cout << "\nmymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
*/


    // Create a graph

    if (test_graph.isCyclic())
        cout << "False" << '\n';
    else
        cout << "True" << '\n';
    return 0;
}