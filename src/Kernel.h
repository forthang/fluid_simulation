#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> 

namespace SPH {
    const float KERNEL_RADIUS = 20.0f;
    const float POLY6 = 315.0f / (64.0f * glm::pi<float>() * powf(KERNEL_RADIUS, 9));
    const float SPIKY_GRAD = -45.0f / (glm::pi<float>() * powf(KERNEL_RADIUS, 6));
    const float VISC_LAP = 45.0f / (glm::pi<float>() * powf(KERNEL_RADIUS, 6));

    inline float poly6Kernel(const glm::vec2& r, float h) {
        float len2 = glm::dot(r, r);
        if(len2 >= h*h || len2 == 0.0f) return 0.0f;
        return POLY6 * powf(h*h - len2, 3);
    }

    inline glm::vec2 spikyGradKernel(const glm::vec2& r, float h) {
        float len = glm::length(r);
        if(len >= h || len == 0.0f) return glm::vec2(0);
        return r/len * SPIKY_GRAD * powf(h - len, 2);
    }

    inline float viscLaplacianKernel(const glm::vec2& r, float h) {
        float len = glm::length(r);
        return VISC_LAP * (h - len);
    }
}