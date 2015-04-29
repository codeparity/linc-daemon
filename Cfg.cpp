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

#include <Cfg.h>
#include <encrypt.h>
#include <iostream>
#include <stdlib.h>

using std::endl;

//! construct from CfgFile
Cfg::Cfg (const CfgFile& rkoCfgFile)
{
  m_ostrSrvAddr = rkoCfgFile.GetParam("srvaddr");
  m_i32SrvPort = atoi(rkoCfgFile.GetParam("srvport").c_str());
  m_ostrUserName = rkoCfgFile.GetParam("username");
  try 
  {
    m_ostrPasswd = rkoCfgFile.GetParam("password");
    m_ostrAuthInfo = Encrypt(m_ostrPasswd, time(NULL));
  }
  catch (CfgErr& rErr)
  {
    m_ostrAuthInfo = rkoCfgFile.GetParam("authinfo");
  }
  m_ostrHWAddr = rkoCfgFile.GetParam("hwaddr");
}

//! get the server IP address
const string& Cfg::GetSrvAddr (void)
{
  return m_ostrSrvAddr;
}

//! get the server port
int Cfg::GetSrvPort (void)
{
  return m_i32SrvPort;
}

//! get the user name
const string& Cfg::GetUserName (void)
{
  return m_ostrUserName;
}

//! get authentication info for this username
const string& Cfg::GetAuthInfo (void)
{
  return m_ostrAuthInfo;
}

//! brief get the NIC's hardware address
const string& Cfg::GetHWAddr (void)
{
  return m_ostrHWAddr;
}

/*
 * $Log: Cfg.cpp,v $
 * Revision 1.2  2003/04/05 05:12:36  mrnk
 * Fixed version and help strings. Added support for cleartext passwords based on Rahul Mittal's code.
 *
 * Revision 1.1  2002/12/17 17:46:27  mrnk
 * dup()ing on fd 0,1,2 instead of closing.
 *
 */
