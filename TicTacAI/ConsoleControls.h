#pragma once
#include <windows.h> 

void Console_gotoXY(int x, int y);

void Console_Resize(HWND m_console, RECT m_rect, int x, int y);

void Console_Clear();
