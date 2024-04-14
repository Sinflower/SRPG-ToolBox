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

#include <fstream>
#include <iostream>
#include <nlohmann\json.hpp>
#include <string>
#include <vector>
#include <map>
#include <format>

#include "Utils.h"

#define Config ConfigManager::GetInstance()

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
	void Add(const std::string& key, const T& value)
	{
		m_json[key] = value;
	}

	template<typename T>
	T Get(const std::string& key)
	{
		if (!m_json.contains(key))
			throw std::runtime_error(std::format("Error: Key '{}' not found.", key));

		return m_json[key].get<T>();
	}

	void Add2Array(const std::string& arr, const std::string& value, const std::vector<uint32_t>& elems)
	{
		if (!m_json.contains(arr))
			m_json[arr] = nlohmann::json::array();

		nlohmann::ordered_json obj;
		obj["name"] = value;

		if (!elems.empty())
			obj["elems"] = elems;

		m_json[arr].push_back(obj);
	}

	void Add2Array(const std::string& arr, const std::wstring& value, const std::vector<uint32_t>& elems)
	{
		Add2Array(arr, ws2s(value), elems);
	}

	void Load(const std::wstring& filename)
	{
		load(filename);
	}

	void Save(const std::wstring& filename)
	{
		save(filename);
	}

	nlohmann::ordered_json& GetNext(const std::string& key)
	{
		if (!m_json.contains(key) || !m_json[key].is_array())
			return m_empty;

		m_map.try_emplace(key, 0);
		return m_json[key][m_map[key]++];
	}

	void Clear()
	{
		m_json.clear();
		m_map.clear();
	}

private:
	ConfigManager() = default;
	~ConfigManager() = default;

	void load(const std::wstring& filename)
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

	void save(const std::wstring& filename)
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
	nlohmann::ordered_json m_json = {};
	nlohmann::ordered_json m_empty = {};
	std::map<std::string, uint32_t> m_map;

};
