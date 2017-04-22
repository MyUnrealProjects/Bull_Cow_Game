#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame() { Reset(); } //default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4,7}, {5, 10}, {6, 15}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	
	const FString HIDDEN_WORD = "planet";

	
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
// recives a valid guess increments turn, and return counts.  
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//incriment the turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop thorugh all letters in the Hiddenword
	int32 WordLength = MyHiddenWord.length(); //assuming same length as the guess
	
	for(int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the Guess
		for(int32 GChar = 0; GChar<WordLength; GChar++){

			//if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if(MHWChar == GChar)
				{
					BullCowCount.Bulls++; // incriments bulls
				}
				else {
					BullCowCount.Cows++; //incriments cows
				}
			}	
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;//if not lower case //return error //TODO write function 
	} 
	else if (Guess.length () != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length; //guess length wrong //return eeror
	}
	else
	{
		return EGuessStatus::OK;
	}
		
	return EGuessStatus::OK; 
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true; }

	//set up our map
	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) //for al letters of the word
	{
		Letter = tolower(Letter); //handle mixed case

		if (LetterSeen[Letter]) { return false; } // not isogram
		else { LetterSeen[Letter] = true; }
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	//treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true; }
	TMap <char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		if (islower(Letter)) { return true; }
		else {
			return false;
		}
	}
}

