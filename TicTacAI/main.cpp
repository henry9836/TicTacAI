#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "ConsoleControls.h"
#include "main.h"
#include "GameCtrl.h"

using namespace std;
/*
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
|   |   |   |
+---+---+---+
*/
int mainmenu() {
	Console_Clear();
	for (int i = 0; i < 3; i++)
	{
		cout << "+---+---+---+" << endl;
		cout << "|   |   |   |" << endl;
	}
	cout << "+---+---+---+" << endl;
	
	// INTRO ANIMATION
	Console_gotoXY(6, 3);
	cout << "X";
	Beep(450, 200);
	Console_gotoXY(2, 1);
	cout << "O";
	Beep(450, 200);
	Console_gotoXY(10, 5);
	cout << "X";
	Beep(450, 200);
	Console_gotoXY(6, 1);
	cout << "O";
	Beep(450, 200);
	Console_gotoXY(10, 1);
	cout << "X";
	Beep(450, 200);
	Console_gotoXY(10, 3);
	cout << "O";
	Beep(450, 200);
	Console_gotoXY(2, 5);
	cout << "X";
	Beep(450, 200);

	Beep(700, 50);
	Beep(1000, 50);
	Beep(1300, 50);
	Beep(1600, 50);
	Beep(1900, 50);

	Console_gotoXY(0, 9);
	cout << "TicTacToe" << endl << "by Henry Oliver" << endl << "Please Select A Mode:" << endl << "1. Player vs. AI" << endl << "2. Player vs. Player" << endl << "99. Exit" << endl;
	
	int choice;

	cin >> choice;

	switch (choice)
	{
	case 1: {
		GameINIT(false); //PvE
		break;
	}
	case 2: {
		GameINIT(true); //PvP
		break;
	}
	case 99: { //Quit
		return 99;
		break;
	}
	default: {
		//USER INPUT IS WRONG
		while (choice != 1 || choice != 2 || choice != 99) {
			cout << "Invalid Option Please Input either a 1,2 or 99: ";
			cin >> choice;
			if (choice == 1 || choice == 2) {
				switch (choice)
				{
				case 1: {
					GameINIT(false); //PvE
					break;
				}
				case 2: {
					GameINIT(true); //PvP
					break;
				}
				case 99: { //Quit
					return 99;
					break;
				}
				default:
					break;
				}
				break;
			}
		}
		break;
	}
	}

	return 0;
}

int main() {

	HWND m_console = GetConsoleWindow();
	RECT m_rect;

	GetWindowRect(m_console, &m_rect);
	Console_Resize(m_console, m_rect, 550, 550);

	while (true) //menu loop
	{
		int tmp = mainmenu(); //start main menu
		if (tmp == 99) {
			break;
		}
	}

	cout << "Closing Program..." << endl;

	return 0;
}