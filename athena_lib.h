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

void findFilename(const char *str,const char *dir, std::vector<std::string> &fileVec);


void _splitpath(const char *path_, const char *ext_);


#endif