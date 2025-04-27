
add_clang_library(clangTidyMISRAPointerTypeConversationsModule STATIC
  AvoidAtomicVoidPointerCheck.cpp    
  PointerTypeConversationsModule.cpp  
  WrongNullPointerValueCheck.cpp
)
