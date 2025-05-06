//Miscellaneous utility functions/macros

//Integer min/max/abs
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(a) ((a) > 0 ? (a) : -(a))

char* ordinal(unsigned int n, char buf[], int len);