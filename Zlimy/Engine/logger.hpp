#pragma once
#include <mutex>
#include <Windows.h>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#pragma warning(disable : 4996)
namespace IExtreme::Engine::Ugr
{
	class Logger
	{
	public:
		
		enum class LogPriority
		{
			Trace, Debug, Info, Warn, Error, Fatal
		};
		class Color
		{
		public:
			Color(const wchar_t* str, BYTE color, bool endline = false)
			{
				SetUTF16();
				SetConsoleTextAttribute(handle, color);
				if (endline) std::wcout << str << char(0x0A); else std::wcout << str;
				SetConsoleTextAttribute(handle, defColor);
			}
			Color(const char* str, BYTE color, bool endline = false)
			{
				SetUTF8();
				SetConsoleTextAttribute(handle, color);
				if (endline) std::cout << str << char(0x0A); else std::cout << str;
				SetConsoleTextAttribute(handle, defColor);
			}
			static inline void Init()
			{
				SetUTF16();
				handle = GetStdHandle(STD_OUTPUT_HANDLE);
				defColor = 0x07;
			}
			static inline void SetColor(BYTE color)
			{
				SetConsoleTextAttribute(handle, color);
			}
			static inline void SetUTF16()
			{
				_setmode(_fileno(stdout), _O_U16TEXT);
			}
			static inline void SetUTF8()
			{
				_setmode(_fileno(stdout), _O_TEXT);
			}
		private:
			static BYTE defColor;
			static HANDLE handle;
		};
	private:
		LogPriority pri = LogPriority::Info;
		std::mutex logMutex;
		bool logging = true;
		char buffer[80];
		const char* timestampFormat = "%T  %d-%m-%Y";

	public:
		static void Logging(bool enable)
		{
			getInstance().logging = enable;
		}
		static void Init()
		{
			Color::Init();
		}
		static void SetPriority(LogPriority pri)
		{
			getInstance().pri = pri;
		}

		static LogPriority GetPriority()
		{
			return getInstance().pri;
		}

		static void SetTimestampFormat(std::string timestampFormat)
		{
			getInstance().timestampFormat = timestampFormat.c_str();
		}

		static std::string GetTimestampFormat() 
		{
			return getInstance().timestampFormat;
		}

		template<typename... Args>
		static void Debug(const char* msg, Args... args)
		{
			getInstance().log("[Debug]    : ", LogPriority::Debug, msg, args...);
		}

		template<typename... Args>
		static void Info(const char* msg, Args... args)
		{
			getInstance().log("[Info]     : ", LogPriority::Info, msg, args...);
		}

		template<typename... Args>
		static void Trace(const char* msg, Args... args)
		{
			getInstance().log("[Trace]    : ", LogPriority::Trace, msg, args...);
		}

		template<typename... Args>
		static void Warn(const char* msg, Args... args)
		{
			getInstance().log("[Warn]     : ", LogPriority::Warn, msg, args...);
		}

		template<typename... Args>
		static void Error(const char* msg, Args... args)
		{
			getInstance().log("[Error]    : ", LogPriority::Error, msg, args...);
		}

		template<typename... Args>
		static void Fatal(const char* msg, Args... args)
		{
			getInstance().log("[Fatal]    : ", LogPriority::Fatal, msg, args...);
		}
	private:
		static Logger& getInstance()
		{
			static Logger instance;

			return instance;
		}

		Logger() {}
		Logger(const Logger&) = delete;
		Logger& operator= (const Logger&) = delete;

		~Logger()
		{

		}

		template<typename... Args>
		void log(const char* msgPriStr, LogPriority msgPri, const char* msg, Args... args)
		{
			if (pri <= msgPri && logging)
			{
				std::time_t currentTime = std::time(0);
				std::tm* timeStamp = std::localtime(&currentTime);

				switch (msgPri)
				{
				case IExtreme::Engine::Ugr::Logger::LogPriority::Trace:

					break;
				case IExtreme::Engine::Ugr::Logger::LogPriority::Debug:
					Color::Color(L"| \x26A0 | -- ", 0x06);
					Color::SetColor(0x06);
					break;
				case IExtreme::Engine::Ugr::Logger::LogPriority::Info:
					Color::Color(L"| !  | -- ", 0x09);
					Color::SetColor(0x09);
					break;
				case IExtreme::Engine::Ugr::Logger::LogPriority::Warn:
					Color::Color(L"| \x274C | -- ", 0x0E);
					Color::SetColor(0x0E);
					break;
				case IExtreme::Engine::Ugr::Logger::LogPriority::Error:
					Color::Color(L"| \x00D7 | -- ", 0x04);
					Color::SetColor(0x04);
					break;
				case IExtreme::Engine::Ugr::Logger::LogPriority::Fatal:
					Color::Color(L"| \x2716 | -- ", 0xC4);
					Color::SetColor(0xC4);
					break;
				default:
					break;
				}

				Color::SetUTF8();
				std::strftime(buffer, 80, timestampFormat, timeStamp);
				std::printf("%s    ", buffer);
				std::printf(msgPriStr);
				std::printf(msg, args...);
				std::printf("\n");

				Color::SetColor(0x07);
			}
		}
	};
}
