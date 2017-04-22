/*this is the console exe that makes the use of BullCow class
this acts as the view in a MVC pattern and is responsible for all user interactions
for game logic see FBullCowGame class
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes for as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game which we reuse across game

// the entry point to our app
int main() 
{
	bool bPlayAgain = false;
	do{
	PrintIntro();
	PlayGame();
	bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0; // exit the application
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game \n";

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()<< " letter isogram I'm thinking of? \n";
	return;
}

//loop continually until user gives valid guess
FText GetValidGuess() 
{
	
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do{
		//get a guess from the player	
		int32 CurrentTry = BCGame.GetCurrentTry();
		
		std::cout << "try " << CurrentTry << " of "<< BCGame.GetMaxTries() << ". Please take a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout <<"please make sure you are writing in lowercaswe \n\n";
			break;

			default:
				break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PlayGame() //TODO change to get valid guess
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " tries" << "\n\n";

	//loop  asking for guesses while game NOT won
	//and there are still tries remaining
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); //TODOmake a loop to check for valid guesses
		
		// submit valid guesses
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl<< std::endl;
	}
	PrintGameSummary();
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
	std::cout << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!\n";
	}
	else {
		std::cout << "Better luck next time...";
	}
}

