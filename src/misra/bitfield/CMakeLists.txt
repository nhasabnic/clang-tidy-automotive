
add_clang_library(clangTidyMISRABitfieldComponent STATIC
  AvoidBitfieldsInUnionsCheck.cpp
  AvoidSignedSingleBitFieldsCheck.cpp
  BitfieldComponent.cpp
  WrongBitfieldTypeCheck.cpp
)
