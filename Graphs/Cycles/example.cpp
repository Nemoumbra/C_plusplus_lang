#include <iostream>
#include <vector>
#include <queue>;
#include <Windows.h>
using namespace std;
int DFS(int v, int call, int from, int dest, vector <int> &color, vector <int> &parent, vector <int> &first, vector <int> &data, vector <int> &next) {
	if (color[v]!=0)
		return 0;
	parent[v]=from;
	if (call != v) {
		if (v == dest) {
			return 1;
		}
		color[v]=1;
	}
	for (int i=first[v]; i!=-1; i = next[i]) {
		if (call != data[i] && call != v) {
		    if (DFS(data[i], -1, v, dest, color, parent, first, data, next) == 1)
			    return 1;
		}
		if (call != data[i] && call == v) {
			if (DFS(data[i], call, v, dest, color, parent, first, data, next) == 1)
				return 1;
		}
	}
	color[v]=2;
	return 0;
}

void cycles_detector(vector <int> &first, vector <int> &data, vector <int> &next, vector <int> &path) {
	vector <int> colour(first.size()), parent(first.size());
	for (int i=0; i<first.size(); i++) {
		for (int j=0; j<first.size(); j++) {
			colour[j]=0;
		}
		if (DFS(i, i, i, i, colour, parent, first, data, next) == 1) {
			path.push_back(i);
			for (int j=parent[i]; j!=i; j=parent[j]) {
				path.push_back(j);
			}
			path.push_back(i);
			for (int j=0; j<path.size()/2; j++) {
				swap(path[j], path[path.size()-1-j]);
			}
			return;
		}
	}
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
	vector <int> road;
	cycles_detector(first, data, next, road);
	if (road.size()!=0) {
		cout<<"Cycle found!"<<endl;
		for (int i=0; i<road.size(); i++) {
			cout<<road[i]<<" ";
		}
	}
	else cout<<"No cycles found";
	cout<<endl;
	system("pause");
	return 0;
}
