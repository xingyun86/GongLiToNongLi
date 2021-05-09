// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <string>
#include <time.h>
#include <SolarLunarConverter.h>

#ifndef _USRDLL
#define EXPORT_API  _declspec(dllimport)
#else
#define EXPORT_API  _declspec(dllexport)
#endif
//通用版将wstring转化为string
__inline 
std::string W_To_A(const std::wstring& ws, unsigned int cp = CP_ACP)
{
    if (!ws.empty())
    {
        std::string s(WideCharToMultiByte(cp, 0, ws.data(), -1, NULL, 0, NULL, NULL), ('\0'));
        return s.substr(0, WideCharToMultiByte(cp, 0, ws.c_str(), -1, (LPSTR)s.data(), (int)s.size(), NULL, NULL) - 1);
    }
    return ("");
}
//通用版将string转化为wstring
__inline 
std::wstring A_To_W(const std::string& s, unsigned int cp = CP_ACP)
{
    if (!s.empty())
    {
        std::wstring ws(MultiByteToWideChar(cp, 0, s.data(), -1, NULL, 0), (L'\0'));
        return ws.substr(0, MultiByteToWideChar(cp, 0, s.data(), -1, (LPWSTR)ws.data(), (int)ws.size()) - 1);
    }
    return (L"");
}
time_t date2uinx(const char(&date)[9])
{
    struct tm tm = { 0 };
    sscanf(date, "%04d%02d%02d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon--;
    return mktime(&tm);
}
const char* unix2date(char(&date)[9], const time_t& t)
{
    memset(date, '\0', 9);
    struct tm tm = { 0 };
    localtime_s(&tm, &t);
    strftime(date, 9, "%Y%m%d", &tm);
    return date;
}
void GongLiToNongLi(
    char(&lunar_hour)[5], 
    char(&lunar_day)[5], 
    char(&lunar_month)[9], 
    char(&lunar_year_era)[7], 
    char(&lunar_year_zodiac)[5], 
    const char* calendar = "19980101")
{
    const char* m_TianGan[] = {
        "甲",
        "乙",
        "丙",
        "丁",
        "戊",
        "己",
        "庚",
        "辛",
        "壬",
        "癸",
    };
    const char* m_DiZhi[] = {
        "子",
        "丑",
        "寅",
        "卯",
        "辰",
        "巳",
        "午",
        "未",
        "申",
        "酉",
        "戌",
        "亥",
    };
    const char* m_ShuXiang[] = {
        "鼠",
        "牛",
        "虎",
        "兔",
        "龙",
        "蛇",
        "马",
        "羊",
        "猴",
        "鸡",
        "狗",
        "猪",
    };
    const int m_TimeSection[] = {
        2300,59,
        100,259,
        300,459,
        500,659,
        700,859,
        900,1059,
        1100,1259,
        1300,1459,
        1500,1659,
        1700,1859,
        1900,2059,
        2100,2259,
    };
    const char* m_DayName[] = {
      "*",
      "初一","初二","初三","初四","初五",
      "初六","初七","初八","初九","初十",
      "十一","十二","十三","十四","十五",
      "十六","十七","十八","十九","二十",
      "廿一","廿二","廿三","廿四","廿五",
      "廿六","廿七","廿八","廿九","三十",
    };
    const char* m_MonthName[] = { "*",
        "正","二","三","四","五","六","七","八","九","十","十一","腊",
    };

    Solar solar = { 0 };
    char calendar_date[9] = { 0 }, czYear[5] = { 0 }, czMonth[3] = { 0 }, czDay[3] = { 0 };
    memcpy(calendar_date, calendar, 8);
    if (strlen(calendar) == 12)
    {
        char time_section[5] = { 0 };
        char szDate[9] = { 0 };
        memcpy(time_section, calendar + 8, 4);
        int nTimeSection = atoi(time_section);
        if (m_TimeSection[0] <= nTimeSection && nTimeSection < 2400)
        {
            sprintf(lunar_hour, "%s时", m_DiZhi[0]);
            strcpy(calendar_date, unix2date(szDate, date2uinx(calendar_date) + 86400));
        }
        else
        {
            if (nTimeSection <= m_TimeSection[1] && nTimeSection >= 0)
            {
                sprintf(lunar_hour, "%s时", m_DiZhi[0]);
            }
            else
            {
                for (int i = 2; i < (int)sizeof(m_TimeSection) / sizeof(*m_TimeSection); i += 2)
                {
                    if (m_TimeSection[i] <= nTimeSection && nTimeSection <= m_TimeSection[i + 1])
                    {
                        sprintf(lunar_hour, "%s时", m_DiZhi[i / 2]);
                        break;
                    }
                }
            }
        }
    }
    solar.solarYear = atoi((const char*)memcpy(czYear, calendar_date, 4));
    solar.solarMonth = atoi((const char*)memcpy(czMonth, calendar_date + 4, 2));
    solar.solarDay = atoi((const char*)memcpy(czDay, calendar_date + 6, 2));
    Lunar lunar = CSolarLunarConverter::SolarToLunar(solar);

    sprintf(lunar_day, "%s", m_DayName[lunar.lunarDay]);

    if (lunar.lunarMonth < 1)
    {
        sprintf(lunar_month, "闰%s月", m_MonthName[-1 * lunar.lunarMonth]);
    }
    else
    {
        sprintf(lunar_month, "%s月", m_MonthName[lunar.lunarMonth]);
    }
    sprintf(lunar_year_era, "%s%s年", m_TianGan[((lunar.lunarYear - 4) % 60) % 10], m_DiZhi[((lunar.lunarYear - 4) % 60) % 12]);
    sprintf(lunar_year_zodiac, "%s年", m_ShuXiang[((lunar.lunarYear - 4) % 60) % 12]);
}

extern "C" 
{
    EXPORT_API void __stdcall GL2NLA(char* p_lunar_hour,
        char* p_lunar_day,
        char* p_lunar_month,
        char* p_lunar_year_era,
        char* p_lunar_year_zodiac,
        const char* p_calendar)
    {
        char lunar_hour[5] = { 0 };
        char lunar_day[5] = { 0 };
        char lunar_month[9] = { 0 };
        char lunar_year_era[7] = { 0 };
        char lunar_year_zodiac[5] = { 0 };
        GongLiToNongLi(lunar_hour, lunar_day, lunar_month, lunar_year_era, lunar_year_zodiac, p_calendar);
        if (p_lunar_hour != nullptr)
        {
            strcpy(p_lunar_hour, lunar_hour);
        }
        if (p_lunar_day != nullptr)
        {
            strcpy(p_lunar_day, lunar_day);
        }
        if (p_lunar_month != nullptr)
        {
            strcpy(p_lunar_month, lunar_month);
        }
        if (p_lunar_year_era != nullptr)
        {
            strcpy(p_lunar_year_era, lunar_year_era);
        }
        if (p_lunar_year_zodiac != nullptr)
        {
            strcpy(p_lunar_year_zodiac, lunar_year_zodiac);
        }
    }
    EXPORT_API void __stdcall GL2NLW(wchar_t* p_lunar_hour,
        wchar_t* p_lunar_day,
        wchar_t* p_lunar_month,
        wchar_t* p_lunar_year_era,
        wchar_t* p_lunar_year_zodiac,
        const wchar_t* p_calendar)
    {
        char lunar_hour[5] = { 0 };
        char lunar_day[5] = { 0 };
        char lunar_month[9] = { 0 };
        char lunar_year_era[7] = { 0 };
        char lunar_year_zodiac[5] = { 0 };
        GongLiToNongLi(lunar_hour, lunar_day, lunar_month, lunar_year_era, lunar_year_zodiac, W_To_A(p_calendar).c_str());
        if (p_lunar_hour != nullptr)
        {
            wcscpy(p_lunar_hour, A_To_W(lunar_hour).c_str());
        }
        if (p_lunar_day != nullptr)
        {
            wcscpy(p_lunar_day, A_To_W(lunar_day).c_str());
        }
        if (p_lunar_month != nullptr)
        {
            wcscpy(p_lunar_month, A_To_W(lunar_month).c_str());
        }
        if (p_lunar_year_era != nullptr)
        {
            wcscpy(p_lunar_year_era, A_To_W(lunar_year_era).c_str());
        }
        if (p_lunar_year_zodiac != nullptr)
        {
            wcscpy(p_lunar_year_zodiac, A_To_W(lunar_year_zodiac).c_str());
        }
    }
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

