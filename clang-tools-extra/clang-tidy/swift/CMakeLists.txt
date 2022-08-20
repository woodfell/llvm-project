set(LLVM_LINK_COMPONENTS support FrontendOpenMP)

add_clang_library(clangTidySwiftModule
  AtomicFlagConstructorCheck.cpp
  ForbiddenFunctionsCheck.cpp
  ForbiddenTypesCheck.cpp
  NoTryCatchCheck.cpp
  NoexceptCorrectnessCheck.cpp
  NonPlacementNewCheck.cpp
  NostdlibassertCheck.cpp
  SwiftTidyModule.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  
  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidySwiftModule
  PRIVATE
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  )
