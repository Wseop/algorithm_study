#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/133500
// DFS

// 리프노드를 찾을 때 까지 재귀호출로 들어가다가 리프노드에 도달하면 부모로 돌아와서 불을 켤지 말지 결정함

vector<vector<int>> adjacent;
vector<bool> lights;

void dfs(int& answer, int node, int parent) {
    for (int child : adjacent[node]) {
        if (child == parent) continue;
        
        dfs(answer, child, node);
        
        if (!lights[child] && !lights[node]) {
            lights[node] = true;
            answer++;
        }
    }
}

int solution(int n, vector<vector<int>> lighthouse) {
    int answer = 0;
    
    adjacent = vector<vector<int>>(n + 1);
    lights = vector<bool>(n + 1, false);
    
    for (const vector<int>& l : lighthouse) {
        adjacent[l[0]].push_back(l[1]);
        adjacent[l[1]].push_back(l[0]);
    }
    
    dfs(answer, 1, 0);
    
    return answer;
}
