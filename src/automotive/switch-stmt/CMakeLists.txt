
add_clang_library(clangTidyAutomotiveSwitchStmtComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInSwitchCheck.cpp
  MissingDefaultInSwitchStatementCheck.cpp
  SwitchStmtComponent.cpp
  UnstructuredSwitchCaseCheck.cpp
  WrongOrderDefaultInSwitchStatementCheck.cpp
)
