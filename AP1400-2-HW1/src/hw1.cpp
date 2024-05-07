#include<iostream>
#include "hw1.h"
#include<random>
#include<iomanip>
#include<stdexcept>
#include<cmath>

Matrix algebra::zeros(std::size_t n, std::size_t m) {
    return Matrix(n, std::vector<double>(m, 0));
}

Matrix algebra::ones(std::size_t n, std::size_t m) {
    return Matrix(n, std::vector<double>(m, 1));
}

Matrix algebra::random(std::size_t n, std::size_t m, double min, double max) {
    if (min > max) {
        throw std::logic_error("min must greater than max");
    }
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<double> distr(min, max);

    Matrix matrix = algebra::zeros(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = distr(eng);
        }
    }
    return matrix;
}

void algebra::show(const Matrix& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i][j] << std::setw(3);
        }
        std::cout << std::endl;
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c) {
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();

    Matrix matrix1 = algebra::zeros(n, m);
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            matrix1[i][j] = matrix[i][j] * c;
        }
    }

    return matrix1;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() || matrix2.empty()) {
        return Matrix();
    }
    std::size_t n1 = matrix1.size();
    std::size_t m1 = matrix1[0].size();
    std::size_t n2 = matrix2.size();
    std::size_t m2 = matrix2[0].size();

    if (m1 != n2) {
        throw std::logic_error("wrong dimensions");
    }

    Matrix m = algebra::zeros(n1, m2);

    for (std::size_t i = 0; i < n1; i++) {
        for (std::size_t j = 0; j < m2; j++) {
            for (std::size_t k = 0; k < n2; k++) {
                m[i][j] += matrix1[i][k] * matrix2[k][j]; 
            }
        }
    }
    return m;
}

Matrix algebra::sum(const Matrix& matrix, double c) {
    if (matrix.empty()) {
        return Matrix();
    }
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();

    Matrix matrix1 = algebra::zeros(n, m);

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            matrix1[i][j] = matrix[i][j] + c;
        }
    }
    return matrix1;
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix();
    }
    else if (matrix1.empty() || matrix2.empty()) {
        throw std::logic_error("wrong dimensions");
    }
    
    std::size_t n1 = matrix1.size();
    std::size_t m1 = matrix1[0].size();
    std::size_t n2 = matrix2.size();
    std::size_t m2 = matrix2[0].size();
    if (n1 != n2 && m1 != m2) {
        throw std::logic_error("wrong dimensions");
    }

    Matrix matrix3 = algebra::zeros(n1, m1);
    for (std::size_t i = 0; i < n1; i++) {
        for (std::size_t j = 0; j < m1; j++) {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return matrix3;
}

Matrix algebra::transpose(const Matrix& matrix) {
    if (matrix.empty()) {
        return Matrix();
    }

    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();

    Matrix matrix1 = algebra::zeros(m, n);

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            matrix1[j][i] = matrix[i][j];
        }
    }
    return matrix1;
}

Matrix algebra::minor(const Matrix& matrix, std::size_t n, std::size_t m) {
    std::size_t n1  = matrix.size();
    std::size_t m1 = matrix[0].size();

    if (n < 0 || n >= n1 || m < 0 || m >= m1) {
        return Matrix();
    }

    Matrix matrix1 = algebra::zeros(n1 - 1, m1 - 1);
    std::size_t a = 0, b = 0;
    for (std::size_t i = 0; i < n1; i++) {
        for (std::size_t j = 0; j < m1; j++) {
            if (i == n || j == m) {
                continue;
            }
            matrix1[a][b] = matrix[i][j];
            b++;
            if (b >= m1 - 1) {
                a++;
                b = 0;
            }
        }
    }
    return matrix1;
}

double algebra::determinant(const Matrix& matrix) {
    if (matrix.empty()) {
        return 1;
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("no determinant");
    }
    if (matrix.size() == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double ans = 0;
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();

    for (std::size_t i = 0; i < n; i++) {
        Matrix temp = algebra::minor(matrix, 0, i);
        ans += matrix[0][i] * algebra::determinant(temp) * pow(-1, i);
    }
    return ans;
}

Matrix algebra::inverse(const Matrix& matrix) {
    if (matrix.empty()) {
        return Matrix();
    }
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("non-square matrices have no inverse");
    }
    if (determinant(matrix) == 0) {
        throw std::logic_error("singular matrices have no inverse");
    }
    
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();

    Matrix matrix1 = algebra::zeros(n, m);
    Matrix matrix2(matrix);
    for (std::size_t i = 0; i < n; i++) {
        matrix1[i][i] = 1;
    }

    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = i + 1; j < n; j++) {
            double x = (matrix2[j][i] / matrix2[i][i]) * (-1);
            for (std::size_t k = 0; k < m; k++) {
                matrix1[j][k] += matrix1[i][k] * x;
                if (k == i) {
                    matrix2[j][k] = 0;
                }
                else {
                    matrix2[j][k] += matrix2[i][k] * x;
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double x = (matrix2[j][i] / matrix2[i][i]) * (-1);
            matrix2[i][j] = 0;
            for (int k = 0; k < m; k++) {
                matrix1[j][k] += matrix1[i][k] * x;
            }
        }
    }

    for (std::size_t i = 0; i < n; i++) {
        if (matrix2[i][i] != 1) {
            for (std::size_t j = 0; j < m; j++) {
                matrix1[i][j] /= matrix2[i][i];
            }
        }
    }
    return matrix1;
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    std::size_t n1 = matrix1.size();
    std::size_t m1 = matrix1[0].size();
    std::size_t n2 = matrix2.size();
    std::size_t m2 = matrix2[0].size();

    if (axis == 0) {
        if (m1 != m2) {
            throw std::logic_error("wrong dimensions");
        }
        Matrix m = algebra::zeros(n1 + n2, m1);
        for (std::size_t i = 0; i < n1 + n2; i++) {
            for (std::size_t j = 0; j < m1; j++) {
                if (i >= n1) {
                    m[i][j] = matrix2[i - n1][j];
                }
                else {
                    m[i][j] = matrix1[i][j];
                }
            }
        }
        return m;
    }
    if (n1 != n2) {
        throw std::logic_error("wrong dimensions");
    }
    Matrix m = algebra::zeros(n1, m1 + m2);
    for (std::size_t i = 0; i < n1; i++) {
        for (std::size_t j = 0; j < m1 + m2; j++) {
            if (j >= m1) {
                m[i][j] = matrix2[i][j - m1];
            }
            else {
                m[i][j] = matrix1[i][j];
            }
        }
    }
    return m;
}

Matrix algebra::ero_swap(const Matrix& matrix, std::size_t r1, std::size_t r2) {
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) {
        throw std::logic_error("r1 or r2 out of range");
    }
    Matrix matrix1(matrix);
    for (std::size_t i = 0; i < m; i++) {
        double t = matrix1[r1][i];
        matrix1[r1][i] = matrix1[r2][i];
        matrix1[r2][i] = t;
    }
    return matrix1;
}

Matrix algebra::ero_multiply(const Matrix& matrix, std::size_t r, double c) {
    std::size_t m = matrix[0].size();
    Matrix matrix1(matrix);
    for (std::size_t i = 0; i < m; i++) {
        matrix1[r][i] *= c;
    }
    return matrix1;
}

Matrix algebra::ero_sum(const Matrix& matrix, std::size_t r1, double c, std::size_t r2) {
    std::size_t m = matrix[0].size();

    Matrix matrix1(matrix);
    for (std::size_t i = 0; i < m; i++) {
        matrix1[r2][i] += matrix1[r1][i] * c;
    }
    return matrix1;
}

Matrix algebra::upper_triangular(const Matrix& matrix) {
    if (matrix.empty()) {
        return Matrix();
    }
    std::size_t n = matrix.size();
    std::size_t m = matrix[0].size();
    if (n != m) {
        throw std::logic_error("non-square matrices have no upper triangular form");
    }

    Matrix matrix1(matrix);

    for (std::size_t i = 0; i < n; i++) {
        if (matrix1[i][i] == 0) {
            std::size_t y = i + 1;
            while (y < n && matrix1[y][y] == 0) {
                y++;
            }
            matrix1 = ero_swap(matrix1, i, y);
        }
        for (std::size_t j = i + 1; j < n; j++) {
            double x = (matrix1[j][i] / matrix1[i][i]) * (-1);
            for (std::size_t k = 0; k < m; k++) {
                matrix1[j][k] += matrix1[i][k] * x;
            }
        }
    }
    return matrix1;
}