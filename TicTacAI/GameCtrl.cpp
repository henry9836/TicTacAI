#include <iostream>
#include <windows.h>
#include <vector>
#include <array>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include "main.h"
#include "ConsoleControls.h"
#include "GridControl.h"
#include "GameCtrl.h"

using namespace std;

constexpr int computerToken = 2;
constexpr int playerToken = 1;
constexpr int emptyToken = 0;
constexpr int minX = 2;
constexpr int maxX = 10;
constexpr int minY = 4;
constexpr int maxY = 8;
constexpr int aiMAX = 1000;
constexpr int aiMIN = -1000;

std::array<int, 9> m_grid_state = { 0,0,0,0,0,0,0,0,0 }; //holds our game info on tokens
std::array<int, 9> bak_m_grid_state = { 0,0,0,0,0,0,0,0,0 }; //this will take care of any strange problems


int difficultyLevel = 0;
int keyPressed = 0;
int playerTurn = 0;
int currentX = 0; //X pos on console
int currentY = 0; //Y pos on console
int currentXBoard = 0; //X pos on board
int currentYBoard = 0; //Y pos on board
int winner = 0;
int count1 = 0; //DEBUG VALUE

bool GameOver = false;
bool DEBUG_MODE = false;
bool TurnOver = true;
bool PlacedPiece = false;
bool isPlayer2AI = true;

vector<string> AI_names {"Bob", "Cortana", "Clippy", "Watson", "Skynet", "Little Timmy", "GLaDOS", "HAL-9000", "Bird Brain"}; //AI Names

string player1_name = "Player 1";
string player2_name = "Player 2";

// places a piece on the board
void PlacePiece() {

	/*
	
	Places a token according to the current state of playerTurn as well as board's current X and Y positions
	
	*/

	int refP = emptyToken;

	if (playerTurn == 1) {
		refP = playerToken;
	}
	else {
		refP = computerToken;
	}

	if (currentYBoard == 0) {
		if (m_grid_state[currentXBoard] == 0) {
			m_grid_state[currentXBoard] = refP;
			PlacedPiece = true;
		}
	}
	else if (currentYBoard == 1) {
		if (m_grid_state[currentXBoard + 3] == 0) {
			m_grid_state[currentXBoard + 3] = refP;
			PlacedPiece = true;
		}
	}
	else if (currentYBoard == 2) {
		if (m_grid_state[currentXBoard + 6] == 0) {
			m_grid_state[currentXBoard + 6] = refP;
			PlacedPiece = true;
		}
	}
}

int CheckForWin(int mode) {
	/*

	Check who won

	Modes:

	1 - AI Check
	2 - Normal Check

	Possible Win Conditions:

	0 - No winner (game still in progress)
	1 - P1 Wins (user)
	2 - P2 Wins (computer/user)
	-1 - Tie

	*/

	if (m_grid_state[0] == m_grid_state[1] 
		&& m_grid_state[2] == m_grid_state[1] 
		&& m_grid_state[0] != 0) 
	{
		winner = m_grid_state[0];
	}
	else if (m_grid_state[3] == m_grid_state[4] 
		&& m_grid_state[5] == m_grid_state[4] 
		&& m_grid_state[3] != 0) 
	{
		winner = m_grid_state[3];
	}
	else if (m_grid_state[6] == m_grid_state[7] 
		&& m_grid_state[8] == m_grid_state[7] 
		&& m_grid_state[6] != 0) 
	{
		winner = m_grid_state[6];
	}
	else if (m_grid_state[0] == m_grid_state[3] 
		&& m_grid_state[6] == m_grid_state[3] 
		&& m_grid_state[0] != 0) 
	{
		winner = m_grid_state[0];
	}
	else if (m_grid_state[1] == m_grid_state[4] 
		&& m_grid_state[7] == m_grid_state[4] 
		&& m_grid_state[1] != 0) 
	{
		winner = m_grid_state[1];
	}
	else if (m_grid_state[2] == m_grid_state[5] 
		&& m_grid_state[8] == m_grid_state[5] 
		&& m_grid_state[2] != 0) 
	{
		winner = m_grid_state[2];
	}
	else if (m_grid_state[0] == m_grid_state[4] 
		&& m_grid_state[8] == m_grid_state[4] 
		&& m_grid_state[0] != 0) 
	{
		winner = m_grid_state[0];
	}
	else if (m_grid_state[2] == m_grid_state[4] 
		&& m_grid_state[6] == m_grid_state[4] 
		&& m_grid_state[2] != 0) 
	{
		winner = m_grid_state[2];
	}
	else if (m_grid_state[0] != 0 && m_grid_state[1] != 0 && m_grid_state[2] != 0 && m_grid_state[3] != 0 && m_grid_state[4] != 0 && m_grid_state[5] != 0 && m_grid_state[6] != 0 && m_grid_state[7] != 0 && m_grid_state[8] != 0) {
		winner = -1;
	}
	else {
		winner = 0;
	}

	if (mode == 2) {
		switch (winner)
		{
		case 0: {
			GameOver = false;
			break;
		}
		default: {
			GameOver = true;
			break;
		}
		}
	}

	return winner;
}

int minimax(int depth, int m_Turn, int alpha, int beta) {

	/*
	
	minimax function checks all possible moves and tells AI which is the best move
	
	*/

	int winner = CheckForWin(1); // get winner

	if (winner != 0) { // if winner exists
		if (winner == 2) { // if computer wins
			int score = 100 - depth;
			if (DEBUG_MODE) {
				Console_gotoXY(0, 21);
				cout << "Score: " << score << endl;
			}
			return score;
		}
		else if (winner == -1) { // tie
			int score = 0;
			if (DEBUG_MODE) {
				Console_gotoXY(0, 21);
				cout << "Score: " << score << endl;
			}
			return score;
		}
		else { // if player wins
			int score = -100 + depth;
			if (DEBUG_MODE) {
				Console_gotoXY(0, 21);
				cout << "Score: " << score << endl;
			}
			return score;
		}
	}

	if (DEBUG_MODE) {
		Console_gotoXY(0, 23);
		cout << "Depth: " << depth;
	}

	if (depth > difficultyLevel) { //difficulty handicap
		return 0;
	}

	bool canMakeAMove = std::any_of(begin(m_grid_state), end(m_grid_state), [](int i) { return i == 0; }); //Checks if we can make a move
	if (!canMakeAMove)
	{
		return 0;
	}

	if (m_Turn == playerToken) { //if player's turn
		int bestVal = 1000;
		for (size_t i = 0; i < 9; i++)
		{
			if (m_grid_state[i] == emptyToken) {
				m_grid_state[i] = playerToken;
				count1++;
				if (DEBUG_MODE) {
					Console_gotoXY(0, 20);
					cout << count1 << endl;
				}
				int value = minimax(depth + 1, computerToken, alpha, beta); //simulate computer's turn

				m_grid_state[i] = emptyToken; //reset after simulation
				bestVal = min(bestVal, value);

				beta = min(beta, bestVal);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		return bestVal;
	}
	else { //if computer's turn
		int bestVal = -1000;
		for (size_t i = 0; i < 9; i++)
		{
			if (m_grid_state[i] == emptyToken) {
				m_grid_state[i] = computerToken;
				count1 ++;
				if (DEBUG_MODE) {
					Console_gotoXY(0, 20);
					cout << count1 << endl;
				}
				int value = minimax(depth + 1, playerToken, alpha, beta); //simulate player's turn

				m_grid_state[i] = emptyToken; //reset after simulation
				bestVal = max(bestVal, value);
	
				alpha = max(alpha, bestVal);
				if (beta <= alpha)
				{
					break;
				}
			}
		}
		return bestVal;
	}
}

void AI_Move() {

	/*
	
	AI takes it's turn

	*/

	int pos = -1;
	int best = -1000;
	int moveValue = 0;
	int depth = 0;
	bool solved = false;

	for (size_t i = 0; i < 9; i++) //backup grid for safe restore
	{
		bak_m_grid_state[i] = m_grid_state[i];
	}

	if (!solved) {
		for (int j = 0; j < 9; j++)
		{
			if (m_grid_state[j] == emptyToken)
			{
				m_grid_state[j] = computerToken; //take first move in simulation
				moveValue = minimax(0, playerToken, aiMIN, aiMAX); // simulate player's turn
				m_grid_state[j] = emptyToken; //reset board
				if (moveValue > best)
				{
					pos = j;
					best = moveValue;
				}
			}

		}
	}

	for (size_t i = 0; i < 9; i++) //safe restore to fix any potential bugs
	{
		m_grid_state[i] = bak_m_grid_state[i];
	}

	//Set the x and y pos of the board according to pos

	if (pos == 0 || pos == 3 || pos == 6)
	{
		currentXBoard = 0;
	}
	else if (pos == 1 || pos == 4 || pos == 7)
	{
		currentXBoard = 1;
	}
	else if (pos == 2 || pos == 5 || pos == 8)
	{
		currentXBoard = 2;
	}
	if (pos == 0 || pos == 1 || pos == 2)
	{
		currentYBoard = 0;
	}
	else if (pos == 3 || pos == 4 || pos == 5)
	{
		currentYBoard = 1;
	}
	else if (pos == 6 || pos == 7 || pos == 8)
	{
		currentYBoard = 2;
	}

	playerTurn = 2;

	PlacePiece();
}



void Move(int dir) {
	/*
		Input directions:

		1 - UP
		2 - DOWN
		3 - LEFT
		4 - RIGHT
	
	*/

	int Ydiff = 2;
	int Xdiff = 4;

	//Move to a spot on the board

	switch (dir)
	{
	case 1: {
		if (currentY > minY) {
			currentYBoard -= 1;
			currentY -= Ydiff;
			Console_gotoXY(currentX, currentY);
		}
		break;
	}
	case 2: {
		if (currentY < maxY) {
			currentYBoard += 1;
			currentY += Ydiff;
			Console_gotoXY(currentX, currentY);
		}
		break;
	}
	case 3: {
		if (currentX > minX) {
			currentXBoard -= 1;
			currentX -= Xdiff;
			Console_gotoXY(currentX, currentY);
		}
		break;
	}
	case 4: {
		if (currentX < maxX) {
			currentXBoard += 1;
			currentX += Xdiff;
			Console_gotoXY(currentX, currentY);
		}
		break;
	}
	default:
		break;
	}
}

void GAMEOVERSCREEN() { //Tell player that game is over and display winner
	Console_Clear();
	string default_color = "color 07"; //white on black
	string m_color = "color 20"; //black on green
	if (winner == -1) {
		m_color = "color 40"; //black on red
	}

	for (size_t i = 0; i < 3; i++) //Flash the screen different colors
	{
		system(m_color.c_str());
		Beep(700, 50);
		system(default_color.c_str());
		Beep(1000, 50);
		system(m_color.c_str());
		Beep(1300, 50);
		system(default_color.c_str());
		Beep(1600, 50);
		system(m_color.c_str());
		Beep(1900, 50);
		system(default_color.c_str());
		Beep(2300, 50);
		system(m_color.c_str());
	}
	Console_Clear();
	Console_gotoXY(0, 0);
	switch (winner)
	{
	case 1: {
		cout << " -= " << player1_name << " Wins! =- " << endl;
		break;
	}
	case 2: {
		cout << " -= "<< player2_name << " Wins! =- " << endl;
		break;
	}
	case -1: {
		cout << " -= Tie =- " << endl;
		cout << "GameOver!" << endl;
		break;
	}
	default: {
		cout << "GameOver!" << endl;
		break;
	}
	}
	Console_gotoXY(0, 3);
	DrawGrid(m_grid_state);
	Console_gotoXY(0, 10);
	system("pause"); //wait for user to continue
	system(default_color.c_str());
}

//Initalise variables
void GameINIT(bool pvpMode){ 
	isPlayer2AI = false;
	count1 = 0;
	Console_Clear();
	difficultyLevel = 0;
	winner = 0;
	keyPressed = 0;
	playerTurn = 1;
	GameOver = false;
	DEBUG_MODE = false;
	PlacedPiece = false;
	TurnOver = true;
	currentXBoard = 0;
	currentYBoard = 0;
	currentX = 2;
	currentY = 4;
	fill(begin(m_grid_state), end(m_grid_state), 0);

	cout << "Player 1's Name: ";
	cin >> player1_name;
	if (pvpMode) {
		cout << "Player 2's Name: ";
		cin >> player2_name;
		isPlayer2AI = false;
	}
	else {
		srand((unsigned int)time(NULL));
		int randomname = rand() % AI_names.size();
		player2_name = AI_names[randomname];
		cout << "AI's Name: " << player2_name << endl;
		isPlayer2AI = true;
		while (true) {
			cout << "Difficult Level [1-9]: ";
			cin >> difficultyLevel;
			if (difficultyLevel == 1 || difficultyLevel == 2 || difficultyLevel == 3 || difficultyLevel == 4 || difficultyLevel == 5 || difficultyLevel == 6 || difficultyLevel == 7 || difficultyLevel == 8 || difficultyLevel == 9) {
				break;
			}
		}
	}
	GameOn(pvpMode);
}

//MAIN GAME LOOP
void GameOn(bool pvpMode) {
	Console_Clear();
	cout << "-= " << player1_name << " vs. " << player2_name << " =-" << endl << endl;
	while (!GameOver)
	{
		if (TurnOver)
		{
			TurnOver = false;
			CheckForWin(2);
			if (GameOver) {
				break;
			}
			Console_gotoXY(0, 19);
			cout << "                                                    "; //clear name area
			Console_gotoXY(0, 19);
			switch (playerTurn)
			{
			case 1:
			{
				cout << player1_name << "'s Turn";
				break;
			}
			case 2:
			{
				cout << player2_name << "'s Turn";
				break;
			}
			default:
				break;
			}
			Console_gotoXY(0, 3);
			DrawGrid(m_grid_state);
			Console_gotoXY(currentX, currentY);

			if (playerTurn == 1 || (playerTurn == 2 && !isPlayer2AI)) { //Human Turn

				keyPressed = NULL;
				keyPressed = _getch();

				if (keyPressed == 224) { //Stop Arrow Keys from inputing twice and breaking the game
					keyPressed = _getch();
				}

				if (keyPressed == 27) { //DEBUG MODE toggled with esc
					DEBUG_MODE = !DEBUG_MODE;
				}

				Beep(1000, 100);

				if (keyPressed == 119 || keyPressed == 87 || keyPressed == 72) { //Up keys
					Move(1);
				}

				else if (keyPressed == 80 || keyPressed == 115 || keyPressed == 83) { //Down keys
					Move(2);
				}

				else if (keyPressed == 97 || keyPressed == 65 || keyPressed == 75) { //Left keys
					Move(3);
				}

				else if (keyPressed == 100 || keyPressed == 68 || keyPressed == 77) { //Right keys
					Move(4);
				}

				else if (keyPressed == 13 || keyPressed == 101 || keyPressed == 69 || keyPressed == 32) { //Enter, e, E, Space
					PlacePiece();
				}

			}

			else { //AI Turn
				AI_Move();
			}

			if (DEBUG_MODE) { //displays dev info (toggle with esc key)
				Console_gotoXY(0, 20);
				cout << "                                                   ";
				Console_gotoXY(0, 20);
				cout << "[DEBUG] KEY: " << keyPressed << "  playerTurn: " << playerTurn << endl << "X: " << currentX << " Y: " << currentY;
			}

			if (PlacedPiece == true) { //turn is over
				if (playerTurn == 1) {
					playerTurn = 2;
				}
				else if (playerTurn == 2) {
					playerTurn = 1;
				}
				currentX = 2;
				currentY = 4;
				currentXBoard = 0;
				currentYBoard = 0;
				PlacedPiece = false;
			}
			TurnOver = true;
		}
	}
	GAMEOVERSCREEN(); //game is over
}
