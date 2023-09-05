#include "Model.h";




Model::Model(const std::string& obj_filepath, const std::string& shader_filepath)
    :shader(Shader(shader_filepath))
{

    ParseModelFile(obj_filepath);

    //Set default color
    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0);
}

Model::~Model() {
    std::cout << "DELETING MODEL" << std::endl;
}


void Model::Bind() {
    shader.Bind();
    ibo.Bind();
    vao.Bind();
}

void Model::ChangeMVPUniform(glm::mat4 MVP) {
    shader.SetUniformMat4f("u_MVP", MVP);
}

void Model::ChangeColorUniform(float r, float g, float b, float a){
    shader.SetUniform4f("u_Color",r,g,b,a);
}

VertexArray* Model::get_vao() {
    return &vao;
}
IndexBuffer* Model::get_ibo() {
    return &ibo;
}
Shader* Model::get_shader() {
    return &shader;
}

void Model::ParseModelFile(const std::string& filepath) {

    std::ifstream stream(filepath);
    std::string line;

    std::vector< float > vbo_data;
    std::vector< unsigned int > ibo_data;

    while (getline(stream, line)) {
        // Print ever line
        // std::cout << line << std::endl;

        if (line[0] == 'v' && line[1] == ' ') { // VBO VERTICIES
            std::string vert_str;
            for (std::string::size_type i = 2; i < line.size(); i++) { // File parsing is shit here
                char c = line[i];
                if (c != ' ') {
                    vert_str += c;
                }
                else {
                    //std::cout << vert_str << " ";
                    vbo_data.push_back(std::stof(vert_str));
                    vert_str = "";
                }
            }
            if (vert_str != "") {
                //std::cout << vert_str << std::endl;
                vbo_data.push_back(std::stof(vert_str));
                vert_str = "";
            }
        }

        if (line[0] == 'f' && line[1] == ' ') { // IBO INDICIES
            std::string indx_str;
            for (std::string::size_type i = 2; i < line.size(); i++) {
                char c = line[i];
                if (c != ' ' && c != '/') {
                    indx_str += c;
                }
                else {
                    //std::cout << indx_str;
                    //if (c == '/')
                        //std::cout << '/';
                    //else
                       // std::cout << ' ';
                    unsigned int index = std::stoul(indx_str) - 1;
                    ibo_data.push_back(index);
                    indx_str = "";
                }

            }
            if (indx_str != "") {
                //std::cout << indx_str << std::endl;
                ibo_data.push_back(std::stoul(indx_str) -1);
                indx_str = "";
            }
        }
    }

    float* vbo_array = &vbo_data[0];
    vbo.Create(vbo_array, vbo_data.size() * sizeof(float));

    std::cout << "VERT COUNT: " << vbo_data.size() << std::endl;

    unsigned int* ibo_array = &ibo_data[0];
    ibo.Create(ibo_array, ibo_data.size());

    std::cout << "INDEX COUNT: " << ibo_data.size() << std::endl;

    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout, 0);


    /*for (int i = 0; i < vbo_data.size(); i++) {
        if (i % 3 == 0)
            std::cout << std::endl;
        std::cout << " " << vbo_array[i];
    }
    std::cout << std::endl << "_____" << std::endl;
    for (int i = 0; i < ibo_data.size(); i++) {
        if (i % 3 == 0)
            std::cout << std::endl;
        std::cout << " " << ibo_array[i];
    }
    std::cout << std::endl << "_____" << std::endl;*/
    

}

void Model::MakeUnitCube() {
    float positions[] = {
        1.000000, - 1.000000, - 1.000000,
        1.000000, - 1.000000, 1.000000,
        - 1.000000, - 1.000000, 1.000000,
        - 1.000000, - 1.000000, - 1.000000,
        1.000000, 1.000000, - 1.000000,
        1.000000, 1.000000, 1.000000,
        - 1.000000, 1.000000, 1.000000,
        - 1.000000, 1.000000, - 1.000000,
    };
    vbo.Create(positions, 8 * 3 * sizeof(float));

    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout, 0);

    unsigned int indices[] = {
        2,3,4,
        8,7,6,
        5,6,2,
        6,7,3,
        3,7,8,
        1,4,8,
        1,2,4,
        5,8,6,
        1,5,2,
        2,6,3,
        4,3,8,
        5,1,8,
    };
    ibo.Create(indices, 12*3);
}

void Model::MakeSquare() {
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,

        -0.5f, -0.5f, 1.0f,
         0.5f, -0.5f, 1.0f,
         0.5f,  0.5f, 1.0f,
        -0.5f,  0.5f, 1.0f,
    };

    vbo.Create(positions, 4 * 3 * 2 * sizeof(float));

    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout, 0);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
    };

    ibo.Create(indices, 12);
}