//Custom assertion handler to provide more information
#pragma once
#include "defines.hh"

// Credits for this idea to Travis Vroman and his Kohi engine.
namespace mg_detail
{
  void report_assertion(const char* expression, const char* message, const char* file, int line);
}

// Treat Microsoft special:
// - Visual Studio (clang) compiler uses Microsoft specific break command
// - All other compilers use gcc compatible break commands
#ifdef MAGMA_ASSERTIONS_ENABLED
# if _MSC_VER
#   include<intrin.h>
#   define debugBreak() __debugbreak()
# else
#   define debugBreak() __builtin_trap()
# endif

# define MG_ASSERT(expr)                                            \
  {                                                                 \
    if(expr) {                                                      \
    }                                                               \
    else {                                                          \
      mg_detail::report_assertion(#expr, "", __FILE__, __LINE__);   \
      debugBreak();                                                 \
    }                                                               \
  }

# define MG_ASSERT_MSG(expr, message)                                   \
  {                                                                     \
    if(expr) {                                                          \
    }                                                                   \
    else {                                                              \
      mg_detail::report_assertion(#expr, message, __FILE__, __LINE__);  \
      debugBreak();                                                     \
    }                                                                   \
  }

#endif