// esta classe gerencia as camadas e aquele menu que tem os botoes de gerenciar as classes

#include "GerenciadorCamadas.h"
#include <string.h>
#include "gl_canvas2d.h"
#include <vector>
#include <stdlib.h>
#include <time.h>


gerenciadorCamadas::gerenciadorCamadas(int grossuraBordasLateraisNasCamadas, int bordaMenuLateralX, int screenHeight, int screenWidth, int inicioMenuLateralX)
{
    borda1X = grossuraBordasLateraisNasCamadas;
    borda1Y = grossuraBordasLateraisNasCamadas;
    borda2X = bordaMenuLateralX;
    borda2Y = screenHeight - grossuraBordasLateraisNasCamadas;
    width = borda2X - borda1X;
    height = borda2Y - borda1Y;

    caixaBotoes1X = inicioMenuLateralX + 13;
    caixaBotoes1Y = 15;
    caixaBotoes2X = screenWidth - 5;
    caixaBotoes2Y = (screenHeight / 20) * (MAX_CAMADAS) + 20;
    pintando = 0;
    qntCamadas = 0;
}

void gerenciadorCamadas::carregaCamada(unsigned char *data, int imgWidth, int imgHeight){ // coloca uma camada nova com a imagem dela no centro
    Camada novaCamada;
    novaCamada.camada = new unsigned char[width * height * 4];
    int i, j, posRGBA, posRGB;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            posRGBA = (i * width + j) * 4;
            novaCamada.camada[posRGBA] = 255;
            novaCamada.camada[posRGBA + 1] = 255;
            novaCamada.camada[posRGBA + 2] = 255;
            novaCamada.camada[posRGBA + 3] = 0;
        }
    }

    for(i = 0; i < imgHeight; i++){
        for(j = 0; j < imgWidth; j++){
            posRGBA = ((width * height / 2 + width / 2) - (imgHeight * width / 2 + imgWidth / 2) + (i * width + j)) * 4; // carrega no centro
            posRGB = (i * imgWidth + j) * 3;
            novaCamada.camada[posRGBA] = data[posRGB];
            novaCamada.camada[posRGBA+1] = data[posRGB+1];
            novaCamada.camada[posRGBA+2] = data[posRGB+2];
            novaCamada.camada[posRGBA+3] = 1;
        }
    }
    novaCamada.visivel = 1;
    camadas.push_back(novaCamada);
    qntCamadas++;
    camadaAtiva = qntCamadas - 1;
}

void gerenciadorCamadas::render(){ // renderiza as camadas e os botoes das camadas
    int i, j, posRGBA, deslocX = borda1X, deslocY = borda1Y;
    float r, g, b;
    for(Camada camada : camadas){
        if(camada.visivel == 0){
            continue;
        }
        for(i = 0; i < height; i++){
            for(j = 0; j < width; j++){
                posRGBA = (i * width + j) * 4;
                r = camada.camada[posRGBA];
                g = camada.camada[posRGBA+1];
                b = camada.camada[posRGBA+2];
                if(camada.camada[posRGBA+3] == 1){ 
                    CV::color(r / 255, g / 255, b / 255);
                    CV::rectFill(j + deslocX, i + deslocY, j + deslocX + 1, i + deslocY + 1);
                }
            }
        }
    }
    renderBotaoCamada();
    renderCaixaCamadas();
}

bool gerenciadorCamadas::verificaMouseCamada(int mouseX, int mouseY){ // função auxiliar pra verificar se o mouse esta na camada
    if(mouseX > borda1X && mouseX < borda2X && mouseY > borda1Y && mouseY < borda2Y){
        return 1;
    }
    return 0;
}

void gerenciadorCamadas::setPintando(bool valor){
    pintando = valor;
}

bool gerenciadorCamadas::getPintando(){
    return pintando;
}

void gerenciadorCamadas::addBotaoCamada(int camadaAtiva, int screenWidth, int screenHeight, int inicioMenuLateralX){ // adiciona um novo botao no menu de gerenciador de camadas
    BotaoCamadas novoBotao;
    novoBotao.borda1X = inicioMenuLateralX + 30;
    novoBotao.borda1Y = screenHeight * (camadaAtiva) / 20 + 20;
    novoBotao.borda2X = screenWidth - 10;
    novoBotao.borda2Y = novoBotao.borda1Y + 30;
    novoBotao.moveCima.borda1X = novoBotao.borda1X - 15;
    novoBotao.moveCima.borda1Y = novoBotao.borda1Y + 16;
    novoBotao.moveCima.borda2X = novoBotao.borda1X - 2;
    novoBotao.moveCima.borda2Y = novoBotao.borda2Y;
    novoBotao.moveCima.cima = 1;

    novoBotao.moveBaixo.borda1X = novoBotao.borda1X - 15;
    novoBotao.moveBaixo.borda1Y = novoBotao.borda1Y;
    novoBotao.moveBaixo.borda2X = novoBotao.borda1X - 2;
    novoBotao.moveBaixo.borda2Y = novoBotao.moveBaixo.borda1Y + 14;
    novoBotao.moveBaixo.cima = 0;

    novoBotao.bordaHideX = (novoBotao.borda1X * 2 + novoBotao.borda2X * 8) / 10;

    novoBotao.posCamada = camadaAtiva;
    char nome[50];
    sprintf(nome, "Camada %d", camadaAtiva + 1);
    strcpy(novoBotao.nome, nome);
    botaoCamadas.push_back(novoBotao);
}

void gerenciadorCamadas::renderBotaoSwitch(BotaoSwitch botaoSwitch){ // renderiza aquelas flechas pra movimentar a camada para cima ou para baixo
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(botaoSwitch.borda1X, botaoSwitch.borda1Y, botaoSwitch.borda2X, botaoSwitch.borda2Y);
    CV::color(1, 1, 1);
    float vector1X[3] = {(float)botaoSwitch.borda1X, (float)(botaoSwitch.borda1X + botaoSwitch.borda2X)/2, (float)botaoSwitch.borda2X};
    float vector1Y[3] = {(float)botaoSwitch.borda1Y, (float)botaoSwitch.borda2Y, (float)botaoSwitch.borda1Y};
    float vector2X[3] = {(float)botaoSwitch.borda1X, (float)(botaoSwitch.borda1X + botaoSwitch.borda2X)/2, (float)botaoSwitch.borda2X};
    float vector2Y[3] = {(float)botaoSwitch.borda2Y, (float)botaoSwitch.borda1Y, (float)botaoSwitch.borda2Y};
    if(botaoSwitch.cima == 1){
        CV::polygonFill(vector1X, vector1Y, 3);
    }
    else{
        CV::polygonFill(vector2X, vector2Y, 3);
    }
}

void gerenciadorCamadas::renderBotaoCamada(){ // renderiza os botoes de cada camada
    for(BotaoCamadas botaoCamada : botaoCamadas){
        CV::color(0.3, 0.3, 0.3);
        CV::rectFill(botaoCamada.borda1X, botaoCamada.borda1Y, botaoCamada.borda2X, botaoCamada.borda2Y);
        CV::color(1, 1, 1);
        if(camadaAtiva == botaoCamada.posCamada){
            CV::rect(botaoCamada.borda1X, botaoCamada.borda1Y, botaoCamada.borda2X, botaoCamada.borda2Y);
        }
        renderBotaoSwitch(botaoCamada.moveCima);
        renderBotaoSwitch(botaoCamada.moveBaixo);
        CV::color(0, 0, 0);
        CV::line(botaoCamada.bordaHideX, botaoCamada.borda1Y, botaoCamada.bordaHideX, botaoCamada.borda2Y);
        CV::color(1, 1, 1);
        CV::text(botaoCamada.bordaHideX + 7, (botaoCamada.borda1Y + botaoCamada.borda2Y) /2 - 2, "Hide");

        CV::text(botaoCamada.borda1X + 5, (botaoCamada.borda1Y + botaoCamada.borda2Y) /2 - 2, botaoCamada.nome);
        if(camadas[botaoCamada.posCamada].visivel == 0){
            CV::color(1, 0, 0);
            CV::line(botaoCamada.bordaHideX, botaoCamada.borda1Y, botaoCamada.borda2X, botaoCamada.borda2Y);
            CV::line(botaoCamada.bordaHideX, botaoCamada.borda2Y, botaoCamada.borda2X, botaoCamada.borda1Y);
        }
    }
}

void gerenciadorCamadas::renderCaixaCamadas(){ // renderiza aquela caixinha em volta dos botoes
    CV::color(0.9, 0.9, 0.9);
    CV::rect(caixaBotoes1X, caixaBotoes1Y, caixaBotoes2X, caixaBotoes2Y);
}

int gerenciadorCamadas::getQntCamadas(){
    return qntCamadas;
}

bool gerenciadorCamadas::verificaBotaoHide(int mouseX, int mouseY){ // verifica se clicou no botao hide, e trata o click
    for(BotaoCamadas botaoCamada : botaoCamadas){
        if(mouseX > botaoCamada.bordaHideX && mouseX < botaoCamada.borda2X && mouseY > botaoCamada.borda1Y && mouseY < botaoCamada.borda2Y){
            if(camadas[botaoCamada.posCamada].visivel == 1){
                camadas[botaoCamada.posCamada].visivel = 0;
            }
            else{
                camadas[botaoCamada.posCamada].visivel = 1;
            }
            return 1;
        }
    }
    return 0;
}

bool gerenciadorCamadas::verificaBotaoAtiva(int mouseX, int mouseY){ // verifica se clicou pra ativar a camada, e trata o click
    for(BotaoCamadas botaoCamada : botaoCamadas){
        if(mouseX > botaoCamada.borda1X && mouseX < botaoCamada.bordaHideX && mouseY > botaoCamada.borda1Y && mouseY < botaoCamada.borda2Y){
            camadaAtiva = botaoCamada.posCamada;
            return 1;
        }
    }
    return 0;
}

bool gerenciadorCamadas::verificaBotaoCima(int mouseX, int mouseY){ // verifica se clicou no botao colocar camada pra cima, e trata o click
    for(BotaoCamadas botaoCamada : botaoCamadas){
        if(mouseX > botaoCamada.moveCima.borda1X && mouseX < botaoCamada.moveCima.borda2X && mouseY > botaoCamada.moveCima.borda1Y && mouseY < botaoCamada.moveCima.borda2Y){
            if(botaoCamada.posCamada < qntCamadas - 1){
                Camada temp = camadas[botaoCamada.posCamada];

                char nome1[50], nome2[50];
                strcpy(nome1, botaoCamadas[botaoCamada.posCamada].nome);
                strcpy(nome2, botaoCamadas[botaoCamada.posCamada + 1].nome);

                camadas[botaoCamada.posCamada] = camadas[botaoCamada.posCamada + 1];
                camadas[botaoCamada.posCamada + 1] = temp;
                
                strcpy(botaoCamadas[botaoCamada.posCamada + 1].nome, nome1);
                strcpy(botaoCamadas[botaoCamada.posCamada].nome, nome2);
                
                if(camadaAtiva == botaoCamada.posCamada){
                    camadaAtiva++;
                }
                else if(camadaAtiva == botaoCamada.posCamada + 1){
                    camadaAtiva--;
                }
                return 1;
            }
            
        }
    }
    return 0;
}

bool gerenciadorCamadas::verificaBotaoBaixo(int mouseX, int mouseY){ // verifica se clicou no botao colocar camada pra baixo, e trata o click
    for(BotaoCamadas botaoCamada : botaoCamadas){
        if(mouseX > botaoCamada.moveBaixo.borda1X && mouseX < botaoCamada.moveBaixo.borda2X && mouseY > botaoCamada.moveBaixo.borda1Y && mouseY < botaoCamada.moveBaixo.borda2Y){
            if(botaoCamada.posCamada > 0){
                Camada temp = camadas[botaoCamada.posCamada];

                char nome1[50], nome2[50];
                strcpy(nome1, botaoCamadas[botaoCamada.posCamada].nome);
                strcpy(nome2, botaoCamadas[botaoCamada.posCamada - 1].nome);

                camadas[botaoCamada.posCamada] = camadas[botaoCamada.posCamada - 1];
                camadas[botaoCamada.posCamada - 1] = temp;
                
                strcpy(botaoCamadas[botaoCamada.posCamada - 1].nome, nome1);
                strcpy(botaoCamadas[botaoCamada.posCamada].nome, nome2);

                if(camadaAtiva == botaoCamada.posCamada){
                    camadaAtiva--;
                }
                else if(camadaAtiva == botaoCamada.posCamada - 1){
                    camadaAtiva++;
                }
                return 1;
            }
            
        }
    }
    return 0;
}

void gerenciadorCamadas::pintarCamada(int mouseX, int mouseY, unsigned char *RGBA, int tipoPintura, int raio){ // funcao pra fazer os efeitos de pintar
    if(tipoPintura == 1){ // pincel
        for(int i = -raio; i <= raio; i++){
            for(int j = -raio; j <= raio; j++){
                if(i*i + j*j <= raio*raio){
                    int posX = mouseX + i - borda1X;
                    int posY = mouseY + j - borda1Y;
                    int posRGBA = (posY * width + posX) * 4;
                    if(posX >= 0 && posX < width && posY >= 0 && posY < height){
                        camadas[camadaAtiva].camada[posRGBA] = RGBA[0];
                        camadas[camadaAtiva].camada[posRGBA + 1] = RGBA[1];
                        camadas[camadaAtiva].camada[posRGBA + 2] = RGBA[2];
                        camadas[camadaAtiva].camada[posRGBA + 3] = RGBA[3];
                    }
                }
            }
        }
        return;
    }
    else if(tipoPintura == 2){ // spray
        srand(time(NULL) + mouseX + mouseY); 
        
        int numPontos = raio * raio / 2; 
        for(int p = 0; p < numPontos; p++){
            int i, j;
            do{
                i = (rand() % (2 * raio)) - raio;
                j = (rand() % (2 * raio)) - raio;
            }while(i*i + j*j > raio*raio);
            
            if(rand() % 100 > 60){  // fica colocando um valor aleatorio pra ver se vai pintar ou não
                int posX = mouseX + i - borda1X;
                int posY = mouseY + j - borda1Y;
                int posRGBA = (posY * width + posX) * 4;
                if(posX >= 0 && posX < width && posY >= 0 && posY < height){
                    camadas[camadaAtiva].camada[posRGBA] = RGBA[0];
                    camadas[camadaAtiva].camada[posRGBA + 1] = RGBA[1];
                    camadas[camadaAtiva].camada[posRGBA + 2] = RGBA[2];
                    camadas[camadaAtiva].camada[posRGBA + 3] = RGBA[3];
                }
            }
        }
        return;
    }
    else if(tipoPintura == 3){ // marca texto
        int alturaHighlight = raio * 5; 
        int larguraHighlight = 2; 
        
        for(int i = -larguraHighlight; i <= larguraHighlight; i++){
            for(int j = -alturaHighlight; j <= alturaHighlight; j++){  
                int posX = mouseX + i - borda1X;
                int posY = mouseY + j - borda1Y;
                int posRGBA = (posY * width + posX) * 4;
                    
                if(posX >= 0 && posX < width && posY >= 0 && posY < height){
                    if(camadas[camadaAtiva].camada[posRGBA + 3] == 1){
                        camadas[camadaAtiva].camada[posRGBA] = (camadas[camadaAtiva].camada[posRGBA] * 0.7 + RGBA[0] * 0.3); // faz uma interpolacao com o que esta e o marca texto
                        camadas[camadaAtiva].camada[posRGBA + 1] = (camadas[camadaAtiva].camada[posRGBA + 1] * 0.7 + RGBA[1] * 0.3);
                        camadas[camadaAtiva].camada[posRGBA + 2] = (camadas[camadaAtiva].camada[posRGBA + 2] * 0.7 + RGBA[2] * 0.3);
                    } else {
                        camadas[camadaAtiva].camada[posRGBA] = RGBA[0]; // se nao tem alpha, pinta normalmente
                        camadas[camadaAtiva].camada[posRGBA + 1] = RGBA[1];
                        camadas[camadaAtiva].camada[posRGBA + 2] = RGBA[2];
                        camadas[camadaAtiva].camada[posRGBA + 3] = RGBA[3]; 
                    }
                }
                
            }
        }
        return;
    }
    else if(tipoPintura == 4){ // balde (floodfill)
        int inicioX = mouseX - borda1X;
        int inicioY = mouseY - borda1Y;
        
        if(inicioX < 0 || inicioX >= width || inicioY < 0 || inicioY >= height) {
            return;
        }
        
        int inicioRGBA = (inicioY * width + inicioX) * 4;
        unsigned char R = camadas[camadaAtiva].camada[inicioRGBA];
        unsigned char G = camadas[camadaAtiva].camada[inicioRGBA + 1];
        unsigned char B = camadas[camadaAtiva].camada[inicioRGBA + 2];
        unsigned char A = camadas[camadaAtiva].camada[inicioRGBA + 3];
        
        if(R == RGBA[0] && G == RGBA[1] && B == RGBA[2] && A == RGBA[3]) { // se ja esta daquela cor, retorna
            return;
        }
        
        std::vector<std::pair<int, int>> fila;
        fila.push_back(std::make_pair(inicioX, inicioY));
        
        while(!fila.empty()) {
            int x = fila.back().first;
            int y = fila.back().second;
            fila.pop_back();
            
            int pos = (y * width + x) * 4;
            
            if(camadas[camadaAtiva].camada[pos] == R && 
               camadas[camadaAtiva].camada[pos + 1] == G && 
               camadas[camadaAtiva].camada[pos + 2] == B && 
               camadas[camadaAtiva].camada[pos + 3] == A) {
                
                camadas[camadaAtiva].camada[pos] = RGBA[0];
                camadas[camadaAtiva].camada[pos + 1] = RGBA[1];
                camadas[camadaAtiva].camada[pos + 2] = RGBA[2];
                camadas[camadaAtiva].camada[pos + 3] = RGBA[3];
                // adiciona na fila os vizinhos
                if(x > 0) fila.push_back(std::make_pair(x - 1, y));
                if(x < width - 1) fila.push_back(std::make_pair(x + 1, y));
                if(y > 0) fila.push_back(std::make_pair(x, y - 1));
                if(y < height - 1) fila.push_back(std::make_pair(x, y + 1));
            }
        }
    }
    else if(tipoPintura == 5){ // borracha
        for(int i = -raio; i <= raio; i++){
            for(int j = -raio; j <= raio; j++){
                if(i*i + j*j <= raio*raio){
                    int posX = mouseX + i - borda1X;
                    int posY = mouseY + j - borda1Y;
                    int posRGBA = (posY * width + posX) * 4;
                    if(posX >= 0 && posX < width && posY >= 0 && posY < height){ // so coloca o alpha em 0 e seta os outros por padrao
                        camadas[camadaAtiva].camada[posRGBA] = 1;
                        camadas[camadaAtiva].camada[posRGBA + 1] = 1;
                        camadas[camadaAtiva].camada[posRGBA + 2] = 1;
                        camadas[camadaAtiva].camada[posRGBA + 3] = 0;
                    }
                }
            }
        }
    }
}

void gerenciadorCamadas::flipVertical(){ // flip vertical
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height / 2; j++){
            int pos1 = (j * width + i) * 4;
            int pos2 = ((height - j - 1) * width + i) * 4;
            unsigned char temp[4];
            memcpy(temp, &camadas[camadaAtiva].camada[pos1], 4); // mem copy mto badass pra desempenho!
            memcpy(&camadas[camadaAtiva].camada[pos1], &camadas[camadaAtiva].camada[pos2], 4);
            memcpy(&camadas[camadaAtiva].camada[pos2], temp, 4);
        }
    }
}

void gerenciadorCamadas::flipHorizontal(){ // flip horizontal
    for(int i = 0; i < width / 2; i++){
        for(int j = 0; j < height; j++){
            int pos1 = (j * width + i) * 4;
            int pos2 = (j * width + (width - i - 1)) * 4;
            unsigned char temp[4];
            memcpy(temp, &camadas[camadaAtiva].camada[pos1], 4); // mem copy mto badass pra desempenho!
            memcpy(&camadas[camadaAtiva].camada[pos1], &camadas[camadaAtiva].camada[pos2], 4);
            memcpy(&camadas[camadaAtiva].camada[pos2], temp, 4);
        }
    }
}

void gerenciadorCamadas::aplicarTonsDecinza(){ // aplica o padrao de tons de cinza, com os pesos de 0.3, 0.59 e 0.11
    for (int i = 0; i < width * height; i++) {
        unsigned char gray = camadas[camadaAtiva].camada[i * 4] * 0.3 + camadas[camadaAtiva].camada[i * 4 + 1] * 0.59 + camadas[camadaAtiva].camada[i * 4 + 2] * 0.11;
                             
        camadas[camadaAtiva].camada[i * 4] = gray;
        camadas[camadaAtiva].camada[i * 4 + 1] = gray;
        camadas[camadaAtiva].camada[i * 4 + 2] = gray;
    }
}

void gerenciadorCamadas::adicionarBrilho(int valorBrilho){ // add brilho
    for (int i = 0; i < width * height; i++) {
        int r = camadas[camadaAtiva].camada[i * 4] + valorBrilho;
        int g = camadas[camadaAtiva].camada[i * 4 + 1] + valorBrilho;
        int b = camadas[camadaAtiva].camada[i * 4 + 2] + valorBrilho;

        if(r > 255) r = 255;
        if(g > 255) g = 255;
        if(b > 255) b = 255;

        if(r < 0) r = 0;
        if(g < 0) g = 0;
        if(b < 0) b = 0;

        camadas[camadaAtiva].camada[i * 4] = r;
        camadas[camadaAtiva].camada[i * 4 + 1] = g;
        camadas[camadaAtiva].camada[i * 4 + 2] = b;
    }
}

void gerenciadorCamadas::adicionarGama(int valorGama){ // add gama
    float gama = (float)valorGama / 10;

    unsigned char lookupTable[256];
    
    for (int i = 0; i < 256; i++) {
        float normalizado = (float)i / 255;
        float corrigido = pow(normalizado, (float)1 / gama);
        lookupTable[i] = (unsigned char)(corrigido * (float)255 + 0.5);
    }

    for (int i = 0; i < width * height; i++) {
        camadas[camadaAtiva].camada[i * 4] = lookupTable[camadas[camadaAtiva].camada[i * 4]];
        camadas[camadaAtiva].camada[i * 4 + 1] = lookupTable[camadas[camadaAtiva].camada[i * 4 + 1]];
        camadas[camadaAtiva].camada[i * 4 + 2] = lookupTable[camadas[camadaAtiva].camada[i * 4 + 2]];
    }
}