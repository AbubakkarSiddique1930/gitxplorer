#include <font.hpp>
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>
#include <include/core/SkTypeface.h>

#ifdef __unix__
    #include <include/ports/SkFontMgr_fontconfig.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_FontConfig(nullptr);
#endif

#ifdef __APPLE__
    #include <include/ports/SkFontMgr_mac_ct.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_CoreText(nullptr);
#endif

#ifdef _WIN32
    #include <include/ports/SkTypeface_win.h>
    sk_sp<SkFontMgr> fontMgr = SkFontMgr_New_DirectWrite(nullptr);
#endif

sk_sp<SkTypeface> Font::LoadTypeFaceFromFile(const char *filePath) {
    return fontMgr->makeFromFile(filePath);
}

SkFont Font::LoadFontFromFile(const char *filePath, float size) {
    return {LoadTypeFaceFromFile(filePath), size};
}
