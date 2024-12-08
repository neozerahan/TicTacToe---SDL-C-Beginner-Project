#include"..\Include\UI.h"

void FadeOut(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect)
{
    SDL_RenderSetViewport(renderer, screenRect); 
    SDL_SetTextureBlendMode(transTexture, SDL_BLENDMODE_BLEND);
    if(transRect->alphaValue >= 0)
    {
        SDL_SetTextureAlphaMod(transTexture, 
                transRect->alphaValue);

        SDL_RenderCopy(renderer, transTexture, 
                NULL, NULL);

        transRect->alphaValue -= fadeSpeed;
        if(transRect->alphaValue <= 0) 
        {
            transRect->transState = NEXT_TRANS_STATE;
            transRect->alphaValue = 0;
        }
    }
}

void FadeIn(CustomRect *transRect, SDL_Renderer *renderer, SDL_Texture *transTexture,
        Uint8 NEXT_TRANS_STATE, Uint16 fadeSpeed, SDL_Rect *screenRect)
{
    SDL_RenderSetViewport(renderer, screenRect);
    SDL_SetTextureBlendMode(transTexture, SDL_BLENDMODE_BLEND);
    if(transRect->alphaValue <= 255)
    {
        SDL_SetTextureAlphaMod(transTexture, 
                transRect->alphaValue);

        SDL_RenderCopy(renderer, transTexture, 
                NULL, NULL);

        transRect->alphaValue += fadeSpeed;
        printf("Transition Alpha Value: %d\n", transRect->alphaValue);
        if(transRect->alphaValue >= 255) 
        {
            transRect->transState = NEXT_TRANS_STATE;
            transRect->alphaValue = 255;
        }
    }
}

void DrawButton(Button *button, SDL_Renderer *renderer, SDL_Window *window, int x, int y,
        int collisionOffSetX, int collisionOffsetY, uint8_t allign, uint8_t showCollisionBox){

    ShowText(&button->text, renderer, x, y, allign); 
    button->rect = button->text.rect;

    button->collisionBox.x1 = button->rect.x + collisionOffSetX;
    button->collisionBox.x2 = button->rect.x + button->rect.w + collisionOffSetX;
    button->collisionBox.y1 = button->rect.y + collisionOffsetY;
    button->collisionBox.y2 = button->rect.y + button->rect.h + collisionOffsetY;

    if(showCollisionBox != TRUE) return;

    SDL_Rect r = {
        button->collisionBox.x1 - collisionOffSetX,
        button->collisionBox.y1 - collisionOffsetY, 
        button->rect.w,
        button->rect.h};

    SDL_SetRenderDrawColor(renderer, 0, 128, 0,0);

    SDL_RenderDrawRect(renderer, &r);
}
