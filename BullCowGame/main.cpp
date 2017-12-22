/* This is the console executable that makes use of the Bull class
This acts as the view in a MVC pattern and responsible for all user
interaction. For game logic see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside of a class
void PrintArt();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();
int32 SelectWordByLength();

FBullCowGame BCGame; // instantiate a new game, which we reuse across the game

//entry point to app
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0; //exit
}



void PrintIntro() 
{
	PrintArt();
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "\nA Bull means your guess contains a correct letter in the right place.";
	std::cout << "\nA Cow means your guess contains a correct letter, but in the wrong place.\n\n";
	SelectWordByLength();
	std::cout << "\nNice! Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of in " << BCGame.GetMaxTries() << " tries? \n ";
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	 {
		FText Guess = GetValidGuess(); 

		// submit valid giuess to the game and receive counts
		FBullCowCount BullCowCount =  BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

int32 SelectWordByLength()
{
	std::cout << "Please, select the hidden word length (3 - 6): ";
	FText SelectedWordLength = "";
	std::getline(std::cin, SelectedWordLength);
	//check if the input is correct
	while (std::cin.fail() || std::cin.eof() || SelectedWordLength.find_first_not_of("3456") != FText::npos || SelectedWordLength.length() != 1) {
		std::cout << "Please, enter a number from 3 to 6: ";
		std::cin.clear();
		std::getline(std::cin, SelectedWordLength);
	}

	BCGame.SetHiddenWord(std::stoi(SelectedWordLength));
	return 0;
}

// loop untill the user gives a valid guess
FText GetValidGuess()  
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Go ahead and enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Plase enter a " << BCGame.GetHiddenWordLength() << " letter word.\n \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Plase enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Plase enter all lowercase letters. \n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until a we get no errors
	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);	
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "\nWELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "\nBetter luck next time! \n";
	}
	return;
}

void PrintArt() {
	
	std::cout << "	    / /               \\ \\   " << std::endl;
	std::cout << "      `//-.|  (  ,\\)\\//\\)\\/_  ) |                    _\\/\\/\\/\\/\\/\\/\\/\\/\\/" << std::endl;
	std::cout << "      //___\\   `\\\\\\/\\\\/\\/\\\\///'  /                   /_                \\\\" << std::endl;
	std::cout << "   ,-'~`-._ `- - -'_   `---`  _ \\`'-~-,_        ,-~''`/    _  `'''`  _'--'` _.-`~'  " << std::endl;
	std::cout << "   \\       `-.  '_`.      .'_` \\ ,--~`/        \\`~' - , / '_'.     .'_'  . - ` / " << std::endl;
	std::cout << "    `.__.-'`/   (-\\        /-) |-.__,'          ',__.-| (-\\        /-)   \\`'-.__.`" << std::endl;
	std::cout << "      ||   |     \\O)  /^\\ (O/  |                     |  \\O) /^\\  (O/     |   ||" << std::endl;
	std::cout << "      `\\\\  |         /   `\\    /       BULLS          \\   /`   \\         |  //`" << std::endl;
	std::cout << "        \\\\  \\       /      `\\ /                        \\ /`      \\       /  //" << std::endl;
	std::cout << "         `\\\\ `-.  /' .---.--.\\           &             /.--.---. '\\  .-` //`" << std::endl;
	std::cout << "           `\\\\/`~(, '()      ()                        ()      ()' ,(~`\\\\/`" << std::endl;
	std::cout << "            /(O) \\\\   _,.-.,_)          COWS           (_,.-.,_   // (O)\\" << std::endl;
	std::cout << "           //  \\\\ `\\'`      /                           \\\\      `'/` //  \\\\" << std::endl;
	std::cout << "          / |  ||   \\------/                               `'~''''`    ||  | \\ "<< std::endl;
	std::cout << "        /  |__||" << std::endl;
}
