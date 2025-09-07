from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.scm import Git
from conan.tools.files import collect_libs
import os

class SimpleBluezConan(ConanFile):
    name = "simplebluez"
    version = "0.10.3"
    license = "MIT"
    url = "https://github.com/simpleble/simpleble"
    description = "Cross-platform Bluetooth Low Energy library for C++."
    topics = ("bluetooth", "ble", "cross-platform")
    settings = "os", "compiler", "build_type", "arch"
#    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def source(self):
        git = Git(self)
        git.clone("https://github.com/simpleble/simpleble.git", target=".", args=["--depth=1", "--branch", "v0.10.3"])

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps= CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder=os.path.join(self.source_folder, "simplebluez"))
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = collect_libs(self)

