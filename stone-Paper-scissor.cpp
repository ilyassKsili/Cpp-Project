#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameSignals{stone=1, paper=2, scissor=3};

enum enWinner{player=1, computer=2, draw=3};

struct stRoundInfo
{
	short RoundNum=0;

	enGameSignals PlayerChiose;
	enGameSignals ComputerChiose;

	enWinner Winner;

	string WinnerName;
};

struct stGameResult
{
	short RoundNumber=0;

	short PlayerWinTimes = 0;
	short ComputerWinTime = 0;
	short DrawTimes = 0;

	enWinner GameWinner;

	string GameWinnerName = "";
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;

	return RandNum;
}

string SignalChiose(enGameSignals signal)
{
	string Signalname[3] = { "stone", "paper", "scissor" };
	return Signalname[signal - 1];
}

string WinnerName(enWinner Winner)
{
	string WinnerName[3] = { "Palyer", "Computer", "No-Winner" };
	return WinnerName[Winner - 1];
}


void GetScreenColor(enWinner Winner)
{
	if (Winner== enWinner::player)
	{
		system("color 2F");
	}
	else if (Winner== enWinner::computer)
	{
		system("color 4F");
		cout << "\a";
	}
	else
	{
		system("color 6F");
	}
}

enWinner HowWonRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChiose==RoundInfo.ComputerChiose)
	{
		return enWinner::draw;
	}
	switch (RoundInfo.PlayerChiose)
	{
	case (enGameSignals::stone):
		if (RoundInfo.ComputerChiose==enGameSignals::paper)
		{
			return enWinner::computer;
		}
		break;
	case(enGameSignals::paper):
		if (RoundInfo.ComputerChiose == enGameSignals::scissor)
		{
			return enWinner::computer;
		}
		break;	
	case(enGameSignals::scissor):
		if (RoundInfo.ComputerChiose == enGameSignals::stone)
		{
			return enWinner::computer;
		}
		break;
	}
	return enWinner::player;
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "---------------Round [" << RoundInfo.RoundNum << "]-----------------\n";
	cout << "PlayerChoise: " << SignalChiose(RoundInfo.PlayerChiose) << endl;
	cout << "ComputerChoise: " << SignalChiose(RoundInfo.ComputerChiose) << endl;

	cout << "RoundWinner: " << RoundInfo.WinnerName << endl;

	GetScreenColor(RoundInfo.Winner);

}

int HowMuchRound()
{
	int number=1;
	do
	{
		cout << "How Many Round Do You Wand To Play From (1) tO (10)?\n";
		cin >> number;

	} while (number<1||number>10);

	return number;
}

enGameSignals ComputerChoise()
{
	return (enGameSignals)RandomNumber(1, 3);
}

enGameSignals PlayerChoise()
{
	int number;
	cout << "Choise signal: (1) stone, (2) paper, (3) scisor?\n";
	cin >> number;

	return (enGameSignals)number;

}

enWinner HowWonGame(stGameResult GameResult)
{
	if (GameResult.PlayerWinTimes > GameResult.ComputerWinTime)
	{
		return enWinner::player;
	}
	else if (GameResult.PlayerWinTimes < GameResult.ComputerWinTime)
	{
		return enWinner::computer;
	}
	else
	{
		return enWinner::draw;
	}
}

stGameResult FillGameResult(short RoundNumber, short PlayerWinTimes, short ComputerWinTimes, short DarwTimes)
{
	stGameResult GameResult;

	GameResult.RoundNumber = RoundNumber;
	GameResult.PlayerWinTimes = PlayerWinTimes;
	GameResult.ComputerWinTime = ComputerWinTimes;
	GameResult.DrawTimes = DarwTimes;
	GameResult.GameWinner = HowWonGame(GameResult);
	GameResult.GameWinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

stGameResult PlayGame(int HowManyRound)
{
	stRoundInfo RoundInfo;
	short PlayerWinTime = 0, ComputerWinTime = 0, DrawTime = 0;

	for (int RoundNumber = 1; RoundNumber <= HowManyRound; RoundNumber++)
	{
		cout << "Round [" << RoundNumber << "] being: \n";
		RoundInfo.RoundNum = RoundNumber;
		RoundInfo.PlayerChiose = PlayerChoise();
		RoundInfo.ComputerChiose = ComputerChoise();
		RoundInfo.Winner = HowWonRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner==enWinner::player)
		{
			PlayerWinTime++;
		}
		else if (RoundInfo.Winner == enWinner::computer)
		{
			ComputerWinTime++;
		}
		else
		{
			DrawTime++;
		}
		PrintRoundResult(RoundInfo);
	}
	return FillGameResult(HowManyRound, PlayerWinTime, ComputerWinTime, DrawTime);
}

void ShowGameOverScreen()
{
	cout << "\t\t--------------------------------------------------\n\n";
	cout << "\t\t\t\t++Game Over++\n\n";
	cout << "\t\t--------------------------------------------------\n\n";
}



void ShowGameResult(stGameResult GameResult)
{
	cout << "\t\tRouns Number: " << GameResult.RoundNumber << endl;
	cout << "\t\tPlayer Win Times: " << GameResult.PlayerWinTimes << endl;
	cout << "\t\tComputer Win Times: " << GameResult.ComputerWinTime << endl;
	cout << "\t\tDarw Win Times: " << GameResult.DrawTimes << endl<< endl;
	cout << "\t\tgame Winner: " << GameResult.GameWinnerName << endl<< endl;

	GetScreenColor(HowWonGame(GameResult));
}

void RestScreen()
{
	system("cls");
	system("color 0F");
}

void StarGame()
{
	char playagain= 'Y';
	do
	{
		RestScreen();
		stGameResult GameResult = PlayGame(HowMuchRound());
		ShowGameOverScreen();
		ShowGameResult(GameResult);

		cout << "do you want to paly again (Y/N) ?\n";
		cin >> playagain;


	} while (playagain == 'Y' || playagain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StarGame();

	return 0;
}



