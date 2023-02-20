## Chess 4D Minimax

Módulo em C para o jogo Chess 4D. Para usar é necessário compilar o código como uma biblioteca compartilhada e usando o LuaJIT conforme a Makefile de exemplo desse repositório.

O módulo é configurável para buscar jogadas níveis N a frente, porém devido ao crescimento exponencial do número de jogadas, o tamanho da árvore de busca pode rapidamente ultrapassar o número de átomos do universo causando a explosão do mesmo.