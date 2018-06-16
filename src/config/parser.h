#ifndef PARSER_H
#define PARSER_H

union parser_data {
    int int_val;
    char* char_val;
};
int yylex (void);
void yyerror (char const *);

#endif
