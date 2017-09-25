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

bool is_equal_longa( uint_longa_t a, uint_longa_t b );
bool is_greater_longa( uint_longa_t a, uint_longa_t b );
bool is_less_longa( uint_longa_t a, uint_longa_t b );

int dump_longa( uint_longa_t number );







#endif
