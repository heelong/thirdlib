#ifndef NAV_STDLIB_FILE_H_
#define NAV_STDLIB_FILE_H_


#include <stdlib.h>
#include <string>
#include <string.h>
typedef wchar_t cqWCHAR;//16位
typedef char cqCHAR;           //8位
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef short int16;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed char int8;

 struct DateTime
 {
	 int16 		m_hours;
	 int16 		m_minutes;
	 int16 		m_seconds;

	 int16 		m_year;
	 int16 		m_month;
	 int16 		m_day;
 #ifdef __cplusplus
	 static DateTime now;
	 static DateTime invalid;
	 inline void invalidate() { m_hours = m_minutes = -1; m_seconds = m_year = m_month = m_day = 0; }
	 inline bool isValid() { return m_minutes >= 0; }
	 inline void setAsNow() { m_hours = -1; m_minutes = m_seconds = m_year = m_month = m_day = 0; }
	 inline bool isNow() { return m_hours == -1 && m_minutes == 0; }
 #endif
 };


//返回字符串长度
size_t cq_wcslen(const cqWCHAR* s);

//返回字符串s的长度
size_t cq_strlen(const cqCHAR* s);

//返回值：s1，字符串s2的前count个字符拷贝到字符串s1
cqCHAR* cq_strncpy(cqCHAR* s1, const cqCHAR* s2, size_t count);

//wchar_t字符串src转为char字符串target

void cq_wchar2char(const cqWCHAR* src, cqCHAR*target, size_t &targetSize);

//char字符串src转为wchar_t字符串target
void cq_char2wchar(const cqCHAR* src, cqWCHAR* target, size_t &targetSize);

//返回值：s1，字符串s2添加到到字符串s1的结尾
cqWCHAR* cq_wcscat(cqWCHAR* s1, const cqWCHAR* s2);

//返回值：s1，字符串s2添加到到字符串s1的结尾
cqCHAR* cq_strcat(cqCHAR* s1, const cqCHAR* s2);

/*当s1<s2时，返回为负数；
当s1==s2时，返回值= 0；
当s1>s2时，返回正数
*/
int32 cq_strcmp(const cqCHAR* s1, const cqCHAR* s2);

//char字符串转int32
int32 cq_atoi(const cqCHAR* s);

//char字符串转int64
int64 cq_atoi64(const cqCHAR* p);

/**	@brief 将 Unicode(UCS-2) 字符串编码为 UTF-8 字符串 
	@param [in] src
		输入的 Unicode 字符串。
	@param [in] srcSize
		输入字符串的长度，单位：字符。如果 src 中的内容以 0 结尾，则可以将 srcSize 设为 SIZE_T_MAX。
	@param [out] dest
		编码后的 UTF-8 字符串存储在这里。
	@param [in] destSize
		dest 的可用空间大小，单位：字节。
	@return
		编码后的内容需要占用的存储空间大小(包括结尾的0)，单位：字节。
	@details
		cq_encodeUtf8() 将 src 中存储的 Unicode 字符串按 UTF-8 编码后存储到 dest 中。
		如果 dest 中的空间无法存放下编码后的完整结果，则只存储部分结果。
		只要 destSize 大于 0，就能保证函数调用后的 dest 中的内容以 0 结尾。
	@note
		用 cq_encodeUtf8(src, srcSize, NULL, 0) 获取获取 src 编码后内容需要占用的存储空间大小。
*/
size_t cq_encodeUtf8(const cqWCHAR* src, size_t srcSize, cqCHAR* dest, size_t destSize);

/**	@brief 将 UTF-8 字符串解码为 Unicode(UCS-2) 字符串
	@param [in] src
		输入的 UTF-8 字符串。
	@param [in] srcSize
		输入字符串的长度，单位：字节。如果 src 中的内容以 0 结尾，则可以将 srcSize 设为 SIZE_T_MAX。
	@param [out] dest
		解码后的 Unicode 字符串存储在这里。
	@param [in] destSize
		dest 的可用空间大小，单位：字符。
	@return
		src 中的内容解码后需要占用的存储空间大小(包括结尾的0)，单位：字符。
	@details
		cq_decodeUtf8() 将 src 中存储的 UTF-8 字符串解码后存储到 dest 中。
		如果 dest 无法存放下解码后的完整结果，则只存储部分结果。
		只要 destSize 大于 0，就能保证函数调用后 dest 中的内容以 0 结尾。
	@note
		用 cq_decodeUtf8(src, srcSize, NULL, 0) 可以获取 src 解码后内容需要占用的存储空间大小。
*/
size_t cq_decodeUtf8(const cqCHAR* src, size_t srcSize, cqWCHAR* dest, size_t destSize);


/**	@brief 对字符串进行分割
	@param [in] buf
		输入的 需要分割的字符或者字符串整体。
	@param [in] spliters
		输入分隔符（例如：,.!@#$%%^&*() \t \n之类可以区别单词的符号）。
	@param [out] context
		这个参数用来存放被分割过的字符串。
	@return
		返回当前分割的字符串	
*/
cqCHAR* cq_strtok_s(cqCHAR* buf, const cqCHAR* spliters, cqCHAR** context);

//stdlib初始化
void Stdlib_init(void);
//stdlib清理
void Stdlib_cleanup(void);
/**
	@brief
		Convert UNIX-timestamp to DateTime.
	@param [in] timestamp
		UNIX-timestamp need to be converted.
	@param [out] dt
		DateTime object.
	@remarks
		The default time zone (GMT) is zero.
		If you want to convert the timestamp to specify time zone
		Example: Beijing, DateTime_addTimeZone(&dt, 8);

		If the UNIX-timestamp is illegal, the dt will be set with 1970-1-1 00:00:00
*/
void DateTime_fromTimestamp(int64 timestamp, DateTime *dt);

#endif