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
    result = result / n;
    return result;
}

db prediction(db x, int degree_polynom, db* coefficient) {
    db result = 0;
    for (int i = 0; i < degree_polynom + 1; i++) {
        result += coefficient[i] * pow(x, i);
    }
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

db MSE_prediction(int len_map, int degree_polynom, db* test, db* coefficient, db* pred, map* map) {
    for (int j = 0; j < len_map; j++) {
        pred[j] = prediction(map[j].key, degree_polynom, coefficient);
    }
    db mse = MSE(len_map, pred, test);
    return mse;
}

void fit(db lambda, int count_steps, int degree_polynom, db* coefficient, int len_map, map* map) {
    db eps = 0.0001;

    db* pred = new db[len_map];
    db* test = new db[len_map];
    get_y_points(len_map, test, map);

    for (int i = 0; i < count_steps; i++) {
        db mse = MSE_prediction(len_map, degree_polynom, test, coefficient, pred, map);

        for (int k = 0; k <= degree_polynom; k++) {
            coefficient[k] += eps;
            db new_mse = MSE_prediction(len_map, degree_polynom, test, coefficient, pred, map);
            db delta_mse = mse - new_mse;
            coefficient[k] -= eps;

            if (delta_mse < 0) {
                coefficient[k] -= lambda;
            }
            else {
                coefficient[k] += lambda;
            }
        }
        printf("Шаг %d, MSE = %f\n", i, mse);
    }

    delete[] pred;
    delete[] test;
}

int main()
{
    filling_map(fun, points);
    print_map(points);

    db coef[3] = { 1, 1, 1 };
    fit(0.0002, 100000, 2, coef, 50, points);
    printf("%f, %f, %f\n", coef[2], coef[1], coef[0]);

    return 0;
}
