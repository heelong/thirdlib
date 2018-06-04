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

void findFilename(const char *str,const char *dir, std::vector<std::string> &fileVec);


void _splitpath(const char *path_, const char *ext_);


#endif