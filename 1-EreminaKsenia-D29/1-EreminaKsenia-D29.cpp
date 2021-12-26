#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PLUS_RANGE(val) (((val) >= 0) ? (val): 0)

#pragma warning(disable:4996)

typedef struct {
    int l_t;
    int d_t;
    int w_t;
    int used_flag;
} Good;

int solver(Good* goods, int N, int K,
    int* sigma, int* ans, int sum,
    int first_iter_flag, int iterator, Good* prev) {

    if (iterator == N || sum > K) {
        if (sum <= K) {
            return 1;
        }
        else {
            return 0;
        }
    }
    for (int i = 0; i < N; i++) {
        if (!goods[i].used_flag) {

            goods[i].used_flag = 1;
            ans[iterator] = i + 1;

            if (first_iter_flag) {
                sigma[iterator] = goods[i].d_t - goods[i].l_t;
            }
            else {
                sigma[iterator] = sigma[iterator - 1] + prev->l_t;
            }

            int sum_val = PLUS_RANGE((sigma[iterator] + goods[i].l_t - goods[i].d_t)) * goods[i].w_t;
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

int delivery_solver(Good* goods, int N, int K, int* ans) {
    int* sigma = (int*)malloc(sizeof(int) * N);
    if (sigma != NULL)
        memset(sigma, '0', sizeof(int) * N); 
    int answer = solver(goods, N, K, sigma, ans, 0, 1, 0, NULL);
    free(sigma);
    return answer;
}

int main(void)
{
    FILE* input = fopen("input.txt", "r");
    int n, k;

    if (input == NULL)
    {
        printf("no file\n");
        fclose(input);
        return 1;
    }

    if (fscanf(input, "%d %d\n", &n, &k) != 2)
    {
        printf("no elements\n");
        fclose(input);
        return 1;
    }
            
    Good* goods = (Good*)malloc(sizeof(Good) * n);
    if (goods == NULL)
    {
        printf("error\n");
        free(goods);
        fclose(input);
        return 1;
    }
    else
        memset(goods, 0, sizeof(Good) * n);
    
    int* ans = (int*)malloc(sizeof(int) * n);
    if (ans == NULL)
    {
        printf("error\n");
        free(ans);
        free(goods);
        fclose(input);
        return 1;
    }
    else
        memset(ans, '0', sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        if (fscanf(input, "%d %d %d", &goods[i].l_t, &goods[i].d_t, &goods[i].w_t) == 3)
            continue;
    }

    int cheak_solver = delivery_solver(goods, n, k, ans);

    FILE* output = fopen("output.txt", "w");

    if (cheak_solver) {
        for (int i = 0; i < n; i++) {
            fprintf(output,"%d ", ans[i]);
        }
    }
    else {
        fprintf(output, "%d ", 0);
    }
    fclose(output);
    fclose(input);
    free(ans);
    free(goods);
    return 0;
}