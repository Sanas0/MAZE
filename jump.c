#include <SDL/SDL.h>

#ifdef WIN32
#pragma comment(lib,"sdl.lib")
#pragma comment(lib,"sdlmain.lib")
#endif

#define STAT_SOL 0
#define STAT_AIR 1

typedef struct
{
	int status;
	float x,y;
	float vx,vy;
} Sprite;

void InitSprite(Sprite* Sp)
{
	Sp->x = 100.0f;
	Sp->y = 220.0f;
	Sp->status = STAT_SOL;
	Sp->vx = Sp->vy = 0.0f;
}

void Render(Sprite* Sp,SDL_Surface* screen)
{
	SDL_Rect R;
	R.x = (Sint16)Sp->x;
	R.y = (Sint16)Sp->y;
	R.w = 20;
	R.h = 40;
	SDL_FillRect(screen,&R,SDL_MapRGB(screen->format,0,255,0));
}

void Saute(Sprite* Sp,float impulsion)
{
	Sp->vy = -impulsion;
	Sp->status = STAT_AIR;
}

void ControleSol(Sprite* Sp)
{
	if (Sp->y>250.0f)
	{
		Sp->y = 250.0f;
		if (Sp->vy>0)
			Sp->vy = 0.0f;
		Sp->status = STAT_SOL;
	}
}

void Gravite(Sprite* Sp,float factgravite,float factsautmaintenu,Uint8* keys)
 {
	if (Sp->status == STAT_AIR && keys[SDLK_SPACE])
		factgravite/=factsautmaintenu;
	Sp->vy += factgravite;
}

void Evolue(Sprite* Sp,Uint8* keys)
{
	float lateralspeed = 0.5f;
	float airlateralspeedfacteur = 1.0f;
	float maxhspeed = 3.0f;
	float adherance = 1.5f;
	float impulsion = 6.0f;
	float factgravite = 0.5f;
	float factsautmaintenu = 3.0f;
// controle lateral
	if (Sp->status == STAT_AIR) // (*2)
		lateralspeed*= airlateralspeedfacteur;
	if (keys[SDLK_LEFT]) // (*1)
		Sp->vx-=lateralspeed;
	if (keys[SDLK_RIGHT])
		Sp->vx+=lateralspeed;
	if (Sp->status == STAT_SOL && !keys[SDLK_LEFT] && !keys[SDLK_RIGHT]) // (*3)
		Sp->vx/=adherance;
// limite vitesse
	if (Sp->vx>maxhspeed) // (*4)
		Sp->vx = maxhspeed;
	if (Sp->vx<-maxhspeed)
		Sp->vx = -maxhspeed;
// saut
	if (keys[SDLK_SPACE] && Sp->status == STAT_SOL)
		Saute(Sp,impulsion);
	Gravite(Sp,factgravite,factsautmaintenu,keys);
	ControleSol(Sp);
// application du vecteur à la position.
	Sp->x +=Sp->vx;
	Sp->y +=Sp->vy;
}

int main(int argc,char** argv)
{
	SDL_Surface* screen;
	int numkeys;
	Uint8 * keys;
	Sprite S;
	Uint32 timer,elapsed;
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(400,320,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
	InitSprite(&S);
	do 
	{
		timer = SDL_GetTicks();
		SDL_FillRect(screen,NULL,0);
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&numkeys);
		//printf ("%d\n",keys);
		Evolue(&S,keys);
		Render(&S,screen);
		SDL_Flip(screen);
		elapsed = SDL_GetTicks() - timer;
		if (elapsed<20)
		SDL_Delay(20-elapsed);
	} while (!keys[SDLK_ESCAPE]);
	SDL_Quit();
	return 0;
}

