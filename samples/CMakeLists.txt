set(target sample)

file(GLOB sources "*.cpp")
file(GLOB headers "*.h*")

add_executable(${target} ${sources} ${headers})
target_link_libraries(${target} ${MP3_LIBRARY})