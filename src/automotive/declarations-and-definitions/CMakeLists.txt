
add_clang_library(clangTidyMISRADeclarationsAndDefinitions STATIC
  AvoidRestrictTypeCheck.cpp
  DeclarationsAndDefinitionsModule.cpp
  FunctionDeclarationMismatchCheck.cpp
  MissingExternalArraySizeCheck.cpp
  StaticInlineCheck.cpp
  UncompleteFunctionPrototypeCheck.cpp
  UniqueEnumValuesCheck.cpp
)
