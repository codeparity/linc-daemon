# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

#   linc is not cyberoam v1.0
#   Copyright (C) 2002  Mayur Naik <mayur@freeshell.org>.
# 
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; version 2 of the License, with the
#   following exceptions:
#   1) Any existing copyright or authorship information in any given source
#      file must remain intact.  If you modify a source file, a notice to that
#      effect must be appended to the authorship information in the source file.
# 
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
# 
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
# 
#   In short you can not change/modify/remove the information above, if you do
#   redistribute this program or any of its modified form, it must be free and
#   there is NO WARRANTY, the author can not be held responsible for any kind
#   of damage caused by this program.


SHELL = /bin/sh

srcdir = .
top_srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/linc-daemon
pkglibdir = $(libdir)/linc-daemon
pkgincludedir = $(includedir)/linc-daemon

top_builddir = .

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
CPP = cc -E
CXX = c++
MAKEINFO = /home/ashish/linc-daemon-1.2/missing makeinfo
PACKAGE = linc-daemon
VERSION = 1.2

bin_PROGRAMS = linc 
noinst_PROGRAMS = testencrypt
man_MANS = linc.1 lincrc.5
EXTRA_DIST = $(man_MANS) sample.lincrc ChangeLog linc.spec linc-srv

linc_SOURCES =  	Msg.h Msg.cpp SrvPxy.h SrvPxy.cpp 	LoginMsg.h LoginMsg.cpp 	ContinueMsg.h ContinueMsg.cpp 	LogoutMsg.h LogoutMsg.cpp 	VComm.h V1Comm.h V1Comm.cpp V2Comm.h V2Comm.cpp 	CliState.h 	ConnState.h ConnState.cpp 	ActiveState.h ActiveState.cpp 	InactiveState.h InactiveState.cpp 	DiscState.h DiscState.cpp 	DeInitState.h DeInitState.cpp 	CfgFile.h CfgFile.cpp Cfg.h Cfg.cpp CfgErr.h 	CmdLine.h CmdLine.cpp 	LogStream.h CliApp.h CliApp.cpp main.cpp   encrypt.h encrypt.cpp


testencrypt_SOURCES = testencrypt.cpp encrypt.h encrypt.cpp
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES =  linc.spec doxy.cfg
PROGRAMS =  $(bin_PROGRAMS) $(noinst_PROGRAMS)


DEFS =  -DPACKAGE=\"linc-daemon\" -DVERSION=\"1.2\" -DHAVE_SYSLOG_H=1 -DIOMANIP_WORKS=1  -I. -I$(srcdir) 
CPPFLAGS = 
LDFLAGS = 
LIBS = 
linc_OBJECTS =  Msg.o SrvPxy.o LoginMsg.o ContinueMsg.o LogoutMsg.o \
V1Comm.o V2Comm.o ConnState.o ActiveState.o InactiveState.o DiscState.o \
DeInitState.o CfgFile.o Cfg.o CmdLine.o CliApp.o main.o encrypt.o
linc_LDADD = $(LDADD)
linc_DEPENDENCIES = 
linc_LDFLAGS = 
testencrypt_OBJECTS =  testencrypt.o encrypt.o
testencrypt_LDADD = $(LDADD)
testencrypt_DEPENDENCIES = 
testencrypt_LDFLAGS = 
CXXFLAGS = -O2
CXXCOMPILE = $(CXX) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@
CFLAGS = 
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
man1dir = $(mandir)/man1
man5dir = $(mandir)/man5
MANS = $(man_MANS)

NROFF = nroff
DIST_COMMON =  README AUTHORS COPYING ChangeLog INSTALL Makefile.am \
Makefile.in NEWS TODO aclocal.m4 configure configure.in doxy.cfg.in \
install-sh linc.spec.in missing mkinstalldirs


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
SOURCES = $(linc_SOURCES) $(testencrypt_SOURCES)
OBJECTS = $(linc_OBJECTS) $(testencrypt_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .cpp .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu --include-deps Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

$(ACLOCAL_M4):  configure.in 
	cd $(srcdir) && $(ACLOCAL)

config.status: $(srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck
$(srcdir)/configure: $(srcdir)/configure.in $(ACLOCAL_M4) $(CONFIGURE_DEPENDENCIES)
	cd $(srcdir) && $(AUTOCONF)
linc.spec: $(top_builddir)/config.status linc.spec.in
	cd $(top_builddir) && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status
doxy.cfg: $(top_builddir)/config.status doxy.cfg.in
	cd $(top_builddir) && CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

mostlyclean-noinstPROGRAMS:

clean-noinstPROGRAMS:
	-test -z "$(noinst_PROGRAMS)" || rm -f $(noinst_PROGRAMS)

distclean-noinstPROGRAMS:

maintainer-clean-noinstPROGRAMS:

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

linc: $(linc_OBJECTS) $(linc_DEPENDENCIES)
	@rm -f linc
	$(CXXLINK) $(linc_LDFLAGS) $(linc_OBJECTS) $(linc_LDADD) $(LIBS)

testencrypt: $(testencrypt_OBJECTS) $(testencrypt_DEPENDENCIES)
	@rm -f testencrypt
	$(CXXLINK) $(testencrypt_LDFLAGS) $(testencrypt_OBJECTS) $(testencrypt_LDADD) $(LIBS)
.cpp.o:
	$(CXXCOMPILE) -c $<

install-man1:
	$(mkinstalldirs) $(DESTDIR)$(man1dir)
	@list='$(man1_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.1*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  if test -f $(srcdir)/$$i; then file=$(srcdir)/$$i; \
	  else file=$$i; fi; \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$(man1dir)/$$inst"; \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(man1dir)/$$inst; \
	done

uninstall-man1:
	@list='$(man1_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.1*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f $(DESTDIR)$(man1dir)/$$inst"; \
	  rm -f $(DESTDIR)$(man1dir)/$$inst; \
	done

install-man5:
	$(mkinstalldirs) $(DESTDIR)$(man5dir)
	@list='$(man5_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.5*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  if test -f $(srcdir)/$$i; then file=$(srcdir)/$$i; \
	  else file=$$i; fi; \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " $(INSTALL_DATA) $$file $(DESTDIR)$(man5dir)/$$inst"; \
	  $(INSTALL_DATA) $$file $(DESTDIR)$(man5dir)/$$inst; \
	done

uninstall-man5:
	@list='$(man5_MANS)'; \
	l2='$(man_MANS)'; for i in $$l2; do \
	  case "$$i" in \
	    *.5*) list="$$list $$i" ;; \
	  esac; \
	done; \
	for i in $$list; do \
	  ext=`echo $$i | sed -e 's/^.*\\.//'`; \
	  inst=`echo $$i | sed -e 's/\\.[0-9a-z]*$$//'`; \
	  inst=`echo $$inst | sed '$(transform)'`.$$ext; \
	  echo " rm -f $(DESTDIR)$(man5dir)/$$inst"; \
	  rm -f $(DESTDIR)$(man5dir)/$$inst; \
	done
install-man: $(MANS)
	@$(NORMAL_INSTALL)
	$(MAKE) $(AM_MAKEFLAGS) install-man1 install-man5
uninstall-man:
	@$(NORMAL_UNINSTALL)
	$(MAKE) $(AM_MAKEFLAGS) uninstall-man1 uninstall-man5

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	-rm -rf $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) zxf $(distdir).tar.gz
	mkdir $(distdir)/=build
	mkdir $(distdir)/=inst
	dc_install_base=`cd $(distdir)/=inst && pwd`; \
	cd $(distdir)/=build \
	  && ../configure --srcdir=.. --prefix=$$dc_install_base \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) dist
	-rm -rf $(distdir)
	@banner="$(distdir).tar.gz is ready for distribution"; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"
dist: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
dist-all: distdir
	-chmod -R a+r $(distdir)
	GZIP=$(GZIP_ENV) $(TAR) chozf $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)
distdir: $(DISTFILES)
	-rm -rf $(distdir)
	mkdir $(distdir)
	-chmod 777 $(distdir)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done

info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS
install-exec: install-exec-am

install-data-am: install-man
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS uninstall-man
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS) $(MANS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir) $(DESTDIR)$(mandir)/man1 \
		$(DESTDIR)$(mandir)/man5


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-noinstPROGRAMS \
		mostlyclean-compile mostlyclean-tags \
		mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-noinstPROGRAMS clean-compile \
		clean-tags clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-noinstPROGRAMS \
		distclean-compile distclean-tags distclean-generic \
		clean-am

distclean: distclean-am
	-rm -f config.status

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-noinstPROGRAMS \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am
	-rm -f config.status

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-noinstPROGRAMS distclean-noinstPROGRAMS \
clean-noinstPROGRAMS maintainer-clean-noinstPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile install-man1 uninstall-man1 install-man5 \
uninstall-man5 install-man uninstall-man tags mostlyclean-tags \
distclean-tags clean-tags maintainer-clean-tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


doc: $(linc_SOURCES) doxy.cfg
	doxygen doxy.cfg && touch doc

#
#   This file is part of linc $Name: rel-1-2 $
#
#   $Log: Makefile.am,v $
#   Revision 1.16  2003/04/05 05:12:36  mrnk
#   Fixed version and help strings. Added support for cleartext passwords based on Rahul Mittal's code.
#
#   Revision 1.15  2003/04/01 11:28:29  mrnk
#   Removed references to removed file config.h
#
#   Revision 1.14  2003/04/01 11:24:04  mrnk
#   Removed references to uncommited sources
#
#   Revision 1.13  2003/04/01 11:13:34  mrnk
#   Fixed crash when /home/mayur was not defined. Added initscript.
#
#   Revision 1.12  2003/04/01 08:47:32  mrnk
#   Fixed code to work with gcc3.
#
#   Revision 1.11  2002/12/17 17:46:40  mrnk
#   dup()ing on fd 0,1,2 instead of closing.
#
#   Revision 1.10  2002/07/06 01:55:33  mrnk
#   Added stub for V2Comm
#
#   Revision 1.9  2002/06/26 18:27:58  mrnk
#   Added version communicator base class.
#   Added stub for version 1 communicator.
#   Added both classes into Makefile.am
#   Updated TODO to reflect the completed tasks.
#
#   ----------------------------------------------------------------------
#
#   Committing in .
#
#   Modified Files:
#   	Makefile.am Makefile.in Msg.cpp TODO stamp-h.in
#   Added Files:
#   	V1Comm.cpp V1Comm.h VComm.h
#   ----------------------------------------------------------------------
#
#   Revision 1.8  2002/06/24 11:15:22  mrnk
#   Disabling dumper code. Actually thinking of using libpcap to write the decode
#   utility, wherein the tool can either sniff on the network or accept data from
#   a tcpdump dump file.
#
#   Revision 1.7  2002/06/23 09:38:43  mrnk
#   Started packet dump interpretation tool
#
#   Revision 1.6  2002/06/22 05:44:50  mrnk
#   Misc formatting changes
#
#   Revision 1.5  2002/06/22 05:33:50  mrnk
#   added Man pages to installation, added man pages, sample rcfile and 
#   ChangeLog to distribution
#
#   Revision 1.4  2002/06/19 11:59:49  mrnk
#   Added CVS keywords to all source files
#

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
