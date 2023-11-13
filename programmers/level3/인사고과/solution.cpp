#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/152995
// 정렬, 완전탐색?

// 정렬 후 2중 for문으로 점수 카운트
// 조건식을 추가하여 탐색 범위를 줄여나가는게 핵심
// 완호의 점수보다 같거나 작은 사원은 체크할 필요 없음 (continue)

// 2중 for문 돌리면 무조건 시간초과 날줄 알았는데 조건문 몇개로 패스가 가능한 경우도 있다는 걸 알게 된 문제

int solution(vector<vector<int>> scores) {
    int answer = 0;
    vector<int> rankCounts(200001, 0);
    int a = scores[0][0];
    int b = scores[0][1];
    
    sort(scores.begin(), scores.end(), [&](const auto& a, const auto& b){
        if (a[0] == b[0])
            return a[1] > b[1];
        else
            return a[0] > b[0];
    });
    
    for (int i = 0; i < scores.size(); i++) {
        bool count = true;
        
        if (a < scores[i][0] && b < scores[i][1]) return -1;
        if (scores[i][0] + scores[i][1] <= a + b) continue;
        
        for (int j = 0; j < scores.size(); j++) {
            if (scores[i][0] < scores[j][0] && scores[i][1] < scores[j][1]) {
                count = false;
                break;
            }
        }
        
        if (count)
            rankCounts[scores[i][0] + scores[i][1]]++;
    }
    
    for (int i = 200000; i > a + b; i--) {
        answer += rankCounts[i];
    }
    answer++;
    
    return answer;
}
