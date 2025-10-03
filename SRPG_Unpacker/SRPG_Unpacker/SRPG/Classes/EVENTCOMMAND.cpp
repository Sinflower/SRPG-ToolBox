/*
 *  File: EVENTCOMMAND.cpp
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

#include "EVENTCOMMAND.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void EVENTCOMMAND::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	res    = fw.ReadDWord();

	if (HIWORD(res) == 1)
		initMemData(comment, fw);

	this_4 = static_cast<WORD>(res);
	this_5 = fw.ReadDWord();

	if (this_5)
		this_6.init(fw);

	pCommand     = createCommand(this_3);
	pCommand->id = fw.ReadDWord();
	pCommand->init(fw);
}

void EVENTCOMMAND::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(res);

	if (HIWORD(res) == 1)
		comment.Write(fw);

	fw.Write(this_5);

	if (this_5)
		this_6.dump(fw);

	fw.Write(pCommand->id);
	pCommand->dump(fw);
}

void EVENTCOMMAND::print(std::ostream& os) const
{
	os << "EVENTCOMMAND" << std::endl;
	os << "this_3: " << this_3 << std::endl;
	os << "this_4: " << this_4 << std::endl;
	os << "this_5: " << this_5 << std::endl; // Maybe trigger present
	os << "this_6: " << this_6 << std::endl;
	// os << "pCommand: " << *pCommand << std::endl;
	os << "Comment: " << comment << std::endl;
}

nlohmann::ordered_json EVENTCOMMAND::toJson() const
{
	nlohmann::ordered_json j;
	nlohmann::ordered_json command = pCommand->ToJson();

	// If the command is empty return empty json
	if (command.is_null() || command.empty())
		return j;

	j["comment"] = comment.ToString();
	j["command"] = command;
	return j;
}