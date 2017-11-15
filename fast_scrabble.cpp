#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
  map<int, multimap<string, string> > dico;
  ifstream file("dico.txt", ios::in);

  if (file) {
    string line, lineSorted;

    while (getline(file, line)) {
      lineSorted = line;
      transform(lineSorted.begin(), lineSorted.end(), lineSorted.begin(), ::tolower);
      sort(lineSorted.begin(), lineSorted.end());
      pair<string, string> p(lineSorted, line);
      dico[line.size()].insert(p);
    }

    file.close();
  }

  while (true) {
    string input;
    cout<<"Entrez des lettres:"<<endl;
    cin>>input;

    if(in)

    transform(input.begin(), input.end(), input.begin(), ::tolower);
    sort(input.begin(), input.end());
    multimap<string, string>::iterator it;
    for(it = dico[input.size()].begin(); it != dico[input.size()].end(); ++it)
      cout << (it->first == input ?  it->second + "\n" : "");

  }

  return 0;
}
