#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(int * x, int * y) {
	return (*y - *x);
}

int compareStr(char* x, char* y) {
	return strncmp(x, y, 256);
}

int main() {
	int arr[10] = { 11, 31, 4, 8, 20, 1, 9, 40, 60, 90 };

	for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
	printf("\n\n");

	qsort(arr, 10, sizeof(int), compare);

	for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
	printf("\n\n");


	//char words[10][256] = { "hello", "play", "sound", "melon", "kakao", "line", "friends", "party", "Monday", "Sunday" };

	char words[10][256] = { "a", "b", "z", "x", "y", "m", "l", "p", "s", "T" };

	for (int i = 0; i < 10; i++) printf("%s, ", words[i]);
	printf("\n\n");

	qsort(words, 10, 256, compareStr);

	for (int i = 0; i < 10; i++) printf("%s, ", words[i]);
	printf("\n\n");



	return 0;
}

