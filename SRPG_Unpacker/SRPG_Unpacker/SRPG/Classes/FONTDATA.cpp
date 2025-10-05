/*
 *  File: FONTDATA.cpp
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

#include "FONTDATA.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void FONTDATA::init(FileReader& fw)
{
	fontSize = fw.ReadDWord();
	this_6   = fw.ReadDWord();
	this_7   = fw.ReadDWord();
	this_9   = fw.ReadDWord();

	if (g_ArcVersion < 0x487)
		this_10 = 0;
	else
		this_10 = fw.ReadDWord();

	initMemData(name, fw);
	initMemData(fontName, fw);
}

void FONTDATA::dump(FileWriter& fw) const
{
	fw.Write(fontSize);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_9);

	if (g_ArcVersion >= 0x487)
		fw.Write(this_10);

	name.Write(fw);
	fontName.Write(fw);
}

nlohmann::ordered_json FONTDATA::toJson() const
{
	nlohmann::ordered_json j = EDITDATA::toJson();

	j["name"]     = name.ToString();
	j["fontName"] = fontName.ToString();
	j["fontSize"] = fontSize;
	return j;
}
