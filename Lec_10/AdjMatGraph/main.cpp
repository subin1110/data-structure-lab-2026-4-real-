#include "AdjMatGraph.h"   // 그래프 클래스 포함
#include <stdio.h>

void main()
{
    //AdjMatGraph g;        // 새로운 그래프 객체 생성
    WGraph g;

    for (int i = 0; i < 7; i++)
        g.insertVertex('A' + i);   // 정점 삽입: 'A' 'B' ...

    g.insertEdge(0, 1);   // 간선 삽입
    g.insertEdge(1, 2);
    g.insertEdge(2, 3);
    g.insertEdge(3, 6);
    g.insertEdge(6, 4);
    g.insertEdge(4, 5);

    printf("인접 행렬로 표현한 그래프\n");
    g.display();

    WGraph wg;
    wg.load("../graph.txt");
    wg.display();

    printf("DFS ==> ");
    g.resetVisited();
    g.DFS(0);
    printf("\n");
}

//return 0;

/*
FILE* fp;
fopen_s(&fp, "../text_out.txt", "w");
g.display(fp);
fclose(fp);
*/
}