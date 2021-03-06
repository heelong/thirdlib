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
void findFilename(const char *str, const char *dir, std::vector<std::string> &fileVec)//不支持中文路径
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
	if (!(HANDLEa = opendir(str)))  // 获取path子目录下的所由文件和目录的列表
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
		if (strncmp(FileInfo->d_name, ".", 1) == 0)
		{
			continue;   // 忽略"."目录  
		}
		else if (FileInfo->d_type == 8)//类型为文件
		{
			std::string temp = FileInfo->d_name;

			std::string sub = temp.substr(temp.length() - strlen(dir_t), temp.length() - 1);
			//std::cout  << sub <<" "<<dir_t<< std::endl;
			if (strncmp(sub.c_str(), dir_t, strlen(dir_t)) == 0)
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
		else if (FileInfo->d_type == 10)    ///link file
		{
			continue; //忽略
		}
		else if (FileInfo->d_type == 4)    ///dir
		{
			continue; //忽略文件夹
		}
	}
	closedir(HANDLEa);
#endif
	return;
}
int itoa_bin(unsigned int data, char *str)
{
	if (str == NULL)
		return -1;

	char *start = str;

	while (data)
	{
		if (data & 0x1)
			*str++ = 0x31; //ASCII 1
		else
			*str++ = 0x30; //ASCII 0

		data >>= 1;
	}

	*str = 0;

	//reverse the order  
	char *low, *high, temp;
	low = start, high = str - 1;

	while (low < high)
	{
		temp = *low;
		*low = *high;
		*high = temp;

		++low;
		--high;
	}

	return 0;
}
void navi_splitpath(const char *path_, const char *ext_)
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
		splitpath(fileVec[i].c_str(), drive, dir, fname, ext);
		printf("path  = %s\n", fileVec[i].c_str());
		printf("drive   = %s\n", drive);
		printf("dir   = %s\n", dir);
		printf("fname = %s\n", fname);
		printf("ext   = %s\n", ext);
		//ProjectfileName_noext={0};
		makepath(ProjectfileName_noext, drive, dir, fname, ext);
		//char ProjectfileName_noext1[300]={0};
		//strcat(ProjectfileName_noext1,dir);
		//strcat(ProjectfileName_noext1,"/");
		//strcat(ProjectfileName_noext1,fname);
		//strcat(ProjectfileName_noext1,"");
		//makepath(ProjectfileName_noext, drive, dir, fname, "");
		std::cout << "out put for path_s=  " << ProjectfileName_noext << std::endl;
#endif
	}
}


void regionGrowingSegmenation()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	if ( pcl::io::loadPCDFile <pcl::PointXYZ> ("D:\\work\\stdtest\\original\\car.pcd", *cloud) == -1)
	{
		std::cout << "Cloud reading failed." << std::endl;
		return ;
	}
	clock_t start, finish;
	start = clock();
	pcl::search::Search<pcl::PointXYZ>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZ> > (new pcl::search::KdTree<pcl::PointXYZ>);
	pcl::PointCloud <pcl::Normal>::Ptr normals (new pcl::PointCloud <pcl::Normal>);
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normal_estimator;
	normal_estimator.setSearchMethod (tree);
	normal_estimator.setInputCloud (cloud);
	normal_estimator.setKSearch (50);
	normal_estimator.compute (*normals);

	pcl::IndicesPtr indices (new std::vector <int>);
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud (cloud);
	pass.setFilterFieldName ("z");
	pass.setFilterLimits (0.0, 1.0);
	pass.filter (*indices);

	pcl::RegionGrowing<pcl::PointXYZ, pcl::Normal> reg;
	reg.setMinClusterSize (50);
	reg.setMaxClusterSize (1000000);
	reg.setSearchMethod (tree);
	reg.setNumberOfNeighbours (30);
	reg.setInputCloud (cloud);
	//reg.setIndices (indices);
	reg.setInputNormals (normals);
	reg.setSmoothnessThreshold (3.0 / 180.0 * M_PI);
	reg.setCurvatureThreshold (1.0);

	std::vector <pcl::PointIndices> clusters;
	reg.extract (clusters);
	finish = clock();
	float totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	std::cout << " -------------Current Frame cluster Time:" << totaltime*1000.0 << "ms" << std::endl;
	std::cout << "Number of clusters is equal to " << clusters.size () << std::endl;
	std::cout << "First cluster has " << clusters[0].indices.size () << " points." << std::endl;
	std::cout << "These are the indices of the points of the initial" <<
		std::endl << "cloud that belong to the first cluster:" << std::endl;
	int counter = 0;
	while (counter < clusters[0].indices.size ())
	{
		std::cout << clusters[0].indices[counter] << ", ";
		counter++;
		if (counter % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;

	return ;
}

#ifndef WIN32
void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext)
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
	char*path_t = const_cast<char*>(path);
	p_whole_name = rindex(path_t, '/');
	if (NULL != p_whole_name)
	{
		p_whole_name++;
		split_whole_name(p_whole_name, fname, ext);

		snprintf(dir, p_whole_name - path, "%s", path);
	}
	else
	{
		split_whole_name(path, fname, ext);
		dir[0] = '\0';
	}
}

static void split_whole_name(const char *whole_name, char *fname, char *ext)
{
	char *p_ext;
	char*whole_name_t = const_cast<char*>(whole_name);
	p_ext = rindex(whole_name_t, '.');
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
void makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext)
{
	//path="0";
	memset(path, '\0', sizeof(path));
	if (drive[0] != '\0')
	{
		strcat(path, drive);
		strcat(path, ":");
	}
	strcat(path, dir);
	strcat(path, "/");
	strcat(path, fname);
	strcat(path, ext);
	strcat(path, "\0");
}
#endif

