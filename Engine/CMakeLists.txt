# Collect all .cpp files automatically
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "include/*.h")

set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_opengl3_loader.h
)

# Build engine as a static library
add_library(Engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
    ${IMGUI_SOURCES}
)

# Public include path — anyone linking Engine gets this
target_include_directories(Engine
    PUBLIC  include/
    PRIVATE src/
    PUBLIC imgui/
)

# Link dependencies
target_link_libraries(Engine
    PUBLIC  glfw
    PUBLIC  glad
    PUBLIC  glm
)

# Compile flags
target_compile_options(Engine PRIVATE
    -Wall -Wextra
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)
