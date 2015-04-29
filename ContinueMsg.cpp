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
 *  $Log: ContinueMsg.cpp,v $
 *  Revision 1.3  2003/04/01 08:47:32  mrnk
 *  Fixed code to work with gcc3.
 *
 *  Revision 1.2  2002/06/19 11:59:49  mrnk
 *  Added CVS keywords to all source files
 *
 */

#include <ContinueMsg.h>
#include <sstream>
 
ContinueMsg::ContinueMsg (string ostrName) 
: Msg (CONTINUE, c_kui32ContinueMsgLen)
{
	ostringstream oNameField;
	oNameField << ostrName;
	SetPayload(oNameField.str());
}

ContinueMsg::ContinueMsg(const Msg& rkoMsg) : Msg(rkoMsg)
{
	if (rkoMsg.Length() != c_kui32ContinueMsgLen)
		throw InvalidMsgException("invalid Msg length");
}

