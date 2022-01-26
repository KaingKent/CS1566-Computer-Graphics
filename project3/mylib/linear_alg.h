typedef struct{
    float x;
    float y;
    float z; 
    float w; 
} vec4;

typedef struct{
    vec4 x;
    vec4 y;
    vec4 z;
    vec4 w;
} mat4;

void printColVec(vec4 v);

vec4 scalarVecMult(vec4 v, float scalar);

vec4 vecAdd(vec4 addend1, vec4 addend2);

vec4 vecSub(vec4 sub1, vec4 sub2);

float magnitudeVec(vec4 v);

vec4 normalize(vec4 v);

float dotProduct(vec4 v1, vec4 v2);

vec4 crossProduct(vec4 v1, vec4 v2);

void printMat(mat4 m);

mat4 scalarMatMult(mat4 m, float scalar);

mat4 matAdd(mat4 addend1, mat4 addend2);

mat4 matSub(mat4 sub1, mat4 sub2);

mat4 matMult(mat4 m1, mat4 m2);

mat4 minor(mat4 m);

mat4 cofactor(mat4 m);

float determinant(mat4 m, mat4 minor);

mat4 inverseMat(mat4 m);

mat4 transposeMat(mat4 m);

vec4 matVecMult(mat4 m, vec4 v);

mat4 identity();

mat4 translation(float x, float y, float z);

mat4 scaling(float x, float y, float z);

mat4 rotateZ(float theta);

mat4 rotateX(float theta);

mat4 rotateY(float theta);

mat4 look_at(float eyex, float eyey, float eyez, 
             float atx, float aty, float atz, 
             float upx, float upy, float upz);

mat4 ortho(float left, float right, float bottom, 
           float top,float near, float far);

mat4 frustum(float left, float right, float bottom, float top, float near, float far);
