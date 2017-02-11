
#include <klee/klee.h>

int calculate_output(int x, int y)
{
    int z;

    if (x < 5) {
        z = x + y;
    } else {
        z = x * y;
    }
    return z;
}

int main()
{
    int output;
    int input_x, input_y;
    
    klee_make_symbolic(&input_x, sizeof(input_x), "input_x");
    klee_make_symbolic(&input_y, sizeof(input_y), "input_y");
    
    output = calculate_output(input_x, input_y);

    klee_output_error(output);
    
    return 0;
}
