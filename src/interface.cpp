//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Interface.h"
#include <string.h>
#include "gl_canvas2d.h"

Interface::Interface(int screenWidth, int screenHeight)
{
    bordaMenuLateralX = screenWidth * 3 / 4;
    grossuraBordasLateraisNasCamadas = 10;
    inicioMenuLateralX = bordaMenuLateralX + grossuraBordasLateraisNasCamadas;
    tamanhoLadoQuadradosFundo = 10;
    borda1X = grossuraBordasLateraisNasCamadas;
    borda1Y = grossuraBordasLateraisNasCamadas;
    borda2X = bordaMenuLateralX;
    borda2Y = screenHeight - grossuraBordasLateraisNasCamadas;

    submenuArquivos.aberto = 0;
    tamanhoBotaoArquivos = 10;
    qntArquivos = 0;
    carregarNomeArquivos();

    botaoAddImagem.borda1X = inicioMenuLateralX + 10;
    botaoAddImagem.borda1Y = screenHeight * 9 / 10;
    botaoAddImagem.borda2X = screenWidth - 10;
    botaoAddImagem.borda2Y = botaoAddImagem.borda1Y + 30;
    botaoAddImagem.tem_borda = 1;

    botaoSelecionado = 0;
    RGBA[0] = 255;
    RGBA[1] = 0;
    RGBA[2] = 0;
    RGBA[3] = 1;
}

void Interface::render(int screenWidth, int screenHeight){
    renderFundo();
    CV::color(0.3, 0.3, 0.3);
    CV::rectFill(bordaMenuLateralX, 0, bordaMenuLateralX + grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, 0, bordaMenuLateralX, grossuraBordasLateraisNasCamadas);
    CV::rectFill(0, 0, grossuraBordasLateraisNasCamadas, screenHeight);
    CV::rectFill(0, screenHeight - grossuraBordasLateraisNasCamadas, bordaMenuLateralX, screenHeight);
    CV::color(0.5, 0.5, 0.5);
    CV::rectFill(inicioMenuLateralX, 0, screenWidth, screenHeight);
    renderBotaoAdd();
    if(submenuArquivos.aberto){
        renderSubmenuArquivos();
    }
}

int Interface::getBordaMenuLateralX(){
    return bordaMenuLateralX;
}

int Interface::getGrossuraBordasLaterais(){
    return grossuraBordasLateraisNasCamadas;
}

void Interface::renderFundo(){
    int i, j;
    int linha = 0, coluna;
    for(i = borda1Y; i < borda2Y; i += tamanhoLadoQuadradosFundo){
        coluna = 0;
        for(j = borda1X; j < borda2X; j += tamanhoLadoQuadradosFundo){
            if((linha + coluna)%2==0){
                CV::color(0.8, 0.8, 0.8);
            }
            else{
                CV::color(0.4, 0.4, 0.4);
            }
            CV::rectFill(j, i, j + tamanhoLadoQuadradosFundo, i + tamanhoLadoQuadradosFundo);
            coluna++;
        }
        linha++;
    }
}

void Interface::renderBotao(BOTAO botao){
    CV::color(0.3, 0.3, 0.3);
    CV::rect(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);

}

bool Interface::verificaClickBotao(BOTAO botao, int mouseX, int mouseY){
    if(mouseX > botao.borda1X && mouseX < botao.borda2X && mouseY > botao.borda1Y && mouseY < botao.borda2Y){
        return 1;
    }
    return 0;
}

void Interface::renderBotaoAdd(){
    renderBotao(botaoAddImagem);
    CV::text(botaoAddImagem.borda1X + 5, (botaoAddImagem.borda1Y + botaoAddImagem.borda2Y) /2 - 2, "Adicionar uma imagem/camada");
}

BOTAO Interface::getBotaoAddImagem(){
    return botaoAddImagem;
}

void Interface::carregarNomeArquivos(){
    struct dirent *entry;
    DIR *dp = opendir(".\\Trab1GabrielBaggio\\images");

    if (dp == nullptr)
        printf("Erro ao abrir diret�rio das imagens, ajeitar nos diretorios do windows pra ficar certo");
    int cont = 0;
    while ((entry = readdir(dp))){
        if(cont > 1){
            BotaoArquivo novoBotao;
            novoBotao.deltaY = tamanhoBotaoArquivos * qntArquivos;
            novoBotao.nome = entry->d_name;
            botaoArquivos.push_back(novoBotao);
            qntArquivos++;
        }
        cont++;
    }

    closedir(dp);
}

void Interface::renderSubmenuArquivos(){
    int i = 0;
    CV::color(0.2, 0.2, 0.2);
    CV::rectFill(submenuArquivos.borda1X, submenuArquivos.borda1Y, submenuArquivos.borda2X, submenuArquivos.borda2Y);
    CV::color(1, 1, 1);
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        CV::text(submenuArquivos.borda1X, submenuArquivos.borda1Y + botaoArquivo.deltaY, botaoArquivo.nome.c_str());
        i++;
    }
}

void Interface::setAbertoSubmenuArquivos(bool aberto, int mouseX, int mouseY){
    submenuArquivos.aberto = aberto;
    submenuArquivos.borda1X = mouseX;
    submenuArquivos.borda1Y = mouseY - qntArquivos * 10;
    submenuArquivos.borda2X = mouseX + 150;
    submenuArquivos.borda2Y = mouseY;
}

bool Interface::getAbertoSubmenuArquivos(){
    return submenuArquivos.aberto;
}

Submenu Interface::getSubmenuArquivos(){
    return submenuArquivos;
}

bool Interface::verificaClickSubmenu(Submenu submenu, int mouseX, int mouseY){
    if(mouseX > submenu.borda1X && mouseX < submenu.borda2X && mouseY > submenu.borda1Y && mouseY < submenu.borda2Y){
        return 1;
    }
    return 0;
}

std::string Interface::verificaArquivoParaAbrir(int mouseX, int mouseY){
    int i = 0;
    for(BotaoArquivo botaoArquivo : botaoArquivos){
        if(mouseX > submenuArquivos.borda1X - 2 && mouseX < submenuArquivos.borda2X + 2 && mouseY > submenuArquivos.borda1Y + botaoArquivo.deltaY - 2 && mouseY < submenuArquivos.borda1Y + botaoArquivo.deltaY + tamanhoBotaoArquivos + 2){
            return botaoArquivo.nome;
        }
    }
    return botaoArquivos[0].nome;
}

int Interface::getBotaoSelecionado(){
    return botaoSelecionado;
}

unsigned char *Interface::getRGBA(){
    return RGBA;
}