#include <bits/stdc++.h>
using namespace std;

#define d 256
vector<string> key;
vector<string> data;
vector<string> qkey;
vector<string> qdata;

void search(string pat, string txt,string qdes, string dbdes, int q)
{
    //cout << "*"<< endl;
   // cout << pat << endl;
    //cout << txt << endl;
    int M = pat.length();
   // cout << "M length is " << M << endl;
    int N = txt.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

   // cout << "$" << endl;
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
        //cout << "#" << endl;

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if (p == t)
        {
            //cout << "*" << endl;
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                //cout << "**" << endl;
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M){
                 //cout << "Pattern found at index " << i << endl;
                 qdes.erase(0,1);
                 dbdes.erase(0,1);
                 cout << qdes << endl << "[" << dbdes << "]" << " at offset " << i << endl;
            }
               
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

void readDNA()
{
    string line;
    string strdata;
    int flag = 0;
    ifstream myfile("data");
    if (myfile.is_open())
    {
        while (getline(myfile, line))

        {

            if (line[0] == '>' || line[0] == EOF)
            {
                if (flag == 1)
                {
                    data.push_back(strdata);
                    strdata.clear();
                }

                // cout << "\nyes\n";
                key.push_back(line);
                flag = 1;
                //cout << key;
            }
            else
            {
                strdata += line;
                //data.push_back(line);
            }
        }
        myfile.close();
        //cout << data;

        //cout << key;
    }

    else
        cout << "Unable to open file";
}

void readQuery()
{
    string line;
    string strdata;
    int flag = 0;
    ifstream myfile("query");
    if (myfile.is_open())
    {
        while (getline(myfile, line))

        {

            if (line[0] == '>' || line[0] == EOF)
            {
                if (flag == 1)
                {
                    qdata.push_back(strdata);
                    strdata.clear();
                }

                // cout << "\nyes\n";
                qkey.push_back(line);
                flag = 1;
                //cout << key;
            }
            else
            {
                strdata += line;
                //data.push_back(line);
            }
        }
        myfile.close();
        //cout << data;

        //cout << key;
    }

    else
        cout << "Unable to open file";
}

int main()
{
    int q = 101;
    readDNA();
    readQuery();

    //  for (int i = 0; i < key.size(); i++)
    //     {
    //         cout << key[i] << endl;
    //         cout << "-------------" << endl;
    //         cout << data[i] << endl;
    //     }

    // for (int i = 0; i < qkey.size(); i++)
    // {
    //     cout << qkey[i] << endl;
    //     cout << "-------------" << endl;
    //     cout << qdata[i] << endl;
    // }

    for (int i = 0; i < data.size(); i++)
    {
        //string dna = data[i];
        for (int j = 0; j < qdata.size(); j++)
        {
            //cout << data[i] << endl;
            // cout << qdata[i] << endl;
            search(qdata[j], data[i],qkey[j],key[i], q);
        }
    }
    return 0;
}