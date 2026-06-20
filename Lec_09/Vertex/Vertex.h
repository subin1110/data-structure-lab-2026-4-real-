#pragma once
#ifndef VERTEX_SETS_H
#define VERTEX_SETS_H
#define MAX_VTXS 256
// VertexSets.h : 정점 집합 클래스
class VertexSets {
    int     parent[MAX_VTXS]; // 부모 정점의 id
    int     nSets;            // 집합의 개수
public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;    // 모든 정점이 고유의 집합에 속함
    }
    bool isRoot(int i) { return parent[i] < 0; }

    int findSet(int v) {     // v가 속한 집합을 찾아 반환
        while (!isRoot(v)) v = parent[v];
        return v;
    }
    void unionSets(int s1, int s2) {    // 집합 s1을 집합 s2에 합침
        parent[s1] = s2;
        nSets--;
    }
};


// HeapNode.h: 힙에 저장할 노드 클래스

class HeapNode {
    int key;    // Key 값: 간선의 가중치
    int v1;     // 정점 1
    int v2;     // 정점 2
public:
    HeapNode(int k, int u, int v) : key(k), v1(u), v2(v) {}
    void setKey(int k) { key = k; }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
};


// MinHeap.h: 최소 힙 클래스 (프로그램 10.7)
... // 코드 동일

    // 삽입 함수
    void insert(int key, int u, int v) {
    if (isFull()) return;
    int i = ++size;
    while (i != 1 && key < getParent(i).getKey()) {
        node[i] = getParent(i);
        i /= 2;
    }
    node[i].setKey(key, u, v);
}

... // 코드 동일
};


class WGraphMST : public WGraph {
public:
    void Kruskal() {     // kruskal의 최소 비용 신장 트리 프로그램
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
        VertexSets set(size);    // size개의 집합을 만듦
        int edgeAccepted = 0;       // 선택된 간선의 수
        while (edgeAccepted < size - 1) { // 간선의 수 < (size-1)
            HeapNode& e = heap.remove();
            int uset = set.findSet(e.getV1());
            int vset = set.findSet(e.getV2());
            if (uset != vset) {
                printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());
                set.unionSets(uset, vset);        // 두개의 집합을 합함.
                edgeAccepted++;
            }
        }
    }
};

// 12장-WGraphMST.cpp
#include "WGraphMST.h"
void main()
{
    WGraphMST g;
    g.load("graph.txt");
    // printf("입력 그래프: graph.txt\n");
    // g.display("graph.txt");
    printf("MST By Kruskal's Algorithm\n");
    g.Kruskal();
}