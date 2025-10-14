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

#include <format>
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
			const BYTE *pKey = m_cryptKey.data();
			DWORD keySize    = static_cast<DWORD>(m_cryptKey.size());

			CryptHashData(phHash, pKey, keySize, 0);
			CryptDeriveKey(m_hCryptProv, m_algorithm, phHash, 0, &m_hKey);
			CryptDestroyHash(phHash);
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

void Crypt::switchToVeryOldKey()
{
	if (isThisKeyAlreadySet(CRYPT_KEY_VERY_OLD))
		return;

	m_algorithm = CALG_RC2;
	// Yes it is really just length() the type is ignored
	setKey(CRYPT_KEY_VERY_OLD.c_str(), CRYPT_KEY_VERY_OLD.length());
	reinitCryptEngine();
}

void Crypt::switchToNewKey()
{
	if (isThisKeyAlreadySet(CRYPT_KEY_NEW))
		return;

	m_algorithm = CALG_RC4;
	setKey(CRYPT_KEY_NEW.c_str(), CRYPT_KEY_NEW.length());
	reinitCryptEngine();
}

void Crypt::switchToCustomKey(const void *key, const std::size_t &size)
{
	m_algorithm = CALG_RC4;
	setKey(key, size);
	reinitCryptEngine();
}

void Crypt::crypt(std::vector<uint8_t> &data, const bool &decrypt, const bool &overrideDoFlag)
{
	if (!m_doCrypt && !overrideDoFlag)
		return;

	if (data.empty())
		return;

	BOOL res;
	DWORD length = static_cast<DWORD>(data.size());
	DWORD bufLen = length;

	uint8_t *pData = data.data();

	if (decrypt)
	{
		res = CryptDecrypt(m_hKey, NULL, TRUE, NULL, pData, &length);

		if (m_algorithm == CALG_RC2)
		{
			// For the RC2 cypher the length is updated to the real data length (minus padding)
			// Make sure the data vector is resized to the new length
			data.resize(length);
		}
	}
	else
	{
		if (m_algorithm == CALG_RC2)
		{
			// As the old format uses the RC2 cypher the data buffer must be a multiple of the block size
			DWORD blockSize = getBlockLength();
			DWORD padding   = blockSize - (length % blockSize);
			if (padding == 0) padding = blockSize;
			data.resize(data.size() + padding, 0);
			bufLen += padding;
		}

		res = CryptEncrypt(m_hKey, NULL, TRUE, NULL, pData, &length, bufLen);
	}

	if (!res)
		std::cerr << "Error: CryptDecrypt/CryptEncrypt failed: " << GetLastError() << std::endl;
}

void Crypt::setKey(const void *key, const std::size_t &size)
{
	m_cryptKey.resize(size);
	memcpy(m_cryptKey.data(), key, size);
}

bool Crypt::isThisKeyAlreadySet(const std::wstring &key) const
{
	if (m_cryptKey.size() != key.length())
		return false;
	return (memcmp(m_cryptKey.data(), key.c_str(), key.length()) == 0);
}

bool Crypt::isThisKeyAlreadySet(const void *key, const std::size_t &size) const
{
	if (m_cryptKey.size() != size)
		return false;
	return (memcmp(m_cryptKey.data(), key, size) == 0);
}

DWORD Crypt::getBlockLength() const
{
	if (m_hKey == NULL)
	{
		std::cerr << "Error: Cryptographic key not initialized" << std::endl;
		return 0;
	}

	DWORD blockLen = 0;
	DWORD size     = sizeof(DWORD);
	if (!CryptGetKeyParam(m_hKey, KP_BLOCKLEN, reinterpret_cast<BYTE *>(&blockLen), &size, 0))
	{
		std::cerr << "Error: Unable to get block length" << std::endl;
		return 0;
	}

	return blockLen / 8; // Convert bits to bytes
}
