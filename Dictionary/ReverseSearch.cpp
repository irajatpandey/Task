    #include <bits/stdc++.h> 
    #include<string.h>
    #include<vector>
    using namespace std;
    /* Dictionary Class contains the structure of Trie */
    class Dictionary{ 
        public:
        bool isTerminal; 
        Dictionary *parent;
        char c;
        unordered_map<char, Dictionary*> hashMap; 
        long int frequency; 
    }; 
    vector<Dictionary*> HashTable;
    // this function is used to create new node
    Dictionary* createNewNode(Dictionary *parent, char c) 
    { 
        Dictionary* node = new Dictionary; 
        node -> isTerminal = false; 
        node -> c = c;
        node -> parent = parent;
        return node; 
    }
    
// This function is used to add word with its frequency
    void addWordInDictionary(Dictionary*& root, const string& word, const int& frequency) 
    { 
        // If root is nullptr then create the node
        if(root == nullptr){ 

            root = createNewNode(NULL, 0); 
        }

        Dictionary* myDictionary = root; 

        for (int index = 0; index < word.size(); index++) { 

            char pick = word[index]; 

            /* If there is no path present create a new node  and insert it into the hashMap*/
            if (myDictionary -> hashMap.find(pick) == myDictionary -> hashMap.end()){ 

                myDictionary -> hashMap[pick] = createNewNode(myDictionary, pick); 
            }

            myDictionary = myDictionary -> hashMap[pick]; 
        } 

        // at the end of the word make its boolean value is true  and put the frequency of word in mydictionary -> frequencey = frequency
        myDictionary -> isTerminal = true; 
        myDictionary -> frequency = frequency; 
        HashTable.push_back(myDictionary); // add my dictionary to the HashTable
    } 




string findTheWordInTheDictionary(Dictionary * root, int number){
     string word;

     if(number >= HashTable.size()) return word;

    Dictionary *node = HashTable[number];

	
	while(node -> parent){
        word += node -> c;
        node = node -> parent;
      
    }
      reverse(word.begin(), word.end());
    
    
      return word;
   
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
            int n;
            cout << "Enter the value of n \n";
	        cin  >> n;

            string ans = findTheWordInTheDictionary(root, n);
            if(ans.size() > 0) cout << ans << endl;
            else {
                cout << "NO Word found\n";
            }
        }

        return 0;              
    } 