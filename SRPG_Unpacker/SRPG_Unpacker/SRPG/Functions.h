#pragma once

#include <Windows.h>

#include "../MemData.h"
#include "../FileAccess.h"

void initMemData(MemData& memData, FileReader& fw, const DWORD& size = -1);

class EDITDATA* createSRPGClass(const DWORD& type);
class EDITDATA* createCommand(const DWORD& type);