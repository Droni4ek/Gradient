#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "map.h"
typedef double db;

map points[50];

db fun(double x) {
    return 0.5 * x * x + 14;
}

void filling_map(db(*fun)(db), map* points) {
    srand(42);
    db step = (rand() % 14) / (db)27;

    db x_st = -7;

    for (int i = 0; i < 50; ++i) {
        points[i].key = x_st;
        points[i].value = fun(x_st);

        x_st += step;
    }
}

void get_y_points(int n, double* res, map* points) {
    for (int i = 0; i < n; i++)
        res[i] = points[i].value;
}

void get_x_points(int n, double* res, map* points) {
    for (int i = 0; i < n; i++)
        res[i] = points[i].key;
}

void print_map(map* points) {
    for (int i = 0; i < 50; ++i)
        printf("%f, %f \n", points[i].key, points[i].value);
}

db MSE(int n, db* y_p, db* y_t) {
    db result = 0;

    for (int i = 0; i < n; ++i)
        result += (y_p[i] - y_t[i]) * (y_p[i] - y_t[i]);

    result = result / n / (n - 1);

    return sqrt(result);
}

db prediction(db x, int degree_polynom, ...) {
    va_list args;
    va_start(args, degree_polynom);

    db result = 0;
    for (int i = 0; i < degree_polynom + 1; ++i) {
        result += va_arg(args, db) * pow(x, i);
    }

    va_end(args);

    return result;
}

void damage_points(int n, map* points) {
    srand(42);

    for (int i = 0; i < n; ++i) {
        printf("%f ", points[i].value);
        db dmage = ((rand() % 100) / 99.0 * 0.5);
        points[i].value += dmage * ((rand() % 2 == 0) ? -1 : 1);
        printf("%f %f \n", points[i].value, dmage);
    }
}

void fit(db lambda, int count_steps, int degree_polynom, db* coefficient, int len_map, db* map) {

    for (int i = 0; i < count_steps; ++i) {
    
    }

}

int main()
{
    filling_map(fun, points);

    print_map(points);

    /*db test_y[50];
    get_y_points(50, test_y, points);

    damage_points(50, points);
    db test_y_1[50];
    get_y_points(50, test_y_1, points);*/

    //printf("%f", MSE(50, test_y, test_y_1));


}