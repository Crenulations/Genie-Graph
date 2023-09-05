#include "Colony.h"

Colony::Colony(int max_nodes, int max_edges, std::vector< unsigned char > gene_buffer)
	: max_nodes(max_nodes), max_edges(max_edges), gene_buffer(gene_buffer)
{

    LoadOperationArray();
    std::cout << "wu" << std::endl;

}

Colony::~Colony() {

    std::cout << "Colony Deleted" << std::endl;

}


void Colony::InitializeColony() {
    read_pos.clear();
    chromo_data.clear();
    active_nodes.clear();
    spike_data.clear();
    excite_data.clear();
    register_A.clear();
    register_B.clear();
    register_C.clear();
    register_D.clear();
    edge_data.clear();
    loc_data.clear();
    vel_data.clear();
    color_data.clear();
    for (int i = 0; i < max_nodes * 1; i++) {
        read_pos.push_back(0);
        active_nodes.push_back(false);
        spike_data.push_back(0);
        excite_data.push_back(0);
        chromo_data.push_back(0);
        register_A.push_back(0);
        register_B.push_back(0);
        register_C.push_back(0);
        register_D.push_back(0);
    }
    for (int i = 0; i < max_edges * 2; i++) {
        edge_data.push_back(0);
        edge_data.push_back(0);
    }
    for (int i = 0; i < max_nodes*3; i++) {
        loc_data.push_back(0);
        loc_data.push_back(0);
        loc_data.push_back(0);

        vel_data.push_back(0);
        vel_data.push_back(0);
        vel_data.push_back(0);
        //color_data.push_back(randFloat());
        color_data.push_back(0.3);
        color_data.push_back(0.3);
        color_data.push_back(0.3);
    }

    active_nodes[0] = true;
    
    a_count = 1;
    nodeModel.CreateVAO(loc_data, color_data);
    nodeModel.CreateIBO(&edge_data[0], edge_data.size());
}

void Colony::UpdateNodes() {
    float scale = 1;
    float drag = 0.9;

    spike_data[0] = spike_data[0] * 0.95;
    color_data[0] = spike_data[0];
    color_data[1] = spike_data[0];
    color_data[2] = spike_data[0];

   
    for (int i = 1; i < a_count; i++) { //Skip moving vert 0
        int offset = i * 3;

        vel_data[offset]     = (vel_data[offset])  * drag;
        vel_data[offset + 1] = (vel_data[offset+1])* drag;
        vel_data[offset + 2] = (vel_data[offset+2]) * drag;
      
        loc_data[offset]   += (vel_data[offset])   * scale;
        loc_data[offset+1] += (vel_data[offset+1]) * scale;
        loc_data[offset+2] += (vel_data[offset+2]) * scale;

        
        vel_data[offset] += sin((randFloat() - 0.50)) * 0.005;;
        vel_data[offset+ 1] += sin((randFloat() - 0.5)) * 0.005;;
        vel_data[offset+ 2] += sin((randFloat() - 0.5)) * 0.005;;


        spike_data[i] = spike_data[i] * 0.95;
        
        if(spike_data[i]>=0.3)
            color_data[offset] = spike_data[i];
        color_data[offset + 1] = spike_data[i];
        color_data[offset + 2] = spike_data[i];

        excite_data[i] += (randFloat() - 0.5) * 0.01;// Randomize
        if (excite_data[i]>1)
            SpikeNode(i);
    }

    nodeModel.SwapLocationBuffer(&loc_data[0]);
    nodeModel.SwapEdgeBuffer(&edge_data[0]);
    nodeModel.SwapColorBuffer(&color_data[0]);
}

void Colony::UpdateEdges() {
    float ks = 0.1f; // stiffness
    float L0 = 0.3f; //res length

    for (int i = 0; i < e_count; i++) {
        int offset = i * 2;
        int n_1 = edge_data[offset] * 3;
        int n_2 = edge_data[offset+1] * 3;

        float d_x = (loc_data[n_2]     - loc_data[n_1]);
        float d_y = (loc_data[n_2 + 1] - loc_data[n_1 + 1]);
        float d_z = (loc_data[n_2 + 2] - loc_data[n_1 + 2]);
        float dist = VecMag(d_x, d_y, d_z);

        float s_f = -ks * (dist - L0); // Spring Force

        float f_x = (d_x * s_f);//+ dmp_x;
        float f_y = (d_y * s_f);//+ dmp_y;
        float f_z = (d_z * s_f);//+ dmp_z;

        vel_data[n_1]     -= f_x;
        vel_data[n_1 + 1] -= f_y;
        vel_data[n_1 + 2] -= f_z;

        vel_data[n_2]     += f_x;
        vel_data[n_2 + 1] += f_y;
        vel_data[n_2 + 2] += f_z;
    }
}

NodeModel* Colony::GetNodeModel() {
    return &nodeModel;
}

void Colony::Update() { // Updates Entire Colony

    tick_count++;

    if (tick_count % 5 == 1) { // Spike the 0th node on interval
        SpikeNode(0);
    }

    for (int i = 0; i < a_count && i < max_nodes; i++) {
        ProcessNode(i);
    }
}



void Colony::ProcessNode(int node) { // Updates individual nodes
    cid = node;
    if (!active_nodes[cid])
        return;
    cid_read_pos = read_pos[cid];
    break_process = false;

    int chrome_offset = (256 * chromo_data[cid]);

    unsigned char operation = gene_buffer[chrome_offset + cid_read_pos];
    unsigned char operand = gene_buffer[chrome_offset + (cid_read_pos + 1)];

    (*this.*op_array[operation])(operand);

    if (read_pos[cid] > 256)
        break_process = true;

    if (break_process)
        active_nodes[cid] = false;
    else
        read_pos[cid] = (cid_read_pos + 2);
}


void Colony::LoadOperationArray() {

    // Okay so I wanted to make this function (and op_array) static but the operation array is basically
    // an array of pointers to these instatiated functions so idk

    for (int i = 0; i < 256; i++) {
        op_array[i] = &Colony::op_00;
    }
    op_array[0] = &Colony::op_00;
    op_array[3] = &Colony::op_03;

    op_array[68] = &Colony::op_44;
    op_array[128] = &Colony::op_80;


    op_array[161] = &Colony::op_A1;
    op_array[162] = &Colony::op_A2;
    op_array[163] = &Colony::op_A3;
    op_array[175] = &Colony::op_AF;

    op_array[177] = &Colony::op_B1;
    op_array[178] = &Colony::op_B2;
    op_array[179] = &Colony::op_B3;
    op_array[191] = &Colony::op_BF;

    op_array[193] = &Colony::op_C1;
    op_array[194] = &Colony::op_C2;
    op_array[195] = &Colony::op_C3;
    op_array[202] = &Colony::op_CA;
    op_array[203] = &Colony::op_CB;
    op_array[207] = &Colony::op_CF;

    op_array[209] = &Colony::op_D1;
    op_array[210] = &Colony::op_D2;
    op_array[211] = &Colony::op_D3;
    op_array[223] = &Colony::op_DF;


    op_array[255] = &Colony::op_FF;
}

// Individual Node Actions

void Colony::DivideNode(unsigned int idx) {
    int parent_off = idx * 3;
    int child_off = a_count * 3;

    if (a_count > max_nodes - 5)
        return;

    active_nodes[a_count] = true;

    loc_data[child_off] = loc_data[parent_off] + ((randFloat() - 0.5) / 1);
    loc_data[child_off + 1] = loc_data[parent_off + 1] + ((randFloat() - 0.5) / 1);
    loc_data[child_off + 2] = loc_data[parent_off + 2] + ((randFloat() - 0.5) / 1);

    register_A[a_count] = register_A[idx];
    register_B[a_count] = register_B[idx];
    register_C[a_count] = register_C[idx];
    register_D[a_count] = register_D[idx];
    read_pos[a_count] = (int)register_D[idx];
    chromo_data[a_count] = chromo_data[idx];


    edge_data[(e_count * 2)] = idx;
    edge_data[(e_count * 2) + 1] = a_count;

    a_count++;
    e_count++;
}

void Colony::SpikeNode(unsigned int idx) {
    excite_data[idx] -= 1;
    spike_data[idx] = 1;

    for (int i = 0; i < e_count; i++) {
        int offset = i * 2;

        if (edge_data[offset] == idx) {
            excite_data[edge_data[offset + 1]] += 0.95;
        }
    }
}

void Colony::ConnectNodes(unsigned int idx, int val) {
    for (int i = 0; i < a_count; i++) {
        if (register_C[i] == val) {
            
            edge_data[(e_count * 2)] = idx;
            edge_data[(e_count * 2) + 1] = i;
            e_count++;
        }
    }
}



