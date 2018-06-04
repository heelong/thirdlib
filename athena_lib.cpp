#include "athena_lib.h"
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <limits>
#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
void findFilename(const char *str,const char *dir, std::vector<std::string> &fileVec)//不支持中文路径
{
#ifdef _WIN32
	struct _finddata_t FileInfo;
	intptr_t HANDLEa;
	char szFind[300];
	strcpy(szFind, str);
	strcat(szFind, "\\*.");
	strcat(szFind, dir);


	char filename[300];
	strcpy_s(filename, str);


	if ((HANDLEa = _findfirst(szFind, &FileInfo)) == -1L)
		return;
	do
	{
		char filename[300];
		strcpy_s(filename, str);
		strcat_s(filename, "\\");
		strcat_s(filename, FileInfo.name);
		fileVec.push_back(filename);
		//cout << FileInfo.name << endl;
	} while (_findnext(HANDLEa, &FileInfo) == 0);

	_findclose(HANDLEa);
#else
	DIR *HANDLEa;//保存目录相关信息
	if ( !(HANDLEa = opendir(str)) )  // 获取path子目录下的所由文件和目录的列表
	{  
		return; //path指向文件,返回空 
	}
	struct dirent *FileInfo;
	char dir_t[100];
	memset(dir_t, '\0', sizeof(dir_t));
	strcat(dir_t, ".");
	strcat(dir_t, dir);  //  获取文件类型

	fileVec.clear();
	while ((FileInfo = readdir(HANDLEa)) != NULL)
	{
		
		struct stat file_stat;
		if ( strncmp(FileInfo->d_name, ".", 1) == 0 )  
		{  
		  continue;   // 忽略"."目录  
		} 
		else if (FileInfo->d_type==8)//类型为文件
		{
			std::string temp = FileInfo->d_name;
			
			std::string sub = temp.substr(temp.length() - strlen(dir_t), temp.length()-1);
			//std::cout  << sub <<" "<<dir_t<< std::endl;
			if(strncmp(sub.c_str(),dir_t,strlen(dir_t))==0)
			{
				char szFind[300];
				memset(szFind, '\0', sizeof(szFind));
				strcpy(szFind, str);
				if (!strcmp(szFind, "/"))
				{
					szFind[0] = '\0';
				}
				strcat(szFind, "/");
				strcat(szFind, FileInfo->d_name);
				if (lstat(szFind, &file_stat) < 0)//成功执行时，返回0。失败返回-1
				{
					return;
				}
				fileVec.push_back(szFind);
			}
		}
		else if(FileInfo->d_type == 10)    ///link file
		{
			continue; //忽略
		}
		else if(FileInfo->d_type == 4)    ///dir
		{
			continue; //忽略文件夹
		}
	}
	closedir(HANDLEa);
#endif
	return;
}

void _splitpath(const char *path_, const char *ext_)
{
	char drive[_MAX_DRIVE], dir[_MAX_DIR], ext[_MAX_EXT], fname[_MAX_FNAME];
	char ProjectfileName_noext[300];
	std::vector<std::string> fileVec;
	findFilename(path_, ext_, fileVec);
	for (int i = 0; i < fileVec.size(); i++)
	{
		std::cout << fileVec[i] << std::endl;
#ifdef _WIN32
		std::cout << "out put for _splitpath_s:" << std::endl;
		_splitpath_s(fileVec[i].c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
		printf("path  = %s\n", fileVec[i].c_str());
		printf("drive   = %s\n", drive);
		printf("dir   = %s\n", dir);
		printf("fname = %s\n", fname);
		printf("ext   = %s\n", ext);
		_makepath_s(ProjectfileName_noext, _MAX_PATH, drive, dir, fname, "");
		std::cout << "out put for path_s=  " << ProjectfileName_noext << std::endl;
#else
		_splitpath(fileVec[i].c_str(), drive, dir, fname, ext);
		printf("path  = %s\n", fileVec[i].c_str());
		printf("drive   = %s\n", drive);
		printf("dir   = %s\n", dir);
		printf("fname = %s\n", fname);
		printf("ext   = %s\n", ext);
		_makepath(ProjectfileName_noext, drive, dir, fname, "");
		std::cout << "out put for path_s=  " << ProjectfileName_noext << std::endl;
#endif
	}
}


