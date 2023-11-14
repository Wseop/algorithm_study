#include <string>
#include <vector>
#include <iostream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/150367
// 분할 정복

// 포화 이진트리를 이진수로 표현했을 때 자릿수는 아래와 같이 고정된 갯수
// 1, 3, 7, 15, 31, 63, ...
// 입력의 최댓값인 10^15를 이진수로 변환하면 52자리이므로, 최대로 가능한 자릿수는 63
// 따라서, 입력으로 들어오는 십진수를 이진수로 변환후 자릿수를 큰 쪽으로 맞춰주면 됨 (앞부터 0으로 채움)

// 루트노드가 0인 경우 좌우 자식 노드에는 무조건 0밖에 올 수 없음(비워둔 자리이므로 자식을 가질 수 없음) -> 000
// 루트노드가 1인 경우 좌우 자식 노드는 0 또는 1 모두 가능 -> 010, 011, 110, 111
// 이를 이용하여 분할 정복을 시도

// 길이가 3이 될때까지 가운데를 기준으로 분할 (가운데 포함 X)
// 000 이면 빈 트리를 뜻하는 0을 반환
// 그 외에 가능한 구조인 경우는 1을 반환
// 불가능한 구조이면 -1을 반환

int check(string number) {
    if (number == "1")
        return 1;
    
    if (number.size() == 3) {
        if (number == "000") return 0;
        else if (number == "010" || number == "011" || number == "110" || number == "111") return 1;
        else return -1;
    }
    
    int len = number.size();
    int l = check(number.substr(0, len / 2));
    int r = check(number.substr(len / 2 + 1, len / 2));
    if (l == -1 || r == -1) return -1;
    
    string result(3, '0');
    result[0] = l + '0';
    result[1] = number[len / 2];
    result[2] = r + '0';
    if (result == "000") return 0;
    else if (result == "010" || result == "011" || result == "110" || result == "111") return 1;
    else return -1;
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    vector<int> digits = {1, 3, 7, 15, 31, 63};
    
    for (long long number : numbers) {
        string binary;
        string binaryNumber;
        
        while (number != 0) {
            binary += number % 2 + '0';
            number /= 2;
        }
        
        for (const int& digit : digits) {
            if (digit >= binary.size()) {
                // 자릿수 부족한 만큼 앞에 0 채우기
                for (int i = 0; i < digit - binary.size(); i++) {
                    binaryNumber += "0";
                }
                break;
            }
        }
        
        // 이진수 완성
        for (int i = binary.size() - 1; i >= 0; i--) {
            binaryNumber += binary[i];
        }
        
        int result = check(binaryNumber);
        if (result == -1)
            answer.push_back(0);
        else
            answer.push_back(1);
    }
    
    return answer;
}
