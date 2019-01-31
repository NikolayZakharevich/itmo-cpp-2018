#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <ostream>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <cstring>

class Matrix {
private:
    unsigned int n, m;
    int **matrix;
    void checkSizeEquivalence(const Matrix &first, const Matrix &second);

public:
    Matrix();
    Matrix(unsigned int n, unsigned int m);
    Matrix(const Matrix &other);
    ~Matrix();

    int &operator()(unsigned int row, unsigned int col);
    int &operator()(unsigned int row, unsigned int col) const;
    Matrix &operator=(const Matrix &other);

    Matrix operator+(int value) const;
    Matrix operator-(int value) const;
    Matrix operator*(int value) const;

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;

    Matrix &operator+=(int value);
    Matrix &operator-=(int value);
    Matrix &operator*=(int value);

    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);

    Matrix &transpose();
    Matrix &dot(const Matrix &other);

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &outMatrix);
    friend std::ifstream &operator>>(std::ifstream &stream, const Matrix &inMatrix);
};

#endif // MATRIX_H_INCLUDED
