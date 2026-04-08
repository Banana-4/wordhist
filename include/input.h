#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "memory.h"
#include "error_codes.h"

ERROR_CODES input_loop(StrArray **words, int *h);
