#include "Renderer.h"


Renderer::Renderer(RuntimeVars* settings)
    :camera(Camera(settings))
{

}

void Renderer::Draw(Model& model) const {
    glDrawElements(GL_TRIANGLES, model.get_ibo()->GetCount(), GL_UNSIGNED_INT, nullptr);
}


void Renderer::DrawNodeModelVerts(NodeModel& nodes) const {
    nodes.ChangeMVPUniform(camera.GetView());
    glDrawArrays(GL_POINTS, 0, nodes.vert_count);
}
void Renderer::DrawNodeModelEdges(NodeModel& nodes) const {
    glDrawElements(GL_LINES, nodes.edge_count, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 GetModelPositionMat(Position pos) {
    return glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
}


void Renderer::Clear() const{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
