// GongLiToNongLi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <SolarLunarConverter.h>

int main(int argc, char ** argv)
{
    std::cout << "Hello World!" << std::endl;
    Solar solar;
    //const char* calendar = "20210402";// 0001";
    const char* calendar = "20140521";// 0001";// 0001";

    char lunar_hour_era[5] = { 0 };
    char lunar_day[7] = { 0 };
    char lunar_day_era[7] = { 0 };
    char lunar_month[9] = { 0 };
    char lunar_month_era[7] = { 0 };
    char lunar_year_era[7] = { 0 };
    char lunar_year_zodiac[7] = { 0 };
    char constell[7] = { 0 };
    char weekday[7] = { 0 };

    CalendarToSolar(&solar, calendar);
    GongLiToNongLi(lunar_hour_era, lunar_day, lunar_day_era, lunar_month, lunar_month_era, lunar_year_era, lunar_year_zodiac, &solar);
    std::cout << calendar << "---" << lunar_hour_era << "," << lunar_day << "," << lunar_day_era << "," << lunar_month << "," << lunar_month_era << "," << lunar_year_era << "," << lunar_year_zodiac << "," << GetConstell(constell, solar.solarMonth, solar.solarDay) << "," << GetWeekDay(weekday, solar.solarYear, solar.solarMonth, solar.solarDay) << std::endl;
    HMODULE hModule = LoadLibraryW((sizeof(void*) == sizeof(double)) ? L"GL2NL64" : L"GL2NL32");
    if (hModule != nullptr)
    {
        typedef void(__stdcall* PFN_GL2NLA)(char* lunar_hour_era, char* lunar_day, char* lunar_day_era, char* lunar_month, char* lunar_month_era, char* lunar_year_era, char* lunar_year_zodiac, char* constell, char*weekday, const char* calendar);
        PFN_GL2NLA fnGL2NLA = (PFN_GL2NLA)GetProcAddress(hModule, "GL2NLA");
        if (fnGL2NLA != nullptr)
        {
            const char* calendar = "201405211103";
            char lunar_hour_era[5] = { 0 };
            char lunar_day[7] = { 0 };
            char lunar_day_era[7] = { 0 };
            char lunar_month[9] = { 0 };
            char lunar_month_era[7] = { 0 };
            char lunar_year_era[7] = { 0 };
            char lunar_year_zodiac[7] = { 0 };
            char constell[7] = { 0 };
            char weekday[7] = { 0 };
            fnGL2NLA(lunar_hour_era, lunar_day, lunar_day_era, lunar_month, lunar_month_era, lunar_year_era, lunar_year_zodiac, constell, weekday, calendar);
            std::cout << calendar << "---" << lunar_hour_era << "," << lunar_day << "," << lunar_day_era << "," << lunar_month << "," << lunar_month_era << "," << lunar_year_era << "," << lunar_year_zodiac << "," << constell << "," << weekday << std::endl;
        }
        typedef void(__stdcall* PFN_GL2NLW)(wchar_t* lunar_hour_era, wchar_t* lunar_day, wchar_t* lunar_day_era, wchar_t* lunar_month, wchar_t* lunar_month_era, wchar_t* lunar_year_era, wchar_t* lunar_year_zodiac, wchar_t* constell, wchar_t* weekday, const wchar_t* calendar);
        PFN_GL2NLW fnGL2NLW = (PFN_GL2NLW)GetProcAddress(hModule, "GL2NLW");
        if (fnGL2NLW != nullptr)
        {
            const wchar_t* calendar = L"201405211103";
            wchar_t lunar_hour_era[5] = { 0 };
            wchar_t lunar_day[7] = { 0 };
            wchar_t lunar_day_era[7] = { 0 };
            wchar_t lunar_month[9] = { 0 };
            wchar_t lunar_month_era[7] = { 0 };
            wchar_t lunar_year_era[7] = { 0 };
            wchar_t lunar_year_zodiac[7] = { 0 };
            wchar_t constell[7] = { 0 };
            wchar_t weekday[7] = { 0 };
            fnGL2NLW(lunar_hour_era, lunar_day, lunar_day_era, lunar_month, lunar_month_era, lunar_year_era, lunar_year_zodiac, constell, weekday, calendar);
            std::cout << W_To_A(calendar) << "---" << W_To_A(lunar_hour_era) << "," << W_To_A(lunar_day) << "," << W_To_A(lunar_day_era) << "," << W_To_A(lunar_month) << "," << W_To_A(lunar_month_era) << "," << W_To_A(lunar_year_era) << "," << W_To_A(lunar_year_zodiac) << "," << W_To_A(constell) << "," << W_To_A(weekday) << std::endl;
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
