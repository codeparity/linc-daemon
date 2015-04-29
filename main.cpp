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
 *  $Log: main.cpp,v $
 *  Revision 1.9  2003/04/01 11:13:34  mrnk
 *  Fixed crash when /home/mayur was not defined. Added initscript.
 *
 *  Revision 1.8  2003/04/01 08:47:33  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.7  2002/12/18 08:14:33  mrnk
 *  Added a fork to prevent the process from reacquiring a terminal. Thanks to Sandip Bhattacharya for pointing this out.
 *
 *  Revision 1.6  2002/12/17 17:46:49  mrnk
 *  dup()ing on fd 0,1,2 instead of closing.
 *
 *  Revision 1.5  2002/12/17 15:52:32  mrnk
 *  Moved daemonization code into a separate function.
 *
 *  Revision 1.4  2002/06/25 14:53:55  mrnk
 *  Removed unnecessary #include <config.h> s from source files
 *
 *  Revision 1.3  2002/06/22 12:09:47  mrnk
 *  documented main.cpp
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */
#include <stdlib.h>
#include <CmdLine.h>
#include <CliApp.h>
extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
}

enum FORK_STATUS_en
{
  FORK_ERROR = -1,
  FORK_CHILD = 0
};

void Daemonize (void);

int main(int argc, char *argv[])
{
  //! parse the command line
  CmdLine oCmd (argc, argv);
  
  //! if user is querying the version, show him and exit
  if (oCmd.ShowVersion())
  {
    cerr << oCmd.Version() << endl;
    return 0;
  }

  //! if the user needs help, give it and exit
  if (oCmd.HelpNeeded())
  {
    cerr << oCmd.Version() << endl;
    cerr << "Usage: " << oCmd.Usage() << endl;
    cerr << oCmd.CLIHelp();
    return 0;
  }

  //! if we are not to start in debug mode, background and detach
  if (!oCmd.DebugMode())
  {
    Daemonize();
  }

  //! initialize the application
  CliApp *poCliApp = CliApp::Instance(oCmd);

  //! start the client application
  int i32Result = poCliApp->Run();
  CliApp::Destroy();

  return i32Result;
}

void Daemonize (void)
{
  int32_t i32Res;

  /** change cwd to "/" so that we do not prevent any partitions from being 
   * unmounted
   */
  i32Res = chdir("/");
  if (-1 == i32Res)
  {
    cerr << "chdir failed" << endl;
  }

  /* this gives explicit control over the mask of any created files
   * (not neccesary for us because we don't create any file ... we may later)
   */
  i32Res = umask(0);
  // umask always succeeds

  // dup "/dev/null" on stdin, stdout, stderr
  int32_t i32NullDesc = open ("/dev/null", O_RDWR);
  if (-1 == i32NullDesc)
  {
    cerr << "could not open /dev/null" << endl;
    exit (-1);
  }

  i32Res = dup2(i32NullDesc, 0);
  if (-1 == i32Res)
  {
    cerr << "dup2(0) failed" << endl;
  }

  i32Res = dup2(i32NullDesc, 1);
  if (-1 == i32Res)
  {
    cerr << "dup2(1) failed" << endl;
  }

  //! return control to the command line
  switch (fork())
  {
    case FORK_ERROR: 
      cerr << "fork failed" << endl;
      exit(-1);
      break;

    case FORK_CHILD:
      //! proceed further
      break;

    default:
      //! exit the parent
      exit(0);
      break;
  }

  //! form a new process group
  i32Res = setsid();
  if (-1 == i32Res)
  {
    cerr << "setsid failed" << endl;
    exit(-1);
  }

  //! let the session leader exit
  switch (fork())
  {
    case FORK_ERROR: 
      cerr << "fork failed" << endl;
      exit(-1);
      break;

    case FORK_CHILD:
      // proceed further
      break;

    default:
      // exit the parent
      exit(0);
      break;
  }

  i32Res = dup2(i32NullDesc, 2);
}
