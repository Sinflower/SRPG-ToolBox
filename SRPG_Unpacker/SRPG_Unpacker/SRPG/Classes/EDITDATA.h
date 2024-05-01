/*
 *  File: EDITDATA.h
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

#include <Windows.h>
#include <array>
#include <fstream>
#include <vector>

#include <nlohmann\json.hpp>

#include "../../FileAccess.h"
#include "../../Utils.h"
#include "../Functions.h"
#include "../Version.h"

class EDITDATA
{
public:
	EDITDATA();
	virtual ~EDITDATA();
	std::string name() const;
	std::wstring wname() const;
	virtual void init(FileReader& fw);
	virtual void dump([[maybe_unused]] FileWriter& fw) const;
	virtual void print(std::ostream& os) const;
	virtual void print(std::wostream& os) const;
	nlohmann::ordered_json ToJson() const;

	friend std::ostream& operator<<(std::ostream& os, EDITDATA const& dt)
	{
		dt.print(os);
		return os;
	}

	friend std::wostream& operator<<(std::wostream& os, EDITDATA const& dt)
	{
		dt.print(os);
		return os;
	}

protected:
	virtual nlohmann::ordered_json toJson() const
	{
		return nlohmann::ordered_json();
	}

public:
	EDITDATA* pNext = nullptr;
	DWORD id        = 0;
};
