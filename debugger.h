#pragma once
#include "stdio.h"

#define breakpoint debugf("in file %s function %s reach line %lu with breakpoint\n",__FILE__, __func__,__LINE__);