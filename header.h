typedef struct matrix
{
    int size,flag;
    void** arr;

} matrix;

typedef struct complex
{
   float real, img;
} complex;

void complex_summ(complex* cnumber1, complex* cnumber2 );

void complex_multip(complex* cnumber1, complex* cnumber2);

void copybytes(void *from, void *to, int size);

matrix* enter_matrix();

void program_exit();

matrix* multiplication_by_a_constant();

matrix* matrix_summ();

matrix* matrix_multiplication();

void print_matrix(matrix* matrix);

void user();

void comparison_float(int size, float **parr );

void comparison_complex(int size, complex **parr );

void test();

void main();
