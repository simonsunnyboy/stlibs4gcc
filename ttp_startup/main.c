/**
 * Basepage command line parser for TOS
 *
 * @file main.c
 *
 * @copyright Copyright (c) 2025 Matthias Arndt <marndt@final-memory.org>
 *
 *            The MIT License applies. See the file LICENSE for details.
 *
 * @brief Example TTP displaying the passed command line parameters
 */
#include <osbind.h>

int main ( int argc, char *argv[] )
{
	int nr = 0;
	( void ) Cconws ( "\033E" );
	( void ) Cconws ( "Test .ttp got parameters:\n\r" );

	while ( argc > 0 )
	{
		( void ) Cconws ( argv[nr] );
		( void ) Cconws ( "\n\r" );
		nr++;
		argc--;
	}

	( void ) Cconws ( "---------------------------------------\n\rpress ENTER\n\r" );
	Cconin();
	return 0;
}
