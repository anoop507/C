#include <stdio.h>
#define SIZE 9

void print_board(int board[][SIZE]) {
    for (int i=0;i<SIZE;i++) {
        for (int j=0;j<SIZE;j++) {
            if (board[i][j]==0) printf("* ");
            else printf("%d ",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void find_emptyCell(int board[][SIZE],int pos[2]) {
    for (int i=pos[0]+1;i<SIZE;i++) { // not sure whether pos[0]+1 and pos[1]+1 works correctly
        for (int j=pos[1]+1;j<SIZE;j++) {
            if (board[i][j] == 0) {
                pos[0] = i;
                pos[1] = j;
                return;
            }
        }
    }
}

int valid_square(int board[][SIZE], int val,int row,int col) {
    int rowStart = (row/3)*3, colStart = (col/3)*3;
    for (int i=rowStart;i<rowStart+3;i++) {
        for (int j=colStart;j<colStart+3;j++) {
            if (board[i][j] == val) return 0;
        }
    }
    return 1;
}

int valid_row(int board[][SIZE],int val,int row) {
    for (int i=0;i<SIZE;i++) {
        if (board[row][i] == val) return 0;
    }
    return 1;
}

int valid_col(int board[][SIZE],int val,int col) {
    for (int i=0;i<SIZE;i++) {
        if (board[i][col] == val) return 0;
    }
    return 1;
}

int valid(int board[][SIZE],int val,int row,int col) {
    return valid_row(board,val,row) && valid_col(board,val,col) && valid_square(board,val,row,col);
}

int solve(int board[][SIZE]) {
    int empty_pos[2] = {-1,-1};
    find_emptyCell(board,empty_pos);
    if (empty_pos[0]==-1 && empty_pos[1]==-1) return 1;

    for (int guess=1;guess<10;guess++) {
        if (valid(board,guess,empty_pos[0],empty_pos[1])) {
            board[empty_pos[0]][empty_pos[1]] = guess;
            if (solve(board)) return 1;
            board[empty_pos[0]][empty_pos[1]] = 0;
        }
    }
    return 0;
}

int main() {

    int puzzle[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 9, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 2, 0, 0, 0, 8},
    {0, 6, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 8, 0, 0, 4, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 0},
    {7, 0, 0, 6, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 5, 0, 0, 0, 0, 0, 0}
    };

    printf("The provided puzzle:\n");
    print_board(puzzle);
    if (solve(puzzle)) {
        printf("Solved puzzle:\n");
        print_board(puzzle);
    }
    else printf("The provided puzzle is unsolvable.");
}

// 9 6 2 1 7 8 3 5 4 
// 8 1 5 9 4 3 7 6 2 
// 4 3 7 6 5 2 8 1 9 
// 6 5 8 2 3 1 4 9 7 
// 7 4 3 8 9 5 1 2 6 
// 2 9 1 4 6 7 5 8 3 
// 5 8 6 7 2 4 9 3 1 
// 3 2 4 5 1 9 6 7 8 
// 1 7 9 3 8 6 2 4 5    