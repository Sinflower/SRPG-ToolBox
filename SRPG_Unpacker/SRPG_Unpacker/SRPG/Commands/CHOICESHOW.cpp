/*
 *  File: CHOICESHOW.cpp
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

#include "CHOICESHOW.h"
#include "../CMenuOperation.h"

void CHOICESHOW::init(FileReader& fw)
{
	if (g_ArcVersion < 0x401)
	{
		NOT_IMPLEMENTED
		/*
		v4 = a1[1];
		v5 = *a1;
		*(_OWORD *)lpString = 0i64;
		v6 = *(_DWORD *)(v5 + v4);
		v4 += 4;
		a1[1] = v4;
		v25[0] = v6;
		v7 = *(_DWORD *)(v5 + v4);
		v4 += 4;
		a1[1] = v4;
		v25[1] = v7;
		v8 = *(_DWORD *)(v5 + v4);
		v4 += 4;
		a1[1] = v4;
		v25[2] = v8;
		v25[3] = *(_DWORD *)(v5 + v4);
		a1[1] = v4 + 4;
		initMemData(a1, (void **)lpString);
		initMemData(a1, (void **)&lpString[1]);
		initMemData(a1, (void **)&lpString[2]);
		result = initMemData(a1, (void **)&lpString[3]);
		v9 = 0;
		v24 = 0;
		do
		{
			v10 = *(WCHAR **)((char *)lpString + v9);
			if ( v10 )
			{
				v11 = (_DWORD *)this[3];
				v12 = (_DWORD *)(*(int (__thiscall **)(_DWORD *))*v11)(v11);
				v12[2] = sub_ED1340(v11);
				v13 = v11[1];
				v14 = v13 + 4;
				if ( *(_DWORD *)(v13 + 4) )
				{
					do
					{
						v13 = *(_DWORD *)v14;
						v15 = *(_DWORD *)(*(_DWORD *)v14 + 4) == 0;
						v14 = *(_DWORD *)v14 + 4;
					}
					while ( !v15 );
				}
				*(_DWORD *)(v13 + 4) = v12;
				v12[3] = 0;
				v16 = lstrlenW(v10);
				if ( v16 )
				{
					v21 = 2 * v16 + 2;
					v17 = GetProcessHeap();
					v18 = (WCHAR *)HeapAlloc(v17, 8u, v21);
					lstrcpyW(v18, v10);
					if ( v12[3] )
					{
						v22 = (void *)v12[3];
						v19 = GetProcessHeap();
						HeapFree(v19, 0, v22);
					}
					v12[3] = v18;
				}
				v9 = v24;
				v12[6] = 0;
				v12[7] = 0x20000;
				v12[4] = *(int *)((char *)v25 + v24);
				v20 = GetProcessHeap();
				result = HeapFree(v20, 0, v10);
			}
			v9 += 4;
			v24 = v9;
		}
		while ( v9 < 16 );
		*/
	}
	else
	{
		allocAndSetCMenuOp(&pChoiceData, SRPGClasses::CHOICEDATA, fw);
		this_4 = fw.ReadDWord();
	}
}

void CHOICESHOW::dump(FileWriter& fw) const
{
	if (g_ArcVersion < 0x401)
	{
		NOT_IMPLEMENTED
	}
	else
	{
		pChoiceData->dump(fw);
		fw.Write(this_4);
	}
}
