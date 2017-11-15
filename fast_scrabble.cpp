#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

int main()
{
  map<int, multimap<string, string> > dico;
  ifstream file("dico.txt", ios::in);

  if (file) {
    string line, lineSorted;

    while (safeGetline(file, line)) {
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

    transform(input.begin(), input.end(), input.begin(), ::tolower);
    sort(input.begin(), input.end());
    multimap<string, string>::iterator it;
    for(it = dico[input.size()].begin(); it != dico[input.size()].end(); ++it)
      cout << (it->first == input ?  it->second + "\n" : "");

  }

  return 0;
}
