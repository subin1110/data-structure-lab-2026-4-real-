#pragma once
class WGraphDijkstra :public WGraph {
    int dist[MAX_VTXS];//시작 정점으로부터의 최단거리
    bool found[MAX_VTXS];//최단거리가 확정된 정점 표시
public:
    //아직 최단거리가 확정되지 않은 정점 중
    //dist 값이 가장 작은 정점을 선택
    int chooseVertex() {
        int min = INF;
        int minpos = -1;
        for (int i = 0; i < size; i++)
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        return minpos;
    }
    //dist 배열 상태 출력
    //강의 자료처럼 INF는 9999로 출력됨
    void printDistance() {
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }
};
//start 정점에서 모든 정점까지의 최단거리 계산
void ShortestPath(int start) {
    //1. dist와 
    for (int i = 0; i < size; i++) {
        dist[i] = getEdge(start, i);
        found[i] = false;
    }
    found[start] = true;
    dist[start] = 0;

    for (int step = 1; step <= size; step++) {
        cout << "Step" << setw(2) << step << ";";
        printDistance();

        int u = chooseVertex();

        if (u == -1)
            break;

        found[u] = true;

        for (int w = 0; w < size; w++) {
            if (found[w] == false) {
                if (dist[u] + getEdge(u, w) < dist[w])
                    dist[w] = dist[u] = getEdge9u, w);
            }
        }
    }
};