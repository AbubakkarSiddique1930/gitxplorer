from conan import ConanFile

class ConanDeps(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("spdlog/1.15.3")
        self.requires("glfw/3.4")
        self.requires("skia/138.20250708.0")