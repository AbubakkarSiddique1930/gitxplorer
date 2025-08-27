#include <font.hpp>
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>
#include <include/core/SkTypeface.h>

// Platform dependent FontMgr
#ifdef __APPLE__
    #error TEST
    #include <include/ports/SkFontMgr_mac_ct.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_CoreText(nullptr);
#elif __unix__
    #include <include/ports/SkFontMgr_fontconfig.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_FontConfig(nullptr);
#elif __WIN32
    #include <include/ports/SkTypeface_win.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_DirectWrite(nullptr);
#else
    #error Platform not supported for FontMgr
#endif // Platform dependent FontMgr

sk_sp<SkTypeface> Font::LoadTypeFaceFromFile(const char *filePath) {
    return fontMgr->makeFromFile(filePath);
}

SkFont Font::LoadFontFromFile(const char *filePath, float size) {
    return {LoadTypeFaceFromFile(filePath), size};
}
