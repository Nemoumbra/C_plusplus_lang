#include <stdio.h>
#include <iostream>
void task_median_naive() {
	int N = 0;
	scanf("%d", &N);
	int * arr = new int[N];
	int size = 0;
	int a, b;
	int l, r, m;
	for (int i = 0; i < N; i++) {
		scanf("%d", &a);
		if (!a) {
			scanf("%d", &arr[size]);

			l = -1, r = size + 1;
			while (r - l > 1) {
				m = (l + r) / 2;
				if (arr[m] >= arr[size]) {
					r = m;
				}
				else {
					l = m;
				}
			}
			if (l == size + 1) {
				b = r;
			}
			else {
				while (arr[r] == arr[size]) {
					r++;
					if (r == size + 1) {
						break;
					}
				}
				b = r;
			}

			for (int j = 0; j < size - b; j++) {
				std::swap(arr[size - j], arr[size - j - 1]);
			}
			size++;
		}
		else {
			printf("%d\n", arr[(size + 1)/ 2 - 1]);
		}
	}
	delete[] arr;
}

int main() {
	task_median_naive();
	return 0;
}