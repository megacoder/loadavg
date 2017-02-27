#########################################################################
# vim: ts=8 sw=8
#########################################################################
# Author:   tf135c (James Reynolds)
# Filename: Makefile
# Date:     2006-12-17 09:23:46
#########################################################################
# Note that we use '::' rules to allow multiple rule sets for the same
# target.  Read that as "modularity exemplarized".
#########################################################################

TARGETS	=all clean distclean clobber check install uninstall tags
TARGET	=all

SUBDIRS	=

.PHONY:	${TARGETS} ${SUBDIRS}

CC	=ccache gcc4 -march=i686 -std=gnu99
DEFS	=-D_FORTIFY_SOURCE=2
OPT	=-Os
OPT	=-O0
INCS	=-I.
CFLAGS	=${OPT} -Wall -Wextra -Werror -pedantic -pipe -g ${DEFS} ${INCS}
LDFLAGS	=-g
LDLIBS	=-lSegFault

all::	loadavg

loadavg: loadavg.c loadavg.h
	${CC} ${CFLAGS} -DETEST -o $@ loadavg.c

${TARGETS}::

clean::
	${RM} a.out *.o core.* lint tags

distclean clobber:: clean
	${RM} loadavg

check::	loadavg
	./loadavg ${ARGS}

install::

uninstall::

tags::
	ctags -R .

debug::	loadavg
	insight ./loadavg

# ${TARGETS}::
# 	${MAKE} TARGET=$@ ${SUBDIRS}

# ${SUBDIRS}::
# 	${MAKE} -C $@ ${TARGET}
