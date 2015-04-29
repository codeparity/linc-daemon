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
 *  $Log: DeInitState.h,v $
 *  Revision 1.4  2002/06/22 08:32:00  mrnk
 *  fixed typo
 *
 *  Revision 1.3  2002/06/22 08:31:02  mrnk
 *  Documented class DeinitState
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __DEINITCLISTATE_H
#define __DEINITCLISTATE_H

#include <CliState.h>
#include <LogoutMsg.h>

/** @brief The deinitializing state
 *
 * This state defines the application logic when the client is deinitializing.
 *
 * The application logic in this state is defined in the Logic() method.
 * */
class DeInitState: public CliState
{
	public:
		/** @brief constructor
		 *
		 * @param rkoLogoutMsg the logout message for performing a 
		 * clean logout
		 * */
		DeInitState (const LogoutMsg& rkoLogoutMsg);

		//! destructor 
		~DeInitState (void);

		/** @brief the application login in the deinitializing state
		 *
		 * In this state, the client will attempt a clean logout from
		 * the current session. In case of either success or failure,
		 * the client has to exit.
		 * */
		void Logic (void);

	private:
		//! the logout message for performing a clean logout
		LogoutMsg *m_poLogoutMsg;
};

#endif//__DEINITCLISTATE_H
