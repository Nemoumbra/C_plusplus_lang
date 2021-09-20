#include <iostream>
#include <vector>
#include <cmath>
//#include <fstream>
//#include <string>
//#include <map>
using namespace std;

void sort(vector <int> &arr)
{
	bool not_swapped = false;
	for (int i=0; i<arr.size(); i++) 
	{
		not_swapped = true;
		for (int j=0; j<arr.size()-1 - i; j++) 
		{
			if (arr[j] > arr[j+1]) 
			{
				swap(arr[j], arr[j+1]);
				not_swapped = false;
			}
		}
		if (not_swapped)
			return;
	}
	return;
}
void task_tiles() {
	long long int W, H, N;
	cin >> W >> H >> N;
	int l = 0, r = min(0, 0), m;
	int m_prev = m;
	while (r >= l) {
		m = (l+r)/2;
		if (m > l) {
			l = m;
		}
		else {
			r = m;
		}
	}
}
int bin_search(int* arr, int l, int r, int elem) {
	r++;
	l--;
	int m;
	while (r-l>1) {
		m = (r+l)/2;
		if (arr[m] > elem) {
			r=m;
		}
		else {
			l=m;
		}
	}
	if (arr[l] == elem)
		return l;
	if (arr[r] == elem)
		return r;
	return -1;
}
int bin_search(vector <int> &arr, int starting_from, int ending_at, int elem) {
	if (arr[starting_from] == elem)
		return starting_from;
	if (arr[ending_at] == elem)
		return ending_at;
	//int r = ending_at + 1;
	//int l = starting_from - 1;
	int r=ending_at, l = starting_from;
	int m;
	while (r-l>1) {
		m = (r+l)/2;
		if (arr[m] > elem) {
			r=m;
		}
		else {
			l=m;
		}
	}
	if (arr[l] == elem)
		return l;
	if (arr[r] == elem)
		return r;
	return -1;
}
bool bin_search_bool(int* arr, int starting_from, int less_than, int elem) {
	int l=starting_from-1, r=less_than+1, m;
	while (r-l>1) {
		m = (arr[r]+arr[l])/2;
		if (arr[m] > arr[l]) {
			l = m;
		}
		else {
			r = m;
		}
	}
	if (arr[l] == elem || arr[r] == elem) {
		return true;
	}
	return false;
}
bool bin_search_bool(vector<int> arr, int starting_from, int less_than, int elem) {
	int l=starting_from-1, r=less_than+1, m;
	while (r-l>1) {
		m = (arr[r]+arr[l])/2;
		if (arr[m] > arr[l]) {
			l = m;
		}
		else {
			r = m;
		}
	}
	if (arr[l] == elem || arr[r] == elem) {
		return true;
	}
	return false;
}
void task_merge() {
	const int mod = 1000000000;
	int N;
	cin >> N;
	int* arr = new int[2*N];
	int s = 0;
	for (int i=0; i<N; i++) {
		cin >> arr[i];
	}
	int b;
	int k=0;
	while (1) {
		cin >> b;

	}
}
void task_extract_pair_sum() {
	int N, M;
	cin >> N >> M;
	//int* mas = new int[N];
	vector <int> mas(N);
	for (int i=0; i<N; i++) {
		cin >> mas[i];
	}
	
	int p, index;
	sort(mas);
	for (int i=0; i<M; i++) {
		cin >> p;
		for (int j=0; mas[j] < p; j++) {
			index = bin_search(mas, 0, N-1, p-mas[j]);
			if (index != -1 && mas[index] != mas[j]) {
				cout << mas[j] << " " << mas[index] << "\n";
				break; //next query
			}
		}
		if (index == -1)
			cout << "Not found\n";
	}
}
int main() {
	//task_extract_pair_sum();
	//vector <int> mas(10);
	//mas = {1, 2, 2,
	int x=0;
	x++ && ++x;
	cout << x;
	system("pause");
	return 0;
}
