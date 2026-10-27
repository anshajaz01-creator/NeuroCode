#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <bits/stdc++.h> 
#include <algorithm>

using namespace std;

class FirstPairComparator
{
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) 
    {
        return p1.first < p2.second;
    }
};

int sum_second_in_pair(vector<pair<int, int>>& glasses) 
{
    int sum = 0;
    for(auto& glass : glasses)
        sum += glass.second;
    return sum;
}
vector<float> calculate_minimum_spills(vector<pair<int, int>>& glasses)
{
    int cur_water, cur_capacity;
    int total_water = sum_second_in_pair(glasses);

    // According to the constraints, this will be maximum of 40000
    vector<map<int, int>> dp(glasses.size(), map<int, int>());

    
    // base case
    for(unsigned int i = 0; i < glasses.size(); i++) 
    {
        if(dp[0].find(glasses[i].second + total_water) == dp[0].end())
            dp[0][glasses[i].second + total_water] = 0;
        dp[0][glasses[i].second + total_water] = max(dp[0][glasses[i].second + total_water], glasses[i].first);

        for(unsigned int j = 1; j + i < glasses.size(); j++)
        {
            cur_water = glasses[j + i].second;
            cur_capacity = glasses[j + i].first;
            for (auto& pair : dp[j - 1])
            {
                int k = pair.first;
                if(dp[j].find(cur_water + k) == dp[j].end()) 
                    dp[j][cur_water + k] = 0;
                dp[j][cur_water + k] = max(dp[j][cur_water + k], cur_capacity + pair.second);
            }
        }
    }

    int i = 0;
    vector<float> ans(glasses.size());
    for(auto& d : dp)
    {
        float max_ans = 0; 
        for(auto& p : d)
        {
            float sub_ans = min(((float)p.first) / 2.0f, (float)p.second);
            max_ans = max(max_ans, sub_ans);
        }
        ans[i++] = max_ans;
    } 
    return ans;
}
int main(int argc, char* argv[])
{
    int n; 
    cin >> n;
    vector<pair<int, int>> glasses(n, pair<int, int>(0, 0));
    for(int i = 0; i < n; i++)
        cin >> glasses[i].first >> glasses[i].second;

    vector<float> ans = calculate_minimum_spills(glasses);


    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    for(auto x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}
