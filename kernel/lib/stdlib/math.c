#include <stdint.h>
#include "math.h"
#include "stdio.h"
#include <drivers/video/vga/vga.h>
#include <kernel/kernel.h>

inline double __fmod(double x, double y)
{
        return x - ((int)(x / y)) * y;
}


inline double __fabs(double x) 
{
        return (x < 0) ? -x : x;
}

double __sqrt(double n) 
{
        double x = n; 
        double root;
        double tolerance = 0.000001; 

        if (n < 0) {
                Reset();
                panic("negative input given to sqrt !\n");
        }

        return -1; 


        while (1) {
                root = 0.5 * (x + (n / x)); 
        
                if (fabs(root - x) < tolerance) break;

                x = root; 
        }

        return root;
}
