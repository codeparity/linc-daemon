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
 *  */

/* VComm.h */

#ifndef __VCOMM_H
#define __VCOMM_H

#include <stdexcept>
#include <SrvPxy.h>

//! Exception thrown when the server reports failure
class TransException : public runtime_error 
{
	public:
		//! constructor
		TransException (string ostrDesc) : runtime_error(ostrDesc)
		{}
};

/** @brief The Version Communicator class
 *
 * This class is responsible for implementing a particular version of the
 * Cyberoam protocol. The public interface of the class will be methods that
 * allow clients of this class to perform the generic Login/Logout/Keepalive
 * transactions. These methods will all return on success and throw
 * appropriate exceptions on failure.
 * */
class VComm
{
	public:
		/** @brief the constructor 
		 *
		 * @param poSrv The server proxy to use to communicate with
		 * the server
		 * */
		VComm (SrvPxy *poSrv);

		//! The login transaction interface
		virtual void Login (void)=0;

		//! The logout transaction interface
		virtual void Logout (void)=0;

		//! The keepalive transaction interface
		virtual void KeepAlive (void)=0;

	protected:
		//! The server proxy for communicating with the server
		SrvPxy *m_poSrv;
};

// Implementation
inline VComm::VComm (SrvPxy *poSrv)
{
	m_poSrv = poSrv;
}

#endif

/* 
 * This file is part of linc $Name: rel-1-2 $
 *
 * $Log: VComm.h,v $
 * Revision 1.1  2002/06/26 18:27:58  mrnk
 * Added version communicator base class.
 * Added stub for version 1 communicator.
 * Added both classes into Makefile.am
 * Updated TODO to reflect the completed tasks.
 *
 * ----------------------------------------------------------------------
 *
 * Committing in .
 *
 * Modified Files:
 * 	Makefile.am Makefile.in Msg.cpp TODO stamp-h.in
 * Added Files:
 * 	V1Comm.cpp V1Comm.h VComm.h
 * ----------------------------------------------------------------------
 *
 *
 * */
