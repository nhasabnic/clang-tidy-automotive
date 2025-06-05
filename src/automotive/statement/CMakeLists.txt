
add_clang_library(clangTidyAutomotiveStatementComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInCaseStmtCheck.cpp
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
