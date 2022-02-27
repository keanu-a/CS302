// Keanu Aloua
// February 24, 2022
// Multiplying matrices by multithreading

#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

std::vector< std::vector<int> > matrix1, matrix2, endMatrix;

void multiplyMatrices(int row1, int col2, int row2);
void printMatrix(std::vector< std::vector<int> > matrix, int row, int col);

int main()
{   
    // File Variables
    std::string filename;
    std::ifstream file;

    // Matrix Variables
    int n1, m1, n2, m2, num;

    // Thread Variables
    std::vector<std::thread> threadPool;
    int maxThreads = std::thread::hardware_concurrency();

    // Prompting user for file name
    std::cout << "Enter filename: ";
    std::cin >> filename;
    file.open(filename);


    // Getting Matrix 1
    file >> n1 >> m1; // Gets rows and cols for matrix 1
    for (int i = 0; i < n1; i++) {
        std::vector<int> row;

        while (file >> num) 
        {
            // Checks to see if row is done
            if (file.peek() == '\n') {
                row.push_back(num);
                break;
            } 
            else {
                row.push_back(num);
            }
        }

        matrix1.push_back(row);
    }

    // Getting Matrix 2
    file >> n2 >> m2; // Gets rows and cols for matrix 2
    for (int i = 0; i < n2; i++) {
        std::vector<int> row;

        while (file >> num) 
        {
            // Checks to see if row is done
            if (file.peek() == '\n') {
                row.push_back(num);
                break;
            } 
            else {
                row.push_back(num);
            }
        }

        matrix2.push_back(row);
    }

    // Setting result matrix to all zeroes
    // This is for when the threads do the calculations, we can set the value in the matrix
    for (int i = 0; i < n1; i++) {
        std::vector<int> row;

        for (int j = 0; j < m2; j++) {
            row.push_back(0);
        }

        endMatrix.push_back(row);
    }

    // ------------------------------------------------------------- //
    // ---------------- START MATRIX MULTIPLICATION ---------------- //
    // ------------------------------------------------------------- //

    // Going to go through each row of matrix 1    
    for (int i = 0; i < n1; i++) {

        // Each column of matrix 2
        for (int j = 0; j < m2; j++) {

            threadPool.push_back( std::thread(multiplyMatrices, i, j, n2) );

            // Checks if spawned max number of threads
            if (threadPool.size() % maxThreads == 0) {

                // Joins all threads before spawning more threads
                for (int i = 0; i < threadPool.size(); i++) {
                    threadPool[i].join();
                }

                // Clears the vector
                threadPool.clear();
            }
        }
    }

    // Joins threads if there are any running after loop ends
    for (int i = 0; i < threadPool.size(); i++) {
        threadPool[i].join();
    }

    // Outputs result matrix
    printMatrix(endMatrix, endMatrix.size(), endMatrix[0].size());
 
    return 0;
}

void multiplyMatrices(int row1, int col2, int row2) {
    int sum = 0;

    // Each row of matrix 2
    for (int k = 0; k < row2; k++) {
        sum += matrix1[row1][k] * matrix2[k][col2];
    }

    // Setting result matrix spot to calculated sum
    endMatrix[row1][col2] = sum;

    return;
}

void printMatrix(std::vector< std::vector<int> > matrix, int row, int col) {
    // Function to print a matrix

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    return;
}
