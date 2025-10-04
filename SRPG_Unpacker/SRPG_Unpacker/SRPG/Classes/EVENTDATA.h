/*
 *  File: EVENTDATA.h
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

#pragma once

#include "EDITDATA.h"
#include "LEGENDDATA.h"
#include "SHOPDATA.h"

struct EVENTDATA : public EDITDATA, public LEGENDDATA
{
	~EVENTDATA();

	struct ELEM_15
	{
		DWORD this_1 = 0;
		DWORD this_2 = 0;
		MemData this_3;
		MemData this_4;
		friend std::ostream& operator<<(std::ostream& os, ELEM_15 const& elem)
		{
			os << "ELEM_15: " << std::endl;
			os << "this_1: " << elem.this_1 << std::endl;
			os << "this_2: " << elem.this_2 << std::endl;
			os << "this_3: " << elem.this_3 << std::endl;
			os << "this_4: " << elem.this_4 << std::endl;
			return os;
		}
	};

	struct PlaceEvent
	{
		DWORD x                 = 0;
		DWORD y                 = 0;
		DWORD locationEventType = 0;
		DWORD itemDropsSw       = 0;
		DWORD dropItem          = 0;
		DWORD dropGold          = 0;
		DWORD dropBonus         = 0;
		DWORD this_7            = 0;
		QWORD changeChips       = 0;
		DWORD this_10           = 0;
		MemData this_11;
		DWORD this_12 = 0;
		DWORD this_13 = 0;
		SHOPDATA shopData;
		DWORD this_22 = 0;
		DWORD this_23 = 0;
		DWORD this_24 = 0;

		friend std::ostream& operator<<(std::ostream& os, PlaceEvent const& elem)
		{
			os << "x: " << elem.x << std::endl;
			os << "y: " << elem.y << std::endl;
			os << "Local Event Type: " << elem.locationEventType << std::endl;
			os << "Item Drops Switches: " << elem.itemDropsSw << std::endl;
			os << "Drop Item: " << elem.dropItem << std::endl;
			os << "Drop Gold: " << elem.dropGold << std::endl;
			os << "Drop Bonus: " << elem.dropBonus << std::endl;
			os << "this_7: " << elem.this_7 << std::endl;
			os << "Change Chips: " << elem.changeChips << std::endl;
			os << "this_10: " << elem.this_10 << std::endl;
			os << "this_11: " << elem.this_11 << std::endl;
			os << "this_12: " << elem.this_12 << std::endl;
			os << "this_13: " << elem.this_13 << std::endl;
			os << "shopData: " << elem.shopData << std::endl;
			return os;
		}
	};

	virtual void print(std::ostream& os) const;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	void sub_FD4620(FileReader& fw);
	DWORD res    = 0;
	DWORD this_8 = 0;
	PlaceEvent this_9; // Does not look like it contains anything that is relevant for translation
	LPVOID this_10 = nullptr;
	LPVOID this_11 = nullptr;
	LPVOID this_12 = nullptr;
	LPVOID this_13 = nullptr;
	DWORD this_14  = 0;
	ELEM_15 this_15;
	LPVOID this_16 = nullptr;
	LPVOID this_17 = nullptr;
	LPVOID this_18 = nullptr;

	class CMenuOperation* pPages = nullptr;

	DWORD this_20 = 0;
	DWORD this_21 = 0;
	MemData this_22;
	DWORD this_23 = 0;

protected:
	virtual nlohmann::ordered_json toJson() const override;
};
