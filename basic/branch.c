/*
 * Simple branching
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>

int main()
{
    int output;
    int input_x, input_y;
    char pred;

    klee_track_error(&input_x, "input_x_error");
    klee_track_error(&input_y, "input_y_error");

    klee_make_symbolic(&pred, sizeof(char), "pred");

    if (pred) {
        output = input_x + input_y;
    } else {
        output = input_x * input_y;
    }

    klee_bound_error(output, "output", 1.3);

    return 0;
}
