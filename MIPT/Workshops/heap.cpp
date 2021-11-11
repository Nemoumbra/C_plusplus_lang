#include <iostream>
 
struct binary_heap_new {
	long long * arr;
	int * num;
	int * pointer; //pointer[i] == v and num[v] == i if v was added on the i-th query
	int size;
	int query;
	inline void exchange(int u, int v) {
		int t1 = pointer[num[u]];
		pointer[num[u]] = pointer[num[v]];
		pointer[num[v]] = t1;
 		
		long long t2 = arr[u];
		arr[u] = arr[v];
		arr[v] = t2;
 
		t1 = num[u];
		num[u] = num[v];
		num[v] = t1;
	}
	void sift_up(int v) {
		while (v != 1) {
			if (arr[v] < arr[v / 2]) {
				exchange(v, v/2);
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
					++u;
				}
			}
			if (arr[u] < arr[v]) {
				exchange(u, v);
				v = u;
			}
			else {
				break;
			}
		}
	}
	binary_heap_new(int max_size, int max_q) {
		arr = new long long[max_size + 1];
		num = new int[max_size + 1];
		pointer = new int[max_q + 1];
		size = 0;
		query = 0;
	}
	inline long long getMin() {
		++query;
		return arr[1];
	}
	void insert(long long x) {
		++size;
		++query;
		arr[size] = x;
		num[size] = query;
		pointer[query] = size;
		sift_up(size);
	}
	void decrease_key(int i, int delta) {
		++query;
		arr[pointer[i]] -= delta;
		sift_up(pointer[i]);
	}
	void extractMin() {
		//previously num[1] == i, pointer[i] == 1
		++query;
		if (size > 0) {
			exchange(1, size);
			--size;
			sift_down(1);
		}
	}
	~binary_heap_new() {
		delete[] arr;
		delete[] num;
		delete[] pointer;
	}
};
 
void task_heap() {
	int q = 0;
	std::cin >> q;
	int a = 0, b = 0;
	binary_heap_new heap(100000, q);
	char buffer[12];
	for (int i = 0; i < q; ++i) {
		std::cin >> buffer;
		switch(buffer[0]) {
			case 'i': {
				std::cin >> a;
				heap.insert(a);
				break;
			}
			case 'g': {
				std::cout << heap.getMin() << "\n";
				break;
			}
			case 'e': {
				heap.extractMin();
				break;
			}
			case 'd': {
				std::cin >> a >> b;
				heap.decrease_key(a, b);
				break;
			}
		}
	}
}
int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	task_heap();
	return 0;
}