#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/15008/lessons/121683

// 각 알파벳이 호출된 횟수 -> counts
// 각 알파벳의 영역의 갯수 -> splits

// splits 업데이트시 알파벳이 붙어있는 경우는 세지 않음
// -> 현재 index와 바로 앞의 알파벳이 다른 경우만 셈
// 0번 index는 미리 초기화

// counts와 splits 모두 2이상인 경우만 결과에 추가

string solution(string input_string) {
    string answer = "";
    vector<int> counts(26, 0);
    vector<int> splits(26, 0);
    
    counts[input_string[0] - 'a']++;
    splits[input_string[0] - 'a']++;
    
    for (int i = 1; i < input_string.size(); i++) {
        char ch = input_string[i];
        counts[ch - 'a']++;
        
        if (ch != input_string[i - 1]) {
            splits[ch - 'a']++;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (counts[i] >= 2 && splits[i] >= 2) {
            answer += i + 'a';
        }
    }
    
    if (answer == "")
        answer = "N";
    
    return answer;
}
