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
 *  $Log: CfgFile.h,v $
 *  Revision 1.4  2002/12/17 17:46:36  mrnk
 *  dup()ing on fd 0,1,2 instead of closing.
 *
 *  Revision 1.3  2002/06/22 10:49:01  mrnk
 *  Documented configuration related classes
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

/* CfgFile.h */

#ifndef __CFGFILE_H
#define __CFGFILE_H

#include <map>
#include <string>

#include <CfgErr.h>

/** @brief the configuration file class
 *
 * this class can parse simple configuration files containing 
 * <name>=<value> pairs, whitespace and hashed comments
 * It can return the parameters by name, set parameters by name and save
 * parameters back to file.
 * */
class CfgFile
{
	public:
		/** @brief constructor
		 *
		 * @param ostrFileName name of the config file
		 * */
		CfgFile (string ostrFileName);

    /** @brief query the configuration filename */
    const string& GetFileName (void) { return m_ostrFileName; }

		/** @brief get a parameter value
		 *
		 * @param rkostrKey the parameter key
		 * */
		const string& GetParam(const string& rkostrKey) const;

		/** @brief set a parameter value
		 *
		 * @param rkostrKey the parameter key
		 * @param rkostrValue the parameter value
		 * */
		void SetParam(const string& rkostrKey
				, const string& rkostrValue);

		/** Read from a file */
		void Read (string ostrFileName="");

		/** write to a file */
		void Write (string ostrFileName="");

	private:
		//! the filename
		string m_ostrFileName;

		//! parameters
		map<string, string> m_oMapParams;
};


#endif
