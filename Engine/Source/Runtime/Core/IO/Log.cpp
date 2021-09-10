// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Log.h"

#include "Core/VTime.h"
#include "Platform/PlatformDetection.h"

#ifdef ICE_WIN64

#include <Windows.h>

#endif

#undef near
#undef far

namespace Iceblur
{
    void Log::Init()
    {
        m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleColor(EConsoleColor::White);
    }

    void Log::Print(const std::string& text)
    {
        SetConsoleColor(EConsoleColor::White);
        ICE_PRINT(text);
    }

    void Log::Message(const std::string& message)
    {
        SetConsoleColor(EConsoleColor::White);
        std::string out = GetFormattedTime() + " " + message;
        ICE_PRINT(out);
    }

    void Log::Info(const std::string& info)
    {
        SetConsoleColor(EConsoleColor::Blue);
        std::string out = GetFormattedTime() + " [INFO] " + info;
        ICE_PRINT(out);
    }

    void Log::Warn(const std::string& warning)
    {
        SetConsoleColor(EConsoleColor::Yellow);
        std::string out = GetFormattedTime() + " [WARNING] " + warning;
        ICE_PRINT(out);
    }

    void Log::Error(const std::string& error)
    {
        SetConsoleColor(EConsoleColor::Red);
        std::string out = GetFormattedTime() + " [ERROR] " + error;
        ICE_PRINT(out);
    }

    void Log::SetConsoleColor(EConsoleColor color)
    {
        SetConsoleTextAttribute(m_ConsoleHandle, color);
    }

    std::string Log::GetFormattedTime()
    {
        TimeData now = VTime::GetTimeNow();

        std::string formattedTime = "[" + TimeData::ToString(now.Hours) + ":"
                                    + TimeData::ToString(now.Minutes) + ":"
                                    + TimeData::ToString(now.Seconds) + "]";
        return formattedTime;
    }
}
