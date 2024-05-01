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

#define DecryptData Crypt::GetInstance().Decrypt
#define EncryptData Crypt::GetInstance().Encrypt
#define EnableCrypt Crypt::GetInstance().SetDoCrypt

class Crypt
{
	inline static const std::wstring CRYPT_KEY = L"keyset";

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

	void Decrypt(std::vector<uint8_t> &data)
	{
		crypt(data, true);
	}

	void Encrypt(std::vector<uint8_t> &data)
	{
		crypt(data, false);
	}

private:
	Crypt()
	{
		initCryptEngine();
	}

	~Crypt()
	{
		destoryCryptEngine();
	}

	bool initCryptEngine();

	void destoryCryptEngine();

	void crypt(std::vector<uint8_t> &data, bool decrypt = true);

private:
	HCRYPTKEY m_hKey        = NULL;
	HCRYPTPROV m_hCryptProv = NULL;

	bool m_doCrypt = true;
};