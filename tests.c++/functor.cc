#include <iostream>

class Prueba {
public:
  static void run() {std::cout << "Hola desde clase de Prueba->run()" << std::endl;}
};

void hola() {std::cout << "Hola desde clase de hola()" << std::endl;}

typedef void function();
void run(function f) {
    std::cout << "Run...." << std::endl;
    f();
}

int main() {
  Prueba p;
  run(p.run);

  run(hola);

  return EXIT_SUCCESS;
}
