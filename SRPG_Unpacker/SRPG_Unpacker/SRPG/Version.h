#pragma once

#include <Windows.h>
#include <codecvt>
#include <stdint.h>
#include <string>

extern DWORD g_ArcVersion; // dts archive file version, i.e., SRPG version

#define NOT_IMPLEMENTED                                                                                  \
	{                                                                                                    \
		std::cerr << __FILE__ << ":" << __LINE__ << " ERROR This has not been implemented" << std::endl; \
		exit(-1);                                                                                        \
	}

// static inline std::wstring s2ws(const std::string& str)
//{
//	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
// }
//
// static inline std::string ws2s(const std::wstring& wstr)
//{
//	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wstr);
// }
