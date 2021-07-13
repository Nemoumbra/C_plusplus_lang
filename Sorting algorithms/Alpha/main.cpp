#include <iostream>
#include <time.h>
#include <Windows.h>
#include <vector>
using namespace std;
void print_array(vector <int> &array) {
	for (int i=0; i<array.size(); i++) {
		cout<<array[i]<<" ";
		if ((i+1)%10 ==0) 
			cout<<endl;
	}
	cout<<endl;
}
int check(vector <int> &array) {
	for (int i=0; i<array.size()-1; i++) {
		if (array[i]>array[i+1])
			return 0;
	}
	return 1;
}
void bubblesort(vector <int> &array, int * g) {
	int swapped;
	for (int i=1; i<array.size(); i++, (*g)++) {
		swapped=0;
		for (int j=0; j<array.size()-i; j++, (*g)++) {
			if (array[j]>array[j+1]) {
				swap(array[j], array[j+1]);
				(*g)++;
		     	swapped=1;
			}
		}
		if (!swapped)
			return;
	}
}
void shakersort(vector <int> &array, int *g) {
	int swapped;
	for (int i=0; i<array.size()/2; i++, (*g)++) {
		swapped=0;
		for (int j=i; j<array.size()-1-i; j++, (*g)++) {
			if (array[j]>array[j+1]) {
				swap(array[j], array[j+1]);
				(*g)++;
				swapped=1;
			}
		}
		if (!swapped)
			return;
		swapped=0;
		for (int j=array.size()-2-i; j>i; j--, (*g)++) {
			if (array[j]<array[j-1]) {
				swap(array[j], array[j-1]);
				(*g)++;
				swapped=1;
			}
		}
		if (!swapped)
			return;
	}
}
void countsort(vector <int> &array, int *g, int *m) {
	int max=array[0], min=max;
	for (int i=0; i<array.size(); i++, (*g)++) {
		if (array[i]>max) {
			max=array[i];
			(*g)++;
		}
		if (array[i]<min) {
			min=array[i];
			(*g)++;
		}
	}
	vector <int> temp(max-min+1, 0);
	(*m)=max-min+1;
	for (int i=0; i<array.size(); i++, (*g)++) {
		    temp[array[i]-min]++;
			(*g)++;
	    }
	int k=0;
	for (int i=0; i<temp.size(); i++, (*g)++) {
		 for (int j=0; j<temp[i]; j++, (*g)++) {
			 array[k]=i+min;
			 k++;
		     (*g)++;
		 }
	}
}
void selectsort(vector <int> &array, int *g) {
	int max, done;
	for (int i=0; i<array.size(); i++, (*g)++) {
		max=0;
		done=1;
		for (int j=0; j<array.size()-i; j++, (*g)++) {
			if (array[j]>array[max]) {
				max=j;
				(*g)++;
			}
			if (j<array.size()-1) {
				if (array[j]>array[j+1]) {
					done=0;
				}
			}
		}
		if (done == 1)
			return;
		swap(array[max], array[array.size()-1-i]);
		(*g)++;
	}
}
void double_selectsort(vector <int> &array, int *g) {
	int max, min, done;
	for (int i=0; i<array.size()/2; i++, (*g)++) {
		max=i;
		min=array.size()-1-i;
		done=1;
		for (int j=i; j<array.size()-i; j++, (*g)++) {
			if (array[j]>array[max]) {
				max=j;
				(*g)++;
			}
			if (array[j]<array[min]) {
				min=j;
				(*g)++;
			}
			if (j < array.size()-1) {
				if (array[j]>array[j+1]) {
					done=0;
				}
			}
		}
		if (done == 1)
			return;
		swap(array[min], array[i]);
		if (max == i) {
			swap(array[min], array[array.size()-1-i]);
		}
		else {
			swap(array[max], array[array.size()-1-i]);
		}
		(*g)+=2;
	}
}
void insertsort(vector <int> &array, int *g) {
	int k;
	for (int i=0; i<array.size()-1; i++, (*g)++) {
		k=i+1;
		(*g)++;
		while(array[k-1]>array[k]) {
			swap(array[k], array[k-1]);
			(*g)++;
			k--;
			(*g)++;
			if (k == 0)
				break;
		}
	}
}
void merge(vector <int> A, vector <int> B, vector <int> res, int *g) {
	int p1=0, p2=0;
	while (p1 < A.size() && p2 < B.size()) {
		if (A[p1] > B[p2]) {
			res.push_back(B[p2]);
			p2++;
			(*g)++;
		}
		else if (A[p1] == B[p2]) {
			res.push_back(A[p1]);
			res.push_back(B[p2]);
			p1++;
			p2++;
			(*g)+=2;
		}
		else {
			res.push_back(A[p1]);
			p1++;
			(*g)++;
		}
	}
	if (p1 == A.size()) {
		for (int i=p1; i<B.size(); i++, (*g)++) {
			res.push_back(B[i]);
		}
	}
	else {
		for (int i=p2; i<A.size(); i++, (*g)++) {
			res.push_back(A[i]);
		}
	}
}
void mergesort(vector <int> &array, int *g) {
	int m = array.size()/2;
	(*g)++;
	vector <int> mas1(m), mas2(array.size()-m);
	for (int i=0; i<mas1.size(); i++, (*g)++) {
		mas1[i]=array[i];
	}
	for (int i=m+1; i<mas2.size(); i++, (*g)++) {
		mas2[i]=array[i];
	}
	mergesort(mas1, g);
	mergesort(mas2, g);
	merge(mas1, mas2, array, g);
}
int main() {
	clock_t a, b;  
	int g=0, m=0;
	int k;
	cout<<"Choose the algotithm by entering the corresponding number"<<endl;
	cout<<"Bubble sort (1), shaker sort (2), selection sort (3), double section sort (4),"<<endl;
	cout<<"insertion sort (5), counting sort (6), merge sort (7)"<<endl;
	cin>>k;
	switch (k) {
	case 1: 
		cout<<"Bubble sort";
		break;
	case 2:
		cout<<"Shaker sort";
		break;
	case 3:
		cout<<"Selection sort";
		break;
	case 4:
		cout<<"Double selection sort";
		break;
	case 5:
		cout<<"Insertion sort";
		break;
	case 6:
		cout<<"Counting sort";
		break;
	case 7:
		cout<<"Merge sort";
		break;
	default:
		cout<<"Error: input mismatch";
		system("pause");
		exit(1);
	}
	cout<<" chosen"<<endl;
	int N;
	cout<<"Enter the number of random integers"<<endl;
	cin>>N;
	cout<<"Creating an array of "<<N<<" integers"<<endl;
	vector <int> mas(N);
	srand(777);
	for (int i=0; i<N; i++) {
		mas[i]=rand()%10000+rand();
	}
	cout<<"Done, sorting started"<<endl;
	a = clock();
	int success1=1, success2=1;
	if (a == -1)
		success1=0;
	switch (k) {
	case 1 : 
		bubblesort(mas, &g);
		break;
	case 2 :
		shakersort(mas, &g);
		break;
	case 3:
		selectsort(mas, &g);
	case 4:
		double_selectsort(mas, &g);
		break;
	case 5:
		insertsort(mas, &g);
		break;
	case 6:
		countsort(mas, &g, &m);
		break;
	case 7:
		mergesort(mas, &g);
		break;
	}
	if (success1 == 1) {
		b = clock();
	}
	if (b == -1)
		success2=0;
	double time;
	if (check(mas) == 1) {
		cout<<"Success! ";
	}
	else cout<<"Failure! ";
	cout<<"It took "<<g<<" operations and ";
	if (success1 == 0 || success2 == 0) {
		cout<<"the time could not be measured"<<endl;
	}
	else {
		time=difftime(b,a);
		cout<<time/CLOCKS_PER_SEC<<" seconds"<<endl;
	}
	if (k == 6) {
		cout<<"Memory used: "<<sizeof(int)*m<<" bytes"<<endl;
	}
	system("pause");
	return 0;
}
