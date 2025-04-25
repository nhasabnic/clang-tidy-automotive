
add_clang_library(clangTidyMISRADeclsAndDefsModule STATIC
  AvoidRestrictTypeCheck.cpp
  DeclsAndDefsModule.cpp
  FunctionDeclarationMismatchCheck.cpp
  MissingExternalArraySizeCheck.cpp
  StaticInlineCheck.cpp
  UncompleteFunctionPrototypeCheck.cpp
  UniqueEnumValuesCheck.cpp
)
