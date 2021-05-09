// GongLiToNongLi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <SolarLunarConverter.h>

time_t date2uinx(const char (&date)[9])
{
    struct tm tm = {0};
    sscanf(date, "%04d%02d%02d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900;
    tm.tm_mon--;
    return mktime(&tm);
}
const char* unix2date(char(&date)[9], const time_t& t)
{
    struct tm tm = { 0 };
    memset(date, '\0', 9);
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
    std::cout << lunar.lunarYear << lunar.lunarMonth << lunar.lunarDay << std::endl;

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

int main(int argc, char ** argv)
{
    std::cout << "Hello World!" << std::endl;

    const char* calendar = "20210402";// 0001";

    char lunar_hour[5] = { 0 };
    char lunar_day[5] = { 0 };
    char lunar_month[9] = { 0 };
    char lunar_year_era[7] = { 0 };
    char lunar_year_zodiac[5] = { 0 };
    GongLiToNongLi(lunar_hour, lunar_day, lunar_month, lunar_year_era, lunar_year_zodiac, calendar);
    std::cout << calendar << "---" << lunar_hour << "," << lunar_day << "," << lunar_month << "," << lunar_year_era << "," << lunar_year_zodiac << std::endl;
    
    HMODULE hModule = LoadLibrary(TEXT("GL2NL32"));
    if (hModule != nullptr)
    {
        typedef void(__stdcall* PFN_GL2NLA)(char* lunar_hour, char* lunar_day, char* lunar_month, char* lunar_year_era, char* lunar_year_zodiac, const char* calendar);
        PFN_GL2NLA fnGL2NLA = (PFN_GL2NLA)GetProcAddress(hModule, "GL2NLA");
        if (fnGL2NLA != nullptr)
        {
            const char* calendarA = "202104020001";

            char lunar_hourA[5] = { 0 };
            char lunar_dayA[5] = { 0 };
            char lunar_monthA[9] = { 0 };
            char lunar_year_eraA[7] = { 0 };
            char lunar_year_zodiacA[5] = { 0 };
            fnGL2NLA(lunar_hourA, lunar_dayA, lunar_monthA, lunar_year_eraA, lunar_year_zodiacA, calendarA);
            std::cout << calendarA << "---" << lunar_hourA << "," << lunar_dayA << "," << lunar_monthA << "," << lunar_year_eraA << "," << lunar_year_zodiacA << std::endl;

        }
        typedef void(__stdcall* PFN_GL2NLW)(wchar_t* lunar_hour, wchar_t* lunar_day, wchar_t* lunar_month, wchar_t* lunar_year_era, wchar_t* lunar_year_zodiac, const wchar_t* calendar);
        PFN_GL2NLW fnGL2NLW = (PFN_GL2NLW)GetProcAddress(hModule, "GL2NLW");
        if (fnGL2NLW != nullptr)
        {
            const wchar_t* calendarW = L"202104020001";

            wchar_t lunar_hourW[5] = { 0 };
            wchar_t lunar_dayW[5] = { 0 };
            wchar_t lunar_monthW[9] = { 0 };
            wchar_t lunar_year_eraW[7] = { 0 };
            wchar_t lunar_year_zodiacW[5] = { 0 };
            fnGL2NLW(lunar_hourW, lunar_dayW, lunar_monthW, lunar_year_eraW, lunar_year_zodiacW, calendarW);
            std::cout << calendarW << "---" << lunar_hourW << "," << lunar_dayW << "," << lunar_monthW << "," << lunar_year_eraW << "," << lunar_year_zodiacW << std::endl;

        }
        FreeLibrary(hModule);
    }
    system("PAUSE");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
