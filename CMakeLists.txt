cmake_minimum_required(VERSION 3.28)

# run "emcmake cmake -B web-build"
# then "cmake --build web-build --config Release"

set(PROJECT_NAME "GreekQuiz")
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (APPLE AND NOT EMSCRIPTEN)
enable_language(OBJC)
enable_language(OBJCXX)
endif ()
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:/Zc:__cplusplus>
    )
endif()

# submodules
add_subdirectory(libs/visage)
add_subdirectory(libs/SQLiteCPP)

# resources (need a polytonic Greek font)
file(GLOB_RECURSE FONT_TTF_FILES fonts/*.ttf)
add_embedded_resources(EmbeddedFontResources "example_fonts.h" "resources::fonts" "${FONT_TTF_FILES}")


add_executable(${PROJECT_NAME} 
  src/main.cpp
  src/App.cpp
  src/DbManager.cpp
  src/QuizItem.cpp
  src/Betacode.cpp
  libs/unibetacode/ub_utf8.c
  libs/unibetacode/ub_greek2beta.c
  libs/unibetacode/ub_beta2greek.c
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_LINUX")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_MACOS")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Build for 10.14")
    add_compile_options(-mmacosx-version-min=15.0)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -D_GLIBCXX_USE_CXX11_ABI=1)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_WINDOWS")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
include_directories(libs/visage libs/SQLiteCpp libs/unibetacode src)

if (EMSCRIPTEN)
    MESSAGE(STATUS "Building for WebAssembly")    
    target_link_options(${PROJECT_NAME}
      PRIVATE
      --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/minshell.html
      -sGL_ENABLE_GET_PROC_ADDRESS
      -sALLOW_MEMORY_GROWTH=1
      --bind
      -s STACK_SIZE=48MB
      "-sEXPORTED_FUNCTIONS=['_main', '_pasteCallback']"
      "-sEXPORTED_RUNTIME_METHODS=['ccall', 'cwrap', 'UTF8ToString']"
      "-sNO_DISABLE_EXCEPTION_CATCHING"
  )

  set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX ".html"
    OUTPUT_NAME "index"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/builds/${EXAMPLE}"
  )
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
  visage
  VisageEmbeddedFonts
  EmbeddedFontResources
  SQLiteCpp
  sqlite3 # ${SQL} 
)
