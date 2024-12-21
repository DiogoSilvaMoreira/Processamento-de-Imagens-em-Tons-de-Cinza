--------- Projeto de Manipulação de Imagens PGM ---------

Objetivo

O objetivo deste projeto é adquirir conhecimentos sobre a manipulação de imagens em formato de matrizes, utilizando operações de controle e geração de novas imagens a partir de imagens lidas de arquivos no formato PGM.
Descrição

O aplicativo desenvolvido realiza a leitura de uma imagem no formato PGM e permite a execução de diversas operações de manipulação sobre a imagem. Cada operação é realizada a partir de um menu interativo, gerando um novo arquivo PGM como resultado.

As operações disponíveis no projeto incluem o escurecimento ou clareamento da imagem, rotação, binarização, redução de tamanho e suavização da imagem. Cada operação resulta em um novo arquivo de imagem que pode ser visualizado ou utilizado para etapas posteriores de processamento.

Após a leitura do arquivo, o aplicativo realizará as seguintes operações sobre a imagem:

    Escurecimento ou clareamento da imagem com um fator informado pelo usuário.
    Rotação da imagem à direita ou à esquerda.
    Binarização da imagem com um fator de limiar informado pelo usuário.
    Redução da imagem para um tamanho de 64 x 64 pixels.
    Aplicação de filtro passa-baixa para suavizar a imagem.

Arquivo de Entrada

O arquivo de entrada, chamado imagem.pgm, deve conter a imagem no formato PGM. O formato segue as seguintes especificações:

    Primeira linha: String "P2" (indicando que é uma imagem no formato ASCII).
    Segunda linha: Quantidade de colunas e linhas (ex: width height).
    Terceira linha: Valor máximo de tons de cinza (ex: 255).
    Linhas seguintes: Valores inteiros representando os tons de cinza dos pixels, entre 0 e o valor máximo de tons de cinza.

Exemplo de arquivo PGM:

P2
4 4
255
0 0 0 255
0 255 0 0
255 0 0 255
0 0 255 0

---

Requisitos

O aplicativo deverá realizar as seguintes operações sobre a imagem:

    Escurecer ou clarear a imagem por um fator informado pelo usuário.
    Rotacionar a imagem à direita: Gira a imagem 90 graus no sentido horário.
    Rotacionar a imagem à esquerda: Gira a imagem 90 graus no sentido anti-horário.
    Binarizar a imagem: Converte a imagem em preto e branco com base em um fator de limiar informado pelo usuário.
    Iconizar a imagem: Reduz a imagem para 64 x 64 pixels.
    Aplicar filtro passa-baixa: Suaviza a imagem, aplicando um filtro para reduzir detalhes.

Cada operação deve ser implementada em uma função separada e gerar um arquivo de saída no formato PGM correspondente.
Tecnologias Utilizadas

    Linguagem de programação: C++
    Estruturas de controle: Condicionais, loops.
    Leitura e escrita de arquivos: Manipulação de arquivos no formato PGM.

Como Executar

    Clone o repositório.
    Coloque o arquivo imagem.pgm no mesmo diretório do projeto.
    Compile o código e execute o aplicativo.


    
