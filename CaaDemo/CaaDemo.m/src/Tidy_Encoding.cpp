
#include "Tidy_Encoding.h"
#include "Tidy_UTF8String.h"
using namespace Tidy;

Encoding Encoding::UTF8 = 65001;
Encoding Encoding::Locale = 0;
Encoding Encoding::GBK = 936;

Encoding::Encoding()
{
	this->Target = 65001;
}

Encoding::Encoding(unsigned int Target)
{
	this->Target = Target;
}

UTF8String Encoding::Name()
{
	switch (Target)
	{
	case 0:
		return "Locale";
	case 65001:
		return "UTF8";
	case 936:
		return "GBK";
	default:
		return "Unknown";
	}
}

