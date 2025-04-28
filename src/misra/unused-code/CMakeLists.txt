
add_clang_library(clangTidyMISRAUnusedCode STATIC
  UnusedCodeModule.cpp
  UnusedLabelCheck.cpp
  UnusedMacroCheck.cpp
  UnusedObjectDefinitionCheck.cpp
  UnusedTagCheck.cpp
  UnusedTypeCheck.cpp
)
