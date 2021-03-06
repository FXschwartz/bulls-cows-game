#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// Make syntax Unreal friendly
using int32 = int;

FBullCowGame::FBullCowGame() { reset(); }

int32 FBullCowGame::getCurrentTry() const { return myCurrentTry; }
int32 FBullCowGame::getHiddenWordLength() const { return myHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

int32 FBullCowGame::getMaxTries() const {
	TMap<int32, int32> wordLengthToMaxTries{{3,4},{4,7},{5,10},{6,15},{7,20}};
	return wordLengthToMaxTries[myHiddenWord.length()];
}

void FBullCowGame::reset() {
	const FString hidden_word = "clear"; // This must be an isogram
	myHiddenWord = hidden_word;
	bGameIsWon = false;
	myCurrentTry = 1;

	return;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const {
	if(!isIsogram(guess)) {
		return EGuessStatus::notIsogram;
	}
	else if(!isLowerCase(guess)) {
		return EGuessStatus::notLowerCase;
	}
	else if(guess.length() != getHiddenWordLength()) {
		return EGuessStatus::wrongLength;
	}
	else {
		return EGuessStatus::ok;
	}
}

// Recieves a VALID guess, increments turn, and returns count;
FBullCowCount FBullCowGame::submitValidGuess(FString guess) {
	myCurrentTry++;
	FBullCowCount bullCowCount;

	int32 hiddenWordCount = myHiddenWord.length();
	int32 guessWordCount = guess.length();

	for(int32 i = 0; i < hiddenWordCount; i++) {
		for(int32 j = 0; j < guessWordCount; j++) {
			if(myHiddenWord[i] == guess[j]) {
				if(i == j) bullCowCount.bulls++;
				else bullCowCount.cows++;
			}
		}
	}
	if(bullCowCount.bulls == hiddenWordCount) bGameIsWon = true;
	else bGameIsWon = false;
	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString guess) const {
	if(guess.length() <= 1) return true;
	TMap<char, bool> currentLetter;
	for(auto letter : guess) {
		letter = tolower(letter);
		if(currentLetter[letter]) return false;
		else {
			currentLetter[letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString guess) const {
	if(guess.length() <= 1) return true;
	for(auto letter : guess) {
		if(!islower(letter)) return false;
	}
	return true;
}
