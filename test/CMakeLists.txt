set(target ${MP3_TESTS})

file (GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")



#почему добавляем hdrs в строчку ниже
add_executable(${target} ${srcs} ${hdrs})
#убрал из линклибрарис ${MP2_LIBRARY}
target_link_libraries(${target} gtest)
target_include_directories(${target} PUBLIC ${MP3_INCLUDE})