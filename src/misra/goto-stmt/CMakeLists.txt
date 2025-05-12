
add_clang_library(clangTidyMISRAGotoStmtComponent STATIC
  AvoidGotoCheck.cpp  
  ForwardGotoLabelCheck.cpp  
  GotoStmtComponent.cpp
  UnusedLabelCheck.cpp
)
