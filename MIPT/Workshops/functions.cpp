#ifndef INCLUDED
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <deque>
#include <ctime>
#include <queue>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

namespace functions {

	struct node {
		int value;
		node* prev;
		int min, max;
	};

	struct stack {
	private:
		node* last;
		int _size;
	public:
		stack() {
			last = NULL;
			_size = 0;
		}
		void push(int x) {
			node* n = new node();
			n->prev = last;
			n->value = x;
			if (last == NULL) {
				n->max = x;
				n->min = x;
			}
			else {
				n->max = ((last->max >= x) ? last->max : x);
				n->min = ((last->min <= x) ? last->min : x);
			}
			last = n;
			_size++;
		}
		void pop() {
			if (last != NULL) {
				node* n = last->prev;
				delete last;
				last = n;
				_size--;
			}
		}
		int top() {
			if (last != NULL) {
				return last->value;
			}
			exit(1001);
		}
		bool empty() {
			return (last == NULL);
		}
		int size() {
			return _size;
		}
		int min() {
			if (last != NULL) {
				return last->min;
			}
			exit(1001);
		}
		int max() {
			if (last != NULL) {
				return last->max;
			}
			exit(1001);
		}
		void clear() {
			while (_size > 0) {
				pop();
			}
		}
		~stack() {
			clear();
		}
	};

	struct queue {
	private:
		stack del, add;
		void _move_to_del() {
			while (!add.empty()) {
				del.push(add.top());
				add.pop();
			}
		}
	public:
		void push(int x) {
			add.push(x);
		}
		void pop() {
			if (del.empty()) {
				_move_to_del();
			}
			del.pop();
		}
		int front() {
			if (del.empty()) {
				_move_to_del();
			}
			return del.top();
		}
		bool empty() {
			return (add.empty() && del.empty());
		}
		int size() {
			return (del.size() + add.size());
		}
		int min() {
			return ((add.min() <= del.min()) ? add.min() : del.min());
		}
		int max() {
			return ((add.max() >= del.max()) ? add.max() : del.max());
		}
	};

	int max(int a, int b) {
		return (a >= b) ? a : b;
	}
	int min(int a, int b) {
		return (a <= b) ? a : b;
	}
	int cmp_int(const void * p1, const void * p2) {
		return *(const int*)(p1)-*(const int*)(p2);
		/*if (*((const int*)(p1)) == *((const int*)(p2))) {
			return 0;
		}
		for (int mod = 10; ; mod *= 10) {
			if (*((const int*)(p1)) % mod - *((const int*)(p2)) % mod) {
				return *((const int*)(p1)) % mod - *((const int*)(p2)) % mod;
			}
		}*/
	}
	int cmp_char(const void * p1, const void * p2) {
		return *(const char*)(p1)-*(const char*)(p2);
	}

	bool checksorting(int * array, int size) {
		for (int i = 0; i < size - 1; i++) {
			if (array[i] > array[i + 1])
				return false;
		}

		return true;
	}

	void print_arr(int * arr, int size) {
		for (int i = 0; i < size; i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
	void prefixsumify(int * arr, int size) {
		for (int i = 1; i < size; i++) {
			arr[i] += arr[i - 1];
		}
	}
	void prefixsumify(int * arr, int * pref, int l, int r) {
		pref[0] = arr[0];
		for (int i = l; i < r; i++) {
			arr[i] += arr[i - 1];
			pref[i] = arr[i] + pref[i - 1];
		}
	}

	void create_sequence(int length, int min_n, int max_n, const char * filename) {
		std::ofstream file(filename);
		std::srand(std::time(0));
		file << length << " " << (std::rand() << 4) << "\n";
		for (int i = 0; i < length; i++) {
			file << (((std::rand() << 7) + rand() << 2) % max_n) + min_n << "\n";
		}
	}
	void assign_cin_to_file(const char * filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			std::cin.rdbuf(file.rdbuf());
		}
	}

	void bubblesort(std::vector < int > &arr) {
		bool swapped;
		for (unsigned int i = 0; i < arr.size(); i++) {
			swapped = false;
			for (unsigned int j = 0; j < arr.size() - 1 - i; j++) {
				if (arr[j] > arr[j + 1]) {
					std::swap(arr[j], arr[j + 1]);
					swapped = true;
				}
			}
			if (!swapped) {
				return;
			}
		}
	}

	int binsearch_inssort(std::vector < int > &arr, int rightmost, int value) {
		int l = -1, r = rightmost + 1;
		int m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (arr[m] >= value) {
				r = m;
			}
			else {
				l = m;
			}
		}
		//if (l == -1) {
		//	return 0;
		//}
		if (l == rightmost) {
			return r;
		}
		while (arr[r] == value) {
			r++;
			if (r == rightmost + 1) {
				break;
			}
		}
		//Или меняем условия в цикле "r-l>1".

		return r;
	}
	void inssort(std::vector < int > &arr) {
		int index;
		for (unsigned int i = 0; i < arr.size(); i++) {
			index = binsearch_inssort(arr, i, arr[i]);
			for (unsigned int j = 0; j < i - index; j++) {
				std::swap(arr[i - j], arr[i - j - 1]);
			}
		}
	}
	int binsearch_inssort(int * arr, int rightmost, int value) {
	int l = -1, r = rightmost + 1;
	int m;
	while (r - l > 1) {
		m = (l + r) / 2;
		if (arr[m] >= value) {
			r = m;
		}
		else {
			l = m;
		}
	}
	if (l == rightmost) {
		return r;
	}
	while (arr[r] == value) {
		r++;
		if (r == rightmost + 1) {
			break;
		}
	}
	return r;
}

	double find_root(double(*F)(double), double l, double r, double accuracy) {
		double m;
		while (r - l > accuracy) {
			m = (l + r) / 2;
			if (F(m)*F(l) <= 0) {
				r = m;
			}
			if (F(m)*F(r) <= 0) {
				l = m;
			}
		}
		return l;
	}
	//double F(double x) {
	//	return std::sin(x) + std::sqrt(x) + 3;
	//}

	int binsearch(std::vector < int > &arr, int left, int value) {
		int l = left - 1;
		unsigned int r = arr.size();
		int m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (arr[m] >= value) {
				r = m;
			}
			else {
				l = m;
			}
		}
		if (l == left - 1) {
			if (arr[r] == value) {
				return r;
			}
			else {
				return -1;
			}
		}
		if (r == arr.size()) {
			return -1;
		}
		if (arr[r] == value) {
			return r;
		}
		return -1;
	}
	int binsearch(int* arr, int size, int left, int value) {
		int l = left - 1;
		int r = size;
		int m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (arr[m] >= value) {
				r = m;
			}
			else {
				l = m;
			}
		}
		/*if (l == left - 1) {
			if (arr[r] == value) {
				return r;
			}
			else {
				return -1;
			}
		}*/
		if (r == size) {
			return -1;
		}
		if (arr[r] == value) {
			return r;
		}
		return -1;
	}
	//if there is at least one element with value = "value", returns its index, otherwise returns -1.

	//if value is in the array, returns its left-most occurence, otherwise UB. Works for sorted and partitioned by "value" arrays.
	int left_binsearch(int * arr, int size, int left, int value) {
		int l = left - 1;
		int r = size;
		int m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (arr[m] >= value) {
				r = m;
				if (arr[m] == value) {
					break;
				}
			}
			else {
				l = m;
			}
		}
		// now arr[r] == value
		while (arr[r] == value) {
			r--;
			if (r == -1) {
				break;
			}
		}
		return r + 1;
	}
	//same, but returns right-most occurence
	int right_binsearch(int * arr, int size, int left, int value) {
		int l = left - 1;
		int r = size;
		int m;
		while (r - l > 1) {
			m = (l + r) / 2;
			if (arr[m] >= value) {
				r = m;
				if (arr[m] == value) {
					break;
				}
			}
			else {
				l = m;
			}
		}
		// now arr[r] == value
		while (arr[r] == value) {
			r++;
			if (r == size) {
				break;
			}
		}
		return r;
	}

	void add_constant_to_range(int * arr, int l, int r, int k, int * pref) {
		// l from 0, r up to size - 1

	}

	void adding_progression_task() {
		int * arr;
		int * empty_arr;
		int N;
		std::cin >> N;
		arr = new int[N], empty_arr = new int[N];
		for (int i = 0; i < N; i++) {
			arr[i] = 0;
			empty_arr[i] = 0;
		}
		int l, r, a, d;
		int q;
		q = 2;
		for (int i = 0; i < q; i++) {
			std::cin >> l >> r >> a >> d;
			arr[l] += a;

			empty_arr[l + 1] += d;
			if (r + 1 < N) { 
				empty_arr[r + 1] -= d; 
			}
		}
		prefixsumify(empty_arr, N);
		for (int i = 1; i < N; i++) {
			arr[i] += arr[i - 1] + empty_arr[i];
		}
		print_arr(arr, N);
		std::cout << N;
	}

	void Partition(std::vector < int > &arr, int key) {
		std::vector < int > temp(arr.size());
		int k = 0;
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] < key) {
				temp[k] = arr[i];
				k++;
			}
		}
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] == key) {
				temp[k] = arr[i];
				k++;
			}
		}
		for (unsigned int i = 0; i < arr.size(); i++) {
			if (arr[i] > key) {
				temp[k] = arr[i];
				k++;
			}
		}
		arr = temp;
	}
	void Partition(int * arr, int size, int key, int &l_end, int &r_start) {
		std::vector < int > temp(size);
		int k = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i] < key) {
				temp[k] = arr[i];
				k++;
			}
		}
		l_end = k;
		for (int i = 0; i < size; i++) {
			if (arr[i] == key) {
				temp[k] = arr[i];
				k++;
			}
		}
		r_start = k;
		for (int i = 0; i < size; i++) {
			if (arr[i] > key) {
				temp[k] = arr[i];
				k++;
			}
		}
		for (int i = 0; i < size; i++) {
			arr[i] = temp[i];
		}
	}
	void Linear_partition(int * arr, int size, int key, int &left_part_size, int &two_parts_size) {
		int i = 0, j = size - 1;
		while (i <= j) {
			while (arr[i] < key) {
				++i;
			}
			while (arr[j] > key) {
				--j;
			}
			if (i <= j) {
				std::swap(arr[i], arr[j]);
				++i;
				--j;			
			}
		}
		left_part_size = i;
		two_parts_size = j;
	}
	void three_way_partition(int * arr, int size, int low_val, int high_val) {
		int l = 0, r = size - 1;
		for (int i = 0; i <= r;) {
			if (arr[i] < low_val) {
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
				if (arr[i] > high_val) {
					std::swap(arr[i], arr[r]);
					r--;
				}
				else {
					i++;
				}
			}
		}
	}
	void new_partition(int * arr, int size, int pivot, int& first_block_size, int& first_two_blocks_size) {
		//if (size < 2) {
		//	return;
		//	//debatable
		//}
		//std::cout << "Pivot = " << pivot << "\n";
		//std::cout << "Before: "; print_arr(arr, size);
		three_way_partition(arr, size, pivot, pivot);
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
		first_block_size = p2;
		while (first_block_size - p1 > 1) {
			m = (first_block_size + p1) / 2;
			if (arr[m] < pivot) {
				p1 = m;
			}
			else {
				first_block_size = m;
			}
		}
		first_two_blocks_size = size;
		while (first_two_blocks_size - p2 > 1) {
			m = (first_two_blocks_size + p2) / 2;
			if (arr[m] > pivot) {
				first_two_blocks_size = m;
			}
			else {
				p2 = m;
			}
		}
	} 
	void fast_new_partition(int * arr, int size, int pivot, int& first_block_size, int& first_two_blocks_size) {
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
		first_block_size = p2;
		while (first_block_size - p1 > 1) {
			m = (first_block_size + p1) / 2;
			if (arr[m] < pivot) {
				p1 = m;
			}
			else {
				first_block_size = m;
			}
		}
		first_two_blocks_size = size;
		while (first_two_blocks_size - p2 > 1) {
			m = (first_two_blocks_size + p2) / 2;
			if (arr[m] > pivot) {
				first_two_blocks_size = m;
			}
			else {
				p2 = m;
			}
		}
	}

	void quicksort(std::vector < int > &arr) {
		int m = std::rand() % arr.size();
		Partition(arr, arr[m]);
		//TBA
	}
	void quicksort(int * arr, int size) {
		if (size < 2) return;
		int m = std::rand() % size, l = 0, r = 0;
		Partition(arr, size, arr[m], l, r);
		quicksort(arr, l);
		quicksort(arr + r, size - r);
	}
	void linear_quicksort(int * arr, int size) {
		if (size < 2) return;
		print_arr(arr, size);
		std::cout << "\n";
		int x = arr[std::rand() % size];
		int b1 = 0, b2 = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i] == x) {
				std::swap(arr[i], arr[b2]);
				print_arr(arr, size); std::cout << "\n";
				b2++;
			}
			else {
				if (arr[i] < x) {
					std::swap(arr[i], arr[b1]);
					print_arr(arr, size); std::cout << "\n";
					b1++;
				}
			}
			if (b1 == b2) {
				std::swap(arr[i], arr[b2]);
				print_arr(arr, size); std::cout << "\n";
				b2++;
			}
		}
		std::cout << b1 << " " << b2 << "\n";
		print_arr(arr, size);
		//linear_quicksort(mas, 
		//linear_quicksort(mas + 
	}

	int * merge(int* arr_1, int* arr_2, int size_1, int size_2) {
		int* mas = new int[size_1 + size_2];
		int p1 = 0, p2 = 0;
		//int min_n = min(size_1, size_2);
		int k = 0;
		while (p1 < size_1 && p2 < size_2) {
			if (arr_1[p1] < arr_2[p2]) {
				mas[k] = arr_1[p1];
				k++;
				p1++;
			}
			else {
				if (arr_1[p1] > arr_2[p2]) {
					mas[k] = arr_2[p2];
					k++;
					p2++;
				}
				else {
					mas[k] = arr_1[p1];
					mas[k + 1] = arr_2[p2];
					k += 2;
					p1++;
					p2++;
				}
			}
		}
		if (p1 != size_1) {
			for (int i = p1; i < size_1; i++) {
				mas[k] = arr_1[i];
				k++;
			}
		}
		if (p2 != size_2) {
			for (int i = p2; i < size_2; i++) {
				mas[k] = arr_2[i];
				k++;
			}
		}
		return mas;
	}
	void merge(int * arr_1, int * arr_2, int size_1, int size_2, int * buffer) {
		int p1 = 0, p2 = 0;
		int k = 0;
		while (p1 < size_1 && p2 < size_2) {
			if (arr_1[p1] < arr_2[p2]) {
				buffer[k] = arr_1[p1];
				k++;
				p1++;
			}
			else {
				if (arr_1[p1] > arr_2[p2]) {
					buffer[k] = arr_2[p2];
					k++;
					p2++;
				}
				else {
					buffer[k] = arr_1[p1];
					buffer[k + 1] = arr_2[p2];
					k += 2;
					p1++;
					p2++;
				}
			}
		}
		if (p1 != size_1) {
			for (int i = p1; i < size_1; i++) {
				buffer[k] = arr_1[i];
				k++;
			}
		}
		if (p2 != size_2) {
			for (int i = p2; i < size_2; i++) {
				buffer[k] = arr_2[i];
				k++;
			}
		}
	}
	int * mergesort(int* arr, int size) {
		if (size == 1) {
			//return arr;
			int * mas = new int[1];
			mas[0] = arr[0];
			//delete[] arr;
			return mas;
		}
		int length = size / 2;
		int * mas1 = mergesort(arr, length);
		int * mas2 = mergesort(arr + length, size - length);
		int * mas = merge(mas1, mas2, length, size - length);
		delete[] mas1;
		delete[] mas2;
		//arr = mas;
		return mas;
	}

	int quickselect(int * arr, int size, int k) {
		if (k < 1 || k > size) {
			return -1;
		}
		if (size == 1) {
			return arr[0];
		}
		int m = std::rand() % size, l = 0, r = 0;
		//Partition(arr, size, arr[m], l, r);
		fast_new_partition(arr, size, arr[m], l, r);
		if (k <= l) {
			return quickselect(arr, l, k);
		}
		if (k <= r) {
			return arr[r-1];
		}
		return quickselect(arr + r, size - r, k - r);
	}
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
	struct binary_heap_new {
		int * arr;
		int * num;
		int * pointer; //pointer[i] == v and num[v] == i if v was added on the i-th query
		//long long arr[10], num[10], pointer[10];
		int size;
		int query;
		void exchange(int u, int v) {
			std::swap(pointer[num[u]], pointer[num[v]]);
			std::swap(arr[u], arr[v]);
			std::swap(num[u], num[v]);
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
						u++;
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
		binary_heap_new(int max_size) {
			arr = new int[max_size + 1];
			num = new int[max_size + 1];
			pointer = new int[max_size + 1];
			size = 0;
			query = 0;
		}
		int getMin() {
			query++;
			return arr[1];
		}
		void insert(int x) {
			size++;
			//now size == query
			query++;
			arr[size] = x;
			num[size] = query;
			pointer[query] = size;
			sift_up(size);
		}
		void decrease_key(int i, int delta) {
			query++;
			arr[pointer[i]] -= delta;
			sift_up(pointer[i]);
		}
		void extractMin() {
			//previously num[1] == i, pointer[i] == 1
			query++;
			arr[1] = arr[size];
			pointer[num[size]] = 1;
			size--;
			sift_down(1);
		}
		void heapify() {
			for (int i = size; i >= 1; i--) {
				sift_down(i);
			}
		}
		void erase(int v) {
			arr[v] = arr[1] - 1;
			sift_up(v);
			extractMin();
		}
		~binary_heap_new() {
			delete[] arr;
			delete[] num;
			delete[] pointer;
		}
	};
	struct binary_heap_vector {
		std::vector <long long> arr;
		std::vector <int> num;
		std::vector <int> pointer; //pointer[i] == v and num[v] == i if v was added on the i-th query
		inline void exchange(int u, int v) {
			int k = num[u];
			int m = num[v];
			std::swap(pointer[k], pointer[m]);
			std::swap(arr[u], arr[v]);
			std::swap(num[u], num[v]);
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
			while (2 * v <= arr.size() - 1) {
				u = 2 * v;
				if (u < arr.size() - 1) {
					if (arr[u + 1] < arr[u]) {
						u++;
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
		binary_heap_vector() {
			arr.push_back(-1);
			num.push_back(-1);
			pointer.push_back(-1);
		}
		inline long long getMin() {
			pointer.push_back(-1);
			return arr[1];
		}
		void insert(long long x) {
			arr.push_back(x);
			num.push_back(pointer.size() - 1);
			pointer.push_back(arr.size() - 1);
			sift_up(arr.size());
		}
		void decrease_key(int i, int delta) {
			pointer.push_back(-1);
			arr[pointer[i]] -= delta;
			sift_up(pointer[i]);
		}
		void extractMin() {
			//previously num[1] == i, pointer[i] == 1
			pointer.push_back(-1);
			if (arr.size() > 1) {
				exchange(1, arr.size() - 1);
				arr.pop_back();
				num.pop_back();
				if (arr.size() > 1) {
					sift_down(1);
				}
			}
		}
	};

	struct vector {
		int * arr;
		int size;
		int capacity;
		vector(int start_capacity = 16) {
			arr = new int[start_capacity];
			capacity = start_capacity;
			size = 0;
		}
		void push_back(int x) {
			if (size < capacity) {
				arr[size] = x;
				size++;
			}
			else {
				//std::cout << "I think, we should realloc now: cap = " << capacity << ", size = " << size << "\n";
				capacity *= 2;
				int * temp = new int[capacity];
				for (int i = 0; i < size; i++) {
					temp[i] = arr[i];
				}
				temp[size] = x;
				size++;
				delete[] arr;
				arr = temp;
			}
		}
		int operator[](int i) {
			return arr[i];
		}
		void pop_back() {
			size--;
			if (size <= capacity / 4) {
				//std::cout << "I think, we should realloc now: cap = " << capacity << ", size = " << size << "\n";
				capacity /= 2;
				int * temp = new int[capacity];
				for (int i = 0; i < size; i++) {
					temp[i] = arr[i];
				}
				delete[] arr;
				arr = temp;
			}
		}
		~vector() {
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

	void foo(int * mas, int size) {
		int * arr = new int[size];
		mas = arr;
		delete[] mas;
		mas = arr;
	}

	struct binary_minmax_heap {
		int * min_arr;
		int * max_arr;
		//int min_arr[10];
		//int max_arr[10];
		int minheap_size;
		int maxheap_size;
		//max_to_min[i] = j <=> max_arr[i] = min_arr[j] <=> min_to_max[j] = i;
		int * max_to_min;
		int * min_to_max;
		//int max_to_min[10];
		//int min_to_max[10];

		void minheap_siftup(int v) {
			while (v != 1) {
				if (min_arr[v / 2] > min_arr[v]) {
					std::swap(min_arr[v / 2], min_arr[v]);
					std::swap(min_to_max[v / 2], min_to_max[v]);
					std::swap(max_to_min[min_to_max[v / 2]], max_to_min[min_to_max[v]]);
					v /= 2;
				}
				else {
					break;
				}
			}
		}
		void minheap_siftdown(int v) {
			int u;
			while (2 * v <= minheap_size) {
				u = 2 * v;
				if (u < minheap_size && min_arr[u] > min_arr[u+1]) {
					u++;
				}
				if (min_arr[u] < min_arr[v]) {
					std::swap(min_arr[u], min_arr[v]);
					std::swap(min_to_max[u], min_to_max[v]);
					std::swap(max_to_min[min_to_max[u]], max_to_min[min_to_max[v]]);
					v = u;
				}
				else {
					break;
				}
			}
		}
		void maxheap_siftup(int v) {
			while (v != 1) {
				if (max_arr[v / 2] > max_arr[v]) {
					std::swap(max_arr[v / 2], max_arr[v]);
					std::swap(max_to_min[v / 2], max_to_min[v]);
					std::swap(min_to_max[max_to_min[v / 2]], min_to_max[max_to_min[v]]);
					v /= 2;
				}
				else {
					break;
				}
			}
		}
		void maxheap_siftdown(int v) {
			int u;
			while (2 * v <= maxheap_size) {
				u = 2 * v;
				if (u < maxheap_size && max_arr[u] > max_arr[u+1]) {
					u++;
				}
				if (max_arr[u] < max_arr[v]) {
					std::swap(max_arr[u], max_arr[v]);
					std::swap(max_to_min[u], max_to_min[v]);
					std::swap(min_to_max[max_to_min[u]], min_to_max[max_to_min[v]]);
					v = u;
				}
				else {
					break;
				}
			}
		}

		binary_minmax_heap(int max_size) {
			min_arr = new int[max_size + 1];
			max_arr = new int[max_size + 1];
			max_to_min = new int[max_size + 1];
			min_to_max = new int[max_size + 1];
			minheap_size = 0;
			maxheap_size = 0;
		}

		void minheap_extractMin() {
			min_arr[1] = min_arr[minheap_size];
			min_to_max[1] = min_to_max[minheap_size];
			max_to_min[min_to_max[minheap_size]] = 1;
			minheap_size--;
			minheap_siftdown(1);
		}
		void maxheap_extractMax() {
			max_arr[1] = max_arr[maxheap_size];
			max_to_min[1] = max_to_min[maxheap_size];
			min_to_max[max_to_min[maxheap_size]] = 1;
			maxheap_size--;
			maxheap_siftdown(1);
		}

		void minheap_erase(int v) {
			min_arr[v] = min_arr[1] - 1;
			minheap_siftup(v);
			minheap_extractMin();
		}
		void maxheap_erase(int v) {
			max_arr[v] = max_arr[1] - 1;
			maxheap_siftup(v);
			maxheap_extractMax();
		}
		void insert(int x) {
			minheap_size++;
			maxheap_size++;
			min_arr[minheap_size] = x;
			max_arr[maxheap_size] = -x;
			max_to_min[minheap_size] = minheap_size;
			min_to_max[maxheap_size] = maxheap_size;
			minheap_siftup(minheap_size);
			maxheap_siftup(maxheap_size);
		}
		int getMin() {
			int ans = min_arr[1];
			maxheap_erase(min_to_max[1]);
			//std::cout << is_synchronized() << "\n";
			minheap_extractMin();
			return ans;
		}
		int getMax() {
			int ans = max_arr[1];
			minheap_erase(max_to_min[1]);
			maxheap_extractMax();
			return -ans;
		}

		~binary_minmax_heap() {
			delete[] min_arr;
			delete[] max_arr;
			delete[] max_to_min;
			delete[] min_to_max;
		}

		bool is_synchronized() {
			for (int i = 1; i <= minheap_size; i++) {
				if (min_arr[i] != -max_arr[min_to_max[i]]) {
					std::cout << "Min error\n";
					std::cout << min_arr[i] << " " << min_to_max[i] << " " << max_arr[min_to_max[i]] << "\n";
					return false;
				}
				if (max_arr[i] != -min_arr[max_to_min[i]]) {
					std::cout << "Max error\n";
					std::cout << -max_arr[i] << " " << max_to_min[i] << " " << min_arr[max_to_min[i]] << "\n";
					return false;
				}
			}
			return true;
		}
	};
}
