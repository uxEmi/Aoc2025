#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("input.in");
    
    vector<pair<long long, long long>> pts;
    string s;
    while(fin >> s){
        for(char &c : s) if(c == ',') c = ' ';
        stringstream ss(s);
        long long x, y;
        ss >> x >> y;
        pts.push_back({x, y});
    }
    
    int n = pts.size();
    
    set<long long> xs_set, ys_set;
    for(auto &p : pts){
        xs_set.insert(p.first);
        ys_set.insert(p.second);
    }
    
    vector<long long> xs(xs_set.begin(), xs_set.end());
    vector<long long> ys(ys_set.begin(), ys_set.end());
    
    set<long long> xs_full, ys_full;
    for(long long x : xs){
        xs_full.insert(x);
        xs_full.insert(x - 1);
        xs_full.insert(x + 1);
    }
    for(long long y : ys){
        ys_full.insert(y);
        ys_full.insert(y - 1);
        ys_full.insert(y + 1);
    }
    
    xs.assign(xs_full.begin(), xs_full.end());
    ys.assign(ys_full.begin(), ys_full.end());
    
    map<long long, int> xi, yi;
    for(int i = 0; i < (int)xs.size(); i++) xi[xs[i]] = i;
    for(int i = 0; i < (int)ys.size(); i++) yi[ys[i]] = i;
    
    int W = xs.size(), H = ys.size();
    
    vector<vector<int>> grid(W, vector<int>(H, 0));
    
    for(int i = 0; i < n; i++){
        int j = (i + 1) % n;
        long long px1 = pts[i].first, py1 = pts[i].second;
        long long px2 = pts[j].first, py2 = pts[j].second;
        
        if(px1 == px2){
            int cx = xi[px1];
            long long yLo = min(py1, py2), yHi = max(py1, py2);
            for(int cy = 0; cy < H; cy++){
                if(ys[cy] >= yLo && ys[cy] <= yHi){
                    grid[cx][cy] = 1;
                }
            }
        } else {
            int cy = yi[py1];
            long long xLo = min(px1, px2), xHi = max(px1, px2);
            for(int cx = 0; cx < W; cx++){
                if(xs[cx] >= xLo && xs[cx] <= xHi){
                    grid[cx][cy] = 1;
                }
            }
        }
    }
    
    vector<pair<int,int>> queue;
    queue.push_back({0, 0});
    grid[0][0] = 2;
    
    while(!queue.empty()){
        auto [cx, cy] = queue.back();
        queue.pop_back();
        
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        
        for(int d = 0; d < 4; d++){
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if(nx >= 0 && nx < W && ny >= 0 && ny < H && grid[nx][ny] == 0){
                grid[nx][ny] = 2;
                queue.push_back({nx, ny});
            }
        }
    }
    
    
    vector<vector<int>> prefix(W + 1, vector<int>(H + 1, 0));
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            int val = (grid[i][j] == 2) ? 1 : 0;
            prefix[i+1][j+1] = val + prefix[i][j+1] + prefix[i+1][j] - prefix[i][j];
        }
    }
    
    auto countOutside = [&](int cx1, int cy1, int cx2, int cy2) -> int {
        if(cx1 > cx2) swap(cx1, cx2);
        if(cy1 > cy2) swap(cy1, cy2);
        return prefix[cx2+1][cy2+1] - prefix[cx1][cy2+1] - prefix[cx2+1][cy1] + prefix[cx1][cy1];
    };
    
    long long ans = 0;
    
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int cx1 = xi[pts[i].first], cy1 = yi[pts[i].second];
            int cx2 = xi[pts[j].first], cy2 = yi[pts[j].second];
            
            if(countOutside(cx1, cy1, cx2, cy2) == 0){
                long long area = (abs(pts[i].first - pts[j].first) + 1) * 
                                 (abs(pts[i].second - pts[j].second) + 1);
                ans = max(ans, area);
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
