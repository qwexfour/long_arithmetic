#include"longalib.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>


int construct_with_str_longa( uint_longa_t *number, long unsigned int n_decimal, char *str_number )
{
	long int position;         //position in str_number
	long int i;                     //position in internal array digits
	char str_digit[POWER_OF_BASE_LONGA + 1];   //to copy a piece of str_number that represent a digit there
	long int n;
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
	{
		printf( "ERROR: attempt to free a NULL pointer\n" );
		return -1;
	}
	free( number->digits );
	number->digits = NULL;
	number->n = 0;
	return 0;
}


int copy_longa( uint_longa_t *dest, uint_longa_t src )
{
	unsigned long i;
	if( src.n == 0 || dest->n < src.n )
		return -1;
	for( i = 0; i < src.n; i++ )
		dest->digits[i] = src.digits[i];
	for( i = src.n; i < dest->n; i++ )
		dest->digits[i] = 0;
	return 0;
}

int copyn_longa( uint_longa_t *dest, uint_longa_t src, unsigned long n, unsigned long m )
{
	if( n > m || dest->n < m - n + 1 || src.n < m )
		return -1;
	for( unsigned long i = 0, j = n; j <= m; i++, j++ )
		dest->digits[i] = src.digits[j];
	for( unsigned long i = m - n + 1; i < dest->n; i++ )
		dest->digits[i] = 0;
	return 0;
}

int zero_longa( uint_longa_t *number )
{
	for( long unsigned i = 0; i < number->n; i++ )
		number->digits[i] = 0;
	return 0;
}

int dump_longa( uint_longa_t number )
{
	printf( "%ld\n", number.n );
	for( int i = 0; i < number.n; i++ )
		printf( "    %d:%d\n", i, number.digits[i] );
	return 0;
}

int fprintf_longa( FILE *output, uint_longa_t a )
{
	if( a.n == 0 )
		return -1;
	fprintf( output, "%d", a.digits[a.n - 1] );
	for( int i = a.n - 2; i >= 0; i-- )
		fprintf( output, "%04d", a.digits[i] );
	fprintf( output, "\n" );
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
	long int i;
	if( number->n == 1 )
		return 0;
	if( number->n == 0 || number->digits == NULL )
		return -1;
	for( i = number->n - 1; i > 0; i-- )
		if( number->digits[i] != 0 )
			break;
	number->n = i + 1;
	//number->digits = realloc( number->digits, number->n );
	return 0;
}


int add_longa( uint_longa_t *sum, uint_longa_t a, uint_longa_t b )
{
	long sum_len = max( a.n, b.n ) + 1;
	long min_len = min( a.n, b.n );
	long i = 0;
	int carry_over = 0;
	//
	if( a.n == 0 || b.n == 0 || sum->n < sum_len )
		return -1;
	//construct_longa( sum, sum_len );
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
	if( is_less_longa( a, b ) || difference->n < a.n )
		return -1;
	//construct_longa( difference, a.n );
	for( long int i = 0; i < b.n; i++ ) //because b has less digits or same
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) % BASE_LONGA;   //cause mod works wrong with negative numbers
		carry_over = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	for( long int i = b.n; i < a.n; i++ )
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] + carry_over ) % BASE_LONGA;
		carry_over = ( BASE_LONGA + a.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	return 0;
}

int mul_longa( uint_longa_t *product, uint_longa_t a, uint_longa_t b )
{
	int carry_over = 0;
	unsigned long temp = 0;
	unsigned long product_len = a.n + b.n;       //TODO: check overflow
	if( a.n == 0 || b.n == 0 || product->n < product_len )    
		return -1;
	zero_longa( product );
	for( long int j = 0; j < b.n; j++ )
	{
		carry_over = 0;
		for( int i = 0; i < a.n; i++ )
		{
			temp = a.digits[i] * b.digits[j] + product->digits[i + j] + carry_over;
			product->digits[i + j] = temp % BASE_LONGA;
			carry_over = temp / BASE_LONGA;
		}
		product->digits[j + a.n] = carry_over;
	}
	return 0;
}

int simple_div_longa( uint_longa_t *quotient, uint_longa_t a, digit_longa_t b )
{
	int carry_over = 0;
	unsigned long temp = 0;
	if( b >= BASE_LONGA || b == 0 || a.n == 0 || quotient->n < a.n )
		return -1;
	//construct_longa( quotient, a.n );
	for( long int i = a.n - 1; i >= 0; i-- )
	{
		temp = carry_over * BASE_LONGA + a.digits[i];
		quotient->digits[i] = temp / b;
		carry_over = temp % b;
	}
	return 0;
}

long int_pow_longa( uint_longa_t *result, uint_longa_t a, unsigned long power )
{
	unsigned long result_len = a.n * power;
	int bits_in_power = 0;
	int cur_bit = 0;
	long unsigned int temp = power;
	uint_longa_t cur_result, temp_result;
	if( a.n == 0 )
		return -1;
	if( result->n < result_len )
		return result_len;
	if( a.n == 1 && a.digits[0] == 0 )
	{
		if( power == 0 )
			return -1;
		else
			return 0;     //because must be 0, and it is alredy 0
	}
	if( a.n == 1 && a.digits[0] == 1 )
	{
		result->digits[0] = 1;
		return 0;
	}
	if( construct_longa( &cur_result, result_len ) || construct_longa( &temp_result, result_len ) )
	{
		return -1;
	}
	for( bits_in_power = 0; temp > 0; temp /= 2, bits_in_power++ );    //to calculate how many bits in power
	copy_longa( &cur_result, a );
	cur_result.n = a.n;      //for multiplication to work correct: it needs no leading zeros
	for( int i = bits_in_power - 2; i >=0; i-- )
	{
		//dump_longa( cur_result );
		temp_result.n = cur_result.n + cur_result.n;     //for mul...
		mul_longa( &temp_result, cur_result, cur_result );
		cur_bit = ( power >> i ) % 2;
		if( cur_bit )
		{
			cur_result.n = temp_result.n + a.n;
			mul_longa( &cur_result, temp_result, a );
		}
		else
		{
			cur_result.n = temp_result.n;   //for copying and later mul to work correct
			copy_longa( &cur_result, temp_result );
		}
	}
	//dump_longa( cur_result );
	if( copy_longa( result, cur_result ) )
	{
		printf( "ERROR: in function pow_longa messed up cur_result.n and temp_result.n properties\n" );
		return -1;
	}
	//dump_longa( *result );
	destruct_longa( &cur_result );
	destruct_longa( &temp_result );
	return 0;
}

long pow_longa( uint_longa_t *result, uint_longa_t a, uint_longa_t b )
{
	unsigned long power = 0;
	if( a.n == 0 || b.n == 0 )
		return -1;
	if( a.n == 1 && a.digits[0] == 0 )
	{
		if( b.n == 1 && b.digits[0] == 0 )
			return -1;
		else
			return 0;     //because the result must be 0, and it is alredy 0
	}
	if( a.n == 1 && a.digits[0] == 1 )
	{
		result->digits[0] = 1;
		return 0;
	}
	if( b.n > 4 )    //because even 2^(10000^4) has more than 1000000 digits
		return -1;
	power = b.digits[b.n - 1];
	for( int i = b.n - 2; i >= 0; i-- )   //converting to int
	{
		power *= BASE_LONGA;
		power += b.digits[i];
	}
	return int_pow_longa( result, a, power );
}


long unsigned int max( long unsigned int a, long unsigned int b )
{
	if( a > b )
		return a;
	return b;
}

long unsigned int min( long unsigned int a, long unsigned int b )
{
	if( a < b )
		return a;
	return b;
}

