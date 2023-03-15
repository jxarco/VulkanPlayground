#version 450

layout (binding = 0) uniform ParameterUBO {
    mat4 model;
    mat4 view;
    mat4 proj;
    float deltaTime;
    vec3 foo;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    fragColor = inColor.rgb;
    fragTexCoord = inTexCoord;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
}