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
 *  $Log: ActiveState.cpp,v $
 *  Revision 1.5  2002/06/25 14:53:55  mrnk
 *  Removed unnecessary #include <config.h> s from source files
 *
 *  Revision 1.4  2002/06/22 08:17:19  mrnk
 *  removed unnecessary return statements
 *
 *  Revision 1.3  2002/06/22 07:31:22  mrnk
 *  Documented class ActiveState
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

extern "C" {
#include <unistd.h>
}
#include <ActiveState.h>
#include <iostream>
#include <CliApp.h>

//! constructor
ActiveState::ActiveState (const ContinueMsg& rkoContinueMsg
		, int32_t i32PollInterval)
{
	m_poContinueMsg = new ContinueMsg(rkoContinueMsg);
	m_i32PollInterval = i32PollInterval;
}

//! destructor
ActiveState::~ActiveState (void)
{
	delete m_poContinueMsg;
	m_poContinueMsg = NULL;
}

//! application logic
void ActiveState::Logic (void)
{
	CliApp::Instance()->Logger() << ends << LOG_DEBUG
		<< "Active state logic" << endl;

	CliApp::Instance()->Logger() << ends << LOG_INFO 
		<< "Continuing" << endl;

	//! send a keepalive message to the server
	CliApp::Instance()->Server()->Send(*m_poContinueMsg);
	try 
	{
		//! try to get a response from the server
		Msg oRecvMsg = CliApp::Instance()->Server()->Recv();

		//! if the server does not respond positively
		if (oRecvMsg.Type() != CONTINUING )
		{
			//! the application should change state to connecting
			CliApp::Instance()->Logger() << ends << LOG_INFO 
				<< "ACTIVE => CONN" << endl;
			CliApp::Instance()->StateTrans(CONN);
		}
		else
		{
			//! otherwise, we're still active
			CliApp::Instance()->Logger() << ends << LOG_INFO
				<< "ACTIVE" << endl;
			//! sleep for some time before the next keepalive
			sleep(m_i32PollInterval);
		}
	} 
	catch (TimeoutException& roExc) 
	{ 
		//! if the server does not respond for some time
		CliApp::Instance()->Logger() << ends << LOG_DEBUG
			<< "Timeout in continue" << endl;
	}
	catch (SyscallException& roExc)
	{
		//! if we are interrupted before the server can respond
		CliApp::Instance()->Logger() << ends << LOG_CRIT
			<< "Syscall failed in ACTIVE: "
			<< roExc.what() << endl;
		CliApp::Instance()->StateTrans(ERROR);
	}
}
