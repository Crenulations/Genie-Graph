#include "ColonyManager.h"

ColonyManager::ColonyManager(int max_nodes, int max_edges)
	:max_nodes(max_nodes), max_edges(max_edges)
{

    CreateColony(LoadGeneBuffer("res/genes/gene_1.g"));
    CreateColony(LoadGeneBuffer("res/genes/gene_spiking.g"));
    CreateColony(LoadGeneBuffer("res/genes/gene_triangles.g"));
    CreateColony(LoadGeneBuffer("res/genes/gene_1.g"));
    CreateColony(LoadGeneBuffer("res/genes/gene_spiking.g"));
    CreateColony(LoadGeneBuffer("res/genes/gene_triangles.g"));
    //CreateColony(CreateRandomGeneBuffer());
    //CreateColony(CreateRandomGeneBuffer());
    //CreateColony(CreateRandomGeneBuffer());
    //CreateColony(CreateRandomGeneBuffer());
    //CreateColony(CreateRandomGeneBuffer());
    //CreateColony(CreateRandomGeneBuffer());
    colonies[0]->InitializeColony();
    colonies[1]->InitializeColony();
    colonies[2]->InitializeColony();
    colonies[3]->InitializeColony();
    colonies[4]->InitializeColony();
    colonies[5]->InitializeColony();

}

ColonyManager::~ColonyManager() {
    SaveGeneBuffer("res/genes/gene_r.g");
}

void ColonyManager::CreateColony(std::vector< unsigned char > gene_buffer) {

    //std::vector< unsigned char > gene_buffer = LoadGeneBuffer(geneURL);

    Colony* col = new Colony(max_nodes, max_edges, gene_buffer);

    colonies.push_back(col);
}

std::vector< unsigned char > ColonyManager::LoadGeneBuffer(const std::string& filepath) {
    unsigned int count = 0;
    std::vector< unsigned char > gene_buffer;


    std::basic_ifstream<unsigned char> input_file(filepath, std::ifstream::binary);
    unsigned char byte = 0;
    while (input_file.get(byte)) {

        gene_buffer.push_back(byte);
        count++;
    }
    input_file.close();
    return gene_buffer;
}
void ColonyManager::SaveGeneBuffer(const std::string& filepath) {
    std::ofstream output(filepath, std::ofstream::binary);
    for (int i = 0; i < colonies[0]->gene_buffer.size(); i++) {
        output << colonies[0]->gene_buffer[i];
    }
    output.close();
}
std::vector< unsigned char > ColonyManager::CreateRandomGeneBuffer() {
    std::random_device engine;
    std::vector< unsigned char > gene_buffer;

    for (int i = 0; i < 256 * 16; i++) {
        gene_buffer.push_back(engine());
    }
    return gene_buffer;
}



