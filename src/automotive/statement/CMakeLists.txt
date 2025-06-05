
add_clang_library(clangTidyAutomotiveStatementComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInSwitchCheck.cpp
  MissingDefaultInSwitchStatementCheck.cpp
  StatementComponent.cpp
  UnstructuredSwitchCaseCheck.cpp
  WrongOrderInSwitchStmtCheck.cpp
  AvoidGotoCheck.cpp
  ForwardGotoLabelCheck.cpp
  UnusedLabelCheck.cpp
  MissingCompoundCheck.cpp
  MissingElseCheck.cpp
)
