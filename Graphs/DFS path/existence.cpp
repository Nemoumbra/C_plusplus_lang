#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
int DFS(int v, int dest, vector <int> &color, vector <vector <int>> matrix) {
	if (color[v]!=0) {
		return 0; //не найдено
	}
	color[v]=1;
	if (v == dest)
		return 1;
	for (int i=0; i<matrix.size(); i++) {
		if (matrix[v][i] == 1) {
			if (DFS(i, dest, color, matrix) == 1) {
				return 1;
			}
		}
	}
	color[v]=2;
	return 0;
}


int main() {
	int n;
	cin >> n;
	vector <vector <int>> matrix(n, vector <int> (n));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin >> matrix[i][j];
		}
	}
	int A, B;
	cin >> A >> B;
	vector <int> color(n, 0);
	if (DFS(A, B, color, matrix)) {
		cout<<"Possible";
	}
	else cout<<"Impossible";
	cout<<endl;
	system("pause");
	return 0;
}
