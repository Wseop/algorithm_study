#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15008/lessons/121686
// 우선순위 큐

// 현재 시간을 기준으로 실행가능한 프로그램을 "모두" 대기 큐(waitq)로 이동
// 대기 큐에 아무것도 없으면 당장 다음으로 실행가능한 프로그램 1개를 대기 큐로 이동, 이 프로그램은 시작시간이 가장 빠르고 우선순위가 가장 높은 프로그램
// 대기 큐에 있는 프로그램 중 우선순위가 가장 높은 프로그램을 하나씩 실행, 이 때 대기 큐에 있는 모든 프로그램은 당장 실행이 가능한 프로그램들임

// 위 작업을 실행하기 위해서 우선순위 큐 2개를 준비
// 1. 시작시간 -> 우선순위 순으로 정렬 : pq
// 2. 우선순위 -> 시작시간 순으로 정렬 : waitq

// 실행가능 여부는 시작시간을 우선으로 정렬한 pq에서,
// 다음으로 실행시킬 프로그램은 우선순위를 우선으로 정렬한 waitq에서 pop하여 계산

// 결과 업데이트
// 1. 현재시간 <= 프로그램 시작시간 -> 현재시간 = 시작시간 + 실행시간
// 2. 현재시간 >  프로그램 시작시간 -> 대기시간 += 현재시간 - 시작시간
                                  -> 현재시간 += 실행시간

struct Program {
    int priority;
    int startTime;
    int runTime;
};

struct timeFirst {
    bool operator()(const Program& a, const Program& b){
        if (a.startTime > b.startTime) return true;
        else if (a.startTime == b.startTime && a.priority > b.priority) return true;
        else return false;
    }
};

struct priorityFirst {
    bool operator()(const Program& a, const Program& b){
        if (a.priority > b.priority) return true;
        else if (a.priority == b.priority && a.startTime > b.startTime) return true;
        else return false;
    }
};

vector<long long> solution(vector<vector<int>> program) {
    vector<long long> answer(11, 0);
    priority_queue<Program, vector<Program>, timeFirst> pq;
    priority_queue<Program, vector<Program>, priorityFirst> waitq;
    
    for (const vector<int>& p : program) {
        pq.push({p[0], p[1], p[2]});
    }
    
    while (!pq.empty()) {
        Program p;

        while (!pq.empty()) {
            p = pq.top();
            
            if (p.startTime <= answer[0]) {
                waitq.push(p);
                pq.pop();
            } else break;
        }

        if (waitq.empty()) {
            waitq.push(pq.top());
            pq.pop();
        }
        
        p = waitq.top();
        waitq.pop();
        
        if (answer[0] <= p.startTime) {
            answer[0] = p.startTime + p.runTime;
        } else {
            answer[p.priority] += answer[0] - p.startTime;
            answer[0] += p.runTime;
        }
    }
    while (!waitq.empty()) {
        Program p = waitq.top();
        waitq.pop();
        
        if (answer[0] <= p.startTime) {
            answer[0] = p.startTime + p.runTime;
        } else {
            answer[p.priority] += answer[0] - p.startTime;
            answer[0] += p.runTime;
        }
    }
    
    return answer;
}
