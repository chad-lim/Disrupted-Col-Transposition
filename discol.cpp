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

	/*
	Checks for any non-alphanumeric characters and outputs them to stderr
	After writing to stderr, remove non-alphanumeric characters
	Then, change the remaining key string to all upper case
	Finally, we ensure that the key is no greater than 36 characters as specified
	*/
	nonAlphaNumStdErr(keyString);
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
		xEncrypt(matrix, pear1, pear2, keyString, strSortedKey, inputs);
	}
	else{

	}

	if(DEBUG){
		std::cout << matrix.size() << " " << matrix[1].size() << std::endl;
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
void xEncrypt(std::vector<std::vector<char> > &matrix, std::vector<std::pair<char, int> > pear1, std::vector<std::pair<char, int> > pear2, std::string &keyString, std::string &strSortedKey, std::string inputs){
	int row = keyString.size()+1;
	int column = keyString.size();
	int counter = 0;

	std::cout << "Size of inputs should be 26: " << inputs.size() << std::endl;
	for(int i = 0; i < row; i++){
		if(i != 0){
			for(int j = 0; j < pear2.at(i-1).second+1; j++){

				matrix[i][j] = inputs.at(counter);
				//std::cout << matrix[i][j] << std::endl;
				if(counter+1 <= inputs.size()){
					std::cout << counter++ << std::endl;
				}
			}
		}
		else{
			for(int j = 0; j < column; j++){


				matrix[i][j] = inputs.at(counter);
				std::cout << matrix[i][j] << std::endl;

				counter++;

			}
			//std::cout << " End row " << i << std::endl;
		}
	}


	std::cout << "\n2 | 3 | 4 | 6 | 1 | 5 |" << std::endl;
	counter = 0;
	// Print

	for(int i = 0; i < row; i++){
		//std::cout << "test" << matrix[0][5] << std::endl;
		if(i != 0){
			//	std::cout << i << " pear.at(i-1).second = " << pear2.at(i-1).second << std::endl;

			for(int j = 0; j < pear2.at(i-1).second+1; j++){
				//std::cout << "Counter: " << counter << std::endl;
				//std::cout << i << " " << j << " test != 0 and != NULL " << std::endl;
				std::cout << matrix[i][j] << " | ";
				counter++;

			}
		}
		else{
			for(int j = 0; j < column; j++){
				//std::cout << i << " " << j << " test == 0 and != NULL " << std::endl;
				std::cout << matrix[i][j] << " | ";
				counter++;
			}
		}
		putchar('\n');
	}
}

void makePair(std::vector<std::pair<char, int> > &pear1, std::vector<std::pair<char, int> > &pear2, std::string &keyString, std::string &strSortedKey){
	int order1 = 0;
	int order2 = 0;
	// Let's find the index of the sorted letter in the string instead


	for(int i = 0; i < keyString.size(); i++){
		order1 = strSortedKey.find(keyString.at(i));
		order2 = keyString.find(strSortedKey.at(i));
		//std::cout << strSortedKey.at(i) << " " << order2 <<std::endl;
		//strSortedKey.erase(order+1, 1);

		// TODO: PEAR1 IS FOR READING OUT THE COLUMNS
		pear1.push_back(std::make_pair(keyString.at(i), order1));

		// TODO: PEAR2 IS FOR MAKING THE MATRIX
		pear2.push_back(std::make_pair(keyString.at(i), order2));
	}

}

void sortKey(std::string &strSortedKey, std::string &keyString){
	std::vector<char> sortedKey;

	for(int i = 0; i < keyString.size(); i++){
		sortedKey.push_back(keyString.at(i));
	}
	std::sort(sortedKey.begin(), sortedKey.end());


	std::string temp;
	for(int i = 0; i < sortedKey.size(); i++){
		std::stringstream ss;
		ss << sortedKey.at(i);
		ss >> temp;
		strSortedKey.append(temp);
	}
	std::cout << strSortedKey << std::endl;
}

void setMatrix(std::vector<std::vector<char>> &matrix, std::string keyString){
	int height = keyString.size()+1;
	int width = keyString.size();
	// Set up sizes. (HEIGHT x WIDTH)
	std::cout << "Matrix height: " << height << std::endl;
	std::cout << "Matrix width: " << width << std::endl;
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

void nonAlphaNumStdErr(std::string &inputs){
	for(std::string::iterator i = inputs.begin(); i != inputs.end(); i++){
		if(!isalnum(inputs.at(i - inputs.begin()))){
			fprintf(stderr, "Error, character: [%c] is non-alphanumeric. Ignoring.\n", inputs.at(i-inputs.begin()));
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
		help = true;
	}
	// If the user gives a new value for n, take note of it
	// Assumes input in the form -L<n>, with no space between L and n

	// Program ends if given any invalid input argument
	if(arguments != "-e" && arguments != "-d" && arguments != "-t" && arguments != "-b" && arguments.at(1) != 'k' && arguments.at(0) != '-'){
		fprintf(stderr, "Error: Non-valid input argument(s)\nUsage: discol [-e | -d] -k<String> -t -b -<N> -h\nTerminating\n");
		exit(EXIT_SUCCESS);
	}
}
