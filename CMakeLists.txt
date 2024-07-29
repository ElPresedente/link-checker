cmake_minimum_required(VERSION 3.28)
set(CMAKE_TOOLCHAIN_FILE "F:/vcpkg/scripts/buildsystems/vcpkg.cmake")
message("Toolchain=${CMAKE_TOOLCHAIN_FILE}")
project(link_checker)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(gumbo-query)
add_subdirectory(OpenXLSX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS url locale)
find_package(cpr CONFIG REQUIRED)


add_executable(link_checker main.cc
        src/ui/MainWindow.cpp
        src/Page.cpp
        src/Network.cpp
        src/requests/AsyncHead.cpp
        src/requests/AsyncGet.cpp
        src/Logger.cpp
        src/Utility.cpp
        src/ui/ProgressBarMessage.cpp
        src/ui/ProgressBarMessage.hpp
)
target_link_libraries(link_checker
        gumbo_query_static
        PkgConfig::GTKMM #спасибо реддит
        cpr::cpr
        Boost::url
        Boost::locale
        OpenXLSX::OpenXLSX
)