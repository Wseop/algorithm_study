#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/92343
// DFS

// 되돌아올 수 있다는 점에 주의
// 한 번 방문을 했다면 해당 노드의 자식노드들까지 가는 길이 열림
// 배열로 길이 열린 노드들을 기록하여 DFS 탐색을 진행
// 이미 방문한 노드를 또 계산하지 않도록 하기 위해 배열에서 현재 노드는 삭제해주어야 함

vector<vector<int>> tree(17);

void search(int& answer, const vector<int>& info, vector<int> nexts, int sheep, int wolf, int node) {
    if (info[node]) wolf++;
    else sheep++;
    
    answer = answer < sheep ? sheep : answer;
    
    if (sheep <= wolf) return;
    
    for (auto iter = nexts.begin(); iter != nexts.end(); iter++) {
        if (*iter == node) {
            nexts.erase(iter);
            break;
        }
    }
    
    for (int child : tree[node]) {
        nexts.push_back(child);
    }
    
    for (int next : nexts) {
        search(answer, info, nexts, sheep, wolf, next);
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer = 0;
    vector<int> nexts = {0};
    
    for (const vector<int>& edge : edges) {
        tree[edge[0]].push_back(edge[1]);
    }
    
    search(answer, info, nexts, 0, 0, 0);
    
    return answer;
}
