//#pragma once
//获取时间
#ifndef NAV_COMMON_TIME_H_
#define NAV_COMMON_TIME_H_

#include <chrono>
#include <ostream>
#include <ratio>
#include <iostream>
using namespace std;
#include <time.h> 
#include <stdio.h>


//#include "CommonHeader.h"

using TimePoint = std::chrono::system_clock::time_point;
#define GPS2UTC_leapSecond  18  //GPS-UTC=18s (Year:2017)
#define GPS2UNIX_Second   315964800  //GPS起始时间1980年1月6日，UNIX起始时间1970年1月1日，相差秒数

struct ntptime
{
	unsigned int integer; //1900年以来的秒数
	unsigned int fraction;//小数部份，单位是微秒数的4294.967296(=2^32/10^6)倍
};

double GPS_To_UTC_CurDay(int Hour, int Minutes, double Seconds, int UTCOffset = 18);

double GPSWeekSecond_To_UTC(double GPStime, int Year, int Month, int Day, int UTCOffset = 18);
double UTC_To_GPSWeekSecond(double UTCtime, int UTCOffset = 18);

double UTCDayTimeToUTC(double UTCdaytime);

double NTP_To_UTC(unsigned long long NTPtims);
double NTP_To_UTC(unsigned long long NTPtims, double CurUTCTime);


double NTP_To_UTC(ntptime NTPtims);
void UTC_To_NTP(double UTCTime, ntptime &NTPtims);
double GetSysTemUTC();

void UTC_To_HMS(double Seconds);

double UTCStringTotime(unsigned long long TimeString);



class NAVI_SYS_TIME {
public:
	NAVI_SYS_TIME(){ m_CurUTCTime = 0; TimeOffset_DevToReal = 0; start_time_ = std::chrono::system_clock::now(); bIsStop = false; }

	void SetUTCTime(double CurUTCTime);
	double GetUTCTime();

	void SetUTCTime_Computer(double CurUTCTime);
	double GetUTCTime_Computer();

	double GetStaticTime();


	bool IsStop(){ return bIsStop; }
	void Stop(){ bIsStop = true; }
	void Run(){ bIsStop = false; }


private:
	bool bIsStop;


	TimePoint start_time_;
	TimePoint end_time_;

	double TimeOffset_DevToReal;
	double m_CurUTCTime;
	//boost::lock_guard<boost::mutex> lockGuard;
};


inline double  GPS2UNIX(int GpsWeek, double GpsSecond)
{
	return GpsWeek*86400.0*7.0 + GpsSecond + GPS2UNIX_Second - GPS2UTC_leapSecond;
};

#endif  // CARTOGRAPHER_COMMON_TIME_H_
