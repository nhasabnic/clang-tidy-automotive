
add_clang_library(clangTidyAutomotiveStatementComponent STATIC
  AvoidBooleanInSwitchCheck.cpp  
  MissingBreakInCaseStmtCheck.cpp
  MissingDefaultInSwitchStmtCheck.cpp
  StatementComponent.cpp
  UnstructuredSwitchStmtCheck.cpp
  WrongOrderInSwitchStmtCheck.cpp
  AvoidGotoCheck.cpp
  ForwardGotoLabelCheck.cpp
  UnusedLabelCheck.cpp
  MissingCompoundStmtCheck.cpp
  MissingElseCheck.cpp
)
