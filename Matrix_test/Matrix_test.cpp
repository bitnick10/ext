#include <ext/ext.h>

void debug() {
}
void main() {
    debug();
    Describe("Matrix", []() {
        It("should be able to do product math", []() {
            int a[] = {1, 2, 3, 4};
            int b[] = { -1, 0, 1, 2};
            int c[] = { -1, 0, 3, 6};
            Matrix<int> matrix1(a, 2, 2);
            Matrix<int> matrix2(b, 2, 2);
            Matrix<int> result = Matrix<int>::Product(matrix1, matrix2);
            Expect(result).ToBe(Matrix<int>(c, 2, 2));
        });
    });
}