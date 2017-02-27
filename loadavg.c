/*
 *------------------------------------------------------------------------
 * vim: ts=4 sw=4
 *------------------------------------------------------------------------
 * Author:   tf135c (James Reynolds)
 * Filename: loadavg.c
 * Created:  2006-12-17 09:24:03
 *------------------------------------------------------------------------
 */

#include <sys/sysinfo.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <gcc-compat.h>

#include <loadavg.h>

LoadAvg_t *
loadavg_new(
	void
)
{
	LoadAvg_t * const	result = malloc( sizeof( *result ) );

	assert( result );
	return( result );
}

LoadAvg_t *
loadavg_init(
	LoadAvg_t *			lda
)
{
	LoadAvg_t *			result;

	result = NULL;
	do	{
		LoadAvg_t *		working;

		working = lda;
		if( !working )	{
			working = loadavg_new();
		}
		working->cookie = fopen( "/proc/loadavg", "rt" );
		if( working->cookie )	{
			result = working;
			break;
		}
		if( !lda )	{
			free( working );
		}
	} while( 0 );
	return( result );
}

int
loadavg_get(
	LoadAvg_t * const		lda
)
{
	int						result;

	result = -1;
	do	{
		static	char const	delim[] = { " \t\r\n" };
		char				buf[ BUFSIZ ];
		int					argc;
		char *				argv[ 1 + ( (BUFSIZ+1) / 2) ];
		char *				bp;

		rewind( lda->cookie );
		if( !fgets( buf, sizeof( buf ), lda->cookie ) )	{
			break;
		}
		/* 
		 * Tokenize the line.  Because we were clever, we'll have 
		 * enough room for all the tokens, no matter how many there are.
		 */
		for(
			argc = 0, bp = buf;
			(argv[ argc ] = strtok( bp, delim ));
			++argc, bp = NULL
		);
		assert( argc > 3 );
		/* Publish the values we're interested in							*/
		lda->loads[ 0 ] = atof( argv[ 0 ] );
		lda->loads[ 1 ] = atof( argv[ 1 ] );
		lda->loads[ 2 ] = atof( argv[ 2 ] );
		/* Finito, Benito!													*/
		result = 0;
	} while( 0 );
	return( result );
}

LoadAvg_t *
loadavg_uninit(
	LoadAvg_t * const		lda
)
{
	if( lda->cookie )	{
		fclose( lda->cookie );
		lda->cookie = NULL;
	}
	return( lda );
}

LoadAvg_t *
loadavg_free(
	LoadAvg_t *			lda
)
{
	loadavg_free( lda );
	free( lda );
	return( NULL );
}

#ifdef	ETEST

int
main(
	int					argc			_unused,
	char * *			argv			_unused
)
{
	static	char const	fmt[] = { "%23s %.3g\n" };
	LoadAvg_t * const	lda = loadavg_init( NULL );

	if( loadavg_get( lda ) )	{
		fprintf( stderr, "loadavg_get() failed.\n" );
		exit( 1 );
	}
	printf( fmt, "1-minute avg",  loadavg_oneminute(     lda ) );
	printf( fmt, "5-minute avg",  loadavg_fiveminute(    lda ) );
	printf( fmt, "15-minute avg", loadavg_fifteenminute( lda ) );
	return( 0 );
}
#endif	/* ETEST */
