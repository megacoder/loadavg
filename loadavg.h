/*
 *------------------------------------------------------------------------
 * vim: ts=4 sw=4
 *------------------------------------------------------------------------
 * Author:   tf135c (James Reynolds)
 * Filename: loadavg.h
 * Created:  2006-12-17 09:44:17
 *------------------------------------------------------------------------
 */

#ifndef	LOADAVG_H
# define LOADAVG_H

typedef struct loadavg_s	{
	double		loads[ 3 ];			/* One, five & fifteen minute history	*/
	void *		cookie;				/* Internal data used by routine		*/
} LoadAvg_t;

LoadAvg_t *						loadavg_new( void );
LoadAvg_t *						loadavg_init( LoadAvg_t * );
int				_nonnull((1))	loadavg_get( LoadAvg_t * );
LoadAvg_t *		_nonnull((1))	loadavg_uninit( LoadAvg_t * );
LoadAvg_t *		_nonnull((1))	loadavg_free( LoadAvg_t * );

# define						loadavg_oneminute(l)		( (l)->loads[0] )
# define						loadavg_fiveminute(l)		( (l)->loads[1] )
# define						loadavg_fifteenminute(l)	( (l)->loads[2] )

#endif	/* LOADAVG_H */
