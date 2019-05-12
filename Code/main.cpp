/* Kevin Koch COSC 320 Final Project
 * Topic: Graph Isomorphism
 * Goals: To demonstrate some brute-force Graph Isomorphism testing on different algorithms and explore the complexities of a NP-HARD problem */
#include <iostream>

#include "graph.h"

int main()
{
    Graph test(false);
    for (int i = 0; i < 2; i++)
        test.addVertex(i);
    test.addEdge(0, 1);
    //test.addEdge(0, 3);
    //test.addEdge(2, 1);
    Graph test2(false);
    for (int i = 0; i < 2; i++)
        test2.addVertex(i);
    //test2.addEdge(0, 3);
    //test2.addEdge(2, 1);
    test2.addEdge(0, 1);
    test.A1(test2);
    return 0;
}