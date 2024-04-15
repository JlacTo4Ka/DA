#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const long long MAX_INT = 9223372036854775807;

bool ReadMatrix(const std::string &file_name,
                std::vector<std::vector<long long>> &matrix) {
    std::ifstream inputFile(file_name);

    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return false;
    }

    long long int sizeof_rows, sizeof_cols;
    inputFile >> sizeof_rows >> sizeof_cols;
    matrix.resize(sizeof_rows, std::vector<long long int>(sizeof_cols));

    for (int row = 0; row < sizeof_rows; row++) {
        for (int column = 0; column < sizeof_cols; column++) {
            inputFile >> matrix[row][column];
        }
    }

    inputFile.close();
    return true;
}

    void Solve(const std::vector<std::vector<long long>> &matrix) {
    long long int sizeof_rows = matrix.size();
    long long int sizeof_cols = matrix[0].size();

    long long int matrix_support[sizeof_rows][sizeof_cols];
    long long int matrix_path[sizeof_rows][sizeof_cols];

    for (int row = 0; row < sizeof_rows; row++) {
        for (int column = 0; column < sizeof_cols; column++) {
            matrix_path[row][column] = 0;
        }
    }

    for (int row = 0; row < sizeof_rows; row++) {
        for (int column = 0; column < sizeof_cols; column++) {
            if (row == 0) {
                matrix_support[0][column] = matrix[0][column];
            }
            if (row != 0 && column == 0) {
                    matrix_support[row][0] =
                        std::min(matrix_support[row - 1][0], matrix_support[row - 1][1]) +
                            matrix[row][0];
            }
            if (row != 0 && column == sizeof_cols - 1) {
                matrix_support[row][sizeof_cols - 1] = std::min(matrix_support[row - 1][sizeof_cols - 1],
                                                matrix_support[row - 1][sizeof_cols - 2]) +
                                        matrix[row][sizeof_cols - 1];
            }
            if (row != 0 && column != sizeof_cols - 1 && column != 0) {
                matrix_support[row][column] = std::min(std::min(matrix_support[row - 1][column - 1],
                                                    matrix_support[row - 1][column]),
                                        matrix_support[row - 1][column + 1]) +
                                    matrix[row][column];
            }
        }
    }

    long long int min_sum = MAX_INT;
    long long int cur_col[sizeof_rows];
    for (int column = 0; column < sizeof_cols; column++) {
        if (matrix_support[sizeof_rows - 1][column] < min_sum) {
            min_sum = matrix_support[sizeof_rows - 1][column];
            cur_col[0] = column;
        }
    }
    matrix_path[sizeof_rows - 1][cur_col[0]] = 1;

    int count = 0;
    for (int row = sizeof_rows - 1; row >= 0; row--) {
        if (cur_col[count] != 0 && cur_col[count] != sizeof_cols - 1 && row != 0) {
            if (matrix_support[row - 1][cur_col[count] - 1] <=
                    matrix_support[row - 1][cur_col[count]] &&
                matrix_support[row - 1][cur_col[count] - 1] <=
                    matrix_support[row - 1][cur_col[count] + 1]) {
                        
                cur_col[count + 1] = cur_col[count] - 1;
                matrix_path[row - 1][cur_col[count] - 1] = 1;
            }
            if (matrix_support[row - 1][cur_col[count]] <=
                    matrix_support[row - 1][cur_col[count] - 1] &&
                matrix_support[row - 1][cur_col[count]] <=
                    matrix_support[row - 1][cur_col[count] + 1]) {

                cur_col[count + 1] = cur_col[count];
                matrix_path[row - 1][cur_col[count]] = 1;
            }
            if (matrix_support[row - 1][cur_col[count] + 1] <=
                    matrix_support[row - 1][cur_col[count] - 1] &&
                matrix_support[row - 1][cur_col[count] + 1] <=
                    matrix_support[row - 1][cur_col[count]]) {

                cur_col[count + 1] = cur_col[count] + 1;
                matrix_path[row - 1][cur_col[count] + 1] = 1;
            }
        }
        if (row == 0 && cur_col[count - 1] != 0 && cur_col[count - 1] != sizeof_cols - 1) {
            if (matrix_support[row][cur_col[count - 1] - 1] <=
                    matrix_support[row][cur_col[count - 1]] &&
                matrix_support[row][cur_col[count - 1] - 1] <=
                    matrix_support[row][cur_col[count - 1] + 1]) {

                cur_col[count] = cur_col[count - 1] - 1;
                matrix_path[0][cur_col[count - 1] - 1] = 1;
                break;
            }
            if (matrix_support[row][cur_col[count - 1]] <=
                    matrix_support[row][cur_col[count - 1] - 1] &&
                matrix_support[row][cur_col[count - 1]] <=
                    matrix_support[row][cur_col[count - 1] + 1]) {

                cur_col[count] = cur_col[count - 1];
                matrix_path[0][cur_col[count - 1]] = 1;
                break;
            }
            if (matrix_support[row][cur_col[count - 1] + 1] <=
                    matrix_support[row][cur_col[count - 1] - 1] &&
                matrix_support[row][cur_col[count - 1] + 1] <=
                    matrix_support[row][cur_col[count - 1]]) {

                cur_col[count] = cur_col[count - 1] + 1;
                matrix_path[0][cur_col[count - 1] + 1] = 1;
                break;
            }
        }
        if (cur_col[count] == 0 && row != 0) {
            if (matrix_support[row - 1][cur_col[count]] <=
                    matrix_support[row - 1][cur_col[count] + 1]) {

                cur_col[count + 1] = cur_col[count];
                matrix_path[row - 1][cur_col[count]] = 1;
            }
            if (matrix_support[row - 1][cur_col[count] + 1] <
                    matrix_support[row - 1][cur_col[count]]) {

                cur_col[count + 1] = cur_col[count] + 1;
                matrix_path[row - 1][cur_col[count] + 1] = 1;
            }
        }

        if (cur_col[count - 1] == 0 && row == 0) {
            if (matrix_support[0][cur_col[count - 1]] <=
                    matrix_support[0][cur_col[count - 1] + 1]) {

                cur_col[count] = cur_col[count - 1];
                matrix_path[0][cur_col[count - 1]] = 1;
                break;
            } 
        if (matrix_support[0][cur_col[count - 1] + 1] <
                matrix_support[0][cur_col[count - 1]]) {

            cur_col[count] = cur_col[count - 1] + 1;
            matrix_path[0][cur_col[count - 1] + 1] = 1;
            break;
        }
        }
        if (cur_col[count] == sizeof_cols - 1 && row != 0) {
            if (matrix_support[row - 1][cur_col[count] - 1] <=
                    matrix_support[row - 1][cur_col[count]]) {

                cur_col[count + 1] = cur_col[count] - 1;
                matrix_path[row - 1][cur_col[count] - 1] = 1;
            }
            if (matrix_support[row - 1][cur_col[count]] <
                    matrix_support[row - 1][cur_col[count] - 1]) {

                cur_col[count + 1] = cur_col[count];
                matrix_path[row - 1][cur_col[count]] = 1;
            }
        }

        if (cur_col[count - 1] == sizeof_cols - 1 && row == 0) {
            if (matrix_support[0][cur_col[count - 1] - 1] <=
                    matrix_support[0][cur_col[count - 1]]) {

                cur_col[count] = cur_col[count - 1] - 1;
                matrix_path[0][cur_col[count - 1] - 1] = 1;
                break;
            }
            if (matrix_support[0][cur_col[count - 1]] <
                    matrix_support[0][cur_col[count - 1] - 1]) {

                cur_col[count] = cur_col[count - 1];
                matrix_path[0][cur_col[count - 1]] = 1;
                break;
            }
        }
        if (row != 0)
            count++;
    }
    std::ofstream outputFile("output.txt");

    outputFile << min_sum << std::endl;

    bool flag_otv;
    for (int row = 0; row < sizeof_rows; row++) {
        flag_otv = 0;
        for (int column = 0; column < sizeof_cols; column++) {
            if (matrix_path[row][column] == 1 && flag_otv == false) {
                outputFile << '(' << row+1 << ',' << column+1 << ") ";
                flag_otv = true;
            }
        }
    }
    outputFile.close(); 
}

int main() {
  std::vector<std::vector<long long>> matrix;
  unsigned int err = 0;

  if (ReadMatrix("input.txt", matrix) != true) {
    err = 1;
  }

  Solve(matrix);

  return err;
}
