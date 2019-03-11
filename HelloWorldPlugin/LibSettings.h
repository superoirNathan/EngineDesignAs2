#pragma once

#ifdef HELLOWORLDPLUGIN_EXPORTS
#define LIB_API __declspec(dllexport)
#elif HELLOWORLDPLUGIN_IMPORTS
#define LIB_API __declspec(dllimport)
#else
#define LIB_API
#endif