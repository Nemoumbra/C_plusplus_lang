#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
using namespace std;
void sort(vector <int> &array) {
	vector <int> temp;
	int k;
	for (int i=0; i<array.size(); i++) {
		temp.push_back(array[i]);
		k=i;
		if (i!=0) {
			while(temp[k-1]>temp[k]) {
				swap(temp[k], temp[k-1]);
				k--;
				if (k == 0)
					break;
			}
		}
	}
	for (int i=0; i<array.size(); i++) {
		array[i]=temp[i];
	}
}
int main() {
	cout<<"Let's test the given sorting algorithm"<<endl;
	clock_t a, b;
	double res=0.0;
	vector <int> mas(5000);
	srand(100);
	for (int i=0; i<100; i++) {
		for (int j=0; j<5000; j++)
			mas[j]=rand()%10000+rand();
		a=clock();
		if (a==-1)
			exit(1);
		sort(mas);
		b=clock();
		if (b == -1)
			exit(-1);
		res+=difftime(b,a);
	}
	cout<<res/CLOCKS_PER_SEC<<" seconds"<<endl;
	system("pause");
	return 0;
}
