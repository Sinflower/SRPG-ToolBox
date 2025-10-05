/*
 *  File: SRPG_InterOpData.hpp
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

class SRPG_InterOpData : public SRPG_ContainerBase
{
public:
	SRPG_InterOpData() {}
	virtual ~SRPG_InterOpData() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;
	void ApplyPatches(const std::filesystem::path& patchPath) override;

private:
	CMenuOperation* m_pInteropAnimeData    = nullptr; // this_231
	CMenuOperation* m_pInteropMediaData    = nullptr; // this_232
	CMenuOperation* m_pInteropGraphicsData = nullptr; // this_233
	CMenuOperation* m_pInteropUIData       = nullptr; // this_234
	CMenuOperation* m_pInteropTextUIData   = nullptr; // this_235
	CMenuOperation* m_pInteropScreenData   = nullptr; // this_236
	CMenuOperation* m_pInteropStringData1  = nullptr; // this_237
	CMenuOperation* m_pInteropStringData2  = nullptr; // this_238
};
