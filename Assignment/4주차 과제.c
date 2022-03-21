#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

void GetNumbers(int* arr);
void BubbleSort(int* arr);

int main()
{
	int numbers[6] = { 0, };

	GetNumbers(numbers);

	BubbleSort(numbers);

	printf("\n%d %d %d %d %d %d", numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]);

	return 0;
}

void GetNumbers(int* arr)
{
	printf("숫자 6개를 입력하세요. : ");
	scanf("%d %d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4], &arr[5]);
}

void BubbleSort(int* arr)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == j)
				continue;

			if (arr[i] <= arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}