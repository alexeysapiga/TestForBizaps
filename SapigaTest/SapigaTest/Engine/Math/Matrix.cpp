#include "Matrix.h"
#include <cfloat>

Matrix::Matrix() {
    identity();
}

Matrix::Matrix(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    identity();

    matrix_[0] = v1.x; matrix_[1] = v2.x; matrix_[2] = v3.x; 
    matrix_[4] = v1.y; matrix_[5] = v2.y; matrix_[6] = v3.y; 
    matrix_[8] = v1.z; matrix_[9] = v2.z; matrix_[10] = v3.z; 
}

Matrix::Matrix(const float* elements) {
    for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++)
        matrix_[i] = elements[i];
}

const float* Matrix::getMatrix() {
    return matrix_;
}

const float* Matrix::getMatrix() const {
    return matrix_;
}

float& Matrix::operator[] (int i) {
    return matrix_[i]; 
}

const float& Matrix::operator[] (int i) const {
    return matrix_[i]; 
}

void Matrix::setRow(int index, const Vector3& vec) {
    matrix_[index * MATRIX_SIZE] = vec.x;
    matrix_[index * MATRIX_SIZE + 1] = vec.y;
    matrix_[index * MATRIX_SIZE + 2] = vec.z;
}

void Matrix::identity() {
    for (int i = 0; i < MATRIX_SIZE * MATRIX_SIZE; i++) {
        matrix_[i] = (i % (MATRIX_SIZE + 1) == 0) ? 1.0f : 0.0f;
    }
}

void Matrix::translate(const Vector3& vec) {
    int index = MATRIX_SIZE * (MATRIX_SIZE - 1);
    matrix_[index + 0] = vec.x;
    matrix_[index + 1] = vec.y;
    matrix_[index + 2] = vec.z;
}

Matrix Matrix::operator *(const Matrix &rhs) const {

    Matrix r;
    auto rightMatrix = rhs.getMatrix();
    int row = -1;
    int col = 0;
    for (int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++) {
        float sum = 0.0f;
    
        if (i % MATRIX_SIZE == 0) {
            row++; col = 0;
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            sum += matrix_[j + MATRIX_SIZE * row] * rhs[MATRIX_SIZE * j + col];
        }
        col++;
        r[i] = sum;
    }
    
    return r;
}



void Matrix::lookAt(const Vector3 &localForward, const Vector3 &targetDirection, const Vector3 &worldUp) {
     Vector3 worldRight = worldUp.cross(targetDirection).normalized();

    Vector3 perpWorldUp = targetDirection.cross(worldRight).normalized();
    
    setRow(0, worldRight);
    setRow(1, perpWorldUp);
    setRow(2, targetDirection);
}

bool Matrix::constructInvert(const float m[16]) {
    double inv[16], det;
    int i;

    inv[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] -
        m[8] * m[7] * m[14] -
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (int i = 0; i < 16; i++)
        matrix_[i] = inv[i] * det;

    return true;
}

Vector3 Matrix::multiply(const Vector3& vec, float w) {
    Vector3 result;
    float wn = 1.0f;
    result.x = (matrix_[0] * vec.x + matrix_[1] * vec.y + matrix_[2] * vec.z + matrix_[3] * w) * wn;
    result.y = (matrix_[4] * vec.x + matrix_[5] * vec.y + matrix_[6] * vec.z + matrix_[7] * w) * wn;
    result.z = (matrix_[8] * vec.x + matrix_[9] * vec.y + matrix_[10] * vec.z + matrix_[11] * w) * wn;

    return result;
}

bool Matrix::testMult() {
    Matrix m1;
    Matrix m2;
    for (int i = 0; i < 16; i++){
        m1[i] = i + 1;
        m2[i] = 16 - i;
    }

    Matrix m3 = m1 * m2;
    float result[] = { 
        80.0f,  70.0f,  60.0f,  50.0f,
        240.0f, 214.0f, 188.0f, 162.0f,
        400.0f, 358.0f, 316.0f, 274.0f, 
        560.0f, 502.0f, 444.0f, 386.0f };

    for (int i = 0; i < 16; i++)
        if (m3[i] != result[i]) return false;

    return true;
}

bool Matrix::testInverse() {
    Matrix m;
    m[5] =  2.0f; m[10] = 3.0f; m[15] = 4.0f;
    m[12] = 5.0f; m[13] = 6.0f; m[3] =  70.0f; m[7] = 8.0f;

    Matrix mr;
    mr.constructInvert(m.getMatrix());

    Matrix mul = mr * m;

    for (int i = 0; i < 16; i++)
    {
        if (i % (MATRIX_SIZE + 1) == 0)
        {
            if (mul[i] - 1.0f > FLT_EPSILON) return false;
        }
        else
        {
            if (fabs(mul[i] - 0.0f) > FLT_EPSILON) return false;
        }
    }
     
    return true;
}
