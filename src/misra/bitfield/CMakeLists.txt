
add_clang_library(clangTidyMISRABitfieldComponent STATIC
  AvoidBitfieldInUnionCheck.cpp
  AvoidSignedSingleBitFieldCheck.cpp
  BitfieldComponent.cpp
  WrongBitfieldTypeCheck.cpp
)
