#include<stdio.h>
#include<string.h>
#include"longalib.h"



int main()
{
	FILE *input;
	char str[1000000];
	int len = 0;
	uint_longa_t number;
	input = fopen( "iotest.in", "r" );
	while( fscanf( input, "%s", str ) > 0 )
	{
		len = strlen( str );
		construct_with_str_longa( &number, len, str );
		delete_leading_zeros_longa( &number );
		dump_longa( number );
		destruct_longa( &number );
	}
	fclose( input );
	return 0;
}

