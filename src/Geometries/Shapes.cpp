#include "Primitives/Geometry.hpp"

namespace TotoGL {

PlaneGeometry::PlaneGeometry(const float &width, const float &height)
    : Geometry(
          { { { -width / 2, -height / 2, 0 },
              { 0, 0, 1 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, 0 },
              { 0, 0, 1 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, 0 },
              { 0, 0, 1 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, 0 },
              { 0, 0, 1 },
              { 0, 1 },
              { 1, 1, 1 } } },
          { { 0, 1, 2 }, { 2, 3, 0 } }) {
}

BoxGeometry::BoxGeometry(
    const float &width, const float &height, const float &depth)
    : Geometry(
          { { { -width / 2, -height / 2, depth / 2 },
              { 0, 0, 1 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, depth / 2 },
              { 0, 0, 1 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, depth / 2 },
              { 0, 0, 1 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, depth / 2 },
              { 0, 0, 1 },
              { 0, 1 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, depth / 2 },
              { 1, 0, 0 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, -depth / 2 },
              { 1, 0, 0 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, -depth / 2 },
              { 1, 0, 0 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, depth / 2 },
              { 1, 0, 0 },
              { 0, 1 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, -depth / 2 },
              { 0, 0, -1 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { -width / 2, -height / 2, -depth / 2 },
              { 0, 0, -1 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, -depth / 2 },
              { 0, 0, -1 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, -depth / 2 },
              { 0, 0, -1 },
              { 0, 1 },
              { 1, 1, 1 } },
            { { -width / 2, -height / 2, -depth / 2 },
              { -1, 0, 0 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { -width / 2, -height / 2, depth / 2 },
              { -1, 0, 0 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, depth / 2 },
              { -1, 0, 0 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, -depth / 2 },
              { -1, 0, 0 },
              { 0, 1 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, depth / 2 },
              { 0, 1, 0 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, depth / 2 },
              { 0, 1, 0 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { width / 2, height / 2, -depth / 2 },
              { 0, 1, 0 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { -width / 2, height / 2, -depth / 2 },
              { 0, 1, 0 },
              { 0, 1 },
              { 1, 1, 1 } },
            { { -width / 2, -height / 2, -depth / 2 },
              { 0, -1, 0 },
              { 0, 0 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, -depth / 2 },
              { 0, -1, 0 },
              { 1, 0 },
              { 1, 1, 1 } },
            { { width / 2, -height / 2, depth / 2 },
              { 0, -1, 0 },
              { 1, 1 },
              { 1, 1, 1 } },
            { { -width / 2, -height / 2, depth / 2 },
              { 0, -1, 0 },
              { 0, 1 },
              { 1, 1, 1 } } },
          { { 0, 1, 2 },
            { 2, 3, 0 },
            { 4, 5, 6 },
            { 6, 7, 4 },
            { 8, 9, 10 },
            { 10, 11, 8 },
            { 12, 13, 14 },
            { 14, 15, 12 },
            { 16, 17, 18 },
            { 18, 19, 16 },
            { 20, 21, 22 },
            { 22, 23, 20 } },
          { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 }) {
}

SphereGeometry::SphereGeometry(
    const float &radius, const int &width_segments,
    const int &height_segments) {
    for (int y = 0; y <= height_segments; ++y) {
        for (int x = 0; x <= width_segments; ++x) {
            float xSegment = (float)x / (float)width_segments;
            float ySegment = (float)y / (float)height_segments;
            float xPos = radius * glm::cos(xSegment * 2.0f * PI) *
                glm::sin(ySegment * PI);
            float yPos = radius * glm::cos(ySegment * PI);
            float zPos = radius * glm::sin(xSegment * 2.0f * PI) *
                glm::sin(ySegment * PI);

            vertices().push_back({ { xPos, yPos, zPos },
                                   { xPos, yPos, zPos },
                                   { xSegment, ySegment },
                                   { 1.0f, 1.0f, 1.0f } });

            if (x < width_segments && y < height_segments) {
                uint i1 = y * (width_segments + 1) + x;
                uint i2 = i1 + width_segments + 1;

                triangles().push_back({ i1, i2, i1 + 1 });
                triangles().push_back({ i1 + 1, i2, i2 + 1 });
            }
        }
    }
    update();
}
CylinderGeometry::CylinderGeometry(
    const float &radius_top, const float &radius_bottom, const float &height,
    const int &radial_segments, const int &height_segments,
    const bool &open_ended) {
    for (int y = 0; y <= height_segments; ++y) {
        for (int x = 0; x <= radial_segments; ++x) {
            float u = (float)x / radial_segments;
            float v = (float)y / height_segments;

            float radius = v * (radius_bottom - radius_top) + radius_top;
            float xPos = radius * glm::cos(u * 2.0f * glm::pi<float>());
            float yPos = v * height - height / 2.0f;
            float zPos = radius * glm::sin(u * 2.0f * glm::pi<float>());

            glm::vec3 normal = glm::normalize(glm::vec3(xPos, 0.0f, zPos));

            vertices().push_back({ { xPos, yPos, zPos },
                                   normal,
                                   { u, v },
                                   { 1.0f, 1.0f, 1.0f } });

            if (x < radial_segments && y < height_segments) {
                uint i1 = y * (radial_segments + 1) + x;
                uint i2 = i1 + radial_segments + 1;

                triangles().push_back({ i1, i2, i1 + 1 });
                triangles().push_back({ i1 + 1, i2, i2 + 1 });
                materials().push_back(0);
            }
        }
    }

    if (!open_ended) {
        uint baseIndex = vertices().size();
        for (int x = 0; x <= radial_segments; ++x) {
            float u = (float)x / radial_segments;
            float xPos = radius_top * glm::cos(u * 2.0f * glm::pi<float>());
            float yPos = height / 2.0f;
            float zPos = radius_top * glm::sin(u * 2.0f * glm::pi<float>());

            vertices().push_back({ { xPos, yPos, zPos },
                                   { 0, 1, 0 },
                                   { (xPos / radius_top) / 2.0f + 0.5f,
                                     (zPos / radius_top) / 2.0f + 0.5f },
                                   { 1.0f, 1.0f, 1.0f } });

            if (x < radial_segments) {
                triangles().push_back(
                    { baseIndex, baseIndex + x + 1, baseIndex + x + 2 });
                materials().push_back(1);
            }
        }
        baseIndex = vertices().size();
        for (int x = 0; x <= radial_segments; ++x) {
            float u = (float)x / radial_segments;
            float xPos = radius_top * glm::cos(u * 2.0f * glm::pi<float>());
            float yPos = -height / 2.0f;
            float zPos = radius_top * glm::sin(u * 2.0f * glm::pi<float>());

            vertices().push_back({ { xPos, yPos, zPos },
                                   { 0, -1, 0 },
                                   { (xPos / radius_top) / 2.0f + 0.5f,
                                     (zPos / radius_top) / 2.0f + 0.5f },
                                   { 1.0f, 1.0f, 1.0f } });

            if (x < radial_segments) {
                triangles().push_back(
                    { baseIndex, baseIndex + x + 1, baseIndex + x + 2 });
                materials().push_back(2);
            }
        }
    }
    update();
}

} // namespace TotoGL
