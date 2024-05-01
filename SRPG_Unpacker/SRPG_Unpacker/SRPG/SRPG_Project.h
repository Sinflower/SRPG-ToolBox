#pragma once

// Compatible up to v1.292


#include <windows.h>

#include <array>
#include <vector>

#include "../MemData.h"
#include "../FileAccess.h"

class CMenuOperation;

struct SRPG_ProjectData
{
	DWORD version = 0;
	DWORD resFlag = 0;
	std::vector<BYTE> data;
};

class SRPG_Project
{
	static inline const std::wstring PROJECT_FILE_NAME = L"project.srpgs";

	struct ResourceFlags
	{
		ResourceFlags() {}
		ResourceFlags(const DWORD& flag)
		{
			HasResData = ((flag & 1) == 0);
			HasUIResData = ((flag & 2) == 0);
			HasMediaData = ((flag & 4) == 0);
			HasFontData = ((flag & 8) == 0);
			HasVideoData = ((flag & 0x20) == 0);
		}

		bool HasResData = false;
		bool HasUIResData = false;
		bool HasMediaData = false;
		bool HasFontData = false;
		bool HasVideoData = false;
	};

public:
	SRPG_Project(const SRPG_ProjectData& projData);

	~SRPG_Project();

	void Dump(const std::wstring& outFolder) const;

	nlohmann::ordered_json GetResMapping() const;

private:
	void loadProject();

	// ---------------------------------

	void loadMap();

	// ---------------------------------

	void loadAnimations();

	// ---------------------------------

	// this = this_86
	void loadDatabase();

	// this = this_86
	void sub_F8E4E0();

	// this = this_142
	void sub_F7DA50();

	// this = this_186
	void sub_F7DD10();

	// ---------------------------------

	void loadGameLayout();

	// ---------------------------------

	void sub_F8EC70();

	// ---------------------------------

	void loadStorySettings();

	// ---------------------------------

	// this = this_405
	void loadBaseSettings();

	// ---------------------------------

	void loadResources();

	// ---------------------------------

	void dump(FileWriter& fw) const;

	void dumpAsProj(FileWriter& fw) const;

	// ---------------------------------

	void dumpMap(FileWriter& fw) const;

	// ---------------------------------

	void dumpAnimations(FileWriter& fw) const;

	// ---------------------------------

	void dumpDatabase(FileWriter& fw) const;

	void dump_sub_F8E4E0(FileWriter& fw) const;

	void dump_sub_F7DA50(FileWriter& fw) const;

	void dump_sub_F7DD10(FileWriter& fw) const;

	// ---------------------------------

	void dumpGameLayout(FileWriter& fw) const;

	// ---------------------------------

	void dump_sub_F8EC70(FileWriter& fw) const;

	// ---------------------------------

	void dumpStorySettings(FileWriter& fw) const;

	// ---------------------------------

	void dumpBaseSettings(FileWriter& fw) const;

	// ---------------------------------

	void dumpResources(FileWriter& fw) const;
	void dumpResourcesProj(FileWriter& fw) const;

	// ---------------------------------

	nlohmann::ordered_json getResMapping() const;

	// ---------------------------------

private:
	FileReader m_fw;
	ResourceFlags m_resFlags = {};

	DWORD res1 = 0;
	DWORD res2 = 0;

	// this_1-4 = dword_FF4B10 -- File Header / Beginning
	DWORD this_1 = 0;
	DWORD this_2 = 0;
	DWORD this_3 = 0;
	DWORD this_4 = 0;

	// --- sub_F58C80 ---
	CMenuOperation* m_pbEventData = nullptr; // this_230
	// ----- sub_F8F6E0 -----

	CMenuOperation* m_pMapData = nullptr; // this_15
	CMenuOperation* m_pMapTreeData1 = nullptr; // this_16
	CMenuOperation* m_pMapTreeData2 = nullptr; // this_17
	CMenuOperation* m_pDayNightData = nullptr; // this_18 (new)
	CMenuOperation* m_pEventData1 = nullptr; // this_18
	CMenuOperation* m_pEventData2 = nullptr; // this_19
	CMenuOperation* m_pUnitData1 = nullptr; // this_20

	// sub_F8F6E0 - this_15
	DWORD this_21 = 0;
	BYTE this_22 = 0;
	DWORD this_23 = 0;
	BYTE this_24 = 0;
	std::array<CMenuOperation*, 12> m_pJumpIDData = { nullptr }; // this_25-this_36
	std::array<CMenuOperation*, 10> m_pJumpIDData2 = { nullptr }; // this_25-this_36
	std::array<CMenuOperation*, 6> m_pParamHeadData = { nullptr };
	MemData this_37;

	// ----- sub_F8F6E0 -----


	// ----- sub_F8F9F0 -----

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

	// ----- sub_F8F9F0 -----

	// ----- sub_F8DD30 -----

	CMenuOperation* m_pUnitData2 = nullptr; // this_86
	CMenuOperation* m_pClassData = nullptr; // this_87
	CMenuOperation* m_pWeaponData = nullptr; // this_88
	CMenuOperation* m_pItemData = nullptr; // this_89
	CMenuOperation* m_pSkillData = nullptr; // this_90
	CMenuOperation* m_pStateData = nullptr; // this_91
	CMenuOperation* m_pPassData1 = nullptr; // this_92
	CMenuOperation* m_pPassData2 = nullptr; // this_93
	CMenuOperation* m_pScreenScroll = nullptr; // this_94
	CMenuOperation* m_pScreenShake = nullptr; // this_95
	std::array<CMenuOperation*, 4> m_pWeaponTypeData = { nullptr }; // this_96-this_99
	CMenuOperation* m_pDifficultyData = nullptr; // this_100
	CMenuOperation* m_pFontData = nullptr; // this_101
	CMenuOperation* m_pSwitchData1 = nullptr; // this_102
	CMenuOperation* m_pScreenffect = nullptr; // this_103
	std::array<CMenuOperation*, 10> m_pNPCData = { nullptr }; // this_104-this_113
	CMenuOperation* m_pStringData1 = nullptr; // this_114
	CMenuOperation* m_pFacialData = nullptr; // this_115
	CMenuOperation* m_pStringData2 = nullptr; // this_116
	std::array<CMenuOperation*, 6> m_pVariableData = { nullptr }; // this_117-this_122
	CMenuOperation* m_pStringData3 = nullptr; // this_123
	CMenuOperation* m_pStringData4 = nullptr; // this_124
	CMenuOperation* m_pStringData5 = nullptr; // this_125
	CMenuOperation* m_pTypeIDData = nullptr; // this_126
	CMenuOperation* m_pRaceData = nullptr; // this_127
	CMenuOperation* m_pFusionData = nullptr; // this_128
	CMenuOperation* m_pMetamorRData = nullptr; // this_129
	CMenuOperation* m_pPassGroupData = nullptr; // this_130
	std::array<CMenuOperation*, 10> m_pOriginalData = { nullptr }; // this_131-this_140
	CMenuOperation* m_pStringData6 = nullptr; // this_141
	MemData this_142;
	MemData this_143;
	MemData this_144;
	MemData this_145;
	MemData this_146;
	MemData this_147;
	DWORD this_148 = 0;
	DWORD this_149 = 0;
	DWORD this_150 = 0;
	DWORD this_151 = 0;
	DWORD this_152 = 0;
	DWORD this_153 = 0;
	DWORD this_154 = 0;
	DWORD this_155 = 0;
	DWORD this_156 = 0;
	DWORD this_157 = 0;
	DWORD this_158 = 0;
	DWORD this_159 = 0;
	DWORD this_160 = 0;
	DWORD this_161 = 0;
	DWORD this_162 = 0;
	DWORD this_163 = 0;
	DWORD this_164 = 0;
	DWORD this_165 = 0;
	DWORD this_166 = 0;
	DWORD this_167 = 0;
	DWORD this_168 = 0;
	DWORD this_169 = 0;
	DWORD this_170 = 0;
	DWORD this_171 = 0;
	DWORD this_172 = 0;
	DWORD this_173 = 0;
	DWORD this_174 = 0;
	DWORD this_175 = 0;
	DWORD this_176 = 0;
	DWORD this_177 = 0;
	DWORD this_178 = 0;
	DWORD this_179 = 0;
	DWORD this_180 = 0;
	DWORD this_181 = 0;
	DWORD this_182 = 0;
	DWORD this_183 = 0;
	CMenuOperation* m_pItemGroupData = nullptr; // this_184
	CMenuOperation* m_pUnitIDData = nullptr; // this_185
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
	CMenuOperation* m_pItemGroupData1 = nullptr; // this_226
	CMenuOperation* m_pShopLayout1 = nullptr; // this_227
	DWORD this_228 = 0;
	DWORD this_229 = 0;
	DWORD this_230 = 0;
	DWORD this_231 = 0;

	// ----- sub_F8DD30 -----


	// ----- sub_F8F250 -----

	DWORD this_375 = 0;
	DWORD this_376 = 0;
	DWORD this_377 = 0;
	DWORD this_378 = 0;
	DWORD this_379 = 0;
	DWORD this_380 = 0;
	DWORD this_381 = 0;

	CMenuOperation* m_pMessageLayoutData = nullptr; // this_382
	CMenuOperation* m_pShopLayout2 = nullptr; // this_383

	CMenuOperation* m_pTypeIDData2 = nullptr;

	CMenuOperation* m_pCommandLayoutData1 = nullptr; // this_384
	CMenuOperation* m_pCommandLayoutData2 = nullptr; // this_385
	CMenuOperation* m_pCommandLayoutData3 = nullptr; // this_386
	CMenuOperation* m_pCommandLayoutData4 = nullptr; // this_387
	CMenuOperation* m_pCommandLayoutData5 = nullptr; // this_388
	struct RESOURCELAYOUTDATA* m_pResourceLayoutData = nullptr; // this_389

	// ----- sub_F8F250 -----


	// ----- sub_F8EC70 -----

	CMenuOperation* m_pInteropAnimeData = nullptr; // this_231
	CMenuOperation* m_pInteropMediaData = nullptr; // this_232
	CMenuOperation* m_pInteropGraphicsData = nullptr; // this_233
	CMenuOperation* m_pInteropUIData = nullptr; // this_234
	CMenuOperation* m_pInteropTextUIData = nullptr; // this_235
	CMenuOperation* m_pInteropScreenData = nullptr; // this_236
	CMenuOperation* m_pInteropStringData1 = nullptr; // this_237
	CMenuOperation* m_pInteropStringData2 = nullptr; // this_238

	// ----- sub_F8EC70 -----


	// ----- sub_F8ED60 -----

	CMenuOperation* m_pCharacterData = nullptr; // this_239
	CMenuOperation* m_pWordData = nullptr; // this_240
	CMenuOperation* m_pGalleryData = nullptr; // this_241
	CMenuOperation* m_pSoundModeData = nullptr; // this_242

	DWORD this_243 = 0;
	DWORD this_244 = 0;
	DWORD this_245 = 0;
	DWORD this_246 = 0;
	DWORD this_247 = 0;
	DWORD this_248 = 0;
	DWORD this_249 = 0;

	// ----- sub_F8ED60 -----


	// ----- sub_F8EE60 -----

	CMenuOperation* m_pRestShopData1 = nullptr; // this_405
	CMenuOperation* m_pRestShopData2 = nullptr; // this_406
	CMenuOperation* m_pQuestData = nullptr; // this_407
	CMenuOperation* m_pRestAreaData = nullptr; // this_408

	std::array<CMenuOperation*, 6> m_pEventDatas = { nullptr }; // this_409-this_414
	CMenuOperation* m_pSwitchData2 = nullptr; // this_415
	MemData this_416;

	DWORD this_417 = 0;
	CMenuOperation* m_pTestMember = nullptr; // this_418
	DWORD this_419 = 0;
	DWORD this_420 = 0;
	DWORD this_421 = 0;
	DWORD this_422 = 0;
	DWORD this_423 = 0;
	CMenuOperation* m_pItemGroupData2 = nullptr; // this_424
	DWORD this_425 = 0;
	DWORD this_426 = 0;
	DWORD this_427 = 0;
	DWORD this_428 = 0;
	DWORD this_429 = 0;

	// ----- sub_F8EE60 -----

	// --- sub_F58C80 ---

	// --- sub_8F8980 ---

	std::array<DWORD, 21> m_unknown = { 0 };

	std::array<CMenuOperation*, 16> m_resData = { nullptr };
	std::array<CMenuOperation*, 15> m_uIResData = { nullptr };
	std::array<CMenuOperation*, 2> m_mediaData = { nullptr };
	CMenuOperation* m_pInstalledFontData = nullptr;
	CMenuOperation* m_pVideoData = nullptr;
	std::array<CMenuOperation*, 4> m_classIDData = { nullptr };

	// --- sub_8F8980 ---
};

