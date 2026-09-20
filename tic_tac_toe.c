#include <stdio.h>

#define BOARD_SIZE 3

static void initialize_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row;
    int column;
    char position = '1';

    for (row = 0; row < BOARD_SIZE; row++)
    {
        for (column = 0; column < BOARD_SIZE; column++)
        {
            board[row][column] = position++;
        }
    }
}

static void display_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row;

    printf("\n");
    for (row = 0; row < BOARD_SIZE; row++)
    {
        printf(" %c | %c | %c \n",
               board[row][0], board[row][1], board[row][2]);
        if (row < BOARD_SIZE - 1)
        {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

static int has_winner(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    int index;

    for (index = 0; index < BOARD_SIZE; index++)
    {
        if ((board[index][0] == player &&
             board[index][1] == player &&
             board[index][2] == player) ||
            (board[0][index] == player &&
             board[1][index] == player &&
             board[2][index] == player))
        {
            return 1;
        }
    }

    return (board[0][0] == player &&
            board[1][1] == player &&
            board[2][2] == player) ||
           (board[0][2] == player &&
            board[1][1] == player &&
            board[2][0] == player);
}

static int board_is_full(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row;
    int column;

    for (row = 0; row < BOARD_SIZE; row++)
    {
        for (column = 0; column < BOARD_SIZE; column++)
        {
            if (board[row][column] >= '1' && board[row][column] <= '9')
            {
                return 0;
            }
        }
    }

    return 1;
}

static int read_move(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    char input[100];
    int position;
    int row;
    int column;

    printf("Player %c, choose a position (1-9) or q to quit: ", player);
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return -1;
    }

    if (input[0] == 'q' || input[0] == 'Q')
    {
        return -2;
    }

    if (sscanf(input, "%d", &position) != 1 || position < 1 || position > 9)
    {
        printf("Please enter a number from 1 to 9.\n");
        return 0;
    }

    row = (position - 1) / BOARD_SIZE;
    column = (position - 1) % BOARD_SIZE;
    if (board[row][column] < '1' || board[row][column] > '9')
    {
        printf("That position is already taken.\n");
        return 0;
    }

    return position;
}

int main(void)
{
    char board[BOARD_SIZE][BOARD_SIZE];
    char player = 'X';
    int position;

    initialize_board(board);
    printf("Tic-Tac-Toe\n");
    printf("===========\n");
    printf("Enter the number of the position where you want to place your mark.\n");

    while (1)
    {
        display_board(board);
        position = read_move(board, player);
        if (position == -1)
        {
            printf("\nInput ended. Game over.\n");
            return 1;
        }
        if (position == -2)
        {
            printf("\nThanks for playing!\n");
            return 0;
        }
        if (position == 0)
        {
            continue;
        }

        board[(position - 1) / BOARD_SIZE][(position - 1) % BOARD_SIZE] = player;
        if (has_winner(board, player))
        {
            display_board(board);
            printf("Player %c wins!\n", player);
            return 0;
        }
        if (board_is_full(board))
        {
            display_board(board);
            printf("It's a draw!\n");
            return 0;
        }

        player = player == 'X' ? 'O' : 'X';
    }
}
