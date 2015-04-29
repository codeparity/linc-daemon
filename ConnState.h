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
 *  $Log: ConnState.h,v $
 *  Revision 1.3  2002/06/22 08:19:25  mrnk
 *  Documented class ConnState.\n Removed do..while
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __CONNCLISTATE_H
#define __CONNCLISTATE_H

#include <CliState.h>
#include <LoginMsg.h>

/** @brief Connecting state logic
 *
 * This class defines the application logic when in connecting state. 
 *
 * This state is reached when the client is logging in to the server. 
 *
 * The application logic of this state is implemented in the Logic() method.
 * */
class ConnState: public CliState
{
	public:
		/** @brief constructor
		 *
		 * @param rkoLoginMsg Login message to send to the server
		 * @param i32PollInterval Period to wait before exiting from
		 * this state after the client is successfully logged in.
		 * @param i32DenyTimeout Period to wait before retrying if a
		 * login attempt is unsuccessful
		 * */
		ConnState (const LoginMsg& rkoLoginMsg, int32_t i32PollInterval
				, int32_t i32DenyTimeout);

		//! destructor
		~ConnState (void);

		/** @brief application login in the connecting state
		 *
		 * In this state, the client tries to login to the server.
		 * If the login succeeds, the client will change state to
		 * active and sleep for the keepalive period before returning.
		 * If the login fails, the client will remain in connecting
		 * state and retry after the deny timeout.
		 * */
		void Logic (void);

	private:
		//! Login message to send to the server
		LoginMsg *m_poLoginMsg;

		/** @brief the keepalive period
		 *
		 * i32PollInterval Period to wait before exiting from this
		 * state after the client is successfully logged in.
		 * */
		int32_t m_i32PollInterval;

		/** @brief the deny timeout 
		 *
		 * Period to wait before retrying if a login attempt is 
		 * unsuccessful
		 * */
		int32_t m_i32DenyTimeout;
};

#endif//__CONNCLISTATE_H
