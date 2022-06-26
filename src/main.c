#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int menuOption = 0, playerCount = 0, turn = 1, winner = 0, valid = 0;
	int i, j, piece, roll, startI, startJ, nextI, nextJ, rollTemp;
	char turnC;
	char board[9][9][3];
	int pieces[4][2];
	char temp;

	// Prompt user with menu options
	while (menuOption != 1 && menuOption != 3) {
		printf("Welcome to Kizma Birader\n1 - Play    2 - How to play    3 - Exit\nSelect option: ");
		scanf("%d", &menuOption);
		scanf("%c", &temp);
		// How to play
		if (menuOption == 2) {
			printf("1. Each player has 4 pieces.\n"
				   "2. There might be 2 , 3, or 4 players (Yellow (Y), Red (R), Green (G) and Blue (B)).\n"
				   "3. At each round the respective player rolls the single dice (1 6).\n"
				   "4. Each piece is allowed to leave from the nest, if the dice shows \"6\".\n"
				   "5. At each cell, only one single piece could exist.\n"
				   "6. Each player is allowed to place any number of his/her pieces into the raceway.\n"
				   "7. If the player rolls six, he/she could either place a piece into the board from the\n"
				   "nest or play any piece on the board.\n"
				   "8. A piece could move forward even if there is a piece of any opponent on its way.\n"
				   "9. If a piece stops at the same place of another piece of the same player, the player is\n"
				   "not allowed to move it. He/she should wait for his/her next turn.\n"
				   "10. Nobody could hurt a piece if it reaches at the final destination.\n"
				   "11. If any piece could reach to the location of another players' piece, the piece should\n"
				   "return to its nest.\n"
				   "12. The player whose all 4 pieces reach at final destination becomes the WINNER.\n");
		}
	}
	// Play
	if (menuOption == 1) {
		// Ask the player count
		while (playerCount < 2 || playerCount > 4) {
			printf("Player count (2-4): ");
			scanf("%d", &playerCount);
			scanf("%c", &temp);
		}
		// Initialize board
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				// HY
				if (i < 2 && j < 2) {
					board[i][j][0] = 'Y';
					board[i][j][1] = (i * 3 + (j + 1) - i * j * 2) + '0';
					board[i][j][2] = '\0';
				}
				// HR
				else if (i < 2 && j > 6) {
					board[i][j][0] = 'R';
					board[i][j][1] = (i * 3 + (j - 6) - i * (j - 7) * 2) + '0';
					board[i][j][2] = '\0';
				}
				// HG
				else if (i > 6 && j < 2 && playerCount > 2) {
					board[i][j][0] = 'G';
					board[i][j][1] = ((i - 7) * 3 + (j + 1) - (i - 7) * j * 2) + '0';
					board[i][j][2] = '\0';
				}
				// HB
				else if (i > 6 && j > 6 && playerCount > 3) {
					board[i][j][0] = 'B';
					board[i][j][1] = ((i - 7) * 3 + (j - 6) - (i - 7) * (j - 7) * 2) + '0';
					board[i][j][2] = '\0';
				}
				// DY
				else if (i == 4 && j > 0 && j < 4) {
					board[i][j][0] = 'Y';
					board[i][j][1] = '\0';
				}
				// DR
				else if (j == 4 && i > 0 && i < 4) {
					board[i][j][0] = 'R';
					board[i][j][1] = '\0';
				}
				// DG
				else if (j == 4 && i > 4 && i < 8) {
					if (playerCount > 2) {
						board[i][j][0] = 'G';
						board[i][j][1] = '\0';
					} else {
						board[i][j][0] = '\0';
					}
				}
				// DB
				else if (i == 4 && j > 4 && j < 8) {
					if (playerCount > 3) {
						board[i][j][0] = 'B';
						board[i][j][1] = '\0';
					} else {
						board[i][j][0] = '\0';
					}
				}
				// Empty
				else if (((i < 3 || i > 5) && (j < 3 || j > 5)) || (i == 4 && j == 4)) {
					board[i][j][0] = '\0';
				}
				// P
				else {
					board[i][j][0] = '.';
					board[i][j][1] = '\0';
				}
			}
		}
		// Make moves until there is a winner
		while (!winner) {
			// Reset turn
			if (turn == playerCount + 1) {
				turn = 1;
			}
			// Print whose turn it is
			printf("--------------------------------\nTurn: ");
			if (turn == 1) {
				printf("Yellow\n");
				turnC = 'Y';
				startI = 3;
				startJ = 0;
			}
			else if (turn == 2) {
				printf("Red\n");
				turnC = 'R';
				startI = 0;
				startJ = 5;
			}
			else if (turn == 3) {
				printf("Green\n");
				turnC = 'G';
				startI = 8;
				startJ = 3;
			}
			else {
				printf("Blue\n");
				turnC = 'B';
				startI = 5;
				startJ = 8;	
			}
			// Print board
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					printf("%s\t", board[i][j]);
				}
				printf("\n");
			}
			// Roll the die
			srand(time(0));
			roll = rand() % 6 + 1;
			printf("You rolled: %d\n", roll);
			// Get all the pieces of the color
			for (i = 0; i < 9; i++) {
				for (j = 0; j < 9; j++) {
					if (board[i][j][0] == turnC) {
						pieces[board[i][j][1] - '1'][0] = i;
						pieces[board[i][j][1] - '1'][1] = j;
					}
				}
			}
			// Check if there are valid moves
			valid = 0;
			i = 0;
			while (i < 4 && !valid) {
				// Valid if the piece is in the base, starting position has no piece of the same color and rolled 6
				if ((pieces[i][0] < 2 || pieces[i][0] > 6) && (pieces[i][1] < 2 || pieces[i][1] > 6)) {
					if (board[startI][startJ][0] != turnC && roll == 6) {
						valid = 1;
					}
				}
				// For pieces that are not in the base, check if they can be moved
				else {
					nextI = pieces[i][0];
					nextJ = pieces[i][1];
					rollTemp = roll;
					// Move the piece one by one as much as the amount rolled
					while (rollTemp) {
						// Stop moving if the piece went out of the track
						if (board[nextI][nextJ][0] == '\0') {
							rollTemp = 1;
						}
						// Go to DY
						else if (turn == 1 && nextI == 4 && nextJ < 4) {
							nextJ++;
						}
						// Go to DR
						else if (turn == 2 && nextI < 4 && nextJ == 4) {
							nextI++;
						}
						// Go to DG
						else if (turn == 3 && nextI > 4 && nextJ == 4) {
							nextI--;
						}
						// Go to DB
						else if (turn == 4 && nextI == 4 && nextJ > 4) {
							nextJ--;
						}
						// Go right
						else if ((nextI == 0 && nextJ < 5) || (nextI == 3 && (nextJ < 3 || nextJ > 4) && nextJ != 8)) {
							nextJ++;
						}
						// Go left
						else if ((nextI == 5 && (nextJ < 4 || nextJ > 5) && nextJ != 0) || (nextI == 8 && nextJ > 3)) {
							nextJ--;
						}
						// Go down
						else if ((nextJ == 5 && (nextI < 3 || nextI > 4) && nextI != 8) || (nextJ == 8 && nextI < 5)) {
							nextI++;
						}
						// Go up
						else if ((nextJ == 0 && nextI > 3) || (nextJ == 3 && (nextI < 4 || nextI > 5) && nextI != 0)) {
							nextI--;
						}
						rollTemp--;
					}
					// Valid if the piece will not be on another piece of their own or outside the track
					if (board[nextI][nextJ][0] != turnC && board[nextI][nextJ][0] != '\0') {
						valid = 1;
					}
					// Valid if the piece will be on one of the ending positions
					else if (board[nextI][nextJ][1] == '\0' && board[nextI][nextJ][0] != '\0') {
						valid = 1;
					}
				}
				i++;
			}
			// If there are no valid moves, prompt the user to skip their turn
			if (!valid) {
				printf("No valid moves. Press enter to continue.");
				scanf("%c", &temp);
			}
			// If there are valid moves, continue playing for the turn
			while (valid) {
				piece = 0;
				// Ask the user which piece they want to play
				while (piece < 1 || piece > 4) {
					printf("Piece you want to move (1-4): ");
					scanf("%d", &piece);
					scanf("%c", &temp);
				}
				// Get the coordinates of the pieces
				i = pieces[piece - 1][0];
				j = pieces[piece - 1][1];
				// Check if the piece can be moved, if so move the piece
				// If the piece is in the base
				if ((i < 2 || i > 6) && (j < 2 || j > 6)) {
					// If the starting position has no piece of the same color and rolled 6
					if (board[startI][startJ][0] != turnC && roll == 6) {
						printf("%c%d got out of its nest.\n", turnC, piece);
						// If starting position has a piece of the other colors, send them to their base
						if (board[startI][startJ][0] != '.') {
							printf("%s returned to its nest.\n", board[startI][startJ]);
							// If the piece at the starting position is Yellow
							if (board[startI][startJ][0] == 'Y') {
								// Place the piece to their respected place at their base, based on their number
								if (board[startI][startJ][1] - '1' < 2) {
									board[0][board[startI][startJ][1] - '1'][0] = board[startI][startJ][0];
									board[0][board[startI][startJ][1] - '1'][1] = board[startI][startJ][1];
									board[0][board[startI][startJ][1] - '1'][2] = '\0';
								} else {
									board[1][3 - (board[startI][startJ][1] - '1')][0] = board[startI][startJ][0];
									board[1][3 - (board[startI][startJ][1] - '1')][1] = board[startI][startJ][1];
									board[1][3 - (board[startI][startJ][1] - '1')][2] = '\0';
								}
							}
							// If the piece at the starting position is Red
							else if (board[startI][startJ][0] == 'R') {
								// Place the piece to their respected place at their base, based on their number
								if (board[startI][startJ][1] - '1' < 2) {
									board[0][board[startI][startJ][1] - '1' + 7][0] = board[startI][startJ][0];
									board[0][board[startI][startJ][1] - '1' + 7][1] = board[startI][startJ][1];
									board[0][board[startI][startJ][1] - '1' + 7][2] = '\0';
								} else {
									board[1][10 - (board[startI][startJ][1] - '1')][0] = board[startI][startJ][0];
									board[1][10 - (board[startI][startJ][1] - '1')][1] = board[startI][startJ][1];
									board[1][10 - (board[startI][startJ][1] - '1')][2] = '\0';
								}
							}
							// If the piece at the starting position is Green
							else if (board[startI][startJ][0] == 'G') {
								// Place the piece to their respected place at their base, based on their number
								if (board[startI][startJ][1] - '1' < 2) {
									board[7][board[startI][startJ][1] - '1'][0] = board[startI][startJ][0];
									board[7][board[startI][startJ][1] - '1'][1] = board[startI][startJ][1];
									board[7][board[startI][startJ][1] - '1'][2] = '\0';
								} else {
									board[8][3 - (board[startI][startJ][1] - '1')][0] = board[startI][startJ][0];
									board[8][3 - (board[startI][startJ][1] - '1')][1] = board[startI][startJ][1];
									board[8][3 - (board[startI][startJ][1] - '1')][2] = '\0';
								}
							}
							// If the piece at the starting position is Blue
							else if (board[startI][startJ][0] == 'B') {
								// Place the piece to their respected place at their base, based on their number
								if (board[startI][startJ][1] - '1' < 2) {
									board[7][board[startI][startJ][1] - '1' + 7][0] = board[startI][startJ][0];
									board[7][board[startI][startJ][1] - '1' + 7][1] = board[startI][startJ][1];
									board[7][board[startI][startJ][1] - '1' + 7][2] = '\0';
								} else {
									board[8][10 - (board[startI][startJ][1] - '1')][0] = board[startI][startJ][0];
									board[8][10 - (board[startI][startJ][1] - '1')][1] = board[startI][startJ][1];
									board[8][10 - (board[startI][startJ][1] - '1')][2] = '\0';
								}
							}
						}
						// Move the piece out of the base to the starting position
						board[startI][startJ][0] = turnC;
						board[startI][startJ][1] = piece + '0';
						board[startI][startJ][2] = '\0';
						board[i][j][0] = '\0';
						valid = 0;
					}
				}
				// For pieces that are not in the base, check if they can be moved, if so move them
				else {
					nextI = i;
					nextJ = j;
					rollTemp = roll;
					// Move the piece one by one as much as the amount rolled
					// Same procedure as above
					while (rollTemp) {
						// Stop moving if the piece went out of the track
						if (board[nextI][nextJ][0] == '\0') {
							rollTemp = 1;
						}
						// Go to DY
						else if (turn == 1 && nextI == 4 && nextJ < 4) {
							nextJ++;
						}
						// Go to DR
						else if (turn == 2 && nextI < 4 && nextJ == 4) {
							nextI++;
						}
						// Go to DG
						else if (turn == 3 && nextI > 4 && nextJ == 4) {
							nextI--;
						}
						// Go to DB
						else if (turn == 4 && nextI == 4 && nextJ > 4) {
							nextJ--;
						}
						// Go right
						else if ((nextI == 0 && nextJ < 5) || (nextI == 3 && (nextJ < 3 || nextJ > 4) && nextJ != 8)) {
							nextJ++;
						}
						// Go left
						else if ((nextI == 5 && (nextJ < 4 || nextJ > 5) && nextJ != 0) || (nextI == 8 && nextJ > 3)) {
							nextJ--;
						}
						// Go down
						else if ((nextJ == 5 && (nextI < 3 || nextI > 4) && nextI != 8) || (nextJ == 8 && nextI < 5)) {
							nextI++;
						}
						// Go up
						else if ((nextJ == 0 && nextI > 3) || (nextJ == 3 && (nextI < 4 || nextI > 5) && nextI != 0)) {
							nextI--;
						}
						rollTemp--;
					}
					// Check if the piece will not be on another piece of their own or outside the track
					if (board[nextI][nextJ][0] != turnC && board[nextI][nextJ][0] != '\0') {
						printf("Moved %c%d.\n", turnC, piece);
						// Check if there is a piece from another color, if so send them to their base
						// Same procedure as above
						if (board[nextI][nextJ][0] != '.') {
							printf("%s returned to its nest.\n", board[nextI][nextJ]);
							if (board[nextI][nextJ][0] == 'Y') {
								if (board[nextI][nextJ][1] - '1' < 2) {
									board[0][board[nextI][nextJ][1] - '1'][0] = board[nextI][nextJ][0];
									board[0][board[nextI][nextJ][1] - '1'][1] = board[nextI][nextJ][1];
									board[0][board[nextI][nextJ][1] - '1'][2] = '\0';
								} else {
									board[1][3 - (board[nextI][nextJ][1] - '1')][0] = board[nextI][nextJ][0];
									board[1][3 - (board[nextI][nextJ][1] - '1')][1] = board[nextI][nextJ][1];
									board[1][3 - (board[nextI][nextJ][1] - '1')][2] = '\0';
								}
							}
							else if (board[nextI][nextJ][0] == 'R') {
								if (board[nextI][nextJ][1] - '1' < 2) {
									board[0][board[nextI][nextJ][1] - '1' + 7][0] = board[nextI][nextJ][0];
									board[0][board[nextI][nextJ][1] - '1' + 7][1] = board[nextI][nextJ][1];
									board[0][board[nextI][nextJ][1] - '1' + 7][2] = '\0';
								} else {
									board[1][10 - (board[nextI][nextJ][1] - '1')][0] = board[nextI][nextJ][0];
									board[1][10 - (board[nextI][nextJ][1] - '1')][1] = board[nextI][nextJ][1];
									board[1][10 - (board[nextI][nextJ][1] - '1')][2] = '\0';
								}
							}
							else if (board[nextI][nextJ][0] == 'G') {
								if (board[nextI][nextJ][1] - '1' < 2) {
									board[7][board[nextI][nextJ][1] - '1'][0] = board[nextI][nextJ][0];
									board[7][board[nextI][nextJ][1] - '1'][1] = board[nextI][nextJ][1];
									board[7][board[nextI][nextJ][1] - '1'][2] = '\0';
								} else {
									board[8][3 - (board[nextI][nextJ][1] - '1')][0] = board[nextI][nextJ][0];
									board[8][3 - (board[nextI][nextJ][1] - '1')][1] = board[nextI][nextJ][1];
									board[8][3 - (board[nextI][nextJ][1] - '1')][2] = '\0';
								}
							}
							else if (board[nextI][nextJ][0] == 'B') {
								if (board[nextI][nextJ][1] - '1' < 2) {
									board[7][board[nextI][nextJ][1] - '1' + 7][0] = board[nextI][nextJ][0];
									board[7][board[nextI][nextJ][1] - '1' + 7][1] = board[nextI][nextJ][1];
									board[7][board[nextI][nextJ][1] - '1' + 7][2] = '\0';
								} else {
									board[8][10 - (board[nextI][nextJ][1] - '1')][0] = board[nextI][nextJ][0];
									board[8][10 - (board[nextI][nextJ][1] - '1')][1] = board[nextI][nextJ][1];
									board[8][10 - (board[nextI][nextJ][1] - '1')][2] = '\0';
								}
							}
						}
						board[nextI][nextJ][0] = turnC;
						board[nextI][nextJ][1] = piece + '0';
						board[nextI][nextJ][2] = '\0';
						board[i][j][0] = '.';
						board[i][j][1] = '\0';
						valid = 0;
					}
					// If the piece will be on one of the ending positions
					else if (board[nextI][nextJ][1] == '\0' && board[nextI][nextJ][0] != '\0') {
						printf("Moved %c%d.\n", turnC, piece);
						board[nextI][nextJ][0] = turnC;
						board[nextI][nextJ][1] = piece + '0';
						board[nextI][nextJ][2] = '\0';
						// If the piece is not coming from one of the ending positions, rename the position to empty
						if (!((i == 4 && j > 0 && j < 8) || (j == 4 && i > 0 && i < 8))) {
							board[i][j][0] = '.';
						}
						board[i][j][1] = '\0';
						valid = 0;
					}
				}
				// Check if there is a winner
				if ((turn == 1 && board[4][0][0] == turnC && board[4][1][1] != '\0' && board[4][2][1] != '\0' && board[4][3][1] != '\0')
					|| (turn == 2 && board[0][4][0] == turnC && board[1][4][1] != '\0' && board[2][4][1] != '\0' && board[3][4][1] != '\0')
					|| (turn == 3 && board[8][4][0] == turnC && board[7][4][1] != '\0' && board[6][4][1] != '\0' && board[5][4][1] != '\0')
					|| (turn == 4 && board[4][8][0] == turnC && board[4][7][1] != '\0' && board[4][6][1] != '\0' && board[4][5][1] != '\0')) {
					winner = turn;
				}
				// If the piece the user is trying to move is not movable, alert the user
				if (valid) {
					printf("Cannot play %c%d.\n", turnC, piece);
				}
			}
			turn++;
		}
		// Print the winner
		if (winner == 1) {
			printf("Yellow");
		}
		else if (winner == 2) {
			printf("Red");
		}
		else if (winner == 3) {
			printf("Green");
		}
		else if (winner == 4) {
			printf("Blue");
		}
		printf(" won.\n");
	}
	return 0;
}