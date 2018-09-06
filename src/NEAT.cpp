#ifndef NEAT_CPP
#define NEAT_CPP

#include "NEAT.hpp"
using namespace ANN_USM;

/*
	IDEAS PARA OPTIMIZAR EL C�DIGO:
		2) INTEGRAR LISTAS DE NODOS Y DE CONNECCIONES CON LOS NODOS Y CONECCIONES ACTUALES (ESO SE DEBE IMPLEMENTAR DESDE GENETIC ENCODING TAMBI�N
		POR EJEMPLO EN EL MOMENTO EN QUE SE CARGA UN GENOMA).


	OBSERVAR QUE NO DAN LOS MISMOS RESULTADOS CON LAS DOS VERSIONES DE CROSSOVER!!
*/

Genetic_Encoding Population::put_randoms_weight(Genetic_Encoding organism){
	for (int i = 0; i < (int)organism.Lconnection_genes.size(); ++i)
		organism.Lconnection_genes[i].weight=2.0*(rand()%10000)/10000.0-1.0;
	return organism;
}

Genetic_Encoding Population::mutation_change_weight(Genetic_Encoding organism){
	double delta;
	for(int i = 0; i < (int)organism.Lconnection_genes.size(); i++ ){
		if( rand()/(double)RAND_MAX <= PROBABILITY_CHANGE_WEIGHT ){
			delta = 2*(rand()%RAND_MAX)/(double)RAND_MAX-1;
			organism.Lconnection_genes.at(i).weight = delta*0.2 + 0.8*organism.Lconnection_genes.at(i).weight;
		}
	}
	return organism;
}

/*Population::Population(string path1,string path2, string _name, string _save_path){

	name = (char *)malloc(strlen(_name.c_str())+1);
	save_path = (char *)malloc(strlen(_save_path.c_str())+1);
	strcpy(name,_name.c_str());
	strcpy(save_path,_save_path.c_str());

	current_generation=0;

	load_user_definitions(path1);
	lenght = POPULATION_MAX;
	Genetic_Encoding _organism;
	_organism.load(path2);

	expectative_iterations = 1;
	_organism.niche=0;
	fitness_champion = 0;
	last_innovation=0;
	row_orderer_list = _organism.row_orderer_list;
	last_row = _organism.row_orderer_list.size();
	champion = _organism;
	Niche niche_temp;

	for (int i = 0; i < 5; ++i)
	{
		fitness_mean_of_past_generation.push_back(0.0);
	}
	

	// ================FOR REDUNDANCE ============
	for (int i = 0; i < (int)_organism.Lconnection_genes.size(); ++i){
		int in = _organism.Lconnection_genes.at(i).in;
		int out = _organism.Lconnection_genes.at(i).out;
		while((int)historical_innovation.size()-1 < in)
		{
			vector <int> temp;
			historical_innovation.push_back(temp);
		}
		while((int)historical_innovation.at(in).size()-1 < out)
		{
			historical_innovation.at(in).push_back(-1);
		}
		if(historical_innovation.at(in).at(out) < 0){
			historical_innovation.at(in).at(out) = _organism.Lconnection_genes.at(i).innovation;
			if(last_innovation < _organism.Lconnection_genes.at(i).innovation)
				last_innovation = _organism.Lconnection_genes.at(i).innovation;
		}
	}
	last_innovation++;
	//============================================

	last_node = (int)_organism.Lnode_genes.size()-1;

	for (int i = 0; i < POPULATION_MAX; ++i)
		organisms.push_back( put_randoms_weight(_organism) );

	cerr << "organisms.size(): " << organisms.size() << "\tPOPULATION_MAX:" << POPULATION_MAX  << endl;

	prev_organisms.push_back(_organism);
	niche_temp.organism_position.push_back(0);
	niche_temp.exist=true;
	niche_temp.niche_champion_position=0;
	current_niches.push_back(niche_temp);
	spatiation();

}*/

Population::Population(char path1[],char path2[], char _name[], char _save_path[]){
	name = (char *)malloc(strlen(_name)+1);
	save_path = (char *)malloc(strlen(_save_path)+1);
	strcpy(name,_name);
	strcpy(save_path,_save_path);

	current_generation=0;

	load_user_definitions(path1);
	lenght = POPULATION_MAX;
	Genetic_Encoding _organism;
	_organism.load(path2);

	expectative_iterations = 1;
	_organism.niche=0;
	fitness_champion = 0;
	last_innovation=0;
	row_orderer_list = _organism.row_orderer_list;
	last_row = _organism.row_orderer_list.size();
	champion = _organism;
	Niche niche_temp;

	for (int i = 0; i < 5; ++i)
	{
		fitness_mean_of_past_generation.push_back(0.0);
	}

	// ================FOR REDUNDANCE ============
	for (int i = 0; i < (int)_organism.Lconnection_genes.size(); ++i){
		int in = _organism.Lconnection_genes.at(i).in;
		int out = _organism.Lconnection_genes.at(i).out;
		while((int)historical_innovation.size()-1 < in)
		{
			vector <int> temp;
			historical_innovation.push_back(temp);
		}
		while((int)historical_innovation.at(in).size()-1 < out)
		{
			historical_innovation.at(in).push_back(-1);
		}
		if(historical_innovation.at(in).at(out) < 0){
			historical_innovation.at(in).at(out) = _organism.Lconnection_genes.at(i).innovation;
			if(last_innovation < _organism.Lconnection_genes.at(i).innovation)
				last_innovation = _organism.Lconnection_genes.at(i).innovation;
		}
	}
	last_innovation++;
	//============================================

	last_node = (int)_organism.Lnode_genes.size()-1;

	for (int i = 0; i < POPULATION_MAX; ++i)
		organisms.push_back( put_randoms_weight(_organism) );

	cerr << "organisms.size(): " << organisms.size() << "\tPOPULATION_MAX:" << POPULATION_MAX  << endl;

	prev_organisms.push_back(_organism);
	niche_temp.organism_position.push_back(0);
	niche_temp.exist=true;
	niche_temp.niche_champion_position=0;
	//current_niches.push_back(niche_temp);
	bestHistoricalFitness = 0.0;
	vector <Niche> t_niches;
	current_niches = Speciate(t_niches, organisms);
	//spatiation();
}

Population::Population(char path1[],char path2[], char _name[], char _save_path[], int simulatorsAmount){

	name = (char *)malloc(strlen(_name)+1);
	save_path = (char *)malloc(strlen(_save_path)+1);
	strcpy(name,_name);
	strcpy(save_path,_save_path);

	current_generation=0;

	load_user_definitions(path1, simulatorsAmount);
	lenght = POPULATION_MAX;
	Genetic_Encoding _organism;
	_organism.load(path2);

	expectative_iterations = 1;
	_organism.niche=0;
	fitness_champion = 0;
	last_innovation=0;
	row_orderer_list = _organism.row_orderer_list;
	last_row = _organism.row_orderer_list.size();
	champion = _organism;
	Niche niche_temp;

	for (int i = 0; i < 5; ++i)
	{
		fitness_mean_of_past_generation.push_back(0.0);
	}
	

	// ================FOR REDUNDANCE ============
	for (int i = 0; i < (int)_organism.Lconnection_genes.size(); ++i){
		int in = _organism.Lconnection_genes.at(i).in;
		int out = _organism.Lconnection_genes.at(i).out;
		while((int)historical_innovation.size()-1 < in)
		{
			vector <int> temp;
			historical_innovation.push_back(temp);
		}
		while((int)historical_innovation.at(in).size()-1 < out)
		{
			historical_innovation.at(in).push_back(-1);
		}
		if(historical_innovation.at(in).at(out) < 0){
			historical_innovation.at(in).at(out) = _organism.Lconnection_genes.at(i).innovation;
			if(last_innovation < _organism.Lconnection_genes.at(i).innovation)
				last_innovation = _organism.Lconnection_genes.at(i).innovation;
		}
	}
	last_innovation++;
	//============================================

	last_node = (int)_organism.Lnode_genes.size()-1;

	for (int i = 0; i < POPULATION_MAX; ++i)
		organisms.push_back( put_randoms_weight(_organism) );


	prev_organisms.push_back(_organism);
	niche_temp.organism_position.push_back(0);
	niche_temp.exist=true;
	niche_temp.niche_champion_position=0;
	//current_niches.push_back(niche_temp);
	bestHistoricalFitness = 0.0;
	vector <Niche> t_niches;
	current_niches = Speciate(t_niches, organisms);
	//spatiation();
}

Genetic_Encoding Population::mutation_node(Genetic_Encoding organism){
	int number_of_connections = organism.Lconnection_genes.size();
	int connection_to_mutate;
	int innov1,innov2, node, row;
	Discrete_Probabilities sack_of_nodes_to_take;
	vector <int> inverse_to_connections;


	// Se obtienen todos los candidatos que cumplen con el requisito;
	for(int i=0; i < number_of_connections; i++ ){
		if(  organism.Lconnection_genes.at(i).exist && organism.Lconnection_genes.at(i).enable ){
			node = obtain_historical_node(organism.Lconnection_genes.at(i).in, organism.Lconnection_genes.at(i).out);
			if(node < (int)organism.Lnode_genes.size()){
				if(!organism.Lnode_genes.at(node).exist) {
					sack_of_nodes_to_take.add_element(0.0);
					inverse_to_connections.push_back(i);
				}
			}else{
				sack_of_nodes_to_take.add_element(0.0);
				inverse_to_connections.push_back(i);
			}
		}
	}



	if(inverse_to_connections.size() == 0){
		cerr << "Error::Mutation_node()::Is imposible that no exist node to mutate";
		exit(1);
	}


	connection_to_mutate = inverse_to_connections.at(sack_of_nodes_to_take.take_one_randomly());
	node = obtain_historical_node(organism.Lconnection_genes.at(connection_to_mutate).in, organism.Lconnection_genes.at(connection_to_mutate).out);
	row = obtain_row(node, organism.Lnode_genes.at(organism.Lconnection_genes.at(connection_to_mutate).in).row, organism.Lnode_genes.at( organism.Lconnection_genes.at(connection_to_mutate).out ).row );
	organism.add_node(node, row ,HIDDEN);
	organism.row_orderer_list = row_orderer_list;
	// add connections
	organism.Lconnection_genes.at(connection_to_mutate).enable=0; // disabling old connection.
	innov1 = obtain_innovation(organism.Lconnection_genes.at(connection_to_mutate).in, node);
	innov2 = obtain_innovation(node, organism.Lconnection_genes.at(connection_to_mutate).out);
	organism.add_connection(innov1, organism.Lconnection_genes.at(connection_to_mutate).in, node, 1.0);
	organism.add_connection(innov2, node, organism.Lconnection_genes.at(connection_to_mutate).out, organism.Lconnection_genes.at(connection_to_mutate).weight);
	return organism;
}

int Population::obtain_row(int node, int row_node_initial_in, int row_node_initial_out){

	try{
		if(historical_row.at(node) >= 0) {
			return historical_row.at(node);
		}
	}
	catch (const std::out_of_range& oor){}



	int row_position_in(-1);
	int row_position_out(-1);
	bool flag_in(false), flag_out(false);
	for (int i = 0; i < (int)row_orderer_list.size(); ++i)
	{
		if(!flag_in) 	if(row_node_initial_in == row_orderer_list.at(i)) {  row_position_in =  i; flag_in=true; }
		if(!flag_out)	if(row_node_initial_out == row_orderer_list.at(i)){  row_position_out = i; flag_out=true;}
		if(flag_in && flag_out) break;
	}

	if(row_position_in == -1 || row_position_out == -1 ){
		cerr << "ERROR::IN OBTAIN_ROW FUNCTION::" << row_node_initial_in << "\t" << row_position_in << "\t" << row_node_initial_out << "\t" << row_position_out << "\t" << row_orderer_list.size() << "\n" << "Error:: Function obtain_row :: Row_node_in or row_node_out does not exist .\n";
		exit(1);
	}

	while((int)historical_row.size()-1 < node)
	{
		historical_row.push_back(-1);
	}
	
	if(historical_row.at(node) >= 0) {
		return historical_row.at(node);
	}


	if(row_position_in == row_position_out ){
		return row_node_initial_in;
	}

	if(abs(row_position_out - row_position_in) == 1 ){
		
		historical_row.at(node) = last_row;
		if(row_position_out > row_position_in)row_orderer_list.insert(row_orderer_list.begin() + row_position_in + 1, last_row);
		else row_orderer_list.insert(row_orderer_list.begin() + row_position_in - 1, last_row);
		last_row++;
		return historical_row.at(node);
	}
	else{
		if(row_position_in > row_position_out){
			historical_row.at(node) = row_orderer_list.at(row_position_in - 1);
		}
		else
			historical_row.at(node) = row_orderer_list.at(row_position_in + 1);
		return historical_row.at(node);
	}




}

// RECORDAR: son inicial in y inicial out, esa es la idea.
int Population::obtain_historical_node(int in, int out){
	while((int)historical_nodes.size()-1 < in)
	{
		vector <int> temp;
		historical_nodes.push_back(temp);
	}
	while((int)historical_nodes.at(in).size()-1 < out)
	{
		historical_nodes.at(in).push_back(-1);
	}
	if(historical_nodes.at(in).at(out) < 0){
		last_node = last_node + 1;
		historical_nodes.at(in).at(out) = last_node;
	}
	return historical_nodes.at(in).at(out);
}

int Population::obtain_innovation(int in, int out){
	while((int)historical_innovation.size()-1 < in)
	{
		vector <int> temp;
		historical_innovation.push_back(temp);
	}
	while((int)historical_innovation.at(in).size()-1 < out)
	{
		historical_innovation.at(in).push_back(-1);
	}
	if(historical_innovation.at(in).at(out) < 0){
		historical_innovation.at(in).at(out) = last_innovation;
		last_innovation++;
	}
	return historical_innovation.at(in).at(out);
}

Genetic_Encoding Population::mutation_connection(Genetic_Encoding organism){
	int innovation(-1);
	int number_of_nodes = (int)organism.Lnode_genes.size();
	Discrete_Probabilities sack_of_nodes_to_take;
	vector < vector < int > > inverse_to_nodes;


	
	//generando la lista inverstida para hacer más fácil el procedimiento posterior.
	vector <int> inverted_orderer_list; // input: row output:place
	for(int i=0; i < (int)row_orderer_list.size(); i++ ){
		for(int j=0; j < (int)row_orderer_list.size(); j++ ){
			if(i == row_orderer_list.at(j)) inverted_orderer_list.push_back(j);
		}
	}
	for(int in = 0; in < number_of_nodes; in++){
		for(int out=0; out < number_of_nodes; out++){
			if(in != out){
				if(organism.Lnode_genes.at(in).exist  && organism.Lnode_genes.at(out).exist){
						innovation = obtain_innovation(in, out);
						if((int)organism.Lconnection_genes.size() - 1 < innovation){
							sack_of_nodes_to_take.add_element(0.0);
							vector <int> temp_vect;
							temp_vect.push_back(in);
							temp_vect.push_back(out);
							inverse_to_nodes.push_back(temp_vect);
						}
						else if(!organism.Lconnection_genes[innovation].exist){
							sack_of_nodes_to_take.add_element(0.0);
							vector <int> temp_vect;
							temp_vect.push_back(in);
							temp_vect.push_back(out);
							inverse_to_nodes.push_back(temp_vect);
						}
					
				}
			}
		}
	}
	if(inverse_to_nodes.size() == 0){ // No existe ningún par de nodos que no estén conectados anteriormente
		return organism;
	}
	int randoms_nodes = sack_of_nodes_to_take.take_one_randomly();
	innovation = obtain_innovation(inverse_to_nodes.at(randoms_nodes).at(0), inverse_to_nodes.at(randoms_nodes).at(1));
	organism.add_connection(innovation,inverse_to_nodes.at(randoms_nodes).at(0), inverse_to_nodes.at(randoms_nodes).at(1), 2*(rand()%RAND_MAX)/(double)RAND_MAX - 1.0);
	return organism;
}

ostream & operator<<(ostream & o, ANN_USM::Population & pop) {
	for (int i = 0; i < (int)pop.organisms.size(); ++i){
		o << pop.organisms[i];
		o << "\n";
	}
	return o;
}

void Population::save(char path[]){
	ofstream file;
	file.open (path);
	file << *this;
	file.close();
}

double Population::compatibility(Genetic_Encoding orgm1, Genetic_Encoding orgm2){
	double distance;
	int E(0);
	int D(0);
	double W(0);
	int limit_sup;

	bool flag_orgm1_is_greater(false);
	if(orgm1.Lconnection_genes.size() > orgm2.Lconnection_genes.size()) flag_orgm1_is_greater=true;
	if(flag_orgm1_is_greater) limit_sup = (int)orgm1.Lconnection_genes.size();
	else limit_sup = (int)orgm2.Lconnection_genes.size();

	if(flag_orgm1_is_greater){
		for(int i=0; i < (int)orgm2.Lconnection_genes.size(); i++){
			if(orgm1.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).exist && orgm1.Lconnection_genes.at(i).enable && orgm2.Lconnection_genes.at(i).enable ){
				W += abs(orgm1.Lconnection_genes.at(i).weight - orgm2.Lconnection_genes.at(i).weight);
			}
			else if( (orgm1.Lconnection_genes.at(i).exist && orgm1.Lconnection_genes.at(i).enable) || (orgm2.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).enable)) D++;
		}
		for(int i = (int)orgm2.Lconnection_genes.size(); i < (int)orgm1.Lconnection_genes.size(); i++ )
			if(orgm1.Lconnection_genes.at(i).exist && orgm1.Lconnection_genes.at(i).enable)E++;
	}
	else{
		for(int i=0; i < (int)orgm1.Lconnection_genes.size(); i++){
			if( orgm1.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).exist && orgm1.Lconnection_genes.at(i).enable && orgm2.Lconnection_genes.at(i).enable){
			W += abs(orgm1.Lconnection_genes.at(i).weight - orgm2.Lconnection_genes.at(i).weight);
			}
			else if((orgm1.Lconnection_genes.at(i).exist && orgm1.Lconnection_genes.at(i).enable) || (orgm2.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).enable)) D++;
	}
	for(int i = (int)orgm1.Lconnection_genes.size(); i < (int)orgm2.Lconnection_genes.size(); i++ )
		if(orgm2.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).enable )E++;
	}


	//Lo siguiente es para que los genomas pequeños sean capaces de generar nichos diferentes así lograr una diversificación desde un principio.
	double divisor;
	double small_gnomes_adjust;
	if(limit_sup > 10){
		divisor = 1.0 + ( 1.0 - exp(-(limit_sup + 10.0)/2.5) )*(limit_sup - 1.0); 
		small_gnomes_adjust=1.0;
	} 
	else{
		divisor = 1.0;
		if(ORGANISM_DISTANCE_3 < 1.0) small_gnomes_adjust=1.0/ORGANISM_DISTANCE_3;
		else small_gnomes_adjust=1.0;
	}
	distance = ORGANISM_DISTANCE_1*E/divisor + ORGANISM_DISTANCE_2*D/divisor + ORGANISM_DISTANCE_3*W*small_gnomes_adjust;
	
	return distance;
}

Genetic_Encoding Population::crossover(Genetic_Encoding orgm1, Genetic_Encoding orgm2){
	Genetic_Encoding orgm_resutl;

	int conn_size_1 = orgm1.Lconnection_genes.size();
	int conn_size_2 = orgm2.Lconnection_genes.size();
	int node_size_1 = orgm1.Lnode_genes.size();
	int node_size_2 = orgm2.Lnode_genes.size();

	int conn_limit_sup, conn_limit_inf, node_limit_sup, node_limit_inf;
	bool connection_1_is_larger, node_1_is_larger;

	if(conn_size_1>conn_size_2) {		conn_limit_sup=conn_size_1;		conn_limit_inf=conn_size_2;		connection_1_is_larger=true;}
	else{		conn_limit_sup=conn_size_2;		conn_limit_inf=conn_size_1;		connection_1_is_larger=false;	}
	if(node_size_1>node_size_2) {		node_limit_sup=node_size_1;		node_limit_inf=node_size_2;		node_1_is_larger=true;	}
	else{		node_limit_sup=node_size_2;		node_limit_inf=node_size_1;		node_1_is_larger=false;	}


	int i=0;
	while( i < conn_limit_sup)
	{
		if (i >= conn_limit_inf)
		{
			if(connection_1_is_larger){
				if(orgm1.Lconnection_genes[i].exist==1){
					orgm_resutl.add_connection(orgm1.Lconnection_genes[i]);
				}
			}
			else{
				if(orgm2.Lconnection_genes[i].exist==1){
					orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
				}
			}
		}

		else{
			if( orgm1.Lconnection_genes[i].exist && orgm2.Lconnection_genes[i].exist ){
				if(orgm1.Lconnection_genes[i].enable && orgm2.Lconnection_genes[i].enable){
					(rand()%10 >= 5) ? orgm_resutl.add_connection(orgm1.Lconnection_genes[i]) : orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
				}
				else{
					//(!orgm1.Lconnection_genes[i].enable)? orgm_resutl.add_connection(orgm1.Lconnection_genes[i]) : orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
					if(!orgm1.Lconnection_genes[i].enable){
						if( ((double)rand())/RAND_MAX < PROB_ENABLE_AN_DISABLE_CONNECTION ){
							orgm1.Lconnection_genes[i].enable = true;
							orgm_resutl.add_connection(orgm1.Lconnection_genes[i]);
						}
						else{
							orgm_resutl.add_connection(orgm1.Lconnection_genes[i]);
						}
					}
					else{
						if( ((double)rand())/RAND_MAX < PROB_ENABLE_AN_DISABLE_CONNECTION ){
							orgm2.Lconnection_genes[i].enable = true;
							orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
						}
						else{
							orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
						}
					}
				}
			}
			else if ( orgm1.Lconnection_genes[i].exist || orgm2.Lconnection_genes[i].exist)
				(orgm1.Lconnection_genes[i].exist ) ? orgm_resutl.add_connection(orgm1.Lconnection_genes[i]) : orgm_resutl.add_connection(orgm2.Lconnection_genes[i]);
		}

		i++;
	}


	i=0;
	while(i < node_limit_sup){
		if (i >= node_limit_inf)
		{
			if(node_1_is_larger){
				if(orgm1.Lnode_genes[i].exist==1){
					orgm_resutl.add_node(orgm1.Lnode_genes[i]);
				}
			}
			else{
				if(orgm2.Lnode_genes[i].exist==1 ){
					orgm_resutl.add_node(orgm2.Lnode_genes[i]);
				}
			}
		}

		else{
			if( orgm1.Lnode_genes[i].exist && orgm2.Lnode_genes[i].exist )
				(rand()%10 >= 5) ? orgm_resutl.add_node(orgm1.Lnode_genes[i]) : orgm_resutl.add_node(orgm2.Lnode_genes[i]);
			else if ( orgm1.Lnode_genes[i].exist || orgm2.Lnode_genes[i].exist )
				(orgm1.Lnode_genes[i].exist) ? orgm_resutl.add_node(orgm1.Lnode_genes[i]) : orgm_resutl.add_node(orgm2.Lnode_genes[i]);
		}
		i++;
	}
	orgm_resutl.row_orderer_list = row_orderer_list;
	return orgm_resutl;
}

/*


//Version 2
// No sé por qué pero tengo la impresión que este método funciona peor.
Genetic_Encoding Population::crossover(Genetic_Encoding orgm1, Genetic_Encoding orgm2){
	Genetic_Encoding orgm_resutl;
	Genetic_Encoding * orgm_greater_connections;
	Genetic_Encoding * orgm_lower_connections;
	Genetic_Encoding * orgm_greater_nodes;
	Genetic_Encoding * orgm_lower_nodes;

	if( orgm1.Lconnection_genes.size() > orgm2.Lconnection_genes.size() ){
		orgm_greater_connections = &orgm1;
		orgm_lower_connections = &orgm2;
	}
	else{
		orgm_greater_connections = &orgm2;
		orgm_lower_connections = &orgm1;
	}
	if(orgm1.Lnode_genes.size() > orgm2.Lnode_genes.size()){
		orgm_greater_nodes = &orgm1;
		orgm_lower_nodes = &orgm2;
	}
	else{
		orgm_greater_nodes = &orgm2;
		orgm_lower_nodes = &orgm1;
	}
	//==========================CONNECTION=================
	for(int i = 0; i < (int)orgm_lower_connections->Lconnection_genes.size();i++){
		if(orgm1.Lconnection_genes.at(i).exist && orgm2.Lconnection_genes.at(i).exist ){
			if(rand()%10 < 5 ){
				orgm_resutl.add_connection(orgm1.Lconnection_genes.at(i));
			}
			else{
				orgm_resutl.add_connection(orgm2.Lconnection_genes.at(i));
			}
		}
		else{
			if( orgm1.Lconnection_genes.at(i).exist ){
				orgm_resutl.add_connection(orgm1.Lconnection_genes.at(i));
			}
			else if(orgm2.Lconnection_genes.at(i).exist){
				orgm_resutl.add_connection(orgm2.Lconnection_genes.at(i));
			}
		}
	}
	for(int i =  (int)orgm_lower_connections->Lconnection_genes.size(); i < (int)orgm_greater_connections->Lconnection_genes.size();i++){
		if(orgm_greater_connections->Lconnection_genes.at(i).exist)
			orgm_resutl.add_connection(orgm_greater_connections->Lconnection_genes.at(i));
	}
	//===================================================

	//==========================NODES=====================
	for(int i = 0; i < (int)orgm_lower_nodes->Lnode_genes.size();i++){
			if( orgm1.Lnode_genes.at(i).exist ){
				orgm_resutl.add_node(orgm1.Lnode_genes.at(i));
			}
			else if(orgm2.Lnode_genes.at(i).exist){
				orgm_resutl.add_node(orgm2.Lnode_genes.at(i));
			}
	}
	for(int i =  (int)orgm_lower_nodes->Lnode_genes.size(); i < (int)orgm_greater_nodes->Lnode_genes.size();i++){
		if(orgm_greater_nodes->Lnode_genes.at(i).exist)
			orgm_resutl.add_node(orgm_greater_nodes->Lnode_genes.at(i) );
	}
	//===================================================

	orgm_resutl.row_orderer_list = row_orderer_list;
	return orgm_resutl;
}



*/

//		PAPER VERSION.

/*

void Population::spatiation(){
	//Se hace el traspaso generacional, ahora los nichos actuales pasan a ser nichos previos.
	vector<Niche>().swap(prev_niches);
	prev_niches = current_niches;
	vector<Niche>().swap(current_niches);


	vector <Niche> real_niches;
	vector <Niche> current_niches_temp;

	for (int i = 0; i < (int)prev_niches.size(); ++i)
	{
		if (prev_niches.at(i).exist )
		{
			if(prev_niches.at(i).organism_position.size() >0)
				real_niches.push_back(prev_niches[i]);
		}
	}

	Niche aux_niche;
	aux_niche.exist=false;
	for(int i=0; i < (int)real_niches.size(); i++){
		current_niches_temp.push_back(aux_niche);
	}
	// Obtain an random representant
	vector <int> representant_of_niche;
	for(int i = 0; i < (int)real_niches.size(); i++){
		representant_of_niche.push_back( real_niches.at(i).organism_position.at(rand()%real_niches.at(i).organism_position.size()) );
	}

	for(int i=0; i < (int)organisms.size(); i++ ){
			bool have_niche(false);
			for(int j=0; j < (int)real_niches.size(); j++){
				if( compatibility(organisms.at(i), prev_organisms.at( representant_of_niche.at(j) ) )  < DISTANCE_THRESHOLD ){
					have_niche=true;
					current_niches_temp.at(j).exist=true;
					current_niches_temp.at(j).organism_position.push_back(i);
					break;
				}
			}
			if(!have_niche){
				for(int j= (int)real_niches.size(); j <   (int)current_niches_temp.size() ; j++){
					if( compatibility(organisms.at(i), organisms.at( representant_of_niche.at(j) ) )  < DISTANCE_THRESHOLD ){
						have_niche=true;
						current_niches_temp.at(j).organism_position.push_back(i);
						break;
					}
				}
			}
			if(!have_niche){
				Niche temp_niche;
				temp_niche.exist=true;
				current_niches_temp.push_back(temp_niche);
				representant_of_niche.push_back(i);
				current_niches_temp.at(current_niches_temp.size()-1).organism_position.push_back(i);
			}
	}

	for (int i = 0; i < (int)current_niches_temp.size(); ++i)
		if( current_niches_temp.at(i).exist ) current_niches.push_back(current_niches_temp.at(i));

	for (int i = 0; i < (int)current_niches.size(); ++i)
	{
			for (int j = 0; j < (int)current_niches.at(i).organism_position.size(); ++j)
			{
				organisms.at(current_niches.at(i).organism_position.at(j)).niche = i;
			}
	}
}

*/

void Population::print_niches()
{
	for (int i = 0; i < (int)current_niches.size(); ++i)
		if(current_niches[i].exist)
			cout << "Niche " << i << ":\t\t\t" <<  current_niches[i].organism_position.size() << endl;
		else
			cout << "Niche " << i << ":\t\t\t0\n";
}

// THIS SHOULD BE IN THE CLASS FILE
//bool Genetic_Encoding::FitnessSort(Genetic_Encoding first_genome, Genetic_Encoding second_genome)
//{
//	return first_genome.fitness > second_genome.fitness;
//}
/////////////////////////////////////

bool FitnessSort(Genetic_Encoding first_genome, Genetic_Encoding second_genome)
{
	return first_genome.fitness > second_genome.fitness;
}

double Niche::GetBestGenomeFitness()
{
	return bestFitness;
}

void Niche::UpdateChampion()
{
	double t_bestFitness = 0.0;
	Genetic_Encoding t_bestGenome;
	for (unsigned int i = 0; i < s_organisms.size(); i++)
	{
		if (s_organisms[i].fitness >= t_bestFitness) 
		{
			t_bestGenome = s_organisms[i];
			t_bestFitness = s_organisms[i].fitness;
		}
	}
	
	bestGenome = t_bestGenome;
	bestFitness = t_bestFitness;
}

bool GenomesFitnessSort(Niche first_niche, Niche second_niche)
{
	return first_niche.GetBestGenomeFitness() > second_niche.GetBestGenomeFitness();
}

void Niche::SortGenomesByFitness()
{
	sort(s_organisms.begin(), s_organisms.end(), FitnessSort);
}

unsigned int Population::ObtainRandomOrganism(Niche a_niche)
{
	unsigned int t_organismSelected;

	if (survivalSelection)
	{
		unsigned int t_topSize = survivalThreshold * a_niche.s_organisms.size();
		if (t_topSize == 0) t_topSize = 1;
		t_organismSelected = (unsigned int)(rand() % t_topSize);
	}
	else
	{
		Discrete_Probabilities t_organismsProbabilities;
		unsigned int t_organismsAmount = a_niche.s_organisms.size();

		for(unsigned int p = 0; p < t_organismsAmount; p++)
		{
			t_organismsProbabilities.add_element(a_niche.s_organisms[p].shared_fitness);
		}

		t_organismSelected = (unsigned int)t_organismsProbabilities.obtain_uniformrandom_element();
	}

	return t_organismSelected;
}

void Population::Epoch()
{
	prev_niches = current_niches;
	prev_organisms = organisms;

	vector <Niche> t_niches;
	t_niches = current_niches;

	// Update fitness values
	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		for (unsigned j = 0; j < t_niches[i].s_organisms.size(); j++)
		{
			t_niches[i].s_organisms[j].fitness = organisms[t_niches[i].organism_position[j]].fitness;
		}
	}

	// Ordenar especies por mejor fitness
	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		t_niches[i].SortGenomesByFitness();
		t_niches[i].UpdateChampion();
	}

	sort(t_niches.begin(), t_niches.end(), GenomesFitnessSort);

	// Actualizar especies
	// -Encontrar mejor especie -> almacenar
	// -Incrementar edad de las especies
	// -Marcar mejor especie para que sobreviva
	// -Resetear edad de la mejor especie para penalizar aquellas que no evolucionan cada ciertas generaciones
	int prev_championNiche = -1;
	int current_championNiche = -1;

	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		if (t_niches[i].championNiche)
		{
			prev_championNiche = i;
		}
		t_niches[i].championNiche = false;
	}

	destagnationState = false;

	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		t_niches[i].years++;
		t_niches[i].amount_of_offspring = 0;

		bool t_bestHistoricalMarked = false;

		if (t_niches[i].bestFitness >= bestHistoricalFitness)
		{
			t_niches[i].championNiche = true;
			current_championNiche = i;

			if (t_niches[i].bestFitness - bestHistoricalFitness > /*STAGNATION_FACTOR*/ 0.1) // REVIEW THIS
			{
				destagnationState = true;
			}

			t_bestHistoricalMarked = true; // REVIEW THIS TO MAKE IT USEFUL
			bestHistoricalGenome = t_niches[i].bestGenome;
			bestHistoricalFitness = t_niches[i].bestFitness;
		}
	}

	if (current_championNiche != -1)
	{
		if (current_championNiche != prev_championNiche && prev_championNiche != -1) t_niches[prev_championNiche].years = 0;
	}
	else
	{
		t_niches[prev_championNiche].championNiche = true;
	}	

	// Ajustar fitness de las especies (share fitness)
	// -Boost a los genomas jóvenes y penalización a las genomas viejos
	double p_sharedFitness = 0.0;
	double p_avgSharedFitness = 0.0;

	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		unsigned int t_nicheSize = t_niches[i].s_organisms.size();
		double t_avgFitnessSum = 0.0;

		for (unsigned int j = 0; j < t_nicheSize; j++)
		{
			t_niches[i].s_organisms[j].shared_fitness = t_niches[i].s_organisms[j].fitness / (double)t_nicheSize;
			p_sharedFitness += t_niches[i].s_organisms[j].shared_fitness;

			t_avgFitnessSum += t_niches[i].s_organisms[j].fitness;
		}

		t_niches[i].avgFitness = t_avgFitnessSum / t_nicheSize;
	}


	p_avgSharedFitness = p_sharedFitness / (double)POPULATION_MAX;
	
	// Setear herencia por individuo y especie
	double t_bestFitness = 0.0;
	for (unsigned int i = 0; i < t_niches.size(); i++)
	{
		unsigned int t_nicheSize = t_niches[i].s_organisms.size();
		for (unsigned int j = 0; j < t_nicheSize; j++)
		{
			t_niches[i].s_organisms[j].offspring = t_niches[i].s_organisms[j].shared_fitness / p_avgSharedFitness;
			t_niches[i].amount_of_offspring += t_niches[i].s_organisms[j].offspring;

			if (t_niches[i].s_organisms[j].fitness > t_bestFitness)
			{
				champion = t_niches[i].bestGenome;
				fitness_champion = t_niches[i].bestFitness;
			}				
		}

		clog << "Media: " << t_niches[i].avgFitness << "\t MaxFitness: " << t_niches[i].bestFitness << "\t Pertenecientes: " << t_niches[i].s_organisms.size() << "\t Descendencia: " << t_niches[i].amount_of_offspring << endl;
	}

	// Lidiar con estancamiento global
	generationsWithoutChange++;
	if (destagnationState)
	{
		generationsWithoutChange = 0;
		destagnationState = false;
	}

	// Reproducción
	vector<Genetic_Encoding>().swap(organisms);
	vector<Niche>().swap(current_niches);

	organisms = EpochReproduce(t_niches);
	current_niches = Speciate(t_niches, organisms);

	for (unsigned int i = 0; i < current_niches.size(); )
	{
		if (current_niches[i].s_organisms.size() == 0)
			current_niches.erase(current_niches.begin() + i);
		else
			i++;
	}

	unsigned int t_organismsAmount = 0;
	unsigned int t_positionCompatible;
	bool t_nicheCompatibleFound = false;

	for (unsigned int i = 0; i < current_niches.size(); i++)
	{
		current_niches[i].representant = current_niches[i].s_organisms[0];
		t_organismsAmount += current_niches[i].s_organisms.size();

		// This will be used in case the duplicates will be made of the best genome ever
		/*
		if (compatibility(bestHistoricalGenome, current_niches[i].representant) < DISTANCE_THRESHOLD)
		{
			t_nicheCompatibleFound = true;
			t_positionCompatible = i;
		}
		*/
	}

	if (t_organismsAmount != organisms.size()) clog << "ERROR DE TAMAÑO EN GENERACION " << current_generation << endl;

    if (t_organismsAmount < (unsigned int)POPULATION_MAX)
    {
        unsigned int t_deltaPopulation = POPULATION_MAX - t_organismsAmount;
        clog << "WARNING DE TAMAÑO EN GENERACION " << current_generation << endl;
        while (organisms.size() < POPULATION_MAX)
        {
        	organisms.push_back(current_niches[0].representant);
    		current_niches[0].s_organisms.push_back(current_niches[0].representant);
    		current_niches[0].organism_position.push_back(organisms.size() - 1);
        }
        /*
        for (unsigned int i = 0; i < t_deltaPopulation; i++)
        {
        	if (t_nicheCompatibleFound)
        	{
        		organisms.push_back(bestHistoricalGenome);
        		current_niches[t_positionCompatible].s_organisms.push_back(bestHistoricalGenome); // REVIEW THIS!!! add some parameter to allow this
        		current_niches[t_positionCompatible].organism_position.push_back(organisms.size() - 1);
        	}
        	else
        	{
        		organisms.push_back(current_niches[0].representant);
        		current_niches[0].s_organisms.push_back(current_niches[0].representant);
        		current_niches[0].organism_position.push_back(organisms.size() - 1);
        	}
        }
        */
    }

	current_generation++;
}

vector <Niche> Population::Speciate(vector <Niche> &a_niches, vector <Genetic_Encoding> &a_organisms)
{
	for (unsigned int i = 0; i < a_niches.size(); i++)
	{
		a_niches[i].s_organisms.clear();
		a_niches[i].organism_position.clear();
	}

	bool t_nicheCompatibleFound;
	for (unsigned int i = 0; i < a_organisms.size(); i++)
	{
		t_nicheCompatibleFound = false;

		if (a_niches.size() == 0)
		{
			Niche t_niche;
			t_niche.exist = true;
			t_niche.years = 0;
			t_niche.s_organisms.push_back(a_organisms[i]);
			t_niche.organism_position.push_back(i);
			t_niche.representant = t_niche.s_organisms[0];
			t_niche.bestFitness = 0.0;
			t_niche.avgFitness = 0.0;
			a_niches.push_back(t_niche);
		}
		else
		{
			for (unsigned int j = 0; j < a_niches.size(); j++)
			{
				if(compatibility(a_organisms[i], a_niches[j].representant) < DISTANCE_THRESHOLD){
					t_nicheCompatibleFound = true;
					a_niches[j].s_organisms.push_back(a_organisms[i]);
					a_niches[j].organism_position.push_back(i);
					break;
				}
			}

			if (!t_nicheCompatibleFound)
			{
				Niche t_niche;
				t_niche.exist = true;
				t_niche.years = 0;
				t_niche.s_organisms.push_back(a_organisms[i]);
				t_niche.organism_position.push_back(i);
				t_niche.representant = t_niche.s_organisms[0];
				t_niche.bestFitness = 0.0;
				t_niche.avgFitness = 0.0;
				a_niches.push_back(t_niche);
			}		
		}
	}

	return a_niches;
}

vector <Genetic_Encoding> Population::EpochReproduce(vector <Niche> &a_niches)
{
	vector <Genetic_Encoding> n_genomes;

	for (unsigned int i = 0; i < a_niches.size(); i++)
	{
		unsigned int t_offspring = abs(floor(a_niches[i].amount_of_offspring)); // abs just to be fure is positive. It should be positive without it

		if (t_offspring == 0) continue;

		unsigned int t_organismsAmount = a_niches[i].s_organisms.size();
		unsigned int t_eliteOffspring = static_cast<unsigned int>(round((double)t_organismsAmount * eliteOffspringParam));
		unsigned int t_eliteCount = 0;

		//Discrete_Probabilities t_organismsProbabilities;

		for (unsigned int j = 0; j < t_offspring; j++)
		{
			unsigned int t_randomMotherId;
			unsigned int t_randomFatherId;

			Genetic_Encoding t_randomMother;
			Genetic_Encoding t_randomFather;

			Genetic_Encoding t_son;

			if (t_eliteCount < t_eliteOffspring)
			{
				t_son = a_niches[i].s_organisms[t_eliteCount];
				t_eliteCount++;
			}
			else
			{
				t_randomMotherId = ObtainRandomOrganism(a_niches[i]);
				t_randomMother = a_niches[i].s_organisms[t_randomMotherId];

				if (100.0 * (double)rand() / RAND_MAX < PERCENTAGE_OFFSPRING_WITHOUT_CROSSOVER) // should have another parameter name and value
				{ 
					t_son = mutation_change_weight(t_randomMother); // should mutate topology too
				}
				else
				{
					if ((double)rand() / RAND_MAX < PROBABILITY_INTERSPACIES_MATING && a_niches.size() > 1)
					{
						unsigned int t_randomFatherNiche;
						unsigned int t_newOrganismsAmount;

						while (true)
						{
							t_randomFatherNiche = rand() % a_niches.size();
							if(t_randomFatherNiche != i) break;
						}

						t_newOrganismsAmount = a_niches[t_randomFatherNiche].s_organisms.size();

						t_randomFatherId = ObtainRandomOrganism(a_niches[t_randomFatherNiche]);
						t_randomFather = a_niches[t_randomFatherNiche].s_organisms[t_randomFatherId];
						t_son = crossover(t_randomMother, t_randomFather);
					}
					else
					{
						if (t_organismsAmount == 1)
							t_son = mutation_change_weight(t_randomMother); // should mutate topology too
						else
						{
							// Could use another method to make sure the best genomes of the species survive. REVIEW THIS
							while (true)
							{
								//t_randomFatherId = (unsigned int)t_organismsProbabilities.obtain_uniformrandom_element();
								t_randomFatherId = ObtainRandomOrganism(a_niches[i]);
								if(t_randomFatherId != t_randomMotherId || allowClones) break;
							}

							t_randomFather = a_niches[i].s_organisms[t_randomFatherId];
							t_son = crossover(t_randomMother, t_randomFather);
						}
					}
				}

				// REVIEW THIS
				if ((double)rand() / RAND_MAX < LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE){
					t_son = mutation_node(t_son);
				}
				// AND THIS
				if ((double)rand() / RAND_MAX < LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION) {
					t_son = mutation_connection(t_son);
				}

				// Maybe verify if the genome exist already. REVIEW THIS

				if (PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE != 0)
				{
					for (unsigned int k = 0; k < t_son.Lnode_genes.size(); k++)
					{
						if ((double)rand() / RAND_MAX <= PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE)
						{
							t_son.Lnode_genes[k].change_random_function_randomly();
						}
					}
				}

			}
				
				
			n_genomes.push_back(t_son);
		}
	}

	return n_genomes;
}

void Population::load_user_definitions(char address[]){
	ifstream file (address);
	file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
	char buffer[length]; // In JSON format
	file.read (buffer,length);
	file.close();
	char * pch;

	char delimiters[] = " \n\":\t{},[";
	pch = strtok (buffer,delimiters);
	pch = strtok (NULL,delimiters);
	POPULATION_MAX =  atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_1 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_2 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_3 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	DISTANCE_THRESHOLD = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PERCENTAGE_OFFSPRING_WITHOUT_CROSSOVER = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_INTERSPACIES_MATING = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROB_ENABLE_AN_DISABLE_CONNECTION = atof(pch);
	/* Lnodes.size() comparation */
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGE_POPULATION_DISCRIMINATOR = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	GENERATIONS = atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_WEIGHT = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE = atof(pch);

	//cerr << "PROBABILITY_INTERSPACIES_MATING: " << PROBABILITY_INTERSPACIES_MATING << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " << SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION<< endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION << endl;
	//cerr << "PROB_ENABLE_AN_DISABLE_CONNECTION: " << PROB_ENABLE_AN_DISABLE_CONNECTION << endl;
	//cerr << "GENERATIONS" << GENERATIONS << endl;
	//cerr << "PROBABILITY_CHANGE_WEIGHT" << PROBABILITY_CHANGE_WEIGHT << endl;
	//cerr << "PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE" << PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE << endl;

}

void Population::load_user_definitions(char address[], int simulatorsAmount){
	ifstream file (address);
	file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
	char buffer[length]; // In JSON format
	file.read (buffer,length);
	file.close();
	char * pch;

	char delimiters[] = " \n\":\t{},[";
	pch = strtok (buffer,delimiters);
	pch = strtok (NULL,delimiters);
	POPULATION_MAX =  simulatorsAmount - atoi(pch)%simulatorsAmount + atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_1 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_2 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_3 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	DISTANCE_THRESHOLD = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PERCENTAGE_OFFSPRING_WITHOUT_CROSSOVER = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_INTERSPACIES_MATING = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROB_ENABLE_AN_DISABLE_CONNECTION = atof(pch);
	/* Lnodes.size() comparation */
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGE_POPULATION_DISCRIMINATOR = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	GENERATIONS = atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_WEIGHT = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE = atof(pch);

	//cerr << "POPULATION_MAX" << POPULATION_MAX << endl;
	//cerr << "PROBABILITY_INTERSPACIES_MATING: " << PROBABILITY_INTERSPACIES_MATING << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " << SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION<< endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION << endl;
	//cerr << "PROB_ENABLE_AN_DISABLE_CONNECTION: " << PROB_ENABLE_AN_DISABLE_CONNECTION << endl;
	//cerr << "GENERATIONS" << GENERATIONS << endl;
	//cerr << "PROBABILITY_CHANGE_WEIGHT" << PROBABILITY_CHANGE_WEIGHT << endl;
	//cerr << "PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE" << PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE << endl;

}

void Population::load_user_definitions(string address){
	ifstream file (address.c_str());
	file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);
	char buffer[length]; // In JSON format
	file.read (buffer,length);
	file.close();
	char * pch;

	char delimiters[] = " \n\":\t{},[";
	pch = strtok (buffer,delimiters);
	pch = strtok (NULL,delimiters);
	POPULATION_MAX =  atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_1 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_2 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	ORGANISM_DISTANCE_3 = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	DISTANCE_THRESHOLD = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PERCENTAGE_OFFSPRING_WITHOUT_CROSSOVER = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_INTERSPACIES_MATING = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROB_ENABLE_AN_DISABLE_CONNECTION = atof(pch);
	/* Lnodes.size() comparation */
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	LARGE_POPULATION_DISCRIMINATOR = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	GENERATIONS = atoi(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_WEIGHT = atof(pch);
	pch = strtok (NULL,delimiters);
	pch = strtok (NULL,delimiters);
	PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE = atof(pch);

	//cerr << "POPULATION_MAX" << POPULATION_MAX << endl;
	//cerr << "PROBABILITY_INTERSPACIES_MATING: " << PROBABILITY_INTERSPACIES_MATING << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " << SMALLER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION<< endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_NODE << endl;
	//cerr << "LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION: " <<LARGER_POPULATIONS_PROBABILITY_ADDING_NEW_CONNECTION << endl;
	//cerr << "PROB_ENABLE_AN_DISABLE_CONNECTION: " << PROB_ENABLE_AN_DISABLE_CONNECTION << endl;
	//cerr << "GENERATIONS" << GENERATIONS << endl;
	//cerr << "PROBABILITY_CHANGE_WEIGHT" << PROBABILITY_CHANGE_WEIGHT << endl;
	//cerr << "PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE" << PROBABILITY_CHANGE_NODE_FUNCTION_PER_NODE << endl;

}


/**
\brief obtains the number such that the expectation of times that enter to "while" method be amount_of_times  
*/
double Population::obtain_while_limit(double amount_of_times){
	return (amount_of_times/(amount_of_times + 1.0));
}

/**
\brief obtains the number such that the expectation of times that enter to "while" method be amount_of_times  
*/
double Population::obtain_while_limit(int amount_of_times){
	return ((double)amount_of_times/((double)amount_of_times + 1.0) );
}



void Population::change_window_of_fitness_generation(double fitness_mean_current_generation){

	if( (fitness_mean_current_generation > fitness_mean_of_past_generation.at(0) ) || (fitness_mean_current_generation > fitness_mean_of_past_generation.at(1)) || (fitness_mean_current_generation > fitness_mean_of_past_generation.at(2)) || (fitness_mean_current_generation > fitness_mean_of_past_generation.at(3)) || (fitness_mean_current_generation > fitness_mean_of_past_generation.at(4)) || (fitness_mean_current_generation > fitness_mean_of_past_generation.at(4))  ){
		expectative_iterations++;
	}else{
		if(expectative_iterations/2.0 < 1) expectative_iterations = 1;
		else{
			expectative_iterations/=2.0;
		}
	}

	fitness_mean_of_past_generation.at(0)=fitness_mean_of_past_generation.at(1);
	fitness_mean_of_past_generation.at(1)=fitness_mean_of_past_generation.at(2);
	fitness_mean_of_past_generation.at(2)=fitness_mean_of_past_generation.at(3);
	fitness_mean_of_past_generation.at(3)=fitness_mean_of_past_generation.at(4);
	fitness_mean_of_past_generation.at(4)=fitness_mean_current_generation;
}



void	Population::print_to_file_currrent_generation(){
	for (int i = 0; i < (int)organisms.size(); ++i)
	{
		stringstream archive_name;
		archive_name << save_path;
		if(name != NULL){
			archive_name << name ;
		}
		archive_name <<  "G" << current_generation << "P" << i; 
		organisms.at(i).save((char *)archive_name.str().c_str());
	}
}

#endif