




int menu() {
	// int filesRuns;
	// if (argc!=2){
	// 	cout << "Parametros errados, por favor .. utilize ./parser NUMERODEFILESNOFOLDERFILES";
	// 	return 0;
	// }
	// int num_files_system = atoi(argv[1]);
	int answer;
	int checkIndice = 0;
	system("clear");

	//Menu.
	while (answer !=3){
		cout << "Escolha a opção desejada. Digite: "<<endl;
		cout << "1- Para VectorModel."<<endl;
		cout << "2- Para realizar pesquisa."<<endl;
		cout << "3- Para sair"<<endl;
		cin >> answer;
		cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
		if (answer == 1){
			
		}else if(answer ==2){
			if (checkIndice ==0){

				loadRefIdsFromFiles();
				checkIndice =1;
			}
			binary_search();
			cout << "Pressione Enter para continuar";
			cin.ignore ();
			system("clear");
		}
		else{
			return 0;
		}
	}
}