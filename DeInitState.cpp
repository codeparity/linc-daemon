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
 *  $Log: DeInitState.cpp,v $
 *  Revision 1.4  2002/06/25 14:53:55  mrnk
 *  Removed unnecessary #include <config.h> s from source files
 *
 *  Revision 1.3  2002/06/22 08:31:02  mrnk
 *  Documented class DeinitState
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

extern "C" {
#include <unistd.h>
}
#include <DeInitState.h>
#include <iostream>
#include <CliApp.h>

//! constructor
DeInitState::DeInitState (const LogoutMsg& rkoLogoutMsg)
{
	m_poLogoutMsg = new LogoutMsg(rkoLogoutMsg);
}

//! destructor
DeInitState::~DeInitState (void)
{
	delete m_poLogoutMsg;
	m_poLogoutMsg = NULL;
}

//! the application login in deinitializing state
void DeInitState::Logic (void)
{
	CliApp::Instance()->Logger() << ends << LOG_DEBUG 
		<< "DeInit state logic" << endl;

	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "Disconnecting" << endl;

	//! send a logout message to the server
	CliApp::Instance()->Server()->Send(*m_poLogoutMsg);
	try 
	{
		//! try to receive a response from the server
		Msg oRecvMsg = CliApp::Instance()->Server()->Recv();
		CliApp::Instance()->Logger() << ends << LOG_INFO 
			<< "DEINIT => EXIT" << endl;
		//! we've cleanly logged out :). enter exit state
		CliApp::Instance()->StateTrans(EXIT);
	} 
	catch (TimeoutException& roExc) 
	{ 
		//! the server did not respond for a long time
		CliApp::Instance()->Logger() << ends << LOG_DEBUG 
			<< "Timeout in logout" << endl;
		/** we've haven't cleanly logged out :(. enter exit state 
		 * anyway
		 * */
		CliApp::Instance()->StateTrans(EXIT);
	}
	catch (SyscallException& roExc)
	{
		CliApp::Instance()->Logger() << ends << LOG_CRIT
			<< "Syscall failed in DEINIT: "
			<< roExc.what() << endl;
		CliApp::Instance()->StateTrans(ERROR);
	}

}
