/* Kevin Koch COSC 320 Final Project
 * Topic: Graph Isomorphism
 * Goals: To demonstrate some brute-force Graph Isomorphism testing on different algorithms and explore the complexities of a NP-HARD problem */
#include <iostream>
#include <chrono>
#include "graph.h"

int main()
{
    //Test 1
    Graph test(false);
    for (int i = 0; i < 6; i++)
        test.addVertex(i);
    for (int i = 0; i < 3; i++)
        test.addEdge(i, i + 1);
    Graph test2(false);
    for (int i = 0; i < 6; i++)
        test2.addVertex(i);
    for (int i = 2; i < 5; i++)
        test2.addEdge(i, i + 1);

    auto start = std::chrono::system_clock::now();
    std::cout << "Testing isomorphism on a graph with 6 nodes, 3 edges" << std::endl;

    test.A1NP(test2);

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";

    //Test 2
    Graph test3(false);
    for (int i = 0; i < 7; i++)
        test3.addVertex(i);
    for (int i = 0; i < 5; i++)
        test3.addEdge(i, i + 1);
    Graph test4(false);
    for (int i = 0; i < 7; i++)
        test4.addVertex(i);
    for (int i = 1; i < 6; i++)
        test4.addEdge(i, i + 1);

    std::cout << "Testing isomorphism on a graph with 7 nodes, 6 edges" << std::endl;

    start = std::chrono::system_clock::now();
    test3.A1NP(test4);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";

    //Test 3
    Graph test6(false);
    for (int i = 0; i < 5; i++)
        test6.addVertex(i);
    for (int i = 3; i < 4; i++)
        test6.addEdge(i, i + 1);
    Graph test7(false);
    for (int i = 0; i < 6; i++)
        test7.addVertex(i);
    for (int i = 5; i < 6; i++)
        test7.addEdge(i - 1, i);

    start = std::chrono::system_clock::now();
    std::cout << "Testing isomorphism on a graph with 6 nodes, 1 edges" << std::endl;
    test6.A1NP(test7);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";

    //Test 3
    Graph testa(false);
    for (int i = 0; i < 8; i++)
        testa.addVertex(i);
    for (int i = 0; i < 4; i++)
        testa.addEdge(i, i + 1);
    Graph testb(false);
    for (int i = 0; i < 8; i++)
        testb.addVertex(i);
    for (int i = 5; i < 8; i++)
        testb.addEdge(i - 1, i);

    start = std::chrono::system_clock::now();
    std::cout << "Testing isomorphism on a graph with 8 nodes, 4 edges" << std::endl;
    testa.A1NP(testb);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";

    //Test 4
    Graph test8(false);
    for (int i = 0; i < 7; i++)
        test8.addVertex(i);
    for (int i = 0; i < 4; i++)
        test8.addEdge(i, i + 1);
    Graph test9(false);
    for (int i = 0; i < 7; i++)
        test9.addVertex(i);
    for (int i = 4; i < 7; i++)
        test9.addEdge(i - 1, i);

    start = std::chrono::system_clock::now();
    std::cout << "Testing isomorphism on a graph with 7 nodes, 4 edges" << std::endl;
    test8.A1NP(test9);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";

    //Test 5
    Graph test10(false);
    for (int i = 0; i < 6; i++)
        test10.addVertex(i);
    for (int i = 0; i < 5; i++)
        test10.addEdge(i, i + 1);
    Graph test11(false);
    for (int i = 0; i < 6; i++)
        test11.addVertex(i);
    for (int i = 2; i < 6; i++)
        test11.addEdge(i - 1, i);

    start = std::chrono::system_clock::now();
    std::cout << "Testing isomorphism on a graph with 6 nodes, 5 edges" << std::endl;
    test10.A1NP(test11);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n\n";
    return 0;
}