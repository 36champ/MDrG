#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void output(vvll &edges)
{
    ofstream out("graph.dot");
    out << "digraph {\n";
    for(vll e: edges)
    {
        out << e[0] << " -- " << e[1] << " [color = red]\n";
    }
    out << "}\n";
}

int main()
{
    ll n, r;
    cout << "Insert the number of vertices: ";
    cin >> n;
    cout << "Insert the degree of each vertex: ";
    cin >> r;

    assert(r >= 3);
    assert(n > r);
    assert((n * r) % 2 == 0);

    vvll edges;
    if(n == r + 1)
    {
        for(int i=0; i<n; i++) for(int j=i+1; j<n; j++) edges.pb({i, j});
    }
    else if(n < 2 * r + 2)
    {
        for(int i=1; i<=r/2; i++) for(int j=0; j<n; j++) edges.pb({j, (j + i) % n});
        if(r % 2 == 1) for(int i=0; i<n/2; i++) edges.pb({i, i + n / 2});
    }
    else if(n == 2 * r + 2)
    {
        edges.pb({0, 1});
        edges.pb({0, 2});
        edges.pb({1, 2 * r - 1});
        edges.pb({2, 2 * r});
        edges.pb({2 * r - 1, 2 * r + 1});
        edges.pb({2 * r, 2 * r + 1});

        for(int i=3; i<=r; i++) for(int j=0; j<i; j++) edges.pb({j, i});
        for(int i=r+1; i<=2*r-2; i++) for(int j=i+1; j<2*r+2; j++) edges.pb({i, j});
    }
    else
    {
        // Find k
        ll k = n / (r + 1) - 1;

        if(n % (r + 1) == 0) // d = 3k
        {
            //(1, r, [1, r - 2, 2], r, 1)
            ll d = 3 * k;
            vll lb(d + 1), ub(d + 1), cnt(d + 1);

            for(int i=0; i<=d; i++)
            {
                if(i == 0 || i == d) cnt[i] = 1;
                else if(i == 1 || i == d - 1) cnt[i] = r;
                else if(i % 3 == 2) cnt[i] = 1;
                else if(i % 3 == 0) cnt[i] = r - 2;
                else if(i % 3 == 1) cnt[i] = 2;
            }

            ll start = 0;
            for(int i=0; i<=d; i++)
            {
                lb[i] = start;
                ub[i] = start + cnt[i];
                start += cnt[i];
            }

            // Inbetween
            for(int i=0; i<d; i++)
            {
                if(i == 1 || i == d - 2) continue;
                for(int u=lb[i]; u<ub[i]; u++) for(int v=lb[i+1]; v<ub[i+1]; v++) edges.pb({u, v});
            }
            edges.pb({ub[1] - 1, lb[2]});
            edges.pb({ub[1] - 2, lb[2]});
            edges.pb({ub[d - 2] - 1, ub[d - 1] - 1});
            edges.pb({ub[d - 2] - 2, ub[d - 1] - 2});

            // Inside
            for(int i=lb[1]; i<ub[1]-2; i++) for(int j=i+1; j<ub[1]; j++) edges.pb({i, j});
            for(int i=lb[d-1]; i<ub[d-1]-2; i++) for(int j=i+1; j<ub[d-1]; j++) edges.pb({i, j});
            for(int l=3; l<d; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});
            for(int l=4; l<d; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});
        }
        else if(r % 2 == 0)
        {
            if(n % (r + 1) <= 2) // d = 3k + 1
            {
                //(1, r, [1, r - 2, 2], 1, r, x)
                ll d = 3 * k + 1, x = n % (r + 1);
                vll lb(d + 1), ub(d + 1), cnt(d + 1);

                for(int i=0; i<=d; i++)
                {
                    if(i == 0) cnt[i] = 1;
                    else if(i == d) cnt[i] = x;
                    else if(i == 1 || i == d - 1) cnt[i] = r;
                    else if(i % 3 == 2) cnt[i] = 1;
                    else if(i % 3 == 0) cnt[i] = r - 2;
                    else if(i % 3 == 1) cnt[i] = 2;
                }

                ll start = 0;
                for(int i=0; i<=d; i++)
                {
                    lb[i] = start;
                    ub[i] = start + cnt[i];
                    start += cnt[i];
                }

                // Inbetween
                for(int i=0; i<d; i++)
                {
                    if(i == 1 || i == d - 2) continue;
                    for(int u=lb[i]; u<ub[i]; u++) for(int v=lb[i+1]; v<ub[i+1]; v++) edges.pb({u, v});
                }
                edges.pb({ub[1] - 1, lb[2]});
                edges.pb({ub[1] - 2, lb[2]});

                // Inside
                for(int i=lb[1]; i<ub[1]-2; i++) for(int j=i+1; j<ub[1]; j++) edges.pb({i, j});
                for(int l=3; l<d-1; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});
                for(int l=4; l<d-1; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});

                if((r - x + 1) % 2 == 1)
                {
                    edges.pb({lb[d-1], lb[d-1]+1});
                    for(int i=lb[d-1]+2; i<ub[d-1]; i++) edges.pb({lb[d-2], i});
                    for(int i=2; i<=(r - x + 1)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[d - 1] + j, lb[d - 1] + (j + i) % r});
                    for(int i=0; i<r/2; i++) edges.pb({lb[d - 1] + i, lb[d - 1] + i + r / 2});
                }
                else
                {
                    edges.pb({lb[d-1], lb[d-1]+r/2});
                    for(int i=lb[d-1]+1; i<lb[d-1]+r/2; i++) edges.pb({lb[d-2], i});
                    for(int i=lb[d-1]+r/2+1; i<ub[d-1]; i++) edges.pb({lb[d-2], i});
                    for(int i=1; i<=(r - x - 1)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[d - 1] + j, lb[d - 1] + (j + i) % r});
                }
            }
            else // d = 3k + 2
            {
                //(1, r, 2, [1, r - 2, 2], 1, r, x)
                ll d = 3 * k + 2, x = n % (r + 1) - 2;
                vll lb(d + 1), ub(d + 1), cnt(d + 1);

                for(int i=0; i<=d; i++)
                {
                    if(i == 0 || i == d - 2) cnt[i] = 1;
                    else if(i == d) cnt[i] = x;
                    else if(i == 1 || i == d - 1) cnt[i] = r;
                    else if(i % 3 == 0) cnt[i] = 1;
                    else if(i % 3 == 1) cnt[i] = r - 2;
                    else if(i % 3 == 2) cnt[i] = 2;
                }

                ll start = 0;
                for(int i=0; i<=d; i++)
                {
                    lb[i] = start;
                    ub[i] = start + cnt[i];
                    start += cnt[i];
                }

                // Inbetween
                for(int i=0; i<d; i++)
                {
                    if(i == 1 || i == d - 2) continue;
                    for(int u=lb[i]; u<ub[i]; u++) for(int v=lb[i+1]; v<ub[i+1]; v++) edges.pb({u, v});
                }

                // Inside
                for(int l=4; l<d-1; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});
                for(int l=5; l<d-1; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});

                // Inbetween D_{3k}, D_{3k+1} + Inside D_{3k + 1}
                if((r - x + 1) % 2 == 1)
                {
                    edges.pb({lb[d-1], lb[d-1]+1});
                    for(int i=lb[d-1]+2; i<ub[d-1]; i++) edges.pb({lb[d-2], i});
                    for(int i=2; i<=(r - x + 1)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[d - 1] + j, lb[d - 1] + (j + i) % r});
                    for(int i=0; i<r/2; i++) edges.pb({lb[d - 1] + i, lb[d - 1] + i + r / 2});
                }
                else
                {
                    edges.pb({lb[d-1], lb[d-1]+r/2});
                    for(int i=lb[d-1]+1; i<lb[d-1]+r/2; i++) edges.pb({lb[d-2], i});
                    for(int i=lb[d-1]+r/2+1; i<ub[d-1]; i++) edges.pb({lb[d-2], i});
                    for(int i=1; i<=(r - x - 1)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[d - 1] + j, lb[d - 1] + (j + i) % r});
                }

                // Inbetween D_1, D_2 + Inside D-1
                //if((r - 3) % 2 == 1)
                {
                    for(int i=lb[1]; i<ub[1]; i++) if(i != lb[1]) edges.pb({i, lb[2]});
                    for(int i=lb[1]; i<ub[1]; i++) if(i != lb[1] + 1) edges.pb({i, lb[2] + 1});
                    edges.pb({lb[1], lb[1] + 1});
                    for(int i=2; i<=(r - 1)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[1] + j, lb[1] + (j + i) % r});
                    for(int i=0; i<r/2; i++) edges.pb({lb[1] + i, lb[1] + i + r / 2});
                }
                /*else
                {
                    for(int i=lb[1]; i<ub[1]; i++) if(i != lb[1]) edges.pb({i, lb[2]});
                    for(int i=lb[1]; i<ub[1]; i++) if(i != lb[1] + r / 2) edges.pb({i, lb[2] + 1});
                    edges.pb({lb[1], lb[1] + r / 2});
                    for(int i=1; i<=(r - 3)/2; i++) for(int j=0; j<r; j++) edges.pb({lb[1] + j, lb[1] + (j + i) % r});
                }*/
            }
        }
        else
        {
            // d = 3k + 2
            //(1, r, 1, [1, r - 1, 1], 1, r, x)
            ll d = 3 * k + 2, x = n % (r + 1) - 1;
            vll lb(d + 1), ub(d + 1), cnt(d + 1);

            for(int i=0; i<=d; i++)
            {
                if(i == 0 || i == d - 2) cnt[i] = 1;
                else if(i == d) cnt[i] = x;
                else if(i == 1 || i == d - 1) cnt[i] = r;
                else if(i % 3 == 0) cnt[i] = 1;
                else if(i % 3 == 1) cnt[i] = r - 1;
                else if(i % 3 == 2) cnt[i] = 1;
            }

            ll start = 0;
            for(int i=0; i<=d; i++)
            {
                lb[i] = start;
                ub[i] = start + cnt[i];
                start += cnt[i];
            }

            // Inbetween
            for(int i=0; i<d; i++)
            {
                if(i == 1 || i == d - 2) continue;
                for(int u=lb[i]; u<ub[i]; u++) for(int v=lb[i+1]; v<ub[i+1]; v++) edges.pb({u, v});
            }

            // Inside
            for(int l=4; l<d-1; l+=3) for(int i=lb[l]; i<ub[l]; i++) for(int j=i+1; j<ub[l]; j++) edges.pb({i, j});

            // Inbetween D_{3k}, D_{3k+1} + Inside D_{3k + 1}
            for(int i=lb[d-1]; i<ub[d-1]-1; i++) edges.pb({lb[d-2], i});
            for(int i=2; i<=(r - x)/2; i++) for(int j=0; j<r-1; j++) edges.pb({lb[d-1] + j, lb[d-1] + (j + i) % (r - 1)});
            for(int i=lb[d-1]; i<lb[d-1]+r-x; i++) edges.pb({i, ub[d-1]-1});
            for(int i=lb[d-1]+r-x; i<ub[d-1]-1; i+=2) edges.pb({i, i+1});

            // Inbetween D_1, D_2 + Inside D-1
            for(int i=lb[1]; i<ub[1]-1; i++) {edges.pb({i, ub[1] - 1}); edges.pb({i, lb[2]});}
            for(int i=1; i<=(r - 3)/2; i++) for(int j=0; j<r-1; j++) edges.pb({lb[1] + j, lb[1] + (j + i) % (r - 1)});
        }
    }

    output(edges);
}
