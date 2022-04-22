#include <iostream>
#include <vector>
using namespace std;

int pairup(int i, int n, string &base, vector<vector<int>> &opt, vector<int> &partner, vector<int> &global_partner);
int satisfyConds(int i, int j, string &base, vector<int> &partner);
bool matches_base(char x, char y);
int main()
{
    string base;
    cout << "Enter your RNA base sequence in uppercase format:\n";
    cin >> base;
    cout << "Sequence Length: " << base.length() << "\n";
    vector<int> partner(base.length() + 1, 0);
    vector<int> global_partner(base.length() + 1, 0);
    vector<vector<int>> opt(base.length() + 1, vector<int>(base.length() + 1));
    for (int i = 0; i < base.length(); i++)
    {
        for (int j = 0; j < base.length(); j++)
        {
            // if (i >= j - 4)
            opt[i][j] = 0;
            // else
            // opt[i][j] = -1;
        }
    }
    int ans = 0;
    ans = pairup(1, base.length(), base, opt, partner, global_partner);
    cout << "No. of pairs: " << ans << endl;
}

int pairup(int start, int end, string &base, vector<vector<int>> &opt, vector<int> &partner, vector<int> &global_partner)
{
    if ((start > 0) && (start < (base.length() - 4)) && (end > 5) && (end <= base.length()) && (start < (end - 4)))
    {
        for (int k = 5; k < end; k++)
        {
            for (int i = 0; i < (int)(partner.size()); i++)
                partner[i] = 0;
            for (int i = start; i <= end - k; i++)
            {
                int j = i + k;
                int maxt = -1;
                bool paired = false;
                int t;
                for (t = i; t < j - 4; t++)
                {
                    if (satisfyConds(t, j, base, partner) == 1)
                    {
                        int ans_paired = pairup(i, t - 1, base, opt, partner, global_partner) + pairup(t + 1, j - 1, base, opt, partner, global_partner);
                        if (maxt < ans_paired)
                        {
                            // partner[partner[t]] = 0;
                            // partner[partner[j]] = 0;
                            partner[t] = j;
                            partner[j] = t;
                            maxt = ans_paired;
                            paired = true;
                        }
                    }
                }
                if (paired)
                {
                    global_partner[t] = j;
                    global_partner[j] = t;
                    opt[i][j] = max(opt[i][j - 1], 1 + maxt);
                }
                else
                {
                    opt[i][j] = opt[i][j - 1];
                }
            }
        }
        return opt[start][end];
    }
    return 0;
}

int satisfyConds(int i, int j, string &base, vector<int> &partner)
{
    if (i > j - 4)
    {
        return 0;
    }
    else
    {
        if (matches_base(base[i - 1], base[j - 1]))
        {
            if (partner[i] == 0 && partner[j] == 0)
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
}

bool matches_base(char x, char y)
{
    if ((x == 'A' && y == 'U') || (x == 'U' && y == 'A') || (x == 'G' && y == 'C') || (x == 'C' && y == 'G'))
        return true;
    else
        return false;
}