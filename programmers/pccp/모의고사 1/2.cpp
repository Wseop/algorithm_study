#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15008/lessons/121684
// 브루트포스

// 재귀호출로 가능한 모든 경우를 탐색
// selects배열로 선택된 학생의 index를 기억, 이미 선택된 경우는 continue
// 최대 score를 반환

int search(int depth, vector<bool> selects, int score, const vector<vector<int>>& ability) {
    if (depth == ability[0].size()) {
        return score;
    }
    
    int ret = 0;
    
    for (int i = 0; i < ability.size(); i++) {
        if (selects[i]) continue;
        
        selects[i] = true;
        int result = search(depth + 1, selects, score + ability[i][depth], ability);
        ret = ret < result ? result : ret;
        selects[i] = false;
    }
    
    return ret;
}

int solution(vector<vector<int>> ability) {
    int answer = 0;
    vector<bool> selects(ability.size(), false);
    
    answer = search(0, selects, 0, ability);
    
    return answer;
}
