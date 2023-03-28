#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;

struct Narudzba {
  int strana;
  double cijena;
  int kolicina;
  int vrijeme;
  public:
    Narudzba(int s, double c, int k, int v) : strana{s}, cijena{c}, 
      kolicina{k}, vrijeme{v} {};
};

vector<Narudzba> filtriraj(const vector<Narudzba> &n, function<bool(Narudzba)> func) {
  vector<Narudzba> m;
  for(int i = 0; i < n.size(); ++i)
  {
    if(func(n[i])) m.push_back(n[i]);
  }

  return m;
}

int main(void)
{
  vector<Narudzba> n;
  n.push_back(Narudzba{0, 1.0, 1, 12});
  n.push_back(Narudzba{1, 2.0, 2, 10});
  n.push_back(Narudzba{0, 3.0, 3, 8});
  n.push_back(Narudzba{1, 4.0, 4, 6});
  n.push_back(Narudzba{1, 5.0, 5, 4});
  n.push_back(Narudzba{0, 6.0, 6, 2});
  auto m = filtriraj(n, [](const Narudzba& x){return x.strana == 0;});

  for(int i = 0; i < m.size(); ++i)
  {
    cout << m[i].cijena << endl;
  }

  sort(m.begin(), m.end(), [](const Narudzba &x, const Narudzba &y){return x.vrijeme < y.vrijeme;});

  for(int i = 0; i < m.size(); ++i)
  {
    cout << m[i].vrijeme << endl;
  }

  return 0;
}
