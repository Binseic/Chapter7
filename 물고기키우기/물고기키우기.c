#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//전역변수 선언
int level;
int arrayFish[6];
int* cursor;

// 함수 선언
void initData();
void printfFishes();
void decreaseWater(long elapsedTime);
int checkFishAlive();

int main(void)
{
	long startTime = 0; // 게임 시작 시간
	int num; // 물을 줄 어항 번호
	long totalElapsedTime = 0; // 총 경과 시간
	long prevElapsedTime = 0; // 직전에 물을 준 시간(물을 준 시간 간격)

	initData(); // 게임 초기화 함수 호출

	startTime = clock(); // 프로그램 실행 이후 현재까지 흐른 시간 저장
	cursor = &arrayFish[0]; // 포인트 변수에 어항 배열의 시작 주소 넣기

	// 어항에 물 주기
	while (1)
	{
		// 어항 물 높이 출력 함수 호출
		printfFishes();

		// 입력 안내 문구
		printf("몇 번째 어항에 물을 줄까요? : ");
		int input_check = scanf_s("%d", &num);
		if (!input_check) {
			printf("[1 ~ 6 사이의 정수만 입력해주세요.]\n\n");
			char flesh[256];
			scanf_s("%s", flesh, (unsigned)sizeof(flesh));
			continue;
		}
		else if (num < 1 || num > 6) {
			printf("[1 ~ 6 사이의 정수만 입력해주세요.]\n\n");
			continue;
		}
		// 총 경과 시간
		totalElapsedTime = (clock() - startTime) / CLOCKS_PER_SEC;

		printf("총 경과 시간 : %ld\n", totalElapsedTime);

		// 물을 준 시간 간격
		prevElapsedTime = totalElapsedTime - prevElapsedTime;

		printf("최근 경과 시간 : %ld\n", prevElapsedTime);

		decreaseWater(prevElapsedTime);

		// 사용자가 입력한 번호의 어항에 물 주기
		// 조건 1. 어항의 물 높이가 0 이하면 물을 주지 않음
		if (cursor[num - 1] == 0) {
			printf("%d번째 어항의 물고기는 이미 죽었으므로 물을 주지 않습니다.\n\n", num);
		}
		// 조건 2. 어항의 물 높이가 0 초과하면 100을 넘지 않는지 확인하고 물을 줌
		else if (cursor[num - 1] <= 100) {
			printf("%d번째 어항에 물을 줍니다.\n", num);
			cursor[num - 1] += 1;
		}
		
		// 레벨업 확인(레벨업은 20초마다 한 번씩 수행)
		if (totalElapsedTime / 20 > level - 1) {
			level++;
			printf("\n-----레벨이 %d로 올랐습니다.-----\n\n", level);
			if (level == 5) {
				printf("최대 레벨에 도달해 게임을 종료합니다.\n");
				exit(0);
			}
		}
		
		// 모든 물고기가 죽었는지 확인
		if (checkFishAlive() == 0) {
			printf("모든 물고기가 죽어 게임을 종료합니다.\n");
			exit(0);
		}
		else {
			printf("물고기가 아직 살아있어서 게임을 지속합니다.\n");
		}

		prevElapsedTime = totalElapsedTime;
	}
	return 0;
}

// 게임 초기화 함수
void initData() {
	level = 1;
	for (int i = 0; i < 6; i++) arrayFish[i] = 100;
}

// 어항 물 높이 출력 함수
void printfFishes() {
	printf("%3d번 %3d번 %3d번 %3d번 %3d번 %3d번\n", 1, 2, 3, 4, 5, 6);
	for (int i = 0; i < 6; i++) {
		printf("  %3d ",arrayFish[i]);
	}
	printf("\n\n");
}

// 어항의 물을 증발(감소)시키는 함수
void decreaseWater(long elapsedTime) {
	for (int i = 0; i < 6; i++) {
		arrayFish[i] -= (level * 3 * (int)elapsedTime);
		if (arrayFish[i] < 0) arrayFish[i] = 0;
	}
}

// 모든 물고기가 죽었는지 확인하는 함수
int checkFishAlive() {
	for (int i = 0; i < 6; i++) return (arrayFish[i] > 0) ? 1 : 0;
}