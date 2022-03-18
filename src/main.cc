#include "Core/Application.hh"
#include "Core/Logger.hh"
#include "Core/Assertions.hh"

#include <filesystem>
#include <iostream>
int main()
{
  // Despite using macros this needs to be set to allow for debug/trace logging at all
  mg::init_logger();

  // make sure the executable is run from the correct path
  // (this way we can find all the resources in the data folder)
  if (!std::filesystem::exists("../data"))
  {
      std::cerr << "Working directory must be set to 'bin/'" << std::endl;
      return EXIT_FAILURE;
  }

  SPDLOG_DEBUG("Testlog");

  // TODO: Create instance of game & run
  std::cout << "Run the game!" << std::endl;

  return EXIT_SUCCESS;
}
