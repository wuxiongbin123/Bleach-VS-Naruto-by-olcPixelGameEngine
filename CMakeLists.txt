cmake_minimum_required(VERSION 3.25)
project(bvn)

set(CMAKE_CXX_STANDARD 17)

set(LINK_DIR "D:/Program Files/MATLAB/R2022a/sys/lcc64/lcc64/lib64")


add_executable(bvn main.cpp olcPixelGameEngine.h engine.cpp engine.h ActionDraw.cpp ActionDraw.h music.cpp music.h)

target_link_libraries(bvn user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs winmm.lib)
