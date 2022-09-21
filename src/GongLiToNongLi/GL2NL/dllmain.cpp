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

extern "C" 
{
    EXPORT_API void __stdcall GL2NLA(char* p_lunar_hour_era,
        char* p_lunar_day,
        char* p_lunar_day_era,
        char* p_lunar_month,
        char* p_lunar_month_era,
        char* p_lunar_year_era,
        char* p_lunar_year_zodiac,
        char* p_constell,
        char* p_weekday,
        const char* p_calendar)
    {
        Solar solar = { 0 };
        char lunar_hour_era[5] = { 0 };
        char lunar_day[7] = { 0 };
        char lunar_day_era[7] = { 0 };
        char lunar_month[9] = { 0 };
        char lunar_month_era[7] = { 0 };
        char lunar_year_era[7] = { 0 };
        char lunar_year_zodiac[7] = { 0 };
        char constell[7] = { 0 };
        char weekday[7] = { 0 };

        CalendarToSolar(&solar, p_calendar);
        GongLiToNongLi(lunar_hour_era, lunar_day, lunar_day_era, lunar_month, lunar_month_era, lunar_year_era, lunar_year_zodiac, &solar);
        GetConstell(constell, solar.solarMonth, solar.solarDay);
        GetWeekDay(weekday, solar.solarYear, solar.solarMonth, solar.solarDay);
        if (p_lunar_hour_era != nullptr)
        {
            strcpy(p_lunar_hour_era, lunar_hour_era);
        }
        if (p_lunar_day != nullptr)
        {
            strcpy(p_lunar_day, lunar_day);
        }
        if (p_lunar_day_era != nullptr)
        {
            strcpy(p_lunar_day_era, lunar_day_era);
        }
        if (p_lunar_month != nullptr)
        {
            strcpy(p_lunar_month, lunar_month);
        }
        if (p_lunar_month_era != nullptr)
        {
            strcpy(p_lunar_month_era, lunar_month_era);
        }
        if (p_lunar_year_era != nullptr)
        {
            strcpy(p_lunar_year_era, lunar_year_era);
        }
        if (p_lunar_year_zodiac != nullptr)
        {
            strcpy(p_lunar_year_zodiac, lunar_year_zodiac);
        }
        if (p_constell != nullptr)
        {
            strcpy(p_constell, constell);
        }
        if (p_weekday != nullptr)
        {
            strcpy(p_weekday, weekday);
        }
    }
    EXPORT_API void __stdcall GL2NLW(wchar_t* p_lunar_hour_era,
        wchar_t* p_lunar_day,
        wchar_t* p_lunar_day_era,
        wchar_t* p_lunar_month,
        wchar_t* p_lunar_month_era,
        wchar_t* p_lunar_year_era,
        wchar_t* p_lunar_year_zodiac,
        wchar_t* p_constell,
        wchar_t* p_weekday,
        const wchar_t* p_calendar)
    {
        Solar solar = { 0 };
        char lunar_hour_era[5] = { 0 };
        char lunar_day[7] = { 0 };
        char lunar_day_era[7] = { 0 };
        char lunar_month[9] = { 0 };
        char lunar_month_era[7] = { 0 };
        char lunar_year_era[7] = { 0 };
        char lunar_year_zodiac[7] = { 0 };
        char constell[7] = { 0 };
        char weekday[7] = { 0 };

        CalendarToSolar(&solar, W_To_A(p_calendar).c_str());
        GongLiToNongLi(lunar_hour_era, lunar_day, lunar_day_era, lunar_month, lunar_month_era, lunar_year_era, lunar_year_zodiac, &solar);
        GetConstell(constell, solar.solarMonth, solar.solarDay);
        GetWeekDay(weekday, solar.solarYear, solar.solarMonth, solar.solarDay);
        if (p_lunar_hour_era != nullptr)
        {
            wcscpy(p_lunar_hour_era, A_To_W(lunar_hour_era).c_str());
        }
        if (p_lunar_day != nullptr)
        {
            wcscpy(p_lunar_day, A_To_W(lunar_day).c_str());
        }
        if (p_lunar_day_era != nullptr)
        {
            wcscpy(p_lunar_day_era, A_To_W(lunar_day_era).c_str());
        }
        if (p_lunar_month != nullptr)
        {
            wcscpy(p_lunar_month, A_To_W(lunar_month).c_str());
        }
        if (p_lunar_month_era != nullptr)
        {
            wcscpy(p_lunar_month_era, A_To_W(lunar_month_era).c_str());
        }
        if (p_lunar_year_era != nullptr)
        {
            wcscpy(p_lunar_year_era, A_To_W(lunar_year_era).c_str());
        }
        if (p_lunar_year_zodiac != nullptr)
        {
            wcscpy(p_lunar_year_zodiac, A_To_W(lunar_year_zodiac).c_str());
        }
        if (p_constell != nullptr)
        {
            wcscpy(p_constell, A_To_W(constell).c_str());
        }
        if (p_weekday != nullptr)
        {
            wcscpy(p_weekday, A_To_W(weekday).c_str());
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

