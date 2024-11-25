project(arcball
    LANGUAGES CXX
)



add_executable(arcball Ball.c Ball.h BallAux.c BallAux.h BallMath.c BallMath.h Body.c Body.h Demo.c)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	target_link_libraries(arcball FakeIrisGL m)
else()
    #target_link_libraries(arcball FakeIrisGL)
endif()


target_link_libraries(arcball PRIVATE glfw
                                      imgui::imgui
                                      FakeIrisGL #TODO: Remove this after all gems are ported
                                      )

target_compile_features(arcball PRIVATE cxx_std_20)