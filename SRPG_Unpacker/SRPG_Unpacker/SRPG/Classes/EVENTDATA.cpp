/*
 *  File: EVENTDATA.cpp
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

#include "EVENTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

EVENTDATA::~EVENTDATA()
{
	delete this_10;
	delete this_11;
	delete this_12;
	delete this_13;
	delete this_16;
	delete this_17;
	delete this_18;
	delete pPages;
}

void EVENTDATA::print(std::ostream& os) const
{
	os << "EVENTDATA" << std::endl;
	LEGENDDATA::print(os);
	os << std::endl;
	os << "this_8: " << this_8 << std::endl;
	os << "this_9: " << std::endl
	   << this_9 << std::endl;
	os << "this_10: " << this_10 << std::endl;
	os << "this_11: " << this_11 << std::endl;
	os << "this_12: " << this_12 << std::endl;
	os << "this_13: " << this_13 << std::endl;
	os << "this_14: " << this_14 << std::endl;
	os << "this_15: " << std::endl
	   << this_15 << std::endl;
	os << "this_16: " << this_16 << std::endl;
	os << "this_17: " << this_17 << std::endl;
	os << "this_18: " << this_18 << std::endl;
	os << "pages: " << *pPages << std::endl;
	os << "this_20: " << this_20 << std::endl;
	os << "this_21: " << this_21 << std::endl;
	os << "this_22: " << this_22 << std::endl;
	os << "this_23: " << this_23 << std::endl;
}

void EVENTDATA::init(FileReader& fw)
{
	this_8  = fw.ReadDWord();
	this_23 = fw.ReadDWord();

	if (this_8)
	{
		switch (this_8)
		{
			case 1:
				// Alloc 1 byte
				this_10 = operator new(1u);
				break;
			case 2:
				// Alloc 0x10 byte
				this_11 = operator new(0x10u);
				break;
			case 4:
				// Alloc 1 byte
				this_12 = operator new(1u);
				break;
			case 5:
				// Alloc 1 byte
				this_13 = operator new(1u);
				break;
			case 6:
				// Alloc 4 byte
				this_14 = 0;
				break;
			case 3:
				this_15 = ELEM_15();
				break;
			case 7:
				// Alloc 0x20 byte
				this_16 = operator new(0x20u);
				break;
			case 9:
				// Alloc 0x1C byte
				this_17 = operator new(0x1Cu);
				break;
			case 12:
				// Alloc 0x18 byte
				this_18 = operator new(0x18u);
				break;
		}
	}
	else
		this_9 = PlaceEvent();

	if (this_8)
	{
		if (this_8 != 1)
		{
			if (this_8 == 2)
			{
				DWORD* pD = reinterpret_cast<DWORD*>(this_11);
				pD[0]     = fw.ReadDWord();

				pD[1] = fw.ReadDWord();

				if (g_ArcVersion >= 0x3F7)
					pD[2] = fw.ReadDWord();

				if (g_ArcVersion >= 0x42D)
					pD[3] = fw.ReadDWord();
			}
			else if (this_8 != 4 && this_8 != 5)
			{
				switch (this_8)
				{
					case 6:
						this_14 = fw.ReadDWord();

						break;
					case 3:
					{
						this_15.this_1 = fw.ReadDWord();

						this_15.this_2 = fw.ReadDWord();

						if (g_ArcVersion >= 0x3F6)
							initMemData(this_15.command, fw);

						if (g_ArcVersion >= 0x469)
							initMemData(this_15.commandMsg, fw);
						break;
					}
					case 7:
						if (g_ArcVersion < 0x406)
						{
							DWORD* pD = reinterpret_cast<DWORD*>(this_16);
							pD[0]     = fw.ReadDWord();
							pD[1]     = fw.ReadDWord();
							pD[2]     = fw.ReadDWord();
							pD[3]     = fw.ReadDWord();
							pD[4]     = fw.ReadDWord();
							pD[5]     = fw.ReadDWord();
						}
						else
							fw.ReadBytes(this_16, 0x20);

						break;
					case 9:
						if (g_ArcVersion < 0x455)
						{
							QWORD* pD = reinterpret_cast<QWORD*>(this_17);
							pD[0]     = fw.ReadQWord();
						}
						else
							fw.ReadBytes(this_17, 0x1C);

						break;
					case 12:
						sub_FD4620(fw);
						break;
				}
			}
		}
	}
	else
	{
		this_9.x                 = fw.ReadDWord();
		this_9.y                 = fw.ReadDWord();
		this_9.locationEventType = fw.ReadDWord();
		this_9.itemDropsSw       = fw.ReadDWord();
		this_9.dropItem          = fw.ReadDWord();
		this_9.dropGold          = fw.ReadDWord();
		this_9.dropBonus         = fw.ReadDWord();
		this_9.this_7            = fw.ReadDWord();

		if (g_ArcVersion < 1028)
			fw.ReadArr(old_0);
		else
			this_9.shopData.init(fw);

		this_9.changeChips = fw.ReadQWord();
		this_9.this_10     = fw.ReadDWord();

		initMemData(this_9.this_11, fw);

		if (g_ArcVersion >= 0x3F7)
		{
			this_9.this_12 = fw.ReadDWord();
			this_9.this_13 = fw.ReadDWord();
		}

		if (g_ArcVersion >= 0x4D2)
		{
			this_9.this_22 = fw.ReadDWord();
			this_9.this_23 = fw.ReadDWord();
			this_9.this_24 = fw.ReadDWord();
		}
	}

	this_20 = fw.ReadDWord();
	this_21 = fw.ReadDWord();

	allocAndSetCMenuOp(&pPages, SRPGClasses::EVENTPAGE, fw);

	initMemData(this_22, fw);

	LEGENDDATA::init(fw);
}

void EVENTDATA::dump(FileWriter& fw) const
{
	fw.Write(this_8);
	fw.Write(this_23);

	if (this_8)
	{
		if (this_8 != 1)
		{
			if (this_8 == 2)
			{
				DWORD* pD = reinterpret_cast<DWORD*>(this_11);
				fw.Write(pD[0]);
				fw.Write(pD[1]);

				if (g_ArcVersion >= 0x3F7)
					fw.Write(pD[2]);

				if (g_ArcVersion >= 0x42D)
					fw.Write(pD[3]);
			}
			else if (this_8 != 4 && this_8 != 5)
			{
				switch (this_8)
				{
					case 6:
						fw.Write(this_14);

						break;
					case 3:
					{
						fw.Write(this_15.this_1);
						fw.Write(this_15.this_2);

						if (g_ArcVersion >= 0x3F6)
							this_15.command.Write(fw);

						if (g_ArcVersion >= 0x469)
							this_15.commandMsg.Write(fw);
						break;
					}
					case 7:
						if (g_ArcVersion < 0x406)
						{
							DWORD* pD = reinterpret_cast<DWORD*>(this_16);
							fw.Write(pD[0]);
							fw.Write(pD[1]);
							fw.Write(pD[2]);
							fw.Write(pD[3]);
							fw.Write(pD[4]);
							fw.Write(pD[5]);
						}
						else
							fw.WriteBytes(this_16, 0x20);

						break;
					case 9:
						if (g_ArcVersion < 0x455)
						{
							QWORD* pD = reinterpret_cast<QWORD*>(this_17);
							fw.Write(pD[0]);
						}
						else
							fw.WriteBytes(this_17, 0x1C);

						break;
					case 12:
						if (res == -1)
							fw.Write(res);
						else
						{
							QWORD* pD = reinterpret_cast<QWORD*>(this_18);
							fw.Write(pD[0]);
							fw.Write(pD[1]);
							fw.Write(pD[2]);
						}

						break;
				}
			}
		}
	}
	else
	{
		fw.Write(this_9.x);
		fw.Write(this_9.y);
		fw.Write(this_9.locationEventType);
		fw.Write(this_9.itemDropsSw);
		fw.Write(this_9.dropItem);
		fw.Write(this_9.dropGold);
		fw.Write(this_9.dropBonus);
		fw.Write(this_9.this_7);

		if (g_ArcVersion < 1028)
			fw.WriteArr(old_0);
		else
			this_9.shopData.dump(fw);

		fw.Write(this_9.changeChips);
		fw.Write(this_9.this_10);

		this_9.this_11.Write(fw);

		if (g_ArcVersion >= 0x3F7)
		{
			fw.Write(this_9.this_12);
			fw.Write(this_9.this_13);
		}

		if (g_ArcVersion >= 0x4D2)
		{
			fw.Write(this_9.this_22);
			fw.Write(this_9.this_23);
			fw.Write(this_9.this_24);
		}
	}

	fw.Write(this_20);
	fw.Write(this_21);

	pPages->Dump(fw);

	this_22.Write(fw);

	LEGENDDATA::dump(fw);
}

void EVENTDATA::sub_FD4620(FileReader& fw)
{
	res = fw.ReadDWord();
	if (res != -1)
	{
		fw.Seek(fw.GetOffset() - 4);
		QWORD* pD = reinterpret_cast<QWORD*>(this_18);
		pD[0]     = fw.ReadQWord();
		pD[1]     = fw.ReadQWord();
		pD[2]     = fw.ReadQWord();
	}
}

nlohmann::ordered_json EVENTDATA::toJson() const
{
	nlohmann::ordered_json j = EDITDATA::toJson();

	j["command"]    = this_15.command.ToString();
	j["commandMsg"] = this_15.commandMsg.ToString();

	pPages->ToJson(j, "pages");

	// If there is no command[Msg] or actual page data skip the entire event
	if ((j["command"].empty() && j["commandMSg"].empty()) && (!j.contains("pages") || j["pages"].empty()))
		j.clear();

	return j;
}

void EVENTDATA::applyPatch(const nlohmann::ordered_json& json)
{
	EDITDATA::applyPatch(json);
	SET_STRING_IF_IN_JSON(json, "command", this_15.command);
	SET_STRING_IF_IN_JSON(json, "commandMsg", this_15.commandMsg);
	APPLY_PATCH_IF_IN_JSON(json, "pages", pPages);
}
