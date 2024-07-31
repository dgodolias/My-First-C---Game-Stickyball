#pragma once
#include <iostream>
#include <random>    // For std::random_device and std::mt19937

static int generateRandomNumber(int min, int max) {

	// Use std::rand to generate a random number in the range [min, max]
	int randomNumber = min + std::rand() % (max - min + 1);

	return randomNumber;
}