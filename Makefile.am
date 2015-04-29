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

bin_PROGRAMS = linc 
noinst_PROGRAMS = testencrypt
man_MANS = linc.1 lincrc.5
EXTRA_DIST = $(man_MANS) sample.lincrc ChangeLog linc.spec linc-srv

linc_SOURCES = \
	Msg.h Msg.cpp SrvPxy.h SrvPxy.cpp \
	LoginMsg.h LoginMsg.cpp \
	ContinueMsg.h ContinueMsg.cpp \
	LogoutMsg.h LogoutMsg.cpp \
	VComm.h V1Comm.h V1Comm.cpp V2Comm.h V2Comm.cpp \
	CliState.h \
	ConnState.h ConnState.cpp \
	ActiveState.h ActiveState.cpp \
	InactiveState.h InactiveState.cpp \
	DiscState.h DiscState.cpp \
	DeInitState.h DeInitState.cpp \
	CfgFile.h CfgFile.cpp Cfg.h Cfg.cpp CfgErr.h \
	CmdLine.h CmdLine.cpp \
	LogStream.h CliApp.h CliApp.cpp main.cpp \
  encrypt.h encrypt.cpp

testencrypt_SOURCES = testencrypt.cpp encrypt.h encrypt.cpp

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
