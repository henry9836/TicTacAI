#include <iostream>
#include <array>
#include "ConsoleControls.h"
#include "GridControl.h"
using namespace std;

void DrawGrid(std::array<int, 9>& m_grid_state) { //Draw the game grid in the console

	//DRAWS EMPTY GRID

	for (int i = 0; i < 3; i++)
	{
		cout << "+---+---+---+" << endl;
		cout << "|   |   |   |" << endl;
	}
	cout << "+---+---+---+" << endl;

	//DRAWS TOKENS IN GRID

	for (int i = 0; i < 9; i++)
	{
		if (m_grid_state[i] != 0) {
			if (m_grid_state[i] == 1) {
				switch (i)
				{
				case 0: {
					Console_gotoXY(2, 4);
					cout << "X";
					break;
				}
				case 1: {
					Console_gotoXY(6, 4);
					cout << "X";
					break;
				}
				case 2: {
					Console_gotoXY(10, 4);
					cout << "X";
					break;
				}
				case 3: {
					Console_gotoXY(2, 6);
					cout << "X";
					break;
				}
				case 4: {
					Console_gotoXY(6, 6);
					cout << "X";
					break;
				}
				case 5: {
					Console_gotoXY(10, 6);
					cout << "X";
					break;
				}
				case 6: {
					Console_gotoXY(2, 8);
					cout << "X";
					break;
				}
				case 7: {
					Console_gotoXY(6, 8);
					cout << "X";
					break;
				}
				case 8: {
					Console_gotoXY(10, 8);
					cout << "X";
					break;
				}
				default: {
					cout << "[WARN] Unknown i in DrawGrid [i=" << i << "]" << endl;
					break;
				}
				}
			}
			else if (m_grid_state[i] == 2) {
				switch (i)
				{
				case 0: {
					Console_gotoXY(2, 4);
					cout << "O";
					break;
				}
				case 1: {
					Console_gotoXY(6, 4);
					cout << "O";
					break;
				}
				case 2: {
					Console_gotoXY(10, 4);
					cout << "O";
					break;
				}
				case 3: {
					Console_gotoXY(2, 6);
					cout << "O";
					break;
				}
				case 4: {
					Console_gotoXY(6, 6);
					cout << "O";
					break;
				}
				case 5: {
					Console_gotoXY(10, 6);
					cout << "O";
					break;
				}
				case 6: {
					Console_gotoXY(2, 8);
					cout << "O";
					break;
				}
				case 7: {
					Console_gotoXY(6, 8);
					cout << "O";
					break;
				}
				case 8: {
					Console_gotoXY(10, 8);
					cout << "O";
					break;
				}
				default: {
					cout << "[WARN] Unknown i in DrawGrid [i=" << i << "]" << endl;
					break;
				}
				}
			}
		}

	}
}