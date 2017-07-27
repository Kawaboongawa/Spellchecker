#pragma once

#include <string.h>
#include <stdio.h>

#include "tools.h"


void levenshtein(char *s1, char *s2, uint len1,
                     uint len2, uint matrix[][len2]);
