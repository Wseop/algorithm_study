#include <string>
#include <vector>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/77886
// 문자열 다루기???

// 110을 추출하는 부분에서 시간을 줄이는게 관건이었던 문제...
// 반복문은 n번만 돌게 고정해두고 내부에서 조건을 조금씩 변경하면서 찾았다

// 110 붙이는 위치
// 사전순으로 앞쪽에 오게 하려면 0보다는 뒤에, 1보다는 앞에 위치해야 함
// 0이 없어서 110을 붙이지 못한 경우에는, 그냥 맨 앞에 붙여주는 케이스밖에 없음 (빈 문자열인 경우도 포함)

vector<string> solution(vector<string> s) {
    vector<string> answer;
    
    for (const string& str : s) {
        int count = 0;
        string temp;
        
        for (int i = 0; i < str.size(); i++) {
            temp += str[i];
            if (temp.size() < 3) continue;
            if (str[i] == '0' && temp.substr(temp.size() - 3, 3) == "110") {
                temp = temp.substr(0, temp.size() - 3);
                count++;
            }
        }
        
        for (int i = 0; i < count; i++) {
            bool inserted = false;
            
            for (int j = temp.size() - 1; j >= 0; j--) {
                if (temp[j] == '0') {
                    temp.insert(j + 1, "110");
                    inserted = true;
                    break;
                }
            }
            
            if (!inserted) {
                temp = "110" + temp;
            }
        }
        
        answer.push_back(temp);
    }
    
    return answer;
}
