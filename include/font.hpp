#pragma once

#include <include/core/SkFont.h>
#include <include/core/SkTypeface.h>

namespace Font {
    sk_sp<SkTypeface> LoadTypeFaceFromFile(const char* filePath);
    SkFont LoadFontFromFile(const char* filePath, float size);
}
