/*
 *  File: ConfigManager.h
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

#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Types.h"
#include "Utils.h"

class ConfigManager
{
public:
	static ConfigManager& GetInstance()
	{
		static ConfigManager instance;
		return instance;
	}

	ConfigManager(ConfigManager const&)  = delete;
	void operator=(ConfigManager const&) = delete;

	
	template<typename T>
	static void Add(const std::string& key, const T& value)
	{
		GetInstance().add<T>(key, value);
	}

	template<typename T>
	static T Get(const std::string& key)
	{
		return GetInstance().get<T>(key);
	}

	static nlohmann::ordered_json GetJson()
	{
		return GetInstance().getJson();
	}

	static void Add2Array(const std::string& arr, const std::string& value, const std::vector<uint32_t>& elems)
	{
		GetInstance().add2Array(arr, value, elems);
	}

	static void Add2Array(const std::string& arr, const std::wstring& value, const std::vector<uint32_t>& elems)
	{
		GetInstance().add2Array(arr, value, elems);
	}

	static void Add2Array(const std::wstring& arr, const std::wstring& value, const std::vector<uint32_t>& elems)
	{
		GetInstance().add2Array(arr, value, elems);
	}

	static void Load(const std::wstring& filename)
	{
		GetInstance().load(filename);
	}

	static void Save(const std::wstring& filename)
	{
		GetInstance().save(filename);
	}

	static nlohmann::ordered_json& GetNext(const std::string& key)
	{
		return GetInstance().getNext(key);
	}

	static nlohmann::ordered_json& GetNext(const std::wstring& key)
	{
		return GetInstance().getNext(key);
	}

	static void Clear()
	{
		GetInstance().clear();
	}

private:
	ConfigManager()  = default;
	~ConfigManager() = default;

	template<typename T>
	void add(const std::string& key, const T& value)
	{
		m_json[key] = value;
	}

	template<typename T>
	T get(const std::string& key)
	{
		if (!m_json.contains(key))
			return T();

		return m_json[key].get<T>();
	}

	nlohmann::ordered_json getJson() const
	{
		return m_json;
	}

	void add2Array(const std::string& arr, const std::string& value, const std::vector<uint32_t>& elems)
	{
		if (!m_json.contains(arr))
			m_json[arr] = nlohmann::json::array();

		nlohmann::ordered_json obj;
		obj["name"] = value;

		if (!elems.empty())
			obj["elems"] = elems;

		m_json[arr].push_back(obj);
	}

	void add2Array(const std::string& arr, const std::wstring& value, const std::vector<uint32_t>& elems)
	{
		add2Array(arr, ws2s(value), elems);
	}

	void add2Array(const std::wstring& arr, const std::wstring& value, const std::vector<uint32_t>& elems)
	{
		add2Array(ws2s(arr), ws2s(value), elems);
	}

	nlohmann::ordered_json& getNext(const std::string& key)
	{
		if (!m_json.contains(key) || !m_json[key].is_array())
			return m_empty;

		m_map.try_emplace(key, 0);
		return m_json[key][m_map[key]++];
	}

	nlohmann::ordered_json& getNext(const std::wstring& key)
	{
		return getNext(ws2s(key));
	}

	void clear()
	{
		m_json.clear();
		m_map.clear();
	}

	void load(const std::filesystem::path& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to open config file." << std::endl;
			return;
		}

		file >> m_json;
		file.close();

		m_map.clear();
	}

	void save(const std::filesystem::path& filename)
	{
		std::ofstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Error: Unable to open config file." << std::endl;
			return;
		}

		file << m_json.dump(4);
		file.close();
	}

private:
	nlohmann::ordered_json m_json  = {};
	nlohmann::ordered_json m_empty = {};
	std::map<std::string, uint32_t> m_map;
};
