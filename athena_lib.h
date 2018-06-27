#ifndef ATHENA_LIB_FILE_H_
#define ATHENA_LIB_FILE_H_


#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <vector>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing.h>


#ifdef _WIN32
#include <io.h>
#else
#include <sys/io.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
* Sizes for buffers used by the _makepath() and _splitpath() functions.
* note that the sizes include space for 0-terminator
*/
#define _MAX_PATH   260 /* max. length of full pathname */
#define _MAX_DRIVE  3   /* max. length of drive component */
#define _MAX_DIR    256 /* max. length of path component */
#define _MAX_FNAME  256 /* max. length of file name component */
#define _MAX_EXT    256 /* max. length of extension component */


#endif
#include <stdio.h>
#include <string.h>

void findFilename(const char *str, const char *dir, std::vector<std::string> &fileVec);


void navi_splitpath(const char *path_, const char *ext_);

int itoa_bin(unsigned int data, char *str);

#endif

void regionGrowingSegmenation();


#ifndef WIN32
void splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);

static void split_whole_name(const char *whole_name, char *fname, char *ext);

void makepath(char *path, const char *drive, const char *dir, const char *fname, const char *ext);
#endif