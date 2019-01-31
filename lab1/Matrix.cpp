#include "matrix.h"

Matrix::Matrix() {
    n = 0;
    m = 0;
}

Matrix::Matrix(unsigned int sizeN, unsigned int sizeM) {
    n = sizeN;
    m = sizeM;
    matrix = new int *[n];
    for (unsigned int row = 0; row < n; row++) {
        matrix[row] = new int [m];
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &other) {
    n = other.n;
    m = other.m;
    matrix = new int *[n];
    for (unsigned int row = 0; row < n; row++) {
        matrix[row] = new int [m];
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] = other.matrix[row][col];
        }
    }
}

Matrix::~Matrix() {
    for (unsigned int row = 0; row < n; row++) {
        delete [] matrix[row];
    }
   delete [] matrix;
}

Matrix &Matrix::operator=(const Matrix &other) {
    this -> ~Matrix();
    new (this) Matrix(other);
    return *this;
}

int &Matrix::operator()(unsigned int row, unsigned int col) {
    if (row < n && col < m) {
        return matrix[row][col];
    } else {
        std::cout << "Bad index";
        exit(EXIT_FAILURE);
    }
}

int &Matrix::operator()(unsigned int row, unsigned int col) const{
    if (row < n && col < m) {
        return matrix[row][col];
    } else {
        std::cout << "Bad index";
        exit(EXIT_FAILURE);
    }
}

Matrix Matrix::operator+(int value) const {
    Matrix newMatrix = *this;
    newMatrix += value;
    return newMatrix;
}

Matrix Matrix::operator-(int value) const {
    Matrix newMatrix = *this;
    newMatrix -= value;
    return newMatrix;
}

Matrix Matrix::operator*(int value) const {
    Matrix newMatrix = *this;
    newMatrix *= value;
    return newMatrix;
}

Matrix Matrix::operator+(const Matrix &other) const {
    Matrix newMatrix = *this;
    newMatrix += other;
    return newMatrix;
}

Matrix Matrix::operator-(const Matrix &other) const {
    Matrix newMatrix = *this;
    newMatrix -= other;
    return newMatrix;
}

Matrix Matrix::operator*(const Matrix &other) const {
    Matrix newMatrix = *this;
    newMatrix *= other;
    return newMatrix;
}

Matrix &Matrix::operator+=(int value) {
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] += value;
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(int value) {
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] -= value;
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(int value) {
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] *= value;
        }
    }
    return *this;
}

void Matrix::checkSizeEquivalence(const Matrix &first, const Matrix &second) {
    if (first.n != second.n || first.m != second.m) {
        std::cout << "Bad size of matrix";
        exit(EXIT_FAILURE);
    }
}

Matrix &Matrix::operator+=(const Matrix &other) {
    checkSizeEquivalence(*this, other);
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] += other.matrix[row][col];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    checkSizeEquivalence(*this, other);
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] -= other.matrix[row][col];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    checkSizeEquivalence(*this, other);
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] *= other.matrix[row][col];
        }
    }
    return *this;
}

Matrix &Matrix::transpose() {
    Matrix temp = *this;
    this -> ~Matrix();

    n = temp.m;
    m = temp.n;
    matrix = new int *[n];
    for (unsigned int row = 0; row < n; row++) {
        matrix[row] = new int [m];
        for (unsigned int col = 0; col < m; col++) {
            matrix[row][col] = temp.matrix[col][row];
        }
    }
    return *this;
}

Matrix &Matrix::dot(const Matrix &other) {
    if (m != other.n) {
        std::cout << "Impossible to multiply matrices";
        exit(EXIT_FAILURE);
    }

    Matrix temp(n, other.m);
    for (unsigned int row = 0; row < n; row++) {
        for (unsigned int col = 0; col < other.m; col++) {
            for (unsigned int k = 0; k < m; k++) {
                temp.matrix[row][col] += matrix[row][k] * other.matrix[k][col];
            }
        }
    }
    (*this) = temp;
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &outMatrix) {
    for (unsigned int row = 0; row < outMatrix.n; row++) {
        for (unsigned int col = 0; col < outMatrix.m; col++) {
            stream << outMatrix.matrix[row][col] << " ";
        }
        stream << "\n";
    }
    return stream;
}

std::ifstream &operator>>(std::ifstream &stream, const Matrix &inMatrix) {
    for (unsigned int row = 0; row < inMatrix.n; row++) {
        for (unsigned int col = 0; col < inMatrix.m; col++) {
            stream >> inMatrix.matrix[row][col];
        }
    }
    return stream;
}
