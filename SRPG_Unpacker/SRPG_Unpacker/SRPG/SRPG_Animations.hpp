/*
 *  File: SRPG_Animations.hpp
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

class SRPG_Animations : public SRPG_ContainerBase
{
public:
	SRPG_Animations() :
		SRPG_ContainerBase("Animations") {}
	virtual ~SRPG_Animations() {}

protected:
	void init(FileReader& fw) override;
	void dump(FileWriter& fw) const override;
	void writePatches(const std::filesystem::path& outPath) const override;

private:
	CMenuOperation* m_pAnimeData1 = nullptr; // this_38
	CMenuOperation* m_pAnimeData2 = nullptr; // this_39
	CMenuOperation* m_pAnimeData3 = nullptr; // this_40
	CMenuOperation* m_pAnimeData4 = nullptr; // this_41

	DWORD this_42 = 0;
	DWORD this_43 = 0;
	DWORD this_44 = 0;
	DWORD this_45 = 0;
	DWORD this_46 = 0;
	DWORD this_47 = 0;
	DWORD this_48 = 0;
	DWORD this_49 = 0;
	DWORD this_50 = 0;
	DWORD this_51 = 0;
	DWORD this_52 = 0;
	DWORD this_53 = 0;
	DWORD this_54 = 0;
	DWORD this_55 = 0;
	DWORD this_56 = 0;
	DWORD this_57 = 0;
	DWORD this_58 = 0;
	DWORD this_59 = 0;

	CMenuOperation* m_pFrameOriginal1 = nullptr; // this_60
	CMenuOperation* m_pFrameOriginal2 = nullptr; // this_61
	CMenuOperation* m_pFrameOriginal3 = nullptr; // this_62

	DWORD this_63 = 0;
	DWORD this_64 = 0;
	DWORD this_65 = 0;
	DWORD this_66 = 0;
	DWORD this_67 = 0;
	DWORD this_68 = 0;
	DWORD this_69 = 0;
	DWORD this_70 = 0;
	DWORD this_71 = 0;
	MemData this_72;
	DWORD this_74 = 0;
	DWORD this_75 = 0;
	DWORD this_76 = 0;
	DWORD this_77 = 0;
	DWORD this_78 = 0;
	DWORD this_79 = 0;
	DWORD this_80 = 0;
	DWORD this_81 = 0;
	DWORD this_82 = 0;
	DWORD this_83 = 0;
	DWORD this_84 = 0;
	DWORD this_85 = 0;
	DWORD this_86 = 0;
	DWORD this_87 = 0;
};
