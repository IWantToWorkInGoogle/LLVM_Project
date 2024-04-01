#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "../src/sim.h"

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

void setDead(int x, int y) {
	state[x][y] = false;
	simPutPixel(x, y, 0xFFFFFF);
}

void setAlive(int x, int y) {
	state[x][y] = true;
	simPutPixel(x, y, 0x000000);
}

void simSetRender() {
	for (int x = 0; x < SIM_X_SIZE; ++x) {
		for (int y = 0; y < SIM_Y_SIZE; ++y) {
			int r = simRand() % INTENSE;
			if (r) setDead(x,y);
			else setAlive(x,y);
		}
	}
	simFlush();
}

void simInit()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SIM_X_SIZE, SIM_Y_SIZE, 0, &Window, &Renderer);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
	srand(time(NULL));
	simSetRender();
    SDL_RenderClear(Renderer);
}

void simExit()
{
    SDL_Event event;
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void simFlush()
{
    SDL_PumpEvents();
    assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
    Uint32 cur_ticks = SDL_GetTicks() - Ticks;
    if (cur_ticks < FRAME_TICKS)
    {
        SDL_Delay(FRAME_TICKS - cur_ticks);
    }
    SDL_RenderPresent(Renderer);
}

void simPutPixel(int x, int y, int argb)
{
    assert(0 <= x && x < SIM_X_SIZE && "Out of range");
    assert(0 <= y && y < SIM_Y_SIZE && "Out of range");
    Uint8 a = argb >> 24;
    Uint8 r = (argb >> 16) & 0xFF;
    Uint8 g = (argb >> 8) & 0xFF;
    Uint8 b = argb & 0xFF;
    SDL_SetRenderDrawColor(Renderer, r, g, b, a);
    SDL_RenderDrawPoint(Renderer, x, y);
    Ticks = SDL_GetTicks();
}

int simRand()
{
    return rand();
}


#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    LLVMContext context;
    // ; ModuleID = 'sim.c'
    // source_filename = "sim.c"
    Module *module = new Module("sim.c", context);
    IRBuilder<> builder(context);

//   define dso_local void @setDead(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
    Type *i32Type = Type::getInt32Ty(context);
    Type *i64Type = Type::getInt64Ty(context);
    Type *voidType = Type::getVoidTy(context);

    ArrayRef<Type *> setDeadParamTypes = {Type::getInt32Ty(context),
                                     Type::getInt32Ty(context)};
    ArrayRef<Type *> noArgs = {};

    FunctionType *setDeadType = FunctionType::get(voidType, setDeadParamTypes, false);
    FunctionCallee setDeadFunc = module->getOrInsertFunction("setDead", setDeadType);

// declare dso_local void @setAlive(i32 noundef %0, i32 noundef %1)
    ArrayRef<Type *> setAliveParamTypes = {Type::getInt32Ty(context),
                                     Type::getInt32Ty(context)};
    FunctionType *setAliveType = FunctionType::get(voidType, setAliveParamTypes, false);
    FunctionCallee setAliveFunc = module->getOrInsertFunction("setAlive", setAliveType);

// declare dso_local void @simSetRender()
    

// declare dso_local void @simFlush()

// declare i32 @SDL_Init(i32 noundef) 

// declare dso_local void @simPutPixel(i32 noundef %0, i32 noundef %1, i32 noundef %2)

// declare void @SDL_Quit() 

// declare dso_local i32 @simRand()

















// Dump LLVM IR
  module->print(outs(), nullptr);

  // Interpreter of LLVM IR
  outs() << "Building code...\n";
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == "simPrepareScreen") {
      return reinterpret_cast<void *>(simPrepareScreen);
    }
    if (fnName == "simCheckQuit") {
      return reinterpret_cast<void *>(simCheckQuit);
    }
    if (fnName == "simSetPixel") {
      return reinterpret_cast<void *>(simSetPixel);
    }
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "ARGB") {
      return reinterpret_cast<void *>(ARGB);
    }
    return nullptr;
  });
  ee->finalizeObject();

  outs() << "Running code...\n";
  simInit();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(appFunc, noargs);
  simClose();
  outs() << "Code was run.\n";
  return EXIT_SUCCESS;

}