#pragma once
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <cstdio>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include <experimental/filesystem>
#include <sys/stat.h>

namespace Cloud
{
    namespace fs = std::experimental::filesystem;
    class FileUtil
    {
    public:
        FileUtil(const std::string& filename)
            : _filename(filename)
        {
        }
        // ��ȡ�ļ���С
        size_t FileSize()
        {
            // int stat(const char *path, struct stat *buf);
            struct stat st;
            int ret = stat(_filename.c_str(), &st);
            if (ret < 0)
            {
                std::cout << "FileSize::get file size failed" << std::endl;
                return 0;
            }
            return st.st_size;
        }
        // ��ȡ�ļ�������ʱ��
        time_t LastAccessTime()
        {
            struct stat st;
            int ret = stat(_filename.c_str(), &st);
            if (ret < 0)
            {
                std::cout << "LastAccessTime::get last access time failed" << std::endl;
                return -1;
            }
            return st.st_atime;
        }
        // ��ȡ�ļ�����޸�ʱ��
        time_t LastModifyTime()
        {
            struct stat st;
            int ret = stat(_filename.c_str(), &st);
            if (ret < 0)
            {
                std::cout << "LastModifyTime::get last modify time failed" << std::endl;
                return -1;
            }
            return st.st_mtime;
        }
        // ��ȡ�����ļ���
        std::string FileName()
        {
            //auto pos = _filename.rfind('/');
            //if (pos == std::string::npos)
            //{
            //    return _filename;
            //}
            //return _filename.substr(pos + 1);
            return fs::path(_filename).filename().string();
        }
        // ��ȡָ��λ�ÿ�ʼ�ƶ����ȵ�����
        bool GetPosLen(std::string* body, size_t pos, size_t len)
        {
            // �жϴ�С
            size_t fsize = FileSize();
            if (pos + len > fsize)
            {
                std::cout << "GetPosLen::get content from pos failed" << std::endl;
                return false;
            }
            // ���ļ�
            std::ifstream ifs;
            ifs.open(_filename, std::ios::binary);
            if (!ifs.is_open())
            {
                std::cout << "GetPosLen::open file failed" << std::endl;
                return false;
            }
            // ���ж�ȡ
            ifs.seekg(pos, std::ios::beg); // ��begin��ʼƫ��pos��λ��
            body->resize(len);
            ifs.read(&(*body)[0], len);
            if (!ifs.good())
            {
                std::cout << "GetPosLen::read file error" << std::endl;
                ifs.close();
                return false;
            }
            ifs.close();
            return true;
        }
        // ��ȡ�ļ�����
        bool GetContent(std::string* body)
        {
            return GetPosLen(body, 0, FileSize());
        }
        // �����ļ�����
        bool SetContent(const std::string& body)
        {
            std::ofstream ofs;
            // ���ļ�
            ofs.open(_filename, std::ios::binary);
            if (!ofs.is_open())
            {
                std::cout << "SetContent::open file failed" << std::endl;
                return false;
            }
            // д��
            ofs.write(&body[0], body.size());
            if (!ofs.good())
            {
                std::cout << "SetContent::Set content error" << std::endl;
                ofs.close();
                return false;
            }
            ofs.close();
            return true;
        }
        // �ж��ļ��Ƿ����
        bool Exists()
        {
            // �ж�·���Ƿ����
            return fs::exists(_filename);
        }
        // ����Ŀ¼
        bool CreateDirectory()
        {
            // ����·��, ����Ŀ¼
            //  ���·���Ѿ�����
            if (Exists())
                return true;
            // ·��������ʱ, ����·��
            return fs::create_directory(_filename);
        }
        // ����Ŀ¼�е��ļ�
        bool ScanDirectory(std::vector<std::string>* array)
        {
            // ��ȡ��ǰ·�������е�Ŀ¼���ļ�
            for (auto& p : fs::directory_iterator(_filename))
            {
                //  �����·��������
                if (fs::is_directory(p))
                    continue;
                // ���ļ����ݷ���vector
                array->push_back(fs::path(p).relative_path().string());
            }
            return true;
        }

        bool Remove()
        {
            if (!Exists())
            {
                std::cout << "FileUtil::Remove failed: file not found" << std::endl;
                return false;
            }
            if (remove(_filename.c_str()) != 0)
            {
                std::cout << "FileUtil::Remove::remove failed" << std::endl;
                return false;
            }
            return true;
        }
        //private:
    public:
        std::string _filename;
    };

}