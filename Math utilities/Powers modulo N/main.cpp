#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;
int power(int a, int b) {
  int res=1;
  for (int i=0; i<b; i++) {
	  res*=a;
  }
  return res;
}
int power_modulo(int a, int b, int m) {
	int res = a % m;
	for (int i=0; i<b-1; i++) {
		res *= a;
		res %= m;
	}
	return res;
}
void bubblesort(int * A, int n) {
 int swapped;
 for (int i=1; i<n; i++) {
  swapped=0;
  for (int j=0; j<n-i; j++)
   if (A[j]>A[j+1]) {
    swap(A[j], A[j+1]);
	swapped=1;
   }
   if (!swapped)
	 return;
 }
}
int main() {
 cout<<"Please enter the natural power and the modulo"<<endl;
 int n, m;
 cin>>n>>m;
 if (m == 0 || n == 0)
  exit(0); 
 int * mas = new int[m];
 for (int i=0; i<m; i++) {
   mas[i]=power_modulo(i, n, m);
 }
 bubblesort(mas, m);
 int x=-1;
 cout<<"Numbers in the power of "<<n<<" give the following resides modulo "<<m<<":"<<endl;
 for (int i=0; i<m; i++) {
  if (mas[i] != x)
   cout<<mas[i]<<" ";
   x = mas[i];
 }
 cout << endl;
 /*int a, b, m;
 cin >> a >> b >> m;
 cout << power_modulo(a, b, m) << endl;*/
 system("pause");
 return 0;
}
