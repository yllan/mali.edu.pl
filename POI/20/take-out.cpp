#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n, k;

struct entry {
    char color;
    int index;
};

void solve(char *buf)
{
    vector<vector<int> > answers;
    vector<entry> stack;

    int c_count_in_k_plus_1_window = 0;

    for (int i = 0; i < n; i++) {
        if (stack.size() >= k + 1 && stack[stack.size() - k - 1].color == 'c')
            c_count_in_k_plus_1_window--;
        entry e;
        e.color = buf[i];
        e.index = i;
        stack.push_back(e);
        if (e.color == 'c')
            c_count_in_k_plus_1_window++;
        if (stack.size() >= k + 1 && c_count_in_k_plus_1_window == 1) {
            vector<int> answer;
            for (int j = 0; j <= k; j++) {
                answer.push_back(stack.back().index);
                stack.pop_back();
            }
            sort(answer.begin(), answer.end());
            answers.push_back(answer);

            // recalculate c_count_in_k_plus_1_window;
            c_count_in_k_plus_1_window = 0;
            for (int j = stack.size() - 1; j >= 0 && j >= (int)stack.size() - k - 1; j--) {
                if (stack[j].color == 'c')
                    c_count_in_k_plus_1_window++;
            }
        }
    }
    
    for (vector<vector<int> >::iterator it = answers.end() - 1; it >= answers.begin(); it--) {
        for (vector<int>::iterator p = it->begin(); p < it->end(); p++) {
            printf("%d ", *p + 1);
        }
        printf("\n");
    }
}

int main() 
{
    scanf("%d %d", &n, &k);

    char buf[n + 1];
    scanf("%s", buf);

    solve(buf);
}