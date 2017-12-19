/* The game logic (no view code or direct used intercation)
The game is a simple guess the word game based on Mastermind
*/

#pragma once

#include <string>
// to make syntax ubreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord();
	int32  SetHiddenWord(int32);
	

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity (FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialisation
	int32 MycurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
