#include "board.h"

void Board::verifyWinningState()
{
	int i, j, countForPlayer1 = 0, countForPlayer2 = 0, foundPlayer1 = false, foundPlayer2 =false, oldHeuristicsPlayer1, oldHeuristicsPlayer2;
	oldHeuristicsPlayer1 = m_heuristicsPlayer1;
	oldHeuristicsPlayer2 = m_heuristicsPlayer2;
	m_heuristicsPlayer1 = 0;
	m_heuristicsPlayer2 = 0;

	//check vertical lines for winning state
	for ( i = 0 ; i < 3 ; i++ )
	{
		if (	( m_board[i] == Player1) &&
				( m_board[i + 3] == Player1) &&
				( m_board[i + 6] == Player1) )
		{
			m_heuristicsPlayer1 = -1000;
			m_winningStatePlayer1 = true;
			return;
		}

		if (	( m_board[i] == Player2) &&
				( m_board[i + 3] == Player2) &&
				( m_board[i + 6] == Player2) )
		{
			m_heuristicsPlayer2 = 1000;
			m_winningStatePlayer2 = true;
			return;
		}
	}

	//check horizontal lines
	for ( i = 0 ; i < 8 ; i+=3 )
	{
		if (	( m_board[i] == Player1) &&
				( m_board[i + 1] == Player1) &&
				( m_board[i + 2] == Player1) )
		{
			m_heuristicsPlayer1 = -1000;
			m_winningStatePlayer1 = true;
			return;
		}

		if (	( m_board[i] == Player2) &&
				( m_board[i + 1] == Player2) &&
				( m_board[i + 2] == Player2) )
		{
			m_heuristicsPlayer2 = 1000;
			m_winningStatePlayer2 = true;
			return;
		}
	}

	// check first diagonals
	if ( ( m_board[0] == Player1) &&
		 ( m_board[4] == Player1) &&
		 ( m_board[8] == Player1) )
	{
		m_heuristicsPlayer1 = -1000;
		m_winningStatePlayer1 = true;
		return;
	}

	if ( ( m_board[0] == Player1) &&
		 ( m_board[4] == Player1) &&
		 ( m_board[8] == Player1) )
	{
		m_heuristicsPlayer2 = 1000;
		m_winningStatePlayer2 = true;
		return;
	}

	//check second diagonal
	if ( ( m_board[2] == Player1) &&
		 ( m_board[4] == Player1) &&
		 ( m_board[6] == Player1) )
	{
		m_heuristicsPlayer1 = -1000;
		m_winningStatePlayer1 = true;
		return;
	}

	if ( ( m_board[2] == Player2) &&
		 ( m_board[4] == Player2) &&
		 ( m_board[6] == Player2) )
	{
		m_heuristicsPlayer2 = 1000;
		m_winningStatePlayer2 = true;
		return;
	}

	//find two consective vertically

	for ( i = 0 ; i < 3; i++)
	{
		countForPlayer1 = 0;
		countForPlayer2 = 0;
		for ( j = i ; j < 8 ; j = j + 3 )
		{
			if ( m_board[j] == Player1)
			{
				countForPlayer1++;
			}
			else if ( m_board[j] == Player2)
			{
				countForPlayer2++;
			}
		}

		if ( countForPlayer1 == 2 && countForPlayer2 == 0 )
		{
			m_heuristicsPlayer1 += -100;
		}
		else if ( countForPlayer1 == 1 && countForPlayer2 == 2 )
		{
			m_heuristicsPlayer1 += -110;
		}
		
		if ( countForPlayer1 == 0 && countForPlayer2 == 2 )
		{
			m_heuristicsPlayer2 += 100;
		}
		else if ( countForPlayer1 == 2 && countForPlayer2 == 1 )
		{
			m_heuristicsPlayer2 += 110;
		}
	}

	//find two consective horizontally

	for ( i = 0 ; i < 8; i = i + 3 )
	{
		countForPlayer1 = 0;
		countForPlayer2 = 0;
		for ( j = i ; j < i + 3 ; j++ )
		{
			if ( m_board[j] == Player1)
			{
				countForPlayer1++;
			}
			else if ( m_board[j] == Player2)
			{
				countForPlayer2++;
			}
		}

		if ( countForPlayer1 == 2 && countForPlayer2 == 0 )
		{
			m_heuristicsPlayer1 += -100;
		}
		else if ( countForPlayer1 == 1 && countForPlayer2 == 2 )
		{
			m_heuristicsPlayer1 += -110;
		}
		
		if ( countForPlayer1 == 0 && countForPlayer2 == 2 )
		{
			m_heuristicsPlayer2 += 100;
		}
		else if ( countForPlayer1 == 2 && countForPlayer2 == 1 )
		{
			m_heuristicsPlayer2 += 110;
		}
	}

	//find two consective in first diagonal
	countForPlayer1 = 0;
	countForPlayer2 = 0;
	for ( i = 0 ; i < 9 ; i = i + 4)
	{
		if ( m_board[i] == Player1)
		{
			countForPlayer1++;
		}
		else if ( m_board[i] == Player2)
		{
			countForPlayer2++;
		}
	}

	if ( countForPlayer1 == 2 && countForPlayer2 == 0 )
	{
		m_heuristicsPlayer1 += -100;
	}
	else if ( countForPlayer1 == 1 && countForPlayer2 == 2 )
	{
		m_heuristicsPlayer1 += -110;
	}
	
	if ( countForPlayer1 == 0 && countForPlayer2 == 2 )
	{
		m_heuristicsPlayer2 += 100;
	}
	else if ( countForPlayer1 == 2 && countForPlayer2 == 1 )
	{
		m_heuristicsPlayer2 += 110;
	}

	//find two consective in second diagonal
	countForPlayer1 = 0;
	countForPlayer2 = 0;
	for ( i = 2 ; i < 7 ; i = i + 2)
	{
		if ( m_board[i] == Player1)
		{
			countForPlayer1++;
		}
		else if ( m_board[i] == Player2)
		{
			countForPlayer2++;
		}
	}

	if ( countForPlayer1 == 2 && countForPlayer2 == 0 )
	{
		m_heuristicsPlayer1 += -100;
	}
	else if ( countForPlayer1 == 1 && countForPlayer2 == 2 )
	{
		m_heuristicsPlayer1 += -110;
	}
	
	if ( countForPlayer1 == 0 && countForPlayer2 == 2 )
	{
		m_heuristicsPlayer2 += 100;
	}
	else if ( countForPlayer1 == 2 && countForPlayer2 == 1 )
	{
		m_heuristicsPlayer2 += 110;
	}

}
