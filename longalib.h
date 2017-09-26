#include<stdio.h>

#ifndef LONGALIB
#define LONGALIB

#define BASE_LONGA 10000             //must be the power of 10
#define POWER_OF_BASE_LONGA 4        //lg( BASE_LONGA )
typedef unsigned int digit_longa_t;    //must be able to contain BASE_LONGA - 1

typedef struct uint_longa_t              //represent a number
{
	int n;
	digit_longa_t *digits;
} uint_longa_t;

int construct_with_str_longa( uint_longa_t *number, long unsigned int n_decimal, char *str_number );
int construct_longa( uint_longa_t *number, long unsigned int n_decimal );
int destruct_longa( uint_longa_t *number );

int delete_leading_zeros_longa( uint_longa_t *number );

int is_equal_longa( uint_longa_t a, uint_longa_t b );
int is_greater_longa( uint_longa_t a, uint_longa_t b );
int is_less_longa( uint_longa_t a, uint_longa_t b );

int add_longa( uint_longa_t *sum, uint_longa_t a, uint_longa_t b );
int sub_longa( uint_longa_t *division, uint_longa_t a, uint_longa_t b );
int mul_longa( uint_longa_t *product, uint_longa_t a, uint_longa_t b );
int simple_div_longa( uint_longa_t *quotient, uint_longa_t a, digit_longa_t b );

int dump_longa( uint_longa_t number );
int fprintf_longa( FILE *output, uint_longa_t number );


long unsigned int max( long unsigned int a, long unsigned int b );
long unsigned int min( long unsigned int a, long unsigned int b );






#endif
