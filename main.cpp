#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//void createAndFillFile(const char *fileName, long start, long end) {
//	FILE *file = fopen(fileName, "w");
//	if (file == NULL) {
//		printf("Failed to open the file for writing.\n");
//		return;
//	}
//
//	for (long i = start; i <= end; i++) {
//		fprintf(file, "%ld\n", i);
//	}
//
//	fclose(file);
//}

//void loadMatrixFromFile(int rows, int cols, int ***matrix, const char *fileName) {
//	FILE *file = fopen(fileName, "r");
//	if (file == NULL) {
//		printf("Failed to open the file.\n");
//		exit(1);
//	}
//
//	*matrix = (int **)malloc(rows * sizeof(int *));
//	for (int i = 0; i < rows; i++) {
//		(*matrix)[i] = (int *)malloc(cols * sizeof(int));
//		for (int j = 0; j < cols; j++) {
//			if (fscanf(file, "%d", &(*matrix)[i][j]) != 1) {
//				printf("Error reading from file.\n");
//				exit(1);
//			}
//		}
//	}
//
//	fclose(file);
//}
//
//void writeMatrixToFile(int rows, int cols, int **matrix, const char *fileName) {
//	FILE *file = fopen(fileName, "w");
//	if (file == NULL) {
//		printf("Failed to open the file for writing.\n");
//		return;
//	}
//
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			fprintf(file, "%d\n", matrix[i][j]);
//		}
//	}
//
//	fclose(file);
//}

void printMatrix(int rows, int cols, int **matrix) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

void createRandomMatrix(int rows, int cols, int ***matrix) {
	*matrix = (int **)malloc(rows * sizeof(int *));
	for (int i = 0; i < rows; i++) {
		(*matrix)[i] = (int *)malloc(cols * sizeof(int));
		for (int j = 0; j < cols; j++) {
			(*matrix)[i][j] = rand() % 10; // Adjust the range of random numbers as needed
		}
	}
}

void freeMatrix(int rows, int **matrix) {
	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

int main() {
	clock_t start, end;

	/*createAndFillFile("matrixA.txt", 1, 10000000);
	createAndFillFile("matrixB.txt", 1, 10000000);
	*/
	//printf("Files 'matrixA.txt' and 'matrixB.txt' have been created.\n");

	int numRowsMatrixA, numColsMatrixA, numRowsMatrixB, numColsMatrixB;

	printf("Enter the dimensions of the first matrix (m x n):\n");
	printf("Enter the number of rows for martrix-A: ");
	scanf("%d", &numRowsMatrixA);
	printf("Enter the number of columns for matrix-A: ");
	scanf("%d", &numColsMatrixA);

	printf("Enter the dimensions of the second matrix (p x q):\n");
	printf("Enter the number of rows for matrix-B: ");
	scanf("%d", &numRowsMatrixB);
	printf("Enter the number of columns for matrix-B: ");
	scanf("%d", &numColsMatrixB);

	if (numColsMatrixA != numRowsMatrixB) {
		printf("Matrix multiplication is not possible. The number of columns in Matrix A must be equal to the number of rows in Matrix B.\n");
		return 1;
	}

	int **matrixA = NULL, **matrixB = NULL, **result = NULL;


	int choice;
	printf("Choose an option:\n");
	printf("1. Load matrices from files\n");
	printf("2. Generate random matrices\n");
	scanf("%d", &choice);

	if (choice == 1) {
		printf(" Ok. u choose to load matrix from file.\n");

		//loadMatrixFromFile(numRowsMatrixA, numColsMatrixA, &matrixA, "matrixA.txt");
		//loadMatrixFromFile(numRowsMatrixB, numColsMatrixB, &matrixB, "matrixB.txt");
	}
	else if (choice == 2) {
		createRandomMatrix(numRowsMatrixA, numColsMatrixA, &matrixA);
		createRandomMatrix(numRowsMatrixB, numColsMatrixB, &matrixB);
	}
	else {
		printf("Invalid choice. Please choose 1 or 2.\n");
		return 1;
	}

	printf("Matrix A:\n");
	printMatrix(numRowsMatrixA, numColsMatrixA, matrixA);

	printf("Matrix B:\n");
	printMatrix(numRowsMatrixB, numColsMatrixB, matrixB);

	// Record start time
	start = clock();

	result = (int **)malloc(numRowsMatrixA * sizeof(int *));
	for (int i = 0; i < numRowsMatrixA; i++) {
		result[i] = (int *)malloc(numColsMatrixB * sizeof(int));
		for (int j = 0; j < numColsMatrixB; j++) {
			result[i][j] = 0;
			for (int k = 0; k < numColsMatrixA; k++) {
				result[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	// Record end time
	end = clock();

	printf("Matrix A * Matrix B:\n");
	printMatrix(numRowsMatrixA, numColsMatrixB, result);

	// Calculate execution time
	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("\nTime taken to multiply matrices: %f seconds\n", cpu_time_used);

	// Free allocated memory
	freeMatrix(numRowsMatrixA, matrixA);
	freeMatrix(numRowsMatrixB, matrixB);
	freeMatrix(numRowsMatrixA, result);
	getch();
	return 0;
}
