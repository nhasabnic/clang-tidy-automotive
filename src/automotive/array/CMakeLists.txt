
add_clang_library(clangTidyAutomotiveArrayComponent STATIC
  ArrayComponent.cpp
  AvoidFlexibleArrayMemberCheck.cpp
  AvoidPartialArrayInitCheck.cpp
  AvoidVariableLengthArrayCheck.cpp
  MissingExternalArraySizeCheck.cpp
)
