#ifdef  _WINDOWS_SOURCE
#ifdef  __caa-demo
#define ExportedBycaa-demo     __declspec(dllexport)
#else
#define ExportedBycaa-demo     __declspec(dllimport)
#endif
#else
#define ExportedBycaa-demo
#endif
