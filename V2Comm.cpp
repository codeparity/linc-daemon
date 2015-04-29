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

/* V2Comm.cpp */

#include <V2Comm.h>
#include <LogStream.h>
#include <CliApp.h>

V2Comm::V2Comm (SrvPxy *poSrv, string ostrUserName, string ostrPassword) 
	: VComm (poSrv)
{
	throw ("V2Comm: clear text passwords are not implemented yet.");

	m_ostrUserName = ostrUserName;
	m_ostrPassword = ostrPassword;
}

//! The login transaction interface
void V2Comm::Login (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V2Comm: Login" << endl;
}

//! The logout transaction interface
void V2Comm::Logout (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V2Comm: Logout" << endl;
}

//! The keepalive transaction interface
void V2Comm::KeepAlive (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V2Comm: Keepalive" << endl;
}

/* 
 * This file is part of linc $Name: rel-1-2 $
 *
 * $Log: V2Comm.cpp,v $
 * Revision 1.1  2002/07/06 01:55:33  mrnk
 * Added stub for V2Comm
 *
 *
 * */
