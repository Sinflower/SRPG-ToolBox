/*
 *  File: CHAPTERSHOW.cpp
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

#include "CHAPTERSHOW.h"
#include "../CMenuOperation.h"

void CHAPTERSHOW::init(FileReader& fw)
{
	useMapData = fw.ReadDWord();
	initMemData(chapterName, fw);
	initMemData(mapName, fw);
}

void CHAPTERSHOW::dump(FileWriter& fw) const
{
	fw.Write(useMapData);
	chapterName.Write(fw);
	mapName.Write(fw);
}

nlohmann::ordered_json CHAPTERSHOW::toJson() const
{
	nlohmann::ordered_json j;
	j["chapterName"] = chapterName.ToString();
	j["mapName"]     = mapName.ToString();
	return j;
}

void CHAPTERSHOW::applyPatch(const nlohmann::ordered_json& json)
{
	SET_STRING_IF_IN_JSON(json, "chapterName", chapterName);
	SET_STRING_IF_IN_JSON(json, "mapName", mapName);
}
