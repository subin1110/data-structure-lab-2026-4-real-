import sys

# 입력 받는 코드입니다. 수정할 필요 없습니다.
sys.stdin = open('case.txt')

N, M = list(map(int, input().split()))

print(N, M)

concerts = []

# 콘서트장 정보를 2차원 리스트에 저장
for v in range(N):
    values = list(map(int, input().split()))
    concerts.append(values)

def count_stages(concerts):
    # 무대 공간의 개수를 저장할 변수
    answer = 0

    # 행과 열의 크기 저장
    N = len(concerts)
    M = len(concerts[0])

    # 방문 여부를 저장하는 리스트
    visited = [[False] * M for _ in range(N)]

    # DFS를 이용해 연결된 무대 공간(0)을 탐색
    def dfs(x, y):
        visited[x][y] = True

        # 상, 하, 좌, 우 이동
        dx = [-1, 1, 0, 0]
        dy = [0, 0, -1, 1]

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]

            # 배열 범위를 벗어나지 않는지 확인
            if 0 <= nx < N and 0 <= ny < M:

                # 무대 공간(0)이고 아직 방문하지 않은 경우 탐색
                if concerts[nx][ny] == 0 and not visited[nx][ny]:
                    dfs(nx, ny)

    # 모든 위치를 확인
    for i in range(N):
        for j in range(M):

            # 새로운 무대 공간을 발견한 경우
            if concerts[i][j] == 0 and not visited[i][j]:

                # 연결된 모든 공간을 DFS로 탐색
                dfs(i, j)

                # 하나의 독립된 무대 공간 발견
                answer += 1

    return answer

print(count_stages(concerts))
