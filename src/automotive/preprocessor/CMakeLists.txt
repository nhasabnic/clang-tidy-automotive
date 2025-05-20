
add_clang_library(clangTidyAutomotivePreprocessorComponent STATIC
  AvoidHashOperatorCheck.cpp
  AvoidMacroNamedAsCkeywordCheck.cpp
  AvoidMultipleHashOperatorsCheck.cpp
  AvoidUndefCheck.cpp
  PreprocessorComponent.cpp
  PreprocessorFlowCheck.cpp
  UnusedMacroCheck.cpp
)
