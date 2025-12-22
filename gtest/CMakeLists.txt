set(target "gtest")
#почему тут библиотека а не exe
add_library(${target} STATIC gtest-all.cc)