#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10  // 行数
#define COLS 10  // 列数
#define MINES 10 // 地雷数量

char board[ROWS][COLS];  // 游戏板
char displayBoard[ROWS][COLS];  // 用户可见的游戏板

// 初始化棋盘
void initBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '0';  // 初始化为0，表示没有地雷
            displayBoard[i][j] = '*';  // 用户可见的部分初始为*表示未翻开
        }
    }
}

// 布置地雷
void placeMines() {
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col] == '0') {  // 确保该位置没有地雷
            board[row][col] = 'M';  // 'M'表示地雷
            minesPlaced++;
        }
    }
}

// 计算邻近的地雷数
void calculateNumbers() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 'M') continue;  // 如果是地雷，跳过

            int mineCount = 0;
            // 检查周围的8个格子
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int newRow = i + x;
                    int newCol = j + y;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && board[newRow][newCol] == 'M') {
                        mineCount++;
                    }
                }
            }
            board[i][j] = mineCount + '0';  // 用字符表示数字
        }
    }
}

// 打印棋盘
void printBoard(char board[ROWS][COLS]) {
    printf("  ");
    for (int i = 0; i < COLS; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%d ", i);
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 用户输入
int userMove() {
    int row, col;
    printf("输入行和列(例如 3 4): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("输入无效，请重新输入。\n");
        return 0;
    }

    if (board[row][col] == 'M') {
        printf("你踩到了地雷，游戏结束！\n");
        return -1;
    } else {
        displayBoard[row][col] = board[row][col];  // 翻开该格子
        if (board[row][col] == '0') {
            // 如果翻开的是空白区域，继续打开相邻的空格
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int newRow = row + x;
                    int newCol = col + y;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && displayBoard[newRow][newCol] == '*') {
                        displayBoard[newRow][newCol] = board[newRow][newCol];
                    }
                }
            }
        }
        return 1;
    }
}

// 检查是否胜利
int checkWin() {
    int coveredCells = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (displayBoard[i][j] == '*') {
                coveredCells++;
            }
        }
    }
    return coveredCells == MINES;  // 如果剩下的未翻开格子数量等于地雷数，玩家获胜
}

int main() {
    initBoard();
    placeMines();
    calculateNumbers();

    printf("欢迎来到扫雷游戏！\n");

    int result = 1;
    while (result > 0) {
        printBoard(displayBoard);
        result = userMove();
        if (checkWin()) {
            printf("恭喜你，扫雷成功！\n");
            break;
        }
    }

    printf("游戏结束，最终的棋盘是：\n");
    printBoard(board);

    return 0;
}

