#ifdef  _WINDOWS_SOURCE
#ifdef  __CaaDemo
#define ExportedByCaaDemo     __declspec(dllexport)
#else
#define ExportedByCaaDemo     __declspec(dllimport)
#endif
#else
#define ExportedByCaaDemo
#endif
