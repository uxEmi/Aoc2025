#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool vef2(long long n){
	long long copy = n;
	vector<int> c,pattern;
	while(n){
		c.emplace_back(n % 10);
		n /= 10;
	}
	reverse(c.begin(),c.end());
	int mid = c.size() / 2;
	for(int i = 0;i < c.size();i++){
		bool ok = true;
		pattern.emplace_back(c[i]);
		if(pattern.size() > mid) break;
		if(c.size() % pattern.size() != 0) continue;
		for(int j = 0;j < c.size();j++)
			if(pattern[j % pattern.size()] != c[j]){
				ok = false;
				break;
			}
		if(ok) {
			return true;
		}
	}
	return false;
}

/*bool vef(long long n){
	vector<int> c;
	while(n){
		c.emplace_back(n % 10);
		n /= 10;
	}
	if(c.size() % 2 == 1) return false;
	reverse(c.begin(),c.end());


	int l = 0,mid = c.size() / 2, r = mid;
	while(l < mid){
		if(c[l] != c[r])
			return false;
		l++;
		r++;
	}

	return true;
}*/

int main(){
	ifstream fin("input.in");
	string s;
	fin >> s;
	for(int i = 0;i < s.length();i++)
		if(s[i] == ',')
			s[i] = ' ';
		else if(s[i] == '-')
			s[i] = ' ';
	long long x,y,ans = 0;
	istringstream ss(s);
	while(ss >> x >> y){
		for(long long i = x;i <= y;i++){
			if(vef2(i))
				ans += i;
		}
	}

	cout << ans;

	return 0;
}
