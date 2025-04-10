//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "GerenciadorCamadas.h"
#include <string.h>
#include "gl_canvas2d.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

#define MAX_CAMADAS 10

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

void gerenciadorCamadas::carregaCamada(unsigned char *data, int imgWidth, int imgHeight){
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

void gerenciadorCamadas::render(){
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

bool gerenciadorCamadas::verificaMouseCamada(int mouseX, int mouseY){
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

void gerenciadorCamadas::addBotaoCamada(int camadaAtiva, int screenWidth, int screenHeight, int inicioMenuLateralX){
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

void gerenciadorCamadas::renderBotaoSwitch(BotaoSwitch botaoSwitch){
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

void gerenciadorCamadas::renderBotaoCamada(){
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

void gerenciadorCamadas::renderCaixaCamadas(){
    CV::color(0.9, 0.9, 0.9);
    CV::rect(caixaBotoes1X, caixaBotoes1Y, caixaBotoes2X, caixaBotoes2Y);
}

int gerenciadorCamadas::getQntCamadas(){
    return qntCamadas;
}

bool gerenciadorCamadas::verificaBotaoHide(int mouseX, int mouseY){
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

bool gerenciadorCamadas::verificaBotaoAtiva(int mouseX, int mouseY){
    for(BotaoCamadas botaoCamada : botaoCamadas){
        if(mouseX > botaoCamada.borda1X && mouseX < botaoCamada.bordaHideX && mouseY > botaoCamada.borda1Y && mouseY < botaoCamada.borda2Y){
            camadaAtiva = botaoCamada.posCamada;
            return 1;
        }
    }
    return 0;
}

bool gerenciadorCamadas::verificaBotaoCima(int mouseX, int mouseY){
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

bool gerenciadorCamadas::verificaBotaoBaixo(int mouseX, int mouseY){
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

void gerenciadorCamadas::pintarCamada(int mouseX, int mouseY, unsigned char *RGBA, int tipoPintura, int raio){
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
        
        int numPoints = raio * raio / 2; 
        for(int p = 0; p < numPoints; p++){
            int i, j;
            do {
                i = (rand() % (2 * raio)) - raio;
                j = (rand() % (2 * raio)) - raio;
            } while(i*i + j*j > raio*raio);
            
            if(rand() % 100 > 60){ 
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
                if(i >= -larguraHighlight && i <= larguraHighlight && 
                   j >= -alturaHighlight && j <= alturaHighlight) {
                    
                    int posX = mouseX + i - borda1X;
                    int posY = mouseY + j - borda1Y;
                    int posRGBA = (posY * width + posX) * 4;
                    
                    if(posX >= 0 && posX < width && posY >= 0 && posY < height){
                        if(camadas[camadaAtiva].camada[posRGBA + 3] == 1){
                            camadas[camadaAtiva].camada[posRGBA] = (camadas[camadaAtiva].camada[posRGBA] * 0.7 + RGBA[0] * 0.3);
                            camadas[camadaAtiva].camada[posRGBA + 1] = (camadas[camadaAtiva].camada[posRGBA + 1] * 0.7 + RGBA[1] * 0.3);
                            camadas[camadaAtiva].camada[posRGBA + 2] = (camadas[camadaAtiva].camada[posRGBA + 2] * 0.7 + RGBA[2] * 0.3);
                        } else {
                            camadas[camadaAtiva].camada[posRGBA] = RGBA[0];
                            camadas[camadaAtiva].camada[posRGBA + 1] = RGBA[1];
                            camadas[camadaAtiva].camada[posRGBA + 2] = RGBA[2];
                            camadas[camadaAtiva].camada[posRGBA + 3] = RGBA[3]; 
                        }
                    }
                }
            }
        }
        return;
    }
    else if(tipoPintura == 4){ // balde (floodfill)
        int startX = mouseX - borda1X;
        int startY = mouseY - borda1Y;
        
        if(startX < 0 || startX >= width || startY < 0 || startY >= height) {
            return;
        }
        
        int startPos = (startY * width + startX) * 4;
        unsigned char targetR = camadas[camadaAtiva].camada[startPos];
        unsigned char targetG = camadas[camadaAtiva].camada[startPos + 1];
        unsigned char targetB = camadas[camadaAtiva].camada[startPos + 2];
        unsigned char targetA = camadas[camadaAtiva].camada[startPos + 3];
        
        if(targetR == RGBA[0] && targetG == RGBA[1] && targetB == RGBA[2] && targetA == RGBA[3]) {
            return;
        }
        
        std::vector<std::pair<int, int>> queue;
        queue.push_back(std::make_pair(startX, startY));
        
        while(!queue.empty()) {
            int x = queue.back().first;
            int y = queue.back().second;
            queue.pop_back();
            
            int pos = (y * width + x) * 4;
            
            if(camadas[camadaAtiva].camada[pos] == targetR && 
               camadas[camadaAtiva].camada[pos + 1] == targetG && 
               camadas[camadaAtiva].camada[pos + 2] == targetB && 
               camadas[camadaAtiva].camada[pos + 3] == targetA) {
                
                camadas[camadaAtiva].camada[pos] = RGBA[0];
                camadas[camadaAtiva].camada[pos + 1] = RGBA[1];
                camadas[camadaAtiva].camada[pos + 2] = RGBA[2];
                camadas[camadaAtiva].camada[pos + 3] = RGBA[3];
                
                if(x > 0) queue.push_back(std::make_pair(x - 1, y));
                if(x < width - 1) queue.push_back(std::make_pair(x + 1, y));
                if(y > 0) queue.push_back(std::make_pair(x, y - 1));
                if(y < height - 1) queue.push_back(std::make_pair(x, y + 1));
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
                    if(posX >= 0 && posX < width && posY >= 0 && posY < height){
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

void gerenciadorCamadas::flipVertical(){
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

void gerenciadorCamadas::flipHorizontal(){
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

void gerenciadorCamadas::aplicarTonsDecinza(){
    for (int i = 0; i < width * height; i++) {
        unsigned char gray = camadas[camadaAtiva].camada[i * 4] * 0.3 + camadas[camadaAtiva].camada[i * 4 + 1] * 0.59 + camadas[camadaAtiva].camada[i * 4 + 2] * 0.11;
                             
        camadas[camadaAtiva].camada[i * 4] = gray;
        camadas[camadaAtiva].camada[i * 4 + 1] = gray;
        camadas[camadaAtiva].camada[i * 4 + 2] = gray;
    }
}