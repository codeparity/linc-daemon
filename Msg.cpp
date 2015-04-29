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
 *  */

#include <Msg.h>
#include <iostream>
#include <iomanip>
#ifdef IOMANIP_WORKS
#include <sstream>
#else//iomanip does not work
#include <strstream>
#endif//IOMANIP_WORKS

Msg::Msg (const char *pcMsg, int32_t i32Len)
  : m_oStrMsg(pcMsg, i32Len)
{
}

Msg::Msg (const Msg& rkoMsg)
{
  m_oStrMsg = rkoMsg.m_oStrMsg;
}

const Msg& Msg::operator= (const Msg& rkoMsg)
{
  m_oStrMsg = rkoMsg.m_oStrMsg;
	return *this;
}

Msg::~Msg (void)
{
}

int32_t Msg::Length (void) const
{
  return m_oStrMsg.size();
}

MSGTYPE_en Msg::Type (void) const
{
	switch (m_oStrMsg[0])
	{
		case LOGGEDIN:
		case DENIED:
		case CONTINUE:
		case CONTINUING:
		case LOGOUT:
		case LOGGEDOUT:
		case LOGIN:
		case DISCONNECTED:
		case PROTOERROR:
			return (MSGTYPE_en) m_oStrMsg[0];

		default:
			return UNKNOWN;
	}
}

string Msg::DescType (MSGTYPE_en enType)
{
	switch (enType)
	{
		case LOGGEDIN:
			return "Logged in";

		case DENIED:
			return "Denied";

		case CONTINUE:
			return "Continue";

		case CONTINUING:
			return "Continuing";

		case LOGOUT:
			return "Logout";

		case LOGGEDOUT:
			return "Logged out";

		case LOGIN:
			return "Login";

		case DISCONNECTED:
			return "Disconnected";

		case PROTOERROR:
			return "Protocol error";

		default:
			return "Unknown";
	}
}

string Msg::DescType (void) const
{
	return DescType(Type());
}

string Msg::Payload (void) const
{
  return m_oStrMsg.substr(c_kui32MsgHdrLen);
}

Msg::operator const char * (void) const
{
  return m_oStrMsg.c_str();
}

Msg::Msg(MSGTYPE_en enType, int32_t i32Len)
{
#ifdef IOMANIP_WORKS
  ostringstream oLengthHdrField;
	oLengthHdrField << setw(1) << (unsigned char) enType 
    << setw(c_kui32MsgHdrLen - 1) << setfill('\0') << left << i32Len;
  m_oStrMsg = oLengthHdrField.str();

  while (m_oStrMsg.size()<i32Len)
  {
    m_oStrMsg += '\0';
  }
#else //iomanip does not work
  char *pcMsg = new char[i32Len];
  bzero(pcMsg, i32Len);

  //! set the message type
  pcMsg[0] = enType;

  //! write the message length in ASCII starting from the 2nd byte
  strstream oLengthHdrField(pcMsg+1, c_kui32MsgHdrLen - 1);
  oLengthHdrField << i32Len << ends;

  for (int i32I=0; i32I<i32Len; i32I++)
  {
    m_oStrMsg += pcMsg[i32I];
  }
  delete pcMsg;
#endif//IOMANIP_WORKS
}

void Msg::SetPayload (const char *kpcMsg, int32_t i32Len)
{
  for (int i=0; ((i<i32Len) && (i<m_oStrMsg.size()-c_kui32MsgHdrLen)); i++)
  {
    m_oStrMsg[i+c_kui32MsgHdrLen] = kpcMsg[i];
  }
}

void Msg::SetPayload (const string rkoStrMsg)
{
  for (int i=0; ((i<rkoStrMsg.size()) 
        && (i<m_oStrMsg.size()-c_kui32MsgHdrLen)); i++)
  {
    m_oStrMsg[i+c_kui32MsgHdrLen] = rkoStrMsg[i];
  }
}

/*
 *  This source file is part of linc $Name: rel-1-2 $
 *  
 *  $Log: Msg.cpp,v $
 *  Revision 1.5  2003/04/01 08:47:33  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.4  2002/06/26 18:27:58  mrnk
 *  Added version communicator base class.
 *  Added stub for version 1 communicator.
 *  Added both classes into Makefile.am
 *  Updated TODO to reflect the completed tasks.
 *
 *  ----------------------------------------------------------------------
 *
 *  Committing in .
 *
 *  Modified Files:
 *  	Makefile.am Makefile.in Msg.cpp TODO stamp-h.in
 *  Added Files:
 *  	V1Comm.cpp V1Comm.h VComm.h
 *  ----------------------------------------------------------------------
 *
 *  Revision 1.3  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */
