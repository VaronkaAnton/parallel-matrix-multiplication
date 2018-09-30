#include "pch.h"
#include "utils.h"

hr_clock::time_point Timer::start_time = hr_clock::now();

void Timer::start() {
	start_time = hr_clock::now();
}

double Timer::end() {
	auto end_time = hr_clock::now();
	return chrono::duration_cast<ms>(end_time - start_time).count() / 1000.;
}

int* init_matrix(int dimension)
{
	int* v = new int[dimension*dimension];
	for (int i = 0; i < dimension*dimension; i++) {
		v[i] = (rand() % 200) - 100;
	}
	return v;
}