/*
 *  File: SectionNames.h
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

#include <string>
#include <vector>

static inline const std::vector<std::string> SECTION_NAMES = {
	"Graphics\\mapchip",
	"Graphics\\charchip",
	"Graphics\\face",
	"Graphics\\icon",
	"Graphics\\motion",
	"Graphics\\effect",
	"Graphics\\weapon",
	"Graphics\\bow",
	"Graphics\\thumbnail",
	"Graphics\\battleback",
	"Graphics\\eventback",
	"Graphics\\screenback",
	"Graphics\\worldmap",
	"Graphics\\eventstill",
	"Graphics\\charillust",
	"Graphics\\picture",
	"UI\\menuwindow",
	"UI\\textwindow",
	"UI\\title",
	"UI\\number",
	"UI\\bignumber",
	"UI\\gauge",
	"UI\\line",
	"UI\\risecursor",
	"UI\\mapcursor",
	"UI\\pagecursor",
	"UI\\selectcursor",
	"UI\\scrollcursor",
	"UI\\panel",
	"UI\\faceframe",
	"UI\\screenframe",
	"Audio\\music",
	"Audio\\sound",
	"Fonts",
	"Video",
	"Script",
	"Material"
};

static inline std::string GetSecNameFromPath(const std::string& path)
{
	std::string p = path;

	std::replace(p.begin(), p.end(), '/', '\\');

	// If the path ends with a backslash, remove it
	if (p.back() == '\\')
		p.pop_back();

	// Check if the path ends with one of the section names
	for (const auto& secName : SECTION_NAMES)
	{
		if (path.ends_with(secName))
			return secName;
	}

	return "";
}