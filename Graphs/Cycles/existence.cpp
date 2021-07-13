#include <iostream>
#include <vector>
#include <queue>;
#include <Windows.h>
using namespace std;
int DFS(int v, int call, int from, int dest, vector <int> &color, vector <int> &first, vector <int> &data, vector <int> &next) {
	if (color[v]!=0)
		return 0;
	if (call != v) {
		if (v == dest) {
			return 1;
		}
		color[v]=1;
	}
	for (int i=first[v]; i!=-1; i = next[i]) {
		if (call != data[i] && call != v) {
		    if (DFS(data[i], -1, v, dest, color, first, data, next) == 1)
			    return 1;
		}
		if (call != data[i] && call == v) {
			if (DFS(data[i], call, v, dest, color, first, data, next) == 1)
				return 1;
		}
	}
	color[v]=2;
	return 0;
}

int cycles_exist(vector <int> &first, vector <int> &data, vector <int> &next) {
	vector <int> colour(first.size());
	for (int i=0; i<first.size(); i++) {
		for (int j=0; j<first.size(); j++) {
			colour[j]=0;
		}
		if (DFS(i, i, i, i, colour, first, data, next) == 1) {
			return 1;
		}
	}
	return 0;
}

int main() {
	int n, m;
	cin>>n>>m;
	vector <int> first(n, -1), data, next;
	int x, y;
	for (int i=0; i<m; i++) {	
		cin>>x>>y;
		data.push_back(y);
		next.push_back(first[x]);
		first[x]=data.size()-1;		
	}
	cout<<"Searching for cycles"<<endl;
	if (cycles_exist(first, data, next)) {
		cout<<"There is at least one cycle";
	}
	else cout<<"No cycles found";
	cout<<endl;
	system("pause");
	return 0;
}
