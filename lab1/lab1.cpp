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
		/*for (int i = 0; i < dimension; i++) {
			for (int j = 0; j < dimension; j++) {
				fout << result[i*dimension + j] << " ";
			}
			fout << endl;
		}*/
		fout << Timer::end() << " ";
		delete[] result;
		result = new int[dimension*dimension]{ 0 };
	}
	fout << endl;
	return 0;
}

void point_multiplication(
	int* m1, int* m2, int* result, int dimension, int parallel_num
) {
#pragma omp parallel for if (parallel_num == 1)
	for (int i = 0; i < dimension; i++) {
		int icurr = i * dimension;
		for (int j = 0; j < dimension; j++) {
			int jcurr = j * dimension;
			for (int k = 0; k < dimension; k++) {
				result[icurr + j] += m1[icurr + k] * m2[jcurr + k];
			}
		}
	}
	return;
}

void block_multiplication(
	int* m1, int* m2, int* result, int dimension,
	int block_size, int parallel_num
) {
	int q = dimension / block_size;
#pragma omp parallel for if (parallel_num == 1)
	for (int i1 = 0; i1 < q; i1++) {
		for (int j1 = 0; j1 < q; j1++) {
			for (int k1 = 0; k1 < q; k1++) {
				for (int i2 = 1; i2 < block_size; i2++) {
					for (int j2 = 1; j2 < block_size; j2++) {
						for (int k2 = 1; k2 < block_size; k2++) {
							int i = i1 * block_size + i2;
							int j = j1 * block_size + j2;
							int k = k1 * block_size + k2;
							result[i*dimension+j] += m1[i*dimension+k] * m2[k*dimension+j];
						}
					}
				}
			}
		}
	}
	return;
}
