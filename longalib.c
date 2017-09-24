#include"longalib.h"
#include<string.h>
#include<stdlib.h>


int construct_longa( long unsigned int n_decimal, uint_longa_t *number, char *str_number )
{
	long int position;
	int i;
	char str_digit[POWER_OF_BASE_LONGA + 1];
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
	for( i = 0; i < number.n; i++ )
		printf( "    %d:%d\n", i, number.digit[i] );
	return 0;
}


