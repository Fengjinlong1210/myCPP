#pragma once
#include <ctime>
#include "util.h"
#include "dataManager.h"
#include "httplib.h"

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

		void RunModule()
		{
			//ѭ����ȡ�����ļ�Ŀ¼���ж��Ƿ���Ҫ�ϴ�������Ҫ�ϴ��Ľ����ϴ�
			while (1)
			{
				// 1. ���������ļ��У���ȡ���б����ļ�
				FileUtil fu(_back_dir);
				std::vector<std::string> files;
				fu.ScanDirectory(&files);
				// 2. ����ж��Ƿ���Ҫ�ϴ�
				for (auto& file : files)
				{
					if (!IsNeedUpload(file))
					{
						continue;
					}

					if (Upload(file))
					{
						//�ϴ��ɹ�������ļ�������Ϣ
						_data_mgr->Insert(file, GetFileId(file));
						std::cout << file << " upload success" << std::endl;
					}
				}
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << "loop once" << std::endl;
			}
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

		bool Upload(const std::string& filename)
		{
			// 1. ��ȡ�ļ�����
			FileUtil fu(filename);
			std::string body;
			fu.GetContent(&body);
			// 2. �����ͻ�������
			httplib::Client client(SERVER_HOST, SERVER_PORT);
			// 3. ��ӱ�ͷ�� ����
			httplib::MultipartFormData item;
			item.content = body;
			item.content_type = "application/octet-stream";
			item.filename = fu.FileName();
			item.name = "file";
			httplib::MultipartFormDataItems items;
			items.push_back(item);
			// 4. ��������
			auto ret = client.Post("/upload", items);
			if (!ret || ret->status != 200)
			{
				std::cout << "Upload:: client upload error" << std::endl;
				return false;
			}
			std::cout << "Upload:: client upload success" << std::endl;
			return true;
		}

		bool IsNeedUpload(const std::string& filename)
		{
			// �ж��ļ��Ƿ���Ҫ�ϴ������������ļ���Ϣ
			//1. �ǲ������ļ� 2. ��û���޸Ĺ�
			std::string ID;
			if (_data_mgr->GetOneByKey(filename, &ID) != false)
			{
				// �и��ļ��ı�����Ϣ���ж��Ƿ���Ҫ�����ϴ�
				std::string new_ID = GetFileId(filename);
				if(ID == new_ID)
				{
					// �ļ�û�б��޸�
					return false;
				}
			}

			//���һ�����ļ������ϴ�����ÿ�ζ���Ҫ�����ϴ�
			// ����Ҫ�ж��ļ��Ƿ���һ��ʱ����û�б��޸Ĺ�������Ҫ�ϴ�
			FileUtil fu(filename);
			if (time(nullptr) - fu.LastModifyTime() < 3)
			{
				return false;
			}
			std::cout << filename << " need upload" << std::endl;
			return true;
		}


	private:
		//����·��
		std::string _back_dir;
		DataManager* _data_mgr;
	};
}