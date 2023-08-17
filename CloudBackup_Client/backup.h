#pragma once
#include "util.h"
#include "dataManager.h"

namespace Cloud
{
#define SERVER_HOST "43.138.29.200"
#define SERVER_PORT 8888
	class Backup
	{
	public:
		Backup(const std::string& backdir, const std::string& backup_file)
		{
			//��ʼ����Ա����
			_back_dir = backdir;
			_data_mgr = new DataManager(backup_file);
		}

		std::string GetFileId(const std::string& filename)
		{
			//�ļ�id = �ļ�·�� + �ļ���С + �ļ�mtime
			std::string ret;
			FileUtil fu(filename);
			ret += fu.FileName() + "-";
			ret += std::to_string(fu.FileSize()) + "-";
			ret += std::to_string(fu.LastModifyTime());
			return ret;
		}
	private:
		//����·��
		std::string _back_dir;
		DataManager* _data_mgr;
	};
}