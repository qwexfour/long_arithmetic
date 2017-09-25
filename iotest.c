#include<stdio.h>
#include<string.h>
#include"longalib.h"



int main()
{
	FILE *input;
	char str[1000000];
	int len = 0;
	char ch = '\0';
	uint_longa_t number;
	input = fopen( "iotest.in", "r" );
	while( fscanf( input, "%s", str ) > 0 )
	{
		len = strlen( str );
		construct_with_str_longa( &number, len, str );
		dump_longa( number );
		destruct_longa( &number );
		fscanf( input, "%c", &ch );
		//printf( "%c\n", ch );
		//fseek( input, -1, SEEK_CUR );
	}
	fclose( input );
	return 0;
}

