#include <string>
#include <vector>
#include <queue>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15009/lessons/121690
// dynamic programming, BFS

// 상하좌우 + 2칸씩 이동하는 경우까지 포함하여 총 8가지 이동경로 존재
// 신발상태까지 포함하여 dp[n][m][2]변수에 최단거리를 저장해가면서 BFS 탐색

struct Pos {
    int x;
    int y;
    int m;
    int s;
};

const int INF = 987654321;

int solution(int n, int m, vector<vector<int>> hole) {
    int answer = INF;
    int dx[8] = {0, 0, -1, 1, 0, 0, -2, 2};
    int dy[8] = {-1, 1, 0, 0, -2, 2, 0, 0};
    vector<vector<vector<int>>> dp(1001, vector<vector<int>>(1001, vector<int>(2, INF)));
    vector<vector<bool>> holes(n + 1, vector<bool>(m + 1, false));
    queue<Pos> q;
    
    for (const vector<int>& h : hole) {
        holes[h[0]][h[1]] = true;
    }
    
    q.push({1, 1, 0, 1});
    dp[1][1][1] = 0;
    while (!q.empty()) {
        Pos pos = q.front();
        q.pop();
        
        for (int i = 0; i < 8; i++) {
            Pos npos = pos;
            npos.x += dx[i];
            npos.y += dy[i];
            npos.m += 1;
            if (i >= 4) {
                npos.s--;
            }
            
            if (npos.s < 0) break;
            if (npos.x < 1 || npos.y < 1 || npos.x > n || npos.y > m || holes[npos.x][npos.y]) continue;
            if (dp[npos.x][npos.y][npos.s] <= npos.m) continue;
            
            dp[npos.x][npos.y][npos.s] = npos.m;
            q.push(npos);
        }
    }
    
    for (int i = 0; i < 2; i++) {
        answer = answer < dp[n][m][i] ? answer : dp[n][m][i];
    }
    if (answer == INF) {
        answer = -1;
    }
    
    return answer;
}
