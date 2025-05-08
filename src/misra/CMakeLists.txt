set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  support
  )

add_subdirectory(char-sets-and-lexical-convs)
add_subdirectory(comment)
add_subdirectory(declarations-and-definitions)
add_subdirectory(expressions)
add_subdirectory(literals-and-constants)
add_subdirectory(pointer-type-conversions)
add_subdirectory(bitfield)
add_subdirectory(switch-statement)
add_subdirectory(unused-code)
add_subdirectory(utils)


add_clang_library(clangTidyMISRAModule
  AvoidApiCheck.cpp
  AvoidFlexibleArrayMemberCheck.cpp
  AvoidFunctionParameterModificationCheck.cpp
  AvoidMacroNamedAsCkeywordCheck.cpp
  AvoidNonBooleanInConditionCheck.cpp
  AvoidSetjmpHeaderCheck.cpp
  AvoidGotoCheck.cpp
  AvoidSignalHeaderCheck.cpp
  AvoidStdargHeaderCheck.cpp
  AvoidAssignmentInExpressionCheck.cpp
  AvoidVariableLengthArrayCheck.cpp
  AvoidstdlibsystemcallCheck.cpp
  AvoidStdlibRandCheck.cpp
  ImplicitFunctionDeclCheck.cpp
  ImplicitIntCheck.cpp
  InvariantControlCheck.cpp
  MissingStaticInternalLinkageCheck.cpp
  MissingReturnValueHandlingCheck.cpp
  NoReturnVoidCheck.cpp
  AtoXCheck.cpp
  AvoidUndefCheck.cpp
  AvoidUnionCheck.cpp
  ExitCheck.cpp
  ForwardGotoLabelCheck.cpp
  MISRATidyModule.cpp
  MissingCompoundCheck.cpp
  MissingElseCheck.cpp
  MultipleReturnStmtCheck.cpp
  PreprocessorFlowCheck.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  clangTidyMiscModule
  clangTidyCERTModule

  clangTidyMISRABitfieldComponent
  clangTidyMISRACharSetsAndLexicalConvs
  clangTidyMISRACommentComponent
  clangTidyMISRADeclarationsAndDefinitions
  clangTidyMISRAExpressions
  clangTidyMISRALiteralsAndConstants
  clangTidyMISRAPointerTypeConversions
  clangTidyMISRASwitchStatementComponent
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
