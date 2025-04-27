set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  support
  )

add_subdirectory(char-sets-and-lexical-convs)
add_subdirectory(comments)
add_subdirectory(decls-and-defs)
add_subdirectory(literals-and-constants)
add_subdirectory(pointer-type-conversations)
add_subdirectory(types)
add_subdirectory(unused-code)
add_subdirectory(utils)


add_clang_library(clangTidyMISRAModule
  AvoidApiCheck.cpp
  AvoidBooleanInSwitchCheck.cpp
  AvoidFunctionParameterModificationCheck.cpp
  AvoidMacroNamedAsCkeywordCheck.cpp
  AvoidNonBooleanInConditionCheck.cpp
  AvoidSetjmpHeaderCheck.cpp
  AvoidCommaOperatorCheck.cpp
  AvoidGotoCheck.cpp
  AvoidSignalHeaderCheck.cpp
  AvoidStdargHeaderCheck.cpp
  AvoidAssignmentInExpressionCheck.cpp
  AvoidstdlibsystemcallCheck.cpp
  AvoidStdlibRandCheck.cpp
  ImplicitFunctionDeclCheck.cpp
  ImplicitIntCheck.cpp
  InvariantControlCheck.cpp
  MissingStaticInternalLinkageCheck.cpp
  MissingBreakInSwitchCheck.cpp
  MissingReturnValueHandlingCheck.cpp
  NoReturnVoidCheck.cpp
  AtoXCheck.cpp
  AvoidUndefCheck.cpp
  AvoidUnionCheck.cpp
  ExitCheck.cpp
  ForwardGotoLabelCheck.cpp
  MISRATidyModule.cpp
  MissingCompoundCheck.cpp
  MissingDefaultInSwitchStatementCheck.cpp
  MissingElseCheck.cpp
  MultipleReturnStmtCheck.cpp
  PreprocessorFlowCheck.cpp
  UnstructuredSwitchCaseCheck.cpp
  WrongOrderDefaultInSwitchStatementCheck.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils
  clangTidyMiscModule
  clangTidyCERTModule

  clangTidyMISRACharSetsAndLexicalConvsModule
  clangTidyMISRACommentsModule
  clangTidyMISRADeclsAndDefsModule
  clangTidyMISRALiteralsAndConstantsModule
  clangTidyMISRAPointerTypeConversationsModule
  clangTidyMISRATypesModule
  clangTidyMISRAUnusedCodeModule
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
