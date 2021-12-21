cmake_minimum_required(VERSION 3.2)

project(stable-fluids)

#Important CMAKE stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(DownloadProject)
# get opengl
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
download_project(
			PROJ         eigen
			SOURCE_DIR   "../../eigen"
			DOWNLOAD_DIR "../extern/.cache/eigen"
			QUIET
                        TLS_VERIFY OFF
                        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
		        GIT_TAG        3.3.7
		)
              
INCLUDE_DIRECTORIES("extern/eigen")
# include directories
include_directories(${PROJECT_SOURCE_DIR}/shared/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


#source code
file(GLOB H_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB H_SHARED_FILES ${PROJECT_SOURCE_DIR}/shared/include/*.h)
file(GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB CPP_SHARED_FILES ${PROJECT_SOURCE_DIR}/shared/src/*.cpp)

add_executable(${PROJECT_NAME} main.cpp ${H_FILES} ${H_SHARED_FILES} ${CPP_FILES} ${CPP_SHRED_FILES})
target_link_libraries(${PROJECT_NAME} GL GLU glut)
