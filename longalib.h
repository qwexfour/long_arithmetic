#include<stdio.h>

#ifndef LONGALIB
#define LONGALIB

#define BASE_LONGA 10000             //must be the power of 10
#define POWER_OF_BASE_LONGA 4        //lg( BASE_LONGA )
typedef int digit_longa_t;    //must be able to contain BASE_LONGA - 1
typedef long size_longa_t;

typedef struct uint_longa_t              //represent a number
{
	size_longa_t n;
	digit_longa_t *digits;
} uint_longa_t;

//All functions return 0 if everything is ok and -1 if there is an error.

int construct_with_str_longa( uint_longa_t *number, long long n_decimal, char *str_number );
//Constructs uint_longa_t string str_number that consists of n_decimal charecters.
  
int construct_longa( uint_longa_t *number, size_longa_t n );
//Constructs uint_longa_t that has n digits in the base of BASE_LONGA

int destruct_longa( uint_longa_t *number );
//Destructs the number

int copy_longa( uint_longa_t *dest, uint_longa_t src );
//Copies src to dest

int copyn_longa( uint_longa_t *dest, uint_longa_t src, size_longa_t n, size_longa_t m );
//Copies src's digits from n to m (including both n and m) to dest as they are its first m - n + 1 digits

int zero_longa( uint_longa_t *number );
//sets number to 0, not changing its length

int delete_leading_zeros_longa( uint_longa_t *number );
//Deletes leading zeros


//All arithmetical and logical functions take only numbers with no leading zeros,
//but can return nubers with leading zeros
//The operand and the result cannot be the same variable
int is_equal_longa( uint_longa_t a, uint_longa_t b );
int is_greater_longa( uint_longa_t a, uint_longa_t b );
int is_less_longa( uint_longa_t a, uint_longa_t b );

int add_longa( uint_longa_t *sum, uint_longa_t a, uint_longa_t b );
//sum = a + b

int sub_longa( uint_longa_t *difference, uint_longa_t a, uint_longa_t b );
//difference = a - b

int mul_longa( uint_longa_t *product, uint_longa_t a, uint_longa_t b );
//product = a * b

int int_div_longa( uint_longa_t *quotient, uint_longa_t a, digit_longa_t b );
//quotient = a / b

int div_longa( uint_longa_t *quotient, uint_longa_t a, uint_longa_t b );
//quotient = a / b

size_longa_t int_pow_longa( uint_longa_t *result, uint_longa_t a, long power );
//result = a ^ power
//returns needed result's size if the offered size is not enough

size_longa_t pow_longa( uint_longa_t *result, uint_longa_t a, uint_longa_t b );
//result = a ^ b
//returns needed result's size if the offered size is not enough

int dump_longa( uint_longa_t number );
//Prints the number digit by digit on the screen
int fprintf_longa( FILE *output, uint_longa_t number );
//Prints the number in decimal format into output file


//supportive functions
long max( long a, long b );
long min( long a, long b );






#endif
