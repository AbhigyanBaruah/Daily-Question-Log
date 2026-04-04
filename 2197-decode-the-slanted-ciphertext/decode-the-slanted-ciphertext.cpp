class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        int n = encodedText.size();
        if (n == 0) return "";
        
        int cols = n / rows;
        
        // Step 1: Fill matrix row-wise
        vector<vector<char>> mat(rows, vector<char>(cols));
        int idx = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = encodedText[idx++];
            }
        }
        
        // Step 2: Traverse diagonally
        string result = "";
        
        for (int startCol = 0; startCol < cols; startCol++) {
            int i = 0, j = startCol;
            
            while (i < rows && j < cols) {
                result += mat[i][j];
                i++;
                j++;
            }
        }
        
        // Step 3: Remove trailing spaces
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        
        return result;
    }
};