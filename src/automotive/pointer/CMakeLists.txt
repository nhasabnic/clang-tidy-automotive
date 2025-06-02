
add_clang_library(clangTidyAutomotivePointerComponent STATIC
  AvoidAtomicVoidPointerCheck.cpp    
  PointerComponent.cpp  
  WrongNullPointerValueCheck.cpp
)
