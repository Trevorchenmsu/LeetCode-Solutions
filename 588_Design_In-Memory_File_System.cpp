/*
solution 1: hash table
time: O(nlogn)
space: O(n)
*/
class FileSystem {
public:
    FileSystem() {
        
    }
    
    vector<string> ls(string path) {
        // the path is file
        if (file_content.count(path)) {
            int idx = path.find_last_of('/');
            return {path.substr(idx + 1)};
        }
        
        // the path is directory
        auto child = dir_children[path];
        return vector<string> (child.begin(), child.end());
    }
    
    void mkdir(string path) {
        istringstream ss(path);
        string token = "", dir = "";
        while (getline(ss, token, '/')) { 
            if (token.empty()) continue;
            if (dir.empty()) dir += "/";
            dir_children[dir].insert(token);
            if (dir.size() > 1) dir += "/";
            dir += token;
        }
    }
    
    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/'); 
        string dir = filePath.substr(0, idx); // find the directory
        string file = filePath.substr(idx + 1); // find the file name
        if (dir.empty()) dir = "/"; // in the root directory
        if (!dir_children.count(dir)) mkdir(dir); // directory does not exit, create it
        dir_children[dir].insert(file);
        file_content[filePath].append(content);
        
    }
    
    string readContentFromFile(string filePath) {
        return file_content[filePath];
    }
    
private:
    unordered_map<string, set<string>> dir_children;
    unordered_map<string, string> file_content;
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */


 /*
solution 2: Trie
time: O(nlogn)
space: O(n)
*/

class FileSystem {
    class TrieNode
    {
        public:
        map<string,TrieNode*>Map;
        bool isFile;
    };
    TrieNode* root;
    unordered_map<string,string>FileContents;
    
public:
    FileSystem() 
    {
        root=new TrieNode();
    }
    
    vector<string> ls(string path) 
    {
        TrieNode* node=root;
        string str;
        for (int i=1; i<path.size(); i++)
        {
            int i0=i;
            while (i<path.size() && path[i]!='/')
                i++;
            str=path.substr(i0,i-i0);
            node=node->Map[str];
        }
        
        if (node->isFile)
            return {str};
        else
        {
            vector<string>results;
            for (auto a:node->Map)
                results.push_back(a.first);
            return results;
        }
    }
    
    void mkdir(string path) 
    {
        TrieNode* node=root;
        for (int i=1; i<path.size(); i++)
        {
            int i0=i;
            while (i<path.size() && path[i]!='/')
                i++;
            string str=path.substr(i0,i-i0);
            if (node->Map.find(str)==node->Map.end())
                node->Map[str]=new TrieNode();                        
            node=node->Map[str];
        }
    }
    
    void addContentToFile(string filePath, string content) 
    {
        TrieNode* node=root;
        for (int i=1; i<filePath.size(); i++)
        {
            int i0=i;
            while (i<filePath.size() && filePath[i]!='/')
                i++;
            string str=filePath.substr(i0,i-i0);
            if (node->Map.find(str)==node->Map.end())
                node->Map[str]=new TrieNode();                        
            node=node->Map[str];
        }
        node->isFile=1;
        FileContents[filePath]+=content;
    }
    
    string readContentFromFile(string filePath) 
    {
        return FileContents[filePath];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem obj = new FileSystem();
 * vector<string> param_1 = obj.ls(path);
 * obj.mkdir(path);
 * obj.addContentToFile(filePath,content);
 * string param_4 = obj.readContentFromFile(filePath);
 */

