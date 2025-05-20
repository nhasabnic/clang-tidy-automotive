
add_clang_library(clangTidyMISRAStdlibComponent STATIC
  AtoXCheck.cpp
  AvoidApiCheck.cpp
  AvoidSetjmpHeaderCheck.cpp
  AvoidSignalHeaderCheck.cpp
  AvoidStdargHeaderCheck.cpp
  AvoidStdlibRandCheck.cpp
  AvoidstdlibsystemcallCheck.cpp
  ExitCheck.cpp
  StdlibComponent.cpp
)
