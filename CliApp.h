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
 *  $Log: CliApp.h,v $
 *  Revision 1.3  2002/06/22 11:33:18  mrnk
 *  Documented class CliApp
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#ifndef __CLIAPP_H
#define __CLIAPP_H

#include <CmdLine.h>
#include <LogStream.h>
#include <CliState.h>
#include <map>
#include <SrvPxy.h>
#include <CfgFile.h>

/** @brief the Cyberoam client application class
 *
 * This class implements the Cyberoam client application. The client is a
 * state machine. States are identified by STATE_ID_en and characterized by
 * CliState.
 *
 * This class is a singleton because we need a single instance of this class
 * in our application and this instance has to be accessible from multiple
 * parts of the program.
 *
 * Calling the Run() method starts the state machine. State transitions happen
 * either due to the message exchanges between the client and server or due to
 * external stimuli by the user in the form of signals.
 * */
class CliApp
{
	public:
		/** @brief the singleton initializer method
		 *
		 * @param rkoCmd command line options
		 * */
		static CliApp *Instance(const CmdLine& rkoCmd);

		/** @brief the singleton access method */
		static CliApp *Instance(void);

		/** @brief the singleton instance destructor */
		static void Destroy (void);

		/** @brief method to start the state machine */
		int32_t Run (void);

		/** @brief the UDP server proxy class */
		SrvPxy *Server (void) { return m_poSrvPxy; }

		/** @brief effect a state transition
		 *
		 * @param enNewState state to enter 
		 * */
		void StateTrans(STATE_ID_en enNewState);

		/** @brief application signal handler */
		static void SignalHandler(int32_t i32Sig);

		/** @brief application logger */
		ostream& Logger (void) { return *m_poLogStream; }

	protected:
		/** @brief singleton constructor */
		CliApp (const CmdLine& rkoCmd);

		/** @brief singleton destructor */
		~CliApp (void);

	private:
		//! actual instance of the application class 
		static CliApp *c_poInstance;

		//! current state
		CliState *m_poState;

		//! map of possible application states
		map <STATE_ID_en, CliState *> m_oMapIDToState;

		//! the UDP server proxy
		SrvPxy *m_poSrvPxy;

		//! the application logger
		LogStream *m_poLogStream;

		//! the application configuration file
		CfgFile *m_poCfgFile;

		//! the application command line
		CmdLine m_oCmd;
};

#endif//__CLIAPP_H
