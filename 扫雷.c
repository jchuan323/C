#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10  // ����
#define COLS 10  // ����
#define MINES 10 // ��������

char board[ROWS][COLS];  // ��Ϸ��
char displayBoard[ROWS][COLS];  // �û��ɼ�����Ϸ��

// ��ʼ������
void initBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '0';  // ��ʼ��Ϊ0����ʾû�е���
            displayBoard[i][j] = '*';  // �û��ɼ��Ĳ��ֳ�ʼΪ*��ʾδ����
        }
    }
}

// ���õ���
void placeMines() {
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (board[row][col] == '0') {  // ȷ����λ��û�е���
            board[row][col] = 'M';  // 'M'��ʾ����
            minesPlaced++;
        }
    }
}

// �����ڽ��ĵ�����
void calculateNumbers() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 'M') continue;  // ����ǵ��ף�����

            int mineCount = 0;
            // �����Χ��8������
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int newRow = i + x;
                    int newCol = j + y;
                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS && board[newRow][newCol] == 'M') {
                        mineCount++;
                    }
                }
            }
            board[i][j] = mineCount + '0';  // ���ַ���ʾ����
        }
    }
}

// ��ӡ����
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

// �û�����
int userMove() {
    int row, col;
    printf("�����к���(���� 3 4): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("������Ч�����������롣\n");
        return 0;
    }

    if (board[row][col] == 'M') {
        printf("��ȵ��˵��ף���Ϸ������\n");
        return -1;
    } else {
        displayBoard[row][col] = board[row][col];  // �����ø���
        if (board[row][col] == '0') {
            // ����������ǿհ����򣬼��������ڵĿո�
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

// ����Ƿ�ʤ��
int checkWin() {
    int coveredCells = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (displayBoard[i][j] == '*') {
                coveredCells++;
            }
        }
    }
    return coveredCells == MINES;  // ���ʣ�µ�δ���������������ڵ���������һ�ʤ
}

int main() {
    initBoard();
    placeMines();
    calculateNumbers();

    printf("��ӭ����ɨ����Ϸ��\n");

    int result = 1;
    while (result > 0) {
        printBoard(displayBoard);
        result = userMove();
        if (checkWin()) {
            printf("��ϲ�㣬ɨ�׳ɹ���\n");
            break;
        }
    }

    printf("��Ϸ���������յ������ǣ�\n");
    printBoard(board);

    return 0;
}

