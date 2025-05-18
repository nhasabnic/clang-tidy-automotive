
add_clang_library(clangTidyMISRAArrayComponent STATIC
  ArrayComponent.cpp
  AvoidFlexibleArrayMemberCheck.cpp
  AvoidPartialArrayInitCheck.cpp
  AvoidVariableLengthArrayCheck.cpp
)
