#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void complex_summ(complex* cnumber1, complex* cnumber2 )
{
    cnumber1->real= cnumber1->real + cnumber2->real;
    cnumber1->img = cnumber1->img + cnumber2->img;
}

void complex_multip(complex* cnumber1, complex* cnumber2)
{
    float creal1 = cnumber1->real;
    cnumber1->real = (cnumber1->real * cnumber2->real ) - (cnumber1->img * cnumber2->img );
    cnumber1->img = (cnumber1->img * cnumber2->real ) + (cnumber2->img * creal1 );
}

void copybytes(void *from, void *to, int size)
{
    char * fromc = (char *)from;
    char * toc = (char *)to;
    for (int i = 0; i < size; i++)
    {
        toc[i] = fromc[i];
    }
}

matrix* enter_matrix()    /*Вводит двумерный массив*/
{
    printf("Выберите тип чисел:\n" );
    printf("1. Вещественные числа.\n" );
    printf("2. Комплексные числа.\n" );
    matrix* matrix = malloc(sizeof(matrix ));
    char button = getch();
    if (button == 49)
    {
        matrix->flag = 0;
        printf("Введите порядок матрицы.\n" );
        scanf("%d", &matrix->size);
        printf("Введите матрицу.\n");
        matrix->arr = (float** )malloc(matrix->size * sizeof(float* ));
            for (int i = 0; i < matrix->size; i++ )
                matrix->arr[i] = (float* )malloc(matrix->size * sizeof(float ));

        float** parr = (float** )matrix->arr;
        for (int i = 0; i < matrix->size; i++ )
            for (int j = 0; j < matrix->size; j++ )
                scanf("%f", &parr[i][j] );

    }
    if (button == 50)
    {
        matrix->flag = 1;
        printf("Введите порядок матрицы.\n" );
        scanf("%d", &matrix->size);
        printf("Введите матрицу.\n");
        matrix->arr = malloc(matrix->size * sizeof(complex*));
        complex** parr = (complex** )matrix->arr;
            for (int i = 0; i < matrix->size; i++ )
                parr[i] = (complex *)malloc(matrix->size * sizeof(complex ));
        for (int i = 0; i < matrix->size; i++ )
            for (int j = 0; j < matrix->size; j++ )
            {
                float real, img;
                scanf("%f %f", &real, &img );
                copybytes(&real, &parr[i][j].real, sizeof(float ));
                copybytes(&img, &parr[i][j].img, sizeof(float ));
            }

    }
    return matrix;
}

void program_exit()
{
    printf("Для выхода из программы нажмите \"пробел\", чтобы продолжить нажмите любую другую клавишу.\n" );
    char button = getch();
    if (button == 32)
    {
        exit(0 );
    }
    main();
}

matrix* multiplication_by_a_constant()
{
    matrix* matrix = enter_matrix();
    if (matrix->flag == 0 | matrix->flag == 1)
        printf("Введите константу:\n" );
    if (matrix->flag == 0 )
    {
        float** parr = (float** )matrix->arr;
        float k;
        scanf("%f", &k );
        for (int i = 0; i < matrix->size; i++ )
            for (int j = 0; j < matrix->size; j++ )
            {
                parr[i][j] = parr[i][j] * k;
            }
    }
    if (matrix->flag == 1 )
    {
        complex** parr = (complex** )matrix->arr;
        complex* k = (complex* )malloc(sizeof(complex ));
        scanf("%f %f", &k->real, &k->img);
        for (int i = 0; i < matrix->size; i++ )
            for (int j = 0; j < matrix->size; j++ )
            {
                 complex_multip(&parr[i][j], k );
            }
    }
    return matrix;
}

matrix* matrix_summ()
{
    printf("Первая матрица\n");
    matrix* matrix1 = enter_matrix();

    printf("Вторая матрица\n");
    matrix* matrix2 = enter_matrix();

    if (matrix1->size != matrix2->size)
    {
        printf("Матрицы имеют разную размерность!\n");
        program_exit();
    }
    if (matrix1->size == matrix2->size)
    {
        if (matrix1->flag == 0 && matrix2->flag == 0 )
        {
            float** parr1 = (float** )matrix1->arr;
            float** parr2 = (float** )matrix2->arr;
            for(int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                    parr1[i][j] = parr1[i][j] + parr2[i][j];
        }
        if ((matrix1->flag == 1 && matrix2->flag == 0 ) | (matrix1->flag == 0 && matrix2->flag == 1 ))
        {
            printf("Введенные матрицы разных типов!\n");
            program_exit();
        }
        if (matrix1->flag == 1 && matrix2->flag == 1 )
        {
            complex** parr1 = (complex** )matrix1->arr;
            complex** parr2 = (complex** )matrix2->arr;
            for(int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                    complex_summ(&parr1[i][j], &parr2[i][j] );
        }
    }
    return matrix1;
}

matrix* matrix_multiplication()
{
    printf("Первая матрица\n");
    matrix* matrix1 = enter_matrix();

    printf("Вторая матрица\n");
    matrix* matrix2 = enter_matrix();

    matrix* matrix3 = (matrix* )malloc(sizeof(matrix ));
    matrix3->size = matrix1->size;
    matrix3->flag = matrix1->flag;
    if (matrix1->size != matrix2->size)
    {
        printf("Матрицы имеют разную размерность!\n");
       program_exit();
    }
    if (matrix1->size == matrix2->size)
    {
        if (matrix1->flag == 0 && matrix2->flag == 0 )
        {
            float** parr1 = (float** )matrix1->arr;
            float** parr2 = (float** )matrix2->arr;
            matrix3->arr = (float** )malloc(matrix3->size * sizeof(float* ));
            for (int i = 0; i < matrix3->size; i++ )
                matrix3->arr[i] = (float* )malloc(matrix3->size * sizeof(float ));
            float** parr3 = (float** )matrix3->arr;
            for (int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                    parr3[i][j] = 0;
            for(int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                    for (int k = 0; k < matrix1->size; k++ )
                        parr3[i][j] = parr3[i][j] + parr1[i][k] * parr2[k][j];
        }
        if ((matrix1->flag == 1 && matrix2->flag == 0 ) | (matrix1->flag == 0 && matrix2->flag == 1 ))
        {
            printf("Введенные матрицы разных типов!\n");
            program_exit();
        }
        if (matrix1->flag == 1 && matrix2->flag == 1 )
        {
            complex** parr1 = (complex** )matrix1->arr;
            complex** parr2 = (complex** )matrix2->arr;
            matrix3->arr = malloc(matrix3->size * sizeof(complex*));
            complex** parr3 = (complex** )matrix3->arr;
            for (int i = 0; i < matrix3->size; i++ )
                parr3[i] = (complex *)malloc(matrix3->size * sizeof(complex ));
             for(int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                {
                    parr3[i][j].real = 0;
                    parr3[i][j].img = 0;
                }

            for(int i = 0; i < matrix1->size; i++ )
                for (int j = 0; j < matrix1->size; j++ )
                  for (int k = 0; k < matrix1->size; k++ )
                  {
                        complex cparr1 = parr1[i][k];
                        complex_multip(&parr1[i][k], &parr2[k][j] );
                        complex* copy = &parr1[i][k];
                        complex_summ(&parr3[i][j], copy );
                        parr1[i][k] = cparr1;
                  }
        }
    }
    return matrix3;
}

void print_matrix(matrix* matrix)
{
    if (matrix->flag == 0)
    {
        float** parr = (float** )matrix->arr;
        for (int i = 0; i < matrix->size; i++ )
        {
            for (int j = 0; j < matrix->size; j++ )
                printf("%.0f ", parr[i][j]);
            printf("\n");
        }
    }
    if (matrix->flag == 1)
    {
        complex** parr = (complex** )matrix->arr;
        for (int i = 0; i < matrix->size; i++)
        {
            for (int j = 0; j < matrix->size; j++ )
                printf("%.0f %.0f ", parr[i][j].real, parr[i][j].img);
            printf("\n");
        }
    }
}

void user()
{
    printf("Выберите необходимую операцию:\n" );
    printf("1. Умножение матрицы на константу.\n" );
    printf("2. Сумма двух матриц\n" );
    printf("3. Умножение матрицы на матрицу.\n" );
    char button = getch();
    if (button == 49)
    {
        matrix* matrix = multiplication_by_a_constant();
        print_matrix(matrix );
        free(matrix);
    }
    if (button == 50)
    {
        matrix* matrix = matrix_summ();
        print_matrix(matrix );
        free(matrix);
    }
    if (button == 51)
    {
        matrix* matrix = matrix_multiplication();
        print_matrix(matrix );
        free(matrix);
    }
    program_exit();
}

void comparison_float(int size, float **parr )
{
    float arr[size][size];
    for (int i = 0; i < size; i++ )
        for (int j = 0; j < size; j++ )
            scanf("%f", &arr[i][j]);
     char flag = 0;
        for (int i = 0; i < size; i++ )
            for (int j = 0; j < size; j++ )
                if (arr[i][j] != parr[i][j] )
                    flag++;
    if (flag == 0)
        printf("Верно\n");
    else
        printf("Неверно\n");
}

void comparison_complex(int size, complex **parr )
{
    complex arr[size][size];
    for (int i = 0; i < size; i++ )
        for (int j = 0; j < size; j++ )
            scanf("%f %f", &arr[i][j].real, &arr[i][j].img);
     char flag = 0;
        for (int i = 0; i < size; i++ )
            for (int j = 0; j < size; j++ )
                if (arr[i][j].real != parr[i][j].real | arr[i][j].img != parr[i][j].img )
                    flag++;
    if (flag == 0)
        printf("Верно\n");
    else
        printf("Неверно\n");
}

void test()
{
    printf("Выберите операцию\n");
    printf("1. Умножение на скаляр\n");
    printf("2. Матричное сложение\n");
    printf("3. Матричное умножение\n");
    char button = getch();
    if (button == 49)
    {
        printf("Выберите тип хранимых элементов\n");
        printf("1. Целые числа\n");
        printf("2. Комплексные числа\n");
        button = getch();
        if (button == 49)
        {
            freopen("test/input_const_mult_z.txt", "r", stdin);
            matrix* matrix = multiplication_by_a_constant();
            float** parr = (float** )matrix->arr;
            freopen("test/output_const_mult_z.txt", "r", stdin);
            comparison_float(matrix->size, parr );
        }
        if (button == 50)
        {
            freopen("test/input_const_mult_complex.txt", "r", stdin);
            matrix* matrix = multiplication_by_a_constant();
            complex** parr = (complex** )matrix->arr;
            freopen("test/output_const_mult_complex.txt", "r", stdin);
            comparison_complex(matrix->size, parr );
        }
    }
    if (button == 50)
    {
        printf("Выберите тип хранимых элементов\n");
        printf("1. Целые числа\n");
        printf("2. Комплексные числа\n");
        button = getch();
        if (button == 49)
        {
            freopen("test/input_summa_z.txt", "r", stdin);
            matrix* matrix = matrix_summ();
            float** parr = (float** )matrix->arr;
            freopen("test/output_summa_z.txt", "r", stdin);
            comparison_float(matrix->size, parr );
        }
        if (button == 50)
        {
            freopen("test/input_summa_complex.txt", "r", stdin);
            matrix* matrix = matrix_summ();
            complex** parr = (complex** )matrix->arr;
            freopen("test/output_summa_complex.txt", "r", stdin);
            comparison_complex(matrix->size, parr );
        }
    }
    if (button == 51)
    {
        printf("Выберите тип хранимых элементов\n");
        printf("1. Целые числа\n");
        printf("2. Комплексные числа\n");
        button = getch();
        if (button == 49)
        {
            freopen("test/input_mult_z.txt", "r", stdin);
            matrix* matrix = matrix_multiplication();
            float** parr = (float** )matrix->arr;
            freopen("test/output_mult_z.txt", "r", stdin);
            comparison_float(matrix->size, parr );
        }
        if (button == 50)
        {
            freopen("test/input_mult_complex.txt", "r", stdin);
            matrix* matrix = matrix_multiplication();
            complex** parr = (complex** )matrix->arr;
            freopen("test/output_mult_complex.txt", "r", stdin);
            comparison_complex(matrix->size, parr );
        }
    }
    program_exit();
}

void main()
{
    system("chcp 1251");
    system("cls");
    printf("Выберите режим работы программы\n");
    printf("1. Пользователь\n");
    printf("2. Тестировщик\n");
    char button = getch();
    if (button == 49)
        user();
    if (button == 50)
        test();
}

