#include <iostream>
#include <stdio.h>

int quickselect_weird(int * arr, int size, int k) {
	if (k < 1 || k > size) {
		return -1;
	}
	if (size == 1) {
		return arr[0];
	}
	int pivot = arr[std::rand() % size];

	int l = 0, r = size - 1;
	for (int i = 0; i <= r;) {
		if (arr[i] < pivot) {
			if (i == l) {
				l++;
				i++;
			}
			else {
				std::swap(arr[i], arr[l]);
				l++;
				i++;
			}
		}
		else {
			if (arr[i] > pivot) {
				std::swap(arr[i], arr[r]);
				r--;
			}
			else {
				i++;
			}
		}
	}

	int p1 = -1, p3 = size, p2 = -1;
	int m;
	
	while (p2 == -1) {
		m = (p1 + p3) / 2;
		if (arr[m] < pivot) {
			p1 = m;
		}
		else {
			p3 = m;
			if (arr[m] == pivot) {
				p2 = m;
			}
		}
	}
	//found pivot
	l = p2;
	while (l - p1 > 1) {
		m = (l + p1) / 2;
		if (arr[m] < pivot) {
			p1 = m;
		}
		else {
			l = m;
		}
	}
	r = size;
	while (r - p2 > 1) {
		m = (r + p2) / 2;
		if (arr[m] > pivot) {
			r = m;
		}
		else {
			p2 = m;
		}
	}
	if (k <= l) {
		return quickselect_weird(arr, l, k);
	}
	if (k <= r) {
		return arr[r-1];
	}
	return quickselect_weird(arr + r, size - r, k - r);
}

void task_quickselect() {
	int N, K;
	std::cin >> N >> K;
	int * arr = new int[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	std::cout << quickselect_weird(arr, N, K+1);
	delete[] arr;
}
int main() {
	task_quickselect();
	return 0;
}