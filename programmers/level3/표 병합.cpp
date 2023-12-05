#include <string>
#include <vector>
#include <sstream>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/150366
// 구현?
// 공백으로 구분된 문자열 parsing 할 때 stringstream 쓰면 편하다...

struct Pos {
    int r;
    int c;
    
    bool operator==(const Pos& p) const {
        return r == p.r && c == p.c;
    }
};

vector<vector<string>> table(51, vector<string>(51));
vector<vector<vector<Pos>>> link(51, vector<vector<Pos>>(51));

void update(int r, int c, string value) {
    vector<Pos> merged = link[r][c];
    
    if (merged.empty()) {
        table[r][c] = value;
    } else {
        for (const Pos& p : merged) {
            table[p.r][p.c] = value;
        }
    }
}

void update(string value1, string value2) {
    for (int i = 1; i <= 50; i++) {
        for (int j = 1; j <= 50; j++) {
            if (table[i][j] == value1)
                table[i][j] = value2;
        }
    }
}

void merge(int r1, int c1, int r2, int c2) {
    if (r1 == r2 && c1 == c2)
        return;
    
    string value = table[r1][c1];
    string value2 = table[r2][c2];
    vector<Pos> merged;
    
    for (const Pos& p : link[r1][c1]) {
        bool exist = false;
        for (const Pos& m : merged) {
            if (m == p) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            merged.push_back(p);
        }
    }
    for (const Pos& p : link[r2][c2]) {
        bool exist = false;
        for (const Pos& m : merged) {
            if (m == p) {
                exist = true;
                break;
            }
        }
        if (!exist) {
            merged.push_back(p);
        }
    }
    
    bool exist = false;
    Pos pos1 = {r1, c1};
    Pos pos2 = {r2, c2};
    for (const Pos& m : merged) {
        if (m == pos1) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        merged.push_back(pos1);
    }
    
    exist = false;
    for (const Pos& m : merged) {
        if (m == pos2) {
            exist = true;
            break;
        }
    }
    if (!exist) {
        merged.push_back(pos2);
    }
    
    for (const Pos& p : merged) {
        link[p.r][p.c] = merged;
        
        if (value.empty()) {
            table[p.r][p.c] = value2;
        } else {
            table[p.r][p.c] = value;
        }
    }
}

void unmerge(int r, int c) {
    string value = table[r][c];
    auto merged = link[r][c];
    
    for (auto iter = merged.begin(); iter != merged.end(); iter++) {
        link[iter->r][iter->c].clear();
        table[iter->r][iter->c] = "";
    }
    
    table[r][c] = value;
}

string print(int r, int c) {
    string value = table[r][c];
    
    if (value.empty()) return "EMPTY";
    else return value;
}

vector<string> solution(vector<string> commands) {
    vector<string> answer;

    for (string command : commands) {
        stringstream ss(command);
        vector<string> params;
        string param;

        while (ss >> param) {
            params.push_back(param);
        }
        
        const string& op = params[0];
        if (op == "UPDATE") {
            if (params.size() == 4) {
                update(stoi(params[1]), stoi(params[2]), params[3]);
            } else {
                update(params[1], params[2]);
            }
        } else if (op == "MERGE") {
            merge(stoi(params[1]), stoi(params[2]), stoi(params[3]), stoi(params[4]));
        } else if (op == "UNMERGE") {
            unmerge(stoi(params[1]), stoi(params[2]));
        } else if (op == "PRINT") {
            answer.push_back(print(stoi(params[1]), stoi(params[2])));
        }
    }
    
    return answer;
}
