#ifndef MATRIX_H //Header protection
#define MATRIX_H
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <fstream>
#include <string>
#include <iomanip>
#include "graph.h"
class Matrix
{
public:
  //Default contstructor
  Matrix();
  /**
   * Matrix::Matrix(int rows, int cols)
   *
   * Constructor for Matrix.
   * Creates a new Matrix with the specified dimensions.
   */
  Matrix::Matrix(int rows, int cols)
  {
    this->n_rows = rows;
    this->n_cols = cols;
    this->mat = new float *[rows];
    for (int i = 0; i < rows; i++)
      this->mat[i] = new float[cols];
  }
  /**
   * Matrix::Matrix(const Matrix &p1)
   *
   * Copy-constructor for Matrix.
   */
  Matrix::Matrix(const Matrix &p1)
  {
    this->n_rows = p1.n_rows;
    this->n_cols = p1.n_cols;
    this->mat = new float *[this->n_rows];

    for (int i = 0; i < this->n_rows; i++)
    {
      this->mat[i] = new float[this->n_cols];
      for (int j = 0; j < this->n_cols; j++)
      {
        this->mat[i][j] = p1.mat[i][j];
      }
    }
  }
  /**
   * Matrix::~Matrix()
   *
   * Destructor for Matrix.
   */
  Matrix::~Matrix()
  {
    for (int i = 0; i < n_rows; i++)
      delete[] this->mat[i];
    delete[] this->mat;
  }

  //Math functions for Matrix

  /**
   * Matrix Matrix::operator+(const Matrix &m1)
   *
   * Adds the given Matrix to this Matrix. Returns the result of the
   * addition.
   */
  Matrix Matrix::operator+(const Matrix &m1)
  {
    Matrix ans(m1);
    for (int i = 0; i < ans.n_rows; i++)
      for (int j = 0; j < ans.n_cols; j++)
      {
        ans.mat[i][j] = m1.mat[i][j] + mat[i][j];
      }
    return ans;
  }
  /**
   * Matrix Matrix::operator-(const Matrix &m1)
   *
   * Subtracts the given Matrix from this Matrix. Returns the result of
   * the subtraction.
   */
  Matrix Matrix::operator-(const Matrix &m1)
  {
    Matrix ans(m1);
    for (int i = 0; i < ans.n_rows; i++)
      for (int j = 0; j < ans.n_cols; j++)
      {
        ans.mat[i][j] = this->mat[i][j] - m1.mat[i][j];
      }

    return ans;
  }
  /**
   * Matrix Matrix::operator*(const Matrix &m1)
   *
   * Multiplies this Matrix by the given Matrix. Returns the result of
   * the multiplication.
   */
  Matrix Matrix::operator*(const Matrix &m1)
  {
    Matrix ans(this->n_rows, m1.n_cols);
    ans.Clear();
    for (int i = 0; i < ans.n_rows; i++)
      for (int j = 0; j < ans.n_cols; j++)
        for (int k = 0; k < n_cols; k++)
        {
          ans.mat[i][j] += this->mat[i][k] * m1.mat[k][j];
        }
    return ans;
  }
  /**
   * Matrix Matrix::operator*(float scale)
   *
   * Returns the result of multiplying this Matrix by the given scale.
   */
  Matrix Matrix::operator*(float scale)
  {
    Matrix ans(this->n_rows, this->n_cols);

    for (int i = 0; i < this->n_rows; i++)
      for (int j = 0; j < this->n_cols; j++)
      {
        ans.mat[i][j] = this->mat[i][j] * scale;
      }
    return ans;
  }
  /**
   * Matrix Matrix::Transpose()
   *
   * Transposes the given matrix.
   */
  Matrix Matrix::Transpose()
  {
    Matrix ans(this->n_cols, this->n_rows);

    for (int i = 0; i < this->n_rows; i++)
      for (int j = 0; j < this->n_cols; j++)
      {
        ans.mat[j][i] = this->mat[i][j];
      }
    return ans;
  }
  /**
   * Matrix Matrix::LeastSquaresLinearRegression()
   *
   * Calculates a Beta hat (AT * A)^-1 * AT * b, where xT represents a
   * matrix transposition, x^-1 represents an inverted matrix, and b is
   * the last column of this matrix.
   */
  Matrix Matrix::LeastSquaresLinearRegression()
  {
    Matrix A(this->n_rows, this->n_cols);
    for (int i = 0; i < this->n_rows; i++)
    {
      for (int j = 0; j < this->n_cols; j++)
      {
        A.mat[i][j] = this->mat[i][j];
        if (j == this->n_cols - 1)
        {
          A.mat[i][j] = 1;
        }
      }
    }

    Matrix b(this->n_rows, 1);
    for (int i = 0; i < this->n_rows; i++)
    {
      b.mat[i][0] = this->mat[i][(this->n_cols - 1)];
    }

    Matrix AT = A.Transpose();
    Matrix A_ = AT * A;
    Matrix Ai = A_.Invert();
    Matrix P1 = Ai * AT;

    Matrix ans = P1 * b;
    return ans;
  }
  /*This function finds the inverse of a matrix that is fed into it using the algorithm given in the data sheet
    We first divide A into four sub matricies, B, C transposed, C and D, where B, C, and D are symmetric and are n/2 x n/2 matricies. Inverse = matrix^-1, Transposed = matrixT
    We then recursively compute B^-1
    We then compute W=C * B^-1 and WT = B^-1 * CT
    We then compute X = W * CT
    Then S = D - X
    Then recursievely compute V = S^-1
    Then compute Y = S^-1 * W and YT
    We Set T = -(YT)
    And U = -(Y)
    We then compute Z = WT * Y
    Set R = B^-1 + Z
    And assemble the inverse of A with R being the upper left quadrant, T the upper right quadrant, U the lower left quadrant, and V the lower right quadrant.*/
  Matrix Matrix::Invert()
  {
    // Special-case for a one-element matrix
    if (this->n_cols == 1 && this->n_rows == 1)
    {
      Matrix base(1, 1);
      base.mat[0][0] = 1 / this->mat[0][0];
      return base;
    }

    bool powerOfTwo = !(this->n_cols == 0) && !(this->n_cols & (this->n_cols - 1));
    if (!powerOfTwo)
    {
      //Checks how much we need to pad
      int power = 2;
      //increments our power of two until it is larger than the number of cols
      while (power < this->n_cols)
      {
        power = power * 2;
      }
      //creates our matrix temp
      Matrix temp(power, power);
      //Makes it an identiy matrix
      temp.Identity();
      //Fills it with our input data
      for (int i = 0; i < this->n_rows; i++)
      {
        for (int j = 0; j < this->n_cols; j++)
          temp.mat[i][j] = this->mat[i][j];
      }
      //inverts the temp matrix
      Matrix tempI = temp.Invert();
      //Creates ans to remove the padded matrix
      Matrix ans(this->n_rows, this->n_cols);
      for (int i = 0; i < this->n_rows; i++)
      {
        for (int j = 0; j < this->n_cols; j++)
          ans.mat[i][j] = tempI.mat[i][j];
      }
      //returns our inverted matrix
      return ans;
    }

    int cols = this->n_cols / 2;
    int rows = this->n_rows / 2;

    Matrix B(rows, cols);
    Matrix C(rows, cols);
    Matrix CT(rows, cols);
    Matrix D(rows, cols);
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        B.mat[i][j] = this->mat[i][j];
        C.mat[i][j] = this->mat[i + rows][j];
        CT.mat[i][j] = this->mat[i][j + cols];
        D.mat[i][j] = this->mat[i + rows][j + cols];
      }
    }

    Matrix Bi = B.Invert();
    Matrix V = (D - (C * Bi) * CT).Invert();
    Matrix R = Bi + (Bi * CT) * (V * (C * Bi));
    Matrix T = (V * (C * Bi)).Transpose() * -1.0;
    Matrix U = (V * (C * Bi)) * -1.0;

    Matrix ans(this->n_rows, this->n_cols);
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        ans.mat[i][j] = R.mat[i][j];
        ans.mat[i][j + cols] = T.mat[i][j];
        ans.mat[i + rows][j] = U.mat[i][j];
        ans.mat[i + rows][j + cols] = V.mat[i][j];
      }
    }
    return ans;
  }

  //Utility functions

  /**
   * int Matrix::MatrixInput(char *file)
   *
   * Reads in data from the given filename and stores it in this Matrix.
   */
  /*void Matrix::MatrixInput(char *file)
  {
    int row = 0, col = 0;
    float num1;

    ifstream f(file);

    while (f >> num1)
    {
      this->mat[row][col] = num1;
      col++;
      if (col == this->n_cols)
      {
        row++;
        col = 0;
      }
    }

    f.close();
  }
  /**
   * void Matrix::Clear()
   *
   * Sets all elements of the matrix to 0.
   */
  void Matrix::Clear()
  {
    for (int i = 0; i < this->n_rows; i++)
      for (int j = 0; j < this->n_cols; j++)
        this->mat[i][j] = 0;
  }
  /**
   * void Matrix::Randomize()
   *
   * Sets all elements of the matrix to random ints between 0 and 9.
   */
  void Matrix::Randomize()
  {
    for (int i = 0; i < this->n_rows; i++)
      for (int j = 0; j < this->n_cols; j++)
        this->mat[i][j] = rand() % 10;
  }
  /**
   * void Matrix::Print()
   *
   * Prints the matrix to standard output.
   */
  void Matrix::Print()
  {
    //Will allow the matrix to print
    for (int i = 0; i < n_rows; i++)
    {
      for (int j = 0; j < n_cols; j++)
      {
        std::cout << this->mat[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
  /**
   * void Matrix::RandomizeDiagonal()
   *
   * Sets all elements of the Matrix to random integers between 0 and 9
   * except for the major diagonal, which is set to 0.
   */
  void Matrix::RandomizeDiagonal()
  {
    for (int i = 0; i < this->n_rows; i++)
    {
      for (int j = 0; j < this->n_cols; j++)
      {
        if (i == j)
          this->mat[i][j] = 0;
        else
          this->mat[i][j] = rand() % 10;
      }
    }
  }

  /**
   * void Matrix::RandomizeUpper()
   *
   * Sets all elements of the Matrix above the major diagonal to random
   * integers between 0 and 9, and sets the rest to 0.
   */
  void Matrix::RandomizeUpper()
  {
    for (int i = 0; i < this->n_rows; i++)
    {
      for (int j = 0; j < this->n_cols; j++)
      {
        if (i <= j)
          this->mat[i][j] = 0;
        else
          this->mat[i][j] = rand() % 10;
      }
    }
  }
  /**
   * void Matrix::Identity()
   *
   * Turns the Matrix into an identity matrix.
   */
  void Matrix::Identity()
  {
    for (int i = 0; i < this->n_rows; i++)
    {
      for (int j = 0; j < this->n_cols; j++)
      {
        if (i == j)
          this->mat[i][j] = 1;
        else
          this->mat[i][j] = 0;
      }
    }
  }
  //creates a vector (nx1) matrix
  void Matrix::VectorMatrix()
  {
    this->Randomize();
  }
  /**
   * int Matrix::MatrixTestAS(const Matrix &m1)
   *
   * Checks if this Matrix can be added to the argument.
   */
  int Matrix::MatrixTestAS(const Matrix &m1)
  {
    return m1.n_cols == this->n_cols && m1.n_rows == this->n_rows;
  }
  /**
   * int Matrix::MatrixTestMul(const Matrix &m1)
   *
   * Checks if this Matrix can be multiplied by the argument.
   */
  int Matrix::MatrixTestMul(const Matrix &m1)
  {
    return this->n_cols == m1.n_rows;
  }

  void Matrix::SetMatrix()
  {
    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[0][3] = 4;
    mat[1][0] = 2;
    mat[1][1] = 3;
    mat[1][2] = 4;
    mat[1][3] = 3;
    mat[2][0] = 3;
    mat[2][1] = 4;
    mat[2][2] = 3;
    mat[2][3] = 2;
    mat[3][0] = 4;
    mat[3][1] = 3;
    mat[3][2] = 2;
    mat[3][3] = 1;
  }

private:
  //Our private data for the matrix
  int n_rows, n_cols;
  float **mat;
};
#endif
