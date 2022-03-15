#include "Core.hh"

#include <filesystem>
#include <iostream>

int main()
{
  // make sure the executable is run from the correct path
  // (this way we can find all the resources in the data folder)
  if (!std::filesystem::exists("../data"))
  {
      std::cerr << "Working directory must be set to 'bin/'" << std::endl;
      return EXIT_FAILURE;
  }

  // TODO: Create instance of game & run
  std::cout << "Run the game!" << std::endl;

  return EXIT_SUCCESS;
}
