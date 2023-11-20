#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/81303
// 연결리스트, 구현?

// 실제 삽입, 삭제를 진행하지 않고 가리키는 index만 변경해주도록 구현
// 삽입, 삭제 진행시 answer 바로 업데이트하여 추가 탐색 없도록 함

// 처음에 stringstream을 써서 입력값 parsing했더니 testcase 7 ~ 10에서 시간초과 발생해서 애먹음

struct Node {
    int left;
    int right;
};

string solution(int n, int k, vector<string> cmd) {
    string answer(n, 'O');
    stack<int> erased;
    vector<Node> table;
    int cursor = k;
    
    for (int i = 0; i < n; i++) {
        table.push_back({i - 1, i + 1});
    }
    table[n - 1].right = -1;
    
    for (const string& c : cmd) {
        if (c[0] == 'U') {
            int x = stoi(c.substr(2));
            for (int i = 0; i < x; i++) {
                cursor = table[cursor].left;
            }
        } else if (c[0] == 'D') {
            int x = stoi(c.substr(2));
            for (int i = 0; i < x; i++) {
                cursor = table[cursor].right;
            }
        } else if (c[0] == 'C') {
            erased.push(cursor);
            answer[cursor] = 'X';
            
            if (table[cursor].right == -1) {
                table[table[cursor].left].right = -1;
                cursor = table[cursor].left;
            } else if (table[cursor].left == -1) {
                table[table[cursor].right].left = -1;
                cursor = table[cursor].right;
            } else {
                table[table[cursor].left].right = table[cursor].right;
                table[table[cursor].right].left = table[cursor].left;
                cursor = table[cursor].right;
            }
        } else if (c[0] == 'Z') {
            int restore = erased.top();
            erased.pop();
            answer[restore] = 'O';
            
            if (table[restore].right == -1) {
                table[table[restore].left].right = restore;
            } else if (table[restore].left == -1) {
                table[table[restore].right].left = restore;
            } else {
                table[table[restore].left].right = restore;
                table[table[restore].right].left = restore;
            }
        }
    }
    
    return answer;
}
