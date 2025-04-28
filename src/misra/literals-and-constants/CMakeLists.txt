
add_clang_library(clangTidyMISRALiteralsAndConstants STATIC
  AvoidLowercaseLiteralSuffixCheck.cpp
  AvoidOctalNumberCheck.cpp
  LiteralsAndConstantsModule.cpp
)
