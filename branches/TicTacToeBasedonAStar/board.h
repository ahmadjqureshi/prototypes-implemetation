#ifndef _BOARD_H_
/*

This class represents the board of TicTacToe.

[x][y]

[0][0]	[0][1]	[0][2]
[1][0]	[1][1]	[1][2]
[2][0]	[2][1]	[2][2]
*/

#include <stdio.h>
#include <vector>

using namespace std;

class Board;

typedef vector<Board> BoardCollection;

enum Player
{
	Player1 = 1,
	Player2
};

#define TwoConsective 2
#define BothTwoConsective 10
#define SaveFromLossing 1

class Board
{
public:
	Board() : m_winningStatePlayer1(false), 
			  m_winningStatePlayer2(false), 
			  m_heuristicsPlayer1(9999), 
			  m_heuristicsPlayer2(9999), 
			  m_blockState(false)
	{
		memset ( m_board, 0, sizeof(unsigned int) * 9 );
	}

	bool setValue(unsigned int x, unsigned int y, Player value)
	{
		if ( ( x >= 3 && x < 0 ) ||
			 ( y >= 3 && y < 0 ) )
		{
			 return false;
		}	  

		m_board[x][y] = value;

		return true;
	}

	int getValue( unsigned int x, unsigned int y )
	{
		return m_board[x][y];
	}

	bool getWinningStatePlayer1() { return m_winningStatePlayer1; }

	bool getWinningStatePlayer2() { return m_winningStatePlayer2; }

	unsigned int getPlayer1Heuristics() { return m_heuristicsPlayer1; }

	unsigned int getPlayer2Heuristics() { return m_heuristicsPlayer2; }

	void verifyWinningState()
	{
		int i, j, countForPlayer1 = 0, countForPlayer2 = 0, foundPlayer1 = false, foundPlayer2 =false, oldHeuristicsPlayer1;
		oldHeuristicsPlayer1 = m_heuristicsPlayer1;

		/*Horizontal and vertical lines*/

		for ( i = 0 ; i < 3 ; i++ )
		{
			if ( (m_board[i][0] == Player1 ) && (m_board[i][1] == Player1 ) && (m_board[i][2] == Player1 ) )
			{
				m_winningStatePlayer1 = true;
				m_heuristicsPlayer1   = 0;
				return;
			}
			else if ( (m_board[i][0] == Player2 ) && (m_board[i][1] == Player2 ) && (m_board[i][2] == Player2 ) )
			{
				m_winningStatePlayer2 = true;
				m_heuristicsPlayer2   = 0;
				return;
			}

			if ( (m_board[0][i] == Player1 ) && (m_board[1][i] == Player1 ) && (m_board[2][i] == Player1 ) )
			{
				m_winningStatePlayer1 = true;
				m_heuristicsPlayer1   = 0;
				return;
			}
			else if ( (m_board[0][i] == Player2 ) && (m_board[1][i] == Player2 ) && (m_board[2][i] == Player2 ) )
			{
				m_winningStatePlayer2 = true;
				m_heuristicsPlayer2   = 0;
				return;
			}
		}
		
		/*Diagonals*/

		if ( (m_board[0][2] == Player1 ) && (m_board[1][1] == Player1 ) && (m_board[2][0] == Player1 ) )
		{
			m_winningStatePlayer1 = true;
			m_heuristicsPlayer1   = 0;
			return;
		}
		else if ( (m_board[0][2] == Player2 ) && (m_board[1][1] == Player2 ) && (m_board[2][0] == Player2 ) )
		{
			m_winningStatePlayer2 = true;
			m_heuristicsPlayer2	  = 0;
			return;
		}

		if ( (m_board[0][0] == Player1 ) && (m_board[1][1] == Player1 ) && (m_board[2][2] == Player1 ) )
		{
			m_winningStatePlayer1 = true;
			m_heuristicsPlayer1   = 0;
			return;
		}
		else if ( (m_board[0][0] == Player2 ) && (m_board[1][1] == Player2 ) && (m_board[2][2] == Player2 ) )
		{
			m_winningStatePlayer2 = true;
			m_heuristicsPlayer2   = 0;
			return;
		}

		//Horizontal two consectives
		for ( i = 0 ; i < 3 ; i++ )
		{
			countForPlayer1 = 0;
			countForPlayer2 = 0;
			for ( j = 0 ; j < 3 ; j++ )
			{
				if ( m_board[i][j] == Player1 )
				{
					countForPlayer1++;
					
				}

				if ( m_board[i][j] == Player2 )
				{
					countForPlayer2++;
				}
			}

			if ( countForPlayer1 == 2 && countForPlayer2 == 0)
			{
				m_heuristicsPlayer1 = 2; 
				foundPlayer1 = true;
			}
			
			if ( countForPlayer1 == 0  && countForPlayer2 == 2)
			{
				m_heuristicsPlayer2 = 2; 
				foundPlayer2 = true;
			}
		}

		//vertical two consectives
		for ( i = 0 ; i < 3 ; i++ )
		{
			countForPlayer1 = 0;
			countForPlayer2 = 0;
			for ( j = 0 ; j < 3 ; j++ )
			{
				if ( m_board[j][i] == Player1 )
				{
					countForPlayer1++;
				}

				if ( m_board[j][i] == Player2 )
				{
					countForPlayer2++;
				}
			}

			if ( countForPlayer1 == 2 && countForPlayer2 == 0)
			{
				m_heuristicsPlayer1 = 2; 
				foundPlayer1		= true;
			}
			
			if ( countForPlayer1 == 0 && countForPlayer2 == 2)
			{
				m_heuristicsPlayer2 = 2;
				foundPlayer2		= true;
			}
		}

		//Diagonal 1
		countForPlayer1 = 0;
		countForPlayer2 = 0;

		for ( i = 0 , j =2; i < 3 ; i++, j--)
		{
			
			if ( m_board[j][i] == Player1 )
			{
				countForPlayer1++;
			}

			if ( m_board[j][i] == Player2 )
			{
				countForPlayer2++;
			}
		}

		if ( countForPlayer1 == 2 && countForPlayer2 == 0)
		{
			m_heuristicsPlayer1 = 2; 
			foundPlayer1 = true;
		}
			
		if ( countForPlayer1 == 0 && countForPlayer2 == 2)
		{
			m_heuristicsPlayer2 = 2; 
			foundPlayer2 = true;
		}

		//Diagonal 2
		countForPlayer1 = 0;
		countForPlayer2 = 0;

		for ( i = 0 ; i < 3 ; i++)
		{
			
			if ( m_board[i][i] == Player1 )
			{
				countForPlayer1++;
			}

			if ( m_board[i][i] == Player2 )
			{
				countForPlayer2++;
			}
		}
		
		if ( countForPlayer1 == 2 && countForPlayer2 == 0)
		{
			m_heuristicsPlayer1 = 2; 
			foundPlayer1 = true;
		}
			
		if ( countForPlayer1 == 0 && countForPlayer2 == 2)
		{
			m_heuristicsPlayer2 = 2;
			foundPlayer2 = true;
		}

		if ( foundPlayer1  &&  foundPlayer2 )
		{
			m_heuristicsPlayer1 = 999 ;
			m_heuristicsPlayer2 = 999 ;
			return;
		}
		
		if ( !foundPlayer1 )
		{
			m_heuristicsPlayer1 = 9999;	
		}

		//Save from lossing player 2
		if ( oldHeuristicsPlayer1 < m_heuristicsPlayer1 )
		{
			m_heuristicsPlayer2 = 1;
			m_blockState =true;
		}
}

private:
	unsigned int	m_board[3][3];
	bool			m_winningStatePlayer1;
	bool			m_winningStatePlayer2;
	bool			m_blockState;
	unsigned int	m_heuristicsPlayer1;
	unsigned int	m_heuristicsPlayer2;

};



#endif
