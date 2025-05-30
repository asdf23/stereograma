#ifndef MODEL3D_H
#define MODEL3D_H

#include <QVector>
#include <QVector3D>


class Model3D
{
public:
    Model3D();
    ~Model3D();
    void LoadObj(const QString & filename);
    void LoadPly(const QString & filename);
    void DrawGL(bool color);
    unsigned int numPoints(){return m_nPoints;}
    const float * pointsData(){return m_points;}
    unsigned int numTriangles(){return m_nTriangles;}
    const unsigned int * trianglesData(){return m_triangles;}
private:
    void normalize();
    float *m_points;
    unsigned char *m_colors;
    unsigned int *m_triangles;
    unsigned int m_nPoints,m_nTriangles;
};

#endif // MODEL3D_H
