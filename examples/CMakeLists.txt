if(ANDROID)
	set(PLATFORM ${CMAKE_CURRENT_SOURCE_DIR}/../ncnn_android)
else()
	set(PLATFORM ${CMAKE_CURRENT_SOURCE_DIR}/../ncnn_linux)
endif()

include_directories(${PLATFORM}/include)
link_directories(${PLATFORM}/lib)

add_executable(ncnn_classify classify.cpp)
target_link_libraries(ncnn_classify ncnn)

install(TARGETS ncnn_classify 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)