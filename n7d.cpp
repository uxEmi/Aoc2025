#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> m;
vector<vector<long long>> dp;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.in");
    string s;
    while(fin >> s)
        m.emplace_back(s);
    
    int r = m.size(),c = m[0].size();
    
    dp = vector<vector<long long>>(r, vector<long long>(c, 0));
    
    int sc = -1;
    for(int j = 0; j < c; j++){
        if(m[0][j] == 'S'){
            sc = j;
            break;
        }
    }
    
    dp[1][sc] = 1;
    
    for(int i = 1; i < r; i++){
        for(int j = 0; j < c; j++){
            if(dp[i][j] == 0) continue;
            
            long long t = dp[i][j];
            
            if(m[i][j] == '^'){
                if(i + 1 < r){
                    if(j - 1 >= 0){
                        dp[i + 1][j - 1] += t;
                    }
                    if(j + 1 < c){
                        dp[i + 1][j + 1] += t;
                    }
                }
            } else {
                if(i + 1 < r){
                    dp[i + 1][j] += t;
                }
            }
        }
    }
    
    long long ans = 0;
    for(int j = 0; j < c; j++){
        ans += dp[r - 1][j];
    }
    
    cout << ans << endl;
    
    return 0;
}
