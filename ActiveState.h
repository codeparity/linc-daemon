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
 *  $Log: ActiveState.h,v $
 *  Revision 1.3  2002/06/22 07:31:22  mrnk
 *  Documented class ActiveState
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __ACTIVECLISTATE_H
#define __ACTIVECLISTATE_H

#include <CliState.h>
#include <ContinueMsg.h>

/** @brief Active state logic
 *
 * This class defines the application logic when in active state. 
 *
 * This state is reached when the client has logged in to the server. 
 *
 * The application logic of this state is implemented in the Logic() method.
 * */
class ActiveState: public CliState
{
	public:
		/** @brief constructor
		 *
		 * @param rkoContinueMsg keepalive message to send to the
		 * server periodically
		 * @param i32PollInterval period for sending keepalive
		 * messages
		 * */
		ActiveState (const ContinueMsg& rkoContinueMsg
				, int32_t i32PollInterval);
		//! destructor
		~ActiveState (void);

		/** @brief The application logic of the ActiveState
		 * 
		 * In this state, the client periodically sends keepalive 
		 * (ContinueMsg) messages to the server(SrvPxy) and listens 
		 * for its response. If the response is positive, the client 
		 * continues to be in active state. If the response is 
		 * negative, the client goes to connecting state (ConnState).
		 * */
		void Logic (void);

	private:
		//! keepalive message to send to the server periodically
		ContinueMsg *m_poContinueMsg;

		//! period for sending keepalive messages
		int32_t m_i32PollInterval;
};

#endif//__ACTIVECLISTATE_H
