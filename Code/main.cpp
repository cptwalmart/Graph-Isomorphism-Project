/* Kevin Koch COSC 320 Final Project
 * Topic: Graph Isomorphism
 * Goals: To demonstrate some brute-force Graph Isomorphism testing on different algorithms and explore the complexities of a NP-HARD problem */
#include <iostream>

#include "graph.h"

int main()
{
    Graph test(false);
    for (int i = 0; i < 4; i++)
        test.addVertex(i);
    test.addEdge(0, 1);
    test.addEdge(0, 2);

    Graph test2(false);
    for (int i = 0; i < 4; i++)
        test2.addVertex(i);
    test2.addEdge(0, 3);
    test2.addEdge(2, 1);
    test2.addEdge(0, 1);
    std::cout << std::endl;
    std::cout << "Testing edge violation~ \n\n";
    test2.A1(test);

    Graph test3(false);
    for (int i = 0; i < 3; i++)
        test3.addVertex(i);
    test3.addEdge(0, 1);
    test3.addEdge(0, 2);

    Graph test4(false);
    for (int i = 0; i < 2; i++)
        test4.addVertex(i);
    test4.addEdge(0, 1);
    std::cout << std::endl;
    std::cout << "Testing vertex violation~ \n\n";
    test4.A1(test3);

    Graph test5(false);
    for (int i = 0; i < 2; i++)
        test5.addVertex(i);
    test5.addEdge(0, 1);
    std::cout << std::endl;
    std::cout << "Testing identical graphs~ \n\n";
    test4.A1(test4);

    Graph test6(false);
    for (int i = 0; i < 3; i++)
        test6.addVertex(i);
    for (int i = 1; i < 2; i++)
        test6.addEdge(i, i+1);
    
    Graph test7(false);
    for (int i = 0; i < 3; i++)
        test7.addVertex(i);
    for (int i = 1; i < 2; i++)
        test7.addEdge(i-1, i);

    std::cout << "Testing isomorphism on a very connected graph with 4 nodes."<<std::endl;
    test6.A1(test7);
    
    return 0;
}