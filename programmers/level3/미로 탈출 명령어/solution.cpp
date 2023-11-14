#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/150365
// DFS

// 가능한 결과값 중 사전순으로 가장 빠른 1가지만 출력하면 되므로 상(u), 하(d), 좌(l), 우(r)를 사전순인 d, l, r, u 순으로 DFS 탐색
// 아래 조건을 추가하여 탐색 최소화
// 현재 위치부터 목적지까지 남은 거리(distance)가 이동 가능한 거리(remain)보다 큰 경우 더 이상 탐색할 필요 X
// 목적지까지 남은 거리(distance)가 홀수(혹은 짝수)인데 이동해야하는 횟수(remain)가 짝수(혹은 홀수)이면 도달 불가능하므로 탐색 중지

// 기본적인 BFS, DFS 문제에서 방문 여부를 기록하여 탐색을 최소화하는 방식을 남은 거리를 이용하여 최소화하는 방식으로 변경한 문제

int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};
char dm[4] = {'d', 'l', 'r', 'u'};

void dfs(const int n, const int m, int x, int y, const int r, const int c, const int k, string result, string& answer) {
    if (result.size() == k) {
        if (x == r && y == c) {
            answer = result;
        }
        return;
    }
    
    if (answer.empty()) {
        int distance = abs(r - x) + abs(c - y);
        int remain = k - result.size();
        
        if (distance > remain) return;
        if ((distance & 1) && !(remain & 1)) return;
        if (!(distance & 1) && (remain & 1)) return;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx <= 0 || ny <= 0 || nx > n || ny > m) continue;
            dfs(n, m, nx, ny, r, c, k, result + dm[i], answer);
        }
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = "";
    string result = "";
    
    dfs(n, m, x, y, r, c, k, result, answer);
    
    if (answer.empty())
        answer = "impossible";
    
    return answer;
}
