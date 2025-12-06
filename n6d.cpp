#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> m;
vector<string> h;
vector<char> op;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	string s;
	long long ans = 0;
	while(getline(fin,s)){
		if(s.find('+') != string::npos || s.find('*') != string::npos)
			break;
		m.emplace_back(s);
	}

	stringstream ss(s);
	char tok;
	while(ss >> tok)
		op.emplace_back(tok);

	h = vector<string>(m[0].size(),"");
	for(int i = 0;i < m.size();i++){
		for(int j = 0;j < m[i].size();j++)
			if(m[i][j] == ' ')
				continue;
			else
				h[j] += m[i][j];
	}


	int c = op.size() - 1;
	long long aux = (op[c] == '+') ? 0 : 1;
	for(int i = h.size() - 1;i >= 0;i--){
		if(h[i] != ""){
			if(op[c] == '+')
				aux += stoll(h[i]);
			else
				aux *= stoll(h[i]);
		}else{
			ans += aux;
			c--;
			aux = (op[c] == '+') ? 0 : 1;
		}
	}

	ans += aux;

	cout << ans;



	/*stringstream ss(s);
	char opc;
	while(ss >> opc){
		long long aux = (opc == '*') ? 1 : 0;

		ans += aux;
	}

	cout << ans;
*/
	/*for(const auto& i : m){
		cout << i << endl;
	}*/



	return 0;
}
