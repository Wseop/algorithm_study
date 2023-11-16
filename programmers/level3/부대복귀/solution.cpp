#include <string>
#include <vector>
#include <queue>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/132266
// BFS

// 방문여부를 체크해서 탐색하는 BFS의 가장 기본적인 문제

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    vector<vector<int>> routes(n + 1);
    
    for (const vector<int>& road : roads) {
        routes[road[0]].push_back(road[1]);
        routes[road[1]].push_back(road[0]);
    }
    
    for (int source : sources) {
        queue<pair<int, int>> q;
        vector<bool> visited(n + 1, false);
        int result = -1;
        
        visited[source] = true;
        q.push({source, 0});
        
        while (!q.empty()) {
            int curr = q.front().first;
            int t = q.front().second;
            q.pop();
            
            if (curr == destination) {
                result = t;
                break;
            }
            
            for (int next : routes[curr]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push({next, t + 1});
                }
            }
        }
        
        answer.push_back(result);
    }
    
    return answer;
}
