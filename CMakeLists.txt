cmake_minimum_required(VERSION 3.20)
project(Wetter)
add_subdirectory(implementation/Wetter)
add_subdirectory(test)
target_include_directories(main PUBLIC
							"${PROJECT_SOURCE_DIR}" 
							"${PROJECT_SOURCE_DIR}/implementation/Wetter"
							)
target_link_libraries(main PUBLIC testee)
