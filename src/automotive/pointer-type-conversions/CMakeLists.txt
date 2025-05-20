
add_clang_library(clangTidyAutomotivePointerTypeConversions STATIC
  AvoidAtomicVoidPointerCheck.cpp    
  PointerTypeConversionsModule.cpp  
  WrongNullPointerValueCheck.cpp
)
