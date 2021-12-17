from conans import ConanFile


class CppStarterProject(ConanFile):
    # Note: options are copied from CMake boolean options.
    # When turned off, CMake sometimes passes them as empty strings.
    options = {
        "cpp_starter_use_imgui": ["ON", "OFF", ""],
        "cpp_starter_use_sdl": ["ON", "OFF", ""]
    }
    #settings = "cppstd","os"
    settings = {"compiler": {"gcc": {"cppstd": [17]},
                 "Visual Studio": {"cppstd": [17]},
                 "Clang":{"cppstd":[17]}}, "os"}
    name = "CppStarterProject"
    version = "0.1"
    '''requires = (
        "boost/1.77.0",
        "eigen/3.4.0",
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "fmt/8.0.1",
        "spdlog/1.9.2",
        "tbb/2020.0"
    )'''
    generators = "cmake", "gcc", "txt", "cmake_find_package"

    def requirements(self):
        if self.settings.os == "Windows" or self.settings.os == "Linux":
            self.requires("boost/1.77.0")
            self.requires("eigen/3.4.0")
            self.requires("catch2/2.13.7")
            self.requires("docopt.cpp/0.6.2")
            self.requires("fmt/8.0.1")
            self.requires("spdlog/1.9.2")
            self.requires("tbb/2020.0")
        if self.settings.os == "Macos":
            self.requires("boost/1.77.0")
            self.requires("eigen/3.4.0")
            self.requires("catch2/2.13.7")
            self.requires("docopt.cpp/0.6.2")
            self.requires("fmt/8.0.1")
            self.requires("spdlog/1.9.2")
        if self.options.cpp_starter_use_imgui == "ON":
            self.requires("imgui-sfml/2.1@bincrafters/stable")
        if self.options.cpp_starter_use_sdl == "ON":
            self.requires("sdl2/2.0.10@bincrafters/stable")

