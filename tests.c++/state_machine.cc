#include <cstdint>
#include <cstdio>

using namespace std;

class LCD {
    void print(const char* s) { puts(s); }
};

extern LCD* lcd;

class Screen;

enum class Clicked : uint8_t { Up, Down, Left, Right, Ok, Esc };

class Interfaze {
    friend class Screen;

  public:
    Interfaze(LCD* lcd);
    void loop();
    void setup();

  private:
    Screen* screen;
    LCD* lcd;
};

class Screen {
  public:
    virtual void up();
    virtual void down();
    virtual void Left();
    virtual void right();
    virtual void ok();
    virtual void esc();

    virtual void timeout();

    virtual ~Screen();

  protected:
    void update_interfaze(Interfaze& interfaze, Screen* screen);
    void set_screen(Interfaze& Interfaze, Screen* screen);

  private:
    void save();
};

void Screen::set_screen(Interfaze& interfaze, Screen* screen)
{
    Screen* aux = interfaze.screen;
    interfaze.screen = screen;
    delete aux;
}

class Main : protected Screen {
    class Show;
    class Edit;
};

class Main::Show : protected Main {
};
class Main::Edit : protected Main {
};

class Second : protected Screen {
    class Show;
    class Edit;
};

class Second::Show : protected Second {
};
class Second::Edit : protected Second {
};

class Third : protected Screen {
    class Show;
    class Edit;
};

class Third::Show : protected Third {
};
class Third::Edit : protected Third {
};
