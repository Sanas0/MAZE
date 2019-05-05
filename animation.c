#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

typedef struct hero
{
  SDL_Surface *image[8];
  SDL_Surface *Hit;
  SDL_Surface *imageActuelle;
  SDL_Rect position;
  SDL_Rect positionO;
  int fram;
  int direction;
  float acc;
  float moving;
  float velocity;

}hero;
hero Inithero(hero p,int x, int y)
{
p.image[0]=IMG_Load("1.png");
p.image[1]=IMG_Load("2.png");
p.image[2]=IMG_Load("3.png");
p.image[3]=IMG_Load("4.png");
p.image[4]=IMG_Load("5.png");
p.image[5]=IMG_Load("6.png");
p.image[6]=IMG_Load("7.png");
p.image[7]=IMG_Load("8.png");
p.image[8]=IMG_Load("9.png");
p.image[9]=IMG_Load("10.png");
p.image[10]=IMG_Load("11.png");
p.image[11]=IMG_Load("12.png");
p.image[12]=IMG_Load("13.png");
/*p.image[13]=IMG_Load("14.png");
p.image[14]=IMG_Load("15.png");
p.image[15]=IMG_Load("16.png");*/
  p.Hit=IMG_Load("17.png");
  p.imageActuelle=p.image[0];
  p.position.x=x;
  p.position.y=y;
  p.positionO=p.position;
  p.fram=0;
  p.direction=0;
  return p;
}
void  Afficherhero(hero p ,SDL_Surface *screen)
{
  SDL_BlitSurface(p.imageActuelle,NULL,screen,&p.position);
}
hero Animatehero(hero p)
{
  if (p.fram>12) {
    p.fram=0;
  }
  else
 p.fram++;
  p.imageActuelle=p.image[p.fram];
  return p;

}
hero Movehero(hero p ,SDL_Rect personnage,int *stat)
{
int distance;
  if(p.position.x>=personnage.x)
    distance=p.position.x-personnage.x;
  else
    distance=personnage.x-p.position.x;
if(distance<50)*stat=1;
else *stat=0;
    if(distance<200)
      {
        if(p.position.x>=personnage.x)
          p.direction=0;
        else
          p.direction=1;
      }
      else
    {  if(p.positionO.x+100==p.position.x)
          p.direction=0;
      if(p.positionO.x-100==p.position.x)
        p.direction=1;}
      if(p.direction==1)
      {
        p.position.x+=5;
      }
      if(p.direction==0)
      {
        p.position.x-=5;
      }
  return p;
}
int main(int argc, char *argv[])
{SDL_Surface *ecran;
  SDL_Surface *personnage =NULL;
   SDL_Init(SDL_INIT_VIDEO);
   hero h;
h=Inithero(h,0,250);
ecran = SDL_SetVideoMode(800, 600,32, SDL_HWSURFACE || SDL_DOUBLEBUF || SDL_FULLSCREEN );
SDL_Rect pos;
pos.y=250;
pos.x=0;

    SDL_Event event;
    int continuer = 1,a;





    while (continuer)
    { SDL_PollEvent(&event);


      
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
		case SDL_KEYUP:
break;
            case SDL_KEYDOWN :

                 switch(event.key.keysym.sym)
                {


                    case SDLK_RIGHT:
pos.x+=30;

                        break;
                    case SDLK_LEFT :

pos.x-=30;

                    break;




                }
                break;


        }
SDL_Delay(90);

h=Movehero(h,pos,&a);
h=Animatehero(h);

 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

 SDL_BlitSurface(personnage,NULL,ecran, &pos);
  Afficherhero(h,ecran);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(personnage);

    SDL_Quit();

    return EXIT_SUCCESS;


}

