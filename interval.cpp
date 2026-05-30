#include "interval.h"

// Define the static class constants
const interval interval::empty(+INFINITY, -INFINITY);
const interval interval::universe(-INFINITY, +INFINITY);

// Define the global intensity constant
const interval intensity(0.000, 0.999);