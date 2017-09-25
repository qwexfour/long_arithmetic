#include"longalib.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>


int construct_with_str_longa( uint_longa_t *number, long unsigned int n_decimal, char *str_number )
{
	long int position;         //position in str_number
	int i;                     //position in internal array digits
	char str_digit[POWER_OF_BASE_LONGA + 1];   //to copy a piece of str_number that represent a digit there
	int n;
	//preporations
	if( n_decimal == 0 )
		return -1;
	n = ( n_decimal - 1 ) / POWER_OF_BASE_LONGA + 1;   //the number of digits of our system
	digit_longa_t *digits = (digit_longa_t*)calloc( n, sizeof( digit_longa_t ) );
	if( digits == NULL )
		return -1;
	str_digit[POWER_OF_BASE_LONGA] = '\0';  //we won't copy null
	//dealing with str_number
	for( position = n_decimal - POWER_OF_BASE_LONGA, i = 0; position > -POWER_OF_BASE_LONGA; position -= POWER_OF_BASE_LONGA, i++ )
	{
		if( position >= 0 )
			strncpy( str_digit, str_number + position, POWER_OF_BASE_LONGA );   //copping a piece of str_number to str_digit
		else
		{
			strncpy( str_digit, str_number, position + POWER_OF_BASE_LONGA );   //to copy the rest
			str_digit[position + POWER_OF_BASE_LONGA] = '\0';   
		}
		digits[i] = atoi( str_digit );
	}
	//moving to structure
	number->n = n;
	number->digits = digits;
	return 0;
}

int construct_longa( uint_longa_t *number, long unsigned int n_decimal )
{
	int n;
	if( n_decimal == 0 )
		return -1;
	n = ( n_decimal - 1 ) / POWER_OF_BASE_LONGA + 1;   //the number of digits of our system
	digit_longa_t *digits = (digit_longa_t*)calloc( n, sizeof( digit_longa_t ) );
	if( digits == NULL )
		return -1;
	number->n = n;
	number->digits = digits;
	return 0;
}

int destruct_longa( uint_longa_t *number )
{
	if( number->digits == NULL )
		return -1;
	number->n = 0;
	free( number->digits );
	return 0;
}

int dump_longa( uint_longa_t number )
{
	printf( "%d\n", number.n );
	for( int i = 0; i < number.n; i++ )
		printf( "    %d:%d\n", i, number.digits[i] );
	return 0;
}

bool is_equal_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n != b.n )
		return false;
	for( int i = 0; i < a.n; i++ )
		if( a.digits[i] != b.digits[i] )
			return false;
	return true;
}

bool is_greater_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n > b.n )
		return true;
	if( a.n < b.n )
		return false;
	for( int i = a.n - 1; i >= 0; i-- )
		if( a.digits[i] > b.digits[i] )
			return true;
		else
			if( a.digits[i] < b.digits[i] )
				return false;
	return false;
}

bool is_less_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n < b.n )
		return true;
	if( a.n > b.n )
		return false;
	for( int i = a.n - 1; i >= 0; i-- )
		if( a.digits[i] < b.digits[i] )
			return true;
		else
			if( a.digits[i] > b.digits[i] )
				return false;
	return false;
}



