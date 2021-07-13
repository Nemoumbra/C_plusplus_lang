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
	cout<<"Enter A and B"<<endl;
	int A, B;
	cin>>A>>B;
	vector <int> road;
	BFS(A, B, first, data, next, road);
	for (int i=0; i<road.size(); i++) {
		cout<<road[i]<<" ";
	}

	system("pause");
	return 0;
}
