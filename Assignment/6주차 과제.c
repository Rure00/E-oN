#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int GetPiecesNum();
int GetResult(int num);
int Combination(int head, int tail);


int main()
{
    int NumOfPieces = GetPiecesNum();
    int result = GetResult(NumOfPieces);

    printf("\n피자를 나누는 방법은 총 %d가지 입니다!! 맛있게 드세요!", result);

    return 0;
}

int GetPiecesNum()
{
    int pieceNum = 0;

    printf("피자가 몇 조각인가요?? : ");
    scanf("%d", &pieceNum);

    return pieceNum;
}

int GetResult(int pieceNum)
{
    int sum = 0;
    int NumOfTwo = pieceNum / 2;

    for (int i = 0; i <= NumOfTwo; i++)
    {
        int head = pieceNum - i;
        sum += Combination(head, i);
    }

    return sum;
}

int Combination(int head, int tail)
{
    int result = 0;

    int Bunmo = 1;
    int Bunja = 1;

    for (int i = 0; i < tail; i++)
    {
        Bunja *= (head - i);
        Bunmo *= (tail - i);
    }
    
    result = Bunja / Bunmo;
    //printf("\n%d C %d = %d",head, tail, result);

    return result;
}