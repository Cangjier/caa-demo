#include "Tidy_GBKString.h"
using namespace Tidy;
    GBKString::GBKString(const LocaleString& target) {
        this->TargetEncoding = 936;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    GBKString::GBKString(const LocaleString&& target) {
        this->TargetEncoding = 936;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif
    GBKString::GBKString(const UTF8String& target) {
        this->TargetEncoding = 936;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    GBKString::GBKString(const UTF8String&& target) {
        this->TargetEncoding = 936;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif