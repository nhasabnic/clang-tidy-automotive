
add_clang_library(clangTidyMISRATypesModule STATIC
  AvoidBitfieldsInUnionsCheck.cpp
  AvoidSignedSingleBitFieldsCheck.cpp
  TypesModule.cpp
  WrongBitfieldTypeCheck.cpp
)
