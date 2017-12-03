#include "discol.h"

void test(){
	std::cout << "test" << std::endl;
}

int main(int argc, char *argv[]){

	std::string inputs = "";
	bool encrypt = true;
	bool decrypt = false;
	std::string keyString = "";
	bool intermediateTable = false;
	bool backfill = false;
	int N = 5;
	bool help = false;
	std::string strSortedKey = "";
	std::vector<std::vector<char> > matrix;
	// Pear1 for reading out the columns
	std::vector<std::pair<char, int> > pear1;
	// Pear2 for making the matrix
	std::vector<std::pair<char, int> > pear2;

	// Get input from std::in
	while(std::cin){
		std::string temp;
		std::getline(std::cin, temp);
		inputs.append(temp);
	}
	inputs.erase(std::remove(inputs.begin(), inputs.end(), '\n'), inputs.end());
	inputs.erase(std::remove(inputs.begin(), inputs.end(), ' '), inputs.end());

	// Ignore non-alphanumeric characters in the input from stdin
	// and also make it upper case
	makeAlphaNumeric(inputs);
	toUpperCase(inputs);


	// Runs through input arguments and gets the values for any flags
	checkArgs(argv, argc,encrypt, decrypt, keyString, intermediateTable, backfill, N, help);
	nonAlphaNumStdErr(inputs, decrypt);
	/*
	Checks for any non-alphanumeric characters and outputs them to stderr
	After writing to stderr, remove non-alphanumeric characters
	Then, change the remaining key string to all upper case
	Finally, we ensure that the key is no greater than 36 characters as specified
	*/
	nonAlphaNumStdErr(keyString, false);
	makeAlphaNumeric(keyString);
	toUpperCase(keyString);
	maxKeyLength(keyString);

	// Create sorted key
	sortKey(strSortedKey, keyString);

	// create matrix for columnar transposition
	setMatrix(matrix, keyString);

	// Create vector pairs for making the matrix and reading it out
	makePair(pear1, pear2, keyString, strSortedKey);

	if(encrypt){
		xEncrypt(matrix, pear1, pear2, keyString, strSortedKey, inputs, intermediateTable, N, backfill);
	}
	else{
		xDecrypt(matrix, pear1, pear2, keyString, strSortedKey, inputs, intermediateTable, N, backfill);
	}

	if(DEBUG){
		if(encrypt){
			std::cout << "encrypting" << std::endl;
		}
		if(decrypt){
			std::cout << "decrypt" << std::endl;
		}
		std::cout << "Key String: " << keyString << std::endl;
		if(intermediateTable){
			std::cout << "Output intermediate table" << std::endl;
		}
		if(backfill){
			std::cout << "backfill" << std::endl;
		}
		std::cout << N << std::endl;
		if(help){
			std::cout << "help" << std::endl;
		}
	}
	return 0;
}

void xDecrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1, std::vector<std::pair<char, int> > pear2, std::string &keyString, std::string &strSortedKey, std::string inputs, bool intermediateTable, int N, bool backfill){
	int row = keyString.size()+1;
	int column = keyString.size();
	int counter = 0;

	fillMatrixDecrypt(inputs, row ,column, counter, matrix, pear1, pear2);

	if(backfill){
		executeBackfill(matrix, row, column, inputs, counter);
	}

	if(intermediateTable){
		intTable(row, column, matrix, pear1);
		putchar('\n');
	}

	readOutDecrypt(matrix, row, column, N);
}

void xEncrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1, std::vector<std::pair<char, int> > pear2, std::string &keyString, std::string &strSortedKey, std::string inputs, bool intermediateTable, int N, bool backfill){
	int row = keyString.size()+1;
	int column = keyString.size();
	int counter = 0;

	fillMatrixEncrypt(inputs, row ,column, counter, matrix, pear2);

	// if(backfill){
	// 	executeBackfill(matrix, row, column, inputs, counter);
	// }

	while (counter < inputs.size()){
		fillMatrixEncrypt(inputs, row, column, counter, matrix, pear2);
		if(backfill){
			executeBackfill(matrix,row,column,inputs,counter);
		}
	}

	if(intermediateTable){
		intTable(row, column, matrix, pear1);
		putchar('\n');
	}

	readOutEncrypt(matrix, pear2, row, column, N);

}

void executeBackfill(std::vector<std::vector<char> > &matrix, int row, int column, std::string inputs, int counter){
	bool b = false;
	if(inputs.size() > counter){
		b = true;
	}
	if(b){
		for(int i = 0; i < row; i++){
			for(int j = 0; j < column; j++){
				if(matrix[i][j] == ' ' && (counter != inputs.size())){
					matrix[i][j] = inputs.at(counter);
					counter++;
				}
			}
		}
	}
}

void fillMatrixDecrypt(std::string &inputs, int &row, int &column, int &counter, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > &pear1, std::vector<std::pair<char, int> > &pear2){
	for(int i = 0; i < row; i++){
		if(i != 0){
			for(int j = 0; j < column; j++){
				if(j < pear2.at(i-1).second+1){
					if(counter != inputs.size()){
						matrix[i][j] = '*';
					}
					else{
						matrix[i][j] = ' ';
					}
					if(counter+1 <= inputs.size()){
						counter++;
					}
					else{

					}
				}
				else{
					matrix[i][j] = ' ';
				}
			}
		}
		else{
			for(int j = 0; j < column; j++){
				matrix[i][j] = '*';
				counter++;
			}
		}
	}
	counter = 0;
	int temp = 0;
	for(int i = 0; i < pear2.size(); i++){
		temp = pear2.at(i).second;
		//std::cout << column << std::endl;
		for(int j = 0; j < row; j++){
			if(matrix[j][temp] == '*'){
				//std::cout << inputs.at(counter) << std::endl;
				matrix[j][temp] = inputs.at(counter);
				counter++;
			}
		}
	}
}

void readOutEncrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear2, int row, int column, int N){
	std::vector<char> output;
	for(int i = 0; i < pear2.size(); i++){
		column = pear2.at(i).second;
		for(int j = 0; j < row; j++){
			output.push_back(matrix[j][column]);
		}
	}


	int counter = 0;
	int tensCounter = 0;
	for(int i = 0; i < output.size(); i++){
		if(output.at(i) != ' '){
			std::cout << output.at(i);
			counter++;
			if(N != 0){
				if(counter == N){
					if(N >= 60){
						putchar('\n');
					}
					else{
						std::cout << " ";
						counter = 0;
						tensCounter++;
						if(tensCounter == 10){
							putchar('\n');
							tensCounter = 0;
						}
					}
				}
			}
		}
	}
	putchar('\n');
}

void readOutDecrypt(std::vector<std::vector<char> > &matrix, int row, int column, int N){
	std::vector<char> output;

	std::string lowerCase;
	//std::string temp;
	char temp;

	for(int i = 0; i < row; i++){
		for(int j = 0; j < column;  j++){
			temp = tolower(matrix[i][j]);
			output.push_back(temp);
		}
	}

	int counter = 0;
	int tensCounter = 0;

	for(int i = 0; i < output.size(); i++){
		if(output.at(i) != ' '){
			std::cout << output.at(i);
			counter++;
			if(N != 0){
				if(counter == N){
					if(N >= 60){
						putchar('\n');
					}
					else{
						std::cout << " ";
						counter = 0;
						tensCounter++;
						if(tensCounter == 10){
							putchar('\n');
							tensCounter = 0;
						}
					}
				}
			}
		}
	}

}

void intTable(int row, int column, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1){
	// Output the key
	for(int i = 0; i < pear1.size(); i++){
		std::cout << pear1.at(i).first << " | ";
	}
	putchar('\n');

	// Output key ordinals
	for(int i = 0; i < pear1.size(); i++){
		std::cout << pear1.at(i).second+1 << " | ";
	}
	putchar('\n');
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			std::cout << matrix[i][j] << " | ";
		}
		putchar('\n');
	}
}

void fillMatrixEncrypt(std::string &inputs, int &row, int &column, int &counter, std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > &pear2){
	for(int i = 0; i < row; i++){
		if(i != 0){
			for(int j = 0; j < column; j++){
				if(j < pear2.at(i-1).second+1){
					if(counter != inputs.size()){
						matrix[i][j] = inputs.at(counter);
					}
					else{
						matrix[i][j] = ' ';
					}
					if(counter+1 <= inputs.size()){
						counter++;
					}
				}
				else{
					matrix[i][j] = ' ';
				}
			}
		}
		else{
			for(int j = 0; j < column; j++){
				matrix[i][j] = inputs.at(counter);
				counter++;
			}
		}
	}
}

void makePair(std::vector<std::pair<char, int> > &pear1, std::vector<std::pair<char, int> > &pear2, std::string &keyString, std::string &strSortedKey){

	int order1 = 0;
	int order2 = 0;

	for(int i = 0; i < keyString.size(); i++){


		order1 = strSortedKey.find(keyString.at(i));


		order2 = keyString.find(strSortedKey.at(i));


		// TODO: PEAR1 IS FOR READING OUT THE COLUMNS
		pear1.push_back(std::make_pair(keyString.at(i), order1));


		// TODO: PEAR2 IS FOR MAKING THE MATRIX
		pear2.push_back(std::make_pair(keyString.at(i), order2));

	}

}

void sortKey(std::string &strSortedKey, std::string &keyString){
	std::vector<char> sortedKey;
	std::vector<char> forNumbers;

	for(int i = 0; i < keyString.size(); i++){
		if(!(isalpha(keyString.at(i)))){
			forNumbers.push_back(keyString.at(i));
		}
		else{
			sortedKey.push_back(keyString.at(i));
		}
	}


	std::sort(forNumbers.begin(), forNumbers.end());

	std::sort(sortedKey.begin(), sortedKey.end());

	for(int i = 0; i < forNumbers.size(); i++){
		sortedKey.push_back(forNumbers.at(i));
	}



	std::string temp;
	for(int i = 0; i < sortedKey.size(); i++){
		std::stringstream ss;
		ss << sortedKey.at(i);
		ss >> temp;
		strSortedKey.append(temp);
	}
}

void setMatrix(std::vector<std::vector<char>> &matrix, std::string keyString){
	int height = keyString.size()+1;
	int width = keyString.size();
	// Set up sizes. (HEIGHT x WIDTH)
	matrix.resize(height);
	for (int i = 0; i < height; ++i){
		matrix[i].resize(width);
	}
}

void maxKeyLength(std::string &keyString){
	if(keyString.size() > 36){
		keyString = keyString.substr(0, 36);
	}
}

void toUpperCase(std::string &keyString){
	for(int i = 0; i < keyString.size(); i++){
		keyString.at(i) = toupper(keyString.at(i));
	}
}

void nonAlphaNumStdErr(std::string &inputs, bool decrypt){
	for(std::string::iterator i = inputs.begin(); i != inputs.end(); i++){
		if(!isalnum(inputs.at(i - inputs.begin()))){
			if(decrypt){
				fprintf(stderr, "Error, character: [%c] is non-alphanumeric. Exiting.\n", inputs.at(i-inputs.begin()));
				exit(1);
			}
			else{
				fprintf(stderr, "Error, character: [%c] is non-alphanumeric. Ignoring.\n", inputs.at(i-inputs.begin()));
			}


		}
	}
}

void makeAlphaNumeric(std::string &inputs){
	for(std::string::iterator i = inputs.begin(); i != inputs.end(); i++){
		if(!isalnum(inputs.at(i - inputs.begin()))){
			inputs.erase(i);
			i--;
		}
	}
}

void checkArgs(char *argv[], int argc, bool &encrypt, bool &decrypt, std::string &keyString, bool &intermediateTable, bool &backfill, int &N, bool &help){

	std::vector <std::string> arguments;

	for(int i = 1; i < argc; i++){
		if(argv[i] !=  NULL){
			arguments.push_back(argv[i]);
			select(arguments.at(i-1), encrypt, decrypt, keyString, intermediateTable, backfill, N, help);
		}
	}
}

void select(std::string arguments, bool &encrypt, bool &decrypt, std::string &keyString, bool &intermediateTable, bool &backfill, int &N, bool &help){
	if (arguments == "-e"){
		encrypt = true;
		decrypt = false;
	}

	else if(arguments == "-d"){
		encrypt = false;
		decrypt = true;
	}
	if(arguments.at(1) == 'k'){
		std::string temp = arguments.substr(2, std::string::npos);
		keyString = temp;
	}

	// Output intermediateTable to std::err
	if(arguments == "-t"){
		intermediateTable = true;
	}

	// Backfill
	if(arguments == "-b"){
		backfill = true;
	}


	if(arguments.at(0) == '-'){
		std::string temp = arguments.substr(1, std::string::npos);
		bool onlyDigits = (temp.find_first_not_of( "0123456789" ) == std::string::npos);
		if (onlyDigits){
			N = std::stoi(temp);
		}

	}

	if(arguments == "-h"){
		std::cout << "\nHELP SELECTED:\nDiscrupted Columnar Transposition Cipher"<< std::endl;
		std::cout << "Please input a file through stdin, and begin execuation by using:"<< std::endl;
		std::cout << "discol [-e | -d] -k<String> -t -b -<N> -h < somefile.txt" << std::endl;
		exit(EXIT_SUCCESS);
	}
	// If the user gives a new value for n, take note of it
	// Assumes input in the form -L<n>, with no space between L and n

	// Program ends if given any invalid input argument
	if(arguments != "-e" && arguments != "-d" && arguments != "-t" && arguments != "-b" && arguments.at(1) != 'k' && arguments.at(0) != '-'){
		fprintf(stderr, "Error: Non-valid input argument(s)\nUsage: discol [-e | -d] -k<String> -t -b -<N> -h\nTerminating\n");
		exit(EXIT_SUCCESS);
	}
}
