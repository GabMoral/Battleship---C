#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Grid size
#define SIZEY 11
#define SIZEX 11

struct Ship {
	char *className;
	char classCode;
	int size;
	int *xArray;
	int *yArray;
	char *statusArray;
	int hp;
};
struct Player {
	char name[16];
	char securityPIN[5];
	char upperGrid[SIZEY][SIZEX];
	char lowerGrid[SIZEY][SIZEX];
	int shipCount;
	struct Ship playerShips[5];
};
//Initialize grid elements
void initGrid(char grid[SIZEY][SIZEX], char fill) {
	for (int i = 0; i < SIZEX - 1; i++) {
		for (int j = 0; j < SIZEY - 1; j++) {
			grid[i][j] = fill;
		}
	}
}
//Fills grid
void grid(char grid[SIZEY][SIZEX]) {
	//print x coordinates
	printf("    ");
	for (int i = 0; i < SIZEX - 1; i++) {
		printf(" %d", i);
	}
	printf("\n");
	printf("    ");
	for (int i = 0; i < SIZEX - 1; i++) {
		printf("--");
	}
	printf("\n");
	//print y coordinates and remaining grid
	for (int i = 0; i < SIZEY - 1; i++) {
		printf(" %d |", i);
		for (int j = 0; j < SIZEX - 1; j++) {
			printf(" %c", grid[i][j]);
		}
		printf("\n");
	}
}
//Displays grid
void dispGrid(char lowerGrid[SIZEY][SIZEX], char upperGrid[SIZEY][SIZEX]) {
	grid(upperGrid);
	printf("\n");
	grid(lowerGrid);
}
//Initialize ships
void initShips(struct Ship* ships) {
	for (int i = 0; i < 5; i++) {
		switch (i) {
		case 0:
			ships[i].className = "Carrier";
			ships[i].classCode = 'C';
			ships[i].size = 5;
			ships[i].statusArray = "CCCCC";
			ships[i].hp = ships[i].size;
			break;
		case 1:
			ships[i].className = "Battleship";
			ships[i].classCode = 'B';
			ships[i].size = 4;
			ships[i].statusArray = "BBBB";
			ships[i].hp = ships[i].size;
			break;
		case 2:
			ships[i].className = "Destroyer";
			ships[i].classCode = 'D';
			ships[i].size = 3;
			ships[i].statusArray = "DDD";
			ships[i].hp = ships[i].size;
			break;
		case 3:
			ships[i].className = "Submarine";
			ships[i].classCode = 'S';
			ships[i].size = 3;
			ships[i].statusArray = "SSS";
			ships[i].hp = ships[i].size;
			break;
		case 4:
			ships[i].className = "Patrol";
			ships[i].classCode = 'P';
			ships[i].size = 2;
			ships[i].statusArray = "PP";
			ships[i].hp = ships[i].size;
			break;
		}
	}
	
}
//Gets player information
void getUser(struct Player* player) {
	//Initialize player
	printf("Enter name(max 15 characters): ");
	scanf("%15s", player->name);
	//read past invalid input
	scanf("%*[^\n]");
	printf("%s\n", player->name);
	printf("Create a 4 character PIN: ");
	scanf("%4s", player->securityPIN);
	//read past invalid input
	scanf("%*[^\n]");
	printf("You're security PIN is %s\n", player->securityPIN);
	printf("Don't forget your PIN, as you will need it to confirm your turn. Entry is case sensitive.\n");
	system("pause");
}
//Gets player ship coordinates
void getCoords(struct Player* player) {
	printf("%s, now you will enter the x and y coordinates of your ships.\n", player->name);
	char inputDir;
	int inputX, inputY;
	int validInput = 0;
	int outOfRange = 0;
	int validDir = 0;
	int colliding = 0;
	for (int j = 0; j < player->shipCount; j++) {
		do {
			printf("Enter the frontend coordinate (x y) and direction (N = north, S = south, W = west, E = east) for the %s (Example: 3 4 N): ", player->playerShips[j].className);
			validInput = scanf("%d %d %c", &inputX, &inputY, &inputDir);

			if (validInput == 0)
				printf("Invalid entry!!!\n");
			if ((inputX < 0 || inputX > 9) || (inputY < 0 || inputY > 9)) {
				printf("Coordinates out of range!!!\n");
				outOfRange = 1;
			}
			else
				outOfRange = 0;
			switch (inputDir) {
			case 'N':
				if (inputY - player->playerShips[j].size + 1 < 0) {
					outOfRange = 1;
					printf("Ship runs out of range!!!\n");
					break;
				}
				validDir = 1;
				break;
			case 'S':
				if (inputY + player->playerShips[j].size - 1 > 9) {
					outOfRange = 1;
					printf("Ship runs out of range!!!\n");
					break;
				}
				validDir = 1;
				break;
			case 'W':
				if (inputX - player->playerShips[j].size + 1 < 0) {
					outOfRange = 1;
					printf("Ship runs out of range!!!\n");
					break;
				}
				validDir = 1;
				break;
			case 'E':
				if (inputX + player->playerShips[j].size - 1 > 9) {
					outOfRange = 1;
					printf("Ship runs out of range!!!\n");
					break;
				}
				validDir = 1;
				break;
			default:
				validDir = 0;
				printf("Invalid direction!!!\n");
			}
			if (validInput != 0 && outOfRange == 0 && validDir == 1) {
				colliding = 0;
				for (int i = 0; i < player->playerShips[j].size && colliding == 0; i++) {
					switch (inputDir) {
					case 'N':
						if (player->lowerGrid[inputY - i][inputX] != '-') {
							colliding = 1;
							printf("Coordinate(s) are taken!!!\n");
							break;
						}
						colliding = 0;
						break;
					case 'S':
						if (player->lowerGrid[inputY + i][inputX] != '-') {
							colliding = 1;
							printf("Coordinate(s) are taken!!!\n");
							break;
						}
						colliding = 0;
						break;
					case 'W':
						if (player->lowerGrid[inputY][inputX - i] != '-') {
							colliding = 1;
							printf("Coordinate(s) are taken!!!\n");
							break;
						}
						colliding = 0;
						break;
					case 'E':
						if (player->lowerGrid[inputY][inputX + i] != '-') {
							colliding = 1;
							printf("Coordinate(s) are taken!!!\n");
							break;
						}
						colliding = 0;
						break;
					}
				}
			}
			//read past invalid input
			scanf("%*[^\n]");
		} while (validInput == 0 || outOfRange == 1 || validDir == 0 || colliding == 1);

		player->playerShips[j].xArray = (int*)malloc(sizeof(int) * player->playerShips[j].size);
		player->playerShips[j].yArray = (int*)malloc(sizeof(int) * player->playerShips[j].size);
		for (int i = 0; i < player->playerShips[j].size; i++) {
			switch (inputDir) {
			case 'N':
				player->playerShips[j].xArray[i] = inputX;
				player->playerShips[j].yArray[i] = inputY - i;
				player->lowerGrid[player->playerShips[j].yArray[i]][player->playerShips[j].xArray[i]] = player->playerShips[j].classCode;
				break;
			case 'S':
				player->playerShips[j].xArray[i] = inputX;
				player->playerShips[j].yArray[i] = inputY + i;
				player->lowerGrid[player->playerShips[j].yArray[i]][player->playerShips[j].xArray[i]] = player->playerShips[j].classCode;
				break;
			case 'W':
				player->playerShips[j].xArray[i] = inputX - i;
				player->playerShips[j].yArray[i] = inputY;
				player->lowerGrid[player->playerShips[j].yArray[i]][player->playerShips[j].xArray[i]] = player->playerShips[j].classCode;
				break;
			case 'E':
				player->playerShips[j].xArray[i] = inputX + i;
				player->playerShips[j].yArray[i] = inputY;
				player->lowerGrid[player->playerShips[j].yArray[i]][player->playerShips[j].xArray[i]] = player->playerShips[j].classCode;
				break;
			}
		}
		//Display upper and lower grid
		dispGrid(player->lowerGrid, player->upperGrid);
	}
}
//Checks security PIN entered matches
void checkPIN(struct Player* player) {
	char inputPIN[5];
	int PINMatch;
	do {
		printf("%s, enter your PIN to access the grid.\nPIN: ", player->name);
		scanf("%4s", &inputPIN);
		PINMatch = strcmp(inputPIN, player->securityPIN);
		if (PINMatch != 0) {
			printf("PIN does not match. Try again.\n");
		}
		else {
			printf("PIN match success.\n");
		}
	} while (PINMatch != 0);
}
//Gets player attack coordinates
void attackCoords(struct Player* player, struct Player* enemy, int* endMatch) {
	int inputX, inputY;
	int validInput = 0;
	int outOfRange = 0;
	int taken;
	do {
		printf("%s, enter the attack coordinates (x y): ", player->name);
		validInput = scanf("%d %d", &inputX, &inputY);

		if (validInput == 0)
			printf("Invalid entry!!!\n");
		if ((inputX < 0 || inputX > 9) || (inputY < 0 || inputY > 9)) {
			printf("Coordinates out of range!!!\n");
			outOfRange = 1;
		}
		else
			outOfRange = 0;
		if (validInput != 0 && outOfRange == 0) {
			taken = 0;
			if (player->upperGrid[inputY][inputX] == 'M') {
				taken = 1;
				printf("Coordinates already missed!!!\n");
			}
			if (player->upperGrid[inputY][inputX] == 'H') {
				taken = 1;
				printf("Coordinates already hit!!!\n");
			}
		}
	} while (validInput == 0 || outOfRange == 1 || taken == 1);
	if (enemy->lowerGrid[inputY][inputX] == '-') {
		player->upperGrid[inputY][inputX] = 'M';
		enemy->lowerGrid[inputY][inputX] = 'M';
		printf("Attack missed.\n");
	}
	else {
		player->upperGrid[inputY][inputX] = 'H';
		if (enemy->lowerGrid[inputY][inputX] == 'C') {
			enemy->playerShips[0].hp--;
			enemy->lowerGrid[inputY][inputX] = 'H';
			printf("Attack hit.\n");
			if (enemy->playerShips[0].hp <= 0) {
				printf("Enemy carrier destroyed.\n");
				enemy->shipCount--;
			}
		}
		if (enemy->lowerGrid[inputY][inputX] == 'B') {
			enemy->playerShips[1].hp--;
			enemy->lowerGrid[inputY][inputX] = 'H';
			printf("Attack hit.\n");
			if (enemy->playerShips[1].hp <= 0) {
				printf("Enemy battleship destroyed.\n");
				enemy->shipCount--;
			}
		}
		if (enemy->lowerGrid[inputY][inputX] == 'D') {
			enemy->playerShips[2].hp--;
			enemy->lowerGrid[inputY][inputX] = 'H';
			printf("Attack hit.\n");
			if (enemy->playerShips[2].hp <= 0) {
				printf("Enemy destroyer destroyed.\n");
				enemy->shipCount--;
			}
		}
		if (enemy->lowerGrid[inputY][inputX] == 'S') {
			enemy->playerShips[3].hp--;
			enemy->lowerGrid[inputY][inputX] = 'H';
			printf("Attack hit.\n");
			if (enemy->playerShips[3].hp <= 0) {
				printf("Enemy submarine destroyed.\n");
				enemy->shipCount--;
			}
		}
		if (enemy->lowerGrid[inputY][inputX] == 'P') {
			enemy->playerShips[4].hp--;
			enemy->lowerGrid[inputY][inputX] = 'H';
			printf("Attack hit.\n");
			if (enemy->playerShips[4].hp <= 0) {
				printf("Enemy patrol boat destroyed.\n");
				enemy->shipCount--;
			}
		}
		if (enemy->shipCount <= 0) {
			printf("All enemy ships have been destroyed.\n%s wins.\n", player->name);
			*endMatch = 1;
		}
	}
}
int main() {
	struct Player player1;
	struct Player player2;
	char initFillLower = '-';
	char initFillUpper = '-';
	int endMatch = 0;
	int endGame = 0;
	char playAgain;
	int validInput;
	
	do {
		//Get user 1 name and PIN
		printf("Player 1\n");
		getUser(&player1);
		//Initialize upper and lower grid
		initGrid(player1.lowerGrid, initFillLower);
		initGrid(player1.upperGrid, initFillUpper);
		player1.shipCount = 5;
		//Initialize player ships
		initShips(player1.playerShips);
		//Display upper and lower grid
		dispGrid(player1.lowerGrid, player1.upperGrid);
		getCoords(&player1);

		system("pause");
		system("cls");

		//Get user 2 name and PIN
		printf("Player 2\n");
		getUser(&player2);
		//Initialize upper and lower grid
		initGrid(player2.lowerGrid, initFillLower);
		initGrid(player2.upperGrid, initFillUpper);
		player2.shipCount = 5;
		//Initialize player ships
		initShips(player2.playerShips);
		//Display upper and lower grid
		dispGrid(player2.lowerGrid, player2.upperGrid);
		getCoords(&player2);

		system("pause");
		system("cls");

		while (1) {
			//Player 1 turn
			checkPIN(&player1);
			//Display upper and lower grid
			dispGrid(player1.lowerGrid, player1.upperGrid);
			attackCoords(&player1, &player2, &endMatch);
			//Display upper and lower grid
			dispGrid(player1.lowerGrid, player1.upperGrid);
			if (endMatch) break;

			system("pause");
			system("cls");

			//Player 2 turn
			checkPIN(&player2);
			//Display upper and lower grid
			dispGrid(player2.lowerGrid, player2.upperGrid);
			attackCoords(&player2, &player1, &endMatch);
			//Display upper and lower grid
			dispGrid(player2.lowerGrid, player2.upperGrid);
			if (endMatch) break;

			system("pause");
			system("cls");
		}
		do {
			printf("Would you like to play again? Yes or No (Y or N). ");
			validInput = scanf(" %c", &playAgain);
			//read past invalid input
			scanf("%*[^\n]");
			if (playAgain != 'Y' && playAgain != 'N') {
				printf("Type Y or N.\n");
				validInput = 0;
			}
			else if (playAgain == 'N') {
				printf("Thanks for playing.\n");
				validInput = 1;
				endGame = 1;
			}
			else if (playAgain == 'Y') {
				printf("New battle starting.\n");
				validInput = 1;
				endGame = 0;
			}
		} while (validInput == 0);
	} while (!endGame);
	system("pause");
	return 0;
}