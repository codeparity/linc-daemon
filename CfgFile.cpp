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
 *  $Log: CfgFile.cpp,v $
 *  Revision 1.5  2003/04/01 08:47:32  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.4  2002/12/17 17:46:34  mrnk
 *  dup()ing on fd 0,1,2 instead of closing.
 *
 *  Revision 1.3  2002/06/22 10:49:01  mrnk
 *  Documented configuration related classes
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#include <CfgFile.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

//! constructor
CfgFile::CfgFile (string ostrFileName)
{
	m_ostrFileName = ostrFileName;
	Read(m_ostrFileName);
}

//! get parameter by key
const string& CfgFile::GetParam(const string& rkostrKey) const
{
	map<string, string>::const_iterator oIter = m_oMapParams.find(rkostrKey);
	if (oIter == m_oMapParams.end())
  {
		throw CfgErr(m_ostrFileName,  "no param '" + rkostrKey + "' in file");
  }
	else
  {
		return oIter->second;
  }
}

//! set a parameter
void CfgFile::SetParam(const string& rkostrKey, const string& rkostrValue)
{
	m_oMapParams[rkostrKey] = rkostrValue;
}

//! read and parse a configuration file
void CfgFile::Read (string ostrFileName)
{
	if ( ostrFileName == "" )
		ostrFileName = m_ostrFileName;
	
	ifstream oInfile(ostrFileName.c_str());
	if (!oInfile)
		throw CfgErr (ostrFileName, "could not open file for reading");

	//! state machine for parsing
	while (oInfile)
	{
		char pcBuf[1024];
		oInfile.getline(pcBuf, 1024, '\n');

		if (!oInfile)
			break;
		
		if (pcBuf[0] == '#' || pcBuf[0] == '\0')
		{
			continue;
		}

		string ostrInput(pcBuf);
		string ostrKey, ostrValue;
		enum POS_en
		{
			POSBEF,
			POSKEY,
			POSBET,
			POSVAL,
			POSAFT,
		};
		POS_en enPos = POSBEF;
		for (int i = 0; 
				(i < ostrInput.length())&&(enPos != POSAFT);
				i++)
			switch (enPos)
			{
				case POSBEF:
					if ((ostrInput[i] == ' ' ) 
							|| (ostrInput[i] 
								== '\t'))
						;
					else
					{
						ostrKey += ostrInput[i];
						enPos = POSKEY;
					}
					break;
					
				case POSKEY:
					if ((ostrInput[i] == ' ' )
							|| (ostrInput[i] 
								== '\t')
							|| (ostrInput[i] 
								== '='))
					{
						enPos = POSBET;
					}
					else
						ostrKey += ostrInput[i];
					break;
					
				case POSBET:
					if ((ostrInput[i] == ' ' )
							|| (ostrInput[i] 
								== '\t')
							|| (ostrInput[i] 
								== '='))
						;
					else
					{
						ostrValue += ostrInput[i];
						enPos = POSVAL;
					}
					break;

				case POSVAL:
					if ((ostrInput[i] == ' ' )
							|| (ostrInput[i] 
								== '\t')
							|| (ostrInput[i] 
								== '#'))
					{
						enPos = POSAFT;
					}
					else
						ostrValue += ostrInput[i];
					break;
			}
		m_oMapParams[ostrKey] = ostrValue;
		
	}
}

//! write the file out
void CfgFile::Write (string ostrFileName)
{
	if ( ostrFileName == "" )
		ostrFileName = m_ostrFileName;
	
	ofstream oOutfile(ostrFileName.c_str());
	if (!oOutfile)
		throw CfgErr(ostrFileName, "could not open file for writing");

	for (map<string,string>::iterator oIter=m_oMapParams.begin();
			oIter!=m_oMapParams.end(); oIter++)
	{
		oOutfile << oIter->first << " = " << oIter->second << endl;
	}
}
