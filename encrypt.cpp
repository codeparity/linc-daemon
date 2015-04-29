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
 */

/* The encryption functions are based on the original code by Rahul Mittal.
 * Rahul Mittal reverse engineered Cyberoam's encryption algorithm.
 *
 * The original code and copyright is reproduced here:
 */

// ----- Rahul Mittal's code -----
/*
    Copyright 2002 Rahul Mittal

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 
USA
*/

/*
char* Encrypt(char* sPlaintext, int nLength) {
    assert (nLength <= 8); // Max length of plaintext password
    char* sTimestamp = new char[10];
    char* sCiphertext = new char[10 + 3*nLength]; // holds ciphertext
    int n1 = 0, n2 = 0;

    // Generate time stamp
    sprintf(sTimestamp, "%010d", time()); // get and store timestamp
    strncpy(sCiphertext, sTimestamp, 10);

    // Generate ciphertext
    for (int i = 0; i < nLength; i++) {
        char c = sPlaintext[i];
        short nScramble = ScrambleTimestamp(sTimestamp, n1, n2);
        for (int j = 0; j < 10; j++)
            sTimestamp[j] ^= c;
        int n = (nScramble & 0xFF) ^ c ^ (nScramble >> 8);
        sprintf(sCiphertext + 10 + (i*3), "%03d", n);
    }

    return sCiphertext;
}

short ScrambleTimestamp(char* sTimestamp, int& nCurrent, int& nPrevious) {
    // nCurrent == BP+0x10
    int nScramble = 0;
    int nIter = 0; // BP+0x1E
    int i;
    int nTemp1; // BP+0x04
    int nTemp2 = 0; // BP+0x12
    int nFinal = 0; // BP+0x20

    while (nIter < 5) {
        i = nIter * 2;
        nScramble = nTemp2 ^ ((sTimestamp[i] << 8) | sTimestamp[i+1]);
        nTemp1 = (nCurrent + nIter) * 0x4E35;
        nCurrent = nPrevious + (nScramble * 0x015A) + nTemp1; // BP+0x0A
        nPrevious = nScramble * 0x015A;
        nTemp2 = nScramble * 0x4E35 + 1;
        nScramble = nCurrent ^ nTemp2;
        nFinal ^= nScramble;
        ++nIter;
    }

    return static_cast(nFinal & 0xFFFF);
}
*/
// ----- Rahul Mittal's code -----
// Also available online at:
// http://mittal.sentris.com/software/slyberoam/sourcecode.asp

/* encrypt.cpp */

#include <encrypt.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

using std::ostringstream;
using std::setw;
using std::setfill;
typedef uint16_t u_int16_t;
typedef int u_int32_t;
#define TS_STRLEN 10

//! scramble the timestamp
u_int16_t ScrambleTimestamp(const string& oStrTimeStamp,
    u_int32_t& rui32Current, u_int32_t& rui32Previous);

string Encrypt(const string& rkoStrPlaintext, time_t tTime)
{
  // Generate the time stamp string
  ostringstream oSrmTS;
  oSrmTS << setw(TS_STRLEN) << setfill('0') << tTime;
  string oStrTimeStamp = oSrmTS.str();

  ostringstream oSrmCiphertext; // holds ciphertext
  oSrmCiphertext << oStrTimeStamp;
  
  // Generate ciphertext
  u_int32_t ui32N1=0, ui32N2=0;
  for (int i = 0; i < rkoStrPlaintext.size(); i++) 
  { 
    // the ith plaintext password character
    char cCh = rkoStrPlaintext[i];

    // call the scramble routine for the ith time
    u_int16_t ui16Scramble = ScrambleTimestamp(oStrTimeStamp, ui32N1, ui32N2);

    // XOR each timestamp character with the password character
    for (int j = 0; j < TS_STRLEN; j++) 
    { 
      oStrTimeStamp[j] ^= cCh; 
    }

    /* transform the encrypted character
     * the encrypted character is an XOR of the char, the high order
     * scramble byte and the lower order scramble byte
     */
    u_int16_t ui16Enc = cCh ^ (ui16Scramble & 0xFF) ^ (ui16Scramble >> 8);

    // write the encrypted character as its byte value
    oSrmCiphertext << setw(3) << setfill('0') << ui16Enc;
  }

  return oSrmCiphertext.str();
}

u_int16_t ScrambleTimestamp(const string& oStrTimeStamp,
    u_int32_t& rui32N1, u_int32_t& rui32N2)
{
  u_int32_t ui32N3 = 0;
  u_int32_t ui32Final = 0;

  for(u_int32_t ui32Iter = 0; ui32Iter < TS_STRLEN/2; ui32Iter++)
  {
    /* the scrambled text is the XOR of ui32N3 and the ui32Iter'th
     * pair of bytes taken together as a u_int16_t value
     */
    u_int32_t ui32Scramble = ui32N3 ^ 
      ((oStrTimeStamp[ui32Iter*2] << 8) | oStrTimeStamp[ui32Iter*2+1]);

    /* I don't pretend to understand the remainder of this compound statement */
    rui32N1 = rui32N2 + (rui32N1 + ui32Iter) * 0x4E35;
    rui32N2 = ui32Scramble * 0x015A;
    rui32N1 += rui32N2;
    ui32N3 = ui32Scramble * 0x4E35 + 1;

    ui32Final ^= rui32N1 ^ ui32N3;
  }

  return static_cast<u_int16_t> (ui32Final & 0xFFFF);
}
/*
 *  This source file is part of linc $Name: rel-1-2 $
 *  
 *  $Log: encrypt.cpp,v $
 *  Revision 1.1  2003/04/05 05:12:37  mrnk
 *  Fixed version and help strings. Added support for cleartext passwords based on Rahul Mittal's code.
 *
 */
