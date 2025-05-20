
add_clang_library(clangTidyAutomotiveGotoStmtComponent STATIC
  AvoidGotoCheck.cpp  
  ForwardGotoLabelCheck.cpp  
  GotoStmtComponent.cpp
  UnusedLabelCheck.cpp
)
