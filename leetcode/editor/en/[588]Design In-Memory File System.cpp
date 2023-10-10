//Design a data structure that simulates an in-memory file system. 
//
// Implement the FileSystem class: 
//
// 
// FileSystem() Initializes the object of the system. 
// List<String> ls(String path)
// 
// If path is a file path, returns a list that only contains this file's name. 
// If path is a directory path, returns the list of file and directory names in 
//this directory. 
// 
// The answer should in lexicographic order. 
// void mkdir(String path) Makes a new directory according to the given path. Th
//e given directory path does not exist. If the middle directories in the path do 
//not exist, you should create them as well. 
// void addContentToFile(String filePath, String content)
// 
// If filePath does not exist, creates that file containing given content. 
// If filePath already exists, appends the given content to original content. 
// 
// 
// String readContentFromFile(String filePath) Returns the content in the file a
//t filePath. 
// 
//
// 
// Example 1: 
//
// 
//Input
//["FileSystem", "ls", "mkdir", "addContentToFile", "ls", "readContentFromFile"]
//
//[[], ["/"], ["/a/b/c"], ["/a/b/c/d", "hello"], ["/"], ["/a/b/c/d"]]
//Output
//[null, [], null, null, ["a"], "hello"]
//
//Explanation
//FileSystem fileSystem = new FileSystem();
//fileSystem.ls("/");                         // return []
//fileSystem.mkdir("/a/b/c");
//fileSystem.addContentToFile("/a/b/c/d", "hello");
//fileSystem.ls("/");                         // return ["a"]
//fileSystem.readContentFromFile("/a/b/c/d"); // return "hello"
// 
//
// 
// Constraints: 
//
// 
// 1 <= path.length, filePath.length <= 100 
// path and filePath are absolute paths which begin with '/' and do not end with
// '/' except that the path is just "/". 
// You can assume that all directory names and file names only contain lowercase
// letters, and the same names will not exist in the same directory. 
// You can assume that all operations will be passed valid parameters, and users
// will not attempt to retrieve file content or list a directory or file that does
// not exist. 
// 1 <= content.length <= 50 
// At most 300 calls will be made to ls, mkdir, addContentToFile, and readConten
//tFromFile. 
// 
// Related Topics Hash Table String Design Trie 
// 👍 1172 👎 132


//leetcode submit region begin(Prohibit modification and deletion)
/*
 * solution 1: hash table + ordered set
 * time: O(1)-ls, O(logn)-mkdir, n is the number of directory series, O(1)-addContentToFIle, readContentFromFile
 * space: O(n)
 * */

class FileSystem {
    unordered_map<string, set<string>> parent_child;
    unordered_map<string, string> file_content;
public:
    FileSystem() {

    }

    vector<string> ls(string path) {
        // the path is a file
        auto it = file_content.find(path);
        if (it != file_content.end())
        {
            int idx = path.find_last_of('/');
            return {path.substr(idx + 1)};
        }

        // the path is a directory
        auto dirs = parent_child[path];
        vector<string> res(dirs.begin(), dirs.end());
        return res;
    }

    void mkdir(string path) {
        stringstream ss(path);
        string token = "", dir = "/";
        while (getline(ss, token, '/'))
        {
            if (token.empty()) continue;
            parent_child[dir].insert(token);
            if (dir.size() > 1) dir += "/";
            dir += token;
        }
    }


    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/');
        string dir = filePath.substr(0, idx);
        string file = filePath.substr(idx + 1);
        if (dir.empty()) dir = "/"; // root directory
        auto it = parent_child.find(dir);
        if (it == parent_child.end()) mkdir(dir);
        parent_child[dir].insert(file);
        file_content[filePath].append(content);
    }

    string readContentFromFile(string filePath) {
        return file_content[filePath];
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
//leetcode submit region end(Prohibit modification and deletion)
