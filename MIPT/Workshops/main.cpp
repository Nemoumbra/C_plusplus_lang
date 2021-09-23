#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include <deque>

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
void bubblesort(std::vector < int > &arr) {
	bool swapped;
	for (unsigned int i = 0; i < arr.size(); i++) {
		swapped = false;
		for (unsigned int j = 0; j < arr.size() - 1 - i; j++) {
			if (arr[j] > arr[j+1]) {
				std::swap(arr[j], arr[j+1]);
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
	if (l == -1) {
		return 0;
	}
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
double find_root(double (*F)(double), double l, double r, double accuracy) {
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
double F(double x) {
	return std::sin(x) + std::sqrt(x) + 3;
}
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
	if (l == left  - 1) {
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

void task_tiles_naive() {
	int W, H, N;
	std::cin >> W >> H >> N;
	long long int max_n = 0, min_n = ((H > W) ? H : W) * N;
	long long int n, l;
	for (int m = 1; m < N; m++) {
		n = W * m;
		l = ceil((double)N / m)*H;
		if (n >= l) {
			max_n = n;
		}
		else {
			max_n = l;
		}
		if (max_n < min_n) {
			min_n = max_n;
		}
	}
	std::cout << min_n << std::endl;
}
void task_tiles_smart() {
	long long int W, H, N;
	std::cin >> W >> H >> N;
	long long int m, l = 0, r = ((H >= W) ? H : W) * N;
	while (r - l > 1) {
		m = (l + r) / 2;
		if ((m / H)*(m / W) >= N) {
			r = m;
		}
		else {
			l = m;
		}
	}
	std::cout << r << std::endl;
}

void task_extract_pair_sum() {
	int N, M;
	std::cin >> N >> M;
	std::vector < int > mas(N);
	for (int i = 0; i < N; i++) {
		std::cin >> mas[i];
	}
	inssort(mas);
	int t, index;
	bool by_break;
	for (int i = 0; i < M; i++) {
		std::cin >> t;
		by_break = false;
		for (int j = 0; j < N; j++) {
			index = binsearch(mas, j, t - mas[j]);
			if (index != -1) {
				if (index != j) {
					std::cout << mas[j] << " " << mas[index] << std::endl;
					by_break = true;
					break;
				}
			}
		}
		if (!by_break) {
			std::cout << "Not found" << std::endl;
		}
	}
}

bool se_book_checker(std::vector < int > &arr, int K, int N, int M) {
	int S = 0;
	int i;
	int k = 0;
	/*unsigned int i = 0;
	for (int k = 0; k < K; k++) {
		for (S = 0; S <= M; i++) {
			if (i == N) {
				return true;
			}
			S += arr[i];
		}
		i--;
		if (i == N) {
			return true;
		}
	}
	return false;
	*/
	for (i = 0; i < N; i++) {
		S += arr[i];
		if (S > M) {
			S = arr[i];
			k++;
			if (k > K) {
				return false;
			}
		}
	}
	if (k + 1 > K) {
		return false;
	}
	return true;
}
void task_se_book_naive() {
	int K, N;
	std::cin >> K >> N;
	std::vector < int > mas(N);
	int t, max_n = 0;
	for (unsigned int i = 0; i < mas.size(); i++) {
		std::cin >> t;
		if (t >= max_n) {
			max_n = t;
		}
		mas[i] = t;
	}
	int S;
	unsigned int i;
	for (int m = max_n; m < 10000; m++) {
		if (se_book_checker(mas, K, N, m)) {
			std::cout << m;
			return;
		}
	}
}
void task_se_book_smart() {
	int K, N;
	//std::cin >> K >> N;
	scanf("%d %d", &K, &N);
	std::vector < int > mas(N);
	int t = 0, max_n = 0;
	for (unsigned int i = 0; i < mas.size(); i++) {
		//std::cin >> t;
		scanf("%d", &t);
		if (t >= max_n) {
			max_n = t;
		}
		mas[i] = t;
	}
	int r = 10000, l = max_n - 1;
	int m;
	while (r - l > 1) {
		m = (r + l) / 2;
		if (se_book_checker(mas, K, N, m)) {
			r = m;
		}
		else {
			l = m;
		}
	}
	std::cout << r;
}

void task_brackets_1() {
	int k = 0;
	std::string s;
	std::cin >> s;
	for (unsigned int i = 0; i < s.size(); i++) {
		switch (s[i]) {
			case '(':
				{
					k++;
					break;
				}
			case ')':
				{
					if (k == 0) {
						std::cout << "NO";
						return;
					}
					k--;
					break;
				}
			default:
				{
					std::cout << ((k == 0) ? "YES" : "NO");
					return;
				}
		}
	}
	std::cout << ((k == 0) ? "YES" : "NO");
}
void task_brackets_2() {
	std::string str;
	std::cin >> str;
	stack s;
	for (unsigned int i = 0; i < str.size(); i++) {
		switch (str[i]) {
			case ')':
				{
					if (s.size() == 0) {
						std::cout << "NO";
						return;
					}
					else {
						if (s.top() == '(') {
							s.pop();
						}
						else {
							std::cout << "NO";
							return;
						}
					}
					break;
				}
			case ']':
				{
					if (s.size() == 0) {
						std::cout << "NO";
						return;
					}
					else {
						if (s.top() == '[') {
							s.pop();
						}
						else {
							std::cout << "NO";
							return;
						}
					}
					break;
				}
			case '}':
				{
					if (s.size() == 0) {
						std::cout << "NO";
						return;
					}
					else {
						if (s.top() == '{') {
							s.pop();
						}
						else {
							std::cout << "NO";
							return;
						}
					}
					break;
				}
			case '>':
				{
					if (s.size() == 0) {
						std::cout << "NO";
						return;
					}
					else {
						if (s.top() == '<') {
							s.pop();
						}
						else {
							std::cout << "NO";
							return;
						}
					}
					break;
				}
			default:
				{
					s.push(str[i]);
				}
		}

	}
	if (s.empty()) {
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
}


void task_vega() {
	std::deque < int > d1, d2;
	int N;
	std::cin >> N;
	char c;
	int n;
	//int k;
	for (int i = 0; i < N; i++) {
		std::cin >> c;
		switch (c) {
			case '+': {
				std::cin >> n;
				/*if (d1.empty()) {
					if (d2.empty()) {
						d1.push_back(n);
					}
					else {
						if (
					}
				}*/
				if (d2.size() % 2 == d1.size() % 2) {
					//не перебрасываем
					d2.push_back(n);
				}
				else {
					//перебрасываем
					d1.push_back(d2.front());
					d2.pop_front();
					d2.push_back(n);
				}
				break;
			}
			case '*': {
				std::cin >> n;
				if (d2.size() % 2 == 0) {
					//не перебрасываем
					
				}
				else {
					//перебрасываем
					
				}
				d1.push_back(n);
				break;
			}
			case '-': {
				std::cout << d1.front() << "\n";
				d1.pop_front();
				break;
			}
		}
	}
}

void task_stack() {
	stack s;
	std::string str;
	bool ending = false;
	int n;
	while (!ending) {
		std::cin >> str;
		if (str == "push") {
			std::cin >> n;
			s.push(n);
			std::cout << "ok\n";
		}
		if (str == "pop") {
			if (s.empty()) {
				std::cout << "error\n";
			}
			else {
				s.pop();
			}
		}
		if (str == "back") {
			if (s.empty()) {
				std::cout << "error\n";
			}
			else {
				std::cout << s.top() << "\n";
			}
		}
		if (str == "size") {
			std::cout << s.size() << "\n";
		}
		if (str == "clear") {
			s.clear();
			std::cout << "ok\n";
		}
		if (str == "exit") {
			std::cout << "bye";
			ending = true;
		}
	}
}

int main() {
	task_stack();
	//int x = 1;
	//++x = 5;
	//(x = 5) = 1;
	return 0;
}
	
	