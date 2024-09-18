#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int targetNumber, guess, attempts = 0;

    // 生成随机数种子
    srand(time(0));

    // 生成 1 到 100 之间的随机数
    targetNumber = rand() % 100 + 1;

    printf("欢迎来到猜数字游戏！我已经想好了一个1到100之间的数字，快来猜猜看吧！\n");

    // 游戏主循环
    do {
        printf("请输入你的猜测: ");
        scanf("%d", &guess);
        attempts++;

        if (guess > targetNumber) {
            printf("太大了！\n");
        } else if (guess < targetNumber) {
            printf("太小了！\n");
        } else {
            printf("恭喜你，猜对了！你总共猜了 %d 次。\n", attempts);
        }
    } while (guess != targetNumber);

    return 0;
}

