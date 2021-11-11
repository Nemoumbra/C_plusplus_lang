//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int num_cmp(const void * p1, const void * p2) {
	const char * s1 = (const char *) (p1);
	const char * s2 = (const char *) (p2);
	int i1 = 0, i2 = 0;
	while (1) {
		while (s1[i1] != '\0' && s2[i2] != '\0') {
			if (s1[i1] < s2[i2]) {
				return -1;
			}
			if (s1[i1] > s2[i2]) {
				return 1;
			}
			++i1; ++i2;
		}
		if (s1[i1] == s2[i2]) { // == '\n'
			return 0;
		}
		((s1[i1] == '\0') ? i1 : i2) = 0;
	}
}
void task_number() {
	char arr[101][101];
	FILE * infile = fopen("number.in", "r");
	int k = 0;
	//int code;
	while (/*(code = */fscanf(infile, "%s", arr[k])/*)*/ == 1) {
		k++;
	}

	qsort(arr, k, sizeof(arr[0]), num_cmp);

	FILE * outfile = fopen("number.out", "w");
	for (int i = k - 1; i >= 0; i--) {
		//std::cout << arr[i];
		fprintf(outfile, "%s", arr[i]);
	}
}
int main() {
	task_number();
	return 0;
}