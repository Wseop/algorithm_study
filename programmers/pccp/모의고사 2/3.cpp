#include <string>
#include <vector>
#include <queue>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15009/lessons/121689
// 큐

// 모든 손님이 다 들어오면 그 이후는 나가는 손님만 존재하므로 order크기 만큼만 반복
// 큐의 크기는 새로운 손님이 들어올 때만 증가
// 따라서, 현재시간을 k씩 증가시키면서 나가는 손님 처리 -> 들어오는 손님 추가 -> answer를 갱신하는 순서로 구현

// 들어오는 손님은 k시간마다 항상 존재하므로, 나가는 손님만 처리해주면 됨
// 1. 제작이 완료되었을 경우(현재시간 >= 제작중인 음료의 완료시간) 나가는 손님이 존재
// 2. 손님 나감 (pop)
// 3-1. 더 이상 대기중인 손님이 없다면(empty) 새로운 손님 기준으로 완료시간 갱신
// 3-2. 큐에 대기중인 음료의 제작시간을 기준으로 완료시간 갱신 -> 1.로 이동, 반복

int solution(vector<int> menu, vector<int> order, int k) {
    int answer = 0;
    int current = 0;
    int complete = 0;
    queue<int> q;
    
    current = -k;
    q.push(menu[order[0]]);
    
    for (int i = 0; i < order.size(); i++) {
        current += k;

        while (current >= complete) {
            q.pop();
            if (q.empty()) {
                complete = current + menu[order[i]];
                break;
            } else {
                complete += q.front();
            }
        }
        
        q.push(menu[order[i]]);
        answer = answer < q.size() ? q.size() : answer;
    }
    
    return answer;
}
