set(LLVM_LINK_COMPONENTS support)

project(clang-copy-finder CXX)

find_package(Clang REQUIRED)
find_package(LLVM REQUIRED)
include(AddClang)
include(AddLLVM)

add_executable(clang-copy-finder copyFinder.cpp)
#add_clang_executable(clang-copy-finder CopyFinder.cpp)
target_include_directories(clang-copy-finder PRIVATE ${CLANG_INCLUDE_DIRS})

target_link_libraries(clang-copy-finder
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )

install(TARGETS clang-copy-finder
    DESTINATION bin)