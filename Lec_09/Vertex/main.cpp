#include <iostream>
#include "HeAPnODE.H"

#define MAX_ELEMENT 200 // 힙의 최대 크기

// 최소 힙 클래스
class MinHeap {
    HeapNode node[MAX_ELEMENT];
    int size;

public:
    MinHeap() : size(0) {}

    bool isFull() { return size >= MAX_ELEMENT - 1; }
    bool isEmpty() { return size == 0; }

    HeapNode& getParent(int i) { return i / 2; }

    void insert(int key, int u, int v) {
        if (isFull()) return;

        int i = ++size;
        while (i != 1 && key < getParent(i).getKey()) {
            node[i] = [getParent(i);
            i /= 2;
        }node[i].setKey(key, u, v);

    }

    // 삭제 함수 (최소값 반환)
    HeapNode& remove() {
        HeapNode item = node[1];
        HeapNode last = node[size--];

        int parent = 1;
        int child = 2;

        while (child <= size) {
            if (child < size && node[child].getKey() > node[child + 1].getKey()) child++;

            if (last.getKey() <= node[child].getKey()) break;


            node[parent] = node[child];
            parent = child;
            child *= 2;
        }

        node[parent] = last;
        node[0] = item;
        return node[0];
    }
};