#include "navi_stdlib.h"
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include <limits>
#include <stdlib.h>
#include <wchar.h>

/*返回字符串长度,程序中使用时会先定义cqWCHAR* s的长度，有值的地方为非0，无值的地方为0
通过是否为0判断结尾*/
size_t cq_wcslen(const cqWCHAR* s)
{
	if(s==NULL)
		return 0;
	else
	{
		size_t len= 0;
		while ((*s++)!=0)
		{
			len++;
		}
		return len;
	}		
}
/*
判断字符数组长度
*/
size_t cq_strlen(const cqCHAR* s)
{
	if (s == NULL)
		return 0;
	else
	{
		size_t len = 0;
		while ((*s++)!='\0')
		{
			//std::cout << *s;
			len++;
		}
		return len;
	}
}

//返回值：s1，字符串s2的前count个字符拷贝到字符串s1
cqCHAR* cq_strncpy(cqCHAR* s1, const cqCHAR* s2, size_t count)
{
	if (s2 == NULL)
		return NULL;
	size_t  i = 0;
	size_t len = cq_strlen(s2);
	cqCHAR* s=s1;
	len = (len > count) ? count : len;
	while ((i < len) && ((*s2)!='\0'))
	{
		*s++ = *s2++;
		i++;
	}
	*s = '\0';
	return s1;
}

//wchar_t字符串src转为char字符串target,宽位转换为窄位需要注意溢出
void cq_wchar2char(const cqWCHAR* src, cqCHAR*target, size_t &targetSize)
{
	if (src == NULL)
		return ;
	size_t i=0;
	size_t len = cq_wcslen(src);
	cqCHAR*target_t = target;
	while (*src != 0)
	{
		//0x0080 0000,0000 1000,0000
		if (0x0080 > *src)
		{
			//const_cast;
			*target_t=static_cast <cqCHAR>(*src);//16位转换为8位窄字符
			++target_t; 
			targetSize += 1;//增加一个字节
		}
		//0x0800 0000 0111 0000,0000; 00000aaa bbbbbbbb ==> 110aaabb 10bbbbbb
		else if (0x0800 > *src)
		{
			*target_t = (static_cast <cqCHAR>(*src >> 6)) | 0xc0;//11000000，获取前八位的后面三位
			*(target_t + 1) = (static_cast <cqCHAR>(*src & 0x003F)) | 0x80;//获取后八位
			target_t += 2; 
			targetSize += 2;//增加两个字节
		}
		//aaaaaaaa bbbbbbbb ==> 1110aaaa 10aaaabb 10bbcccccc 
		else
		{
			*target_t = (static_cast <cqCHAR>(*src >> 12)) | 0xE0;
			*(target_t + 1) = (static_cast <cqCHAR>((*src & 0x0FC0) >> 6)) | 0x80;
			*(target_t + 2) = (static_cast <cqCHAR>(*src & 0x003F)) | 0x80;
			target_t += 3; 
			targetSize += 3;//增加三个字节
		}  
		++src;//挪动两个字节
	}
	*(target + targetSize) = '\0';
}

//char字符串src转为wchar_t字符串target
void cq_char2wchar(const cqCHAR* src, cqWCHAR* target, size_t &targetSize)
{
	if (src == NULL)
		return;
	size_t i = 0;
	size_t len = cq_strlen(src);
	cqWCHAR*_target = target;
	while (i < len)
	{
		*_target++ = *src++;
		i++;
	}
	targetSize = len;
}

//返回值：s1，字符串s2添加到到字符串s1的结尾
cqWCHAR* cq_wcscat(cqWCHAR* s1, const cqWCHAR* s2)
{
	if (s2 == NULL)
		return s1;
	size_t len1 = cq_wcslen(s1);
	size_t len2 = cq_wcslen(s2);
	cqWCHAR* s = s1;
	size_t i = 0;
	while (i++ < len1)
		s++;
	i = 0;
	while (i++ < len2)
		*s++ = *s2++;
	return s1;
}

//返回值：s1，字符串s2添加到到字符串s1的结尾
cqCHAR* cq_strcat(cqCHAR* s1, const cqCHAR* s2)
{
	if (s2 == NULL)
		return s1;
	cqCHAR* s = s1;
	while ((*s) != '\0')
		s++;
	while ((*s2) != '\0')
		*s++ = *s2++;
	*s = '\0';
	return s1;
}

/*当s1<s2时，返回为负数；
当s1==s2时，返回值= 0；
当s1>s2时，返回正数
*/
int32 cq_strcmp(const cqCHAR* s1, const cqCHAR* s2)
{
	while ( ((*s1) == (*s2)) && ((*s1) != '\0') && ((*s2) != '\0'))
	{
		s1++; 
		s2++;
	}
	if (((*s1) != '\0') && ((*s2) == '\0'))
		return int32(*s1);
	else if (((*s1) == '\0') && ((*s2) != '\0'))
		return -int32(*s2);
	else if (((*s1) == '\0') && ((*s2) == '\0'))
		return 0;
	else
		return int32(*s1) - int32(*s2);
}

//char字符串转int32
int32 cq_atoi(const cqCHAR* s)
{
	if (s == NULL)
		return 0;
	int flag = 1;//符号判断开关
	int64 ret=0;//需要转换的数值
	while(*s==' ')
		s++;
	if (*s=='-')
	{
		flag = -1;
	}
	if (*s == '+' || *s == '-')
	{
		s++;
	}
	while (*s!='\0'&&(*s >= '0') && (*s <= '9'))
	{
		ret = ret * 10 + *s - '0';
		if(ret>std::numeric_limits<int>::max())
		{
			if(flag==1)
				return std::numeric_limits<int>::max();
			else
				return std::numeric_limits<int>::min();
		}			
		s++;
	}
	return static_cast<int32>(ret*flag);

}

//char字符串转int64
int64 cq_atoi64(const cqCHAR* p)
{
	if (p == NULL)
		return 0;
	int flag = 1;//符号判断开关
	double ret = 0;//需要转换的数值
	while(*p==' ')
		p++;
	if (*p == '-')
	{
		flag = -1;
	}
	if (*p == '+' || *p == '-')
	{
		p++;
	}
	while (*p!='\0'&&(*p >= '0') && (*p <= '9'))
	{
		ret = ret * 10 + *p - '0';
		if(ret>std::numeric_limits<int64>::max())
		{
			if(flag==1)
				return std::numeric_limits<int64>::max();
			else
				return std::numeric_limits<int64>::min();
		}			
		p++;
	}
	return static_cast<int64>(ret*flag);
}

//将 Unicode(UCS-2) 字符串编码为 UTF-8 字符串 
size_t cq_encodeUtf8(const cqWCHAR* src, size_t srcSize, cqCHAR* dest, size_t destSize)
{
	if (src == NULL)
		return 0;
	cqCHAR* out = dest;
	if (!dest&&destSize == 0)
	{
		while (*src != 0)
		{
			if (0x0080 > *src)
				destSize += 1;//增加一个字节
			else if (0x0800 > *src)
				destSize += 2;//增加两个字节
			else
				destSize += 3;//增加三个字节
			++src;
		}
		return destSize;
	}
	size_t destSize_t = 0;
	while (*src != 0)
	{
		//0x0080 0000,0000 1000,0000
		if (0x0080 > *src)
		{
			destSize_t += 1;
			if (destSize_t >= destSize)//如果 dest 无法存放下解码后的完整结果，则只存储部分结果。
				break;
			/* 1 byte UTF-8 Character.*/
			*out = static_cast<cqCHAR>(*src);//16位转换为8位窄字符
			out += 1; 
		}
		//0x0800 0000 0111 0000,0000
		//00000aaa bbbbbbbb ==> 110aaabb 10bbbbbb
		else if (0x0800 > *src)
		{
			destSize_t += 2;//增加两个字节
			if (destSize_t >= destSize)//如果 dest 无法存放下解码后的完整结果，则只存储部分结果。
			{
				destSize_t -= 1;//无法存储该字符及后面的字符，退出
				break;
			}
			/*2 bytes UTF-8 Character.*/
			*out = (static_cast<cqCHAR>(*src >> 6)) | 0xc0;//11000000，获取前八位的后面三位
			*(out + 1) = (static_cast<cqCHAR>(*src & 0x003F)) | 0x80;//获取后八位
			out += 2; 
		}
		//aaaaaaaa bbbbbbbb ==> 1110aaaa 10aaaabb 10bbcccccc 
		else
		{
			destSize_t += 3;//增加三个字节
			if (destSize_t >= destSize)//如果 dest 无法存放下解码后的完整结果，则只存储部分结果。
			{
				destSize_t -= 2;//无法存储该字符及后面的字符，退出
				break;
			}
			/* 3 bytes UTF-8 Character .*/
			*out = (static_cast<cqCHAR>(*src >> 12)) | 0xE0;
			*(out + 1) = (static_cast<cqCHAR>((*src & 0x0FC0) >> 6)) | 0x80;
			*(out + 2) = (static_cast<cqCHAR>(*src & 0x003F)) | 0x80;
			out += 3; 	
		}
		++src;//挪动两个字节  
	}
	*out = '\0';//
	//*(dest + destSize) = '\0';//
	return destSize_t;
}

//将 UTF-8 字符串解码为 Unicode(UCS-2) 字符串
size_t cq_decodeUtf8(const cqCHAR* src, size_t srcSize, cqWCHAR* dest, size_t destSize)
{
	if (src == NULL)
		return 0;
	cqWCHAR temp1, temp2,* dest_t = dest;
	cqCHAR* in = const_cast<cqCHAR*>(src);
	//destSize = 0;
	if (!dest_t&&destSize == 0)
	{
		while (*in != 0)
		{
			if (0x00 == (*in & 0x80))
				in += 1;
			else if (0xc0 == (*in & 0xe0)/*前两位为11*/ && 0x80 == (*(in + 1) & 0xc0)/*前两位为10*/)
				in += 2;
			else if (0xe0 == (*in & 0xf0) &&0x80 == (*(in + 1) & 0xc0) &&0x80 == (*(in + 2) & 0xc0))
				in += 3;
			else //对于UCS-2，仅仅有2 ^ 16个字符，只需要三个字节就可以
				break;
			destSize += 1;
		}
		return destSize;
	}
	size_t destSize_t = 0;
	while (*in != 0)
	{
		destSize_t += 1;
		if (destSize_t >= destSize)//如果 dest 无法存放下解码后的完整结果，则只存储部分结果。
			break;
		//1字节 0xxxxxxx  
		//0x80=1000,0000，判断*in是否与0x80相等->判断最高位是否为0，如果为0，那么是ASCII字符  
		//不需要处理，直接拷贝即可  0xxxxxxx ==> 00000000 0xxxxxxxx
		if (0x00 == (*in & 0x80))
		{
			*dest_t = static_cast<cqWCHAR>(*in);
			in += 1;
		}
		//2字节 110xxxxx 10xxxxxx   
		//0xe0=1110,0000  
		//0xc0=1100,0000  110xxxxx 10yyyyyy ==> 00000xxx xxyyyyyy
		else if (0xc0 == (*in & 0xe0)/*前两位为11*/ && 0x80 == (*(in + 1) & 0xc0)/*前两位为10*/)
		{
			//0x1f=0001,1111，获得第一个字节的后5位  
			temp1 = static_cast<cqWCHAR>(*in & 0x1f);//此处需要宽字符，16位
			//左移6位  
			temp1 <<= 6;//temp1乘以2的6次方
			//0x3f=0011,1111，获得第二个字节的后6位,加上上面的5位一共有11位  
			temp1 |= static_cast<cqWCHAR>(*(in + 1) & 0x3f);
			*dest_t = temp1;
			in += 2;
		}
		//3字节 1110xxxx 10xxxxxx 10xxxxxx  
		//中文要进入这一个分支  1110xxxx 10yyyyyy 10zzzzzz ==> xxxxyyyy yyzzzzzz
		else if (0xe0 == (*in & 0xf0) &&0x80 == (*(in + 1) & 0xc0) &&0x80 == (*(in + 2) & 0xc0))
		{
			//0x0f=0000,1111,  取出第一个字节的低4位  
			temp1 = static_cast<cqWCHAR>(*in & 0x0f);
			temp1 <<= 12;
			//0x3f=0011,1111,取得第二个字节的低6位  
			temp2 = static_cast<cqWCHAR>(*(in + 1) & 0x3F);
			temp2 <<= 6;
			//取得第三个字节的低6位，最后组成16位  
			temp1 = temp1 | temp2 | static_cast<cqWCHAR>(*(in + 2) & 0x3F);
			*dest_t = temp1;
			in += 3;//移动到下一个字符  
		}
		else //对于UCS-2，仅仅有2 ^ 16个字符，只需要三个字节就可以
		{
			*dest_t = 0x22e0;
			break;//直接退出循环  
		}
		dest_t += 1;
	}
	*dest_t = '\0';//
	return destSize_t;//返回字符数
}

//字符串分割函数
cqCHAR* cq_strtok_s(cqCHAR* buf, const cqCHAR* spliters, cqCHAR** context)
{
#ifdef WIN32
	//调用C++库函数
	return strtok_s(buf,spliters,context);
#else
	return strtok_r(buf, spliters, context);
#endif
}
//stdlib初始化
void Stdlib_init(void)
{

}
//stdlib清理
void Stdlib_cleanup(void)
{

}

void DateTime_fromTimestamp(int64 timestamp, DateTime *dt)
{
	//UTC 协调世界时，又称为世界标准时间，如果要转换成本地时间，需要增加时区
	if (dt == NULL)
		return;
#ifdef _WIN32	
	int64 timestamp_t = timestamp;
	tm t_tm;
	_localtime64_s(&t_tm, &timestamp_t); //获取的是当地时间
	dt->m_year = t_tm.tm_year + 1900;
	dt->m_month = t_tm.tm_mon + 1;

	dt->m_day = t_tm.tm_mday;
	dt->m_hours = t_tm.tm_hour;

	dt->m_minutes = t_tm.tm_min;
	dt->m_seconds = t_tm.tm_sec;
#else  
	time_t timestamp_t = timestamp;
	tm * t_tm = localtime(&timestamp_t);
	dt->m_year = t_tm->tm_year + 1900;
	dt->m_month = t_tm->tm_mon + 1;
	dt->m_day = t_tm->tm_mday;
	dt->m_hours = t_tm->tm_hour;
	dt->m_minutes = t_tm->tm_min;
	dt->m_seconds = t_tm->tm_sec;
#endif
}
