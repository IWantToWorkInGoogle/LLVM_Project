#include <stdlib.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "../src/sim.h"

#define FRAME_TICKS 50
#define INTENSE 5
#define SIM_X_SIZE 512
#define SIM_Y_SIZE 256

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;
bool state[SIM_X_SIZE][SIM_Y_SIZE];

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

using namespace llvm;

int main() {
    LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    Module *module = new Module("top", context);
    IRBuilder<> builder(context);

    // declare void @main()
    FunctionType *funcType = FunctionType::get(builder.getVoidTy(), false);
    Function *mainFunc =
            Function::Create(funcType, Function::ExternalLinkage, "main", module);
    // entry:
    BasicBlock *entryBB = BasicBlock::Create(context, "entry", mainFunc);

    FunctionType *appFuncType = FunctionType::get(builder.getVoidTy(), false);
    Function *appFunc = Function::Create(appFuncType, Function::ExternalLinkage, "app", module);

    {
        BasicBlock *BB0 = BasicBlock::Create(context, "0", appFunc);
        BasicBlock *BB1 = BasicBlock::Create(context, "0", appFunc);
        BasicBlock *BB3 = BasicBlock::Create(context, "3", appFunc);
        BasicBlock *BB4 = BasicBlock::Create(context, "4", appFunc);
        BasicBlock *BB11 = BasicBlock::Create(context, "11", appFunc);
        BasicBlock *BB17 = BasicBlock::Create(context, "17", appFunc);


        builder.SetInsertPoint(BB3);


//    define dso_local void @app() local_unnamed_addr #0 {
        builder.SetInsertPoint(BB0);
//        br label %1
        builder.CreateBr(BB1);
//
        builder.SetInsertPoint(BB1);
//        1:                                                ; preds = %0, %131
        PHINode *val2 = builder.CreatePHI(builder.getInt32Ty(), 1);
        val2->addIncoming(builder.getInt32(0), BB0);
//            %2 = phi i32 [ 0, %0 ], [ %132, %131 ]
        builder.CreateBr(BB4);
//            br label %4
//
        builder.SetInsertPoint(BB3);
//        3:                                                ; preds = %131
        builder.CreateRetVoid();
//            ret void
//
        builder.SetInsertPoint(BB4);
//        4:                                                ; preds = %1, %49
        PHINode *val5 = builder.CreatePHI(builder.getInt64Ty(), 1);
        val5->addIncoming(builder.getInt64(0), BB1);
//            %5 = phi i64 [ 0, %1 ], [ %9, %49 ]
        Value *val6= builder.CreateICmpEQ(val5, builder.getInt64(0));
//            %6 = icmp eq i64 %5, 0
        Value *val7 = builder.CreateAdd(val5, builder.getInt64(4294967295), "", true);
//            %7 = add nuw i64 %5, 4294967295
        Value *val8 = builder.CreateAnd(val7, builder.getInt64(4294967295));
//            %8 = and i64 %7, 4294967295
        Value *val9 = builder.CreateAdd(val5, builder.getInt64(1), "", true, true);
//            %9 = add nuw nsw i64 %5, 1
        Value *val10 = builder.CreateICmpUGT(val5, builder.getInt64(510));
//            %10 = icmp ugt i64 %5, 510
        builder.CreateCondBr(val6, BB17, BB11);
//            br i1 %6, label %17, label %11
//
        builder.SetInsertPoint(BB11);
//        11:                                               ; preds = %4
//            %12 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 0
//            %13 = load i8, i8* %12, align 16, !tbaa !5, !range !9
//            %14 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 1
//            %15 = load i8, i8* %14, align 1, !tbaa !5, !range !9
//            %16 = add nuw nsw i8 %13, %15
//            br label %17
        builder.CreateBr(BB17);
    }

    builder.SetInsertPoint(entryBB);
    builder.CreateRetVoid();

    outs() << "#[LLVM IR]:\n";
    module->print(outs(), nullptr);

    // Interpreter of LLVM IR
    outs() << "Running code...\n";
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
        if (fnName == "simPutPixel") {
            return reinterpret_cast<void *>(simPutPixel);
        }
        if (fnName == "simFlush") {
            return reinterpret_cast<void *>(simFlush);
        }
        return nullptr;
    });
    ee->finalizeObject();
    simInit();
    ArrayRef<GenericValue> noargs;
    GenericValue v = ee->runFunction(mainFunc, noargs);
    simExit();
    outs() << "Code was run: " << v.IntVal << "\n";
    return 0;
}