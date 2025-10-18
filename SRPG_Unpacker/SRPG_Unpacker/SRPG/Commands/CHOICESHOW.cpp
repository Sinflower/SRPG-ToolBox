/*
 *  File: CHOICESHOW.cpp
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

#include "CHOICESHOW.h"
#include "../CMenuOperation.h"
#include "../Classes/CHOICEDATA.h"

void CHOICESHOW::init(FileReader& fw)
{
	if (g_ArcVersion < 1025)
	{
		old_0 = fw.ReadDWord();
		old_1 = fw.ReadDWord();
		old_2 = fw.ReadDWord();
		old_3 = fw.ReadDWord();
		for (auto& choice : old_choices)
			initMemData(choice, fw);
	}
	else
	{
		allocAndSetCMenuOp(&pChoices, SRPGClasses::CHOICEDATA, fw);
		this_4 = fw.ReadDWord();
	}
}

void CHOICESHOW::dump(FileWriter& fw) const
{
	if (g_ArcVersion < 1025)
	{
		fw.Write(old_0);
		fw.Write(old_1);
		fw.Write(old_2);
		fw.Write(old_3);
		for (const auto& choice : old_choices)
			choice.Write(fw);
	}
	else
	{
		pChoices->Dump(fw);
		fw.Write(this_4);
	}
}

nlohmann::ordered_json CHOICESHOW::toJson() const
{
	nlohmann::ordered_json j;
	nlohmann::json choices = nlohmann::json::array();

	if (g_ArcVersion < 1025)
	{
		for (const auto& choice : old_choices)
			choices.push_back(choice.ToString());
	}
	else
	{
		for (const auto* pObj : *pChoices)
		{
			const CHOICEDATA* pChoice = dynamic_cast<const CHOICEDATA*>(pObj);
			choices.push_back(pChoice->choice.ToString());
		}
	}

	j["type"] = "choice";
	j["data"] = choices;

	return j;
}

void CHOICESHOW::applyPatch(const nlohmann::ordered_json& json)
{
	if (json.contains("data") && json["data"].is_array())
	{
		auto& arr = json["data"];

		if (g_ArcVersion < 1025)
		{
			for (std::size_t i = 0; i < old_choices.size(); i++)
			{
				if (i >= arr.size())
					break;
				old_choices[i] = arr[i].get<std::string>();
			}
		}
		else
		{
			auto it   = arr.begin();
			for (auto* pObj : *pChoices)
			{
				if (it == arr.end())
					break;

				CHOICEDATA* pChoice = dynamic_cast<CHOICEDATA*>(pObj);
				pChoice->choice     = it->get<std::string>();
				++it;
			}
		}
	}
}
