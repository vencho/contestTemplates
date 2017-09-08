#include<vector>
#include<algorithm>
#include<utility>
#define fst first
#define snd second

using namespace std;









class IntervalSet
{


private:
vector<pair<int, int> > L;


public:
IntervalSet() { }


void Insert(int a, int b)
{ Insert(make_pair(a, b)); }

void Insert(pair<int, int> p)
    {
    int a, b, x, y, i;

    a = p.fst; b = p.snd;
    for(i = 0; i < L.size(); i++)
        {
        x = L[i].fst; y = L[i].snd;
        if(a == b) return;
        if(x <= a && b <= y) return;
        else if(y <= a || b <= x) continue;
        else if(x <= a && a < y && y < b) { a = y; }
        else if(a < x && x < b && b <= y) { b = x; }
        else
            {
            Insert(make_pair(a, x));
            Insert(make_pair(y, b));
            return;
            }
        }

    if(a == b) return;
    L.push_back(make_pair(a, b));
    if(L.size() > 100) Normalise();
    }

int TotalCover()
    {
    Normalise();
    int ans = 0, i;
    for(i = 0; i < L.size(); i++)
        ans += L[i].snd-L[i].fst;
    return ans;
    }

pair<int, int> LongestUncoveredStretch()
    {
    int i;
    int best = 0;
    pair<int, int> bestPair = make_pair(0, 0);
    Normalise();
    for(i = 1; i < L.size(); i++)
        if(best < L[i].fst - L[i-1].snd)
            {
            best =  L[i].fst - L[i-1].snd;
            bestPair = make_pair(L[i-1].snd, L[i].fst);
            }

    return bestPair;
    }

pair<int, int> LongestCoveredStretch()
    {
    Normalise();
    int i;
    int best = 0;
    int besti = -1;

    for(i = 0; i < L.size(); i++)
        if(L[i].snd - L[i].fst > best)
            {
            best = L[i].snd - L[i].fst;
            besti = i;
            }
    if(besti >= 0) return L[besti];
    else return make_pair(0, 0);
    }

private:
void Display()
    {
    int i;
    printf("Display:\n");
    for(i = 0; i < L.size(); i++)
        printf("%d %d\n", L[i].fst, L[i].snd);
    }


void Normalise()
    {
    int a, b, x, y, i;
    vector<pair<int, int> > F;

    sort(L.begin(), L.end());
    if(L.size() == 0) return;


    a = L[0].fst;
    b = L[0].snd;
    for(i = 1; i < L.size(); i++)
        {
        x = L[i].fst; y = L[i].snd;
        if(x == b) b = y;
        else
            {
            F.push_back(make_pair(a, b));
            a = x; b = y;
            }
        }
    F.push_back(make_pair(a, b));
    L = F;
    }


};










IntervalSet S;
int main()
{
/*
printf("Stretch: (%d, %d).\n", S.LongestCoveredStretch().fst, S.LongestCoveredStretch().snd);
printf("Sum: %d.\n", S.TotalCover());

S.Insert(make_pair(4, 7));
S.Display();
S.Insert(make_pair(2, 6));
S.Display();
S.Insert(make_pair(5, 8));
S.Display();
S.Insert(make_pair(3, 10));
S.Display();
S.Insert(make_pair(1, 9));
S.Display();
S.Insert(make_pair(22, 24));
S.Insert(make_pair(23, 25));
S.Normalise();
S.Display();
printf("Stretch: (%d, %d).\n", S.LongestCoveredStretch().fst, S.LongestCoveredStretch().snd);
printf("Sum: %d.\n", S.TotalCover());
*/

system("pause");
return 0;
}

