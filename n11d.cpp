#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

unordered_map<string, vector<string>> l_v;
unordered_map<string, int> viz;
unordered_map<string, long long> memo; 

string makeKey(const string& nod, int dac, int fft) {
    return nod + "|" + to_string(dac) + "|" + to_string(fft);
}

long long solve(const string& nod) {
    viz[nod] = 1;
    
    int dac_state = viz["dac"];
    int fft_state = viz["fft"];
    
    if (nod == "out") {
        viz[nod] = 0;
        return (dac_state == 1 && fft_state == 1) ? 1 : 0;
    }
    
    string key = makeKey(nod, dac_state, fft_state);
    if (memo.count(key)) {
        viz[nod] = 0;
        return memo[key];
    }
    
    long long paths = 0;
    for (int i = 0; i < l_v[nod].size(); i++) {
        if (viz[l_v[nod][i]] == 0) {
            paths += solve(l_v[nod][i]);
        }
    }
    
    memo[key] = paths;
    viz[nod] = 0;
    return paths;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ifstream fin("input.in");
    string s;
    while (getline(fin, s)) {
        stringstream ss(s);
        string tok;
        ss >> tok;
        string key = tok.substr(0, tok.length() - 1);
        while (ss >> tok) {
            l_v[key].push_back(tok);
        }
    }
    
    cout << solve("svr") << endl;
    
    return 0;
}
