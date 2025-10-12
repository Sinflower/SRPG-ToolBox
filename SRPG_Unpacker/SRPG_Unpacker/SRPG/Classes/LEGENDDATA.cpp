/*
 *  File: LEGENDDATA.cpp
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

#include "LEGENDDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void LEGENDDATA::init(FileReader& fw)
{
	icon = fw.ReadQWord();
	initMemData(name, fw);
	initMemData(description, fw);
}

void LEGENDDATA::dump(FileWriter& fw) const
{
	fw.Write(icon);
	name.Write(fw);
	description.Write(fw);
}

void LEGENDDATA::print(std::ostream& os) const
{
	os << "Icon: " << icon << std::endl
	   << "Name: " << name << std::endl
	   << "Description: " << description;
}

nlohmann::ordered_json LEGENDDATA::toJson() const
{
	nlohmann::ordered_json j = EDITDATA::toJson();
	j["name"]                = name.ToString();
	j["desc"]                = description.ToString();
	return j;
}

void LEGENDDATA::applyPatch(const nlohmann::ordered_json& json)
{
	EDITDATA::applyPatch(json);
	SET_STRING_IF_IN_JSON(json, "name", name);
	SET_STRING_IF_IN_JSON(json, "desc", description);
}
