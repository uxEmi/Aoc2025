#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <cmath>
#include <algorithm>

using namespace std;


long long eucl(const vector<long long>& a,const vector<long long>& b){
	return (a[0]-b[0])*(a[0]-b[0]) + (a[1]-b[1])*(a[1]-b[1]) + (a[2]-b[2])*(a[2]-b[2]);
}
vector<vector<long long>> val_nod,kruskal;
vector<long long> tata;

long long find(long long v){
	if(tata[v] < 0)
		return v;
	return tata[v] = find(tata[v]);
}

void join(long long a,long long b){
	if(tata[a] < tata[b]){
		tata[a] += tata[b];
		tata[b] = a;
	}else{
		tata[b] += tata[a];
		tata[a] = b;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream fin("input.in");
	long long ans = 0;
	string s;
	while(fin >> s){
		for(int i = 0;i < s.length();i++)
			if(s[i] == ',')
				s[i] = ' ';
		stringstream ss(s);
		val_nod.push_back({});
		string tok;
		while(ss >> tok)
			val_nod[val_nod.size() - 1].push_back(stoll(tok));	
	}

	kruskal = vector<vector<long long>>(3);
	tata = vector<long long>(val_nod.size(),-1);
	for(int i = 0;i < val_nod.size();i++)
		for(int j = i + 1;j < val_nod.size();j++){
			long long dis = eucl(val_nod[i],val_nod[j]);
			kruskal[0].push_back(i);
			kruskal[1].push_back(j);
			kruskal[2].push_back(dis);
		}
	vector<int> indices(kruskal[0].size());
	for(int i = 0; i < indices.size(); i++)
    		indices[i] = i;

	sort(indices.begin(), indices.end(), [&](int i, int j) {
	    if(kruskal[2][i] != kruskal[2][j])
        	return kruskal[2][i] < kruskal[2][j];	
	    if(kruskal[0][i] != kruskal[0][j])
        	return kruskal[0][i] < kruskal[0][j];
	    
	   return kruskal[1][i] < kruskal[1][j];
	});

	for(int i = 0; i < indices.size(); i++){
 		   long long h1 = find(kruskal[0][indices[i]]), h2 = find(kruskal[1][indices[i]]);
		    if(h1 != h2){
		        join(h1,h2);
    			}
		    int c = 0;
		    for(int i = 0;i < tata.size();i++)
			    if(tata[i] < 0)
				    c++;
		    if(c == 1){
			ans = val_nod[kruskal[0][indices[i]]][0] * val_nod[kruskal[1][indices[i]]][0];
		    	break;
		    }

	}
	
	cout << ans;

	/*
	vector<long long> aux;
	for(const auto& i : tata)
		if(i < 0)
			aux.push_back(abs(i));
	sort(aux.begin(),aux.end(),greater<long long>());
	ans = aux[0] * aux[1] * aux[2];
	
	cout << ans;

	for(int i = 0;i < kruskal.size();i++){
		for(int j = 0;j < kruskal[i].size();j++)
			cout << kruskal[i][j] << ' ';
		cout << endl;
	}*/
			

	/*
	for(int i = 0;i < val_nod.size();i++){
		for(int j = 0;j < val_nod[i].size();j++)
			cout << val_nod[i][j] << ' ';
		cout << endl;
	}
	prim = vector<vector<long long>>(3,vector<long long>(val_nod.size(),-1));
	int c = 0;
	prim[0][c] = 0;
	prim[1][c] = -1;
	prim[2][c] = 1;
	for(int aux = 0;aux < 10;aux++){
		if(aux == 0){
			long long m = LLONG_MAX,idx = -1; 
			fill(prim[1].begin() + 1,prim[1].end(),0);
			for(int i = 1;i < val_nod.size();i++){
				prim[0][i] = eucl(val_nod[i],val_nod[0]);
				if(prim[0][i] < m){
					m = prim[0][i];
					idx = i;
				}

			}
			c = idx;
			if(c == -1) break;
			prim[2][c] = 1;
		}else{
			long long m = LLONG_MAX,idx = -1; 
			for(int i = 0;i < val_nod.size();i++)
				if(prim[2][i] == 1) continue;
				else{
					long long h = eucl(val_nod[i],val_nod[c]);
					if(h < prim[0][i]){
						prim[0][i] = h;
						prim[1][i] = c;
					}
					if(prim[0][i] < m){
						m = prim[0][i];
						idx = i;
					}
				}
			c = idx;
			if(c == -1) break;
			prim[2][c] = 1;
		}
	}
	
	
	for(const auto& i : prim){
		for(const auto& j : i)
			cout << j << ' ';
		cout << endl;
	}*/

	return 0;
}
