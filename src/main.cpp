#include <include/core/SkColor.h>
#include <include/core/SkData.h>
#include <include/core/SkFont.h>
#include <include/core/SkFontTypes.h>
#include <include/core/SkPaint.h>
#include <include/core/SkStream.h>
#include <modules/svg/include/SkSVGDOM.h>
// #include <modules/skottie/include/Skottie.h>
// #include <modules/skunicode/include/SkUnicode.h>
// #include <modules/sksg/include/SkSGTransform.h>
// #include <modules/skparagraph/include/ParagraphBuilder.h>
#include <GLFW/glfw3.h>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include <window.hpp>
#include <sk.hpp>
#include <font.hpp>

#define RESOURCE_DIR "resources"
#define FONT_DIR RESOURCE_DIR"/fonts"
#define ICON_DIR RESOURCE_DIR"/icons"
#define MDI_DIR ICON_DIR"/mdi"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    spdlog::info("Hello World");

    Window mainWindow;

    try {
        InitGLFW();
        mainWindow = Window(800, 600, "gitxplorer");
        SK::Init(800, 600);
    } catch(const std::runtime_error& err) {
        spdlog::error(err.what());
        return -1;
    }

    SkPaint bgPaint, fgPaint;
    bgPaint.setColor(SkColors::kCyan);
    fgPaint.setColor(SkColors::kBlack);

    SkFont fontMononoki = Font::LoadFontFromFile(
        "resources/fonts/mononoki/mononoki-Regular.ttf", 32
    );
    SkFont fontComfortaa = Font::LoadFontFromFile(
        "resources/fonts/Comfortaa/Comfortaa-Medium.ttf", 32
    );

    auto fileIconData = SkData::MakeFromFileName(MDI_DIR"/file.svg");
    auto fileIconStream = SkMemoryStream::Make(fileIconData);
    sk_sp<SkSVGDOM> fileIcon = SkSVGDOM::MakeFromStream(*fileIconStream);

    // skottie::Animation::Make(nullptr);
    // SkUnicode::convertUtf8ToUtf16("hoo", 8);
    // sksg::Transform::MakeInverse(nullptr);
    // skia::textlayout::ParagraphBuilder::make({}, nullptr);

    while(mainWindow.ShouldNotClose()) {
        glfwPollEvents();
        if(glfwGetKey(mainWindow, GLFW_KEY_ESCAPE))
            break;

        SK::canvas->drawPaint(bgPaint);
        SK::canvas->drawSimpleText(
            "Hello", 5, SkTextEncoding::kUTF8,
            50, 50, fontMononoki, fgPaint
        );
        SK::canvas->drawSimpleText(
            "World", 5, SkTextEncoding::kUTF8,
            50, 90, fontComfortaa, fgPaint
        );
        SK::canvas->save();
        fileIcon->setContainerSize(SkSize::Make(100, 100));
        fileIcon->render(SK::canvas);
        SK::canvas->restore();


        SK::context->flush();

        glfwSwapBuffers(mainWindow);
    }

    SK::Terminate();
    mainWindow.Terminate();
    TerminateGLFW();

    return 0;
}