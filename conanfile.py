from conan import ConanFile
from conan.tools.meson import Meson, MesonToolchain
from conan.tools.gnu import PkgConfig, PkgConfigDeps


## --- Packages
sdl2 = "sdl/2.26.5"
sdl2_ttf = "sdl_ttf/2.20.2"
spdlog = "spdlog/1.13.0"
clove_unit = "clove-unit/2.4.1"


## Look into `system_requirements()`

## adding pip dependencies:
## https://stackoverflow.com/questions/54493352/is-there-a-way-to-add-python-dependencies-to-conan-package

## PkgConfig(self, "sdl2", self.folders.build_folder).includedirs[0] :: contains includes for SDL2

## create script for extracting header files by name from SDL2

## create seoarate script for generating sos::input::keyboard and sos::input::mouse values


class PongSdl2Cpp(ConanFile):
    name = "Pong SDL2 C++"
    version = "0.1"
    description = "Pong. Implementation in C++ using SDL2."
    author = "Nicholas H.R. Sims (nickhrsims@gmail.com)"

    settings = "os", "arch", "compiler", "build_type"
    requires = (sdl2, sdl2_ttf, spdlog, clove_unit)

    options = {"shared": [True, False]}
    default_options = {"shared": False}

    def generate(self: ConanFile):
        pkgconfig = PkgConfigDeps(self)
        toolchain = MesonToolchain(self)
        pkgconfig.generate()
        toolchain.generate()

    def build(self):
        meson = Meson(self)
        meson.configure()
        meson.build()

    def package(self):
        meson = Meson(self)
        meson.install()
