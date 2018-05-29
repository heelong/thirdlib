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
#include <stdio.h>
#include <string.h>

void findFilename(char *str, char *dir, std::vector<std::string> &fileVec);


#ifndef WIN32
void _splitpath(const char *path, char *drive, char *dir, char *fname, char *ext);

void _split_whole_name(const char *whole_name, char *fname, char *ext);
#endif

/*
int err = _splitpath_s(SrcFilePath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
if (err)
return 111;

err = _makepath_s(dirtmp, _MAX_PATH, drive, dir, fname, "");
*/

#endif