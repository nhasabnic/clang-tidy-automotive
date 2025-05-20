
add_clang_library(clangTidyMISRAPointerTypeConversions STATIC
  AvoidAtomicVoidPointerCheck.cpp    
  PointerTypeConversionsModule.cpp  
  WrongNullPointerValueCheck.cpp
)
