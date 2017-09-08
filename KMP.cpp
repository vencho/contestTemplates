#include<iostream>
#include<conio.h>

#include<string>
#include<vector>

using namespace std;

vector <int> KMP(string T, string P);
vector <int> ComputePrefixFunction(string P);


int main()
{
string T, P;
vector <int> ans;


cin >> T >> P;
ans = KMP(T, P);

for(int i = 0; i < ans.size(); i++)
    printf("%d ", ans[i]);
printf("\n");

getch();
return 0;
}


vector <int> KMP(string T, string P)
{
vector <int> ans;
vector <int> pi;

int n = T.length();
int m = P.length();

T.insert(T.begin(), '#');
P.insert(P.begin(), '#');

pi = ComputePrefixFunction(P);

int q = 0;
for(int i = 1; i <= n; i++)
    {
    while(q > 0 && T[i] != P[q + 1]) q = pi[q];
    if(T[i] == P[q + 1]) q++;
    if(q == m)
        {
        ans.push_back(i - m + 1);
        q = pi[q];
        }
    }
return ans;
}



vector <int> ComputePrefixFunction(string P)
{
vector <int> pi;
int m = P.length() - 1;
pi.assign(m + 1, 0);


pi[1] = 0;
int q = 0;


for(int i = 2; i <= m; i++)
    {
    while(q > 0 && P[i] != P[q + 1]) q = pi[q];
    if(P[i] == P[q + 1]) q++;
    pi[i] = q;
    }
return pi;
}
