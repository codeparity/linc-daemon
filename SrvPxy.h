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
 *  $Log: SrvPxy.h,v $
 *  Revision 1.3  2002/06/22 06:48:49  mrnk
 *  Documented class SrvPxy
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __SRVPXY_H
#define __SRVPXY_H

#include <stdexcept>
#include <Msg.h>

//! Exception thrown when a system call fails
class SyscallException : public runtime_error 
{
	public:
		//! constructor
		SyscallException (string ostrDesc) : runtime_error(ostrDesc)
		{}
};

//! Exception thrown in case of select timeouts
class TimeoutException : public runtime_error 
{
	public:
		//! constructor
		TimeoutException (void) : runtime_error("Select timeout")
		{}
};

/** @brief Proxy for the Cyberoam server
 *
 * This class will act as a proxy for the actual Cyberoam server. The Cyberoam
 * server usually listens on UDP port 6060. Messages are exchanged between the
 * client and server over UDP. 
 *
 * Sending messages to the server is implemented via the Send() method and
 * receiving messages from the server is implemented by the Recv() method.
 * 
 * Since UDP does not handle error handling and
 * retransmissions, we have to provide for that in our proxy implementation.
 * Thus the proxy has a timeout value (in seconds) associated with it. Recv()
 * calls will throw a TimeoutException if the server does not respond in the
 * specified time.
 * 
 * */
class SrvPxy
{
	public:
		/** @brief constructor
		 *
		 * @param ostrIPAddr The server IP address
		 * @param i32Port The server port
		 * @param i32Tmo The receive timeout. If in a Recv() call, 
		 * the server does respond within this time, a
		 * TimeoutException will be thrown.
		 * */
		SrvPxy (string ostrIPAddr, int32_t i32Porti, int32_t i32Tmo);

		//! destructor
		~SrvPxy (void);

		//! Send the given message to the server
		void Send (const Msg& rkoMsg);

		//! Return with the message received from the server
		Msg Recv(void);

	private: 
		//! Server IP address
		string m_ostrAddr;

		//! Server port
		int32_t m_i32Port;

		//! Descriptor of communication socket
		int32_t m_i32UDPSocket;

		//! Receive timeout
		int32_t m_i32Tmo;
};

#endif//__SRVPXY_H
