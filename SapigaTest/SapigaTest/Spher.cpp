#include "Spher.h"


Spher::Spher()
{
}


Spher::~Spher()
{
}

void Spher::draw() {
    float r = 2;

    const int NMax = 30;
    const int MMax = 30;
    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
  //  glBegin(GL_POINTS);
    Vector3 vertices[NMax][MMax];
    Vector3 normals[NMax][MMax];
    int triList[NMax * MMax * 6];
    int idx = 0;

    for (int i = 0; i < NMax; i++) {
        for (int j = 0; j < MMax; j++) {
            float teta = i * 3.1415926 / (float)(NMax-1);
            float fi = j * 3.1415926 * 2.0f / (float)(MMax-1);
            float x = r * sin(teta)*cos(fi);
            float y = r * sin(teta)*sin(fi);
            float z = r * cos(teta);
            vertices[i][j] = Vector3(x, y, z);

            normals[i][j] = Vector3(x, y, z);
            //Skip if a new square on the plane hasn't been formed
            if (i == 0 || j == 0)
                continue;
            //Adds the index of the three vertices in order to make up each of the two tris
            triList[idx++] = (NMax * i + j); //Top right
            triList[idx++] = (NMax * i + j - 1); //Bottom right
            triList[idx++] = (NMax * (i - 1) + j - 1); //Bottom left - First triangle
            triList[idx++] = (NMax * (i - 1) + j - 1); //Bottom left 
            triList[idx++] = (NMax * (i - 1) + j); //Top left
            triList[idx++] = (NMax * i + j); //Top right - Second triangl
        }
    }

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);
    glDrawElements(GL_TRIANGLES, (NMax - 1) * (MMax-1) * 6, GL_UNSIGNED_INT, &triList[0]);
    //glEnd();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glPopMatrix();
}

void Spher::update() {

}