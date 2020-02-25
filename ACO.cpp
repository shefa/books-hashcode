struct AntColony{
public:
	int deadline;
	int ants;
	AntColony(){

	}

	void init(){

	}

	void run(){
		while(clock()<deadline){
			generateSolutions();
			pheromoneUpdate();
		}
	}

	void generateSolutions(){

	}

	void pheromoneUpdate(){
		
	}
};