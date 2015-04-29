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
 *  $Log: CliState.h,v $
 *  Revision 1.3  2002/06/22 07:30:57  mrnk
 *  Documented class CliState
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __CLISTATE_H
#define __CLISTATE_H

/** @brief Identifier for the client state
 *
 * This enum only identifies the state of the client. The behaviour of the
 * client in that state is modelled by the CliState abstract class.
 * */
enum STATE_ID_en
{
	INIT,		//!< The initial state
	CONN,		//!< The client is connecting to the server
	ACTIVE,		//!< The client is connected and active
	DISC,		//!< The client is disconnecting from the server
	INACTIVE,	//!< The client is inactive (suspended)
	DEINIT,		//!< The client is deinitializing
	ERROR,		//!< The client encountered an error
	EXIT,		//!< The exit state
};

/** @brief The client state
 *
 * This class models the behaviour of the client. The Logic() method has to be
 * implemented by derived classes to define application logic in any
 * particular state.
 * */
class CliState
{
	public:
		/** @brief State logic 
		 *
		 * This method has to implemented by derived classes to define
		 * application logic.
		 * */
		virtual void Logic(void)=0;
};

#endif//__CLISTATE_H
