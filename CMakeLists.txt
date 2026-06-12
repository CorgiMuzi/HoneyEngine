# ============================================================
#  HoneyEngine — root build script
#  Phase 1 milestone: window + loop + clean shutdown
#
#  Structure: single executable target (방식 1).
#  Designed so that splitting the engine into a library target
#  (방식 2) later is a minimal change — see the "STEP 2" notes.
# ============================================================

cmake_minimum_required(VERSION 3.21)

project(HoneyEngine
    VERSION 0.1.0
    LANGUAGES CXX          # C++ only; skips the needless C-compiler probe
)

# ------------------------------------------------------------
#  Dependencies (resolved by the vcpkg toolchain)
#  Phase 1 needs only SDL3. glm / SDL3_image / json return as
#  their features (Transform, textures, config) are reintroduced.
# ------------------------------------------------------------
find_package(SDL3 CONFIG REQUIRED)

# ------------------------------------------------------------
#  Engine source list
#  Explicit listing (no GLOB): so CMake reliably sees new files.
#  Add one line here per new source file.
#
#  ENGINE_SOURCES is kept separate from main.cpp on purpose.
#  STEP 2: move this variable straight into
#      add_library(HoneyEngineLib STATIC ${ENGINE_SOURCES})
#  and leave only main.cpp in the executable.
# ------------------------------------------------------------
set(ENGINE_SOURCES
    src/private/core/Application.cpp
    src/private/core/HoneyEngine.cpp
)

# ------------------------------------------------------------
#  Executable target
#  add_executable() creates an EMPTY target; sources are attached
#  below via target_sources(). (Don't list sources in both — that
#  would add them twice.)
# ------------------------------------------------------------
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        ${ENGINE_SOURCES}
)

# Declare C++23 as a requirement OF THIS TARGET (not a global default).
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Include path: expose the public headers. PRIVATE because this is a
# single executable with no consumers.
#   STEP 2: when this becomes a library, change PRIVATE -> PUBLIC so the
#   include dir propagates to consumers (the exe, tests, editor...).
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/public
)

# ------------------------------------------------------------
#  Per-compiler options (cross-platform safe)
#  These blocks add flags ONLY for the matching compiler, so the
#  same CMakeLists works on Windows (MSVC) and Ubuntu (GCC/Clang).
# ------------------------------------------------------------
if (MSVC)
    # MSVC defaults to the system code page; force UTF-8 source/exec
    # charset so non-ASCII string literals & comments are safe.
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()
# GCC/Clang already use UTF-8 by default, so no flag is needed there.

# ------------------------------------------------------------
#  Linking
# ------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
)
