#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/136797
// dynamic programming + BFS

// BFS 탐색을 하되, 불필요한 케이스를 제외하는 방법을 생각하기!
// i번째 번호를 누를때, 왼손 오른손의 위치는 동일하지만 이전의 경로에 따라 비용이 다른 케이스가 존재함
// 따라서, 비용이 가장 적은 케이스만 큐에 들어가도록 처리를 해주어야 함
// => dp변수로 최솟값을 기억, 최솟값이 입력된 케이스만 큐에 추가

// 주의해야할 예외 케이스) 이동하고자 하는 손의 반대손이 이미 목적지에 있으면 추가할 필요 X

const int INF = 987654321;

struct Status {
    int lh;
    int rh;
    int cost;
};

vector<vector<int>> costs = {
    {1, 7, 6, 7, 5, 4, 5, 3, 2, 3},
    {7, 1, 2, 4, 2, 3, 5, 4, 5, 6},
    {6, 2, 1, 2, 3, 2, 3, 5, 4, 5},
    {7, 4, 2, 1, 5, 3, 2, 6, 5, 4},
    {5, 2, 3, 5, 1, 2, 4, 2, 3, 5},
    {4, 3, 2, 3, 2, 1, 2, 3, 2, 3},
    {5, 5, 3, 2, 4, 2, 1, 5, 3, 2},
    {3, 4, 5, 6, 2, 3, 5, 1, 2, 4},
    {2, 5, 4, 5, 3, 2, 3, 2, 1, 2},
    {3, 6, 5, 4, 5, 3, 2, 4, 2, 1}
};

int solution(string numbers) {
    int answer = INF;
    vector<vector<vector<int>>> dp(numbers.size(), vector<vector<int>>(10, vector<int>(10, INF)));
    queue<Status> q;
    
    q.push({4, 6, 0});
    
    for (int i = 0; i < numbers.size(); i++) {
        int next = numbers[i] - '0';
        
        while (!q.empty()) {
            Status s = q.front();
            q.pop();
            
            int lCost = s.cost + costs[s.lh][next];
            int rCost = s.cost + costs[s.rh][next];
            
            if (dp[i][next][s.rh] > lCost && next != s.rh) {
                dp[i][next][s.rh] = lCost;
            }
            if (dp[i][s.lh][next] > rCost && next != s.lh) {
                dp[i][s.lh][next] = rCost;
            }
        }
        
        for (int l = 0; l < 10; l++) {
            for (int r = 0; r < 10; r++) {
                if (dp[i][l][r] != INF) {
                    q.push({l, r, dp[i][l][r]});
                }
            }
        }
    }
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            answer = min(answer, dp[numbers.size() - 1][i][j]);
        }
    }
    
    return answer;
}
