project(arcball
    VERSION 1.0
    DESCRIPTION "Arcball Rotation Control"
    LANGUAGES CXX
)



add_executable(arcball 
    Ball.cpp 
    Ball.hpp 
    BallAux.cpp 
    BallAux.hpp 
    BallMath.cpp 
    BallMath.hpp
    Body.cpp 
    Body.hpp 
    Demo.cpp
)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_link_libraries(arcball PRIVATE FakeIrisGL m)
else()
    target_link_libraries(arcball PRIVATE FakeIrisGL)
endif()


target_link_libraries(arcball PRIVATE glfw
                                      imgui::imgui
                                      OpenGL::GL
                                      FakeIrisGL #TODO: Remove this after all gems are ported
                                      )

target_compile_features(arcball PRIVATE cxx_std_20)