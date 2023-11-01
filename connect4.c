#include <stdio.h>
#include <stdbool.h>

/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

bool has_won(board_t board, player_t player) {
// Check horizontal win
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i][j] == player &&
                board[i][j + 1] == player &&
                board[i][j + 2] == player &&
                board[i][j + 3] == player) {
                return true;
            }
        }
    }

// Check vertical win
    for (int j = 0; j < 5; j++) {
        int i = 0;
        if (board[i][j] == player &&
            board[i + 1][j] == player &&
            board[i + 2][j] == player &&
            board[i + 3][j] == player) {
            return true;
        }
    }

// Check diagonal win (top-left to bottom-right)
    for (int j = 0; j < 2; j++) {
        int i = 0;
        if (board[i][j] == player &&
            board[i + 1][j + 1] == player &&
            board[i + 2][j + 2] == player &&
            board[i + 3][j + 3] == player) {
            return true;
        }
    }

// Check diagonal win (top-right to bottom-left)
    for (int j = 4; j > 2; j--) {
        int i = 0;
        if (board[i][j] == player &&
            board[i + 1][j - 1] == player &&
            board[i + 2][j - 2] == player &&
            board[i + 3][j - 3] == player) {
            return true;
        }
    }

    return false; // No win
}

bool is_full(board_t board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

typedef struct {
    int col;
    int score;
} move_t;

int board_score(board_t board, player_t player) {
    int score = 0;
    int maxConsecutive = 0;
    int maxBlocking = 0; // Track potential opponent wins to block them

    // Check the row
    for (int i = 0; i < 4; i++) {
        int consecutive = 0;
        int blocking = 0;
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == player) {
                consecutive++;
            } else if (board[i][j] == EMPTY) {
                blocking++;
            } else {
                blocking = 0;
            }

            if (consecutive == 3) {
                score += 10; // Encourage forming a connect4
            } else if (consecutive == 2 && blocking == 1) {
                score += 3; // Encourage forming a connect4
            } else if (blocking == 3) {
                score += 5; // Encourage blocking opponent's connect4
            } else if (blocking == 2) {
                score += 2; // Encourage blocking opponent's potential connect4
            }

            if (consecutive > maxConsecutive) {
                maxConsecutive = consecutive;
            }
            if (blocking > maxBlocking) {
                maxBlocking = blocking;
            }
        }
    }

    // Check the column
    for (int j = 0; j < 5; j++) {
        int consecutive = 0;
        int blocking = 0;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] == player) {
                consecutive++;
            } else if (board[i][j] == EMPTY) {
                blocking++;
            } else {
                blocking = 0;
            }

            if (consecutive == 3) {
                score += 10; // Encourage forming a connect 4
            } else if (consecutive == 2 && blocking == 1) {
                score += 3; // Encourage forming a connect 4
            } else if (blocking == 3) {
                score += 5; // Encourage blocking opponent's connect 4
            } else if (blocking == 2) {
                score += 2; // Encourage blocking opponent's potential connect 4
            }

            if (consecutive > maxConsecutive) {
                maxConsecutive = consecutive;
            }
            if (blocking > maxBlocking) {
                maxBlocking = blocking;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int j = 0; j < 2; j++) {
        int i = 0;
        int consecutive = 0;
        int blocking = 0;
        for (int k = 0; k < 4; k++) {
            if (board[i + k][j + k] == player) {
                consecutive++;
            } else if (board[i + k][j + k] == EMPTY) {
                blocking++;
            } else {
                blocking = 0;
            }

            if (consecutive == 3) {
                score += 10; // Encourage forming a connect 4
            } else if (consecutive == 2 && blocking == 1) {
                score += 3; // Encourage forming a connect 4
            } else if (blocking == 3) {
                score += 5; // Encourage blocking opponent's connect 4
            } else if (blocking == 2) {
                score += 2; // Encourage blocking opponent's potential connect 4
            }

            if (consecutive > maxConsecutive) {
                maxConsecutive = consecutive;
            }
            if (blocking > maxBlocking) {
                maxBlocking = blocking;
            }
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int j = 4; j > 2; j--) {
        int i = 0;
        int consecutive = 0;
        int blocking = 0;
        for (int k = 0; k < 4; k++) {
            if (board[i + k][j - k] == player) {
                consecutive++;
            } else if (board[i + k][j - k] == EMPTY) {
                blocking++;
            } else {
                blocking = 0;
            }

            if (consecutive == 3) {
                score += 10; // Encourage forming a connect 4
            } else if (consecutive == 2 && blocking == 1) {
                score += 3; // Encourage forming a connect 4
            } else if (blocking == 3) {
                score += 5; // Encourage blocking opponent's connect 4
            } else if (blocking == 2) {
                score += 2; // Encourage blocking opponent's potential connect 4
            }

            if (consecutive > maxConsecutive) {
                maxConsecutive = consecutive;
            }
            if (blocking > maxBlocking) {
                maxBlocking = blocking;
            }
        }
    }

    if (maxConsecutive >= 3) {
        score += 50; // Encourage forming a connect4
    } else if (maxBlocking > 3) {
        score += 100; // Encourage blocking opponent's connect 4
    }

    return score;
}

move_t best_move(board_t board, player_t player) {
    move_t move;
    move.col = -1;
    move.score = player == RED ? -10000 : 10000; // Initialize with a very low/high score

    // Check if the current player has won
    if (has_won(board, player)) {
        move.score = player == RED ? 1000 : -1000;
        return move;
    }

    // Check if the board is full (it's a draw)
    if (is_full(board)) {
        move.score = player == RED ? 1000 : -1000;
        return move;
    }

    if (has_won(board, RED) || has_won(board, BLUE) || is_full(board)) {
        move.score = board_score(board, player);
        return move;
    }

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 4; i++) {
            if (board[i][j] == EMPTY) {
                // Make the move
                board[i][j] = player;

                // Recursively call best_move for the opponent
                move_t make_move = best_move(board, (player == RED) ? BLUE : RED);

                // Undo the move
                board[i][j] = EMPTY;

                // Update the best move if this move has a better score
                if ((player == RED && make_move.score > move.score) ||
                    (player == BLUE && make_move.score < move.score)) {
                    move.col = j;
                    move.score = make_move.score;
                }
                break;
            }
        }
    }

    return move;
}


/* Function to print the current state of the game board */
void print_board(board_t board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            switch (board[i][j]) {
                case EMPTY:
                    printf("  "); // Empty cell
                    break;
                case RED:
                    printf("R "); // Red player's disc
                    break;
                case BLUE:
                    printf("B "); // Blue player's disc
                    break;
            }
        }
        printf("\n");
    }
    printf("1 2 3 4 5\n"); // Column numbers
}

int main() {
    board_t board;
    player_t user;
    player_t bot;

    // Initialize the board to empty
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = EMPTY;
        }
    }

    printf("Choose your color (1 for RED, 2 for BLUE): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        user = RED;
        bot = BLUE;
    } else {
        user = BLUE;
        bot = RED;
    }
    player_t current_player = RED;

    while (1) {
        if (current_player == user) {
            int column;
            int row;

            // Ask the user to select a column until a valid one is chosen
            while (1) {
                printf("Your move (1-5): ");
                scanf("%d", &column);
                column--; // Adjust for 0-based indexing
                row = 0;

                // Check if the selected column is not full
                while (row < 4) {
                    if (board[row][column] == EMPTY) {
                        break;
                    }
                    row++;
                }

                if (row < 4) {
                    break; // Valid move, exit the loop
                } else {
                    printf("Column is full. Please select another column.\n");
                }
            }

            board[row][column] = user;
            print_board(board);

            if (has_won(board, user)) {
                printf("Congratulations! You win!\n");
                break;
            } else if (is_full(board)) {
                printf("It's a draw!\n");
                break;
            }
        } else {
            printf("Computer's move\n");
            move_t move = best_move(board, bot);
            int row = 0;
            while (row < 4) {
                if (board[row][move.col] == EMPTY) {
                    board[row][move.col] = bot;
                    break;
                }
                row++;
            }
            print_board(board);

            if (has_won(board, bot)) {
                printf("Computer wins!\n");
                break;
            } else if (is_full(board)) {
                printf("It's a draw!\n");
                break;
            }
        }

        current_player = (current_player == RED) ? BLUE : RED;
    }

    return 0;
}
