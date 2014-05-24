#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long d, m;
int n;

// The next position by taking taxi with specified distance.
long long next_pos(long long current_pos, long long taxi_distance)
{
    if (current_pos < d && taxi_distance >= (d - current_pos))
        return current_pos + (taxi_distance - (d - current_pos));

    if (current_pos >= d && d + taxi_distance >= current_pos)
        return d + taxi_distance;
    
    // Unreachable: stay.
    return current_pos;
}

int solve(vector<long long> &taxis)
{
    sort(taxis.begin(), taxis.end());
    reverse(taxis.begin(), taxis.end());

    // Even the longest taxi can't drive from d to m: impossible.
    if (taxis.front() < m - d) return 0;

    // See if we can take only one taxi.
    if (taxis.front() >= d + m) return 1;

    // Need to take more than one taxis.

    // Pick a minimum taxi that could drive from d to m. That is, taxis[i] ≥ (m - d)
    vector<long long>::iterator lastTaxi = taxis.begin();
    for (vector<long long>::iterator it = taxis.begin(); it < taxis.end() && *it >= (m - d); lastTaxi = it++);
    long long lastDistance = *lastTaxi;
    taxis.erase(lastTaxi);

    // Simulate the rest, by greedy.
    int count = 0;
    long long pos = 0;

    for (vector<long long>::iterator it = taxis.begin(); pos < d && it < taxis.end(); it++, count++) {
        long long next = next_pos(pos, *it);
        if (next <= pos) break;
        pos = next;
    }
    if (pos >= m) return count;
    return (next_pos(pos, lastDistance) >= m) ? count + 1 : 0;
}

int main()
{
    vector<long long> taxis;

    scanf("%lld %lld %d", &m, &d, &n);
    for (int i = 0; i < n; i++) {
        long long distance;
        scanf("%lld", &distance);
        taxis.push_back(distance);
    }
    printf("%d\n", solve(taxis));
}
