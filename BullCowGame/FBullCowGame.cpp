#pragma once

#include "FBullCowGame.h"
#include <map>
// to make syntax ubreal friendly
#define TMap std::map  
using int32 = int;

FBullCowGame::FBullCowGame() {	Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const { return MycurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "slone"; //this must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MycurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess))  // if the guess isn't a lowercase 
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() !=  GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
	
}

//receives a vaild guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MycurrentTry++;
	FBullCowCount  BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming the same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
		// compare letters agains the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++){
			// if they match
			if (MyHiddenWord[MHWChar] == Guess[GChar]){
				if (MHWChar == GChar){// if they match in the same place
					BullCowCount.Bulls++; //incr bulls
				}
				else{
					BullCowCount.Cows++; //incr cows if not
				}
			}		
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const { 
	//treat  0 and 1 letter words as isigram
	if (Word.length() <= 1) { return true; }

	// set up a map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { //if letter is in the map
			return false; //not isogram
		} 
		else {
			LetterSeen[Letter] = true; //populate the tmap
		}
	}
	return true;  //in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const {
	
	for(auto Letter : Word){
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
