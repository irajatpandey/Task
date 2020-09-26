    #include <bits/stdc++.h> 
    #include<string.h>
    #include<vector>
    using namespace std;
    /* Dictionary Class contains the structure of Trie */
    class Dictionary{ 
        public:
        bool isTerminal; 
        unordered_map<char, Dictionary*> hashMap; 
        long int frequency; 
    }; 

    // this function is used to create new node
    Dictionary* createNewNode() 
    { 
        Dictionary* node = new Dictionary; 
        node -> isTerminal = false; 
        return node; 
    }
    
// This function is used to add word with its frequency
    void addWordInDictionary(Dictionary*& root, const string& word, const int& frequency) 
    { 
        // If root is nullptr then create the node
        if(root == nullptr){ 

            root = createNewNode(); 
        }

        Dictionary* myDictionary = root; 

        for (int index = 0; index < word.size(); index++) { 

            char pick = word[index]; 

            /* If there is no path present create a new node  and insert it into the hashMap*/
            if (myDictionary -> hashMap.find(pick) == myDictionary -> hashMap.end()){ 

                myDictionary -> hashMap[pick] = createNewNode(); 
            }

            myDictionary = myDictionary -> hashMap[pick]; 
        } 

        // at the end of the word make its boolean value is true  and put the frequency of word in mydictionary -> frequencey = frequency
        myDictionary -> isTerminal = true; 
        myDictionary -> frequency = frequency; 
    } 


// This function is basically used to find the word in the dictionary

 int findTheWordInTheDictionary(Dictionary * root, string word){


     if(root == NULL) return -1;
     Dictionary* myDictionary = root; 

	// Find the word int the dictionary
	for (int index = 0; index < word.length(); index++) { 

		myDictionary = myDictionary -> hashMap[word[index]]; 
		if (myDictionary == nullptr) {
			return -1; 

        }
	} 

    if (myDictionary -> isTerminal)  return myDictionary -> frequency; 



    return -1;    
 }



    int main() 
    { 
        Dictionary* root = NULL; 

        // reading the csv file
        ifstream myFileStream("EnglishDictionary.csv");
        if(myFileStream.is_open() == false) {
            cout << "File not found " << endl;
            return 0;
        }
        else{
            string line, word;
            string fre;
            vector<pair<string, int>> v;
            long int f;

            while(getline(myFileStream, line)){
                stringstream ss(line);
                getline(ss, word, ',');
                getline(ss, fre, ',');
                f = stoi(fre);
                v.push_back({word,f});
            }
            // Building the dictionary to store words and frequency
            for(auto it : v){
                addWordInDictionary(root, it.first, it.second);
            }
            string str;
            cout << "Enter the word \n";
	        cin  >> str;

            int ans = findTheWordInTheDictionary(root, str);
            if(ans != -1) cout << "YES " << ans << endl;
            else {
                cout << "NO\n";
            }
        }

        return 0;              
    } 