/*
 *  File: STRINGDATA.cpp
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

#include "STRINGDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void STRINGDATA::init(FileReader& fw)
{
	initMemData(data, fw);
}

void STRINGDATA::dump(FileWriter& fw) const
{
	data.Write(fw);
}

void STRINGDATA::print(std::ostream& os) const
{
	os << data;
}

nlohmann::ordered_json STRINGDATA::toJson() const
{
	return data.ToString();
}

void STRINGDATA::applyPatch(const nlohmann::ordered_json& json)
{
	if (json.is_string())
		data = json.get<std::string>();
	else
		throw std::runtime_error("STRINGDATA::applyPatch: JSON is not a string");
}
