#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int* GetNumbers(int* plength);
int** GetCommands(int* clength, int nlength);
int* Solution(int* arr, int** com, int clength);
void BubbleSort(int* arr, int length);
void PrintArr(int* arr, int length);

int main()
{
	int nLength = 0;
	int cLength = 0;
	
	int* numbers = GetNumbers(&nLength);
	int** commands = GetCommands(&cLength, nLength);


	int* result = Solution(numbers, commands, cLength);

	PrintArr(result, cLength);

	return 0;
}

int* GetNumbers(int* plength)
{
	int length = 0;
	int* arr;

	while (1)
	{
		printf("\n������ ������ �Է��ϼ���. : ");
		scanf("%d", &length);

		if (length < 1 || length > 100)
		{
			printf("\n���Ҵ� 1���� 100 ���̿��� �մϴ�.\n");
		}
		else
		{
			*plength = length;
			break;
		}
	}
	

	arr = (int*)malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++)
	{
		while (1)
		{
			int givedNum = 0;
			printf("%d��° ���Ҹ� �Է��ϼ���. : ", i+1);
			scanf("%d", &givedNum);

			if (givedNum < 1 || givedNum > 100)
			{
				printf("\n���Ҵ� 1���� 100 ���̿��� �մϴ�.\n");
			}
			else
			{
				arr[i] = givedNum;
				break;
			}
		}
	}

	//PrintArr(arr, length);

	return arr;
}

int** GetCommands(int* clength, int nlength)
{
	int length;
	while (1)
	{
		printf("\nCommands�� ���̸� �Է��ϼ���. : ");
		scanf("%d", &length);

		if (length < 1 || length > 100)
		{
			printf("\n1���� 50 ���̿��� �մϴ�.\n");
		}
		else
		{
			*clength = length;
			break;
		}
	}

	int** arr= (int**)malloc(sizeof(int*) * length);
	for (int i = 0; i < length; i++) {
		arr[i] = (int*)malloc(sizeof(int) * 3);
	}

	for (int index = 0; index < length; index++)
	{
		printf("\n%d��° �迭�Դϴ�.", index + 1);

		int i = 0, j = 0;
		while (1)
		{
			printf("\ni�� �Է��ϼ���.");
			scanf("%d", &i);
			

			printf("j�� �Է��ϼ���.");
			scanf("%d", &j);
			

			if (i > j)
			{
				printf("i�� j���� Ů�ϴ�. �ٽ� �Է����ּ���.");
			}
			else if (i > nlength || j > nlength)
			{
				printf("�迭�� ����ϴ�. �ٽ� �Է����ּ���.");
			}
			else
			{
				i--;
				j--;

				arr[index][0] = i;
				arr[index][1] = j;
				break;
			}
		}
		
		int k = 0;
		while (1)
		{
			printf("k�� �Է����ּ���.");
			scanf("%d", &k);

			if (k > j - i + 1)
			{
				printf("�迭�� ����ϴ�. �ٽ� �Է����ּ���.");
			}
			else
			{
				k--;
				arr[index][2] = k;
				break;
			}
		}
	}

	return arr;
}

int* Solution(int* arr, int** com, int clength)
{
	//arr : number, com : commands
	int* result = (int*)malloc(sizeof(int) * clength);

	for (int i = 0; i < clength; i++)
	{
		int command_i = com[i][0];
		int command_j = com[i][1];
		int arrLength = command_j - command_i + 1;

		int* tempArr = (int*)malloc(sizeof(int) * arrLength);

		for (int j = 0; j < arrLength; j++)
		{
			tempArr[j] = arr[command_i + j];
		}

		BubbleSort(tempArr, arrLength);

		int command_k = com[i][2];
		result[i] = tempArr[command_k];

		free(tempArr);
	}


	return result;
}

void BubbleSort(int* arr, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
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

void PrintArr(int* arr, int length)
{
	printf("\n\n");
	for (int i = 0; i < length; i++)
	{
		printf("%d	", arr[i]);
	}
}