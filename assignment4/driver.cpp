// Keanu Aloua
// February 21, 2022
// Working with threads

#include <iostream>
#include <thread>
#include <fstream>
#include <vector>

void printMatrix(std::vector< std::vector<int> > matrix, int row, int col);

int main()
{
    std::vector< std::vector<int> > matrix1, matrix2, endMatrix;
    
    std::string filename;
    std::ifstream file;
    int n1, m1, n2, m2, num;

    // Prompting user for file name
    std::cout << "Please enter a file name: ";
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

    // Calculating
 
    return 0;
}

void printMatrix(std::vector< std::vector<int> > matrix, int row, int col) {
    // Function to print a matrix

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return;
}
