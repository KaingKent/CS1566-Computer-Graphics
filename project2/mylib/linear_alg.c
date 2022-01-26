#include "linear_alg.h"
#include "stdio.h"
#include "math.h"

void printColVec(vec4 v){//prints the column vector
    printf("[%.4f %.4f %.4f %.4f]\n", v.x, v.y, v.z, v.w);
}

vec4 scalarVecMult(vec4 v, float scalar){//multiplies the column vector by a scalar
    vec4 newVec = {v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar};
    return newVec;
}

vec4 vecAdd(vec4 addend1, vec4 addend2){//adds two column vectors together
    vec4 sum = {addend1.x + addend2.x, addend1.y + addend2.y, addend1.z + addend2.z, addend1.w + addend2.w};
    return sum;
}

vec4 vecSub(vec4 sub1, vec4 sub2){//subtracts two column vectors
    vec4 newVec = {sub1.x - sub2.x, sub1.y - sub2.y, sub1.z - sub2.z, sub1.w - sub2.w};
    return newVec;
}

float magnitudeVec(vec4 v){//finds the magnitude of a column vector
    return sqrtf((v.x*v.x) + (v.y*v.y) + (v.z*v.z) + (v.w*v.w));
}

vec4 normalize(vec4 v){//normalizes a vector by multiplying the vector by its magnitude's reciprical
    vec4 newVec = scalarVecMult(v, (1/magnitudeVec(v)));
    return newVec;
}

float dotProduct(vec4 v1, vec4 v2){//finds the dot product (a scalar) of two column vectors
    return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z) + (v1.w*v2.w); 
}

vec4 crossProduct(vec4 v1, vec4 v2){//finds the cross product of two column vectors
    vec4 product = {(v1.y*v2.z) - (v1.z*v2.y), (v1.z*v2.x) - (v1.x*v2.z), (v1.x*v2.y) - (v1.y*v2.x), 0}; 
    return product;
}

void printMat(mat4 m){//prints a 4x4 
    printf("[%.4f %.4f %.4f %.4f]\n", m.x.x, m.y.x, m.z.x, m.w.x);
    printf("[%.4f %.4f %.4f %.4f]\n", m.x.y, m.y.y, m.z.y, m.w.y);
    printf("[%.4f %.4f %.4f %.4f]\n", m.x.z, m.y.z, m.z.z, m.w.z);
    printf("[%.4f %.4f %.4f %.4f]\n", m.x.w, m.y.w, m.z.w, m.w.w);
}

mat4 scalarMatMult(mat4 m, float scalar){//multiplies the matrix by a scalar
    mat4 newMat = {scalarVecMult(m.x, scalar), scalarVecMult(m.y, scalar),scalarVecMult(m.z, scalar),scalarVecMult(m.w, scalar)};
    return newMat;
}

mat4 matAdd(mat4 addend1, mat4 addend2){//adds two matrices
    mat4 newMat = {vecAdd(addend1.x, addend2.x),vecAdd(addend1.y, addend2.y),vecAdd(addend1.z, addend2.z),vecAdd(addend1.w, addend2.w)};
    return newMat;
}

mat4 matSub(mat4 sub1, mat4 sub2){//subtracts sub1 and sub2
    mat4 newMat = {vecSub(sub1.x, sub2.x),vecSub(sub1.y, sub2.y),vecSub(sub1.z, sub2.z),vecSub(sub1.w, sub2.w)};
    return newMat;
}

mat4 matMult(mat4 m1, mat4 m2){//multiplies two matrices 
    mat4 product;

    product.x.x = (m1.x.x * m2.x.x) + (m1.y.x * m2.x.y) + (m1.z.x * m2.x.z) + (m1.w.x * m2.x.w);
    product.x.y = (m1.x.y * m2.x.x) + (m1.y.y * m2.x.y) + (m1.z.y * m2.x.z) + (m1.w.y * m2.x.w);
    product.x.z = (m1.x.z * m2.x.x) + (m1.y.z * m2.x.y) + (m1.z.z * m2.x.z) + (m1.w.z * m2.x.w);
    product.x.w = (m1.x.w * m2.x.x) + (m1.y.w * m2.x.y) + (m1.z.w * m2.x.z) + (m1.w.w * m2.x.w);
    
    product.y.x = (m1.x.x * m2.y.x) + (m1.y.x * m2.y.y) + (m1.z.x * m2.y.z) + (m1.w.x * m2.y.w);
    product.y.y = (m1.x.y * m2.y.x) + (m1.y.y * m2.y.y) + (m1.z.y * m2.y.z) + (m1.w.y * m2.y.w);
    product.y.z = (m1.x.z * m2.y.x) + (m1.y.z * m2.y.y) + (m1.z.z * m2.y.z) + (m1.w.z * m2.y.w);
    product.y.w = (m1.x.w * m2.y.x) + (m1.y.w * m2.y.y) + (m1.z.w * m2.y.z) + (m1.w.w * m2.y.w);
    
    product.z.x = (m1.x.x * m2.z.x) + (m1.y.x * m2.z.y) + (m1.z.x * m2.z.z) + (m1.w.x * m2.z.w);
    product.z.y = (m1.x.y * m2.z.x) + (m1.y.y * m2.z.y) + (m1.z.y * m2.z.z) + (m1.w.y * m2.z.w);
    product.z.z = (m1.x.z * m2.z.x) + (m1.y.z * m2.z.y) + (m1.z.z * m2.z.z) + (m1.w.z * m2.z.w);
    product.z.w = (m1.x.w * m2.z.x) + (m1.y.w * m2.z.y) + (m1.z.w * m2.z.z) + (m1.w.w * m2.z.w);
    
    product.w.x = (m1.x.x * m2.w.x) + (m1.y.x * m2.w.y) + (m1.z.x * m2.w.z) + (m1.w.x * m2.w.w);
    product.w.y = (m1.x.y * m2.w.x) + (m1.y.y * m2.w.y) + (m1.z.y * m2.w.z) + (m1.w.y * m2.w.w);
    product.w.z = (m1.x.z * m2.w.x) + (m1.y.z * m2.w.y) + (m1.z.z * m2.w.z) + (m1.w.z * m2.w.w);
    product.w.w = (m1.x.w * m2.w.x) + (m1.y.w * m2.w.y) + (m1.z.w * m2.w.z) + (m1.w.w * m2.w.w);

    return product;
}

mat4 transposeMat(mat4 m){// finds the transpose of the matrix
    mat4 transpose;
    transpose.x.x = m.x.x;
    transpose.x.y = m.y.x;
    transpose.x.z = m.z.x;
    transpose.x.w = m.w.x;

    transpose.y.y = m.y.y;
    transpose.y.x = m.x.y;
    transpose.y.z = m.z.y;
    transpose.y.w = m.w.y;

    transpose.z.z = m.z.z;
    transpose.z.x = m.x.z;
    transpose.z.y = m.y.z;
    transpose.z.w = m.w.z;

    transpose.w.w = m.w.w;
    transpose.w.x = m.x.w;
    transpose.w.y = m.y.w;
    transpose.w.z = m.z.w;

    return transpose;
}

vec4 matVecMult(mat4 m, vec4 v){//multiplies a matrix by a column vector

    vec4 newVec;

    newVec.x = (m.x.x * v.x) + (m.y.x * v.y) + (m.z.x * v.z) + (m.w.x * v.w);
    newVec.y = (m.x.y * v.x) + (m.y.y * v.y) + (m.z.y * v.z) + (m.w.y * v.w);
    newVec.z = (m.x.z * v.x) + (m.y.z * v.y) + (m.z.z * v.z) + (m.w.z * v.w);
    newVec.w = (m.x.w * v.x) + (m.y.w * v.y) + (m.z.w * v.z) + (m.w.w * v.w);

    return newVec;
}

mat4 minor(mat4 m){//finds the minor of matrix
    mat4 minor;
    minor.x.x = (m.y.y*m.z.z*m.w.w) + (m.y.z*m.z.w*m.w.y) + (m.y.w*m.z.y*m.w.z) - (m.w.y*m.z.z*m.y.w) - (m.w.z*m.z.w*m.y.y) - (m.w.w*m.z.y*m.y.z);
    minor.x.y = (m.y.x*m.z.z*m.w.w) + (m.y.z*m.z.w*m.w.x) + (m.y.w*m.z.x*m.w.z) - (m.w.x*m.z.z*m.y.w) - (m.w.z*m.z.w*m.y.x) - (m.w.w*m.z.x*m.y.z);
    minor.x.z = (m.y.x*m.z.y*m.w.w) + (m.y.y*m.z.w*m.w.x) + (m.y.w*m.z.x*m.w.y) - (m.w.x*m.z.y*m.y.w) - (m.w.y*m.z.w*m.y.x) - (m.w.w*m.z.x*m.y.y);
    minor.x.w = (m.y.x*m.z.y*m.w.z) + (m.y.y*m.z.z*m.w.x) + (m.y.z*m.z.x*m.w.y) - (m.w.x*m.z.y*m.y.z) - (m.w.y*m.z.z*m.y.x) - (m.w.z*m.z.x*m.y.y);

    minor.y.x = (m.x.y*m.z.z*m.w.w) + (m.x.z*m.z.w*m.w.y) + (m.x.w*m.z.y*m.w.z) - (m.w.y*m.z.z*m.x.w) - (m.w.z*m.z.w*m.x.y) - (m.w.w*m.z.y*m.x.z);
    minor.y.y = (m.x.x*m.z.z*m.w.w) + (m.x.z*m.z.w*m.w.x) + (m.x.w*m.z.x*m.w.z) - (m.w.x*m.z.z*m.x.w) - (m.w.z*m.z.w*m.x.x) - (m.w.w*m.z.x*m.x.z);
    minor.y.z = (m.x.x*m.z.y*m.w.w) + (m.x.y*m.z.w*m.w.x) + (m.x.w*m.z.x*m.w.y) - (m.w.x*m.z.y*m.x.w) - (m.w.y*m.z.w*m.x.x) - (m.w.w*m.z.x*m.x.y);
    minor.y.w = (m.x.x*m.z.y*m.w.z) + (m.x.y*m.z.z*m.w.x) + (m.x.z*m.z.x*m.w.y) - (m.w.x*m.z.y*m.x.z) - (m.w.y*m.z.z*m.x.x) - (m.w.z*m.z.x*m.x.y);

    minor.z.x = (m.x.y*m.y.z*m.w.w) + (m.x.z*m.y.w*m.w.y) + (m.x.w*m.y.y*m.w.z) - (m.w.y*m.y.z*m.x.w) - (m.w.z*m.y.w*m.x.y) - (m.w.w*m.y.y*m.x.z);
    minor.z.y = (m.x.x*m.y.z*m.w.w) + (m.x.z*m.y.w*m.w.x) + (m.x.w*m.y.x*m.w.z) - (m.w.x*m.y.z*m.x.w) - (m.w.z*m.y.w*m.x.x) - (m.w.w*m.y.x*m.x.z);
    minor.z.z = (m.x.x*m.y.y*m.w.w) + (m.x.y*m.y.w*m.w.x) + (m.x.w*m.y.x*m.w.y) - (m.w.x*m.y.y*m.x.w) - (m.w.y*m.y.w*m.x.x) - (m.w.w*m.y.x*m.x.y);
    minor.z.w = (m.x.x*m.y.y*m.w.z) + (m.x.y*m.y.z*m.w.x) + (m.x.z*m.y.x*m.w.y) - (m.w.x*m.y.y*m.x.z) - (m.w.y*m.y.z*m.x.x) - (m.w.z*m.y.x*m.x.y);

    minor.w.x = (m.x.y*m.y.z*m.z.w) + (m.x.z*m.y.w*m.z.y) + (m.x.w*m.y.y*m.z.z) - (m.z.y*m.y.z*m.x.w) - (m.z.z*m.y.w*m.x.y) - (m.z.w*m.y.y*m.x.z);
    minor.w.y = (m.x.x*m.y.z*m.z.w) + (m.x.z*m.y.w*m.z.x) + (m.x.w*m.y.x*m.z.z) - (m.z.x*m.y.z*m.x.w) - (m.z.z*m.y.w*m.x.x) - (m.z.w*m.y.x*m.x.z);
    minor.w.z = (m.x.x*m.y.y*m.z.w) + (m.x.y*m.y.w*m.z.x) + (m.x.w*m.y.x*m.z.y) - (m.z.x*m.y.y*m.x.w) - (m.z.y*m.y.w*m.x.x) - (m.z.w*m.y.x*m.x.y);
    minor.w.w = (m.x.x*m.y.y*m.z.z) + (m.x.y*m.y.z*m.z.x) + (m.x.z*m.y.x*m.z.y) - (m.z.x*m.y.y*m.x.z) - (m.z.y*m.y.z*m.x.x) - (m.z.z*m.y.x*m.x.y);
    
    return minor;
}

mat4 cofactor(mat4 m){//finds the cofactor of the matrix
    mat4 cofactor;
    cofactor.x.x = m.x.x;
    cofactor.x.y = -1*m.x.y;
    cofactor.x.z = m.x.z ;
    cofactor.x.w = -1*m.x.w;

    cofactor.y.x = -1*m.y.x;
    cofactor.y.y = m.y.y;
    cofactor.y.z = -1*m.y.z;
    cofactor.y.w = m.y.w;

    cofactor.z.x = m.z.x;
    cofactor.z.y = -1*m.z.y;
    cofactor.z.z = m.z.z;
    cofactor.z.w = -1*m.z.w;

    cofactor.w.x = -1*m.w.x;
    cofactor.w.y = m.w.y;
    cofactor.w.z = -1*m.w.z;
    cofactor.w.w = m.w.w;

    return cofactor;
}

float determinant(mat4 m, mat4 minor){//finds the determinant of the matrix
    float determinant = (m.x.x*minor.x.x) - (m.y.x*minor.y.x) + (m.z.x*minor.z.x) - (m.w.x*minor.w.x);
    return determinant;
}

mat4 inverseMat(mat4 m){//finds the inverse of the matrix
    mat4 minorM = minor(m);

    mat4 cofactorM = cofactor(minorM);

    mat4 transposeM = transposeMat(cofactorM);

    float determinantF = determinant(m, minorM);

    mat4 inverse = scalarMatMult(transposeM, 1/determinantF);
    return inverse;
}

mat4 translation(float xp, float yp, float zp){//use points to translate 
    mat4 translation;

    translation.x.x = 1;
    translation.x.y = 0;
    translation.x.z = 0;
    translation.x.w = 0;

    translation.y.x = 0;
    translation.y.y = 1;
    translation.y.z = 0;
    translation.y.w = 0;

    translation.z.x = 0;
    translation.z.y = 0;
    translation.z.z = 1;
    translation.z.w = 0;

    translation.w.x = xp;
    translation.w.y = yp;
    translation.w.z = zp;
    translation.w.w = 1;

    return translation;
}

mat4 scaling(float xp, float yp, float zp){//scales according to the x y z
    mat4 scaled;

    scaled.x.x = xp;
    scaled.x.y = 0;
    scaled.x.z = 0;
    scaled.x.w = 0;

    scaled.y.x = 0;
    scaled.y.y = yp;
    scaled.y.z = 0;
    scaled.y.w = 0;

    scaled.z.x = 0;
    scaled.z.y = 0;
    scaled.z.z = zp;
    scaled.z.w = 0;

    scaled.w.x = 0;
    scaled.w.y = 0;
    scaled.w.z = 0;
    scaled.w.w = 1;

    return scaled;
}

mat4 rotateZ(float theta){//rotates along the z-axis
    mat4 rotateZ;

    rotateZ.x.x = cos(theta);
    rotateZ.x.y = sin(theta);
    rotateZ.x.z = 0;
    rotateZ.x.w = 0;

    rotateZ.y.x = -sin(theta);
    rotateZ.y.y = cos(theta);
    rotateZ.y.z = 0;
    rotateZ.y.w = 0;

    rotateZ.z.x = 0;
    rotateZ.z.y = 0;
    rotateZ.z.z = 1;
    rotateZ.z.w = 0;
    
    rotateZ.w.x = 0;
    rotateZ.w.y = 0;
    rotateZ.w.z = 0;
    rotateZ.w.w = 1;

    return rotateZ;
}

mat4 rotateX(float theta){//rotates along the x-axis
    mat4 rotateX;

    rotateX.x.x = 1;
    rotateX.x.y = 0;
    rotateX.x.z = 0;
    rotateX.x.w = 0;

    rotateX.y.x = 0;
    rotateX.y.y = cos(theta);
    rotateX.y.z = sin(theta);
    rotateX.y.w = 0;

    rotateX.z.x = 0;
    rotateX.z.y = -sin(theta);
    rotateX.z.z = cos(theta);
    rotateX.z.w = 0;
    
    rotateX.w.x = 0;
    rotateX.w.y = 0;
    rotateX.w.z = 0;
    rotateX.w.w = 1;

    return rotateX;
}

mat4 rotateY(float theta){//rotates along the y-axis
    mat4 rotateY;

    rotateY.x.x = cos(theta);
    rotateY.x.y = 0;
    rotateY.x.z = -sin(theta);
    rotateY.x.w = 0;

    rotateY.y.x = 0;
    rotateY.y.y = 1;
    rotateY.y.z = 0;
    rotateY.y.w = 0;

    rotateY.z.x = sin(theta);
    rotateY.z.y = 0;
    rotateY.z.z = cos(theta);
    rotateY.z.w = 0;
    
    rotateY.w.x = 0;
    rotateY.w.y = 0;
    rotateY.w.z = 0;
    rotateY.w.w = 1;

    return rotateY;
}

mat4 look_at(float eyex, float eyey, float eyez, float atx, float aty, float atz, float upx, float upy, float upz)
{
    mat4 new;
    mat4 new1;

    vec4 vup = {upx, upy, upz, 0.0};

    vec4 vpn = {eyex - atx, eyey- aty, eyez - atz, 0};
    vec4 n = scalarVecMult(vpn, 1.0/magnitudeVec(vpn));

    vec4 cross1 = crossProduct(vup, n);
    vec4 u = scalarVecMult(cross1, 1.0/magnitudeVec(cross1));

    vec4 cross2 = crossProduct(n, u);
    vec4 v = scalarVecMult(cross2, 1.0/magnitudeVec(cross2));

    //float d = magnitudeVec(vpn);

    new.x.x = u.x;
    new.x.y = v.x;
    new.x.z = n.x;
    new.x.w = 0.0;

    new.y.x = u.y;
    new.y.y = v.y;
    new.y.z = n.y;
    new.y.w = 0.0;

    new.z.x = u.z;
    new.z.y = v.z;
    new.z.z = n.z;
    new.z.w = 0.0;

    new.w.x = 0.0;
    new.w.y = 0.0;
    new.w.z = 0.0;
    new.w.w = 1.0;

    new1 = translation(-eyex, -eyey, -eyez);
    new1= matMult(new, new1);

    return new1;
}

mat4 ortho(float left, float right, float bottom, float top,float near, float far){
    mat4 N;

    N.x.x = 2.0/(right - left);
    N.x.y = 0.0;
    N.x.z = 0.0;
    N.x.w = 0.0;
    
    N.y.x = 0.0;
    N.y.y = 2.0/(top - bottom);
    N.y.z = 0.0;
    N.y.w = 0.0;
    
    N.z.x = 0.0;
    N.z.y = 0.0;
    N.z.z = 2.0/(near - far);
    N.z.w = 0.0;

    N.w.x = -((right + left)/(right - left));
    N.w.y = -((top + bottom)/(top - bottom));
    N.w.z = -((near + far)/(near - far));
    N.w.w = 1.0;

    return N;
}
mat4 frustum(float left, float right, float bottom, float top, float near, float far)
{
    mat4 new;

    new.x.x = (-2.0*near)/(right-left);
    new.x.y = 0.0;
    new.x.z = 0.0;
    new.x.w = 0.0;

    new.y.x = 0.0;
    new.y.y = (-2.0*near)/(top-bottom);
    new.y.z = 0.0;
    new.y.w = 0.0;

    new.z.x = (right+left)/(right-left);
    new.z.y = (top+bottom)/(top-bottom);
    new.z.z = (near+far)/(far-near);
    new.z.w = -1.0;

    new.w.x = 0.0;
    new.w.y = 0.0;
    new.w.z = -(2.0*near*far)/(far-near);
    new.w.w = 0.0;

    return new;
}