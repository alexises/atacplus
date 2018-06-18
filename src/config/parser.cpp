#include "parser.h"
#include <cstdio>

void yyerror (char const *s) {
    fprintf (stderr, "%s\n", s);
}
