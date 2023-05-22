#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//�������� ����
int level;
int arrayFish[6];
int* cursor;

// �Լ� ����
void initData();
void printfFishes();
void decreaseWater(long elapsedTime);
int checkFishAlive();

int main(void)
{
	long startTime = 0; // ���� ���� �ð�
	int num; // ���� �� ���� ��ȣ
	long totalElapsedTime = 0; // �� ��� �ð�
	long prevElapsedTime = 0; // ������ ���� �� �ð�(���� �� �ð� ����)

	initData(); // ���� �ʱ�ȭ �Լ� ȣ��

	startTime = clock(); // ���α׷� ���� ���� ������� �帥 �ð� ����
	cursor = &arrayFish[0]; // ����Ʈ ������ ���� �迭�� ���� �ּ� �ֱ�

	// ���׿� �� �ֱ�
	while (1)
	{
		// ���� �� ���� ��� �Լ� ȣ��
		printfFishes();

		// �Է� �ȳ� ����
		printf("�� ��° ���׿� ���� �ٱ��? : ");
		int input_check = scanf_s("%d", &num);
		if (!input_check) {
			printf("[1 ~ 6 ������ ������ �Է����ּ���.]\n\n");
			char flesh[256];
			scanf_s("%s", flesh, (unsigned)sizeof(flesh));
			continue;
		}
		else if (num < 1 || num > 6) {
			printf("[1 ~ 6 ������ ������ �Է����ּ���.]\n\n");
			continue;
		}
		// �� ��� �ð�
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;

		printf("�� ��� �ð� : %ld\n", totalElapsedTime);

		// ���� �� �ð� ����
		prevElapsedTime = totalElapsedTime - prevElapsedTime;

		printf("�ֱ� ��� �ð� : %ld\n", prevElapsedTime);

		decreaseWater(prevElapsedTime);

		// ����ڰ� �Է��� ��ȣ�� ���׿� �� �ֱ�
		// ���� 1. ������ �� ���̰� 0 ���ϸ� ���� ���� ����
		if (cursor[num - 1] == 0) {
			printf("%d��° ������ ������ �̹� �׾����Ƿ� ���� ���� �ʽ��ϴ�.\n\n", num);
		}
		// ���� 2. ������ �� ���̰� 0 �ʰ��ϸ� 100�� ���� �ʴ��� Ȯ���ϰ� ���� ��
		else if (cursor[num - 1] <= 100) {
			printf("%d��° ���׿� ���� �ݴϴ�.\n", num);
			cursor[num - 1] += 1;
		}
		
		// ������ Ȯ��(�������� 20�ʸ��� �� ���� ����)
		if (totalElapsedTime / 20 > level - 1) {
			level++;
			printf("\n-----������ %d�� �ö����ϴ�.-----\n\n", level);
			if (level == 5) {
				printf("�ִ� ������ ������ ������ �����մϴ�.\n");
				exit(0);
			}
		}
		
		// ��� ����Ⱑ �׾����� Ȯ��
		if (checkFishAlive() == 0) {
			printf("��� ����Ⱑ �׾� ������ �����մϴ�.\n");
			exit(0);
		}
		else {
			printf("����Ⱑ ���� ����־ ������ �����մϴ�.\n");
		}

		prevElapsedTime = totalElapsedTime;
	}
	return 0;
}

// ���� �ʱ�ȭ �Լ�
void initData() {
	level = 1;
	for (int i = 0; i < 6; i++) arrayFish[i] = 100;
}

// ���� �� ���� ��� �Լ�
void printfFishes() {
	printf("%3d�� %3d�� %3d�� %3d�� %3d�� %3d��\n", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++) {
		printf("  %3d ",arrayFish[i]);
	}
	printf("\n\n");
}

// ������ ���� ����(����)��Ű�� �Լ�
void decreaseWater(long elapsedTime) {
	for (int i = 0; i < 6; i++) {
		arrayFish[i] -= (level * 3 * (int)elapsedTime);
		if (arrayFish[i] < 0) arrayFish[i] = 0;
	}
}

// ��� ����Ⱑ �׾����� Ȯ���ϴ� �Լ�
int checkFishAlive() {
	for (int i = 0; i < 6; i++) return (arrayFish[i] > 0) ? 1 : 0;
}