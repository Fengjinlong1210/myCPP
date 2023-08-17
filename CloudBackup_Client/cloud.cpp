#define _CRT_SECURE_NO_WARNINGS 1
#include "dataManager.h"
#include "util.h"
#define BACKUP_FILE "./backup.dat"

int main()
{
	//Cloud::FileUtil fu("./");
	//std::vector<std::string> array;
	//fu.ScanDirectory(&array);
	//Cloud::DataManager dataMgr(BACKUP_FILE);
	//for (auto& file : array)
	//{
	//	dataMgr.Insert(file, "TEST431ES13casTEAICSA32EIONCIAWJ123DDODafA");
	//}
	Cloud::DataManager dataMgr(BACKUP_FILE);
	std::string str;
	dataMgr.GetOneByKey(".\\cloud.cpp", &str);
	std::cout << str << std::endl;
	auto it = dataMgr._table.begin();
	while (it != dataMgr._table.end())
	{
		std::cout << it->first << " " << it->second << std::endl;
		++it;
	}
	return 0;
}