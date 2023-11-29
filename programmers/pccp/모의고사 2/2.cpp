#include <string>
#include <vector>
#include <queue>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15009/lessons/121688
// 그리디, 우선순위 큐

// 능력치가 가장 낮은 두 사원을 선택해서 교육시키는 것이 능력치의 합을 가장 낮게 유지하는 방법
// 매번 정렬하지 않고 우선순위 큐를 사용하여 항상 오름차순으로 유지

struct cmp {
    bool operator()(const int& a, const int& b){
        if (a > b) return true;
        else return false;
    }
};

int solution(vector<int> ability, int number) {
    int answer = 0;
    priority_queue<int, vector<int>, cmp> pq;
    
    for (int a : ability) pq.push(a);
    
    for (int i = 0; i < number; i++) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        
        pq.push(a + b);
        pq.push(a + b);
    }
    
    while (!pq.empty()) {
        answer += pq.top();
        pq.pop();
    }
    
    return answer;
}
