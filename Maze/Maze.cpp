#include <stdio.h>
#include <stack>
#include <deque>
#include "Location2D.h"
#include <string>

using namespace std;
const int MAZE_SIZE = 6;

string dfs_result = "";
string bfs_result = "";

char map[MAZE_SIZE][MAZE_SIZE] = {
   {'1', '1', '1', '1', '1', '1'},
   {'e', '0', '1', '0', '0', '1'},
   {'1', '0', '0', '0', '1', '1'},
   {'1', '0', '1', '0', '1', '1'},
   {'1', '0', '1', '0', '0', 'x'},
   {'1', '1', '1', '1', '1', '1'},
};


bool isValidLoc(int r, int c)
{
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE)
        return false;
    else
        return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
    int ds_num;
    printf("데이터 구조 라이브러리 선택 : 1)stack  2)deque \n");
    scanf_s("%d", &ds_num);
    switch (ds_num) {

        // stack DFS
    case 1:
    {
        stack<Location2D> locStack;
        Location2D entry(1, 0);
        locStack.push(entry);

        while (locStack.empty() == false) {
            Location2D here = locStack.top();
            locStack.pop();

            int r = here.row, c = here.col;
            //printf("(%d,%d) ", r, c);
            //dfs_result += "(" + to_string(r) + "," + to_string(c) + ") ";

            if (map[r][c] == 'x') {
                printf("미로 탐색 성공\n");
                goto RESULT;
            }
            else {
                map[r][c] = '.';
                if (isValidLoc(r - 1, c))locStack.push(Location2D(r - 1, c));
                if (isValidLoc(r + 1, c))locStack.push(Location2D(r + 1, c));
                if (isValidLoc(r, c - 1))locStack.push(Location2D(r, c - 1));
                if (isValidLoc(r, c + 1))locStack.push(Location2D(r, c + 1));
            }
        }
        printf("미로 탐색 실패\n");

        break;
    }
    //deque BFS
    case 2:
    {
        deque<Location2D> locDeque;
        Location2D entry(1, 0);
        locDeque.push_back(entry);

        while (locDeque.empty() == false) {
            Location2D here = locDeque.front();
            locDeque.pop_front();

            int r = here.row, c = here.col;
            printf("(%d,%d) ", r, c);
            bfs_result += "(" + to_string(r) + "," + to_string(c) + ") ";

            if (map[r][c] == 'x') {
                printf("미로 탐색 성공\n");
                goto RESULT;
            }
            else {
                map[r][c] = '.';
                if (isValidLoc(r - 1, c))locDeque.push_back(Location2D(r - 1, c));
                if (isValidLoc(r + 1, c))locDeque.push_back(Location2D(r + 1, c));
                if (isValidLoc(r, c - 1))locDeque.push_back(Location2D(r, c - 1));
                if (isValidLoc(r, c + 1))locDeque.push_back(Location2D(r, c + 1));
            }
        }
        printf("미로 탐색 실패\n");
        break;
    }

    // BFS구현
RESULT:
    printf("\n\n======= 최종 비교 =======\n");


    printf("%s\n", dfs_result.c_str());


    printf("%s\n", bfs_result.c_str());

    default:
        printf("잘못된 입력입니다.\n");
    }
    return 0;
}