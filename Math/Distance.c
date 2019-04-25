#include "includes.h"
#include <math.h>
INT16U CalcDistance(INT16S x1,INT16S y1,INT16S x2,INT16S y2)
{
    return (INT16U)sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

