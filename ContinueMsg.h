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
 *  $Log: ContinueMsg.h,v $
 *  Revision 1.3  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __CONTINUEMSG_H
#define __CONTINUEMSG_H

#include <Msg.h>

/** @brief The continue session / keepalive message
 *
 * This message is sent from client to server in the Continue session
 * transaction. Keepalive messages are necessary in order to detect that a
 * user is still logged on. A client session will be expired by the server if
 * a keepalive message is not received periodically.
 * The message derives from the class Msg. Only the username is carried in the
 * payload which is 50 bytes long.
 */
class ContinueMsg : public Msg
{
	public:
		/** @brief Constructor 
		 *
		 * @param ostrName username
		 */
		ContinueMsg (string ostrName);

		/** @brief construct a ContinueMsg from Msg */
		ContinueMsg(const Msg& rkoMsg);

	protected:
		/** @brief continue message length */
		static const u_int32_t c_kui32ContinueMsgLen = 55;
};

#endif//__CONTINUEMSG_H
