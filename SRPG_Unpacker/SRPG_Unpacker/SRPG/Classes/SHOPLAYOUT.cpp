/*
 *  File: SHOPLAYOUT.cpp
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

#include "SHOPLAYOUT.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void SHOPLAYOUT::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();

	m_interOpScreenData.init(fw);

	for (MemData& ph : shopMessages)
		initMemData(ph, fw);

	if (g_ArcVersion >= 0x43D)
		this_19 = fw.ReadDWord();
}

void SHOPLAYOUT::dump(FileWriter& fw) const
{
	fw.Write(this_4);
	fw.Write(this_5);

	m_interOpScreenData.dump(fw);

	for (const MemData& ph : shopMessages)
		ph.Write(fw);

	if (g_ArcVersion >= 0x43D)
		fw.Write(this_19);
}

nlohmann::ordered_json SHOPLAYOUT::toJson() const
{
	nlohmann::ordered_json j = EDITDATA::toJson();

	j["name"] = m_interOpScreenData.gameName.ToString();
	j["msg"]  = nlohmann::ordered_json::array();

	for (const MemData& msg : shopMessages)
		j["msg"].push_back(msg.ToString());

	return j;
}

void SHOPLAYOUT::applyPatch(const nlohmann::ordered_json& json)
{
	EDITDATA::applyPatch(json);
	SET_STRING_IF_IN_JSON(json, "name", m_interOpScreenData.gameName);

	if (json.contains("msg") && json["msg"].is_array())
	{
		for (std::size_t i = 0; i < shopMessages.size(); i++)
		{
			if (i < json["msg"].size() && json["msg"][i].is_string())
				shopMessages[i] = json["msg"][i].get<std::string>();
		}
	}
}
