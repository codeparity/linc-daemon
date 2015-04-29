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
 *  $Log: LogStream.h,v $
 *  Revision 1.4  2002/06/22 11:03:09  mrnk
 *  typo fixed
 *
 *  Revision 1.3  2002/06/22 11:01:03  mrnk
 *  Documented the Logging classes
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __LOGSTREAM_H
#define __LOGSTREAM_H

#include <iostream>
#include <stdexcept>

#include <stdio.h>
#include <string>
extern "C" {
#include <syslog.h>
}

/** @brief a streambuf that actually logs to syslog
 *
 * this streambuf will log to syslog instead of writing to a file
 * */
class LogStreamBuf : public streambuf
{
	public:
		/** @brief construct the streambuf
		 *
		 * @param pkcIdent The identification string that'll appear in
		 * the syslog message
		 * @param i32Facility the syslog facility to use
		 * @param bDebug whether messages should be logged to stderr
		 * */
		LogStreamBuf(const char *pkcIdent, int i32Facility
				, bool bDebug)
		{
			if (bDebug)
				openlog(pkcIdent, LOG_PERROR|LOG_PID
						, i32Facility);
			else
				openlog(pkcIdent, LOG_PID
						, i32Facility);
			m_bNextPrio = false;
			m_i32Priority = LOG_DEBUG;
		}

		//! destructor
		~LogStreamBuf(void)
		{
			closelog();
		}

		/** @brief overridden overflow operator
		 *
		 * this method of streambuf is overridden in order to do
		 * special processing on the ends and endl characters
		 * */
		int overflow(int ch)
		{
			streamsize n = pptr() - pbase();
			if (n && sync())
				return EOF;

			switch (ch)
			{
				case '\n':
					/** on encountering endl, log the 
					 * message
					 * */
					syslog(m_i32Priority
							, m_ostrBuf.c_str()); 
					m_ostrBuf="";
					m_bNextPrio = false;
					break;
				case '\0':
					/** the logging priority follows ends
					 * */
					m_bNextPrio = true;
					break;
				case EOF :
					pbump (-n); // reset pptr()
					m_bNextPrio = false;
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					/** any integer following an ends is
					 * interpreted as the logging priority
					 * */
					if (m_bNextPrio)
						m_i32Priority = ch;
					else
						m_ostrBuf += ch; 
					m_bNextPrio = false;
					break;
				default: 
					/** accumulate stuff to be logged into
					 * a buffer */
					m_ostrBuf += ch; 
					m_bNextPrio = false;
					break;
			}
			return 0;
		}

	private:
		//! the buffer to log
		string m_ostrBuf;

		//! logging priority
		int m_i32Priority;

		//! whether previous character was ends
		bool m_bNextPrio;
};

//! this class derived from ostream is just a wrapper aroung LogStreamBuf
class LogStream : private LogStreamBuf, public ostream
{
	public:
		LogStream (const char *pkcIdent, int i32Facility=LOG_DAEMON
				, bool bDebug=false) 
			: LogStreamBuf(pkcIdent, i32Facility, bDebug) 
			, ostream ((LogStreamBuf *) this), ios(0) {};
};

#endif//__LOGSTREAM_H
