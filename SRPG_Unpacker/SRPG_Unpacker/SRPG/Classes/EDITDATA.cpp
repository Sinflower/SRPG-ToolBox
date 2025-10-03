/*
 *  File: EDITDATA.cpp
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

#include "EDITDATA.h"
#include "../CMenuOperation.h"

EDITDATA::EDITDATA()
{
}

EDITDATA::~EDITDATA()
{
}

std::string EDITDATA::name() const
{
	return typeid(*this).name();
}

std::wstring EDITDATA::wname() const
{
	return s2ws(std::string(typeid(*this).name()));
}

void EDITDATA::init(FileReader& fw)
{
	std::cerr << __FUNCSIG__ << " - IMPLEMENT ME - " << name() << std::endl;
	exit(-1);
}

void EDITDATA::dump(FileWriter& fw) const
{
	std::cerr << __FUNCSIG__ << " - IMPLEMENT ME - " << name() << std::endl;
	exit(-1);
}

void EDITDATA::print(std::ostream& os) const
{
	os << "Printing of " << name() << " currently not implemented";
}

void EDITDATA::print(std::wostream& os) const
{
	os << L"Printing of " << wname() << L" currently not implemented";
}

nlohmann::ordered_json EDITDATA::ToJson() const
{
	nlohmann::ordered_json j;
	const nlohmann::ordered_json data = toJson();

	if (data.empty())
		return j;

	j["id"]   = id;
	j["type"] = name();
	j["data"] = data;
	return j;
}
