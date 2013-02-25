#ifndef LEVELREADER_H
#define LEVELREADER_H


#include <string.h>
#include <list>
#include "math/glVector.hpp"
#include "rendering/Body.hpp"
#include "rendering/BodySet.hpp"
#include "io/Read3DS.hpp"
#include "rendering/TexturedMesh.hpp"
#include "rendering/PowerUp.hpp"
#include "view/RenderFrame.hpp"
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomText>
#include <QFile>
#include <QString>


class LevelReader
{
public:
        /**
         * @brief Ctor
         */
        LevelReader(RenderFrame* rf);

        /**
         * @brief Dtor
         */
        ~LevelReader();

        /**
         * @brief Erstellt Level aus einer XML-Datei
         * @param XML-Datei
         * @return set mit allen bodies
         */
        BodySet* getLevel(QString filename);
private:
        /**
         * @brief parst eine XML-Datei und speichert das Level im Bodyset
         * @param filename XML-Datei
         * @param bodyset Level
         * @return true bei Erfolg, false sonst
         */
        bool parse(QString filename, BodySet* bodyset);

	RenderFrame* m_renderFrame;

};

#endif /* LevelReader.hpp */
