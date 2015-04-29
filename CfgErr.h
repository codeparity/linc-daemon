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
 */

#ifndef __CFGERR_H
#define __CFGERR_H

#include <string>
#include <stdexcept>

using namespace std;

/** @brief configuration error
 *
 * This exception is thrown whenever a configuration error is discovered by
 * linc
 */
class CfgErr : public runtime_error
{
  public:
    /** @brief constructor */
    CfgErr (const string& rkostrFileName, const string& rkostrErrorMsg)
      : runtime_error (rkostrFileName + ": " + rkostrErrorMsg)
    {
      m_ostrFileName = rkostrFileName;
      m_ostrErrorMsg = rkostrErrorMsg;
    }

    /** @brief destructor */
    ~CfgErr (void) throw () {}

    //! get the name of the misconfigured file
    const string& GetFileName (void) { return m_ostrFileName; }

    //! get the error description
    const string& GetErrorMsg (void) { return m_ostrErrorMsg; }

  private:
    //! the file name which had the error
    string m_ostrFileName;

    //! the error description
    string m_ostrErrorMsg;
};

#endif//__CFGERR_H

/*
 * $Log: CfgErr.h,v $
 * Revision 1.2  2003/04/01 08:47:32  mrnk
 * Fixed code to work with gcc3.
 *
 * Revision 1.1  2002/12/17 17:46:31  mrnk
 * dup()ing on fd 0,1,2 instead of closing.
 *
 */
