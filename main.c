#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void array_generation(int n, double* m){//n - размер массива, m - указатель на начало массива, a - параметр
    short a;
    printf("Enter 1 to make sorted array\n");
    printf("Enter 2 to make back-sorted array\n");
    printf("Enter 3,4 to make unsorted array:\n");
    scanf("%d", &a);
    for(int i = 0; i < n; i++){
        if(a == 1){
            m[i] = (n - i);//элементы упорядочены
        }
        else if(a == 2){
            m[i] = (i + 1) / 1.0;//элементы упорядочены в обратном порядке
        }
        else{
            m[i] = (double)((rand() - rand())/(1.0 * rand()));//расстановка элементов случайна
        }
    }
}

void shell_sort(int n, double *m){
    int j, k, d = n;
    int com = 0, mov = 0;//задаем переменные для подсчета сравнений и перестановок
    do{
        d = d / 2;//задаем шаг сортировки, каждую итерацию уменьшая его
        for(int i = 0; n > i; i++){
            j = i;
            k = i - d;
            while(k >= 0 && ++com && (fabs(m[k]) < fabs(m[j])) ){//помещаем каждый элемент в группе между
                m[k] = m[k] + m[j];                                    //большим и меньшим его
                m[j] = m[k] - m[j];
                m[k] = m[k] - m[j];
                j = k;
                k = k - d;
                mov++;
            }
        }
    }while(d > 0);
    printf("Number of comparasions: %d Number of moves: %d\n", com, mov);
}

void heapify(double *m, int n, int i, int* com, int* mov){
    int min = i;
    if((2 * i + 1 < n) && ++(*com) && (fabs(m[min]) > fabs(m[2 * i + 1]))){//сравниваем корень и левого сына
        min = 2 * i + 1;
    }
    if((2 * i + 2 < n) && ++(*com) && (fabs(m[min]) > fabs(m[2 * i + 2]))){//сравниваем наименьший элемент из корня
        min = 2 * i + 2;                                                         //и левого сына с правым сыном
    }
    if(min != i){//если один из сыновей больше корня,
        (*mov)++;//меняем их местами и рекурсивно используем функцию для соответствующего поддерева
        m[i] = m[i] + m[min];
        m[min] = m[i] - m[min];
        m[i] = m[i] - m[min];
        heapify(m, n, min, com, mov);
    }
}

void heap_sort(int n, double *m){
    int com = 0,mov = 0;//задаем переменные для подсчета сравнений и перестановок
    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(m, n, i, &com, &mov);//создаем кучу из исходного массива
    }
    for (int i = n - 1; i > 0; i--){
        mov++;//подсчитываем перестановки
        m[0] = m[0] + m[i];//переставляем первый и последний элементы
        m[i] = m[0] - m[i];
        m[0] = m[0] - m[i];
        heapify(m, i, 0, &com, &mov);//укорачиваем массив и делаем кучу из оставшихся элементов
    }                                               //повторяем пока весь массив не отсортирован
    printf("Number of comparasions: %d Number of moves: %d\n", com , mov);
}

int main(){
    srand(time(NULL));
    printf("Enter N:\n");
    int n;
    scanf("%d", &n);
    double *m = (double *) malloc(n * sizeof(double));
    double *md = (double *) malloc(n * sizeof(double));
    array_generation(n, m);//генерируем массив
    printf("Generated array:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", m[i]);
        md[i] = m[i];//дублируем массив для того чтобы проверить обе сортировки
    }
    printf("\n");
    printf("Shell-sorted array:\n");
    shell_sort(n,m);//используем сортировку Шелла
    for(int i = 0; i < n; i++){
        printf("%f ", m[i]);
    }
    printf("\n");
    printf("Heap-sorted array:\n");
    heap_sort(n,md);//используем пирамидальную сортировку
    for(int i = 0; i < n; i++){
        printf("%f ", md[i]);
    }
    free(m);//освобождаем память
    free(md);
    return 0;
}
