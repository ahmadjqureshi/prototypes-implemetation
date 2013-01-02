/*
The Board class represents TicTacToe board.
*/

#include <vector>

using namespace std;

#ifndef _BOARD_H_
#define _BOARD_H_
/*
Board representation
[0] [1] [2]
[3] [4] [5]
[6] [7] [8]
*/

enum BoardSquare
{
	Empty	= 0,
	Player1 = 1, //Consider it as Min node of Minimax algo
	Player2		 //Consider it as Max node of Minimax algo
};

enum Turn
{
	Player1Turn = 1,
	Player2Turn
};

class Board
{
public:
	Board() :	m_winningStatePlayer1( false ),
				m_winningStatePlayer2( false ),
				m_heuristicsPlayer1(0),
				m_heuristicsPlayer2(0)
	{
		memset ( m_board, 0, sizeof(BoardSquare) * 9 );
	}

	void		setValue( int index, BoardSquare squareVal) { m_board[index] = squareVal; }
	BoardSquare	getValue( int index) { return m_board[index]; }

	bool		getWinningStatePlayer1() { return m_winningStatePlayer1; }

	bool		getWinningStatePlayer2() { return m_winningStatePlayer2; }

	int			getPlayer1Heuristics() { return m_heuristicsPlayer1; }

	int			getPlayer2Heuristics() { return m_heuristicsPlayer2; }

	void		verifyWinningState();

private:
	BoardSquare		m_board[9];
	bool			m_winningStatePlayer1;
	bool			m_winningStatePlayer2;
	int				m_heuristicsPlayer1;
	int				m_heuristicsPlayer2;
};

typedef vector<Board> BoardCollection;

#endif
