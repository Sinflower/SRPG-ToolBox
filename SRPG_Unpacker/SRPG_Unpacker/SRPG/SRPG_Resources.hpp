/*
 *  File: SRPG_Resources.hpp
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

#include <array>
#include <nlohmann/json.hpp>

class CMenuOperation;

class SRPG_Resources : public SRPG_ContainerBase
{
	struct ResourceFlags
	{
		ResourceFlags() {}
		ResourceFlags(const DWORD& flag)
		{
			HasResData   = ((flag & 1) == 0);
			HasUIResData = ((flag & 2) == 0);
			HasMediaData = ((flag & 4) == 0);
			HasFontData  = ((flag & 8) == 0);
			HasVideoData = ((flag & 0x20) == 0);
		}

		bool HasResData   = false;
		bool HasUIResData = false;
		bool HasMediaData = false;
		bool HasFontData  = false;
		bool HasVideoData = false;
	};

public:
	SRPG_Resources(const DWORD& resFlag) :
		SRPG_ContainerBase("Resources"),
		m_resFlags(resFlag)
	{}

	virtual ~SRPG_Resources() {}

	nlohmann::ordered_json GetResMapping() const;

	const std::array<DWORD, 21>& GetUnknown() const
	{
		return m_unknown;
	}

	protected:
	void init(FileReader& fw) override;
	void dump(FileWriter& fw) const override;
	void dumpProj(FileWriter& fw) const override;
	void writePatches(const std::filesystem::path& outPath) const;

private:
	ResourceFlags m_resFlags;

	std::array<DWORD, 21> m_unknown = { 0 };

	std::array<CMenuOperation*, 16> m_resData    = { nullptr };
	std::array<CMenuOperation*, 15> m_uIResData  = { nullptr };
	std::array<CMenuOperation*, 2> m_mediaData   = { nullptr };
	CMenuOperation* m_pInstalledFontData         = nullptr;
	CMenuOperation* m_pVideoData                 = nullptr;
	std::array<CMenuOperation*, 4> m_classIDData = { nullptr };
};
