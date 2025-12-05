#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	string s;
	long long ans = 0, dial = 50;
	while(fin >> s){
		char dir = s[0];
		long long rot = stoi(s.substr(1)) % 100,zeros = stoi(s.substr(1)) / 100;
		if(zeros) ans += zeros;
		if(dir == 'L'){
			if(dial >= rot){
				if(dial == rot)
					ans++;
				dial -= rot;
			}else{
				if(dial != 0)
					ans++;
				long long aux = abs(dial - rot);
				dial = 100 - aux;
				
			}
		}else{
			if(dial + rot < 100)
				dial += rot;
			else{
				dial = (dial + rot) % 100;
				ans++;
			}
		}

		
	}

	cout << ans ;

	return 0;
}
