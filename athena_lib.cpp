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
void findFilename(char *str, char *dir, std::vector<std::string> &fileVec)//不支持中文路径
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



#ifndef WIN32
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
{
	char *p_whole_name;

	drive[0] = '\0';
	if (NULL == path)
	{
		dir[0] = '\0';
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	if ('/' == path[strlen(path)])
	{
		strcpy(dir, path);
		fname[0] = '\0';
		ext[0] = '\0';
		return;
	}

	//p_whole_name = rindex(path, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		_split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		_split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}

static void _split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;

	//p_ext = rindex(whole_name, '.');
	if (NULL != p_ext)
	{
		strcpy(ext, p_ext);
		snprintf(fname, p_ext - whole_name + 1, "%s", whole_name);
	}
	else
	{
		ext[0] = '\0';
		strcpy(fname, whole_name);
	}
}

#endif

