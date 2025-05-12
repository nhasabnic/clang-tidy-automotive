set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  support
  )

add_subdirectory(array)
add_subdirectory(char-sets-and-lexical-convs)
add_subdirectory(comment)
add_subdirectory(declarations-and-definitions)
add_subdirectory(goto-stmt)
add_subdirectory(operator)
add_subdirectory(literals-and-constants)
add_subdirectory(pointer-type-conversions)
add_subdirectory(bitfield)
add_subdirectory(preprocessor)
add_subdirectory(return-stmt)
add_subdirectory(switch-stmt)
add_subdirectory(unused-code)
add_subdirectory(utils)


add_clang_library(clangTidyMISRAModule
  AvoidApiCheck.cpp
  AvoidFunctionParameterModificationCheck.cpp
  AvoidNonBooleanInConditionCheck.cpp
  AvoidSetjmpHeaderCheck.cpp
  AvoidSignalHeaderCheck.cpp
  AvoidStdargHeaderCheck.cpp
  AvoidAssignmentInExpressionCheck.cpp
  AvoidstdlibsystemcallCheck.cpp
  AvoidStdlibRandCheck.cpp
  ImplicitFunctionDeclCheck.cpp
  ImplicitIntCheck.cpp
  InvariantControlCheck.cpp
  MissingStaticInternalLinkageCheck.cpp
  AtoXCheck.cpp
  AvoidUnionCheck.cpp
  ExitCheck.cpp
  MISRATidyModule.cpp
  MissingCompoundCheck.cpp
  MissingElseCheck.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  clangTidyMiscModule
  clangTidyCERTModule

  clangTidyMISRAArrayComponent
  clangTidyMISRABitfieldComponent
  clangTidyMISRACharSetsAndLexicalConvs
  clangTidyMISRACommentComponent
  clangTidyMISRADeclarationsAndDefinitions
  clangTidyMISRAGotoStmtComponent
  clangTidyMISRAOperatorComponent
  clangTidyMISRALiteralsAndConstants
  clangTidyMISRAPointerTypeConversions
  clangTidyMISRAPreprocessorComponent
  clangTidyMISRAReturnStmtComponent
  clangTidyMISRASwitchStmtComponent
  clangTidyMISRAUnusedCode
  clangTidyMISRAUtils

  DEPENDS
  ClangDriverOptions
  )

clang_target_link_libraries(clangTidyMISRAModule
  PRIVATE
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  )
