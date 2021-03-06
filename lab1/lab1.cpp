#include "pch.h"
#include "lab1.h"

const string USAGE = "./lab1 -n <dimension> -r <block_size> -t <num_of_threads> -o <out_file>";


int main(int argc, char* argv[]) {
	if (argc < 8) {
		cerr << "Error. Correct input is:" << endl;
		cerr << USAGE << endl;
		return 1;
	}

	int dimension, block_size, threads_num;
	string filename = "output.txt";

	for (int i = 1; i < argc; i += 2) {
		if (string(argv[i]) == "-n") {
			dimension = atoi(argv[i + 1]);
		}
		else if (string(argv[i]) == "-r") {
			block_size = atoi(argv[i + 1]);
		}
		else if (string(argv[i]) == "-t") {
			threads_num = atoi(argv[i + 1]);
		}
		else if (string(argv[i]) == "-o") {
			filename = argv[i + 1];
		}
		else {
			cerr << USAGE << endl;
			return 1;
		}
	}

	fstream fout;
	fout.open(filename, fstream::out | fstream::app);
	omp_set_dynamic(0);
	omp_set_num_threads(threads_num);

	int *m1 = init_matrix(dimension), *m2 = init_matrix(dimension);
	int *result = new int[dimension*dimension] {0};
	//fout << block_size << " ";

	// 0 - sequential, 1 - outer parallel, 2 - inner parallel
	for (int parallel_code = 0; parallel_code <= 2; parallel_code++) {
		Timer::start();
		if (block_size == 1) {
			point_multiplication(m1, m2, result, dimension, parallel_code);
		}
		else {
			block_multiplication(m1, m2, result, dimension, block_size, parallel_code);
		}
		fout << Timer::end() << " ";
	}
	return 0;
}

void point_multiplication(
	int* m1, int* m2, int* result, int dimension, int parallel_code
) {
#pragma omp parallel for if (parallel_code == 1)
for (int i = 0; i < dimension; i++) { //i is private since defined in a parallel region
	#pragma omp parallel for if (parallel_code == 2)
	for (int j = 0; j < dimension; j++) {
			result[i*dimension + j] = 0;
			for (int k = 0; k < dimension; k++) {
				result[i*dimension + j] += m1[i*dimension + k] * m2[k*dimension + j];
				// left matrix is row-major and right is row-major
			}
		}
	}
	return;
}

void block_multiplication(
	int* m1, int* m2, int* result, int dimension,
	int block_size, int parallel_code
) {
	int step = dimension / block_size;
#pragma omp parallel for if (parallel_code == 1)
	for (int i1 = 0; i1 < dimension; i1+=block_size) {
	#pragma omp parallel for if (parallel_code == 2)
		for (int j1 = 0; j1 < dimension; j1+= block_size) {
			for (int k1 = 0; k1 < dimension; k1+= block_size) {
				for (int i = i1; i < i1 + block_size; i++) {
					for (int j = j1; j < j1 + block_size; j++) {
						result[i*dimension + j] = 0;
						for (int k = k1; k < k1 + block_size; k++) {
							result[i*dimension + j] += m1[i*dimension+k] * m2[k*dimension+j];
							// left matrix is row-major and right is row-major
						}
					}
				}
			}
		}
	}
	return;
}