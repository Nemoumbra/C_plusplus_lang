#include <iostream>
#include <vector>
#include <queue>;
#include <Windows.h>
using namespace std;
void BFS(int A, int B, vector <int> &first, vector <int> &data, vector <int> &next, vector <int> &path) {
	vector <int> been(first.size(), 0), dist(first.size());
	queue <int> q;
	int v;
	q.push(A);
	been[A]=1;
	while (!q.empty()) {
		v = q.front();
		for (int i=first[v]; i!=-1; i = next[i]) {
			if (!been[data[i]]) {
				been[data[i]]=1;
				dist[data[i]]=dist[v]+1;
				q.push(data[i]);
			}
		}
		q.pop();
	}
	int t;
	if (been[B]) {
		path.push_back(B);
		for (int i=B; dist[i]!=0; i = t) {
			for (int j = first[i]; j!=-1; j = next[j]) {
				if (dist[i]==dist[data[j]]+1) {
					path.push_back(data[j]);
					t=data[j];
					break;
				}
			}
		}
		for (int i=0; i<path.size()/2; i++) {
			swap(path[i], path[path.size() - i - 1]);
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
	
	vector <int> been(n, 0);
	queue <int> q;
	int v, count=0, N=0, t=-1;
	while (N!=t) {
     t=N;
	 count++;
	 been[N]=count;
	 q.push(N);
	 while (!q.empty()) {
		 v = q.front();
		 for (int i=first[v]; i!=-1; i = next[i]) {
			 if (!been[data[i]]) {
				 been[data[i]]=count;
				 q.push(data[i]);
			 }
		 }
		 q.pop();
	 }
	 for (int k=0; k<n; k++)  {
			if (!been[k]){
				N=k;
				break;
			}
		}
	}
	cout<<count<<" components found:"<<endl;
	for (int i=1; i<=count; i++) {
		for (int j=0; j<n; j++) {
			if (been[j] == i)
				cout<<j<<" "; 
		}
		cout<<endl;
	}
	system("pause");
	return 0;
}
