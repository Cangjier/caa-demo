
#ifndef __TIDY_IO_FILEINFO_H__
#define __TIDY_IO_FILEINFO_H__
#include "Tidy_Macro.h"
#include "Tidy_LocaleString.h"
#include "Tidy_DateTime.h"
namespace Tidy
{
	namespace IO
	{
		class DirectoryInfo;
		class  FileAttributes
		{
		public:
#ifndef Tidy_IO_File_RegisterAttribute
#define Tidy_IO_File_RegisterAttribute(Name, NameStr) \
	LocaleString Get##Name() { return ReadAttribute(NameStr); }
#endif // !Tidy_IO_File_RegisterAttribute

			FileAttributes(LocaleString Target)
			{
				this->Target = Target;
			}

			LocaleString Target;

			LocaleString ReadAttribute(LocaleString Name);
			Tidy_IO_File_RegisterAttribute(CompanyName, "CompanyName");
			Tidy_IO_File_RegisterAttribute(FileDescription, "FileDescription");
			Tidy_IO_File_RegisterAttribute(FileVersion, "FileVersion");
			Tidy_IO_File_RegisterAttribute(InternalName, "InternalName");
			Tidy_IO_File_RegisterAttribute(LegalCopyright, "LegalCopyright");
			Tidy_IO_File_RegisterAttribute(OriginalFilename, "OriginalFilename");
			Tidy_IO_File_RegisterAttribute(ProductName, "ProductName");
			Tidy_IO_File_RegisterAttribute(ProductVersion, "ProductVersion");
			Tidy_IO_File_RegisterAttribute(Comments, "Comments");
			Tidy_IO_File_RegisterAttribute(LegalTrademarks, "LegalTrademarks");
		};
		class  FileInfo
		{
		public:
			FileInfo();
			FileInfo(LocaleString target);

			LocaleString Target;

		public:
			DirectoryInfo Parent();

			LocaleString Name();

			LocaleString Extension();

			LocaleString NameWithoutExtension();
            
			int Size();

			FileAttributes Attributes()
			{
				return FileAttributes(Target);
			}

			void ReName(LocaleString name);

			void MoveTo(LocaleString destPath);

			void Delete();

			void CopyTo(LocaleString destPath);

			DateTime GetLastModifiedTime();
		};
	}
}
#endif