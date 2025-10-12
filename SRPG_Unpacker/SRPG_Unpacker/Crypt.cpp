/*
 *  File: Crypt.cpp
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

#include "Crypt.h"

#include <iostream>

bool Crypt::initCryptEngine()
{
	HCRYPTHASH phHash;

	if (m_hKey == NULL)
	{
		if (!CryptAcquireContext(&m_hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			std::cerr << "Error: Unable to create Crypt Context" << std::endl;
			return false;
		}

		if (CryptCreateHash(m_hCryptProv, CALG_MD5, 0, 0, &phHash))
		{
			const std::wstring &CRYPT_KEY = (m_useNewKey ? CRYPT_KEY_NEW : CRYPT_KEY_OLD);
			CryptHashData(phHash, reinterpret_cast<const BYTE *>(CRYPT_KEY.c_str()), static_cast<DWORD>(CRYPT_KEY.length()), 0);
			CryptDeriveKey(m_hCryptProv, CALG_RC4, phHash, 0, &m_hKey);
			CryptDestroyHash(phHash);
			std::cout << "Info: Crypt Engine initialized using " << (m_useNewKey ? "new" : "old") << " key" << std::endl;
		}
		else
		{
			std::cerr << "Error: Unable to create Crypt Hash" << std::endl;
			CryptReleaseContext(m_hCryptProv, 0);
			m_hCryptProv = NULL;
			return false;
		}
	}

	return true;
}

void Crypt::destoryCryptEngine()
{
	if (m_hKey)
	{
		CryptDestroyKey(m_hKey);
		m_hKey = NULL;
	}
	if (m_hCryptProv)
	{
		CryptReleaseContext(m_hCryptProv, 0);
		m_hCryptProv = NULL;
	}
}

void Crypt::switchToNewKey()
{
	std::cout << "Info: Switching to new crypt key" << std::endl;
	if (m_useNewKey)
		return;
	m_useNewKey = true;
	destoryCryptEngine();
	initCryptEngine();
}

void Crypt::crypt(std::vector<uint8_t> &data, bool decrypt)
{
	if (!m_doCrypt)
		return;

	if (data.empty())
		return;

	BOOL res;
	DWORD length = static_cast<DWORD>(data.size());

	uint8_t *pData = data.data();

	if (decrypt)
		res = CryptDecrypt(m_hKey, NULL, TRUE, NULL, pData, &length);
	else
		res = CryptEncrypt(m_hKey, NULL, TRUE, NULL, pData, &length, length);

	if (!res)
		std::cerr << "Error: CryptDecrypt/CryptEncrypt failed: " << GetLastError() << std::endl;
}