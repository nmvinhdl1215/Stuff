#include<stdlib.h>
#include<ctime>
#include<iostream>
#include<random>
#include<chrono>
#include<utility>
#include<assert.h>

#include "Utility.h"

std::mt19937_64 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

long long getRand(long long l, long long h) {
	return std::uniform_int_distribution<long long>(l, h)(rng);
}

void clearBuffer() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
