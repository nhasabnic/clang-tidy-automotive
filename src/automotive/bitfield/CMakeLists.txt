
add_clang_library(clangTidyAutomotiveBitfieldComponent STATIC
  AvoidBitfieldInUnionCheck.cpp
  AvoidSignedSingleBitFieldCheck.cpp
  BitfieldComponent.cpp
  WrongBitfieldTypeCheck.cpp
)
