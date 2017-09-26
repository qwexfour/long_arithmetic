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

int construct_longa( uint_longa_t *number, long unsigned int n )
{
	if( n == 0 )
		return -1;
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

int is_equal_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n != b.n )
		return 0;
	for( int i = 0; i < a.n; i++ )
		if( a.digits[i] != b.digits[i] )
			return 0;
	return 1;
}

int is_greater_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n > b.n )
		return 1;
	if( a.n < b.n )
		return 0;
	for( int i = a.n - 1; i >= 0; i-- )
		if( a.digits[i] > b.digits[i] )
			return 1;
		else
			if( a.digits[i] < b.digits[i] )
				return 0;
	return 0;
}

int is_less_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n < b.n )
		return 1;
	if( a.n > b.n )
		return 0;
	for( int i = a.n - 1; i >= 0; i-- )
		if( a.digits[i] < b.digits[i] )
			return 1;
		else
			if( a.digits[i] > b.digits[i] )
				return 0;
	return 0;
}

int delete_leading_zeros_longa( uint_longa_t *number )
{
	int i;
	if( number->n == 1 )
		return 0;
	if( number->n == 0 || number->digits == NULL )
		return -1;
	for( i = number->n - 1; i > 0; i-- )
		if( number->digits[i] != 0 )
			break;
	number->n = i + 1;
	number->digits = realloc( number->digits, number->n );
	return 0;
}


int add_longa( uint_longa_t *sum, uint_longa_t a, uint_longa_t b )
{
	int sum_len = max( a.n, b.n ) + 1;
	int min_len = min( a.n, b.n );
	int i = 0;
	int carry_over = 0;
	//
	construct_longa( sum, sum_len );
	for( i = 0; i < min_len; i++ )
	{
		sum->digits[i] = ( a.digits[i] + b.digits[i] + carry_over ) % BASE_LONGA;
		carry_over = ( a.digits[i] + b.digits[i] + carry_over ) / BASE_LONGA;
	}
	if( a.n > b.n )
		for( i = min_len; i < a.n; i++ )
		{
			sum->digits[i] = ( a.digits[i] + carry_over ) % BASE_LONGA;
			carry_over = ( a.digits[i] + carry_over ) / BASE_LONGA;
		}
	else
		for( i = min_len; i < b.n; i++ )
		{
			sum->digits[i] = ( b.digits[i] + carry_over ) % BASE_LONGA;
			carry_over = ( b.digits[i] + carry_over ) / BASE_LONGA;
		}
	sum->digits[sum_len - 1] = carry_over;
	return 0;
}

int sub_longa( uint_longa_t *difference, uint_longa_t a, uint_longa_t b )
{
	int carry_over = 0;
	if( is_less_longa( a, b ) )
		return -1;
	construct_longa( difference, a.n );
	for( int i = 0; i < b.n; i++ ) //because b has less digits or same
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) % BASE_LONGA;   //cause mod works wrong with negative numbers
		carry_over = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	for( int i = b.n; i < a.n; i++ )
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] + carry_over ) % BASE_LONGA;
		carry_over = ( BASE_LONGA + a.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	return 0;
}

int mul_longa( uint_longa_t *product, uint_longa_t a, uint_longa_t b )
{
	int carry_over = 0;
	long unsigned int = 0;
	long unsigned int product_len = a.n * b.n;       //TODO: check overflow
	if( construct_longa( product, product_len ) )    //if there was an error
		return -1;
	for( int j = 0; j < b.n; j++ )
	{
		carry_over = 0;
		for( int i = 0; i < a.n; i++ )
		{
			temp = a.digits[i] * b.digits[j] + product->digits[i + j] + carry_over;
			product->digits[i] = temp % BASE_LONGA;
			carry_over = temp / BASE_LONGA;
		}
		product->digits[j + a.n] = carry_over;
	}
}
