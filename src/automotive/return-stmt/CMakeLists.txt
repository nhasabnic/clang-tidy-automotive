
add_clang_library(clangTidyMISRAReturnStmtComponent STATIC
  MissingReturnValueHandlingCheck.cpp
  MultipleReturnStmtCheck.cpp
  NoReturnVoidCheck.cpp
  ReturnStmtComponent.cpp
)
