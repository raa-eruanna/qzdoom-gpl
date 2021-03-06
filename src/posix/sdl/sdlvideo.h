#include "hardware.h"
#include "v_video.h"
#include "sdlglvideo.h"

class SDLFB : public SDLBaseFB
{
	DECLARE_CLASS(SDLFB, SDLBaseFB)
public:
	SDLFB(int width, int height, bool bgra, bool fullscreen, SDL_Window *oldwin);
	~SDLFB();

	bool Lock(bool buffer);
	void Unlock();
	bool Relock();
	void ForceBuffering(bool force);
	bool IsValid();
	void Update();
	PalEntry *GetPalette();
	void GetFlashedPalette(PalEntry pal[256]);
	void UpdatePalette();
	bool SetGamma(float gamma);
	bool SetFlash(PalEntry rgb, int amount);
	void GetFlash(PalEntry &rgb, int &amount);
	void SetFullscreen(bool fullscreen);
	int GetPageCount();
	bool IsFullscreen();

	friend class SDLGLVideo;

	virtual void SetVSync(bool vsync);
	virtual void ScaleCoordsFromWindow(SWORD &x, SWORD &y);

	SDL_Window *GetSDLWindow() override { return Screen; }

private:
	PalEntry SourcePalette[256];
	BYTE GammaTable[3][256];
	PalEntry Flash;
	int FlashAmount;
	float Gamma;
	bool UpdatePending;

	SDL_Window *Screen;
	SDL_Renderer *Renderer;
	union
	{
		SDL_Texture *Texture;
		SDL_Surface *Surface;
	};

	bool UsingRenderer;
	bool NeedPalUpdate;
	bool NeedGammaUpdate;
	bool NotPaletted;

	void UpdateColors();
	void ResetSDLRenderer();

	SDLFB() {}
};
