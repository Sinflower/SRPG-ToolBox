/*
 *  File: Crypt.h
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

#pragma once

#include <Windows.h>
#include <string>
#include <vector>

class Crypt
{
	inline static const std::wstring CRYPT_KEY_VERY_OLD = L"_dummy";
	inline static const std::wstring CRYPT_KEY_OLD      = L"keyset";
	inline static const std::wstring CRYPT_KEY_NEW      = L"_dynamic";

public:
	static Crypt &GetInstance()
	{
		static Crypt instance;
		return instance;
	}

	Crypt(Crypt const &)          = delete;
	void operator=(Crypt const &) = delete;

	void SetDoCrypt(const bool &en)
	{
		m_doCrypt = en;
	}

	static void DecryptData(std::vector<uint8_t> &data)
	{
		GetInstance().crypt(data, true);
	}

	static void EncryptData(std::vector<uint8_t> &data)
	{
		GetInstance().crypt(data, false);
	}

	static void EnableCrypt(const bool &en)
	{
		GetInstance().SetDoCrypt(en);
	}

	static void SwitchToVeryOldKey()
	{
		GetInstance().switchToVeryOldKey();
	}

	static void SwitchToNewKey()
	{
		GetInstance().switchToNewKey();
	}

	template<typename T, std::size_t S>
	static void SwitchToCustomKey(const std::array<T, S> &key)
	{
		GetInstance().switchToCustomKey(key.data(), key.size() * sizeof(T));
	}

private:
	Crypt()
	{
		setKey(CRYPT_KEY_OLD.c_str(), CRYPT_KEY_OLD.length());
		initCryptEngine();
	}

	~Crypt()
	{
		destoryCryptEngine();
	}

	bool initCryptEngine();

	void destoryCryptEngine();

	void reinitCryptEngine()
	{
		destoryCryptEngine();
		initCryptEngine();
	}

	void switchToVeryOldKey();
	void switchToNewKey();

	void switchToCustomKey(const void *key, const std::size_t &size);

	void crypt(std::vector<uint8_t> &data, bool decrypt = true);

	void setKey(const void *key, const std::size_t &size);
	bool isThisKeyAlreadySet(const std::wstring &key) const;
	bool isThisKeyAlreadySet(const void *key, const std::size_t &size) const;

private:
	HCRYPTKEY m_hKey        = NULL;
	HCRYPTPROV m_hCryptProv = NULL;
	ALG_ID m_algorithm      = CALG_RC4;

	std::vector<BYTE> m_cryptKey = {};

	bool m_doCrypt   = true;
};