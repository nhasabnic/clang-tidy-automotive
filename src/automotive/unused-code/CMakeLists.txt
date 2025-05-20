
add_clang_library(clangTidyMISRAUnusedCode STATIC
  UnusedCodeModule.cpp
  UnusedObjectDefinitionCheck.cpp
  UnusedTagCheck.cpp
  UnusedTypeCheck.cpp
)
