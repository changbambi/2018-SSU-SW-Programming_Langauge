#include "StdAfx.h"
#include "GameBoard.h"

/**
�� �� : GameBoard()
�� �� : GameBoard Ŭ������ ������, ������ �������,
���� �� ���� �迭�� �������� �޸� �Ҵ�����
*/
GameBoard::GameBoard()
{
	preMoves = new Position[16];
	board = new char*[4];

	for (int i = 0; i<4; i++)
	{
		board[i] = new char[4];
	}
};

/**
�� �� : GameBoard(const GameBoard& copy)
�� �� : ���� �����ڷν�, ��Ī�� �˻翡�� �������� �����Ҷ�,
���� �Ҵ��� ������ ���� ���縦 �� ���ְ� ����
*/
GameBoard::GameBoard(const GameBoard& copy)
{
	preMoves = new Position[16];
	board = new char*[4];

	for (int i = 0; i<4; i++)
	{
		board[i] = new char[4];
	}

	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			board[i][j] = copy.board[i][j];

	for (int i = 0; i<16; i++)
	{
		preMoves[i].x = copy.preMoves[i].x;
		preMoves[i].y = copy.preMoves[i].y;
	}

	moveCnt = copy.moveCnt;
	state = copy.state;
	playerCom = copy.playerCom;
	oppnentCom = copy.oppnentCom;
	//startLevel = copy.startLevel;
	Level = copy.Level;
};

/**
�� �� : GetBoardStat()
�� �� : ������ ���� ��ȯ
*/
int GameBoard::GetBoardStat()
{
	return state;
};

/**
�� �� : InitBoard(int startCom, int movedCnt, int nlevelA, int nlevelB)
�� �� : �ʱ�ȭ�� �ʿ��� ������ ���ڸ� �߽����� �������� �ʱ�ȭ���ִ� �Լ�
*/
void GameBoard::InitBoard(int startCom, int movedCnt, int nlevelC)
{
	moveCnt = movedCnt;		/* ��� ° ���� ���� */

	/*if (startCom == 0)		/* ���� ��ǻ�Ϳ� ��ǻ�� ������ ���� */
	//{
	//	starterCom = 'X';		oppnentCom = 'O';
	//	startLevel = nlevelA;	oppLevel = nlevelB;
	//}
	//else
	//{
	//	starterCom = 'O';		oppnentCom = 'X';
	//	startLevel = nlevelB;	oppLevel = nlevelA;
	//}
	playerCom = 'X';
	oppnentCom = 'O';
	Level = nlevelC;

	if (movedCnt == 0)		/* �ҷ��� �������� ���θ� �˻��ؼ� ������ �ʱ�ȭ */
	{
		for (int i = 0; i<4; i++)
			for (int j = 0; j<4; j++)
				board[i][j] = ' ';
	}
};

/**
�� �� : RandomMove(int preX, int preY)
�� �� : �����⸦ ���������� ������ ���Ҵ� ���� �ٸ����� ������ �����ϰ� ��ǥ����
*/
void GameBoard::RandomMove()
{
	int newX, newY;
	int preX, preY;
	bool overlap = true;
	srand(GetTickCount());

	UndoMove();
	preX = preMoves[moveCnt].x;
	preY = preMoves[moveCnt].y;

	while (overlap)
	{
		newX = rand() % 4;
		newY = rand() % 4;

		if (moveCnt <= 14)	/* �� ��ǥ�� 2�� �̻��϶� */
		{
			if ((newX != preX) && (newY != preY))	/* �������λ����� ��ǥ�� ������ǥ�� ���ϰ� */
				if (board[newX][newY] == ' ')		/* �ش� ��ǥ�� ����ִ� �������� �˻� */
					overlap = false;
		}
		else
		{
			if (board[newX][newY] == ' ')
				overlap = false;
		}
	}
	DoMove(newX, newY);
};

/**
�� �� : DoMove(int x, int y)
�� �� :	�Է¹��� ��ǥ������ �����ǿ� ���� ��
*/
void GameBoard::DoMove(int x, int y)
{
	if (moveCnt % 2 == 0)			/* ���� �������� �˻� */
		board[x][y] = 'X';
	else
		board[x][y] = 'O';

		preMoves[moveCnt].x = x;
		preMoves[moveCnt].y = y;

	moveCnt++; /* ���� ���� ���� ��Ŵ */
};

/**
�� �� : UndoMove()
�� �� : ���Ҵ� ���� �Ѵܰ� �������·� �������� �Լ�
*/
void GameBoard::UndoMove()
{
	moveCnt--;
	board[preMoves[moveCnt].x][preMoves[moveCnt].y] = ' ';
}

/**
�� �� : CheckState()
�� �� : ���� �������� ����, �����̰����, �������� �˻��ؼ� ���°��� �������ִ� �Լ�
*/
void GameBoard::CheckState()
{
	int i;

	for (i = 0; i<4; i++)				/* ���� ������ �˻� */
	{
		if (board[i][0] != ' ')
		{
			if ((board[i][0] == 'X') && (board[i][1] == 'X') && (board[i][2] == 'X') && (board[i][3] == 'X'))
			{
				state = STATE_WINP;
				return;
			}
			if ((board[i][0] == 'O') && (board[i][1] == 'O') && (board[i][2] == 'O') && (board[i][3] == 'O'))
			{
				state = STATE_WINC;
				return;
			}
		}
		if (board[0][i] != ' ')		/* ���� ������ �˻� */
		{
			if ((board[0][i] == 'X') && (board[1][i] == 'X') && (board[2][i] == 'X') && (board[3][i] == 'X'))
			{
				state = STATE_WINP;
				return;
			}
			if ((board[0][i] == 'O') && (board[1][i] == 'O') && (board[2][i] == 'O') && (board[3][i] == 'O'))
			{
				state = STATE_WINC;
				return;
			}
		}
	}

	if ((board[0][0] != ' ') && (board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] == board[3][3]))	/* ù��° �밢�� �˻� */
	{
		if (board[0][0] == 'X')
		{
			state = STATE_WINP;
			return;
		}
		else
		{
			state = STATE_WINC;
			return;
		}
	}

	if ((board[0][3] != ' ') && (board[0][3] == board[1][2]) && (board[0][3] == board[2][1]) && (board[0][3] == board[3][0])) /* �ι�° �밢�� �˻� */
	{
		if (board[0][2] == 'X')
		{
			state = STATE_WINP;
			return;
		}
		else
		{
			state = STATE_WINC;
			return;
		}
	}

	if (moveCnt > 7)
	{
		state = STATE_DRAW;		/* ����� �� */
	}
}; 