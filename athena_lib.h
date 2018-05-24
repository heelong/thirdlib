#ifndef ATHENA_LIB_FILE_H_
#define ATHENA_LIB_FILE_H_


#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#ifdef _WIN32
#include <io.h>
#else
#include <sys/io.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif


void findFilename(char *str, char *dir, std::vector<std::string> &fileVec);
#include <stdio.h>
#include <string.h>

#ifndef WIN32
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);

static void _split_whole_name(const char *whole_name, char *fname, char *ext);
#endif

/* main test */
int main(void)
{
	char *path = "/home/test/dir/f123.txt";
	// char *path = "/home/test/dir/123.txt";
	// char *path = "/home/test/dir/123";
	// char *path = "123";
	// char *path = "123.txt";

	char drive[128];
	char dir[128];
	char fname[128];
	char ext[128];

	_splitpath(path, drive, dir, fname, ext);
	printf("path  = %s\n", path);
	printf("dir   = %s\n", dir);
	printf("fname = %s\n", fname);
	printf("ext   = %s\n", ext);

	return 0;
}
/*
int err = _splitpath_s(SrcFilePath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
if (err)
return 111;

err = _makepath_s(dirtmp, _MAX_PATH, drive, dir, fname, "");
*/
#ifndef WIN32
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);

static void _split_whole_name(const char *whole_name, char *fname, char *ext);

#endif

#endif