#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void MySum();

int main()
{
	MySum();
}

void MySum()
{
	int arr[6];
	int sum = 0;

	printf("���ڸ� �Է��ϼ���. : ");
	scanf("%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &arr[5]);

	for (int i = 0; i < 6; i++)
	{
		sum += arr[i];
	}

	printf("\n��� ���� ���� %d�Դϴ�.\n", sum);
}