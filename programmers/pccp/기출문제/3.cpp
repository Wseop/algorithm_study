#include <string>
#include <vector>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/250135

// 1초마다 초침은 6도, 분침은 1/10도, 시침은 1/120도를 움직임
// 연속된 구간을 검사해야하므로 i초일때 i+1초까지 각 침이 움직일 수 있는 범위를 비교
// i초는 포함하지 않고 i+1초는 포함하여 비교 -> 시작구간을 검사할 수 없으므로 예외처리해줌
// 위 조건에 따라 for문은 [start, end) 구간을 돌려야함

int solution(int h1, int m1, int s1, int h2, int m2, int s2) {
    int answer = 0;
    int start = h1 * 60 * 60 + m1 * 60 + s1;
    int end = h2 * 60 * 60 + m2 * 60 + s2;
    double h[2], m[2], s[2];
    
    h[0] = start % 43200 * (1 / (double)120);
    m[0] = start % 3600 * (1 / (double)10);
    s[0] = start % 60 * (double)6;
    
    if (h[0] == s[0] && m[0] == s[0]) {
        answer++;
    }
    
    for (int i = start; i < end; i++) {
        for (int j = 0; j < 2; j++) {
            h[j] = (i + j) % 43200 * (1 / (double)120);
            m[j] = (i + j) % 3600 * (1 / (double)10);
            s[j] = (i + j) % 60 * (double)6;
        }

        // i+1초에 0도로 돌아온 경우는 360도로 계산해야함 (i초일때 초침이 354도이면 i+1초일때 초침은 360도이어야 하므로)
        if (h[1] == 0) h[1] = 360;
        if (m[1] == 0) m[1] = 360;
        if (s[1] == 0) s[1] = 360;
        
        if (h[1] == s[1] && m[1] == s[1]) {
            answer++;
        } else {
            if (h[0] > s[0] && h[1] <= s[1]) {
                answer++;
            }
            if (m[0] > s[0] && m[1] <= s[1]) {
                answer++;
            }
        }
    }
    
    return answer;
}
