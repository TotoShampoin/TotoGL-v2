#pragma once

#include "Materials/Material.hpp"
#include "Primitives/Primitives.hpp"
#include "Primitives/Uniform.hpp"
#include <map>
#include <memory>
#include <string>

namespace TotoGL {

class ShaderMaterial : public Material {
public:
    ShaderMaterial(const std::string& vertex_source, const std::string& fragment_source);
    ~ShaderMaterial() override;
    static std::shared_ptr<ShaderMaterial> create(const std::string& vertex_source, const std::string& fragment_source) {
        return std::make_shared<ShaderMaterial>(vertex_source, fragment_source);
    }

    const Uniform& uniform(const std::string& name) const { return uniform(uniformId(name)); }

    Uniform& uniform(const std::string& name) { return uniform(uniformId(name)); }

    void applyModel(const Matrix4&) override;
    void applyCamera(const std::shared_ptr<Camera>&) override;
    void applyLight(const std::shared_ptr<Light>&, const size_t& = 0) override;
    void applyLights(const std::vector<std::shared_ptr<Light>>&) override;
    void activate() override;
    void deactivate() override;
private:
    uint _program_id;
    std::map<int, Uniform> _uniforms;

    const Uniform& uniform(const int& id) const { return _uniforms.at(id); }
    Uniform& uniform(const int& id) { return _uniforms[id]; }
    int uniformId(const std::string& name) const;
};

extern const char* simple_vertex;

}


