#include "config.h"
#include "graph.h"
#include "stationNetwork.h"
#include "logger.h"
#include "dataLoader.h"

#include "ftxui/dom/canvas.hpp"  // for Canvas
#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui

#include <stdio.h>                 // for getchar
#include <stdlib.h>
#include <string.h>
#include <cmath>                   // for cos
#include <ftxui/dom/elements.hpp>  // for Fit, canvas, operator|, border, Element
#include <ftxui/screen/screen.hpp>  // for Pixel, Screen
#include <vector>                   // for vector, allocator

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>




StationNetwork* stationNetwork = (StationNetwork*) malloc(sizeof(StationNetwork));

void finalizeProgram() {
  cleanupStationNetwork(stationNetwork);
  cleanupLogger();
}

int main() {
  using namespace ftxui;

  initializeStationNetwork(stationNetwork);

  initializeLogger();

  std::vector<Station> data = loadNetworkData("../data/estacoeserotas (1) copy.csv");

  buildNetworkFromData(stationNetwork, data);

  printStationNetworkInfo(stationNetwork);

  printStationNetwork(stationNetwork);

  getchar();

  finalizeProgram();

  /*
  StationNetwork* sn = (StationNetwork*) malloc(sizeof(StationNetwork));
  initializeStationNetwork(sn);
  addStation(sn, "Volt");
  addStation(sn, "Veritas");
  addStation(sn, "Vermilion");
  addStation(sn, "Virgo");
  addStation(sn, "Vulture");
  addStation(sn, "Vagabond");
  addStation(sn, "Vanguard");
  addStation(sn, "Voodoo");
  addStation(sn, "Vendetta");
  addRoute(sn, "Volt", "Veritas");
  addRoute(sn, "Veritas", "Virgo");
  addRoute(sn, "Virgo", "Vermilion");
  printStationNetworkInfo(sn);
  printf("Routes:\n");
  printStationNetwork(sn);
  printf("Pls work\n");
  
  */

  /*
  auto c = Canvas(100, 100);

  c.DrawText(0, 0, "My graph:", [](Pixel& p) {
    p.foreground_color = Color::Red;
    p.underlined = true;
  });

  // Triangle:
  //c.DrawPointLine(10, 10, 80, 10, Color::Red);
  //c.DrawPointLine(80, 10, 80, 40, Color::Blue);
  //c.DrawPointLine(80, 40, 10, 10, Color::Green);

  // Circle, not filled and filled:
  c.DrawPointCircle(50, 50, 20);

  // Plot a function:
  std::vector<int> ys(100);
  for (int x = 0; x < 100; x++) {
    ys[x] = int(80 + 20 * cos(x * 0.2));
  }
  for (int x = 0; x < 99; x++) {
    c.DrawPointLine(x, ys[x], x + 1, ys[x + 1], Color::Red);
  }

  auto document = canvas(&c) | border;

  auto screen = Screen::Create(Dimension::Fit(document), Dimension::Full());
  Render(screen, document);
  screen.Print();
  getchar();

  return 0;
  */

  /*
  auto summary = [&] {
    auto content = vbox({
        hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
        hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
        hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
    });
    return window(text(L" Summary "), content);
  };

  auto document =  //
      vbox({
          hbox({
              summary(),
              summary(),
              summary() | flex,
          }),
          summary(),
          summary(),
      });

  // Limit the size of the document to 80 char.
  document = document | size(WIDTH, LESS_THAN, 80);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  std::cout << screen.ToString() << '\0' << std::endl;

  return EXIT_SUCCESS;
  */
}
