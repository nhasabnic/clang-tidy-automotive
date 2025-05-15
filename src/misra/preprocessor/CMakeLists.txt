
add_clang_library(clangTidyMISRAPreprocessorComponent STATIC
  AvoidHashOperatorCheck.cpp
  AvoidMacroNamedAsCkeywordCheck.cpp
  AvoidMultipleHashOperatorsCheck.cpp
  AvoidUndefCheck.cpp
  PreprocessorComponent.cpp
  PreprocessorFlowCheck.cpp
  UnusedMacroCheck.cpp
)
