#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*Varianta brute force
void back(const vector<int>& h,long long& m,long long nr,int idx){
	if(nr > 999999999999)
		return;
	if(nr > m)
		m = nr;
	for(int i = idx;i < h.size();i++)
		back(h,m,nr * 10 + h[i],i + 1);
}
*/
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	string s;
	long long ans = 0;
	while(fin >> s){
		long long nr = 0;
		int idx = -1,m = -1;
		for(int i = 0;i < 12;i++){
			for(int j = (idx == -1) ? 0 : idx; j < s.length();j++){
				if(i + (s.length() - j) + 1  <= 12)
					break;
				if(m < (s[j] - 48)){
					idx = j + 1;
					m = s[j] - 48;
				}

			}
			nr = nr * 10 + m; 
			m = -1;
		}
		ans += nr;
	}	
	cout << ans;
	return 0;
}
