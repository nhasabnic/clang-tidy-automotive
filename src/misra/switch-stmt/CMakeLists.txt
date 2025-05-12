
add_clang_library(clangTidyMISRASwitchStmtComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInSwitchCheck.cpp
  MissingDefaultInSwitchStatementCheck.cpp
  SwitchStmtComponent.cpp
  UnstructuredSwitchCaseCheck.cpp
  WrongOrderDefaultInSwitchStatementCheck.cpp
)
