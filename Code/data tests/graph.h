#ifndef GRAPH_H //Header protection
#define GRAPH_H
#include <vector>
#include <queue>
#include <map>
#include <iostream>
#include <stdio.h>
//#include "matrix.h"

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
    std::vector<int> perm;
    std::vector<bool> used;
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
    //Returns edge count
    int getEdgeCount()
    {
        return numEdges;
    }
    //Returns vertex count
    int getVertCount()
    {
        return numVert;
    }
    //returns indegree
    auto getInDegree()
    {
        return inDegree;
    }
    //returns outdegree
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
            numVert++;
        }
    }
    // add a directed or undirected edge to the graphprint();
    void addEdge(int v1, int v2)
    {
        auto search = vertices.find(v1);
        auto search2 = vertices.find(v2);

        if (search == vertices.end())
        {
            std::cout << "Vertex" << v1 << " DNE \n";
            return;
        }
        else if (search2 == vertices.end())
        {
            std::cout << "Vertex" << v2 << " DNE \n";
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
                numEdges++;
            }
            else if (directed == true)
            {
                vertices[v1].push_back(v2);
                numEdges++;
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
    //Impementation of brute force algorithm
    void A1(Graph G)
    {
        used = std::vector<bool>(numVert);
        perm = std::vector<int>(numVert);
        //Sanity checks isomorphism properties
        bool sanity = sanCheck(G);
        if (!sanity)
        {
            return;
        }
        //Checks base case where the two graphs are identicle
        bool isomorphic = edgeEdgeCheck(G);
        if (isomorphic)
        {
            std::cout << "The graphs are isomorphic, because they're the same graph.\n";
            return;
        }
        isomorphic = bruteForce(numVert - 1, G);
        if (isomorphic)
            std::cout << "The graphs are isomorphic.\n";
        else
        {
            std::cout << "The graphs are not isomorphic.\n";
        }
    }

    bool bruteForce(int level, Graph G)
    {
        bool result = false;
        if (level == -1)
        {
            result = edgeCheck(G);
            if (!result)
                return result;
            std::cout << "result for level" << level << " ";
            printf("%s\n", result ? "true" : "false");
        }
        else
        {
            for (int k = 0; k < this->numVert; k++)
                this->used[k] = false;
            int i = 0;
            while ((i < numVert) && !result)
            {
                if (!used[i])
                {
                    this->used[i] = true;
                    this->perm[level] = i;
                    result = bruteForce(level - 1, G);
                    std::cout << "result for inside loop" << level << " ";
                    printf("%s\n", result ? "true" : "false");
                    this->used[i] = false;
                }
                i++;
            }
        }
        return result;
    }

    bool edgeCheck(Graph G)
    {
        int adj_matrix1[this->numVert][this->numVert];
        int adj_matrix2[this->numVert][this->numVert];
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                adj_matrix1[i][j] = 0;
                adj_matrix2[i][j] = 0;
            }
        }
        for (auto it = G.vertices.cbegin(); it != G.vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix1[it->first][*it2] = 1;
        }
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix2[it->first][*it2] = 1;
        }
        std::cout << "Printing adj matrix 1 \n";
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                std::cout << adj_matrix1[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "\nPrinting adj matrix 2: \n";
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                std::cout << adj_matrix2[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "\n printing perm:\n";
        for (int i = 0; i < this->numVert; i++)
        {
            std::cout << this->perm[i];
            std::cout << std::endl;
        }
        std::cout << "\n";
        bool same = true;
        for (int x = 0; x < (this->numVert - 1); x++)
        {
            int y = 0;
            while ((y < numVert) && same)
            {
                printf("Inner loop of edge check, sanity check, x: %d y: %d\n", x, y);
                if (adj_matrix1[x][y] != adj_matrix2[this->perm[x]][this->perm[y]])
                    same = false;
                y++;
            }
        }
        return same;
    }
    //checks to see if graph is identical to itself
    bool edgeEdgeCheck(Graph G)
    {
        int adj_matrix1[this->numVert][this->numVert];
        int adj_matrix2[this->numVert][this->numVert];
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                adj_matrix1[i][j] = 0;
                adj_matrix2[i][j] = 0;
            }
        }
        for (auto it = G.vertices.cbegin(); it != G.vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix1[it->first][*it2] = 1;
        }
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix2[it->first][*it2] = 1;
        }
        std::cout << "Printing adj matrix 1 \n";
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                std::cout << adj_matrix1[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "\nPrinting adj matrix 2: \n";
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                std::cout << adj_matrix2[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "\n";
        bool same = true;
        for (int x = 0; x < (this->numVert - 1); x++)
        {
            int y = 0;
            while ((y < numVert) && same)
            {
                printf("Inner loop of edge check, sanity check, x: %d y: %d\n", x, y);
                if (adj_matrix1[x][y] != adj_matrix2[x][y])
                    same = false;
                y++;
            }
        }
        return same;
    }
    //small sanity check function based on first 2 properties of graph isomorphism
    bool sanCheck(Graph G)
    {
        if (this->numVert != G.getVertCount())
        {
            std::cout << "There is in violation of the vertex propertry of graph isomorphism!\n";
            return false;
        }
        else if (this->numEdges != G.getEdgeCount())
        {
            std::cout << "This is in violation of the edge property of graph isomorphism!\n";
            return false;
        }
        else
            return true;
    }

    //Impementation of brute force algorithm without a print
    void A1NP(Graph G)
    {
        used = std::vector<bool>(numVert);
        perm = std::vector<int>(numVert);
        //Sanity checks isomorphism properties
        bool sanity = sanCheckNP(G);
        if (!sanity)
        {
            return;
        }
        //Checks base case where the two graphs are identicle
        bool isomorphic = edgeEdgeCheckNP(G);
        if (isomorphic)
        {
            return;
        }
        isomorphic = bruteForceNP(numVert - 1, G);
        if (isomorphic)
            std::cout << "The graphs are isomorphic.\n";
        else
        {
            std::cout << "The graphs are not isomorphic.\n";
        }
    }
    //without a print
    bool bruteForceNP(int level, Graph G)
    {
        bool result = false;
        if (level == -1)
        {
            result = edgeCheckNP(G);
            if (!result)
                return result;
        }
        else
        {
            for (int k = 0; k < this->numVert; k++)
                this->used[k] = false;
            int i = 0;
            while ((i < numVert) && !result)
            {
                if (!used[i])
                {
                    this->used[i] = true;
                    this->perm[level] = i;
                    result = bruteForceNP(level - 1, G);
                    this->used[i] = false;
                }
                i++;
            }
        }
        return result;
    }
    //checks to see if our permutation of the graph is an isomorphism
    bool edgeCheckNP(Graph G)
    {
        int adj_matrix1[this->numVert][this->numVert];
        int adj_matrix2[this->numVert][this->numVert];
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                adj_matrix1[i][j] = 0;
                adj_matrix2[i][j] = 0;
            }
        }
        for (auto it = G.vertices.cbegin(); it != G.vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix1[it->first][*it2] = 1;
        }
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix2[it->first][*it2] = 1;
        }
        bool same = true;
        for (int x = 0; x < (this->numVert - 1); x++)
        {
            int y = 0;
            while ((y < numVert) && same)
            {
                if (adj_matrix1[x][y] != adj_matrix2[this->perm[x]][this->perm[y]])
                    same = false;
                y++;
            }
        }
        return same;
    }
    //checks to see if graph is identical to itself
    bool edgeEdgeCheckNP(Graph G)
    {
        int adj_matrix1[this->numVert][this->numVert];
        int adj_matrix2[this->numVert][this->numVert];
        for (int i = 0; i < this->numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                adj_matrix1[i][j] = 0;
                adj_matrix2[i][j] = 0;
            }
        }
        for (auto it = G.vertices.cbegin(); it != G.vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix1[it->first][*it2] = 1;
        }
        for (auto it = vertices.cbegin(); it != vertices.cend(); ++it)
        {
            for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                adj_matrix2[it->first][*it2] = 1;
        }
        bool same = true;
        for (int x = 0; x < (this->numVert - 1); x++)
        {
            int y = 0;
            while ((y < numVert) && same)
            {
                if (adj_matrix1[x][y] != adj_matrix2[x][y])
                    same = false;
                y++;
            }
        }
        return same;
    }
    //small sanity check function based on first 2 properties of graph isomorphism
    bool sanCheckNP(Graph G)
    {
        if (this->numVert != G.getVertCount())
        {
            return false;
        }
        else if (this->numEdges != G.getEdgeCount())
        {
            return false;
        }
        else
            return true;
    }
};
#endif
