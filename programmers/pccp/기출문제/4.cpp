#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/250134
// dynamic programming + DFS

// dp[빨간수레 x][빨간수레 y][파란수레 x][파란수레 y] = 최솟값
// depth마다 빨간수레, 파란수레 각각 먼저 이동하는 경우를 모두 구해주면서 DFS 탐색...

struct Pos {
    int x, y;
    
    bool operator==(const Pos& other) {
        if (x == other.x && y == other.y) return true;
        else return false;
    }
    
    bool operator!=(const Pos& other) {
        if (x != other.x || y != other.y) return true;
        else return false;
    }
};

const int INF = 987654321;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, m;
Pos endR, endB;
vector<vector<vector<vector<int>>>> dp;

bool isValid(const vector<vector<int>>& maze, const vector<vector<bool>>& visited, Pos p1, Pos p2) {
    if (p1.x < 0 || p1.y < 0 || p1.x >= n || p1.y >= m) return false;
    if (maze[p1.x][p1.y] == 5) return false;
    if (visited[p1.x][p1.y]) return false;
    if (p1 == p2) return false;
    return true;
}

void dfs(const vector<vector<int>>& maze, vector<vector<bool>> visitedR, vector<vector<bool>> visitedB, Pos r, Pos b, int depth) {
    if (r == endR && b == endB) return;
    
    for (int i = 0; i < 4; i++) {
        Pos nr = r;
        
        if (nr != endR) {
            nr.x += dx[i];
            nr.y += dy[i];
            if (!isValid(maze, visitedR, nr, b)) continue;
            visitedR[nr.x][nr.y] = true;
        }
        
        for (int j = 0; j < 4; j++) {
            Pos nb = b;
            
            if (nb != endB) {
                nb.x += dx[j];
                nb.y += dy[j];
                if (!isValid(maze, visitedB, nb, nr)) continue;
                visitedB[nb.x][nb.y] = true;
            }
            
            if (dp[nr.x][nr.y][nb.x][nb.y] > depth + 1) {
                dp[nr.x][nr.y][nb.x][nb.y] = depth + 1;
                dfs(maze, visitedR, visitedB, nr, nb, depth + 1);
            }
            
            visitedB[nb.x][nb.y] = false;
        }
        visitedR[nr.x][nr.y] = false;
    }
    for (int i = 0; i < 4; i++) {
        Pos nb = b;
        
        if (nb != endB) {
            nb.x += dx[i];
            nb.y += dy[i];
            if (!isValid(maze, visitedB, nb, r)) continue;
            visitedB[nb.x][nb.y] = true;
        }
        
        for (int j = 0; j < 4; j++) {
            Pos nr = r;
            
            if (nr != endR) {
                nr.x += dx[j];
                nr.y += dy[j];
                if (!isValid(maze, visitedR, nr, nb)) continue;
                visitedR[nr.x][nr.y] = true;
            }
            
            if (dp[nr.x][nr.y][nb.x][nb.y] > depth + 1) {
                dp[nr.x][nr.y][nb.x][nb.y] = depth + 1;
                dfs(maze, visitedR, visitedB, nr, nb, depth + 1);
            }
            
            visitedR[nr.x][nr.y] = false;
        }
        visitedB[nb.x][nb.y] = false;
    }
}

int solution(vector<vector<int>> maze) {
    int answer = 0;
    Pos startR, startB;
    
    n = maze.size();
    m = maze[0].size();
    
    vector<vector<bool>> visitedR(n, vector<bool>(m, false));
    vector<vector<bool>> visitedB(n, vector<bool>(m, false));
    dp = vector<vector<vector<vector<int>>>>(n, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m, INF))));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Pos pos = {i, j};
            if (maze[i][j] == 1) startR = pos;
            else if (maze[i][j] == 2) startB = pos;
            else if (maze[i][j] == 3) endR = pos;
            else if (maze[i][j] == 4) endB = pos;
        }
    }
    
    visitedR[startR.x][startR.y] = true;
    visitedB[startB.x][startB.y] = true;
    dp[startR.x][startR.y][startB.x][startB.y] = 0;
    
    dfs(maze, visitedR, visitedB, startR, startB, 0);
    
    answer = dp[endR.x][endR.y][endB.x][endB.y];
    if (answer == INF) answer = 0;
    
    return answer;
}
