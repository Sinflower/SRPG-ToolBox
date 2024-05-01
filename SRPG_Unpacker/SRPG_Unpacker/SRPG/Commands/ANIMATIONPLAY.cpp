// Compatible up to v1.292

#include "ANIMATIONPLAY.h"

void ANIMATIONPLAY::init(FileReader& fw)
{
	fw.ReadBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}

void ANIMATIONPLAY::dump(FileWriter& fw) const
{
	fw.WriteBytes(data.data(), static_cast<DWORD>(data.size() * sizeof(DWORD)));
}
