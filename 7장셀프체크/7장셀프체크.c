#include <stdio.h>

void square(int* x);

int main() {
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (int i = 0; i < 10; i++) {
		square(&arr[i]);
		if (i == 9) printf("%d", arr[i]);
		else printf("%d, ", arr[i]);
	}

	return 0;
}

void square(int* x) {
	if (*x % 2 == 0) *x *= *x;
}