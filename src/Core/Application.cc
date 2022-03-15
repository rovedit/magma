#include "Core.hh"
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>


// Initialize static (class) variables
bool mg::Window::glfwInitialized = false;

// Real code
void mg::Error(ErrorType errType, std::string errMsg) {
  if (errType == ErrorType::Warning) {
    std::cerr << "[WARNING]: " + errMsg << std::endl;
  }
  else if (errType == ErrorType::Severe) {
    throw std::runtime_error("[SEVERE]: " + errMsg);
  }
  else if (errType == ErrorType::Critical) {
    throw std::runtime_error("[CRITICAL]: " + errMsg);
  }
}

mg::Window::Window() {
  Window(defaultWidth, defaultHeight, defaultTitle);
}

mg::Window::Window(int width, int height, const char* title) {
  if (!glfwInit()) {
    Error(ErrorType::Critical, "Could not initialize glfw!");
  }

  this->width = width;
  this->height = height;

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // don't create OpenGL context
  instance = glfwCreateWindow(width, height, title, nullptr, nullptr);
  //glfwSetWindowUserPointer(instance, this);
}

bool mg::Vulkan::createInstance() {
  if (enableValidationLayers && !checkValidationLayerSupport()) {
    Error(ErrorType::Severe, "Validation layers requested, but not available!");
  }

  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pNext = nullptr;
  //appInfo.pApplicationName;
  //appInfo.applicationVersion;
  appInfo.pEngineName = "Magma";
  appInfo.engineVersion = 1;
  appInfo.apiVersion = VK_API_VERSION_1_3;

  return true;
}

bool mg::Vulkan::checkValidationLayerSupport()
{
  // Gather available layers
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  // Check if all predefined validation layers are available
  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound) {
      return false;
    }
  }

  return true;
}