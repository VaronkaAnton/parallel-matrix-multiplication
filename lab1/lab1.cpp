#include "pch.h"
#include "lab1.h"

const string USAGE = "./lab1 -n <dimension> -r <block_size> -t <num_of_threads> -o <out_file>";


int main(int argc, char* argv[]) {
	if (argc < 8) {
		cerr << "Error. Usage is:" << endl;
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

	int **matrix1 = init_matrix(dimension), **matrix2 = init_matrix(dimension);
	int *result = new int[dimension*dimension] {0};
	fout << block_size << " " << endl;

	// 0 - sequential, 1 - parallel
	for (int parallel_num = 0; parallel_num <= 1; parallel_num++) {
		Timer::start();
		int* m1 = convert_left(matrix1, dimension);
		int* m2 = convert_right(matrix2, dimension);

		if (block_size == 1) {
			point_multiplication(m1, m2, result, dimension, parallel_num);
		}
		else {
			block_multiplication(m1, m2, result, dimension, block_size, parallel_num);
		}
		
		fout << Timer::end() << " ";
	}
	fout << endl;
	return 0;
}

void point_multiplication(
	int* m1, int* m2, int* result, int dimension, int parallel_num
) {
#pragma omp parallel for if (parallel_num == 1)
	for (int i = 0; i < dimension; i++) { //i is private since defined in a parallel region
		int icurr = i * dimension;
		for (int j = 0; j < dimension; j++) {
			int jcurr = j * dimension;
			int sum = 0;
			for (int k = 0; k < dimension; k++) {
				sum += m1[icurr + k] * m2[jcurr + k];
			}
			result[icurr + j] = sum;
		}
	}
	return;
}

void block_multiplication(
	int* m1, int* m2, int* result, int dimension,
	int block_size, int parallel_num
) {
	int step = dimension / block_size;
#pragma omp parallel for if (parallel_num == 1)
	for (int i1 = 0; i1 < dimension; i1+=step) {
		for (int j1 = 0; j1 < dimension; j1+=step) {
			for (int k1 = 0; k1 < dimension; k1+=step) {
				for (int i = i1; i < i1 + step; i++) {
					int icurr = i * dimension;
					for (int j = j1; j < j1 + step; j++) {
						int jcurr = j * dimension;
						int sum = 0;
						for (int k = k1; k < k1 + step; k++) {
							sum += m1[icurr+k] * m2[jcurr+k];
						}
						result[icurr + j] = sum + 1;
					}
				}
			}
		}
	}
	return;
}