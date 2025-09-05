#include <cstdlib>
#include <include/core/SkFontTypes.h>
#include <iostream>
#include <cstdio>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <include/core/SkData.h>
#include <include/core/SkImage.h>
#include <include/core/SkImageInfo.h>
#include <include/core/SkPaint.h>
#include <include/core/SkRefCnt.h>
#include <include/core/SkSurface.h>
#include <include/core/SkStream.h>
#include <include/encode/SkPngEncoder.h>

#include <font.hpp>
#include <spdlog/spdlog.h>

void WriteSurfaceToPNG(sk_sp<SkSurface> surface, const char* imagePath) {
    sk_sp<SkImage> img = surface->makeImageSnapshot();

    auto png = SkPngEncoder::Encode(nullptr, img.get(), {});
    SkFILEWStream file(imagePath);
    if(!file.isValid()) {
        spdlog::error("Failed to write png file at {}", imagePath);
        exit(-1);
    }
    file.write(png->data(), png->size());
}

int main(int argc, char* argv[]) {
    
    if(argc < 3)
        return -1;

    SkImageInfo iinfo = SkImageInfo::MakeN32Premul(256, 256);
    auto surface = SkSurfaces::Raster(iinfo);
    SkCanvas* canvas = surface->getCanvas();

    SkPaint bgPaint{SkColors::kCyan};
    SkPaint fgPaint{SkColors::kBlack};

    SkFont fontMononoki = Font::LoadFontFromFile(
        "resources/fonts/mononoki/mononoki-Regular.ttf", 32
    );
    SkFont fontComfortaa = Font::LoadFontFromFile(
        "resources/fonts/Comfortaa/Comfortaa-Medium.ttf", 32
    );

    fontMononoki.setSubpixel(true);
    fontMononoki.setHinting(SkFontHinting::kNormal);
    fontMononoki.setEdging(SkFont::Edging::kSubpixelAntiAlias);
    fontComfortaa.setSubpixel(true);
    fontComfortaa.setHinting(SkFontHinting::kNormal);
    fontComfortaa.setEdging(SkFont::Edging::kSubpixelAntiAlias);

    // Golden image
    canvas->drawPaint(bgPaint);
    canvas->drawSimpleText(
        "Hello", 5, SkTextEncoding::kUTF8,
        50, 50, fontMononoki, fgPaint
    );
    canvas->drawSimpleText(
        "World", 5, SkTextEncoding::kUTF8,
        50, 90, fontComfortaa, fgPaint
    );

    WriteSurfaceToPNG(surface, argv[1]);

    // Alt golden image
    canvas->drawPaint(bgPaint);
    canvas->drawSimpleText(
        "Hell", 4, SkTextEncoding::kUTF8,
        50, 50, fontMononoki, fgPaint
    );
    canvas->drawSimpleText(
        "World", 5, SkTextEncoding::kUTF8,
        50, 90, fontComfortaa, fgPaint
    );

    WriteSurfaceToPNG(surface, argv[2]);

    return 0;
}