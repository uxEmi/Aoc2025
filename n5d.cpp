#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	long long ans  = 0;
	string s;
	vector<pair<long long,long long>> h;
	while(fin >> s){
		if (s.find('-') == string::npos) 
			break;
		for(int i = 0;i < s.length();i++)
			if(s[i] == '-')
				s[i] = ' ';
		string x1,x2;
		stringstream ss(s);
		ss >> x1;
		ss >> x2;
		h.push_back({stoll(x1),stoll(x2)});
	}
	sort(h.begin(),h.end(),[&](pair<long long,long long> p1, pair<long long,long long> p2){
		if(p1.first != p2.first)
			return  p1.first < p2.first;
		return p1.second < p2.second;		
	});
	
	for(int i = 0;i < h.size() - 1;)
		if(h[i].first <= h[i + 1].first && h[i].second >= h[i + 1].second){
			h.erase(h.begin() + i + 1);
		}
		else if(h[i].second >= h[i + 1].first){
			h[i].second = h[i + 1].second;
			h.erase(h.begin() + i + 1);
		}else{
			i++;
		}
	for(int i = 0;i < h.size();i++){
		cout << h[i].first << ' ' << h[i].second << endl;
		ans += h[i].second - h[i].first + 1;
	}

/*	sort(h.begin(),h.end());
	long long n;
	bool ok;
	ok = false;	
	n = stoll(s);
	cout << n << endl;
	for(int i = 0;i < h.size();i++)
		if(h[i].first <= n && h[i].second >= n){
			ok = true;
			break;
		}
	if(ok){
		ans++;
	}
	while(fin >> s){
		ok = false;	
		n = stoll(s);
		cout << n << endl;
		for(int i = 0;i < h.size();i++)
			if(h[i].first <= n && h[i].second >= n){
				ok = true;
				break;
			}

		if(ok){
			ans++;
		}
	}*/
	cout << ans;

	return 0;
}
