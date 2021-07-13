#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
int DFS(int v, int dest, vector <int> &color, vector <int> &first, vector <int> &data, vector <int> &next) {
	if (color[v]!=0) {
		return 0; //не найдено
	}
	color[v]=1;
	if (v == dest)
		return 1;
	for (int i=first[v]; i!=-1; i = next[i]) {
		if (DFS(data[i], dest, color, first, data, next) == 1) {
			return 1;
		}
	}
	color[v]=2;
	return 0;
}
int main() {
	int n;
	cin>>n;
	vector <vector <int>> matrix(n, vector <int> (n));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin>>matrix[i][j];
		}
	}
	vector <int> first(n, -1), data, next, color(n, 0)/*, parent(n), path*/;
	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n; j++) {
			if (matrix[i][j] == 1) {
				data.push_back(i);
				next.push_back(first[j]);
				first[j]=data.size()-1;
				data.push_back(j);
				next.push_back(first[i]);
				first[i]=data.size()-1;
			}
		}
	}
	int A, B;
	cin>>A>>B;
	int Flag = DFS(A, B, color, first, data, next);
	if (Flag == 1)
		cout<<"Possible"<<endl;
	else 
		cout<<"Impossible"<<endl;
	system("pause");
	return 0;
}
