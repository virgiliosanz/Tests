#include <iostream>

int main() {
    long long M = 600851475143;
    long long P=0;

	for(long long i = 3; i * i <= M; i += 2) {
        if((M % i) == 0) {
            P = i;
            while((M % i) == 0)
                M /= i;
        }
    }
    if(M > 1) P = M;
    std::cout << P << std::endl;

    return EXIT_SUCCESS;
}
