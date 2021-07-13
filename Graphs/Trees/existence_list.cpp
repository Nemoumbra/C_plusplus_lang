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

int BFS(int A, vector <int> &first, vector <int> &data, vector <int> &next) {
	vector <int> been(first.size());
	queue <int> q;
	q.push(A);
	been[A]=1;
	int v;
	while (!q.empty()) {
		v = q.front();
		for (int i=first[v]; i!=-1; i = next[i]) {
			if (!been[data[i]]) {
			    been[data[i]]=1;
			    q.push(data[i]);
			}
		}
		q.pop();
	}
	for (int i=0; i<first.size(); i++) {
		if (!been[i]) {
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
	cout<<"Checking if this graph is a tree"<<endl;
	if (cycles_exist(first, data, next) || BFS(0, first, data, next)) {
		cout<<"Not a tree";
	}
	else cout<<"It's a tree";
	cout<<endl;
	system("pause");
	return 0;
}
