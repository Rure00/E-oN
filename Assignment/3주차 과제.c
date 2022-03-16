#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void MySum(int* arr);

int main()
{
	int arr[6];

	MySum(arr);
}

void MySum(int* arr)
{
	int sum = 0;

	printf("숫자를 입력하세요. : ");
	scanf("%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &arr[5]);

	for (int i = 0; i < 6; i++)
	{
		sum += arr[i];
	}

	printf("\n모든 수의 합은 %d입니다.\n", sum);
}