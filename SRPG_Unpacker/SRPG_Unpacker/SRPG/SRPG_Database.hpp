/*
 *  File: SRPG_Database.hpp
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

class SRPG_Database : public SRPG_ContainerBase
{
public:
	SRPG_Database() {}
	virtual ~SRPG_Database() {}
	void Init(FileReader& fw) override;
	void Dump(FileWriter& fw) const override;
	void WritePatches(const std::filesystem::path& outPath) const override;
	void ApplyPatches(const std::filesystem::path& patchPath) override;

	std::string GetWindowTitle() const
	{
		return m_windowTitle.ToString();
	}

	std::string GetGameTitle() const
	{
		return m_gameTitle.ToString();
	}

	void SetWindowTitle(const std::string& title)
	{
		m_windowTitle = title;
	}

	void SetGameTitle(const std::string& title)
	{
		m_gameTitle = title;
	}

private:
	void sub_F8E4E0(FileReader& fw);
	void sub_F7DA50(FileReader& fw);
	void sub_F7DD10(FileReader& fw);

	void dump_sub_F8E4E0(FileWriter& fw) const;
	void dump_sub_F7DA50(FileWriter& fw) const;
	void dump_sub_F7DD10(FileWriter& fw) const;

private:
	CMenuOperation* m_pPlayerUnits      = nullptr;
	CMenuOperation* m_pClasses          = nullptr;
	CMenuOperation* m_pWeapons          = nullptr;
	CMenuOperation* m_pItems            = nullptr;
	CMenuOperation* m_pSkills           = nullptr;
	CMenuOperation* m_pStates           = nullptr;
	CMenuOperation* m_pOriginalTerrains = nullptr;
	CMenuOperation* m_pRuntimeTerrains  = nullptr;
	CMenuOperation* m_pClassTypes       = nullptr;
	CMenuOperation* m_pMoveTypeData     = nullptr;

	std::array<CMenuOperation*, 4> m_pWeaponTypes = { nullptr };

	CMenuOperation* m_pDifficulties = nullptr;
	CMenuOperation* m_pFonts        = nullptr;
	CMenuOperation* m_pSwitchData   = nullptr;
	CMenuOperation* m_pClassGroups  = nullptr;

	std::array<CMenuOperation*, 10> m_pNPCSettings = { nullptr };

	CMenuOperation* m_pStringData1 = nullptr;
	CMenuOperation* m_pFacialData  = nullptr;
	CMenuOperation* m_pStringData2 = nullptr;

	std::array<CMenuOperation*, 6> m_pVariableData = { nullptr };

	CMenuOperation* m_pStringData3     = nullptr;
	CMenuOperation* m_pCmdStrPlaceEv   = nullptr; // Command Strings - Place Events
	CMenuOperation* m_pCmdStrTalkEv    = nullptr; // Command Strings - Talk Events
	CMenuOperation* m_pTypeIDData      = nullptr;
	CMenuOperation* m_pRaces           = nullptr;
	CMenuOperation* m_pFusionSettings  = nullptr;
	CMenuOperation* m_pTransformations = nullptr;
	CMenuOperation* m_pPassGroupData   = nullptr;

	std::array<CMenuOperation*, 10> m_pOriginalData = { nullptr };

	CMenuOperation* m_pStringData6 = nullptr;

	MemData m_windowTitle;
	MemData m_gameTitle;
	MemData this_144;
	MemData this_145;
	MemData this_146;
	MemData this_147;
	DWORD this_148        = 0;
	DWORD this_149        = 0;
	DWORD this_150        = 0;
	DWORD this_151        = 0;
	DWORD this_152        = 0;
	DWORD this_153        = 0;
	DWORD this_154        = 0;
	DWORD this_155        = 0;
	DWORD m_gold          = 0;
	DWORD m_bonus         = 0;
	DWORD m_maxSkillCount = 0;
	DWORD m_maxItemCount  = 0;
	DWORD m_convoyItem    = 0;
	DWORD m_maxEnemyCount = 0;
	DWORD m_maxLv         = 0;
	DWORD m_maxHP         = 0;
	DWORD m_maxStr        = 0;
	DWORD m_maxMag        = 0;
	DWORD m_maxSkl        = 0;
	DWORD m_maxSpd        = 0;
	DWORD m_maxLck        = 0;
	DWORD m_maxDef        = 0;
	DWORD m_maxRes        = 0;
	DWORD m_maxMov        = 0;
	DWORD m_maxWlv        = 0;
	DWORD m_maxBld        = 0;
	DWORD m_pursuitValue  = 0;
	DWORD m_minExp        = 0;
	DWORD m_leaderExp     = 0;
	DWORD m_subLeaderExp  = 0;
	DWORD this_178        = 0;
	DWORD this_179        = 0;
	DWORD this_180        = 0;
	DWORD this_181        = 0;
	DWORD this_182        = 0;
	DWORD this_183        = 0;

	CMenuOperation* m_pItemGroupData = nullptr;
	CMenuOperation* m_pUnitIDData    = nullptr;
	MemData this_186;

	DWORD this_187 = 0;
	DWORD this_188 = 0;
	DWORD this_189 = 0;
	DWORD this_190 = 0;
	DWORD this_191 = 0;
	DWORD this_192 = 0;
	DWORD this_193 = 0;
	DWORD this_194 = 0;
	DWORD this_195 = 0;
	DWORD this_196 = 0;
	DWORD this_197 = 0;
	DWORD this_198 = 0;
	DWORD this_199 = 0;
	DWORD this_200 = 0;
	DWORD this_201 = 0;
	DWORD this_202 = 0;
	DWORD this_203 = 0;
	DWORD this_204 = 0;
	DWORD this_205 = 0;
	DWORD this_206 = 0;
	DWORD this_207 = 0;
	DWORD this_208 = 0;
	DWORD this_209 = 0;
	DWORD this_210 = 0;
	DWORD this_211 = 0;
	DWORD this_212 = 0;
	DWORD this_213 = 0;
	DWORD this_214 = 0;
	DWORD this_215 = 0;
	DWORD this_216 = 0;
	DWORD this_217 = 0;
	DWORD this_218 = 0;
	DWORD this_219 = 0;
	DWORD this_220 = 0;
	DWORD this_221 = 0;
	DWORD this_222 = 0;
	DWORD this_223 = 0;
	DWORD this_224 = 0;
	DWORD this_225 = 0;

	CMenuOperation* m_pItemGroupData1 = nullptr;
	CMenuOperation* m_pShopLayout1    = nullptr;

	DWORD this_228 = 0;
	DWORD this_229 = 0;
	DWORD this_230 = 0;
	DWORD this_231 = 0;
};
