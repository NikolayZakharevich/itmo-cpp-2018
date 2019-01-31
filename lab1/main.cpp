#include "matrix.h"
#include <vector>
#include <string>
#include <limits.h>

int main()
{
    std::ifstream fin ("input.txt");
    Matrix a(1, 1);
    int x = 10;
    Matrix b(x, x);
    a = b;
    a = Matrix(20, 10) + Matrix(20, 10);
    a(1, 2) = 10;
    std::cout << a;
   // unsigned int matrixAmount;

  //  fin >> matrixAmount;
/*
    std::vector <Matrix> matrix(matrixAmount);
    for (unsigned int i = 0; i < matrixAmount; i++) {
        unsigned int nI, mI;
        fin >> nI >> mI;
        matrix[i] = Matrix(nI, mI);
        fin >> matrix[i];
    }

    unsigned int queriesAmount;
    fin >> queriesAmount;

    Matrix a(3, 3);
    int c = a(1, 2);


    std::string query;
    std::getline(fin, query); // get '\n' symbol
    while (queriesAmount--) {
        std::getline(fin, query);
        if (query[1] == '(') { // a(i, j)
            std::cout << matrix[query[0] - '0']((query[2] - '0'), (query[4]));
        }
        if (query[2] == '=') { // a = b + C, a = b - C, a = b * C
            if (query[6] == '+') {
                matrix[query[0] - '0'] = matrix[query[4] - '0'] + (query[8] - '0');
            } else if (query[6] == '-') {
                matrix[query[0] - '0'] = matrix[query[4] - '0'] - (query[8] - '0');
            } else if (query[6] == '*') {
                matrix[query[0] - '0'] = matrix[query[4] - '0'] * (query[8] - '0');
            }
        } else if (query[3] == '=') { // a += C, a -= C, a *= C
            if (query[2] == '+') {
                matrix[query[0] - '0'] += (query[5] - '0');
            } else if (query[2] == '-') {
                matrix[query[0] - '0'] -= (query[5] - '0');
            } else if (query[2] == '*') {
                matrix[query[0] - '0'] *= (query[5] - '0');
            }
        } else if (query.find("transpose") != std::string::npos) { // a transpose
            matrix[query[0] - '0'].transpose();
        } else if (query.find("dot") != std::string::npos) { // a dot b
            matrix[query[0] - '0'].dot(matrix[query[6] - '0']);
        }
    }

    for (unsigned int i = 0; i < matrixAmount; i++) {
        std::cout << matrix[i] << "\n";
    }*/

    return 0;
}
