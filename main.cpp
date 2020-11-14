#include "Game.hpp"
#include <gtkmm.h>
int main(int argc, char *argv[]) {
  using namespace game;
  using namespace Gtk;
  using namespace Glib;
  gWindow *pWindow = nullptr;
  auto app = gApplication::create(argc, argv, "org.gtkmm.example");
  gRefPtr<gBuilder> builder =
      gBuilder::create_from_file("tictactoegameUI.glade");
  builder->get_widget("TicTacToe", pWindow);
  Board board{
      {empty, empty, empty}, {empty, empty, empty}, {empty, empty, empty}};
  app->run(*pWindow);
  delete pWindow;
  return 0;
}
