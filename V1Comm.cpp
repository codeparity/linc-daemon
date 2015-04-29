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

/* V1Comm.cpp */

#include <V1Comm.h>
#include <LogStream.h>
#include <CliApp.h>

V1Comm::V1Comm (SrvPxy *poSrv, string ostrUserName, string ostrPassword) 
	: VComm (poSrv)
{
	m_ostrUserName = ostrUserName;
	m_ostrPassword = ostrPassword;
}

//! The login transaction interface
void V1Comm::Login (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V1Comm: Login" << endl;
}

//! The logout transaction interface
void V1Comm::Logout (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V1Comm: Logout" << endl;
}

//! The keepalive transaction interface
void V1Comm::KeepAlive (void)
{
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "V1Comm: Keepalive" << endl;
}

/* 
 * This file is part of linc $Name: rel-1-2 $
 *
 * $Log: V1Comm.cpp,v $
 * Revision 1.1  2002/06/26 18:27:58  mrnk
 * Added version communicator base class.
 * Added stub for version 1 communicator.
 * Added both classes into Makefile.am
 * Updated TODO to reflect the completed tasks.
 *
 * ----------------------------------------------------------------------
 *
 * Committing in .
 *
 * Modified Files:
 * 	Makefile.am Makefile.in Msg.cpp TODO stamp-h.in
 * Added Files:
 * 	V1Comm.cpp V1Comm.h VComm.h
 * ----------------------------------------------------------------------
 *
 *
 * */
