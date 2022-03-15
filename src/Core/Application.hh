#pragma once
#include <vector>
#include <string>

// Forward declarations
typedef struct GLFWwindow GLFWwindow;
typedef struct VkInstance_T* VkInstance;

namespace mg {
  // Test code
  void print_int(int32_t i);

  // Real code
  enum class ErrorType {
    Warning = 0,
    Severe,
    Critical
  };

  void Error(ErrorType errType, std::string errMsg);

  // GLFWwindow encapsulation.
  struct Window {
    Window();
    Window(int width, int height, const char* title);

  public:
    GLFWwindow* instance;
    int width;
    int height;

  private:
    static bool glfwInitialized;
    const int defaultWidth = 1024;
    const int defaultHeight = 768;
    const char* defaultTitle = "Magma Window";
  };

  class MagmaApp {
    
  };


  class Vulkan {
  public:
    bool createInstance();


  private:
    bool checkValidationLayerSupport();

  private:
    VkInstance instance;
    const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
  };
}