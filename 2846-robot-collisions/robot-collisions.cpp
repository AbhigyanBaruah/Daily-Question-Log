class Solution {
public:
vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0); 

        sort(ids.begin(), ids.end(), [&](int a, int b) {
            return positions[a] < positions[b];
        });

        vector<int> st; 

        for (int id : ids) {
            if (directions[id] == 'R') {
                st.push_back(id);
            } else {
                while (!st.empty() && healths[id] > 0) {
                    int top_id = st.back();
                    
                    if (healths[top_id] < healths[id]) {
                        healths[top_id] = 0; 
                        st.pop_back();
                        healths[id] -= 1;
                    } 
                    else if (healths[top_id] > healths[id]) {
                        healths[top_id] -= 1; 
                        healths[id] = 0; 
                    } 
                    else {
                        healths[top_id] = 0;
                        st.pop_back();
                        healths[id] = 0;
                    }
                }
            }
        }

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) {
                result.push_back(healths[i]);
            }
        }

        return result;
    }
};