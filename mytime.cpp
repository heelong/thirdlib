
//  获取时间
#include "mytime.h"
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include<sys/time.h>
#include<unistd.h>	
#endif


#define JAN_1970      0x83aa7e80   //  1970年1月1日与1900年1月1日的秒数的十六机制数

using std::chrono::duration_cast;
using std::chrono::milliseconds;  //ms
using std::chrono::microseconds;  //us
using std::chrono::nanoseconds;  //ns

 
void NAVI_SYS_TIME::SetUTCTime(double CurGPSTime)
{
	m_CurUTCTime = CurGPSTime;
	TimeOffset_DevToReal = CurGPSTime - GetSysTemUTC();
	//start_time_ = std::chrono::system_clock::now();
}

double NAVI_SYS_TIME::GetUTCTime()
{
	//end_time_ = std::chrono::system_clock::now();
	//uint64_t elapsed_time = duration_cast<microseconds>(end_time_ - start_time_).count();

	return m_CurUTCTime;// +double(elapsed_time) / 1000000.0;
}

double NAVI_SYS_TIME::GetStaticTime()
{
	return m_CurUTCTime;
}

double NAVI_SYS_TIME::GetUTCTime_Computer()
{
	return GetSysTemUTC() + TimeOffset_DevToReal;
}

void NAVI_SYS_TIME::SetUTCTime_Computer(double CurUTCTime)
{
	TimeOffset_DevToReal = CurUTCTime - GetSysTemUTC();
}



double GPS_To_UTC_CurDay(int Hour, int Minutes, double Seconds, int UTCOffset)
{
	double Time;

	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);
#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif
	timeinfo.tm_hour = Hour + 8;
	timeinfo.tm_min = Minutes;
	timeinfo.tm_sec = int(Seconds);

	long long ltime;
	ltime = mktime(&timeinfo);  //年月日转UTC时间

	Time = ltime + (Seconds - int(Seconds)) - UTCOffset;

	return Time;
}

//注意：
double GPSWeekSecond_To_UTC(double GPStime, int Year, int Month, int Day, int UTCOffset)
{
	double Time;

	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);

#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif

	int nGPS = int(GPStime);
	int Day2 = nGPS / (24*3600);
	nGPS -= Day2 * (24 * 3600);
	int Hour2 = nGPS / 3600;
	nGPS -= Hour2 * 3600;
	int Minutes2 = nGPS/60;
	nGPS -= Minutes2 * 60;
	int Seconds2 = nGPS;


	timeinfo.tm_hour = Hour2 + 8;
	timeinfo.tm_min = Minutes2;
	timeinfo.tm_sec = Seconds2;
	timeinfo.tm_mday = 0;
	timeinfo.tm_wday = Day2;

	timeinfo.tm_year = Year -1900;
	timeinfo.tm_mon  = Month-1;
	timeinfo.tm_mday = Day;



	long long ltime;
	ltime = mktime(&timeinfo);  //年月日转UTC时间

	Time = ltime + (GPStime - int(GPStime)) - UTCOffset;

	return Time;
}

double UTCDayTimeToUTC(double UTCdaytime)
{
	double Time;

	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);

#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif

	int nGPS = int(UTCdaytime);
	int Day2 = nGPS / (24 * 3600);
	nGPS -= Day2 * (24 * 3600);
	int Hour2 = nGPS / 3600;
	nGPS -= Hour2 * 3600;
	int Minutes2 = nGPS / 60;
	nGPS -= Minutes2 * 60;
	int Seconds2 = nGPS;


	timeinfo.tm_hour = Hour2 + 8;
	timeinfo.tm_min = Minutes2;
	timeinfo.tm_sec = Seconds2;


	long long ltime;
	ltime = mktime(&timeinfo);  //年月日转UTC时间

	Time = ltime + (UTCdaytime - int(UTCdaytime));

	double ccc = GetSysTemUTC() - Time;
	return Time;
}


double UTCStringTotime(unsigned  long long TimeString)
{
	double Time;

	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);

#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif

	int mmm = TimeString % 1000000;
	timeinfo.tm_hour = int(mmm / 10000);
	mmm -= timeinfo.tm_hour * 10000;
	timeinfo.tm_min = int(mmm / 100);;
	mmm -= timeinfo.tm_min * 100;
	timeinfo.tm_sec = mmm;


	long long ltime;
	ltime = mktime(&timeinfo);  //年月日转UTC时间

	return ltime;
}




double UTC_To_GPSWeekSecond(double UTCtime, int UTCOffset)
{
	double Time;

	time_t rawtime = time_t(UTCtime);
	struct tm  timeinfo;

#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif

	Time = double(24) * 3600 * timeinfo.tm_wday + double(3600)*(timeinfo.tm_hour - 8) + timeinfo.tm_min*double(60) + timeinfo.tm_sec + UTCOffset + (UTCtime - int(UTCtime));

	return Time;
}


//获取当前系统时间：精确到微秒
double GetSysTemUTC()
{
	double Second, usecond;
#ifdef _WIN32
	union {
		long long ns100;
		FILETIME ft;  //
	} now;
	GetSystemTimeAsFileTime(&now.ft);
	usecond = ((now.ns100 / 10LL) % 1000000LL); //微秒
	 Second= ((now.ns100 - 116444736000000000LL) / 10000000LL); //1970年以来的秒数
	//116444736000000000为1601年到1970年的秒数。windows时间从1601年开始算，最小单位是100ns，而timeval为unix时间从1970年开始算，最小单位是微秒。 
#else
	struct timeval tv;
	gettimeofday(&tv,NULL);
	usecond = tv.tv_usec;
	Second  = tv.tv_sec;
#endif	
	std::cout.precision(100);
	std::cout << "usecond:" << usecond << std::endl;
	std::cout << "Second:" << Second << std::endl;
	return Second + usecond/1000000.0;
}

void UTC_To_NTP(double UTCTime, ntptime &NTPtims)
{
	NTPtims.integer = (unsigned int)( (unsigned int)(UTCTime) + JAN_1970 );

	double usec = UTCTime - int(UTCTime);
	NTPtims.fraction = (unsigned int)(usec * 0x100000000);
}

double NTP_To_UTC(ntptime NTPtims)
{
	double Second = NTPtims.integer - JAN_1970;

	double usec = double(NTPtims.fraction) / double(4294967296);  //2^32

	return Second + usec;
}

double NTP_To_UTC(unsigned long long NTPtims)
{
	double  second = (unsigned int)(NTPtims >> 32);
	second -= JAN_1970;
	double  ussecond = double((uint32_t)(NTPtims & 0xFFFFFFFF)) / double(4294967296);

	return  second + ussecond;
}

double NTP_To_UTC(unsigned long long NTPtims, double CurUTCTime)
{
	time_t rawtime = (long long)(CurUTCTime);
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif


	double  second = (unsigned int)(NTPtims >> 32);
	double  ussecond = double((uint32_t)(NTPtims & 0xFFFFFFFF)) / double(4294967296);

	double Seconderror = timeinfo.tm_min * 60 + timeinfo.tm_sec- second;
	Seconderror = Seconderror ;
	if (Seconderror < -3000)
		Seconderror += 3600;
	if (Seconderror > 3000)
		Seconderror -= 3600;

	second = CurUTCTime - Seconderror;
	return  second + ussecond;
}


void UTC_To_HMS(double Seconds)
{
	time_t rawtime = (long long)(Seconds);
	struct tm  timeinfo;
#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
#else  
	localtime_r(&rawtime, &timeinfo);
#endif

	char pTime[200];
	sprintf(pTime, "%d%02d%02d%02d%02d%02d.%5lf", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
		timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, Seconds - int(Seconds));
	cout << pTime << endl;
}


