#include <ext/ext.h>

void debug() {
}
void main() {
    debug();
    Describe("Matrix", []() {
        It("should be able to do dot product math", []() {
            do {
                int a[] = {1, 2, 3, 4};
                int b[] = { -1, 0, 1, 2};
                int c[] = { -1, 0, 3, 8};
                Matrix<int> matrix1(a, 2, 2);
                Matrix<int> matrix2(b, 2, 2);
                Matrix<int> result = Matrix<int>::DotProduct(matrix1, matrix2);
                Expect(result).ToBe(Matrix<int>(c, 2, 2));
            } while(0);
        });
        It("should be able to do product math", []() {
            do {
                int a[] = {1, 1, 2, 0};
                int b[] = {0, 2, 3, 1, 1, 2};
                int c[] = {1, 3, 5, 0, 4, 6};
                Matrix<int> matrix1(a, 2, 2);
                Matrix<int> matrix2(b, 3, 2);
                Matrix<int> result = Matrix<int>::Product(matrix1, matrix2);
                Expect(result).ToBe(Matrix<int>(c, 3, 2));
            } while(0);
        });
    });
}