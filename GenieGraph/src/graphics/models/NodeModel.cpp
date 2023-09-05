#include "NodeModel.h"

NodeModel::NodeModel()
    :shader(Shader("res/shaders/Particle.shader"))
{
    std::cout << "Node model created " << std::endl;

    Bind();
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0);
}

NodeModel::~NodeModel(){
    std::cout << "Node Model Deleted" << std::endl;

}

void NodeModel::CreateVAO(std::vector< float > loc_data, std::vector< float > color_data) {


    vbo.Create(&loc_data[0], loc_data.size() * sizeof(float));

    vbo_color.Create(&color_data[0], color_data.size() * sizeof(float));


    vert_count = loc_data.size() / 3;
    std::cout << "VERT COUNT: " << vert_count << std::endl;


    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout, 0);
    layout.Push<float>(3);
    vao.AddBuffer(vbo_color, layout, 1);
}

void NodeModel::CreateIBO(const void* edge_data, unsigned int count) {
    edge_count = count;
    ibo.Create(edge_data, count * sizeof(unsigned int));
}

void NodeModel::SwapLocationBuffer(const void* loc_data) { // Maybe store pointers within vbo, ibo?
    vbo.Update(loc_data, vert_count * 3 * sizeof(float));
}

void NodeModel::SwapEdgeBuffer(const void* edge_data) {
    ibo.Update(edge_data, edge_count * sizeof(unsigned int));
}

void NodeModel::SwapColorBuffer(const void* color_data) {
    vbo_color.Update(color_data, vert_count * 3 * sizeof(unsigned int));
}


void NodeModel::Bind() {
    vao.Bind();
    ibo.Bind();
    shader.Bind();
}

void NodeModel::ChangeMVPUniform(glm::mat4 MVP) {
    shader.SetUniformMat4f("u_MVP", MVP);
}
