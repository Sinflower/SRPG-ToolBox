/*
 *  File: SRPG_StorySettings.hpp
 *  Copyright (c) 2025 Sinflower
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

#include "SRPG_ContainerBase.hpp"

class CMenuOperation;

class SRPG_StorySettings : public SRPG_ContainerBase
{
public:
	SRPG_StorySettings() {}
	virtual ~SRPG_StorySettings() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;
	void ApplyPatches(const std::filesystem::path& patchPath) override;

private:
	CMenuOperation* m_pCharacterData = nullptr; // this_239
	CMenuOperation* m_pWordData      = nullptr; // this_240
	CMenuOperation* m_pGalleryData   = nullptr; // this_241
	CMenuOperation* m_pSoundModeData = nullptr; // this_242

	DWORD this_243 = 0;
	DWORD this_244 = 0;
	DWORD this_245 = 0;
	DWORD this_246 = 0;
	DWORD this_247 = 0;
	DWORD this_248 = 0;
	DWORD this_249 = 0;
};
