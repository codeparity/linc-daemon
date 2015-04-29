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
 *  $Log: SrvPxy.cpp,v $
 *  Revision 1.5  2003/04/01 08:47:33  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.4  2002/06/25 14:53:55  mrnk
 *  Removed unnecessary #include <config.h> s from source files
 *
 *  Revision 1.3  2002/06/22 06:48:49  mrnk
 *  Documented class SrvPxy
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#include <SrvPxy.h>
#include <CliApp.h>
#include <iomanip>

extern "C" {
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
}

//! constructor
SrvPxy::SrvPxy (string ostrIPAddr, int32_t i32Port, int32_t i32Tmo)
{
	//! create a UDP socket
	m_i32UDPSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (m_i32UDPSocket==-1)
	{
		throw SyscallException("socket failed");
	}

	//! assign the supplied params to members
	m_ostrAddr = ostrIPAddr;
	m_i32Port = i32Port;
	m_i32Tmo = i32Tmo;
}

//! destructor
SrvPxy::~SrvPxy (void)
{
	//! close the socket while exiting
	close(m_i32UDPSocket);
}

//! send a message to the server
void SrvPxy::Send (const Msg& rkoMsg)
{
	//! prepare a sockaddr_in structure for the sendto
	struct sockaddr_in stSrvAddr;
	stSrvAddr.sin_family= AF_INET;
	inet_aton( m_ostrAddr.c_str(), &stSrvAddr.sin_addr );
	stSrvAddr.sin_port = htons(m_i32Port);

	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "C->S: " << rkoMsg.DescType() 
    /*<< ":" << setw(rkoMsg.Paylen()) << rkoMsg.Payload() */
    << endl;
	int result;

	//! send the message to the server
	result = sendto(m_i32UDPSocket, 
			rkoMsg, 
			rkoMsg.Length(), 
			0, 
			(struct sockaddr *) &stSrvAddr, 
			sizeof(stSrvAddr)
			);
	if (result==-1)
	{
		throw SyscallException("sendto failed");
	}
}

//! receive a message from the server
Msg SrvPxy::Recv (void)
{
	//! prepare a sockaddr_in structure for the recvfrom
	struct sockaddr_in stSrvAddr;
	stSrvAddr.sin_family= AF_INET;
	inet_aton( m_ostrAddr.c_str(), &stSrvAddr.sin_addr );
	stSrvAddr.sin_port = htons(m_i32Port);

	//! Calling select
	fd_set fds;
	struct timeval timeout;

	FD_ZERO(&fds);
	FD_SET(m_i32UDPSocket, &fds);

	//! use the timeout specified in the constructor
	timeout.tv_sec = m_i32Tmo;
	timeout.tv_usec = 0;

	int result;
	result = select (m_i32UDPSocket+1, &fds, NULL, NULL, &timeout);
	if (result == 0)
	{
		throw TimeoutException();
	}
	else if (result == -1)
	{
		throw SyscallException("Select failed");
	}
	//! Called select
	
	int32_t i32SockLen;
	i32SockLen = sizeof(stSrvAddr);
	char conn_s2c[1024];
	bzero(conn_s2c,1024);
	
	//! receive the message from the server
	result = recvfrom(m_i32UDPSocket, 
			conn_s2c, 
			1024, 
			0, 
			(struct sockaddr *) &stSrvAddr, 
			(socklen_t *) &i32SockLen
			);
	if (result==-1)
	{
		throw SyscallException("recvfrom failed");
	}

	//! create a Msg object from the message
	Msg oMsg(conn_s2c, result);
	CliApp::Instance()->Logger() << ends << LOG_INFO
		<< "S->C: " << oMsg.DescType() << ": " << oMsg.Payload() << endl;

	//! return the Msg object
	return oMsg;
}
