
add_clang_library(clangTidyMISRAPointerTypeConversations STATIC
  AvoidAtomicVoidPointerCheck.cpp    
  PointerTypeConversationsModule.cpp  
  WrongNullPointerValueCheck.cpp
)
