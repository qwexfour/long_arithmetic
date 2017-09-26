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
		if( !fscanf( input, "%s", str ) )
		{
			printf( "ERROR: no operation." );
			return 0;
		}
		op = str[0];
		switch( op )
		{
			case '+':
				construct_longa( &res, max( a.n, b.n ) + 1 );
				if( add_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '-':
				construct_longa( &res, a.n );
				if( sub_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '*':
				construct_longa( &res, a.n + b.n );
				if( mul_longa( &res, a, b ) )
				{
					fprintf( output, "Error\n" );
					break;
				}
				delete_leading_zeros_longa( &res );
				fprintf_longa( output, res );
				destruct_longa( &res );
				break;
			case '/':
				if( b.n == 1 )
				{
					construct_longa( &res, a.n );
					if( simple_div_longa( &res, a, b.digits[0] ) )
					{
						fprintf( output, "Error\n" );
						break;
					}
					delete_leading_zeros_longa( &res );
					fprintf_longa( output, res );
					destruct_longa( &res );
				}
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

