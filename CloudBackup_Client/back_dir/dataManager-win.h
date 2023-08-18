#pragma once
#include <unordered_map>
#include <sstream>
#include "util.h"
namespace Cloud
{
	class DataManager
	{
	public:
		DataManager(const std::string& backup_file)
			:_backup_file(backup_file)
		{
			InitLoad();
		}

		bool InitLoad() 
		{
			// 1. ���ļ��ж�ȡ����
			FileUtil fu(_backup_file);
			std::string body;
			fu.GetContent(&body);
			// 2. ��1��ȡ�������ݷ���hashtable
			std::vector<std::string> array;
			SplitString(body, "\n", &array);
			for (auto& file : array)
			{
				std::vector<std::string> tmp;
				SplitString(file, " ", &tmp);
				if (tmp.size() != 2)
				{
					continue;
				}
				_table[tmp[0]] = tmp[1];
			}
			return true;
		}

		bool Storage() 
		{
			// 1. ��table�ж�ȡkv�� ��ʽ�������뵽�ַ�����
			std::stringstream ss;
			auto it = _table.begin();
			while (it != _table.end())
			{
				ss << it->first << " " << it->second << "\n";
				++it;
			}
			// 2. д�������ļ�
			FileUtil fu(_backup_file);
			fu.SetContent(ss.str());
			return true;
		}

		bool Insert(const std::string& key, const std::string& value)
		{
			_table[key] = value;
			Storage();
			return true;
		}

		bool Update(const std::string& key, const std::string& value)
		{
			_table[key] = value;
			Storage();
			return true;
		}

		bool GetOneByKey(const std::string& key, std::string* value)
		{
			if (_table.count(key) == 0)
			{
				std::cout << "GetOneByKey::File not found" << std::endl;
				return false;
			}
			*value = _table[key];
			return true;
		}

	private:
		int SplitString(const std::string& str, const std::string& sep, std::vector<std::string>* array)
		{
			//�����и����Ӵ�����
			int count = 0;
			size_t pos = 0;
			size_t offset = 0;
			while (1)
			{
				pos = str.find(sep, offset);
				if (pos == std::string::npos) break;
				if (pos == offset) //��������sep
				{
					//ƫ���������ƶ�
					offset = pos + sep.size();
				}
				//�и��Ӵ�
				std::string tmp = str.substr(offset, pos - offset);
				array->push_back(tmp);
				++count;
				//ƫ�����ƶ�
				offset = pos + sep.size();
			}
			if (offset < str.size())
			{
				array->push_back(str.substr(offset));
				++count;
			}
			return count;
		}
	//private:
	public:
		std::string _backup_file;	// �洢������Ϣ
		std::unordered_map<std::string, std::string> _table;
		// �����ļ�·�����ļ�Ψһ��ʶ��KV��ϵ
	};
}