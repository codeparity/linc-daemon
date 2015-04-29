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
 *  $Log: LoginMsg.h,v $
 *  Revision 1.5  2003/04/01 08:47:32  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.4  2003/02/09 03:23:07  mrnk
 *  Incorporated fixes for 2 NICs.
 *
 *  Revision 1.3  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __LOGINMSG_H
#define __LOGINMSG_H

#include <Msg.h>
#include <string>

/** @brief The login message
 * 
 * This message is sent by the client to the server in the login transaction.
 * It derives from the generic Msg class. 
 * The current implementation of this class conforms to the current version of
 * the client - server protocol.
 * The payload is structured as follows:
 * 1) 30 bytes for username
 * 2) 60 bytes for authentication information
 * 3) 17 bytes for the client's interface hardware address
 *
 * @todo This class has to be renamed to V2LoginMsg when we will support
 * multiple versions of the protocol
 */
class LoginMsg : public Msg
{
	public:
		/** @brief Construct a login message 
		 *
		 * @param ostrName The username
		 * @param ostrAuth The authentication string
		 * @param ostrHWAddr The client machine's hardware address
		 * @todo we need a constructor that can accept the clear text
		 * password instead of the authentication string.
		 */
		LoginMsg(string ostrName, string ostrAuth, string ostrHWAddr);

		/** @brief construct a LoginMsg from Msg */
		LoginMsg(const Msg& rkoMsg);

		/** @brief Return the username */
		string Name(void);

		/** @brief Return the authentication info */
		string Auth(void);

		/** @brief Return the hardware address */
		string HWAddr(void);

	protected:
		/** @brief Maximum username length */
		static const u_int32_t c_kui32NameLen = 30;

		/** @brief Maximum authentication info length */
		static const u_int32_t c_kui32AuthLen = 60;

		/** @brief Hardware address length */
		static const u_int32_t c_kui32HWAddrLen = 17;

		/** @brief return the payload length of login message */
		static int32_t LoginMsgPayLen (void) {
			return c_kui32NameLen + c_kui32AuthLen 
				+ c_kui32HWAddrLen;
		}
};

#endif//__LOGINMSG_H
