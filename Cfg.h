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
 *  $Log: Cfg.h,v $
 *  Revision 1.4  2002/12/17 17:46:29  mrnk
 *  dup()ing on fd 0,1,2 instead of closing.
 *
 *  Revision 1.3  2002/06/22 10:49:01  mrnk
 *  Documented configuration related classes
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

/* Cfg.h */

#ifndef __CFG_H
#define __CFG_H

#include <CfgFile.h>

/** @brief application specific configuration info
 *
 * this class extracts application specific parameters from a generic CfgFile
 * and makes it available as member variables 
 * */
class Cfg
{
  public:
    //! construct from a CfgFile
    Cfg (const CfgFile& rkoCfgFile);

    //! get the server IP address
    const string& GetSrvAddr (void);

    //! get the server port
    int GetSrvPort (void);

    //! get the user name
    const string& GetUserName (void);

    /** @brief get authentication info for this username
     *
     * This could either be present in the file directly or can be 
     * generated from a clear text password (to be supported in the next
     * version)
     * @todo clear text passwords
     */
    const string& GetAuthInfo (void);

    /** @brief get the NIC's hardware address
     * 
     * @todo Ideally this should be autodetected. 
     */
    const string& GetHWAddr (void);
    

  private:
    //! server IP address
    string m_ostrSrvAddr;

    //! server UDP port 
    int m_i32SrvPort;

    //! username
    string m_ostrUserName;

    //! authentication info
    string m_ostrAuthInfo;

    //! clear text password
    string m_ostrPasswd;

    //! machine hardware address
    string m_ostrHWAddr;
};


#endif
