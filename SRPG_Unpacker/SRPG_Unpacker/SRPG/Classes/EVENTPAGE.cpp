/*
 *  File: EVENTPAGE.cpp
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

#include "EVENTPAGE.h"
#include "../CMenuOperation.h"
#include "EDITDATA.h"

void EVENTPAGE::init(FileReader& fw)
{
	this_4 = fw.ReadDWord();

	if (this_4)
		this_5.init(fw);

	allocAndSetCMenuOp(&eventCommands, SRPGClasses::EVENTCOMMAND, fw);
}

void EVENTPAGE::dump(FileWriter& fw) const
{
	fw.Write(this_4);

	if (this_4)
		this_5.dump(fw);

	eventCommands->dump(fw);
}

void EVENTPAGE::print(std::ostream& os) const
{
	os << "EVENTPAGE" << std::endl;
	os << "this_4: " << this_4 << std::endl;
	os << "EventPage Data: " << this_5 << std::endl;
	os << "EventCommand: " << *eventCommands << std::endl;
}

nlohmann::ordered_json EVENTPAGE::toJson() const
{
	nlohmann::ordered_json j;

	eventCommands->ToJson(j, "EventCommand");
	return j;
}