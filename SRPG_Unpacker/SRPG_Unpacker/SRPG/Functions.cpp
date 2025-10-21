/*
 *  File: Functions.cpp
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

#include "Functions.h"
#include "Globals.h"

/*************CLASSES****************/
#include "Classes/ANIMEDATA.h"
#include "Classes/ANIMEIDDATA.h"
#include "Classes/BACKLOGDATA.h"
#include "Classes/CHANGEINFODATA.h"
#include "Classes/CHARACTERDATA.h"
#include "Classes/CHARREPLACEDATA.h"
#include "Classes/CHECKDATA.h"
#include "Classes/CHOICEDATA.h"
#include "Classes/CLASSDATA.h"
#include "Classes/CLASSGROUPDATA.h"
#include "Classes/CLASSGROUPENTRYDATA.h"
#include "Classes/CLASSIDDATA.h"
#include "Classes/CLASSTYPEDATA.h"
#include "Classes/CLEARSAVEDATA.h"
#include "Classes/COMMANDLAYOUTDATA.h"
#include "Classes/COMPATIBLEDATA.h"
#include "Classes/COMPLETEGRAPHICSDATA.h"
#include "Classes/COMPLETEMEDIADATA.h"
#include "Classes/COMPLETERECOLLECTIONDATA.h"
#include "Classes/COMPLETESWITCHDATA.h"
#include "Classes/DAYNIGHTDATA.h"
#include "Classes/DECORATIONDATA.h"
#include "Classes/DICTIONARYCONDITION.h"
#include "Classes/DIFFICULTYDATA.h"
#include "Classes/DYNAMICUNITEVENT.h"
#include "Classes/EVENTACTIONDATA.h"
#include "Classes/EVENTCOMMAND.h"
#include "Classes/EVENTDATA.h"
#include "Classes/EVENTPAGE.h"
#include "Classes/EXECUTEREFDATA.h"
#include "Classes/FACIALDATA.h"
#include "Classes/FONTDATA.h"
#include "Classes/FONTGROUPDATA.h"
#include "Classes/FORCEENTRY.h"
#include "Classes/FORCESORTIEDATA.h"
#include "Classes/FRAMEDATA.h"
#include "Classes/FRAMELIST.h"
#include "Classes/FRAMEORIGINAL.h"
#include "Classes/FUSIONDATA.h"
#include "Classes/GALLERYDATA.h"
#include "Classes/GALLERYGROUPDATA.h"
#include "Classes/GEN_EVDATA.h"
#include "Classes/GEN_JSDATA.h"
#include "Classes/IMAGEIDDATA.h"
#include "Classes/INSTALLEDFONTDATA.h"
#include "Classes/INTEROPANIMEDATA.h"
#include "Classes/INTEROPGRAPHICSDATA.h"
#include "Classes/INTEROPMEDIADATA.h"
#include "Classes/INTEROPSCREENDATA.h"
#include "Classes/INTEROPSTRINGDATA.h"
#include "Classes/INTEROPTEXTUIDATA.h"
#include "Classes/INTEROPUIDATA.h"
#include "Classes/INVENTORYDATA.h"
#include "Classes/ITEMCONDITIONDATA.h"
#include "Classes/ITEMCONVERTDATA.h"
#include "Classes/ITEMDATA.h"
#include "Classes/ITEMGROUPDATA.h"
#include "Classes/JIMODATA.h"
#include "Classes/JUMPIDDATA.h"
#include "Classes/LINEPOSDATA.h"
#include "Classes/MAPBASE.h"
#include "Classes/MAPDATA.h"
#include "Classes/MAPPOSDATA.h"
#include "Classes/MAPTREEDATA.h"
#include "Classes/MATERIALDATA.h"
#include "Classes/MEDIADATA.h"
#include "Classes/MEMDATA.h"
#include "Classes/MESSAGELAYOUTDATA.h"
#include "Classes/METAMORDATA.h"
#include "Classes/METAMORHISTORY.h"
#include "Classes/MOSTRECENTINFO.h"
#include "Classes/MOTIONIDDATA.h"
#include "Classes/MOVETYPEDATA.h"
#include "Classes/MULTICOMMANDDATA.h"
#include "Classes/MYDECODATA.h"
#include "Classes/NEWSKILLDATA.h"
#include "Classes/NPCDATA.h"
#include "Classes/OCCUPYDATA.h"
#include "Classes/ORIGINALDATA.h"
#include "Classes/PAIRKEYDATA.h"
#include "Classes/PARAMHEADDATA.h"
#include "Classes/PASSCHIPDATA.h"
#include "Classes/PASSDATA.h"
#include "Classes/PASSGROUPDATA.h"
#include "Classes/PATTERNDATA.h"
#include "Classes/QUESTDATA.h"
#include "Classes/RACEDATA.h"
#include "Classes/REFCUTINDATA.h"
#include "Classes/REINFORCECONTAINER.h"
#include "Classes/REINFORCEDATA.h"
#include "Classes/RENDERPOOLDATA.h"
#include "Classes/RESDATA.h"
#include "Classes/RESOURCELAYOUTDATA.h"
#include "Classes/RESTAREADATA.h"
#include "Classes/RESTSHOPDATA.h"
#include "Classes/REWARDDATA.h"
#include "Classes/RPASSDATA.h"
#include "Classes/SCRIPTCODEDATA.h"
#include "Classes/SHOPDATA.h"
#include "Classes/SHOPLAYOUT.h"
#include "Classes/SKILLDATA.h"
#include "Classes/SOUNDMODEDATA.h"
#include "Classes/SPRITEDATA.h"
#include "Classes/STATEDATA.h"
#include "Classes/STRINGDATA.h"
#include "Classes/SUPPORTDATA.h"
#include "Classes/SWITCHACTIONDATA.h"
#include "Classes/SWITCHDATA.h"
#include "Classes/TESTMEMBER.h"
#include "Classes/TITLESDATA.h"
#include "Classes/TROPHYDATA.h"
#include "Classes/TURNSTATEDATA.h"
#include "Classes/TYPEIDDATA.h"
#include "Classes/UIRESDATA.h"
#include "Classes/UNITCONDITIONDATA.h"
#include "Classes/UNITDATA.h"
#include "Classes/UNITIDDATA.h"
#include "Classes/UNITSTATUSDATA.h"
#include "Classes/VARIABLECONDITIONDATA.h"
#include "Classes/VARIABLEDATA.h"
#include "Classes/VIDEODATA.h"
#include "Classes/WEAPONDATA.h"
#include "Classes/WEAPONTYPEDATA.h"
#include "Classes/WORDDATA.h"
/*************CLASSES****************/

/*************COMMANDS****************/
#include "Commands/ANIMATIONPLAY.h"
#include "Commands/ANIMATIONSTOP.h"
#include "Commands/BACKGROUNDCHANGE.h"
#include "Commands/BONUSCHANGE.h"
#include "Commands/CHAPTERSHOW.h"
#include "Commands/CHOICESHOW.h"
#include "Commands/CLASSCHANGE.h"
#include "Commands/CONSOLELOG.h"
#include "Commands/DAICE.h"
#include "Commands/DAMAGEHIT.h"
#include "Commands/ENVIRONMENTACCESS.h"
#include "Commands/EVENTSKIP.h"
#include "Commands/EVENTSTATECHANGE.h"
#include "Commands/EXPERIENCEPLUS.h"
#include "Commands/FORCEBATTLE.h"
#include "Commands/GOLDCHANGE.h"
#include "Commands/GRAPHICSHIDE.h"
#include "Commands/GRAPHICSSHOW.h"
#include "Commands/HPRECOVERY.h"
#include "Commands/INFOWINDOW.h"
#include "Commands/ITEMCHANGE.h"
#include "Commands/ITEMDURABILITYCHANGE.h"
#include "Commands/ITEMUSE.h"
#include "Commands/LOCATIONFOCUS.h"
#include "Commands/MAPCHIPCHANGE.h"
#include "Commands/MAPINFOCHANGE.h"
#include "Commands/MAPPOSCHOOSE.h"
#include "Commands/MAPPOSOPERATION.h"
#include "Commands/MAPSCROLL.h"
#include "Commands/MAPSTATECHANGE.h"
#include "Commands/MESSAGEERASE.h"
#include "Commands/MESSAGESCROLL.h"
#include "Commands/MESSAGESHOW.h"
#include "Commands/MESSAGETEROP.h"
#include "Commands/MESSAGETITLE.h"
#include "Commands/MOVEOBJECTHIDE.h"
#include "Commands/MOVEOBJECTSHOW.h"
#include "Commands/MUSICPLAY.h"
#include "Commands/MUSICSTOP.h"
#include "Commands/OBJECTADJUST.h"
#include "Commands/PARAMATERCHANGE.h"
#include "Commands/RELATIVETURNMEASURE.h"
#include "Commands/SAVECALL.h"
#include "Commands/SCENECHANGE.h"
#include "Commands/SCREENEFFECT.h"
#include "Commands/SCREENSCROLL.h"
#include "Commands/SCREENSHAKE.h"
#include "Commands/SCREENSTATECHANGE.h"
#include "Commands/SCRIPTEXECUTE.h"
#include "Commands/SKILLCHANGE.h"
#include "Commands/SOUNDPLAY.h"
#include "Commands/SOUNDSTOP.h"
#include "Commands/STILLMESSAGE.h"
#include "Commands/SWITCHACTION.h"
#include "Commands/SYSTEMSETTINGS.h"
#include "Commands/TROPHYCHANGE.h"
#include "Commands/UNITALLCOMMAND.h"
#include "Commands/UNITAPPEAR.h"
#include "Commands/UNITASSIGN.h"
#include "Commands/UNITCAPACITYCHANGE.h"
#include "Commands/UNITFUSION.h"
#include "Commands/UNITINFOCHANGE.h"
#include "Commands/UNITMETAMOR.h"
#include "Commands/UNITMOVE.h"
#include "Commands/UNITPERFORMANCE.h"
#include "Commands/UNITREMOVE.h"
#include "Commands/UNITSLIDE.h"
#include "Commands/UNITSTATEADDITION.h"
#include "Commands/UNITSTATECHANGE.h"
#include "Commands/VARIABLEACTION.h"
#include "Commands/VICTORYMAP.h"
#include "Commands/VIDEOPLAY.h"
#include "Commands/WAITACTION.h"
/*************COMMANDS****************/

void initMemData(MemData& memData, FileReader& fw, const DWORD& size, std::source_location location)
{
	memData.offset = fw.GetOffset();

	if (size == -1)
	{
		memData.size     = fw.ReadDWord();
		memData.readSize = true;
	}
	else
		memData.size = size;

	if (memData.size)
	{
		memData.data.resize(memData.size);
		fw.ReadBytesVec(memData.data);
	}

	if (g_debugMemDataLog.is_open())
	{
		g_debugMemDataLog << "initMemData called from " << std::filesystem::path(location.file_name()).filename() << ":" << location.line() << " - Offset: " << memData.offset << ", Size: " << memData.size << std::endl;
		g_debugMemDataLog << memData << std::endl;
	}
}

void WriteJsonToFile(const nlohmann::ordered_json& json, const std::filesystem::path& path, const std::wstring& name)
{
	const std::filesystem::path fPath = path / name;
	std::ofstream ofs(fPath);

	if (!ofs.is_open())
		throw std::runtime_error("Failed to open file: " + fPath.string());

	ofs << json.dump(4);
	ofs.close();
}

nlohmann::ordered_json ReadJsonFromFile(const std::filesystem::path& path, const std::wstring& name)
{
	const std::filesystem::path fPath = path / name;

	if (!std::filesystem::exists(fPath))
		throw std::runtime_error("File does not exist: " + fPath.string());

	std::ifstream ifs(fPath);

	if (!ifs.is_open())
		throw std::runtime_error("Failed to open file: " + fPath.string());

	nlohmann::ordered_json json = nlohmann::ordered_json::parse(ifs);
	ifs.close();
	return json;
}

void ReadJsonFromFile(nlohmann::ordered_json& json, const std::filesystem::path& path, const std::wstring& name)
{
	json = ReadJsonFromFile(path, name);
}

EDITDATA* createSRPGClass(const DWORD& type)
{
	switch (type)
	{
		case 0:
			return new UNITDATA();
		case 1:
			return new CLASSDATA();
		case 2:
			return new WEAPONDATA();
		case 3:
			return new ITEMDATA();
		case 4:
			return new SKILLDATA();
		case 5:
			return new STATEDATA();
		case 201:
			return new CLASSGROUPDATA();
		case 202:
			return new CLASSGROUPENTRYDATA();
		case 200:
			return new CLASSTYPEDATA();
		case 203:
			return new WEAPONTYPEDATA();
		case 205:
			return new DIFFICULTYDATA();
		case 207:
			return new FONTDATA();
		case 208:
			return new NPCDATA();
		case 221:
			return new RACEDATA();
		case 226:
			return new ORIGINALDATA();
		case 227:
			return new MULTICOMMANDDATA();
		case 225:
			return new RESTSHOPDATA();
		case 223:
			return new QUESTDATA();
		case 224:
			return new RESTAREADATA();
		case 209:
			return new FACIALDATA();
		case 210:
			return new COMPATIBLEDATA();
		case 211:
			return new SUPPORTDATA();
		case 212:
			return new VARIABLEDATA();
		case 213:
			return new CHOICEDATA();
		case 215:
			return new SHOPLAYOUT();
		case 214:
			return new SHOPDATA();
		case 216:
			return new NEWSKILLDATA();
		case 218:
			return new FUSIONDATA();
		case 219:
			return new METAMORDATA();
		case 220:
			return new ITEMCONVERTDATA();
		case 222:
			return new CHARREPLACEDATA();
		case 204:
			return new MOVETYPEDATA();
		case 2502:
			return new TYPEIDDATA();
		case 2500:
			return new UNITIDDATA();
		case 2501:
			return new CLASSIDDATA();
		case 2509:
			return new ANIMEIDDATA();
		case 2510:
			return new RPASSDATA();
		case 2511:
			return new REWARDDATA();
		case 2512:
			return new MOTIONIDDATA();
		case 2513:
			return new PAIRKEYDATA();
		case 2514:
			return new REFCUTINDATA();
		case 2515:
			return new JUMPIDDATA();
		case 2516:
			return new PARAMHEADDATA();
		case 2517:
			return new GEN_JSDATA();
		case 2518:
			return new GEN_EVDATA();
		case 2519:
			return new TITLESDATA();
		case 2520:
			return new CHANGEINFODATA();
		case 300:
			return new RESDATA();
		case 301:
			return new MEDIADATA();
		case 302:
			return new UIRESDATA();
		case 303:
			return new INSTALLEDFONTDATA();
		case 304:
			return new VIDEODATA();
		case 400:
			return new MAPDATA();
		case 100:
			return new PASSDATA();
		case 101:
			return new PASSCHIPDATA();
		case 103:
			return new PASSGROUPDATA();
		case 401:
			return new TESTMEMBER();
		case 405:
			return new ITEMGROUPDATA();
		case 406:
			return new STRINGDATA();
		case 407:
			return new FORCESORTIEDATA();
		case 600:
			return new ANIMEDATA();
		case 601:
			return new FRAMELIST();
		case 602:
			return new FRAMEDATA();
		case 603:
			return new SPRITEDATA();
		case 604:
			return new FRAMEORIGINAL();
		case 700:
			return new INTEROPANIMEDATA();
		case 702:
			return new INTEROPMEDIADATA();
		case 701:
			return new INTEROPGRAPHICSDATA();
		case 703:
			return new INTEROPUIDATA();
		case 704:
			return new INTEROPTEXTUIDATA();
		case 705:
			return new INTEROPSCREENDATA();
		case 706:
			return new INTEROPSTRINGDATA();
		case 805:
			return new GALLERYGROUPDATA();
		case 804:
			return new DICTIONARYCONDITION();
		case 800:
			return new CHARACTERDATA();
		case 801:
			return new WORDDATA();
		case 802:
			return new GALLERYDATA();
		case 803:
			return new SOUNDMODEDATA();
		case 500:
			return new EVENTDATA();
		case 501:
			return new EVENTPAGE();
		case 502:
			return new EVENTCOMMAND();
		case 510:
			return new VARIABLECONDITIONDATA();
		case 505:
			return new ITEMCONDITIONDATA();
		case 506:
			return new UNITCONDITIONDATA();
		case 508:
			return new MAPPOSDATA();
		case 507:
			return new FORCEENTRY();
		case 509:
			return new LINEPOSDATA();
		case 206:
			return new SWITCHDATA();
		case 503:
			return new SWITCHACTIONDATA();
		case 504:
			return new EVENTACTIONDATA();
		case 402:
			return new REINFORCECONTAINER();
		case 403:
			return new REINFORCEDATA();
		case 404:
			return new PATTERNDATA();
		case 2503:
			return new SCRIPTCODEDATA();
		case 2504:
			return new MATERIALDATA();
		case 2505:
			return new MAPBASE();
		case 2506:
			return new UNITSTATUSDATA();
		case 2507:
			return new CHECKDATA();
		case 2508:
			return new IMAGEIDDATA();
		case 900:
			return new MAPTREEDATA();
		case 901:
			return new DAYNIGHTDATA();
		case 1000:
			return new MESSAGELAYOUTDATA();
		case 1001:
			return new COMMANDLAYOUTDATA();
		case 1002:
			return new RESOURCELAYOUTDATA();
		case 10000:
			return new TROPHYDATA();
		case 10016:
			return new INVENTORYDATA();
		case 10013:
			return new TURNSTATEDATA();
		case 10004:
			return new DYNAMICUNITEVENT();
		case 10005:
			return new EXECUTEREFDATA();
		case 10006:
			return new CLEARSAVEDATA();
		case 10007:
			return new COMPLETERECOLLECTIONDATA();
		case 10008:
			return new COMPLETESWITCHDATA();
		case 10009:
			return new COMPLETEGRAPHICSDATA();
		case 10010:
			return new COMPLETEMEDIADATA();
		case 10011:
			return new RENDERPOOLDATA();
		case 10012:
			return new FONTGROUPDATA();
		case 10014:
			return new BACKLOGDATA();
		case 10017:
			return new DECORATIONDATA();
		case 10015:
			return new METAMORHISTORY();
		case 10019:
			return new MEMDATA();
		case 10020:
			return new MYDECODATA();
		case 10021:
			return new OCCUPYDATA();
		case 10022:
			return new JIMODATA();
		case 10023:
			return new MOSTRECENTINFO();
		default:
			std::cerr << "ERROR: Class-Type=" << type << " not implemented" << std::endl;
			exit(-1);
	}

	return nullptr;
}

EDITDATA* createCommand(const DWORD& type)
{
	switch (type)
	{
		case 0:
			return new MESSAGESHOW();
		case 1:
			return new MESSAGEERASE();
		case 101:
			return new MESSAGETITLE();
		case 2:
			return new MESSAGETEROP();
		case 3:
			return new STILLMESSAGE();
		case 100:
			return new MESSAGESCROLL();
		case 103:
			return new CHOICESHOW();
		case 102:
			return new INFOWINDOW();
		case 200:
			return new SCREENSCROLL();
		case 201:
			return new SCREENEFFECT();
		case 202:
			return new SCREENSTATECHANGE();
		case 203:
			return new BACKGROUNDCHANGE();
		case 204:
			return new SCREENSHAKE();
		case 400:
			return new GRAPHICSSHOW();
		case 401:
			return new GRAPHICSHIDE();
		case 402:
			return new ANIMATIONPLAY();
		case 403:
			return new ANIMATIONSTOP();
		case 300:
			return new MUSICPLAY();
		case 301:
			return new MUSICSTOP();
		case 302:
			return new SOUNDPLAY();
		case 303:
			return new SOUNDSTOP();
		case 404:
			return new MOVEOBJECTSHOW();
		case 405:
			return new MOVEOBJECTHIDE();
		case 500:
			return new SCENECHANGE();
		case 501:
			return new SCRIPTEXECUTE();
		case 502:
			return new WAITACTION();
		case 503:
			return new SWITCHACTION();
		case 504:
			return new VARIABLEACTION();
		case 505:
			return new EVENTSKIP();
		case 506:
			return new SAVECALL();
		case 507:
			return new SYSTEMSETTINGS();
		case 508:
			return new ENVIRONMENTACCESS();
		case 509:
			return new CONSOLELOG();
		case 304:
			return new VIDEOPLAY();
		case 510:
			return new OBJECTADJUST();
		case 511:
			return new DAICE();
		case 1000:
			return new UNITAPPEAR();
		case 1001:
			return new UNITREMOVE();
		case 1002:
			return new UNITMOVE();
		case 1003:
			return new UNITASSIGN();
		case 1101:
			return new ITEMCHANGE();
		case 1100:
			return new GOLDCHANGE();
		case 1102:
			return new PARAMATERCHANGE();
		case 1103:
			return new SKILLCHANGE();
		case 1200:
			return new HPRECOVERY();
		case 1202:
			return new EXPERIENCEPLUS();
		case 1203:
			return new CLASSCHANGE();
		case 1403:
			return new MAPCHIPCHANGE();
		case 1404:
			return new MAPSCROLL();
		case 1401:
			return new VICTORYMAP();
		case 1301:
			return new FORCEBATTLE();
		case 1201:
			return new DAMAGEHIT();
		case 1402:
			return new LOCATIONFOCUS();
		case 1300:
			return new ITEMUSE();
		case 1400:
			return new CHAPTERSHOW();
		case 1501:
			return new UNITINFOCHANGE();
		case 1502:
			return new UNITSTATECHANGE();
		case 1503:
			return new MAPINFOCHANGE();
		case 1504:
			return new MAPSTATECHANGE();
		case 1500:
			return new EVENTSTATECHANGE();
		case 1600:
			return new BONUSCHANGE();
		case 1601:
			return new TROPHYCHANGE();
		case 1602:
			return new RELATIVETURNMEASURE();
		case 1603:
			return new ITEMDURABILITYCHANGE();
		case 1604:
			return new UNITSTATEADDITION();
		case 1605:
			return new UNITCAPACITYCHANGE();
		case 1606:
			return new UNITSLIDE();
		case 1607:
			return new UNITFUSION();
		case 1608:
			return new UNITMETAMOR();
		case 1609:
			return new UNITALLCOMMAND();
		case 1800:
			return new UNITPERFORMANCE();
		case 1700:
			return new MAPPOSCHOOSE();
		case 1701:
			return new MAPPOSOPERATION();
		default:
			std::cerr << "ERROR: Command=" << type << " not implemented" << std::endl;
			exit(-1);
	}

	return nullptr;
}
