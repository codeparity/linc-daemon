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
 *  $Log: CmdLine.h,v $
 *  Revision 1.5  2003/04/05 05:12:36  mrnk
 *  Fixed version and help strings. Added support for cleartext passwords based on Rahul Mittal's code.
 *
 *  Revision 1.4  2003/04/01 08:47:32  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.3  2002/06/22 10:32:22  mrnk
 *  Documented class CmdLine
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef CMDLINE_H
#define CMDLINE_H

using namespace std;

#include <string>

/** @brief the application command line
 *
 * This class parses and validates command line options in the form of an 
 * argument count and an array of argument string. It allows access to 
 * the data in an application specific manner.
 * */
class CmdLine
{
	public:
		/** @brief constructor
		 *
		 * @param i32ArgCount the argument count
		 * @param pcArgVec the argument strings vector
		 * */
		CmdLine( int i32ArgCount, char *pcArgVec[] );

		/** @brief whether the user needs help
		 *
		 * this method tests whether the user needs help. 
		 * This could happen either when the user explicitly asks for
		 * help with the -h option, or when he supplies wrong options
		 * */
		bool HelpNeeded (void) { return m_bHelpNeeded; }

		/** @brief whether the application should run in debug mode
		 * */
		bool DebugMode (void) { return m_bDebugMode; }

		/** @brief whether the user supplied the -v option */
		bool ShowVersion (void) { return m_bShowVersion; }

		/** @brief brief command line usage message */
		string Usage (void);

		/** @brief detailed command line usage message */
		string CLIHelp (void);

		/** @brief the version of the application */
		string Version (void);

	private:
		//! help flag
		bool m_bHelpNeeded;

		//! debug flag
		bool m_bDebugMode;

		//! show version flag
		bool m_bShowVersion;

    //! the program name
    string m_oStrProgname;
};

#endif //CMDLINE_H
