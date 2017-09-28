#include"longalib.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<limits.h>


int construct_with_str_longa( uint_longa_t *number, long long n_decimal, char *str_number )
{
	long long position;         //position in str_number
	size_longa_t i;                     //position in internal array digits
	char str_digit[POWER_OF_BASE_LONGA + 1];   //to copy a piece of str_number that represent a digit there
	size_longa_t n;
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

int construct_longa( uint_longa_t *number, size_longa_t n )
{
	if( n <= 0 )
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
	size_longa_t i;
	if( src.n == 0 || dest->n < src.n )
		return -1;
	for( i = 0; i < src.n; i++ )
		dest->digits[i] = src.digits[i];
	for( i = src.n; i < dest->n; i++ )
		dest->digits[i] = 0;
	return 0;
}

int copyn_longa( uint_longa_t *dest, uint_longa_t src, size_longa_t n, size_longa_t m )
{
	if( m < 0 || n > m || dest->n < m - n + 1 || src.n < m )
		return -1;
	for( size_longa_t i = 0, j = n; j <= m; i++, j++ )
		dest->digits[i] = src.digits[j];
	for( size_longa_t i = m - n + 1; i < dest->n; i++ )
		dest->digits[i] = 0;
	return 0;
}

int zero_longa( uint_longa_t *number )
{
	for( size_longa_t i = 0; i < number->n; i++ )
		number->digits[i] = 0;
	return 0;
}

int dump_longa( uint_longa_t number )
{
	printf( "%ld\n", number.n );
	for( size_longa_t i = 0; i < number.n; i++ )
		printf( "    %ld:%d\n", i, number.digits[i] );
	return 0;
}

int fprintf_longa( FILE *output, uint_longa_t a )
{
	if( a.n == 0 )
		return -1;
	fprintf( output, "%d", a.digits[a.n - 1] );
	for( size_longa_t i = a.n - 2; i >= 0; i-- )
		fprintf( output, "%04d", a.digits[i] );
	fprintf( output, "\n" );
	return 0;
}


int is_equal_longa( uint_longa_t a, uint_longa_t b )
{
	if( a.n != b.n )
		return 0;
	for( size_longa_t i = 0; i < a.n; i++ )
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
	for( size_longa_t i = a.n - 1; i >= 0; i-- )
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
	for( size_longa_t i = a.n - 1; i >= 0; i-- )
		if( a.digits[i] < b.digits[i] )
			return 1;
		else
			if( a.digits[i] > b.digits[i] )
				return 0;
	return 0;
}

int delete_leading_zeros_longa( uint_longa_t *number )
{
	size_longa_t i;
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
	size_longa_t sum_len = max( a.n, b.n ) + 1;
	size_longa_t min_len = min( a.n, b.n );
	size_longa_t i = 0;
	int carry_over = 0;
	if( a.n == 0 || b.n == 0 || sum->n < sum_len )
		return -1;
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
	for( i = sum_len; i < sum->n; i++ )
		sum->digits[i] = 0;
	return 0;
}

int sub_longa( uint_longa_t *difference, uint_longa_t a, uint_longa_t b )
{
	int carry_over = 0;
	if( is_less_longa( a, b ) || difference->n < a.n )
		return -1;
	//construct_longa( difference, a.n );
	for( size_longa_t i = 0; i < b.n; i++ ) //because b has less digits or same
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) % BASE_LONGA;   //cause mod works wrong with negative numbers
		carry_over = ( BASE_LONGA + a.digits[i] - b.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	for( size_longa_t i = b.n; i < a.n; i++ )
	{
		difference->digits[i] = ( BASE_LONGA + a.digits[i] + carry_over ) % BASE_LONGA;
		carry_over = ( BASE_LONGA + a.digits[i] + carry_over ) / BASE_LONGA - 1;
	}
	for( size_longa_t i = a.n; i < difference->n; i++ )
		difference->digits[i] = 0;
	return 0;
}

int mul_longa( uint_longa_t *product, uint_longa_t a, uint_longa_t b )
{
	int carry_over = 0;
	long temp = 0;
	size_longa_t product_len = a.n + b.n;
	if( product_len < a.n )      //owerflow
		return -1;
	if( a.n == 0 || b.n == 0 || product->n < product_len )    
		return -1;
	zero_longa( product );
	for( size_longa_t j = 0; j < b.n; j++ )
	{
		carry_over = 0;
		for( size_longa_t i = 0; i < a.n; i++ )
		{
			temp = a.digits[i] * b.digits[j] + product->digits[i + j] + carry_over;
			product->digits[i + j] = temp % BASE_LONGA;
			carry_over = temp / BASE_LONGA;
		}
		product->digits[j + a.n] = carry_over;
	}
	return 0;
}

int int_mul_longa( uint_longa_t *product, uint_longa_t a, digit_longa_t b )
{
	int carry_over = 0;
	long temp = 0;
	size_longa_t product_len = a.n + 1;
	if( a.n == 0 || product->n < product_len )    
		return -1;
	zero_longa( product );
	for( size_longa_t i = 0; i < a.n; i++ )
	{
		temp = a.digits[i] * b + product->digits[i] + carry_over;
		product->digits[i] = temp % BASE_LONGA;
		carry_over = temp / BASE_LONGA;
	}
	product->digits[a.n] = carry_over;
	for( size_longa_t i = a.n + 1; i < product->n; i++ )
		product->digits[i] = 0;
	return 0;
}


int int_div_longa( uint_longa_t *quotient, uint_longa_t a, digit_longa_t b )
{
	int carry_over = 0;
	long temp = 0;
	if( b >= BASE_LONGA || b == 0 || a.n == 0 || quotient->n < a.n )
		return -1;
	for( size_longa_t i = a.n - 1; i >= 0; i-- )
	{
		temp = carry_over * BASE_LONGA + a.digits[i];
		quotient->digits[i] = temp / b;
		carry_over = temp % b;
	}
	for( size_longa_t i = a.n; i < quotient->n; i++ )
		quotient->digits[i] = 0;
	return 0;
}

int div_longa( uint_longa_t *quotient, uint_longa_t a, uint_longa_t b )
{
	if( a.n == 0 || b.n == 0 || quotient->n == 0 )
		return -1;
	if( is_equal_longa( a, b ) )
	{
		quotient->digits[0] = 1;
		return 0;
	}
	if( is_greater_longa( b, a ) )
	{
		quotient->digits[0] = 0;
		return 0;
	}
	if( b.n == 1 )
	{
		return int_div_longa( quotient, a, b.digits[0] );
	}
	digit_longa_t d = BASE_LONGA / ( b.digits[b.n - 1] + 1 );
	digit_longa_t q = 0, r = 0;      //quotien and rest on each step
	digit_longa_t temp = 0;
	size_longa_t quotient_len = a.n - b.n + 1;
	if( quotient->n < quotient_len )
		return -1;
	uint_longa_t norm_a, norm_b, local_a, b_mul_q, new_local_a;
	if( construct_longa( &norm_a, a.n + 1 ) )
	{
		return -1;
	}
	if( construct_longa( &norm_b, b.n + 1 ) )
	{
		destruct_longa( &norm_a );
		return -1;
	}
	if( construct_longa( &local_a, b.n + 1 ) )
	{
		destruct_longa( &norm_a );
		destruct_longa( &norm_b );
		return -1;
	}
	if( construct_longa( &new_local_a, b.n + 1 ) )
	{
		destruct_longa( &norm_a );
		destruct_longa( &norm_b );
		destruct_longa( &local_a );
		return -1;
	}
	if( construct_longa( &b_mul_q, b.n + 1 ) )
	{
		destruct_longa( &norm_a );
		destruct_longa( &norm_b );
		destruct_longa( &local_a );
		destruct_longa( &new_local_a );
		return -1;
	}
	int_mul_longa( &norm_a, a, d );       //normalization
	int_mul_longa( &norm_b, b, d );       //normalization
	delete_leading_zeros_longa( &norm_b );    //we choosed special d so norm_b.n must be equal b.n so we have delete one zero
	for( size_longa_t i = quotient_len - 1; i >= 0; i-- )
	{
		temp = ( norm_a.digits[i + b.n] * BASE_LONGA + norm_a.digits[i + b.n - 1] );
		q = temp / norm_b.digits[b.n - 1];
		r = temp / norm_b.digits[b.n - 1];
		if( q == BASE_LONGA || q * norm_b.digits[b.n - 2] > BASE_LONGA * r + norm_a.digits[i + b.n - 2] )
		{
			q--;
			r += norm_b.digits[b.n - 1];
		}
		copyn_longa( &local_a, norm_a, i, i + b.n );
		if( int_mul_longa( &b_mul_q, norm_b, q ) )
		{
			printf( "Error: in function div_longa int_mul_longa returns 0\n" );
			exit( 0 );
		}
		if( is_less_longa( local_a, b_mul_q ) )
		{
			q--;
			if( int_mul_longa( &b_mul_q, norm_b, q ) )
			{
				printf( "Error: in function div_longa int_mul_longa returns -1\n" );
				exit( 0 );
			}
		}
		if( sub_longa( &new_local_a, local_a, b_mul_q ) )
		{
			printf( "Error: in function div_longa sub returns -1\n" );
			exit( 0 );
		}
		for( size_longa_t j = 0; j < new_local_a.n; j++ )
		{
			norm_a.digits[i + j] = new_local_a.digits[j];
		}
		quotient->digits[i] = q;
	}
	destruct_longa( &norm_a );
	destruct_longa( &norm_b );  
	destruct_longa( &local_a );
	destruct_longa( &new_local_a );
	destruct_longa( &b_mul_q ); 
	return 0;
}


size_longa_t int_pow_longa( uint_longa_t *result, uint_longa_t a, long power )
{
	if( a.n > LONG_MAX / power )  //overflow
		return -1;
	size_longa_t result_len = a.n * power;
	int bits_in_power = 0;
	int cur_bit = 0;
	long temp = power;
	uint_longa_t cur_result, temp_result;
	if( a.n == 0 || power < 0 )
		return -1;
	if( result->n < result_len )
		return result_len;
	if( a.n == 1 && a.digits[0] == 0 )
	{
		if( power == 0 )
			return -1;
		else
			zero_longa( result );
			return 0;     
	}
	if( ( a.n == 1 && a.digits[0] == 1 ) || power == 0 )
	{
		zero_longa( result );
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

size_longa_t pow_longa( uint_longa_t *result, uint_longa_t a, uint_longa_t b )
{
	long power = 0;
	if( a.n == 0 || b.n == 0 )
		return -1;
	if( a.n == 1 && a.digits[0] == 0 )
	{
		if( b.n == 1 && b.digits[0] == 0 )
			return -1;
		else
			zero_longa( result );
			return 0;
	}
	if( ( a.n == 1 && a.digits[0] == 1 ) || ( b.n == 1 && b.digits[0] == 0 ) )
	{
		zero_longa( result );
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


long max( long a, long b )
{
	if( a > b )
		return a;
	return b;
}

long min( long a, long b )
{
	if( a < b )
		return a;
	return b;
}

