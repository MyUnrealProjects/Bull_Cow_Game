#pragma once
#include <string>

using FString = std::string;
using int32 = int;
//all values initialized to 0
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
	Wrong_Length,
	Not_Lowercase

};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const ; //TODO make a more rich return value.



	void Reset(); //TODO make a more rich return value.
	//counts bull and cows and increasing turns # assuming valig guess
	FBullCowCount SubmitValidGuess(FString);


//ignore for now
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;

	bool IsLowercase(FString) const;
};