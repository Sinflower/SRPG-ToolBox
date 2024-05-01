/*
 *  File: SUPPORTDATA.cpp
 *  Copyright (c) 2024 Sinflower
 *
 *  MIT License
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

// Compatible up to v1.292

#include "SUPPORTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SUPPORTDATA::init(FileReader& fw)
{
	this_3  = fw.ReadDWord();
	this_5  = fw.ReadDWord();
	this_6  = fw.ReadDWord();
	this_7  = fw.ReadDWord();
	this_8  = fw.ReadDWord();
	this_9  = fw.ReadDWord();
	this_10 = fw.ReadDWord();

	if (g_ArcVersion >= 1260)
		this_11 = fw.ReadDWord();

	allocAndSetCMenuOp(&this_4, SRPGClasses::TYPEIDDATA, fw);

	if (g_ArcVersion >= 1230)
		allocAndSetCMenuOp(&this_12, SRPGClasses::VARIABLECONDITIONDATA, fw);
	else
	{
		NOT_IMPLEMENTED
		/*
		  v4 = a2[1];
	  v10 = (int *)(*a2 + v4);
	  v5 = *v10;
	  result = v4 + 4;
	  a2[1] = v4 + 4;
	  if ( v5 )
	  {
		a2[1] = v4;
		v6 = *(__m128i *)v10;
		v7 = *((_QWORD *)v10 + 6);
		v8 = (__m128d)*((_OWORD *)v10 + 1);
		v9 = (__m128d)*((_OWORD *)v10 + 2);
		v11[1] = 0;
		v11[3] = _mm_cvtsi128_si32(_mm_srli_si128(v6, 4));
		v12 = __PAIR64__(LODWORD(v8.m128d_f64[0]), v6.m128i_u32[3]);
		a2[1] = v4 + 56;
		v18 = v7;
		v13 = _mm_cvtsi128_si32(_mm_srli_si128((__m128i)v8, 4));
		v15 = _mm_cvtsi128_si32((__m128i)v9);
		v11[2] = 0;
		v11[0] = (int)&VARIABLECONDITIONDATA::`vftable';
		v11[4] = _mm_cvtsi128_si32(_mm_srli_si128(v6, 8));
		v14 = *(_OWORD *)&_mm_unpackhi_pd(v8, v8);
		v16 = _mm_cvtsi128_si32(_mm_srli_si128((__m128i)v9, 4));
		v17 = *(_OWORD *)&_mm_unpackhi_pd(v9, v9);
		result = sub_562310(v11);
	  }
		*/
	}
}

void SUPPORTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);
	fw.Write(this_9);
	fw.Write(this_10);

	if (g_ArcVersion >= 1260)
		fw.Write(this_11);

	this_4->dump(fw);
	// TODO: Implement case for Ver >= 1230
	this_12->dump(fw);
}
