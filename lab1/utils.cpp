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

int get_random_number() {
	return (rand() % 200) - 100;
}

int* init_matrix(int dimension)
{
	int* v = new int[dimension*dimension];
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			v[i*dimension + j] = get_random_number();
		}
	}
	return v;
}