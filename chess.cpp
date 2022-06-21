#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <math.h>
#include <algorithm>

using namespace std;

vector<int> check_csp(vector<int>& current_state){
    vector<int> conflicted;
    int diff_index, diff_value;
    for (size_t i = 0; i < current_state.size(); i++)
    {
        for (size_t j = 0; j < current_state.size(); j++)
        {
           if ((current_state[i] == current_state[j]) && j != i)
           {
              if (find(conflicted.begin(), conflicted.end(), i) == conflicted.end())
              {
                  conflicted.push_back(i);
              }
              if (find(conflicted.begin(), conflicted.end(), j) == conflicted.end())
              {
                  conflicted.push_back(j);
              } 
            //   cout <<"- "<<"i "<< i <<" j"<< j << endl;
           }
        }
    }
    for (size_t i = 0; i < current_state.size(); i++)
    {
        for (size_t j = 1; j <=  current_state.size(); j++)
        {
            for (size_t k = 0; k <  current_state.size(); k++)
            {
                if (current_state[k] == j)
                {
                    diff_index = current_state[i] - j;
                    diff_value = i - k;
                    if (diff_index < 0)
                    {
                        diff_index = -1 * diff_index;
                    }
                    if (diff_value < 0)
                    {
                        diff_value = -1 * diff_value;
                    }
                    if (diff_index == diff_value && diff_index != 0)
                    {
                        if (find(conflicted.begin(), conflicted.end(), i) == conflicted.end())
                        {
                            // cout <<"/ "<<"i "<< i <<" j"<< j << endl;
                            conflicted.push_back(i);
                        }
                    }
                }
            }
        }
    }
    return conflicted;
}

int conflicts_count(vector<int>& current_state, int var){
    vector<int> conflicts_array(current_state.size(), 0);
    int diff_index, diff_value;
    int results;
    for (size_t i = 0; i < current_state.size(); i++)
    {
        conflicts_array[current_state[i] - 1] += 1;
    }
    for (size_t i = 1; i <= current_state.size(); i++)
    {
        results = 0;
        for (size_t j = 1; j <=  current_state.size(); j++)
        {
            for (size_t k = 0; k <  current_state.size(); k++)
            {
                if (current_state[k] == j)
                {
                   diff_index = i - j;
                    diff_value = var - k;
                    if (diff_index < 0)
                    {
                        diff_index = -1 * diff_index;
                    }
                    if (diff_value < 0)
                    {
                        diff_value = -1 * diff_value;
                    }
                    if (diff_index == diff_value && diff_index != 0)
                    {
                        // cout <<"i " <<i <<"j " <<j <<"k "<<k << endl;
                        results ++;
                    }
                }
            }
        }
        conflicts_array[i - 1] += results;
    }
    return (min_element(conflicts_array.begin(), conflicts_array.end()) - conflicts_array.begin()) + 1;
}
void print_chess(vector<int> positions){
    for (size_t i = positions.size(); i > 0; i--)
    {
        for (size_t j = 0; j < positions.size(); j++)
        {
            if (i == positions[j])
            {
                cout<<" x";
            }
            else
            {
                cout << " o";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool min_conflicts(vector<int>& csp, int max_steps){
    vector<int> conflicted;
    int var_index, var, value;
    srand(time(0));
    for (size_t i = 0; i < max_steps; i++)
    {
        conflicted = check_csp(csp);
        if(conflicted.size() == 0){
            cout << i << "  steps" << endl;
            cout <<"Non conflicted"<<endl;
            return true;
        }
        var_index = rand() % conflicted.size();
        
        var = conflicted[var_index];
        
        value = conflicts_count(csp, var);
        csp[var] = value;
        print_chess(csp);
    } 
    return false;
}
int main(){
    int size_chess, pos;
    vector<int> positions;
    cout << "Enter the size of chessboard, (n x n)  : ";
    cin >> size_chess; 
    for (size_t i = 1; i <= size_chess; i++)
    {
        cout << "Enter queen position for column "<< i << endl;
        cin >> pos;
        positions.push_back(pos);
    }
    if(min_conflicts(positions, 1000)){
        print_chess(positions);
    }
}
    
    
