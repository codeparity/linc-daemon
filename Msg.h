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
 *  $Log: Msg.h,v $
 *  Revision 1.5  2003/04/01 08:47:33  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.4  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __MSG_H
#define __MSG_H

#include <stdexcept>
#include <sys/types.h>
#include <string>

using namespace std;

//! message type code
enum MSGTYPE_en
{
	UNKNOWN		= -1,	//!< The message type is not among known types
	LOGGEDIN	= 2,	//!< S->C You are logged in
	DENIED	 	= 3,	//!< S->C Login denied
	CONTINUE	= 4,	//!< C->S Continue this session, Keepalive
	CONTINUING	= 5,	//!< S->C Continuing this session, Keepalive ACK
	LOGOUT		= 7,	//!< C->S Logout of this session
	LOGGEDOUT	= 8,	//!< S->C You've successfully logged out
	DISCONNECTED	= 14,	//!< S->C You're not logged in, keepalive NAK
	LOGIN		= 33,	//!< C->S Log in
	PROTOERROR	= 0x65, //!< S->C Malformed or unexpected message
};

//! Invalid message exception
class InvalidMsgException : public runtime_error 
{
	public:
		InvalidMsgException (string ostrDesc) : runtime_error(ostrDesc)
		{}
};

/** @brief Message class
 *
 * This class provides primitives for parsing and/or building generic messages. 
 * Transaction specific messages can be derived from this class.
 * Cyberoam messages are carried within UDP datagrams. The message consists
 * of a fixed length header followed by a variable length payload. The first
 * byte of the header contains the type of message to follow. The next four
 * bytes contain the length of the message in ASCII as a null terminated
 * string. The remain bytes are the payload.
 * */
class Msg
{
	public:
		/** @brief Construct a message from a raw byte array
		 *
		 * This constructor is useful to directly build a message out 
		 * of the UDP payload.
		 * @param kpcMsg The byte array
		 * @param i32Len Length of the byte array
		 * */
		Msg (const char *kpcMsg, int32_t i32Len);

		/** @brief Copy constructor */
		Msg (const Msg& rkoMsg);

		/** @brief Overloaded assignment operator */
		const Msg& operator= (const Msg& rkoMsg);

		/** @brief destructor */
		~Msg (void);

		/** @brief return the length of this message */
		int32_t Length (void) const;

		/** @brief return the message type */
		MSGTYPE_en Type (void) const;

		/** @brief convert a numeric type to its verbose description
		 *
		 * @param enType The numeric type
		 * */
		static string DescType (MSGTYPE_en enType);

		/** @brief return the description of message type */
		string DescType (void) const;

    /** @brief return the payload of the message as a string */
    string Payload (void) const;
    
		/** @brief get the byte array corresponding to this message */
		operator const char * (void) const;

	protected:
		/** @brief The message header length 
		 *
		 * This member needs to be accessible to derived classes for
		 * calculating offsets
		 * */
		static const u_int32_t c_kui32MsgHdrLen = 5;

		/** @brief Construct an empty message
		 *
		 * This constructor is protected and can only be accessed by
		 * the classes derived from Msg. It allows the classes to
		 * define a payload in or after the constructor 
		 * @param enType Type of the new message
		 * @param i32Len Length of the new message
		 * */
		Msg(MSGTYPE_en enType, int32_t i32Len);

		/** @brief defines the message payload
		 *
		 * This method is called by classes derived from this class in
		 * order to define the payload 
		 * @param rkoStrMsg The payload
		 * */
		void SetPayload (const string rkoStrMsg);

		/** @brief defines the message payload
		 *
		 * This method is called by classes derived from this class in
		 * order to define the payload 
		 * @param kpcMsg The byte array containing payload
		 * @param i32Len payload length
		 * */
		void SetPayload (const char *kpcMsg, int32_t i32Len);

	private:
    /// the message
    string m_oStrMsg;
};

#endif//__MSG_H
