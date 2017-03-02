#ifndef MATRIX_H
#define MATRIX_H

#include "Vector3.h"

#define MATRIX_SIZE 4

class Matrix{
public:
    Matrix();
    Matrix(const float* elements);
    Matrix(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    const float* getMatrix();
    const float* getMatrix() const;

    void identity();

    float& operator[] (int i);
    const float& operator[] (int i) const;
    Matrix operator *(const Matrix &rhs) const;
    
    void translate(const Vector3& vec);
    void lookAt(const Vector3 &localForward, const Vector3 &targetDirection, const Vector3 &worldUp);
    Vector3 multiply(const Vector3& vec, float w);

    bool constructInvert(const float m[16]);
   
    static bool testMult();
    static bool testInverse();

private:
    void setRow(int index, const Vector3& vec);
    float matrix_[MATRIX_SIZE * MATRIX_SIZE];

};

#endif