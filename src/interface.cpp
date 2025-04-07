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

#define posBotoesClick 8/10
#define larguraBotoesClick 10
#define alturaBotoesClick 30
#define distanciaEntreBotoesClick 5

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

    clicar.borda1X = inicioMenuLateralX + 10;
    clicar.borda1Y = screenHeight * posBotoesClick;
    clicar.borda2X = clicar.borda1X + 10;
    clicar.borda2Y = clicar.borda1Y + 30;
    clicar.tem_borda = 1;

    pincel.borda1X = clicar.borda2X + 5;
    pincel.borda1Y = screenHeight * posBotoesClick;
    pincel.borda2X = pincel.borda1X + 10;
    pincel.borda2Y = pincel.borda1Y + 30;
    pincel.tem_borda = 1;

    spray.borda1X = pincel.borda2X + 5;
    spray.borda1Y = screenHeight * posBotoesClick;
    spray.borda2X = spray.borda1X + 10;
    spray.borda2Y = spray.borda1Y + 30;
    spray.tem_borda = 1;

    marcaTexto.borda1X = spray.borda2X + 5;
    marcaTexto.borda1Y = screenHeight * posBotoesClick;
    marcaTexto.borda2X = marcaTexto.borda1X + 10;
    marcaTexto.borda2Y = marcaTexto.borda1Y + 30;
    marcaTexto.tem_borda = 1;

    balde.borda1X = marcaTexto.borda2X + 5;
    balde.borda1Y = screenHeight * posBotoesClick;
    balde.borda2X = balde.borda1X + 10;
    balde.borda2Y = balde.borda1Y + 30;
    balde.tem_borda = 1;

    borracha.borda1X = balde.borda2X + 5;
    borracha.borda1Y = screenHeight * posBotoesClick;
    borracha.borda2X = borracha.borda1X + 10;
    borracha.borda2Y = borracha.borda1Y + 30;
    borracha.tem_borda = 1;

    botaoSelecionado = 0;
    raioCor = 10;
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
    renderBotaoClicar();
    renderBotaoPincel();
    renderBotaoSpray();
    renderBotaoMarcaTexto();
    renderBotaoBalde();
    renderBotaoBorracha();

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
    CV::rectFill(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);

    if(botao.tem_borda){
        CV::color(0.9, 0.9, 0.9);
        CV::rect(botao.borda1X, botao.borda1Y, botao.borda2X, botao.borda2Y);
    }

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

void Interface::renderBotaoClicar(){
    renderBotao(clicar);
    CV::text(clicar.borda1X + 5, (clicar.borda1Y + clicar.borda2Y) /2 - 2, "Click");
}

void Interface::renderBotaoPincel(){
    renderBotao(pincel);
    CV::text(pincel.borda1X + 5, (pincel.borda1Y + pincel.borda2Y) /2 - 2, "Pincel");
}

void Interface::renderBotaoSpray(){
    renderBotao(spray);
    CV::text(spray.borda1X + 5, (spray.borda1Y + spray.borda2Y) /2 - 2, "Spray");
}

void Interface::renderBotaoMarcaTexto(){
    renderBotao(marcaTexto);
    CV::text(marcaTexto.borda1X + 5, (marcaTexto.borda1Y + marcaTexto.borda2Y) /2 - 2, "Marca Texto");
}

void Interface::renderBotaoBalde(){
    renderBotao(balde);
    CV::text(balde.borda1X + 5, (balde.borda1Y + balde.borda2Y) /2 - 2, "Balde");
}

void Interface::renderBotaoBorracha(){
    renderBotao(borracha);
    CV::text(borracha.borda1X + 5, (borracha.borda1Y + borracha.borda2Y) /2 - 2, "Borracha");
}

BOTAO Interface::getBotaoAddImagem(){
    return botaoAddImagem;
}

BOTAO Interface::getBotaoClicar(){
    return clicar;
}

BOTAO Interface::getBotaoPincel(){
    return pincel;
}

BOTAO Interface::getBotaoSpray(){
    return spray;
}

BOTAO Interface::getBotaoMarcaTexto(){
    return marcaTexto;
}

BOTAO Interface::getBotaoBalde(){
    return balde;
}

BOTAO Interface::getBotaoBorracha(){
    return borracha;
}

void Interface::carregarNomeArquivos(){
    struct dirent *entry;
    DIR *dp = opendir(".\\Trab1GabrielBaggio\\images");

    if (dp == nullptr)
        printf("Erro ao abrir diretorio das imagens, ajeitar nos diretorios do windows pra ficar certo");
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