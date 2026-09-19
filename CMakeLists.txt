cmake_minimum_required(VERSION 3.21)  # needed for TARGET_RUNTIME_DLLS below
project(2DGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to a Release build if the user didn't ask for anything specific.
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# --- SFML -------------------------------------------------------------
# Audio is requested in both branches: SoundManager needs sf::Music /
# sf::Sound / sf::SoundBuffer, and without listing it here a config-mode
# find_package will simply never create an SFML::Audio target to link.
find_package(SFML 3 COMPONENTS Graphics Window System Audio QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)
endif()

# --- Sources ------------------------------------------------------------
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(game ${SRC_FILES})

target_include_directories(game PRIVATE
    include
    include/core
    include/entities
    include/managers
    include/ui
)

if(MSVC)
  target_compile_options(game PRIVATE /W4)
else()
  target_compile_options(game PRIVATE
    -Wall -Wextra -Wpedantic -Wunused -Wunused-function -Wunused-parameter -Wunreachable-code
  )
endif()

if(MINGW)
    target_link_options(game PRIVATE -static-libgcc -static-libstdc++)
endif()

if(TARGET SFML::Graphics)
    target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)
else()
    target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# Copy any SFML/OpenAL DLLs the game needs next to the exe after each build,
# so a dynamically-linked Windows build is runnable straight out of the
# build directory (and, more importantly, after install()) without manually
# hunting down DLLs. No-op on platforms without shared runtime DLLs.
if(WIN32)
    add_custom_command(TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_RUNTIME_DLLS:game> $<TARGET_FILE_DIR:game>
        COMMAND_EXPAND_LISTS
    )
endif()

# Assets are resolved at runtime relative to the executable (see
# Assets.hpp), so the build directory needs its own copy of assets/ next
# to the exe for local runs -- this is separate from, and in addition to,
# the install(DIRECTORY assets/ ...) rule below, which handles packaged
# builds.
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game>/assets
)

add_custom_target(run
    COMMAND game
    DEPENDS game
    WORKING_DIRECTORY $<TARGET_FILE_DIR:game>
)

# --- Packaging ------------------------------------------------------------
# `cmake --install build --prefix out` (or just `cpack` from the build dir)
# produces a self-contained folder: the exe plus its assets, ready to zip
# and hand to someone else. This is the piece that was missing entirely
# before — without it there was no way to go from "source tree" to
# "thing a friend can download and run."
install(TARGETS game RUNTIME DESTINATION .)
install(DIRECTORY assets/ DESTINATION assets)

if(WIN32)
  install(FILES $<TARGET_RUNTIME_DLLS:game> DESTINATION .)
endif()

set(CPACK_PACKAGE_NAME "2DGame")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP")
include(CPack)