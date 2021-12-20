#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LABD_DOPF_H
#define PLUS_RANGE(val) (((val) >= 0) ? (val): 0)

typedef struct {
    int l_t;
    int d_t;
    int w_t;
    int used_flag;
} Good;

void stress_test() {
    FILE* input = fopen("C:\\Users\\79215\\Desktop\\ПолитИк\\2 курс\\3 сем\\Алгосы\\1-EreminaKsenia-D29\\input.txt", "r");
    unsigned int n, k;
    fscanf(input, "%d %d\n", &n, &k);
    Good* goods = (Good*)malloc(sizeof(Good) * n);
    memset(goods, 0, sizeof(Good) * n);
    unsigned int* ans = (unsigned int*)malloc(sizeof(unsigned int) * n);
    memset(ans, 0, sizeof(unsigned int) * n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%d %d %d", &goods[i].l_t, &goods[i].d_t, &goods[i].w_t);
    }
    unsigned long start = clock();
    int cheak_solver = delivery_solver(goods, n, k, ans);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("%f\n", time);
    FILE* output = fopen("C:\\Users\\79215\\Desktop\\ПолитИк\\2 курс\\3 сем\\Алгосы\\1-EreminaKsenia-D29\\output.txt", "w");
    if (cheak_solver) {
        for (int i = 0; i < n; i++) {
            fprintf(output, "%d ", ans[i]);
        }
    }
    else {
        fprintf(output, "%d ", 0);
    }
    fclose(output);
    fclose(input);
}

int solver(Good* goods, unsigned N, unsigned K,
    int* sigma, unsigned int* ans, unsigned sum,
    int first_iter_flag, unsigned iterator, Good* prev) {

    if (iterator == N || sum > K) {
        if (sum <= K) {
            return 1;
        }
        else {
            return 0;
        }
    }
    for (unsigned i = 0; i < N; i++) {
        if (!goods[i].used_flag) {

            goods[i].used_flag = 1;
            ans[iterator] = i + 1;

            if (first_iter_flag) {
                sigma[iterator] = goods[i].d_t - goods[i].l_t;
            }
            else {
                sigma[iterator] = sigma[iterator - 1] + prev->l_t;
            }

            unsigned sum_val = PLUS_RANGE((sigma[iterator] + goods[i].l_t - goods[i].d_t)) * goods[i].w_t;
            sum += sum_val;

            if (solver(goods, N, K, sigma, ans, sum, 0, iterator + 1, &goods[i])) {
                return 1;
            }
            sum -= sum_val;
            goods[i].used_flag = 0;
        }
    }
    return 0;
}

int delivery_solver(Good* goods, unsigned N, unsigned K, unsigned int* ans) {
    int* sigma = (int*)malloc(sizeof(int) * N);
    memset(sigma, 0, sizeof(int) * N);
    int answer = solver(goods, N, K, sigma, ans, 0, 1, 0, NULL);
    free(sigma);
    return answer;
}
