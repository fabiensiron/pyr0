/*
 * File: limits.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: actual type limits of the system
 */

#ifndef _LIMITS_H_
# define _LIMITS_H_

# define        CHAR_MAX	0x7f
# define        CHAR_MIN	(-0x7f-1)

# define	USHRT_MAX	0xffffU		/* max value for an unsigned short */
# define	SHRT_MAX	0x7fff		/* max value for a short */
# define        SHRT_MIN        (-0x7fff-1)     /* min value for a short */

# define	UINT_MAX	0xffffffffU	/* max value for an unsigned int */
# define	INT_MAX		0x7fffffff	/* max value for an int */
# define	INT_MIN		(-0x7fffffff-1)	/* min value for an int */

# define        ULONG_MAX	0xffffffffUL	/* max value for an unsigned long */
# define        LONG_MAX	0x7fffffffL	/* max value for a long */
# define        LONG_MIN	(-0x7fffffffL-1)/* min value for a long */

#endif /*!_LIMITS_H_*/
