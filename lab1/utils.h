#ifndef LAB1_UTILS_H
#define LAB1_UTILS_H

#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
typedef chrono::high_resolution_clock hr_clock;
typedef chrono::milliseconds ms;

class Timer {
private:
	static hr_clock::time_point start_time;

public:
	static void start();
	static double end();

};

int get_random_number();
int** init_matrix(int dimension);
int* convert_left(int** matrix, int dimension);
int* convert_right(int** matrix, int dimension);
#endif //LAB1_UTILS_H
