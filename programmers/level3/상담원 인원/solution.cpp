#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/214288
// 완전 탐색 + 우선순위 큐

// 1. 완전 탐색으로 카테고리별 멘토수 지정
// 2. 카테고리 수 만큼 우선순위 큐(오름차순) 할당, 값은 상담자의 종료시간
// 3. 상담자의 카테고리에 해당하는 큐에 대하여...
// 3-1. 큐가 비어있으면 상담자가 없는 것 -> 시작시간 + 상담시간 push
// 3-2. top의 종료 시간이 상담자의 시작 시간보다 크면 대기 -> 대기 시간 추가, top + 상담시간 push
// 3-3. top의 종료 시간이 상담자의 시작 시간보다 작으면 바로 시작 가능 -> 시작시간 + 상담시간 push

// 1.
void search(vector<int> mentors, int n, int& answer, const int k, const vector<vector<int>>& reqs) {
    if (mentors.size() == k && n == 0) {
        // 2.
        priority_queue<int, vector<int>, greater<int>> pq[k];
        int waitTime = 0;

        for (const vector<int>& req : reqs) {
            int start = req[0];
            int duration = req[1];
            int type = req[2] - 1;
            // 3.
            auto& q = pq[type];

            if (q.size() < mentors[type]) {
                // 3-1.
                q.push(start + duration);
            } else {
                int top = q.top();
                q.pop();
                if (top > start) {
                    // 3-2.
                    waitTime += top - start;
                    q.push(top + duration);
                } else {
                    // 3-3.
                    q.push(start + duration);
                }
            }
        }
        
        answer = answer < waitTime ? answer : waitTime;
        return;
    }
    
    for (int i = n; i >= 1; i--) {
        mentors.push_back(i);
        search(mentors, n - i, answer, k, reqs);
        mentors.pop_back();
    }
}

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 987654321;
    vector<int> mentors;
    
    search(mentors, n, answer, k, reqs);
    
    return answer;
}
