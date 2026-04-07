#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "memory.h"
typedef enum {
INP_NO_ERR,
INP_MEM_FAIL,
}INP_ERR;

INP_ERR input_loop(StrArray **words, int *h);
