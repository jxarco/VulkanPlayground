#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <optional>

class VulkanApp {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:

    GLFWwindow* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {
            return graphicsFamily.has_value();
        }
    };

    void initWindow();
    void createInstance();
    void enumerateExtensions();
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    void initVulkan();
    void createLogicalDevice();
    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    void mainLoop();
    void cleanup();
};
