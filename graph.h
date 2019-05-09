#ifndef GRAPH_H //Header protection
#define GRAPH_H
#include <vector>
#include <queue>
#include <map>
#include <iostream>
enum color_t
{
    GREY,
    BLACK,
    WHITE
};

class Graph
{
  private: /* will map an int to a list of its neighbors */
    std::map<int, std::vector<int>> vertices;
    bool directed;
    bool cyclic;
    bool DAG;
    std::map<int, color_t> color;
    std::map<int, int> distance;
    std::map<int, int> parents;
    std::map<int, int> discovery;
    std::map<int, int> finish;
    std::vector<int> topSort;
    int timing;
    int numVert;
    int numEdges;
    std::map<int, int> inDegree;
    std::map<int, int> outDegree;

  public:
    //default constructor
    Graph()
    {
        directed = false;
        cyclic = false;
        DAG = false;
        color[0] = WHITE;
        distance[0] = -1;
        parents[0] = 0;
        discovery[0] = -1;
        finish[0] = -1;
        topSort.push_back(0);
	numVert = 0;
	numEdges = 0;
    }
    //variable constructor
    Graph(bool set)
    {
        directed = set;
        cyclic = false;
        DAG = false;
        color[0] = WHITE;
        distance[0] = -1;
        parents[0] = 0;
        discovery[0] = -1;
        finish[0] = -1;
        topSort.push_back(0);
	numVert = 0;
	numEdges = 0;
    }
    /*Graph(const Graph &p1)
    {
        directed = p1.directed;
        cyclic = p1.cyclic;
        DAG = p1.DAG;
        topSort = p1.topSort;
        color = p1.color;
        distance = p1.distance;
        parents = p1.parents;
        discovery = p1.discovery;
        finish = p1.finish;
        vertices = p1.vertices;
        if(p1.directed){
            for (auto it = p1.vertices.begin(); it != p1.vertices.end(); ++it){
                
            }
        }
    }*/
    int getEdgeCount()
    {
      return numEdges;
    }
    int getVertCount()
    {
      return numVert;
    }
    auto getInDegree()
    {
      return inDegree;
    }
    auto getOutDegree()
    {
      return outDegree;
    }
    //prints what kind of graph it is
    void graphType()
    {
        if (directed == true)
        {
            std::cout << "This is a directed graph.\n";
        }
        else
        {
            std::cout << "This is an undirected graph.\n";
        }
    }
    // add a vertex to the graph2
    void addVertex(int key)
    {
        auto search = vertices.find(key);
        if (search != vertices.end())
            return;
        else
        {
            vertices.insert(std::pair<int, std::vector<int>>(key, 0));
        }
    }
    // add a directed or undirected edge to the graphprint();
    void addEdge(int v1, int v2)
    {
        auto search = vertices.find(v1);
        auto search2 = vertices.find(v2);

        if (search == vertices.end())
        {
            std::cout << "Vertex 1 DNE \n";
            return;
        }
        else if (search2 == vertices.end())
        {
            std::cout << "Vertex 2 DNE \n";
            return;
        }
        else
        {
            //checks if the edge already exists
            for (auto it = vertices[v1].begin(); it != vertices[v1].end(); ++it)
            {
                if (*it == v2)
                {
                    std::cout << "This edge already exists\n";
                    return;
                }
            }
            //checks if its a directed or undirected graph
            if (directed == false)
            {
                vertices[v1].push_back(v2);
                vertices[v2].push_back(v1);
            }
            else if (directed == true)
            {
                vertices[v1].push_back(v2);
            }
            //error checking
            else
            {
                std::cout << "Something's gone terribly wrong \n";
                return;
            }
        }
    }
    //adds edges for timing tests (no prints)
    void addEdgeTiming(int v1, int v2)
    {
        auto search = vertices.find(v1);
        auto search2 = vertices.find(v2);

        if (search == vertices.end())
        {
            return;
        }
        else if (search2 == vertices.end())
        {
            return;
        }
        else
        {
            //checks if the edge already exists
            for (auto it = vertices[v1].begin(); it != vertices[v1].end(); ++it)
            {
                if (*it == v2)
                {
                    //std::cout << "This edge already exists\n";
                    return;
                }
            }
            //checks if its a directed or undirected graph
            if (!directed)
            {
                vertices[v1].push_back(v2);
                vertices[v2].push_back(v1);
            }
            else
            {
                vertices[v1].push_back(v2);
            }
        }
    }
    // prints the adjacency list of each vertex, to show the structure
    void print()
    {
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            std::cout << it->first << ": is the node, its edges are:";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                //I can't for the life of me figure out how to get nothing to print here
                /*if (!*it2)
                    std::cout << "nothing";
                else*/
                std::cout << *it2 << " ";
            }
            std::cout << std::endl;
        }
    }
    // prints the vertices discovered by a BFS, starting at a given vertex
    void printBfs(int start)
    {
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            color.insert(std::pair<int, color_t>(it->first, WHITE));
            distance.insert(std::pair<int, int>(it->first, -1));
            parents.insert(std::pair<int, int>(it->first, NULL));
        }
        auto search = color.find(start);
        if (search == color.end())
            return;
        else
            color[start] = GREY;
        distance[start] = 0;
        std::queue<int> Q;
        Q.push(start);
        while (!Q.empty())
        {
            int u = Q.front();
            std::cout << "Node: " << u << " Distance:" << distance[u] << " parent: " << parents[u] << "\n";
            Q.pop();
            std::vector<int> neighbors = vertices[u];
            for (auto it2 = neighbors.cbegin(); it2 != neighbors.cend(); ++it2)
            {
                if (color[*it2] == WHITE)
                {
                    color[*it2] = GREY;
                    distance[*it2] = distance[u] + 1;
                    parents[*it2] = u;
                    Q.push(*it2);
                }
                color[u] = BLACK;
            }
        }
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            if (distance[it->first] == -1)
            {
                std::cout << "Node: " << it->first << " Distance:"
                          << "\u221E"
                          << "\n";
            }
        }
    }
    //Function to call for a DFS of a tree
    void DFS()
    {
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            color.insert(std::pair<int, color_t>(it->first, WHITE));
            discovery.insert(std::pair<int, int>(it->first, -1));
            finish.insert(std::pair<int, int>(it->first, -1));
            parents.insert(std::pair<int, int>(it->first, NULL));
        }
        timing = 0;

        for (auto it2 = vertices.cbegin(); it2 != vertices.cend(); ++it2)
        {
            if (color[it2->first] == WHITE)
                DFS_Visit(it2->first);
        }
    }
    //function called to actually preform the DFS operands
    void DFS_Visit(int node)
    {
        timing++;
        discovery[node] = timing;
        color[node] = GREY;
        std::vector<int> neighbors = vertices[node];
        for (auto it = neighbors.cbegin(); it != neighbors.cend(); ++it)
        {
            if (color[*it] == WHITE)
            {
                parents[*it] = node;
                DFS_Visit(*it);
            }
        }
        timing++;
        color[node] = BLACK;
        finish[node] = timing;
    }
    //function to call to check if a graph is both directed and acyclic. Uses a modified DFS for this
    void ADFS()
    {
        if (directed)
        {
            for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
            {
                color.insert(std::pair<int, color_t>(it->first, WHITE));
                discovery.insert(std::pair<int, int>(it->first, -1));
                finish.insert(std::pair<int, int>(it->first, -1));
                parents.insert(std::pair<int, int>(it->first, NULL));
            }
            timing = 0;

            for (auto it2 = vertices.cbegin(); it2 != vertices.cend(); ++it2)
            {
                if (color[it2->first] == WHITE)
                    ADFS_Visit(it2->first);
            }
        }
        else
        {
            std::cout << "This is not a directed graph \n";
            return;
        }
        if (cyclic)
        {
            std::cout << "This graph has at least one cycle.\n";
        }
        else
        {
            std::cout << "This graph is acyclic, and directed, therefore this is a DAG.\n";
            DAG = true;
        }
    }
    //function called by ADFS for preforming checks
    void ADFS_Visit(int node)
    {
        timing++;
        discovery[node] = timing;
        color[node] = GREY;
        std::vector<int> neighbors = vertices[node];
        for (auto it = neighbors.cbegin(); it != neighbors.cend(); ++it)
        {
            if (parents[node] == GREY)
            {
                if (parents[node] != *it)
                    cyclic = true;
            }
            else if (color[*it] == WHITE)
            {
                parents[*it] = node;
                ADFS_Visit(*it);
            }
        }
        timing++;
        color[node] = BLACK;
        finish[node] = timing;
    }
    //function called to do a topological sort
    void topSortFunction()
    {
        if (DAG == false)
        {
            std::cout << "This graph is not a DAG.\n";
            return;
        }
        else
        {
            topDFS();
        }
    }
    //Function to call for a DFS of a tree
    void topDFS()
    {
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            color[it->first] = WHITE;
            discovery[it->first] = -1;
            finish[it->first] = -1;
            parents[it->first] = 0;
        }
        timing = 0;

        for (auto it2 = vertices.cbegin(); it2 != vertices.cend(); ++it2)
        {
            if (color[it2->first] == WHITE)
                topDFS_Visit(it2->first);
        }
    }
    //function called to actually preform the DFS operands
    void topDFS_Visit(int node)
    {
        timing++;
        discovery[node] = timing;
        color[node] = GREY;
        std::vector<int> neighbors = vertices[node];
        for (auto it = neighbors.cbegin(); it != neighbors.cend(); ++it)
        {
            if (color[*it] == WHITE)
            {
                parents[*it] = node;
                topDFS_Visit(*it);
            }
        }
        timing++;
        color[node] = BLACK;
        finish[node] = timing;
        topSort.push_back(node);
    }
    void printTopSort()
    {
        std::cout << "Printing top sort: ";
        int size = topSort.size();
        for (int i = 1; i < size; i++)
        {
            std::cout << topSort[i] << " ";
        }
        std::cout << "\n";
    }
    //BFS used for timing tests (no prints)
    void timingBFS(int start)
    {
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            color.insert(std::pair<int, color_t>(it->first, WHITE));
            distance.insert(std::pair<int, int>(it->first, -1));
            parents.insert(std::pair<int, int>(it->first, NULL));
        }
        auto search = color.find(start);
        if (search == color.end())
            return;
        else
            color[start] = GREY;
        distance[start] = 0;
        std::queue<int> Q;
        Q.push(start);
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            std::vector<int> neighbors = vertices[u];
            for (auto it2 = neighbors.cbegin(); it2 != neighbors.cend(); ++it2)
            {
                if (color[*it2] == WHITE)
                {
                    color[*it2] = GREY;
                    distance[*it2] = distance[u] + 1;
                    parents[*it2] = u;
                    Q.push(*it2);
                }
                color[u] = BLACK;
            }
        }
    }

    
};
#endif
