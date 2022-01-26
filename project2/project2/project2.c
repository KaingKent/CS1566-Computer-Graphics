/*
 * project 2
 *
 * 
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include "math.h"
#include <time.h>

#include "../mylib/initShader.h"
#include "../mylib/linear_alg.h"

#define BUFFER_OFFSET(offset) ((GLvoid *)(offset))

#define num_triangles 72 //can set the number of triangles for the entire cone
int num_vertices = 3 * num_triangles;
vec4 cone[num_triangles * 3];
vec4 color[num_triangles * 3];

#define num_triangles_spring 10000
int num_vertices_spring = 3 * num_triangles_spring;
vec4 spring[300000];
vec4 spring_color[num_triangles_spring * 3];

#define num_triangles_tube 60
int num_vertices_tube = num_triangles_tube * 27;
vec4 tube[num_triangles_tube * 27];
vec4 tube_color[num_triangles_tube * 27];

#define num_triangles_maze 15000
int num_vertices_maze = num_triangles_maze * 27;
vec4 maze[num_triangles_maze * 27];
vec4 maze_color[num_triangles_maze * 27];

GLuint ctm_location;
mat4 ctm = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint model_view_location;
mat4 model_view = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

GLuint projection_location;
mat4 projection = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
vec4 cubec[36];
vec4 cube[36] = {{0.0, 0.0, 0.0, 1.0},
                 {1.0, 1.0, 0.0, 1.0},
                 {0.0, 1.0, 0.0, 1.0},
                 {0.0, 0.0, 0.0, 1.0},
                 {1.0, 0.0, 0.0, 1.0},
                 {1.0, 1.0, 0.0, 1.0}, //front face
                 {0.0, 1.0, 0.0, 1.0},
                 {1.0, 1.0, -1.0, 1.0}, // set negatives to 1 if not work
                 {0.0, 1.0, -1.0, 1.0},
                 {0.0, 1.0, 0.0, 1.0},
                 {1.0, 1.0, 0.0, 1.0},
                 {1.0, 1.0, -1.0, 1.0}, //top face
                 {1.0, 0.0, 0.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0},
                 {1.0, 1.0, 0.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0},
                 {1.0, 1.0, -1.0, 1.0},
                 {1.0, 1.0, 0.0, 1.0}, //right face
                 {0.0, 0.0, 0.0, 1.0},
                 {0.0, 1.0, 0.0, 1.0},
                 {0.0, 0.0, -1.0, 1.0},
                 {0.0, 0.0, -1.0, 1.0},
                 {0.0, 1.0, 0.0, 1.0},
                 {0.0, 1.0, -1.0, 1.0}, //left face
                 {0.0, 0.0, 0.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0},
                 {1.0, 0.0, 0.0, 1.0},
                 {0.0, 0.0, 0.0, 1.0},
                 {0.0, 0.0, -1.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0}, //bottom face
                 {0.0, 0.0, -1.0, 1.0},
                 {0.0, 1.0, -1.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0},
                 {0.0, 1.0, -1.0, 1.0},
                 {1.0, 1.0, -1.0, 1.0},
                 {1.0, 0.0, -1.0, 1.0}}; //back face

float x_prev = 600;
float y_prev = 600;
float z_prev = 600;

typedef struct
{
    int visited;
    int north;
    int east;
    int south;
    int west;
} cell;

cell cells[8][8];
int startX;
int startY;
int walls = 0;

typedef struct
{
    GLfloat x;
    GLfloat y;
} vec2;

vec2 tex_coords[64*36*8+1];

vec2* tex_coord()
{
    for(int i= 0; i < 64*6*2; i++)
    {
            int offset = i*6;
            tex_coords[offset].x = 0.5;
            tex_coords[offset].y = 0.5;
            tex_coords[offset+1].x=1.0;
            tex_coords[offset+1].y=0.5;
            tex_coords[offset+2].x=0.5;
            tex_coords[offset+2].y=0.0;
            tex_coords[offset+3].x=0.5;
            tex_coords[offset+3].y=0.5;
            tex_coords[offset+4].x=1.0;
            tex_coords[offset+4].y=0.5;
            tex_coords[offset+5].x=1.0;
            tex_coords[offset+5].y=0.0;
    }
    
    for(int i= 64*6*2; i < 2304-(36); i++)
    {
            int offset = i*6;
            
            tex_coords[offset].x = 0.0;
            tex_coords[offset].y = 0.4;
            tex_coords[offset+1].x=0.4;
            tex_coords[offset+1].y=0.4;
            tex_coords[offset+2].x=0.4;
            tex_coords[offset+2].y=0.0;
            tex_coords[offset+3].x=0.0;
            tex_coords[offset+3].y=0.4;
            tex_coords[offset+4].x=0.4;
            tex_coords[offset+4].y=0.0;
            tex_coords[offset+5].x=0.0;
            tex_coords[offset+5].y=0.0;
    }
    
    for(int i= 2304-(36); i < 2304; i++)
    {
            int offset = i*6;
            tex_coords[offset].x = 0.0;
            tex_coords[offset].y = 1.0;
            tex_coords[offset+1].x=0.5;
            tex_coords[offset+1].y=0.5;
            tex_coords[offset+2].x=0.0;
            tex_coords[offset+2].y=0.5;
            tex_coords[offset+3].x=0.0;
            tex_coords[offset+3].y=1.0;
            tex_coords[offset+4].x=0.5;
            tex_coords[offset+4].y=0.5;
            tex_coords[offset+5].x=0.0;
            tex_coords[offset+5].y=0.5;
    }
    
    return tex_coords;
}

int randomNum(int min, int max)
{

    return (rand() % (max - min + 1)) + min;
}

void removeWall(int x, int y){

    if((x == 0 && y == 0)){

        
        int rf = randomNum(0,1);

        cells[x][y].west = 0;
        

        rf = randomNum(0,1);
        if(rf == 0){
          
            cells[x][y].east = 0;
            cells[x][y+1].west = 0;
        }else if(rf == 1){

            cells[x][y].south = 0;
            cells[x+1][y].north = 0;
        }

    }else if(x == 7 && y == 7){
        int rf = randomNum(0,1);

        cells[x][y].east = 0;
        

        rf = randomNum(0,1);
        if(rf == 0){

            cells[x][y].north = 0;
            cells[x-1][y].south = 0;
        }else if(rf == 1){

            cells[x][y].west = 0;
            cells[x][y-1].east = 0;
        }
    }else if(x == 0 && y > 0){
        int d = 0;
        while(d == 0){
            int r2 = randomNum(0,2);
       
        if(r2 == 0){
            if(cells[x][y].east != 0 && cells[x][y+1].west != 0){
                cells[x][y].east = 0;
                cells[x][y+1].west = 0;
                d = 1;
            }
            
        }else if(r2 == 1){
            if(cells[x][y].west != 0 && cells[x][y-1].east != 0){
                cells[x][y].west = 0;
                cells[x][y-1].east = 0;
                d = 1;
            }
            
        }else if(r2 == 2){
            if(cells[x][y].south != 0 && cells[x+1][y].north != 0){
                cells[x][y].south = 0;
                cells[x+1][y].north = 0;
                d = 1;
            }
            
        }
        }
        
    }else if(y == 0 && x > 0){
        int q = 0;
        while(q == 0){
            int r3 = randomNum(0,2);
            //printf("%d\n", r3);
            if(r3 == 0){
                if(cells[x][y].east != 0 &&  cells[x][y+1].west != 0){
                    cells[x][y].east = 0;
                    cells[x][y+1].west = 0;
                    q = 1;
                }
                
            }else if(r3 == 1){
                if(cells[x][y].north != 0 && cells[x-1][y].south != 0){
                    cells[x][y].north = 0;
                    cells[x-1][y].south = 0;
                    q =1;
                }
                
            }else if(r3 == 2){
                if(cells[x][y].south != 0 && cells[x+1][y].north != 0){
                    cells[x][y].south = 0;
                    cells[x+1][y].north = 0;
                    q= 1;
                }
                
            }
        }
        
    }else if(x == 7){
        int f = 0;
        while(f == 0){
            int r4 = randomNum(0,2);

            if(r4 == 0){
                if(cells[x][y].east != 0 && cells[x][y+1].west != 0){
                    cells[x][y].east = 0;
                    cells[x][y+1].west = 0;
                    f= 1;
                }
                
            }else if(r4 == 1){
                if(cells[x][y].west != 0 && cells[x][y-1].east != 0){
                    cells[x][y].west = 0;
                    cells[x][y-1].east = 0;
                    f = 1;
                }
                
            }else if(r4 == 2){
               if(cells[x][y].north != 0 && cells[x-1][y].south != 0){
                    cells[x][y].north = 0;
                    cells[x-1][y].south = 0;
                    f = 1;
                }
                
            }
     
        }
       
    }else if(y == 7){
        int g = 0;
        while(g == 0){
            int r5 = randomNum(0,2);

            if(r5 == 0){
                if(cells[x][y].south != 0 && cells[x+1][y].north != 0){
                    cells[x][y].south = 0;
                    cells[x+1][y].north = 0;
                    g = 1;
                }
            }else if(r5 == 1){
                 if(cells[x][y].west != 0 && cells[x][y-1].east != 0){
                    cells[x][y].west = 0;
                    cells[x][y-1].east = 0;
                    g = 1;
                }
            }else if(r5 == 2){
               if(cells[x][y].north != 0 && cells[x-1][y].south != 0){
                    cells[x][y].north = 0;
                    cells[x-1][y].south = 0;
                    g = 1;
                }
            }
        }
        
     
    }else{
        int n = 0;
        while(n == 0){
            int r = randomNum(0,3);
            if(r == 0){
                if(cells[x][y].north != 0 && cells[x-1][y].south != 0){
                    cells[x][y].north = 0;
                    cells[x-1][y].south = 0;
                    n = 1;
                }
            }else if(r == 1){
                if(cells[x][y].west != 0 && cells[x][y-1].east != 0){
                    cells[x][y].west = 0;
                    cells[x][y-1].east = 0;
                    n = 1;
                }
            }else if(r == 2){
                if(cells[x][y].south != 0 && cells[x+1][y].north != 0){
                    cells[x][y].south = 0;
                     cells[x+1][y].north = 0;
                    n = 1;
                }
                
            }else if(r == 3){
                if(cells[x][y].east != 0 && cells[x][y+1].west != 0){
                    cells[x][y].east = 0;
                    cells[x][y+1].west = 0;
                    n = 1;
                }
                
            }
        }

        
    }
    
    
}

void start()
{
    startX = randomNum(0, 7);
    startY = randomNum(0, 7);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cells[i][j].visited = 0;
            cells[i][j].north = 1;
            cells[i][j].east = 1;
            cells[i][j].south = 1;
            cells[i][j].west = 1;
        }
    }

    removeWall(0,0);
    removeWall(7,7);
}

int visited()
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (cells[i][j].visited == 0)
            {
                return -1;
            }
        }
    }
    return 0;
}
int p = 0;

void generateMaze(int x, int y){
    //printf("yeet");
    int b = 0;
    if((x == 0 && y == 0) || (x == 7 && y == 7)){
        b = 1;
    }
    
    if(visited() == 0 || p == 150){
        return;
    }
    p++;
    
    if(x > 0 && cells[x-1][y].visited == 0){
        cells[x][y].visited = 1;
        //remove wall
        if(b == 0){
            removeWall(x,y);
        }
        
        generateMaze(x-1, y);
            
        //cells[x-1][y].visited = 0;
    }

    if(x < 7 && cells[x+1][y].visited == 0){
        cells[x][y].visited = 1;
        //remove wall
        
        if(b == 0){
            removeWall(x,y);
        }
        generateMaze(x+1, y);
            
        //cells[x-1][y].visited = 0;
    }

    if(y > 0 && cells[x][y-1].visited == 0){
        cells[x][y].visited = 1;
        //remove wall
       if(b == 0){
            removeWall(x,y);
        }
        generateMaze(x, y-1);
            
        //cells[x-1][y].visited = 0;
    }

    if(y < 7 && cells[x][y+1].visited == 0){
        cells[x][y].visited = 1;
        //remove wall
       if(b == 0){
            removeWall(x,y);
        }
        generateMaze(x, y+1);
            
        //cells[x-1][y].visited = 0;
    }

}


void consoleMaze()
{
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (cells[i][j].north == 1)
            {
                printf("+---+");
            }
            else
            {
                printf("+   +");
            }
        }
        printf("\n");

        for (int j = 0; j < 8; j++)
        {
            if (cells[i][j].west == 1)
            {
                printf("|   ");
                if (cells[i][j].east == 1)
                {
                    printf("|");
                }
                else
                {
                    printf(" ");
                }
            }
            else
            {
                printf("    ");
                if (cells[i][j].east == 1)
                {
                    printf("|");
                }
                else
                {
                    printf(" ");
                }
            }
        }
        printf("\n");

        for (int j = 0; j < 8; j++)
        {
            if (cells[i][j].south == 1)
            {
                printf("+---+");
            }
            else
            {
                printf("+   +");
            }
        }
        printf("\n");
    }
}

void makemaze(){
    int index = 0;
    int tex = 0;
 	
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (cells[i][j].north == 1) {

                    mat4 ps2 = scaling(.25, 1.15, .25);
                    mat4 t2 = translation((j * 1)+ 1 , 0, i * 1 -1);
                    mat4 p2 = matMult(t2,ps2);
		    	for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.5;
	    			tex_coords[offset].y = 0.5;
	    			tex_coords[offset+1].x=1.0;
	    			tex_coords[offset+1].y=0.5;
	    			tex_coords[offset+2].x=0.5;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=1.0;
	    			tex_coords[offset+3].y=0.0;
	    			tex_coords[offset+4].x=0.5;
	    			tex_coords[offset+4].y=0.5;
	    			tex_coords[offset+5].x=1.0;	
	    			tex_coords[offset+5].y=0.5;
		    	}
		    	tex+=6; 
                  	for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p2, cube[e]);
                        
                        index++;
                    }
                    
                }
                
                if (cells[i][j].south == 1) {

                    mat4 ps2 = scaling(.25, 1.15, .25);
                    mat4 t2 = translation((j * 1)+ 1 , 0, i * 1);
                    mat4 p2 = matMult(t2,ps2);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.5;
	    			tex_coords[offset].y = 0.5;
	    			tex_coords[offset+1].x=1.0;
	    			tex_coords[offset+1].y=0.5;
	    			tex_coords[offset+2].x=0.5;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=1.0;
	    			tex_coords[offset+3].y=0.0;
	    			tex_coords[offset+4].x=0.5;
	    			tex_coords[offset+4].y=0.5;
	    			tex_coords[offset+5].x=1.0;
	    			tex_coords[offset+5].y=0.5;
		    	}
		    	tex+=6; 
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p2, cube[e]);
                        index++;
                    }
                }
                
                if (cells[i][j].east == 1) {

                    mat4 ps2 = scaling(.25, 1.15, .25);
                    mat4 t2 = translation((j * 1)+ 1 , 0, i * 1-1);
                    mat4 p2 = matMult(t2,ps2);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.5;
	    			tex_coords[offset].y = 0.5;
	    			tex_coords[offset+1].x=1.0;
	    			tex_coords[offset+1].y=0.5;
	    			tex_coords[offset+2].x=0.5;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=1.0;
	    			tex_coords[offset+3].y=0.0;
	    			tex_coords[offset+4].x=0.5;
	    			tex_coords[offset+4].y=0.5;
	    			tex_coords[offset+5].x=1.0;
	    			tex_coords[offset+5].y=0.5;
		    	}
		    	tex+=6; 
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p2, cube[e]);
                        index++;
                    }
 
                }
                
                if (cells[i][j].west == 1) {

                    mat4 ps2 = scaling(.25, 1.15, .25);
                    mat4 t2 = translation((j * 1) , 0, i * 1-1);
                    mat4 p2 = matMult(t2,ps2);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.5;
	    			tex_coords[offset].y = 0.5;
	    			tex_coords[offset+1].x=1.0;
	    			tex_coords[offset+1].y=0.5;
	    			tex_coords[offset+2].x=0.5;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=1.0;
	    			tex_coords[offset+3].y=0.0;
	    			tex_coords[offset+4].x=0.5;
	    			tex_coords[offset+4].y=0.5;
	    			tex_coords[offset+5].x=1.0;
	    			tex_coords[offset+5].y=0.5;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p2, cube[e]);
                        index++;
                    }
    
                }
                
            }
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (cells[i][j].north == 1) {
                    mat4 s = scaling(1, 1, 0.15);
                    mat4 t = translation((j * 1) , 0, i * 1 - 1.05);
                    mat4 x = matMult(t, s);

                    mat4 ps = scaling(.25, 1.15, .25);
                    mat4 t3 = translation((j * 1) , 0, i * 1 - 1);
                    mat4 p = matMult(t3,ps);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p, cube[e]);
                        index++;
                    }
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(x, cube[e]);
                        index++;
                    }
                }
                
                if (cells[i][j].south == 1) {
                    mat4 s = scaling(1, 1, 0.15);
                    mat4 t = translation((j * 1), 0, i * 1 - .05);
                    mat4 x = matMult(t, s);

                    mat4 ps = scaling(.25, 1.15, .25);
                    mat4 t3 = translation((j * 1), 0, i * 1);
                    mat4 p = matMult(t3,ps);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p, cube[e]);
                        index++;
                    }
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(x, cube[e]);
                        index++;
                    }
                }
                
                if (cells[i][j].east == 1) {

                    mat4 s = scaling(0.15, 1, 1);
                    mat4 t = translation(j * 1 + 1.05, 0, (i * 1));
                    mat4 x = matMult(t, s);

                    mat4 ps = scaling(.25, 1.15, .25);

                    mat4 t3 = translation(j * 1 + 1, 0, (i * 1));
                    mat4 p = matMult(t3,ps);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p, cube[e]);
                        index++;
                    }
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(x, cube[e]);
                        index++;
                    }
                }
                
                if (cells[i][j].west == 1) {

                    mat4 s = scaling(0.15, 1, 1);
                    mat4 t = translation(j * 1  + .05 , 0, (i * 1));
                    mat4 x = matMult(t, s);

                    mat4 ps = scaling(.25, 1.15, .25);
                    mat4 t3 = translation(j * 1, 0, (i * 1));
                    mat4 p = matMult(t3,ps);
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(p, cube[e]);
                        index++;
                    }
			for(int l = tex; l < tex+6; l++)
		    	{
		    		int offset = l*6;
		    		tex_coords[offset].x = 0.0;
	    			tex_coords[offset].y = 0.4;
	    			tex_coords[offset+1].x=0.4;
	    			tex_coords[offset+1].y=0.4;
	    			tex_coords[offset+2].x=0.4;
	    			tex_coords[offset+2].y=0.0;
	    			tex_coords[offset+3].x=0.0;
	    			tex_coords[offset+3].y=0.4;
	    			tex_coords[offset+4].x=0.4;
	    			tex_coords[offset+4].y=0.0;
	    			tex_coords[offset+5].x=0.0;
	    			tex_coords[offset+5].y=0.0;
		    	}
		    	tex+=6;
                    for(int e = 0; e < 36; e++){
                        maze[index] = matVecMult(x, cube[e]);
                        index++;
                    }
                }
                
            }
        }
    	mat4 background = scaling(12.5, .25, 12);
    	mat4 t4 = translation(-2, -.1, 9);
    	mat4 p4 = matMult(t4, background);
    	
    	for(int l = tex; l < tex+6; l++)
	{
		int offset = l*6;
		tex_coords[offset].x = 0.0;
	    	tex_coords[offset].y = 1.0;
	    	tex_coords[offset+1].x=0.5;
	    	tex_coords[offset+1].y=0.5;
	    	tex_coords[offset+2].x=0.0;
	    	tex_coords[offset+2].y=0.5;
	    	tex_coords[offset+3].x=0.0;
	    	tex_coords[offset+3].y=1.0;
	    	tex_coords[offset+4].x=0.5;
	    	tex_coords[offset+4].y=0.5;
	    	tex_coords[offset+5].x=0.0;
	    	tex_coords[offset+5].y=0.5;
	}
	tex+=6;
    	
    	for(int e = 0; e < 36; e++){
		maze[index] = matVecMult(p4, cube[e]);
		index++; 
		}
}

void color_maze()
{
    for (int i = 0; i < 135000; i++)
    {
        int offset = i * 3;

        float tri_color1 = (float)rand() / RAND_MAX; //generates a random float from 0-1
        float tri_color2 = (float)rand() / RAND_MAX;
        float tri_color3 = (float)rand() / RAND_MAX;

        maze_color[offset].x = tri_color1;
        maze_color[offset].y = tri_color2;
        maze_color[offset].z = tri_color3;
        maze_color[offset].w = 1;

        maze_color[offset + 1].x = tri_color1;
        maze_color[offset + 1].y = tri_color2;
        maze_color[offset + 1].z = tri_color3;
        maze_color[offset + 1].w = 1;

        maze_color[offset + 2].x = tri_color1;
        maze_color[offset + 2].y = tri_color2;
        maze_color[offset + 2].z = tri_color3;
        maze_color[offset + 2].w = 1;
    }
}

float t = 135;
float t1 = 4;
float t2 = 0;
float t3 = -1;
float t5 = 3;
int starting = 0;
int top = 0;
int s = 0;

//look_at(4,1,3,4,0,3,0,0,-1)
//start then go to 4 1 8

void idle(void)
{

    //model_view = matMult(look_at(0,1,0,0,0,0,0,0,-1),model_view);
    if (top == 1)
    {
        if (t5 > 4)
        {
            top = 0;
            starting = 1;
        }

        //p2 = vecAdd(scalarVecMult(v, alpha),p1);
        model_view = look_at(t1, 1, t5, 4, 0, 3, 0, t2, t3);
        //glutPostRedisplay();
        t5 += 0.004;
        t1 -= 0.004;
        t3 += 0.004;
        t2 += 0.004;
    }

    if (starting == 1)
    {
        if (t > 495)
        {
            starting = 0;
            s = 1;
        }
        float x = 4 + cos(t * (M_PI / 180));
        float z = 3 + sin(t * (M_PI / 180));
        model_view = look_at(x, 1, z, 4, 0, 3, 0, t2, t3);

        t += 0.4;

    }

    if(s == 1){

    }
    glutPostRedisplay();
}

void init(void)
{

    int width = 800;
    int height = 800;
    GLubyte my_texels[width][height][3];
    
    FILE *fp = fopen("p2texture04.raw", "r");
    int return_value = fread(my_texels, width * height *3, 1, fp);
    fclose(fp);

    
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
        glUseProgram(program);
        
        GLuint mytex[1];
        glGenTextures(1, mytex);
        glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    
    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);
    
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(maze) + sizeof(maze_color) + sizeof(tex_coords), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(maze), maze);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(maze), sizeof(maze_color), maze_color);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(maze) + sizeof(maze_color), sizeof(tex_coords), tex_coords);

        GLuint vPosition = glGetAttribLocation(program, "vPosition");
        glEnableVertexAttribArray(vPosition);
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        GLuint vColor = glGetAttribLocation(program, "vColor");
        glEnableVertexAttribArray(vColor);
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(maze));
        
        GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
        glEnableVertexAttribArray(vTexCoord);
        glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0 + (sizeof(maze) + sizeof(maze_color)));

        GLuint texture_location = glGetUniformLocation(program, "texture");
        glUniform1i(texture_location, 0);

        ctm_location = glGetUniformLocation(program, "ctm");
        model_view_location = glGetUniformLocation(program, "model_view");
        projection_location = glGetUniformLocation(program, "projection_matrix");
    
    glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glDepthRange(1,0);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_LINE);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&ctm);
    glUniformMatrix4fv(model_view_location, 1, GL_FALSE, (GLfloat *)&model_view);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, (GLfloat *)&projection);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices_maze);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if (key == 'q')
    {
        glutLeaveMainLoop();
    }
    else if (key == 's')
    {
        top = 1;
    }

    //glutPostRedisplay();
}
//takes the pixel x and turns it into actual coordinates based on a radius of 1
float pixel_to_coordX(int x)
{
    float holder = 0;

    if (x >= 256)
    {
        holder = (x - 255) / 256.0;
    }
    else if (x < 256)
    {
        holder = (x - 256) / 256.0;
    }

    return holder;
}

//takes the pixel y and turns it into actual coordinates based on a radius of 1
float pixel_to_coordY(int y)
{
    float holder = 0;

    if (y <= 256)
    {
        holder = -(y - 256) / 256.0;
    }
    else if (y > 256)
    {
        holder = -(y - 255) / 256.0;
    }
    return holder;
}

void mouse(int button, int state, int x, int y)
{

    if (button == 3)
    {
        ctm = matMult(scaling(1.02, 1.02, 1.02), ctm); //zoom in
    }
    if (button == 4)
    {
        ctm = matMult(scaling(1 / 1.02, 1 / 1.02, 1 / 1.02), ctm); //zoom out
    }
    if (button == GLUT_LEFT_BUTTON)
    {

        /*takes the pixel x and y and turns them into actual coordinates 
          assuming that the middle of the screen to the edge has a radius of one
          it does this when left click is pressed and released so that the rotation
          is seamless when you stop and start from a different point */
        x_prev = pixel_to_coordX(x);
        y_prev = pixel_to_coordY(y);

        //calculates the imaginary z coord using the formula 1 = sqrt(x^2 + y^2 + z^2)
        z_prev = sqrt(1 - (x_prev * x_prev) - (y_prev * y_prev));
    }

    glutPostRedisplay();
}

void motion(int x, int y)
{

    float x_coord = 0;
    float y_coord = 0;
    float z_coord = 0;

    //takes the pixel x and y and turns them into actual coordinates
    //assuming that the middle of the screen to the edge has a radius of one
    x_coord = pixel_to_coordX(x);
    y_coord = pixel_to_coordY(y);

    //calculates the imaginary z coord using the formula 1 = sqrt(x^2 + y^2 + z^2)
    z_coord = sqrt(1 - (x_coord * x_coord) - (y_coord * y_coord));

    //the two points turned into vectors
    //point - the origin{0,0,0,1}
    vec4 p1 = {x_prev, y_prev, z_prev, 0};
    vec4 p2 = {x_coord, y_coord, z_coord, 0};

    //uses the dot product of the vectors to calculate the angle
    float theta = acos(dotProduct(p2, p1) / (magnitudeVec(p1) * magnitudeVec(p2)));

    //if theta is NaN -> outside the 1 radius glass ball, dont rotate
    if (theta == theta)
    {
        //process of deriving the rotation matrix
        //used example in the "Geometric Objects and Transformations 05" slides as reference

        //calculate the about vector
        vec4 about = crossProduct(p1, p2);
        float m = magnitudeVec(about);
        vec4 v = {about.x / m, about.y / m, about.z / m, 0};

        float d = sqrt((v.y * v.y) + (v.z * v.z));

        mat4 rotatex = rotateX(0);
        rotatex.y.y = v.z / d;
        rotatex.y.z = -(v.y) / d;
        rotatex.z.y = (v.y) / d;
        rotatex.z.z = v.z / d;

        mat4 rotatex_neg = transposeMat(rotatex);

        mat4 rotatey_neg = rotateY(0);
        rotatey_neg.x.x = d;
        rotatey_neg.x.z = -v.x;
        rotatey_neg.z.x = v.x;
        rotatey_neg.z.z = d;

        mat4 rotatey = transposeMat(rotatey_neg);

        mat4 m1 = matMult(rotatey, rotatex_neg);
        mat4 m2 = matMult(rotateZ(theta), m1);
        mat4 m3 = matMult(rotatey_neg, m2);
        mat4 r = matMult(rotatex, m3);

        ctm = matMult(r, ctm);
    }

    //saves the coords to calculate the new theta next
    x_prev = x_coord;
    y_prev = y_coord;
    z_prev = z_coord;

    glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Project 2");
    glewInit();
    tex_coord();



    start();
    generateMaze(0, 0);

    cells[3][3].east = 0;
    cells[3][4].west = 0;
    cells[4][4].west = 0;
    cells[4][3].west = 0;
    //consoleMaze();

    makemaze();


    projection = ortho(-8, 8, -8, 8, 8, -8);
    model_view = matMult(look_at(4, 1, 3, 4, 0, 3, 0, 0, -1), model_view);


    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
