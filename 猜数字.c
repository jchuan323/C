#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int targetNumber, guess, attempts = 0;

    // �������������
    srand(time(0));

    // ���� 1 �� 100 ֮��������
    targetNumber = rand() % 100 + 1;

    printf("��ӭ������������Ϸ�����Ѿ������һ��1��100֮������֣������²¿��ɣ�\n");

    // ��Ϸ��ѭ��
    do {
        printf("��������Ĳ²�: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > targetNumber) {
            printf("̫���ˣ�\n");
        } else if (guess < targetNumber) {
            printf("̫С�ˣ�\n");
        } else {
            printf("��ϲ�㣬�¶��ˣ����ܹ����� %d �Ρ�\n", attempts);
        }
    } while (guess != targetNumber);

    return 0;
}

