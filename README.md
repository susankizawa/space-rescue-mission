# Space Rescue Mission 🚀

Sistema de busca de rotas em uma rede de estações espaciais, desenvolvido em C++ para a disciplina de Teoria de Grafos. Funciona como um "Google Maps" para navegação entre estações espaciais.

## 📋 Descrição

O projeto simula uma rede de estações espaciais interconectadas por rotas com diferentes pesos (distâncias/custos). O objetivo principal é encontrar o caminho mais curto entre estações, similar ao funcionamento de aplicativos de navegação.

O sistema permite:

- Encontrar o caminho mais curto entre estações (Algoritmo de Dijkstra)
- Verificar se o grafo é fortemente conectado
- Verificar estatísticas da rede (densidade, número de rotas, etc)
- Bloquear/desbloquear rotas para simular falhas ou manutenção

## 🛠️ Estruturas Implementadas

- **Grafo direcionado com pesos**: Representação de estações e rotas
- **Dijkstra**: Busca de caminho mais curto considerando pesos das arestas
- **Análise de conectividade**: Verifica se é possível navegar entre todas as estações

## 📁 Estrutura do Projeto
```
space-rescue-mission/
├── src/
│   ├── main.cpp          # Menu principal e interface
│   ├── dijkstra.cpp      # Implementação do algoritmo de Dijkstra
│   ├── graph.cpp         # Estrutura de dados do grafo
│   └── ...
├── include/
│   ├── dijkstra.h
│   ├── graph.h
│   └── ...
├── build_and_run.bat     # Script para compilar e executar
└── CMakeLists.txt
```

## 🚀 Como Compilar e Executar

### Pré-requisitos
- CMake (3.10 ou superior)
- Compilador C++ com suporte a C++17
- Windows (para usar o script .bat)

### Primeira Execução

**Inicializar o projeto:**
```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cd ..
```

### Compilação e Execução

**Windows (recomendado):**
```bat
build_and_run.bat
```

**Manual:**
```bash
# Compilar
cmake --build build -j

# Executar
cd build
./space-rescue-mission
```

## 🎮 Como Usar

Ao executar o programa, você verá um menu interativo:
```
=== REDE DE ESTAÇÕES ESPACIAIS ===
1. Encontrar caminho mais curto
2. Informações da rede
3. Bloquear/Desbloquear rota
4. Sair
```

### Exemplos de Uso

**Encontrar caminho mais curto:**
- Selecione opção 1
- Digite a estação de origem
- Digite a estação de destino
- O sistema mostrará o caminho encontrado

**Testar rotas redundantes:**
- Bloqueie uma rota (opção 4)
- Tente encontrar caminho novamente (opção 1)
- Se ainda houver caminho, existe rota redundante

## 📊 Funcionalidades

### ✅ Implementadas
- [x] Encontrar caminho mais curto (Dijkstra)
- [x] Verificar conectividade entre estações
- [x] Rotas com pesos diferentes
- [x] Bloquear/desbloquear rotas
- [x] Estrutura de grafo direcionado
- [x] Verificar se é fortemente conectado
- [x] Calcular densidade do grafo
- [x] Calcular rotas redundantes (via bloqueio)
- [x] Menu interativo

### 🔮 Futuras (Opcionais)
- [ ] Visualização do grafo (PlantUML/GraphML)
- [ ] Medição de tempo de execução
