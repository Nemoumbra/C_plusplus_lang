#include <iostream>

struct binary_heap_old {
	int * arr;
	int size;
	void sift_up(int v) {
		while (v != 1) {
			if (arr[v] < arr[v / 2]) {
				std::swap(arr[v], arr[v / 2]);
				v /= 2;
			}
			else {
				break;
			}
		}
	}
	void sift_down(int v) {
		int u;
		while (2 * v <= size) {
			u = 2 * v;
			if (u < size) {
				if (arr[u + 1] < arr[u]) {
					u++;
				}
			}
			if (arr[u] < arr[v]) {
				std::swap(arr[u], arr[v]);
				v = u;
			}
			else {
				break;
			}
		}
	}
	binary_heap_old(int max_size) {
		arr = new int[max_size + 1];
		size = 0;
	}
	int getMin() {
		return arr[1];
	}
	void insert(int x) {
		arr[++size] = x;
		sift_up(size);
	}
	void decrease_key(int v, int delta) {
		arr[v] -= delta;
		sift_up(v);
	}
	void extractMin() {
		arr[1] = arr[size--];
		sift_down(1);
	}
	void erase(int i) {
		arr[i] = arr[1] - 1;
		sift_up(i);
		extractMin();
	}
	~binary_heap_old() {
		delete[] arr;
	}
};

struct max_binary_heap {
	binary_heap_old heap;
	max_binary_heap(int max_size) : heap(max_size) {
		
	}
	int getMax() {
		return -heap.arr[1];
	}
	void insert(int x) {
		heap.insert(-x);
	}
	void decrease_key(int v, int delta) {
		heap.decrease_key(v, -delta);
	}
	void extractMax() {
		heap.extractMin();
	}
	void erase(int v) {
		heap.erase(v);
	}
};

void task_first() {
	int N, K;
	std::cin >> N >> K;

	max_binary_heap heap(K + 1);
	int a_0;
	long long x, y;
	int modulo = 1 << 30;
	std::cin >> a_0 >> x >> y;

	int a_i = a_0;
	for (int i = 0; i < K; i++) {
		a_i = (x * a_i + y) % modulo;
		heap.insert(a_i);
	}

	for (int i = K; i < N; i++) {
		a_i = (x * a_i + y) % modulo;
		if (a_i < heap.getMax()) {
			heap.extractMax();
			heap.insert(a_i);
		}
	}

	int * reverse = new int[K];
	for (int i = 0; i < K; i++) {
		reverse[i] = heap.getMax();
		heap.extractMax();
	}
	for (int i = K - 1; i >= 0; i--) {
		std::cout << reverse[i] << " ";
	}

	delete[] reverse;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	task_first();
	return 0;
}