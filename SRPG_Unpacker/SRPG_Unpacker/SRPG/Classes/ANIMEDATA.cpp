/*
 *  File: ANIMEDATA.cpp
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

// Compatible up to v1.317

#include "ANIMEDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void ANIMEDATA::init(FileReader& fw)
{
	allocAndSetCMenuOp(&m_pFrameList, SRPGClasses::FRAMELIST, fw);

	this_9  = fw.ReadWord();
	this_10 = fw.ReadDWord();
	this_11 = fw.ReadDWord();
	this_12 = fw.ReadDWord();

	this_20 = fw.ReadDWord();
	this_21 = fw.ReadDWord();

	sub_36EF00(fw);

	initMemData(this_13, fw);

	// if (g_ArcVersion < 0x49B)
	//	this_20 = 100;

	LEGENDDATA::init(fw);
}

void ANIMEDATA::dump(FileWriter& fw) const
{
	m_pFrameList->Dump(fw);
	fw.Write(this_9);
	fw.Write(this_10);
	fw.Write(this_11);
	fw.Write(this_12);
	fw.Write(this_20);
	fw.Write(this_21);

	if (g_ArcVersion >= 0x3F3)
		fw.Write(this_22);

	if (g_ArcVersion < 0x409)
	{
		NOT_IMPLEMENTED
	}

	fw.Write(this_15);
	fw.Write(this_16);
	fw.Write(this_17);

	m_pTypeIDData->Dump(fw);

	if (g_ArcVersion >= 0x40D)
		this_18.Write(fw);

	if (g_ArcVersion >= 0x411)
		fw.Write(this_19);

	this_13.Write(fw);

	LEGENDDATA::dump(fw);
}

void ANIMEDATA::sub_36EF00(FileReader& fw)
{
	if (g_ArcVersion < 0x3F3)
		this_22 = 0;
	else
		this_22 = fw.ReadDWord();

	if (g_ArcVersion < 0x409)
	{
		NOT_IMPLEMENTED
		/*
		if (this_20)
		{
			if (this_10 != 2 )
			{
				for ( i = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 32) + 4) + 4); i; i = *(_DWORD *)(i + 4) )
				{
					v5 = *(_DWORD *)(this + 56);
					v23 = (**(int (__thiscall ***)(int))v5)(v5);
					*(_DWORD *)(v23 + 8) = (__int16)sub_381340(v5);
					v6 = *(_DWORD *)(v5 + 4);
					v7 = v6 + 4;
					if ( *(_DWORD *)(v6 + 4) )
					{
						do
						{
							v6 = *(_DWORD *)v7;
							v8 = *(_DWORD *)(*(_DWORD *)v7 + 4) == 0;
							v7 = *(_DWORD *)v7 + 4;
						}
						while ( !v8 );
					}
					*(_DWORD *)(v6 + 4) = v23;
					*(_DWORD *)(v23 + 12) = *(unsigned __int16 *)(i + 20);
				}
			}
		}
		if (this_22)
		{
			if (this_10 != 2 )
			{
				for ( j = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 32) + 4) + 4); j; j = *(_DWORD *)(j + 4) )
				{
					v10 = *(_DWORD *)(j + 24);
					if ( v10 == 3 || v10 == 5 )
					{
						v11 = *(_DWORD *)(this + 56);
						v24 = (**(int (__thiscall ***)(int))v11)(v11);
						*(_DWORD *)(v24 + 8) = (__int16)sub_381340(v11);
						v12 = *(_DWORD *)(v11 + 4);
						v13 = v12 + 4;
						if ( *(_DWORD *)(v12 + 4) )
						{
							do
							{
								v12 = *(_DWORD *)v13;
								v8 = *(_DWORD *)(*(_DWORD *)v13 + 4) == 0;
								v13 = *(_DWORD *)v13 + 4;
							}
							while ( !v8 );
						}
						*(_DWORD *)(v12 + 4) = v24;
						*(_DWORD *)(v24 + 12) = *(unsigned __int16 *)(j + 20) | 0x10000;
					}
				}
			}
		}
		if ( this_21)
		{
			if (this_10 == 2 )
			{
				for ( k = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(this + 32) + 4) + 4); k; k = *(_DWORD *)(k + 4) )
				{
					if ( *(_DWORD *)(k + 24) == 6 )
					{
						v15 = *(_DWORD *)(this + 56);
						v25 = (**(int (__thiscall ***)(int))v15)(v15);
						*(_DWORD *)(v25 + 8) = (__int16)sub_381340(v15);
						v16 = *(_DWORD *)(v15 + 4);
						v17 = v16 + 4;
						if ( *(_DWORD *)(v16 + 4) )
						{
							do
							{
								v16 = *(_DWORD *)v17;
								v8 = *(_DWORD *)(*(_DWORD *)v17 + 4) == 0;
								v17 = *(_DWORD *)v17 + 4;
							}
							while ( !v8 );
						}
						*(_DWORD *)(v16 + 4) = v25;
						*(_DWORD *)(v25 + 12) = *(unsigned __int16 *)(k + 20) | 0x20000;
					}
				}
			}
		}
		*/
	}
	else
	{
		this_15 = fw.ReadDWord();
		this_16 = fw.ReadDWord();
		this_17 = fw.ReadDWord();

		allocAndSetCMenuOp(&m_pTypeIDData, SRPGClasses::TYPEIDDATA, fw);
	}

	if (g_ArcVersion >= 0x40D)
		initMemData(this_18, fw);

	if (g_ArcVersion < 0x411)
		this_19 = 1;
	else
		this_19 = fw.ReadDWord();
}
