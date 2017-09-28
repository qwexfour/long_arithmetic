#include<stdio.h>
#include<string.h>
#include<math.h>
#include"longalib.h"



int main()
{
	FILE *input, *output;
	char str[1000001];
	char op;    //operation
	long unsigned int len = 0;
	uint_longa_t a, b, res;
	input = fopen( "input.txt", "r" );
	output = fopen( "output.txt", "w" );
	while( fscanf( input, "%s", str ) > 0 )
	{
		len = strlen( str );
		if( construct_with_str_longa( &a, len, str ) )
		{
			printf( "ERROR: failed to read first operand\n" );
			return 0;
		}
		delete_leading_zeros_longa( &a );
		//dump_longa( a );
		if( !fscanf( input, "%s", str ) )   //reading second operand
		{
			printf( "ERROR: failed to read second operand\n" );
			return 0;
		}
		len = strlen( str );
		if( construct_with_str_longa( &b, len, str ) )
		{
			printf( "ERROR: failed to read second operand\n" );
			return 0;
		}
		delete_leading_zeros_longa( &b );
		if( !fscanf( input, "%s", str ) )
		{
			printf( "ERROR: no operation." );
			return 0;
		}
		op = str[0];
		switch( op )
		{
			case '+':
				if( construct_longa( &res, max( a.n, b.n ) + 1 ) )
				{
					printf( "Error: cannot allocate memory\n" );
					fprintf( output, "Error\n" );
					break;
				}
				if( add_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					destruct_longa( &res );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '-':
				if( construct_longa( &res, a.n ) )
				{
					printf( "Error: cannot allocate memory\n" );
					fprintf( output, "Error\n" );
					break;
				}
				if( sub_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					destruct_longa( &res );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '*':
				if( construct_longa( &res, a.n + b.n ) )
				{
					printf( "Error: cannot allocate memory\n" );
					fprintf( output, "Error\n" );
					break;
				}
				if( mul_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					destruct_longa( &res );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '/':
				construct_longa( &res, a.n );
				if( div_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					destruct_longa( &res );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '^':
				if( construct_longa( &res, 1 ) )
				{
					printf( "Error: cannot allocate memory\n" );
					fprintf( output, "Error\n" );
					break;
				}
				long pow_code = pow_longa( &res, a, b );
				if( pow_code < 0 )
				{
					fprintf( output, "Error\n" );
				}
				if( pow_code == 0 )
				{
					fprintf_longa( output, res );    //only one digit - no place for leading zeros
				}
				if( pow_code > 0 )    //func returns needed size
				{
					destruct_longa( &res );
					if( construct_longa( &res, pow_code ) )
					{
						printf( "Error: cannot allocate memory\n" );
						fprintf( output, "Error\n" );
						break;
					}
					if( pow_longa( &res, a, b ) )
					{
						fprintf( output, "Error\n" );
						destruct_longa( &res );
						break;
					}
					delete_leading_zeros_longa( &res );
					fprintf_longa( output, res );
				}
				destruct_longa( &res );
				break;
			case '=':
				if( is_equal_longa( a, b ) )
					fprintf( output, "true\n" );
				else
					fprintf( output, "false\n" );
				break;
			case '>':
				if( is_greater_longa( a, b ) )
					fprintf( output, "true\n" );
				else
					fprintf( output, "false\n" );
				break;
			case '<':
				if( is_less_longa( a, b ) )
					fprintf( output, "true\n" );
				else
					fprintf( output, "false\n" );
				break;
			default:
				printf( "ERROR: wrong operand\n" );
				return 0;
		}
		destruct_longa( &a );
		destruct_longa( &b );
	}
	fclose( input );
	fclose( output );
	return 0;
}

