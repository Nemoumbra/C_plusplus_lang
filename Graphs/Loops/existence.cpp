#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
int main() {
	int n; 
	cin>>n;
	vector <vector <int>> matrix(n, vector <int> (n));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin>>matrix[i][j];
		}
	}
	//начало задачи
	int flag=0;
	for (int i=0; i<n; i++) {
		if (matrix[i][i] == 1) {
			flag=1;
			break;
		}
	}
	if (flag == 0)
		cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	system("pause");
	return 0;
}
