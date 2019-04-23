#ifndef GRAPHICTYPES_H
#define GRAPHICTYPES_H
// Qt headers
#include <QString>
#include <QMatrix4x4>

// Structure to hold visual effect
struct Effect {
    QString image;
};

// Structure to hold model template information
struct ModelTemplate {
    QString id;
    QString image;
    QVector<float>* data;
    QMatrix4x4* trans;
};

// Structure to hold model information
struct Model {
    QString id;
    uint vbo;
    uint textureId;
    int size;
    QMatrix4x4* trans;
};


#endif // GRAPHICTYPES_H
