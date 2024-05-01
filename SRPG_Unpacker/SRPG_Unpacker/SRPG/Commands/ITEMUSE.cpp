// Compatible up to v1.292

#include "ITEMUSE.h"

void ITEMUSE::init(FileReader& fw)
{
	this_3 = fw.ReadDWord();
	this_4 = fw.ReadDWord();
	this_5 = fw.ReadDWord();
	this_6 = fw.ReadDWord();
	this_7 = fw.ReadDWord();
	this_8 = fw.ReadDWord();

	if (g_ArcVersion >= 1015)
		this_9 = fw.ReadDWord();
}

void ITEMUSE::dump(FileWriter& fw) const
{
	fw.Write(this_3);
	fw.Write(this_4);
	fw.Write(this_5);
	fw.Write(this_6);
	fw.Write(this_7);
	fw.Write(this_8);

	if (g_ArcVersion >= 1015)
		fw.Write(this_9);
}
