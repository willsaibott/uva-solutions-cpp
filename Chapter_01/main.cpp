#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <bitset>
#include "basic.h"
using namespace std;

/*
 * Froming Quiz teams, the solution for UVa 10911 above
 * Using global variables is a bad software engineering practice,
 * but it is OK for competitive programming
 */

int N, target;
double dist[20][20], memo[1 << 16]; // 1 << 26 = 2 ^ 16, note that max N=8

double matching(int bitmask){
    // We initialize 'memo' with -1 in the main function
    if (memo[bitmask] > -0.5)  // this state has been computed before
        return memo[bitmask];  // simply lookup the memo table
    if (bitmask == target)     // all students are already matched
        return memo[bitmask] = 0;   // the cost is 0

    double ans = INF;       // initialize with a large value
    int p1, p2;
    for (p1 = 0; p1 < 2 * N; p1++)
        if (!(bitmask & (1 << p1)))
            break;                  // find the first bit that is off
    for (p2 = p1 + 1; p2 < 2 * N; p2++)   // then, try to match p1
        if (!(bitmask & (1 << p2))) {
            std::bitset<4> x(p1), y(p2), bit(bitmask | (1 << p1) | (1 << p2));
            cout << "Dist[" << x << "][" << y << "]=" << dist[p1][p2] << "\tans=" << ans << "\tbitmask=" << bit << endl;
            //with another bit p2 that is also off
            ans = min(ans,               // pick the min
                      dist[p1][p2] + matching(bitmask | (1 << p1) | (1 << p2)));
        }

    return memo[bitmask] = ans; // store the result in a memo table and return
}

int main () {
    int i, j, caseNo = 1, x[20], y[20];
    //freopen("10911.txt", "r", stdin); // redirect input file to stdin

    while (scanf("%d", &N), N) {
        int size = 2 * N;
        for (i = 0; i < size; i++)
            scanf("%*s %d %d", &x[i], &y[i]); // "%s" skips names
        for (i = 0; i < size - 1; i++)  // build pairwise distance table
            for (j = i + 1; j < size; j++) // have you used hypot before?
                dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);

        // Use DP to solve min weighted perfect matching on samll general graph
        for (i = 0; i < (1 << 16); i++) memo[i] = - 1.0;
        target = (1 << (size)) - 1;
        printf("Case %d: %.2lf\n", caseNo++, matching((0)));
    }
    return 0;
}
