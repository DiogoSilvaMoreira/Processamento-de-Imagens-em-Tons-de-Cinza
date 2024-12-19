/**
 * Universidade Federal de Alfenas (UNIFAL-MG)
 * Trabalho de AEDs I - Alfenas, MG - 18/07/2023
 * Docente: Paulo Bressan
 * Discentes: 
 *  - Pedro Henrique Botelho da Silva (2023.1.08.027)
 *  - Diogo da Silva Moreira (2023.1.08.003)
 * Processamento de imagens em tons de cinza.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime> // Biblioteca de data pro arquivo de log

// Definição da constante com o nome do arquivo de log
#define LOG_FILE "debug.log"

// Definição de constantes de cores
#define YELLOW "\e[1;33m"
#define GREEN "\e[1;32m"
#define RED "\e[1;31m"
#define RESET "\e[0m"
#define CYAN "\e[1;36m"
#define BLUE "\e[1;34m"
#define BLACK "\e[1;30m"

using namespace std;

typedef int image[1000][1000];
string error;

/**
 * Abre um arquivo de imagem e carrega os valores no vetor e nas variáveis que serão
 *  usadas posteriormente.
 *
 * @param filename Nome do arquivo que será aberto.
 * @param input_image Vetor que receberá os valores.
 * @param num_lines Ponteiro para a variável que armazena o número de linhas da imagem.
 * @param num_columns Ponteiro para a variável que armazena o número de colunas da imagem.
 * @param max_gray_value Ponteiro para a variável que armazena o valor máximo de branco da imagem.
 *
 * @return Código de saída da função. 1 - Erro na abertura/processamento da imagem; 0 - Sucesso.
 */
int open_image(string filename, image input_image, int *num_lines, int *num_columns, int *max_gray_value){
    string type;
    // Abrindo arquivo
    ifstream file (filename);
    if (!file.is_open()){
        error = "Não foi possível abrir a imagem! Certifique-se de ter digitado o nome do arquivo corretamente!";
        return 1;
    }
    file >> type >> *num_columns >> *num_lines >> *max_gray_value;
    // Checando se a imagem está no tipo P2 (ASCII), pois, não é possível trabalhar com ela em P5 (binário)
    if (type != "P2"){
        error = "A imagem escolhida não contém o formato P2 (ASCII)!";
        return 1;
    }
    // Evitando problemas com ponteiros
    if (*num_columns > 1000 || *num_lines > 1000){
        error = "A imagem deve ter as dimensões máximas de 1000x1000!";
        return 1;
    }
    for (int i = 0; i < *num_lines; i++){
        for (int j = 0; j < *num_columns; j++){
            file >> input_image[i][j];
        }
    }
    file.close();
    return 0;
}

/**
 * Abre um arquivo de imagem para salvar os valores passados.
 *
 * @param filename Nome do arquivo que será aberto.
 * @param output_image Vetor que receberá os valores.
 * @param num_lines Número de linhas da imagem.
 * @param num_columns Número de colunas da imagem.
 * @param max_gray_value Valor máximo de branco da imagem.
 *
 * @return Código de saída da função. 1 - Erro na abertura da imagem; 0 - Sucesso.
 */
int save_image(string filename, image output_image, int num_lines, int num_columns, int max_gray_value){
    // Abrindo arquivo
    ofstream file (filename);
    if(!file.is_open()){
        error = "Não foi possível criar a imagem de saída!";
        return 1;
    }
    file << "P2" << endl << num_columns << " " << num_lines << endl << max_gray_value << endl;
    for (int i = 0; i < num_lines; i++){
        for (int j = 0; j < num_columns; j++){
            file << output_image[i][j] << " ";
        }
        file << endl;
    }
    file.close();
    return 0;
}

/**
 * Função que ajusta o brilho de cada pixel da imagem baseado em um valor fornecido
 *  pelo usuário.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Número de linhas da imagem.
 * @param num_columns Número de colunas da imagem.
 * @param value Valor que será a base para o ajuste do brilho (incrementar ou decrementar).
 * @param max_gray_value Valor máximo de branco da imagem.
 * @param type Tipo de operação a ser realizada (increase/decrease).
 */
void adjust_bright_image(image input_image, image output_image, int num_lines, int num_columns, int value, int max_gray_value, string type){
    for (int i = 0; i < num_lines; i++){
        for (int j = 0; j < num_columns; j++){
            if (type == "increase") {
                if ((input_image[i][j] + value) > max_gray_value){  // Evitando que o aumento de brilho exceda o valor máximo
                    output_image[i][j] = max_gray_value;
                } else {
                    output_image[i][j] = input_image[i][j] + value;
                }
            } else {
                if ((input_image[i][j] - value) < 0){  // Evitando que a diminuição de brilho exceda o valor mínimo
                    output_image[i][j] = 0;
                } else {
                    output_image[i][j] = input_image[i][j] - value;
                }
            }
        }
    }
}

/**
 * Função que rotaciona uma imagem para a esquerda.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Ponteiro para a variável que armazena o número de linhas da imagem.
 * @param num_columns Ponteiro para a variável que armazena o número de colunas da imagem.
 */
void rotate_image_left(image input_image, image output_image, int *num_lines, int *num_columns){
    for (int i = 0, j = *num_columns; j >= 0; i++, j--){
        for (int k = 0; k < *num_lines; k++){
            output_image[i][k] = input_image[k][j];
        }
    }
    int temp = *num_lines;
    *num_lines = *num_columns;
    *num_columns = temp;
}

/**
 * Função que rotaciona uma imagem para a direita.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Ponteiro para a variável que armazena o número de linhas da imagem.
 * @param num_columns Ponteiro para a variável que armazena o número de colunas da imagem.
 */
void rotate_image_right(image input_image, image output_image, int *num_lines, int *num_columns){
    for (int i = 0; i < *num_columns; i++){
        for (int k = 0, j = *num_lines; k < *num_lines; k++, j--){
            output_image[i][k] = input_image[j][i];
        }
    }
    int temp = *num_lines;
    *num_lines = *num_columns;
    *num_columns = temp;
}

/**
 * Função que binariza uma imagem baseado em um valor fornecido pelo usuário.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Número de linhas da imagem.
 * @param num_columns Número de colunas da imagem.
 * @param value Valor que será o separador para a binarização (acima vira branco; abaixo vira preto).
 * @param max_gray_value Valor máximo de branco da imagem. 
 */
void binarize_image(image input_image, image output_image, int num_lines, int num_columns, int value, int max_gray_value){
    for (int i = 0; i < num_lines; i++){
        for (int j = 0; j < num_columns; j++) {
            if (input_image[i][j] >= value) {
                output_image[i][j] = max_gray_value;
            } else {
                output_image[i][j] = 0;
            }
        }
    }
}

/**
 * Cria um ícone (64x64) de uma imagem.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Ponteiro para a variável que armazena o número de linhas da imagem.
 * @param num_columns Ponteiro para a variável que armazena o número de colunas da imagem.
 *
 * @return Código de saída da função. 1 - Erro na criação do ícone; 0 - Sucesso.
 */
int make_icon(image input_image, image output_image, int *num_lines, int *num_columns){
    int lines_part = (*num_lines) / 64,
        columns_part = (*num_columns) / 64,
        media = 0;
    if (lines_part < 1 || columns_part < 1){
        error = "A imagem não pode ter dimensões menores ou iguais a 64x64!";
        return 1;
    }
    for (int i = 0; i < *num_lines; i += lines_part) {
        for (int j = 0; j < *num_columns; j += columns_part) {
            media = 0;
            for (int k = i; k < i + lines_part; k++) {
                for (int l = j; l < j + columns_part; l++) {
                    media += input_image[k][l];
                }
            }
            media = media / (lines_part * columns_part);
            output_image[i / lines_part][j / columns_part] = media;
        }
    }
    *num_lines = 64;
    *num_columns = 64;
    return 0;
}

/**
 * Função que aplica o efeito passa-baixa na imagem.
 *
 * @param input_image Vetor que será lido.
 * @param output_image Vetor que será escrito.
 * @param num_lines Número de linhas da imagem.
 * @param num_columns Número de colunas da imagem.
 */
void apply_passa_baixa(image input_image, image output_image, int num_lines, int num_columns){
    int new_value = 0;
    for (int i = 1; i < num_lines - 1; i++){
        for (int j = 1; j < num_columns - 1; j++){
            for (int k = i - 1; k <= i + 1; k++){
                for (int l = j -1; l <= j + 1; l++){
                    new_value = input_image[k][l];
                }
            }
            new_value = new_value/9;
            output_image[i][j] = new_value;
        }
    }
    for(int i = 0; i < num_columns; i++){
        output_image[0][i]= input_image[0][i];
        output_image[num_lines - 1][i] = input_image[num_lines - 1][i];
    }
    for(int j = 0; j < num_lines; j++){
        output_image[j][0]= input_image[j][0];
        output_image[j][num_columns - 1] = input_image[j][num_columns - 1];
    }
}

/**
 * Função que escreve as mensagens no arquivo de log.
 *
 * @param message Mensagem que será escrita.
 */
void write_log(string message){
    ofstream file;
    file.open(LOG_FILE, std::ios_base::app); // Abrindo o arquivo como append, para evitar sobrescrita
    // Formatando data e hora atual para escrita do log
    time_t now = time(0);
    tm *datetime = localtime(&now);
    // [Dia/Mês/Ano-Hora:Minuto:Segundo] - Mensagem
    file << "[" << datetime->tm_mday << 
                "/" << (datetime->tm_mon + 1) <<
                "/" << (datetime->tm_year + 1900) <<
                "-" << (datetime->tm_hour) << 
                ":" << (datetime->tm_min) <<
                ":" << (datetime->tm_sec) <<
                "]" << " - " << message << endl;
}

int main() {
    image input_image, output_image;
    string filename, type, msg;
    int lines = 0, columns = 0, max_gray_value = 0, value = 0;

    // Banner
    cout << GREEN "                          _              _ _    _ _   " << endl;
    cout << GREEN "  _ __   __ _ _ __ ___   | |_ ___   ___ | | | _(_) |_ " << endl;
    cout << GREEN " | '_ \\ / _` | '_ ` _ \\  | __/ _ \\ / _ \\| | |/ / | __|" << endl;
    cout << GREEN " | |_) | (_| | | | | | | | || (_) | (_) | |   <| | |_ " << endl;
    cout << GREEN " | .__/ \\__, |_| |_| |_|  \\__\\___/ \\___/|_|_|\\_\\_|\\__|" << endl;
    cout << GREEN " |_|    |___/                                         " << endl << endl << endl;

    // Menu de seleção das opções do programa
    cout << YELLOW "\n\n *-------- Menu de seleção --------*" << endl << 
    BLUE "   0. " << RESET "Sair" << endl <<
    BLUE "   1. " << RESET "Ajustar o brilho da imagem" << endl <<
    BLUE "   2. " << RESET "Rotacionar a imagem" << endl << 
    BLUE "   3. " << RESET "Binarizar a imagem" << endl << 
    BLUE "   4. " << RESET "Criar ícone da imagem" << endl <<
    BLUE "   5. " << RESET "Aplicar filtro passa-baixa" << endl <<
    YELLOW "  Selecione uma opção [0-5]: > " << BLACK;
    cin >> value;
    while ((value < 0) || (value > 5)){
        cout << RED "  Opção inválida! Insira novamente: > " << BLACK;
        cin >> value;
    }

    while(value != 0) {
        // Obtendo nome do arquivo original
        cout << YELLOW " *---------------------------------*\n";
        cout << "   Insira o nome da imagem original (com extensão): > " BLACK;
        cin >> filename;
        while (open_image(filename, input_image, &lines, &columns, &max_gray_value) != 0){
            cout << RED "   ERRO! - " << error << endl;
            cout << YELLOW "   Insira o nome da imagem original (com extensão): > " BLACK;
            cin >> filename;
        }

        // Informações gerais da imagem original
        cout << YELLOW " *----- Informações da imagem -----*" << endl << 
        BLUE "   Nome: " << RESET << filename << endl <<
        BLUE "   Colunas x Linhas: " << RESET << columns << "x" << lines << endl <<
        BLUE "   Valor máximo: " << RESET << max_gray_value << endl;

        if (value == 1){ // Alteração de brilho da imagem
            cout << YELLOW " *-------------- Ação -------------*" << endl << 
            BLUE "   1. " << RESET "Aumentar" << endl <<
            BLUE "   2. " << RESET "Diminuir" << endl <<
            YELLOW "  Selecione uma opção [1-2]: > " BLACK;
            cin >> value;
            while((value < 1) || (value > 2)){
                cout << RED "  Opção inválida! Insira novamente: > " << BLACK;
                cin >> value;
            }
            if (value == 1){
                type = "increase";
                msg = "A imagem " + filename + " teve o brilho aumentado em";
            } else {
                type = "decrease";
                msg = "A imagem " + filename + " teve o brilho diminuído em";
            }
            // Obtendo percentual para aumentar ou diminuir o brilho da imagem
            cout << YELLOW "  Insira o percentual a ser aplicado: > " << BLACK;
            cin >> value;
            while ((value > 100) || (value < 0)){
                cout << RED "  A porcentagem deve estar entre 0% e 100%: > " << BLACK;
                cin >> value;
            }
            msg = msg + " " + to_string(value) + "%";
            value = (value * max_gray_value)/100;
            adjust_bright_image(input_image, output_image, lines, columns, value, max_gray_value, type);
        } else if (value == 2){ // Rotação da imagem
            cout << YELLOW " *-------------- Ação -------------*" << endl << 
            BLUE "   1. " << RESET "Direita" << endl <<
            BLUE "   2. " << RESET "Esquerda" << endl <<
            YELLOW "  Selecione uma opção [1-2]: > " << BLACK;
            cin >> value;
            while((value < 1) || (value > 2)){
                cout << RED "  Opção inválida! Insira novamente: > " << BLACK;
                cin >> value;
            }
            if (value == 1){ // Rotação para a direita
                rotate_image_right(input_image, output_image, &lines, &columns);
                msg = "A imagem " + filename + " foi rotacionada para a direita";
            } else { // Rotação para a esquerda
                rotate_image_left(input_image, output_image, &lines, &columns);
                msg = "A imagem " + filename + " foi rotacionada para a esquerda";
            }
        } else if (value == 3){ // Binarização da imagem
            // Obtendo valor que determinará o valor de binarização
            cout << YELLOW "  Insira o valor para a binarização: > " << BLACK;
            cin >> value;
            while ((value < 0) || (value > max_gray_value)){
                cout << RED "  O valor deve estar entre " << CYAN << "0" << RED << " e " << CYAN << max_gray_value << RED << ": > " << BLACK;
                cin >> value;
            }
            binarize_image(input_image, output_image, lines, columns, value, max_gray_value);
            msg = "A imagem " + filename + " foi binarizada com o valor base em " + to_string(value);
        } else if (value == 4){ // Criação de ícone da imagem
            if(make_icon(input_image, output_image, &lines, &columns) != 0){ // Retorno de erro da função de criação de ícone
                cout << RED "  ERRO! - " << error << endl;
                return 1;
            }
            msg = "Foi criado um ícone da imagem " + filename;
        } else {
            apply_passa_baixa(input_image, output_image, lines, columns);
            msg = "O efeito passa-baixa foi aplicado na imagem " + filename;
        }

        cout << YELLOW " *-------------- Saída -------------*" << endl;
        // Obtendo nome do arquivo de saída
        cout << YELLOW "  Insira o nome da imagem de saída (com extensão): > " << BLACK;
        cin >> filename;
        // Salvando a imagem
        if (save_image(filename, output_image, lines, columns, max_gray_value) != 0) {
            cout << "  ERRO! - " << error << endl;
            return 1;
        }
        cout << YELLOW " *---------------------------------*\n";
        msg = msg + " " + "e foi salva como " + filename;
        cout << GREEN << "  " << msg << endl;
        write_log(msg);

        // Menu de seleção das opções do programa
        cout << YELLOW "\n\n *-------- Menu de seleção --------*" << endl << 
        BLUE "   0. " << RESET "Sair" << endl <<
        BLUE "   1. " << RESET "Ajustar o brilho da imagem" << endl <<
        BLUE "   2. " << RESET "Rotacionar a imagem" << endl << 
        BLUE "   3. " << RESET "Binarizar a imagem" << endl << 
        BLUE "   4. " << RESET "Criar ícone da imagem" << endl <<
        BLUE "   5. " << RESET "Aplicar filtro passa-baixa" << endl <<
        YELLOW "  Selecione uma opção [0-5]: > " << BLACK;
        cin >> value;
        while ((value < 0) || (value > 5)){
            cout << RED "  Opção inválida! Insira novamente: > " << BLACK;
            cin >> value;
        }
    };
   
    return 0;
}