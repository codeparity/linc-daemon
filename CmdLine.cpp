/*  linc is not cyberoam v1.0
 *  Copyright (C) 2002  Mayur Naik <mayur@freeshell.org>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License, with the
 *  following exceptions:
 *  1) Any existing copyright or authorship information in any given source
 *     file must remain intact.  If you modify a source file, a notice to that
 *     effect must be appended to the authorship information in the source file.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  In short you can not change/modify/remove the information above, if you do
 *  redistribute this program or any of its modified form, it must be free and
 *  there is NO WARRANTY, the author can not be held responsible for any kind
 *  of damage caused by this program.
 *  
 *  This source file is part of linc $Name: rel-1-2 $
 *  
 *  $Log: CmdLine.cpp,v $
 *  Revision 1.6  2003/04/05 05:20:01  mrnk
 *  Fixed version string with constant pacage name. Updated TODO.
 *
 *  Revision 1.5  2003/04/05 05:12:36  mrnk
 *  Fixed version and help strings. Added support for cleartext passwords based on Rahul Mittal's code.
 *
 *  Revision 1.4  2003/04/01 11:13:34  mrnk
 *  Fixed crash when /home/mayur was not defined. Added initscript.
 *
 *  Revision 1.3  2002/06/22 10:32:22  mrnk
 *  Documented class CmdLine
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#include <CmdLine.h>
#include <unistd.h>

#define NO_MORE_OPTS -1
#define OPT_HELP_NEEDED 'h'
#define OPT_DEBUG_MODE 'd'
#define OPT_VERSION 'v'

//! constructor
CmdLine::CmdLine( int i32ArgCount, char *pcArgVec[] )
{
	// Initializations
	m_bHelpNeeded = false;
	m_bDebugMode = false;
	m_bShowVersion = false;
  m_oStrProgname = pcArgVec[0];
	
	// Get options
	int i32Opt;
	while ( (i32Opt = getopt(i32ArgCount, pcArgVec, "hdv")) 
			!= NO_MORE_OPTS)
		switch (i32Opt)
		{
			case OPT_HELP_NEEDED:
				m_bHelpNeeded = true;
				break;

			case OPT_VERSION:
				m_bShowVersion = true;
				break;

			case OPT_DEBUG_MODE:
				m_bDebugMode = true;
				break;

			default:
				m_bHelpNeeded = true;
		}

	int i32Opts = 0;
	(m_bHelpNeeded)?i32Opts++:i32Opts;
	(m_bShowVersion)?i32Opts++:i32Opts;
	(m_bDebugMode)?i32Opts++:i32Opts;
	//! if more than one option is specified, it's an error
	if (i32Opts > 1)
	{
		m_bShowVersion = false;
		m_bHelpNeeded = true;
	}
}

string CmdLine::Usage (void)
{
	return m_oStrProgname + " [-h] | [-v] | [-d]";
}

string CmdLine::Version (void)
{
	return (string) "linc " + VERSION + "\t24online authentication client";
}

string CmdLine::CLIHelp (void)
{
	return (string) "-h\t\tShow this help text\n" 
		+ "-v\t\tShow version\n"
		+ "-d\t\tDebug mode\n\n"
		+ "Project homepage at http://linc.sourceforge.net\n"
		+ "Mail queries to linc-users@lists.sourceforge.net\n";
}
