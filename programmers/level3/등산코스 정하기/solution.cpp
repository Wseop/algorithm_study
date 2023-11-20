#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/118669
// DFS, dynamic programming

// 출입구부터 정상까지 가는 모든 경로마다 최대 intensity를 구한뒤, 구한 intensity들 중 최솟값을 찾는 문제
// 단순 visited 배열로 했을 경우 시간초과 발생 -> dynamic programming
// dp <- 각 지점에서 가질수 있는 최소 intensity를 기억

const int INF = 987654321;

vector<vector<pair<int, int>>> adjacent(50001);
vector<bool> isGate(50001, false);
vector<bool> isSummit(50001, false);
vector<int> dp(50001, INF);

void dfs(int node, int intensity, vector<int>& result) {
    if (isSummit[node]) {
        if (result[1] > intensity) {
            result = {node, intensity};
        } else if (result[1] == intensity && result[0] > node) {
            result = {node, intensity};
        }
        return;
    }
    
    for (const pair<int, int>& next : adjacent[node]) {
        if (isGate[next.first]) continue;
        
        int maxIntensity = intensity < next.second ? next.second : intensity;
        if (dp[next.first] <= maxIntensity) continue;
        dp[next.first] = maxIntensity;
        dfs(next.first, maxIntensity, result);
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer = {n + 1, INF};
    
    for (const vector<int>& path : paths) {
        adjacent[path[0]].push_back({path[1], path[2]});
        adjacent[path[1]].push_back({path[0], path[2]});
    }
    for (int gate : gates) {
        isGate[gate] = true;
    }
    for (int summit : summits) {
        isSummit[summit] = true;
    }
    
    for (int gate : gates) {
        vector<int> result = {INF, INF};
        
        dfs(gate, 0, result);
        
        if (answer[1] > result[1]) {
            answer = result;
        } else if (answer[1] == result[1] && answer[0] > result[0]) {
            answer = result;
        }
    }
    
    return answer;
}
