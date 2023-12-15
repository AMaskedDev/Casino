#include <iostream>
#include <random>
#include <ctime>

static int cashWon = 0;

static int GenerateNumber(int max)
{
	static std::mt19937 rng(time(nullptr));  // Seed the random number generator with the current time
	std::uniform_int_distribution<int> distribution(1, max);
	return distribution(rng);
}

void LoseMoney(int money)
{
	if (cashWon >= money)
	{
		cashWon -= money;
	}
	else
	{
		cashWon = 0;
	}

	std::cout << "\nYou lost $" << money << std::endl;
}

void GainMoney(int money)
{
	cashWon += money;
	std::cout << "\nYou won $" << money << std::endl;
}

int main()
{
	// Guess The Number
	int casinoGenerated[6];
	for (int i = 0; i < 6; i++)
	{
		casinoGenerated[i] = GenerateNumber(5);
	}

	std::cout << "\n";

	// Main Game
	for (int i = 0; i < 6; i++)
	{
		// Getting input
		int answer;

		std::cout << "\nEnter number " << 5 - i << ": ";
		std::cin >> answer;

		// Checks
		if (answer != casinoGenerated[i])
		{
			if (cashWon < 0) std::cout << "Wrong!\n";
			LoseMoney(2);
		}
		else
		{
			std::cout << "Correct!\n";
			GainMoney(1);
		}
	}

	system("cls");
	std::cout << "You have won a total of $" << cashWon << " this round!\n\n";

	// Guess The Time
	time_t curr_time;
	time(&curr_time);
	tm tm_local;

#ifdef _MSC_VER
	localtime_s(&tm_local, &curr_time);
#else
	tm_local = *localtime(&curr_time);
#endif

	int hour = tm_local.tm_hour;

	int triesLeft = 4;
	int guessedTime = 0;

	// Main Game
	while (triesLeft > 0)
	{
		// Getting Input
		std::cout << "You have " << triesLeft << " tries\n";
		std::cout << "\nTry to guess the current hour of the time: ";
		std::cin >> guessedTime;

		// Checks
		if (guessedTime > hour)
		{
			std::cout << "That is too high!\n";
			triesLeft--;
			LoseMoney(2);
		}
		else if (guessedTime < hour)
		{
			std::cout << "That is too low!\n";
			triesLeft--;

			LoseMoney(2);
		}
		else
		{
			std::cout << "That is correct!\n";
			cashWon += 0;

			triesLeft = 0;

			GainMoney(1);
		}
	}

	// Printing the final amount of cash the user made
	system("cls");
	std::cout << "You have won a total of $" << cashWon << "!";

	// Pausing the program before exiting
	std::cout << "\n" && system("pause");
	return 0;
}
