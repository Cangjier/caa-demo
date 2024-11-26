#include "Tidy_UTF8String.h"
using namespace Tidy;
    UTF8String::UTF8String(const LocaleString& target) {
        this->TargetEncoding = 65001;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    UTF8String::UTF8String(const LocaleString&& target) {
        this->TargetEncoding = 65001;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif
    UTF8String::UTF8String(const GBKString& target) {
        this->TargetEncoding = 65001;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#if SUPPORT_RVALUE_REFERENCES
    UTF8String::UTF8String(const GBKString&& target) {
        this->TargetEncoding = 65001;
        if (target.TargetEncoding == this->TargetEncoding) {
            this->Target = target.Target;
        } else {
            this->Target = StringUtil::To(target.Target, target.TargetEncoding, this->TargetEncoding);
        }
    }
#endif