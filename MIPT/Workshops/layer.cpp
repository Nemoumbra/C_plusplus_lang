#include <iostream>
#include <stdlib.h>

struct point {
	int x;
	bool left;
};

int cmp_point(const void * p1, const void * p2) {
	return ((const point *)(p1))->x - ((const point *)(p2))->x;
}

void task_layer() {
	int N;
	std::cin >> N;
	point * points = new point[2 * N];
	for (int i = 0; i < 2 * N; i++) {
		std::cin >> points[i].x;
		points[i].left = !(i % 2);
	}

	qsort(points, 2*N, sizeof(point), cmp_point);
	
	int balance = 0;
	long long int total_length = 0;
	int start = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (points[i].left) {
			if (balance == 0) {
				start = points[i].x;
			}
			else {
				if (balance == 1) {
					total_length += points[i].x - start;
				}
			}
			balance++;
		}
		else {
			if (balance == 2) {
				start = points[i].x;
			}
			else {
				if (balance == 1) {
					total_length += points[i].x - start;
				}
			}
			balance--;
		}
	}
	std::cout << total_length;
	delete[] points;
}
int main() {
	task_layer();
	return 0;
}