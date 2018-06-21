#include "navi_stdlib.h"
#include "athena_lib.h"
#include "mytime.h"
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include<sys/time.h>
#include<unistd.h>	
#endif
using namespace std;
int main()
{
    std::cout << "char\t" << sizeof(char) << std::endl;
    std::cout << "unsigned char\t" << sizeof(unsigned char) << std::endl;
    std::cout << "char*\t" << sizeof(char*) << std::endl << std::endl;

    std::cout << "int\t" << sizeof(int) << std::endl;
    std::cout << "unsigned int\t" << sizeof(unsigned int) << std::endl;
    std::cout << "short\t" << sizeof(short) << std::endl;
    std::cout << "unsigned short\t" << sizeof(unsigned short) << std::endl;
    std::cout << "long\t" << sizeof(long) << std::endl;
    std::cout << "unsigned long\t" << sizeof(unsigned long) << std::endl;
	std::cout << "unsigned long int\t" << sizeof(unsigned long int) << std::endl;
    std::cout << "long long\t" << sizeof(long long) << std::endl ;
	std::cout << "unsigned long long\t" << sizeof(unsigned long long) << std::endl << std::endl;
	std::cout << "unsigned long long int\t" << sizeof(unsigned long long int) << std::endl << std::endl;
    std::cout << "float\t" << sizeof(float) << std::endl;
    std::cout << "double\t" << sizeof(double) << std::endl;
    std::cout << "long double\t" << sizeof(long double) << std::endl << std::endl;
	std::cout << "string\t" << sizeof(string) << std::endl << std::endl;

	char str[250] = "D:\\workLearning";
	char dir[250] = "docx";
	navi_splitpath(str, dir);

	int i = 1024;
	char b[33], bs[33],c[33];
	itoa_bin(i,c);
	std::cout << c << std::endl;
	_itoa_s(i, b, 2);
	sprintf_s(bs, "%032s", b);
	printf("i=%d, bs=%s\n", i, bs);

	//size_t len;
	//char  b[256] = "F:\\adasis_v2\\中文\\FDNaviLib_win32_0528150100\\ADASRoute.dat";
	//std::cout << b << std::endl;
	//len = navi_strlen(b);
	//std::cout << "test for navi_strlen: " << len << std::endl;
	//char c[50];
	//std::cout << "test for navi_strncpy: " << navi_strncpy(c, b, 13) << std::endl;
	//wchar_t *a = new wchar_t[250];
	//a = L"root\\home\\桌面\\test.txt";
	//size_t targetSize2 = 0;
	//std::cout << "test for navi_char2wchar: ";
	////navi_char2wchar(b, a, targetSize2);
	//std::wcout << a << std::endl;
	//std::cout << std::endl;
	//
	//size_t targetSize=0;
	//navi_wchar2char(a,target,targetSize);
	//std::cout << "test for navi_wchar2char: " << "16bit char to 8bit char--" << target << std::endl;
	//navi_wcscat(a,target2);
	//std::cout << "test for navi_wcscat: ";
	//size_t lena = navi_wcslen(a);
	//for (size_t i = 0; i < lena; i++)
	//	std::cout << char(a[i]);
	//std::cout << std::endl;
	//navi_strcat(b, target);
	//std::cout << "test for navi_strcat: ";
	//size_t lenb = navi_strlen(b);
	//std::cout <<"len"<< lenb;
	//std::cout << std::endl;
	//std::cout << "test for navi_strcmp: ";
	//std::cout << b << std::endl << target << std::endl;
	//std::cout << navi_strcmp(target, b) << std::endl;
	//
	//char nums[256] = "61010651580245767";
	//int64 //num = navi_atoi(nums);
	//num = navi_atoi64(nums);

	//std::cout << "test for DateTime_fromTimestamp ";
	//int64 timestamp = 0; DateTime dt; //dt.setAsNow();
	//DateTime_fromTimestamp(timestamp,&dt);
	//std::cout << "today is  UTC:" << dt.m_year << " " << dt.m_month << " " << dt.m_day << "   "
	//	<< dt.m_hours << ":" << dt.m_minutes << ":" << dt.m_seconds << std::endl;

	//std::cout << "test for navi_encodeUtf8 :";
	//wchar_t testChar[256] = { 'I', ' ', 'a', 'm', ' ', 'h', 'a', 'p', 'p', 'y' };	
	//size_t dest1Size = 	navi_encodeUtf8(testChar, 0,NULL,0);
	//char* dest1 = new char[dest1Size + 1];
	//int aaa = 0;
	//navi_encodeUtf8(testChar, 0, dest1, dest1Size+1);
	//std::cout << dest1 << std::endl;
	//std::cout << "test for navi_decodeUtf8 :";
	//size_t dest2Size = navi_decodeUtf8(dest1, 0, NULL, 0);
	//wchar_t* dest2 = new wchar_t[dest2Size + 1];
	//navi_decodeUtf8(dest1, 0, dest2, dest2Size+1);
	//std::wcout << dest2 << std::endl;
	//std::cout << "test for navi_encodeUtf8 :";
	//size_t dest3Size = navi_encodeUtf8(dest2, 0, NULL, 0);
	//char* dest3 = new char[dest3Size + 1];//需要得到转换后的字符数
	//navi_encodeUtf8(dest2, 0, dest3, dest3Size+1);
	//std::cout << dest3 << std::endl;
	//delete []dest1;
	//delete []dest2; 
	//delete []dest3;
	//std::cout << "end" << std::endl;
	return 0;
}