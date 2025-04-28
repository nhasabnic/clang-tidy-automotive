
add_clang_library(clangTidyMISRATypes STATIC
  AvoidBitfieldsInUnionsCheck.cpp
  AvoidSignedSingleBitFieldsCheck.cpp
  TypesModule.cpp
  WrongBitfieldTypeCheck.cpp
)
