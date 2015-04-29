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
 *  $Log: CliApp.cpp,v $
 *  Revision 1.5  2003/04/01 11:13:34  mrnk
 *  Fixed crash when /home/mayur was not defined. Added initscript.
 *
 *  Revision 1.4  2002/12/17 17:46:39  mrnk
 *  dup()ing on fd 0,1,2 instead of closing.
 *
 *  Revision 1.3  2002/06/22 11:33:18  mrnk
 *  Documented class CliApp
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

extern "C" {
#include <signal.h>
}
#include <stdlib.h>
#include <Cfg.h>
#include <CliApp.h>
#include <ConnState.h>
#include <ActiveState.h>
#include <InactiveState.h>
#include <DiscState.h>
#include <DeInitState.h>

//! the polling interval (i.e. interval for sending keepalive messages 
#define POLLINTERVAL 120

//! the period spent in inactive state
#define NOTRUNNINTERVAL 300

//! period to wait after the server denies login
#define DENY_TMO 300

//! time to wait for server responses
#define RECV_TMO 10

//! system-wide cfg file
#define SYS_RCFILE "/etc/lincrc"

//! per user cfg file
#define USER_RCFILE ".lincrc"

//! initialize the instance pointer
CliApp *CliApp::c_poInstance = NULL;

//! singleton initializer method
CliApp *CliApp::Instance(const CmdLine& rkoCmd)
{
  if (c_poInstance != NULL)
    throw runtime_error("instance of CliApp exists");
  c_poInstance = new CliApp(rkoCmd);
  return c_poInstance;
}

//! singleton access method
CliApp *CliApp::Instance(void)
{
  if (c_poInstance == NULL)
    throw runtime_error("no previous instance of CliApp");
  else 
    return c_poInstance;
}

//! constructor
CliApp::CliApp (const CmdLine& rkoCmd) : m_oCmd(rkoCmd)
{
  /** if the user has specified debug mode, initialize the LogStream
   * accordingly  */
  if (m_oCmd.DebugMode())
    m_poLogStream = new LogStream(PACKAGE, LOG_DAEMON, true);
  else
    m_poLogStream = new LogStream(PACKAGE, LOG_DAEMON);

  //! ok, we can log now
  *m_poLogStream << ends << LOG_DEBUG
    << "CliApp constructor called." << endl;

  //! try to get our configuration
  m_poCfgFile = NULL;
  try 
  {
    const char *pcHome = getenv("HOME");
    string ostrHomeDir("");
    if (NULL != pcHome)
    {
      ostrHomeDir = pcHome;
    }
    string ostrHomeRCFile = ostrHomeDir + "/" + USER_RCFILE;
    //! first from the per user config file
    m_poCfgFile = new CfgFile(ostrHomeRCFile);
  }
  catch (runtime_error& rErr)
  {
    *m_poLogStream << ends << LOG_CRIT
      << rErr.what() << endl;

    try
    {
      //! fall back to the system-wide config file
      m_poCfgFile = new CfgFile(SYS_RCFILE);
    }
    catch (runtime_error& rErr)
    {
      *m_poLogStream << ends << LOG_CRIT
        << rErr.what() << endl;
      //! we can't proceed without configuration
      exit(-1);
    }
  }
  
  try 
  {
    //! get our configuration from the config file
    Cfg oCfg(*m_poCfgFile);
  
    //! initialize the UDP server proxy
    m_poSrvPxy = new SrvPxy(oCfg.GetSrvAddr(), oCfg.GetSrvPort() 
        , RECV_TMO);
  
    //! initialize application states
    m_oMapIDToState[EXIT] = NULL;
    m_oMapIDToState[ERROR] = NULL;
    m_oMapIDToState[CONN] = new ConnState(
      LoginMsg(oCfg.GetUserName()
      , oCfg.GetAuthInfo()
      , oCfg.GetHWAddr()), POLLINTERVAL, DENY_TMO);
    m_oMapIDToState[ACTIVE] = new ActiveState(
      ContinueMsg(oCfg.GetUserName())
      , POLLINTERVAL);
    m_oMapIDToState[DISC] = new DiscState(
      LogoutMsg(oCfg.GetUserName()));
    m_oMapIDToState[DEINIT] = new DeInitState(
      LogoutMsg(oCfg.GetUserName()));
    m_oMapIDToState[INACTIVE] = new InActiveState(NOTRUNNINTERVAL);
  }
  catch (runtime_error& rErr)
  {
    //! if any of that failed, we can NOT proceed
    *m_poLogStream << ends << LOG_CRIT
      << rErr.what() << endl;
    exit(-1);
  }

  //! set signal handlers
  signal(SIGUSR1, CliApp::SignalHandler);
  signal(SIGUSR2, CliApp::SignalHandler);
  signal(SIGINT,  CliApp::SignalHandler);
  signal(SIGTERM, CliApp::SignalHandler);
  signal(SIGHUP, SIG_IGN);
}

int32_t CliApp::Run (void)
{
  //! enter the initial state
  m_poState = m_oMapIDToState[CONN];

  //! yay
  *m_poLogStream << ends << LOG_DEBUG 
    << "CliApp running." << endl;

  //! unless there is an error or we are asked to exit,
  while (m_poState)
  {
    //! run the current state logic
    m_poState->Logic();
  }

  return 0;
}

//! state transition
void CliApp::StateTrans(STATE_ID_en enNewState)
{
  m_poState = m_oMapIDToState[enNewState];
}

//! destructor
CliApp::~CliApp (void)
{
  *m_poLogStream << ends << LOG_DEBUG 
    << "CliApp destructor called." << endl;

  //! delete all application states
  for (map<STATE_ID_en, CliState *>::iterator 
      oMapIter = m_oMapIDToState.begin();
      oMapIter != m_oMapIDToState.end();
      oMapIter++
      )
    if (oMapIter->second)
    {
      delete oMapIter->second;
      oMapIter->second = NULL;
    }

  //! clean the UDP server proxy
  delete m_poSrvPxy;
  m_poSrvPxy = NULL;

  //! delete the application logger
  delete m_poLogStream;
  m_poLogStream = NULL;

  //! delete the configuration file
  delete m_poCfgFile;
  m_poCfgFile = NULL;
}

//! singleton destructor
void CliApp::Destroy (void)
{
  if (c_poInstance)
  {
    delete c_poInstance;
    c_poInstance = NULL;
  }
}

//! signal handler
void CliApp::SignalHandler(int32_t i32Sig)
{
  switch (i32Sig)
  {
    case SIGUSR1:
      Instance()->StateTrans(CONN);
      break;
    case SIGUSR2:
      Instance()->StateTrans(DISC);
      break;
    case SIGINT:
      Instance()->StateTrans(DEINIT);
      break;
    case SIGTERM:
      Instance()->StateTrans(DEINIT);
      break;
    default:
      Instance()->StateTrans(ERROR);
  }
}
