#include "config.h"
#include "logger.h"
#include "graph.h"
#include "stationNetwork.h"
#include "dataLoader.h"
#include "dijkstra.h"

#include <cstdio>
#include <cstdlib>

enum Screen {
  MAIN_MENU,
  SHORTEST_PATH,
  NETWORK_INFO,
  ROUTE_MANIPULATION,
  EXIT
};

StationNetwork* stationNetwork = (StationNetwork*) malloc(sizeof(StationNetwork));

Screen currentScreen = MAIN_MENU;

void printMenu() {
  printf("\n=== REDE DE ESTAÇÕES ESPACIAIS ===\n");
  printf("1. Encontrar caminho mais curto\n");
  printf("2. Informações da rede\n");
  printf("3. Bloquear/Desbloquear rota\n");
  printf("4. Sair\n");
  printf("Selecione uma opção: ");
}

void finalizeProgram() {
  cleanupStationNetwork(stationNetwork);
  cleanupLogger();
}

int main() {
  initializeStationNetwork(stationNetwork);

  initializeLogger();

  Path* shortestPath = (Path*) malloc(sizeof(Path));

  std::vector<Station> data = loadNetworkData("../data/estacoeserotas (1) copy.csv");

  buildNetworkFromData(stationNetwork, data);

  int select = -1;

  do {
    printMenu();

    scanf("%d", &select);

    switch(select) {
      case SHORTEST_PATH:
        currentScreen = SHORTEST_PATH;

        char origin[MAX_STATION_NAME_LENGTH], destination[MAX_STATION_NAME_LENGTH];

        initializePath(shortestPath);

        printf("Nome da estação de origem: ");
        scanf("%s", origin);
        printf("Nome da estação de destino: ");
        scanf("%s", destination);

        getShortestStationPath(stationNetwork, shortestPath, origin, destination);

        printf("Caminho encontrado:\n");
        printStationPath(stationNetwork, shortestPath);

        break;
      case NETWORK_INFO:
        currentScreen = NETWORK_INFO;
        printStationNetworkInfo(stationNetwork);
        printStationNetwork(stationNetwork);
        break;
      case ROUTE_MANIPULATION:
        currentScreen = ROUTE_MANIPULATION;

        char origin2[MAX_STATION_NAME_LENGTH], destination2[MAX_STATION_NAME_LENGTH];
        int select2, weight;
        select2 = -1;

        printf("Nome da estação de origem: ");
        scanf("%s", origin2);
        printf("Nome da estação de destino: ");
        scanf("%s", destination2);

        printf("1. Bloquear rota\n");
        printf("2. Desbloquear rota\n");
        printf("3. Cancelar\n");
        printf("Selecione uma opção: ");

        scanf("%d", &select2);

        if(select2 == 1) {
          bool success = removeRoute(stationNetwork, origin2, destination2);

          if(success) {
            printf("Rota bloqueada com sucesso!");
          } else {
            printf("Algum erro aconteceu ao tentar bloquear essa rota.");
          }
        } else if(select2 == 2) {
          printf("Peso da rota: ");
          scanf("%d", &weight);

          bool success = addRoute(stationNetwork, origin2, destination2, weight);

          if(success) {
            printf("Rota desbloqueada com sucesso!");
          } else {
            printf("Algum erro aconteceu ao tentar desbloquear essa rota.");
          }
        }

        break;
      case EXIT:
        currentScreen = EXIT;
        printf("Goodbye!\n");
        break;
      default:
        printf("You've selected an invalid option\n");
    }
  } while(select != EXIT);

  
  getchar();
  
  free(shortestPath);
  finalizeProgram();
}
