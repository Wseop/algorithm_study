#include <string>
#include <vector>
#include <cmath>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15008/lessons/121685

// 1세대는 항상 Rr이므로 예외로 처리, 2세대부터 탐색

// (p / 4) == 0 이 될때까지 (n - 2회) 4로 계속 나누면서 나머지(p % 4)는 배열에 저장
// 최종 p의 값을 통해 parents에서 2세대 부모 정보를 가져옴
// 저장해뒀던 나머지 정보(저장한 역순으로)와 현재 parent 정보를 통해 다음 세대의 유전자 정보를 구함

// 부모가 RR, rr이면 결과는 항상 RR, rr
// 부모가 Rr이면 나머지 값에 따라 RR, Rr, Rr, rr (0, 1, 2, 3)

vector<string> solution(vector<vector<int>> queries) {
    vector<string> answer;
    vector<vector<string>> parents = {
        {"RR", "RR", "RR", "RR"}, {"RR", "Rr", "Rr", "rr"}, {"RR", "Rr", "Rr", "rr"}, {"rr", "rr", "rr", "rr"}
    };
    
    for (const vector<int>& query : queries) {
        int n = query[0];
        int p = query[1] - 1;
        
        if (n == 1) answer.push_back("Rr");
        else {
            vector<int> remains;
            string parent;
            
            for (int i = 0; i < n - 2; i++) {
                remains.push_back(p % 4);
                p /= 4;
            }
            
            parent = parents[p][p % 4];
            
            for (int i = remains.size() - 1; i >= 0; i--) {
                int remain = remains[i];
                
                if (parent == "Rr") {
                    if (remain == 0) parent = "RR";
                    else if (remain == 3) parent = "rr";
                    else parent = "Rr";
                } else break;
            }
            
            answer.push_back(parent);
        }
    }
    
    return answer;
}
