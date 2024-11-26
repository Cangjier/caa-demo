#include "Tidy_LocaleString.h"
using namespace Tidy;
    LocaleString::LocaleString(const UTF8String& target) {
        this->TargetEncoding = 0;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    LocaleString::LocaleString(const UTF8String&& target) {
        this->TargetEncoding = 0;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif
    LocaleString::LocaleString(const GBKString& target) {
        this->TargetEncoding = 0;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    LocaleString::LocaleString(const GBKString&& target) {
        this->TargetEncoding = 0;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif