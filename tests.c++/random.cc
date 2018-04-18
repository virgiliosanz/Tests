#include <iostream>
#include <random>

using namespace std;

class Rand_int {
public:
     Rand_int(int low, int high): dist{low, high} {}
     int operator()() { return dist(re); }
private:
     default_random_engine re;
     uniform_int_distribution<> dist;
};

const size_t N = 10;
int main()
{
     Rand_int rnd {0, N - 1 };
     vector<int> histogram(N);
     int dat;
     size_t i;
     for (i = 0; i != 1000; ++i) {
          dat = rnd();
          cout << dat << " ";
          ++histogram[dat];
     }
     cout << endl;


     for (i = 0; i != histogram.size(); ++i) {
          cout << i << '\t';
          for (int j = 0; j != histogram[i]; ++j) cout << '*';
          cout << endl;
     }
}
