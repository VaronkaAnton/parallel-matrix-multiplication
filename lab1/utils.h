#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
typedef chrono::high_resolution_clock hr_clock;
typedef chrono::milliseconds ms;
// https://stackoverflow.com/questions/28928161/cleanest-and-simplest-way-to-get-elapsed-time-since-execution-in-c/28928371

class Timer {
private:
	static hr_clock::time_point start_time;

public:
	static void start();
	static double end();
};

int* init_matrix(int dimension);