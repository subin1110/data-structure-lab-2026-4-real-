A = {
    0: [1, 2, 3],
    1: [4, 5, 2, 0],
    2: [6, 1, 0],
    3: [0],
    4: [1],
    5: [1],
    6: [2]
}

# BFS (너비 우선 탐색)
def bfs(A):
    answer = []                 # 방문 순서 저장
    visited = [False] * len(A)  # 방문 여부 체크
    queue = [0]                 # 시작 노드 0
    visited[0] = True           # 시작 노드 방문 처리

    while queue:
        node = queue.pop(0)     # 큐에서 하나 꺼냄
        answer.append(node)     # 방문 기록

        # 연결된 노드들 순서대로 확인
        for u in A[node]:
            if not visited[u]:  # 아직 방문 안 했으면
                visited[u] = True
                queue.append(u) # 큐에 추가

    return answer


# DFS (깊이 우선 탐색 - 재귀 방식)
def dfs(A):
    answer = []                 # 방문 순서 저장
    visited = [False] * len(A)  # 방문 여부 체크

    def go(v):
        visited[v] = True       # 현재 노드 방문 처리
        answer.append(v)        # 방문 기록

        # 연결된 노드들 순서대로 깊이 탐색
        for u in A[v]:
            if not visited[u]:
                go(u)

    go(0)   # 시작 노드
    return answer


# 결과 실행
bfs_result = bfs(A)
dfs_result = dfs(A)

# 정답 체크
assert bfs_result == [0,1,2,3,4,5,6]
assert dfs_result == [0,1,4,5,2,6,3]

print("PASSED!")
