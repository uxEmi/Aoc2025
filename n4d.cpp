#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <utility>

using namespace std;

vector<string> m;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	string aux;
	long long ans = 0;
	while(fin >> aux)
		m.emplace_back(aux);
	while(true){
		stack<pair<int,int>> st;
		for(int i = 0;i < m.size();i++){
			for(int j = 0;j < m[i].size();j++){
				if(m[i][j] == '.') continue;
				long long n = 0;
				if(i - 1 >= 0 && m[i - 1][j] == '@')
					n++;
				if(i - 1 >= 0 && j - 1 >= 0 && m[i - 1][j - 1] == '@')
					n++;
				if(i - 1 >= 0 && j + 1 < m[i].size() && m[i - 1][j + 1] == '@')
				n++;
				if(i + 1 < m.size() && m[i + 1][j] == '@')
					n++;
				if(i + 1 < m.size() && j - 1 >= 0 && m[i + 1][j - 1] == '@')
					n++;
				if(i + 1 < m.size() && j + 1 < m[i].size() && m[i + 1][j + 1] == '@')
					n++;
				if(j - 1 >= 0 && m[i][j - 1] == '@')
					n++;
				if(j + 1 < m[i].size() && m[i][j + 1] == '@')
					n++;
				if(n < 4){
					ans++;
					st.push({i,j});	
				}
			}
		}
		if(st.empty()) break;
		while(!st.empty()){
			auto [i,j] = st.top();
			st.pop();
			m[i][j] = '.';
		}
	}
	

	/*for(int i = 0;i < m.size();i++){
		for(int j = 0;j < m[i].size();j++)
			cout << m[i][j] << ' ';
		cout << endl;
	}*/
	cout << ans;

	return 0;
}
