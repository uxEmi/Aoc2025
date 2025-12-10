#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
#include <functional>
#include <sstream>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<ll> VL;
typedef vector<VL> VVL;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll solve_machine(int n_counters, vector<vector<int>>& button_indices, vector<ll>& target) {
    int n_buttons = button_indices.size();
    if (n_buttons == 0) {
        for (int i = 0; i < n_counters; i++) {
            if (target[i] != 0) return -1;
        }
        return 0;
    }
    
    VVL A(n_counters, VL(n_buttons, 0));
    for (int j = 0; j < n_buttons; j++) {
        for (int idx : button_indices[j]) {
            if (idx < n_counters) A[idx][j] = 1;
        }
    }
    
    VVL aug(n_counters, VL(n_buttons + 1));
    for (int i = 0; i < n_counters; i++) {
        for (int j = 0; j < n_buttons; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n_buttons] = target[i];
    }
    
    vector<int> pivot_col(n_counters, -1);
    int rank = 0;
    
    for (int col = 0; col < n_buttons && rank < n_counters; col++) {
        int pivot = -1;
        for (int row = rank; row < n_counters; row++) {
            if (aug[row][col] != 0) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        
        swap(aug[rank], aug[pivot]);
        pivot_col[rank] = col;
        
        for (int row = 0; row < n_counters; row++) {
            if (row != rank && aug[row][col] != 0) {
                ll g = gcd(abs(aug[rank][col]), abs(aug[row][col]));
                ll mult_row = aug[rank][col] / g;
                ll mult_rank = aug[row][col] / g;
                for (int c = 0; c <= n_buttons; c++) {
                    aug[row][c] = aug[row][c] * mult_row - aug[rank][c] * mult_rank;
                }
            }
        }
        rank++;
    }
    
    for (int i = rank; i < n_counters; i++) {
        if (aug[i][n_buttons] != 0) return -1;
    }
    
    vector<int> free_vars;
    set<int> pivot_cols;
    for (int i = 0; i < rank; i++) pivot_cols.insert(pivot_col[i]);
    for (int j = 0; j < n_buttons; j++) {
        if (pivot_cols.find(j) == pivot_cols.end()) {
            free_vars.push_back(j);
        }
    }
    
    int n_free = free_vars.size();
    ll best = LLONG_MAX;
    
    ll max_val = 0;
    for (int i = 0; i < n_counters; i++) max_val = max(max_val, target[i]);
    
    function<void(int, VL&, ll)> try_free = [&](int idx, VL& free_vals, ll current_sum) {
        if (current_sum >= best) return;
        
        if (idx == n_free) {
            VL x(n_buttons, 0);
            for (int i = 0; i < n_free; i++) {
                x[free_vars[i]] = free_vals[i];
            }
            
            for (int i = rank - 1; i >= 0; i--) {
                int pc = pivot_col[i];
                ll sum = aug[i][n_buttons];
                for (int j = 0; j < n_buttons; j++) {
                    if (j != pc) {
                        sum -= aug[i][j] * x[j];
                    }
                }
                if (sum % aug[i][pc] != 0) return;
                x[pc] = sum / aug[i][pc];
                if (x[pc] < 0) return;
            }
            
            ll total = 0;
            for (int j = 0; j < n_buttons; j++) {
                if (x[j] < 0) return;
                total += x[j];
            }
            best = min(best, total);
            return;
        }
        
        for (ll v = 0; v <= max_val; v++) {
            free_vals[idx] = v;
            try_free(idx + 1, free_vals, current_sum + v);
        }
    };
    
    if (n_free <= 3) {
        VL free_vals(n_free, 0);
        try_free(0, free_vals, 0);
    } else {
        VL x(n_buttons, 0);
        for (int i = rank - 1; i >= 0; i--) {
            int pc = pivot_col[i];
            ll sum = aug[i][n_buttons];
            for (int j = 0; j < n_buttons; j++) {
                if (j != pc) sum -= aug[i][j] * x[j];
            }
            if (aug[i][pc] == 0) {
                if (sum != 0) return -1;
                x[pc] = 0;
            } else {
                if (sum % aug[i][pc] != 0) return -1;
                x[pc] = sum / aug[i][pc];
                if (x[pc] < 0) return -1;
            }
        }
        ll total = 0;
        for (int j = 0; j < n_buttons; j++) total += x[j];
        best = total;
    }
    
    return best == LLONG_MAX ? -1 : best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("input.in");    
    string line;
    ll total = 0;
    
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        size_t brace_start = line.find('{');
        size_t brace_end = line.find('}');
        if (brace_start == string::npos || brace_end == string::npos) continue;
        
        string jolt_str = line.substr(brace_start + 1, brace_end - brace_start - 1);
        vector<ll> target;
        stringstream ss_jolt(jolt_str);
        string token;
        while (getline(ss_jolt, token, ',')) {
            target.push_back(stoll(token));
        }
        int n_counters = target.size();
        
        vector<vector<int>> buttons;
        size_t pos = 0;
        while ((pos = line.find('(', pos)) != string::npos) {
            size_t end = line.find(')', pos);
            if (end == string::npos) break;
            if (pos > brace_start) break;
            
            string btn_str = line.substr(pos + 1, end - pos - 1);
            vector<int> indices;
            stringstream ss(btn_str);
            while (getline(ss, token, ',')) {
                indices.push_back(stoi(token));
            }
            buttons.push_back(indices);
            pos = end + 1;
        }
        
        ll result = solve_machine(n_counters, buttons, target);
        if (result >= 0) total += result;
    }
    
    cout << total << endl;
    return 0;
}
