
add_clang_library(clangTidyMISRAPreprocessorComponent STATIC
  AvoidMacroNamedAsCkeywordCheck.cpp
  AvoidPreprocessorHashOperatorCheck.cpp
  AvoidUndefCheck.cpp
  PreprocessorComponent.cpp
  PreprocessorFlowCheck.cpp
  UnusedMacroCheck.cpp
)
