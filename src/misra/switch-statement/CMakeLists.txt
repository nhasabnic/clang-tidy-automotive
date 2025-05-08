
add_clang_library(clangTidyMISRASwitchStatementComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInSwitchCheck.cpp
  MissingDefaultInSwitchStatementCheck.cpp
  SwitchStatementComponent.cpp
  UnstructuredSwitchCaseCheck.cpp
  WrongOrderDefaultInSwitchStatementCheck.cpp
)
