#include <iostream>
#include "input.h"
#include "oponente.h"
#include "arena.h"
#include "lutador.h"
#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

extern Arena *arenaSVG;
extern Lutador *lutadorPrincipal;
extern Oponente *lutadorOponente;

void parseCircle(XMLElement *c, int i)
{
  float cx, cy, r;
  Cor cor;
  c->QueryFloatAttribute("cx", &cx);
  c->QueryFloatAttribute("cy", &cy);
  c->QueryFloatAttribute("r", &r);
  Point center = {cx, cy};
  string fill = c->Attribute("fill");

  if (fill == "red")
  {
    cor = {1.0, 0.0, 0.0};
  }
  else if (fill == "blue")
  {
    cor = {0.0, 0.0, 1.0};
  }
  else if (fill == "green")
  {
    cor = {0.0, 1.0, 0.0};
  }

  if (i == 1)
  {
    lutadorPrincipal = new Lutador(center, r, cor, 0);
  }
  else
  {
    lutadorOponente = new Oponente(center, r, cor, 0);
  }
}

void parseRect(XMLElement *ret)
{
  float x, y, width, height;
  Cor cor;
  ret->QueryFloatAttribute("x", &x);
  ret->QueryFloatAttribute("y", &y);
  ret->QueryFloatAttribute("width", &width);
  ret->QueryFloatAttribute("height", &height);
  string fill = ret->Attribute("fill");

  if (fill == "red")
  {
    cor = {1.0, 0.0, 0.0};
  }
  else if (fill == "blue")
  {
    cor = {0.0, 0.0, 1.0};
  }
  else if (fill == "green")
  {
    cor = {0.0, 1.0, 0.0};
  }

  Arena *arena = new Arena(x, y, width, height, cor);
  arenaSVG = arena;
}

void parseSVGFile(string filePath)
{
  XMLDocument arquivoArena;

  arquivoArena.LoadFile(filePath.c_str());

  if (arquivoArena.ErrorID() != 0)
    cout << "Erro no arquivo de entrada config.xml" << endl;
  else
  {
    XMLElement *svg = arquivoArena.FirstChildElement("svg");
    XMLElement *arqSVG = svg->FirstChildElement();

    int i = 0;
    while (arqSVG != NULL)
    {
      string tagType = arqSVG->Value();

      if (tagType == "rect")
      {
        parseRect(arqSVG);
      }
      else if (tagType == "circle")
      {
        parseCircle(arqSVG, i);
        i = i + 1;
      }
      arqSVG = arqSVG->NextSiblingElement();
    }
  }
}
