#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

class VulkanApp {

public:
    void run();

private:

    GLFWwindow* window;
    
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device; // Logical Device

    VkQueue graphicsQueue;

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    // VkInstance, Extensions and Validation Layers
    void createInstance();
    void listSupportedExtensions();
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();

    // Physical and Logical Devices
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    void createLogicalDevice();

    // Commands and Queues
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void setupDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
};
