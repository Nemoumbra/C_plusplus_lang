#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
int DFS(int v, int from, int dest, vector <int> &color, vector <int> &parent, vector <int> &first, vector <int> &data, vector <int> &next) {
	if (color[v]!=0) {
		return 0; //не найдено
	}
	color[v]=1;
	parent[v]=from;
	if (v == dest)
		return 1;
	for (int i=first[v]; i!=-1; i = next[i]) {
		if (DFS(data[i], v, dest, color, parent, first, data, next) == 1) {
			return 1; //найдено
		}
	}
	color[v]=2;
	return 0; //не найдено
}
int main() {
	int n, m;
	cin>>n>>m;
	vector <int> first(n, -1), data, next, color(n, 0), parent(n);
	int A, B;
	for (int i=0; i<m; i++) {	
		cin>>A>>B;
		data.push_back(B);
		next.push_back(first[A]);
		first[A]=data.size()-1;		
	}
	int flag=0;
	vector <int> components (n, 0);
	int t=0, N=-1; 
	for (int i=1; t!=N; i++) {
		N=t; //сохраняем t
		components[N]=i;
		for (int j=1; j<n; j++) {
			if (components[j] == 0) {
				for (int k=0; k<n; k++)
					color[k]=0;
				flag=DFS(N, -1, j, color, parent, first, data, next);
				if (flag == 1) {
					components[j]=i;
				}
				else t=j;
			}
		}
	}
	int count=0;
	for (int i=0; i<n; i++) {
		if (components[i]>count)
			count=components[i];
	}
	cout<<count<<" components found: "<<endl;
	for (int i=1; i<=count; i++) {
		for (int j=0; j<n; j++)
			if (components[j] == i)
				cout<<j<<" ";
		cout<<endl;
	}
	system("pause");
	return 0;
}
