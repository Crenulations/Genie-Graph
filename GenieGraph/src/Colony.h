#pragma once
#include "graphics/models/NodeModel.h"

class Colony {
public:
	int max_nodes, max_edges;

	std::vector< unsigned char > gene_buffer;

	int a_count = 1; // Number of active nodes in buffer
	int e_count = 0; // Number of active edges in buffer

	int tick_count = 0; // Number of ticks

	std::vector< float > loc_data;
	std::vector< float > vel_data;
	std::vector< float > color_data;

	std::vector< unsigned int > edge_data;
	std::vector< bool > active_nodes;

	std::vector< float > spike_data;
	std::vector< float > excite_data;
	std::vector< unsigned int > read_pos;
	std::vector< unsigned int > chromo_data;
	std::vector< unsigned char > register_A;
	std::vector< unsigned char > register_B;
	std::vector< unsigned char > register_C;
	std::vector< unsigned char > register_D;

	NodeModel nodeModel;


	Colony(int max_nodes, int max_edges, std::vector< unsigned char > gene_buffer);
	~Colony();

	void InitializeColony();

	NodeModel* GetNodeModel();

	void UpdateNodes();
	void UpdateEdges();

	void DivideNode(unsigned int i);
	void SpikeNode(unsigned int i);
	void ConnectNodes(unsigned int idx, int val);

	int cid = 0; // Current Node ID
	int cid_read_pos = 0;
	bool break_process = true;

	void ProcessNode(int cid);
	void Update();

	typedef void(Colony::* operation)(unsigned char operand);
	operation op_array[256];

	void LoadOperationArray();







	inline void op_00(unsigned char operand) { // Empty

	}

	inline void op_03(unsigned char operand) { // Jump
		if(operand<256)
			cid_read_pos = (operand - 2);
	}

	inline void op_80(unsigned char operand) { // Switch chromosome
		if (operand < 8) {
			cid_read_pos = -2; // +2 ended at the end of cycle
			chromo_data[cid] = (int)operand;
		}
	}

	inline void op_44(unsigned char operand) {  // Divide
		DivideNode(cid);
	}



	inline void op_A1(unsigned char operand) { // Load A
		register_A[cid] = operand;
	}
	inline void op_A2(unsigned char operand) { // Decriment A
		register_A[cid]--;
	}
	inline void op_A3(unsigned char operand) { // incriment A
		register_A[cid]++;
	}
	inline void op_AF(unsigned char operand) { // If reg_A > skip
		if (register_A[cid] > operand) {
			cid_read_pos += 2; // Skip next operation
		}
	}

	inline void op_B1(unsigned char operand) { // Load B
		register_B[cid] = operand;
	}
	inline void op_B2(unsigned char operand) { // Decriment B
		register_B[cid]--;
	}
	inline void op_B3(unsigned char operand) { // incriment B
		register_B[cid]++;
	}
	inline void op_BF(unsigned char operand) { // If reg_B > skip
		if (register_B[cid] > operand) {
			cid_read_pos += 2; // Skip next operation
		}
	}


	inline void op_C1(unsigned char operand) { // Load C
		register_C[cid] = operand;
	}
	inline void op_C2(unsigned char operand) { // Decriment C
		register_C[cid]--;
	}
	inline void op_C3(unsigned char operand) { // incriment C
		register_C[cid]++;
	}
	inline void op_CF(unsigned char operand) { // If reg_C > skip
		if (register_C[cid] > operand) {
			cid_read_pos += 2; // Skip next operation
		}
	}
	inline void op_CA(unsigned char operand) {  // Connect to Creg by operand 
		ConnectNodes(cid, operand);
	}
	inline void op_CB(unsigned char operand) {  // Connect to Creg by self Breg 
		ConnectNodes(cid, register_B[cid]);
	}


	inline void op_D1(unsigned char operand) { // Load D
		register_D[cid] = operand;
	}
	inline void op_D2(unsigned char operand) { // Decriment D
		register_D[cid]--;
	}
	inline void op_D3(unsigned char operand) { // incriment D
		register_D[cid]++;
	}
	inline void op_DF(unsigned char operand) { // If reg_D > skip
		if (register_D[cid] > operand) {
			cid_read_pos += 2; // Skip next operation
		}
	}

	inline void op_FF(unsigned char operand) {
		break_process = true;
	}
};