/*Main program*/

#include "stdafx.h"
#include "TicTacToeUI.h"
#include <stdio.h>
#include "paths.h"

#define MAX_LOADSTRING 100
#define BUTTON0 300
int ids[] = {	300, 
				301,
				302,
				303,
				304,
				305,
				306,
				307,
				308 };
HWND handles[9];
HWND turnHandle;

#define STATICTEXT 210
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int	  currentTurn = 1;
int   turns = 5;
int noOfTurns = 0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				CreateBoard(HWND hWnd, HINSTANCE hInstance);
void				NextTurn(HWND hWnd, HINSTANCE hInstance, int controlId);
Board				getBoard();
void				setBoard( Board board);
void				makeCPUMove();
void				ResetGame();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TICTACTOEUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOEUI));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOEUI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TICTACTOEUI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & WS_THICKFRAME & WS_DLGFRAME,
      CW_USEDEFAULT, 0, 150, 250, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		
		if ( wmEvent == STN_CLICKED)
		{
			if (wmId >= 300 && wmId <=309 )
			{
				NextTurn( hWnd, hInst, wmId);
				makeCPUMove();
			}
		}
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_CREATE:
		CreateBoard( hWnd, hInst);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		HPEN hLinePen, hPenOld;
		COLORREF qLineColor;
		qLineColor = RGB(0, 0, 255);
		hLinePen = CreatePen( PS_SOLID, 9, qLineColor);
		hPenOld = (HPEN) SelectObject( hdc, hLinePen);

		MoveToEx( hdc, 45, 50, NULL);
		LineTo( hdc, 45, 190);

		SelectObject( hdc, hPenOld);
		DeleteObject( hLinePen);

		//Line 2
		qLineColor = RGB(0, 0, 255);
		hLinePen = CreatePen( PS_SOLID, 9, qLineColor);
		hPenOld = (HPEN) SelectObject( hdc, hLinePen);

		MoveToEx( hdc, 95, 50, NULL);
		LineTo( hdc, 95, 190);

		SelectObject( hdc, hPenOld);
		DeleteObject( hLinePen);

		//Line 3
		qLineColor = RGB(0, 0, 255);
		hLinePen = CreatePen( PS_SOLID, 9, qLineColor);
		hPenOld = (HPEN) SelectObject( hdc, hLinePen);

		MoveToEx( hdc, 3, 95, NULL);
		LineTo( hdc, 140, 95);

		SelectObject( hdc, hPenOld);
		DeleteObject( hLinePen);

		//Line 4
		qLineColor = RGB(0, 0, 255);
		hLinePen = CreatePen( PS_SOLID, 9, qLineColor);
		hPenOld = (HPEN) SelectObject( hdc, hLinePen);

		MoveToEx( hdc, 3, 145, NULL);
		LineTo( hdc, 140, 145);

		SelectObject( hdc, hPenOld);
		DeleteObject( hLinePen);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void CreateBoard(HWND hWnd, HINSTANCE hInstance)
{
	HFONT hNewFont = CreateFont(40,
			                  40,
						      0,
						      0,
						      FW_NORMAL,
						      0,
						      0,
						      0,
						      ANSI_CHARSET,
						      OUT_DEFAULT_PRECIS,
						      CLIP_DEFAULT_PRECIS,
						      DEFAULT_QUALITY,
						      DEFAULT_PITCH | FF_DONTCARE,
						      "Courier New");

	turnHandle = CreateWindowEx(0,	/* more or ''extended'' styles */
					TEXT("STATIC"),                         			/* GUI ''class'' to create */
					TEXT("Your Turn !"),						/* GUI caption */
					WS_CHILD|WS_VISIBLE | WS_EX_TRANSPARENT | SS_CENTER | SS_NOTIFY,   /* control styles separated by | */
					10,                          			/* LEFT POSITION */
					10,                          			/* TOP POSITION  */
					120,                                     				/* WIDTH OF CONTROL */
					20,                                     				/* HEIGHT OF CONTROL */
					hWnd,                                   			/* Parent window handle */
					(HMENU)STATICTEXT,                  		/* control''s ID for WM_COMMAND */
					hInstance,                              			/* application instance */
					NULL);

	for(int button=0; button<9; button++) {
			char buffer[2];
			sprintf( buffer, "%d\0", button ); 				/* Create button caption */
			handles[button] = CreateWindowEx(0,						/* more or ''extended'' styles */
                         		TEXT("STATIC"),                         			/* GUI ''class'' to create */
                         		TEXT(""),						/* GUI caption */
                     			WS_CHILD|WS_VISIBLE|SS_CENTER | SS_NOTIFY,    /* control styles separated by | */
                     			50*(button%3) ,                          			/* LEFT POSITION */
                     			50 + 50*(button/3),                          			/* TOP POSITION  */
                     			40,                                     				/* WIDTH OF CONTROL */
                     			40,                                     				/* HEIGHT OF CONTROL */
                     			hWnd,                                   			/* Parent window handle */
                         		//(HMENU)BUTTON0+button,                  		/* control''s ID for WM_COMMAND */
								(HMENU)ids[button],
                         		hInstance,                              			/* application instance */
                         		NULL);


			SendMessage( handles[button],
				       WM_SETFONT,
					   (WPARAM) hNewFont,
					   MAKELPARAM(TRUE, 0));
		}
}
//currentTurn
//
void NextTurn(HWND hWnd, HINSTANCE hInstance, int controlId)
{
	char param[5];
	char stringForTurn[64];
	int  count;

	count = SendMessage(handles[controlId - 300], WM_GETTEXT, 4, (LPARAM) param);
	if ( count == 0 )
	{
		if ( currentTurn == 1 )
		{
			param[0] = 'O';
			param[1] = '\0';
			currentTurn = 1;
		}
		else
		{
			param[0] = 'X';
			param[1] = '\0';
			currentTurn = 1;
		}

		sprintf( stringForTurn, "Turn of player %d", currentTurn);
		
		if ( currentTurn == 1 )
		{
			sprintf( stringForTurn, "Your Turn !");
		}

		SendMessage(handles[controlId - 300], WM_SETTEXT, 2, (LPARAM) param);

		SendMessage( turnHandle, WM_SETTEXT, strlen(stringForTurn) + 1, (LPARAM) stringForTurn);

		return;
	}

	MessageBox( NULL, "Invalid move try empty box.", "", MB_ICONWARNING);
}

Board getBoard()
{
	char param[5];
	int  count;
	Board board;
	int index =0 , i ,j;

	for ( i = 0 ; i < 3; i++ )
	{
		for ( j = 0 ; j < 3 ; j++ )
		{
			count = SendMessage(handles[index], WM_GETTEXT, 4, (LPARAM) param);
			if ( param[0] == 'O' )
			{
				board.setValue( i, j, Player1 );
			}
			else if ( param[0] == 'X' )
			{
				board.setValue( i, j, Player2 );
			}
			index++;
		}
	}

	board.verifyWinningState();

	return board;
}

void setBoard( Board board)
{
	char param[5];
	int index =0 , i ,j;

	for ( i = 0 ; i < 3; i++ )
	{
		for ( j = 0 ; j < 3 ; j++ )
		{
			Player player = (Player)board.getValue( i, j );

			
			if ( player == Player1 )
			{
				param[0] = 'O';
				param[1] = '\0';
				
			}
			else if ( player == Player2  )
			{
				param[0] = 'X';
				param[1] = '\0';
			}
			else
			{
				param[0] = '\0';
				param[1] = '\0';
			}

			SendMessage(handles[index], WM_SETTEXT, 2, (LPARAM) param);
			index++;
		}
	}
}

void makeCPUMove()
{
	Moves		moves;
	Board		board = getBoard();
	int			msgBoxResult;
	Node		rootNode( board );
	Children	child[8];
	Paths		paths;
	vector<vector<Node>> winningPaths;
	int			i = 0;

	moves.generateMoves( Player2, &rootNode, child, turns);
	
	while ( child[i].size() > 0 )
	{
		i++;
	}
	
	if ( i == 0 )
	{
		msgBoxResult = MessageBox( NULL, "No one wins!!! Do you want to start a new game", "", MB_YESNO);
		if ( msgBoxResult == IDYES)
		{
			ResetGame();
			return;
		}
		else
		{
			exit(0);
		}
	}

	paths.findBestPaths( Player2, child, i, true, &winningPaths);

	if (winningPaths.size() == 0)
	{
		msgBoxResult = MessageBox( NULL, "You win!!! Do you want to start a new game", "", MB_YESNO);
		if ( msgBoxResult == IDYES)
		{
			ResetGame();
			return;
		}
		else
		{
			exit(0);
		}
	}

	Node node = winningPaths[0][1];
	Board nextMove = node.getBoard();

	setBoard( nextMove);
	if (turns >	1 )
		turns= 1;

	if ( nextMove.getWinningStatePlayer1())
	{
		msgBoxResult = MessageBox( NULL, "You win!!! Do you want to start a new game", "", MB_YESNO);
		if ( msgBoxResult == IDYES)
		{
			ResetGame();
			return;
		}
		else
		{
			exit(0);
		}
	}
	else if ( nextMove.getWinningStatePlayer2())
	{
		msgBoxResult = MessageBox( NULL, "I win!!! Do you want to start a new game", "", MB_YESNO);
		if ( msgBoxResult == IDYES)
		{
			ResetGame();
			return;
		}
		else
		{
			exit(0);
		}
	}
}

void ResetGame()
{
	char param[5];
	char stringForTurn[64];
	
	currentTurn = 1;
	turns = 5;
	param[0] = '\0';
	for (int i = 0 ; i < 9 ; i++)
	{
		SendMessage(handles[i], WM_SETTEXT, 1, (LPARAM) param);
	}

	sprintf( stringForTurn, "Your Turn !");


	SendMessage( turnHandle, WM_SETTEXT, strlen(stringForTurn) + 1, (LPARAM) stringForTurn);

}
