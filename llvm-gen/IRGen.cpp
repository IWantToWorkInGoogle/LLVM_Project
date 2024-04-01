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

    ArrayType *innerArrayType = ArrayType::get(Type::getInt8Ty(context), 256);
    ArrayType *outerArrayType = ArrayType::get(innerArrayType, 512);

    GlobalVariable *stateMatrix = new GlobalVariable(*module, outerArrayType, false, GlobalValue::ExternalLinkage, builder.getInt1(false));
    GlobalVariable *newStateMatrix = new GlobalVariable(*module, outerArrayType, false, GlobalValue::ExternalLinkage, builder.getInt1(false));

    FunctionType *funcType = FunctionType::get(PointerType::get(Type::getInt8Ty(context), 0), {Type::getInt64Ty(context), Type::getInt64Ty(context)}, false);
    Function *func = Function::Create(funcType, Function::ExternalLinkage, "getelementptr_function", module);

    Function::arg_iterator argIter = func->arg_begin();
    Argument *idx1Arg = &*argIter;
    Argument *idx2Arg = &*(++argIter);

    Value *indices[] = {
            builder.getInt64(0),
            idx1Arg,
            idx2Arg
    };

    FunctionType *setDeadType = FunctionType::get(voidType, setDeadParamTypes, false);
    FunctionCallee setDeadFunc = module->getOrInsertFunction("setDead", setDeadType);

// declare dso_local void @setAlive(i32 noundef %0, i32 noundef %1)
    ArrayRef<Type *> setAliveParamTypes = {Type::getInt32Ty(context),
                                           Type::getInt32Ty(context)};
    FunctionType *setAliveType = FunctionType::get(voidType, setAliveParamTypes, false);
    FunctionCallee setAliveFunc = module->getOrInsertFunction("setAlive", setAliveType);

// declare dso_local void @simSetRender()
    FunctionType *simSetRenderType = FunctionType::get(voidType, noArgs, false);
    FunctionCallee simSetRenderFunc = module->getOrInsertFunction("simSetRender", simSetRenderType);

// declare dso_local void @simFlush()

    FunctionType *simFlushType = FunctionType::get(voidType, noArgs, false);
    FunctionCallee simFlushFunc = module->getOrInsertFunction("simFlush", simFlushType);

// declare dso_local void @simInit()
    FunctionType *simInitType = FunctionType::get(voidType, noArgs, false);
    FunctionCallee simInitFunc = module->getOrInsertFunction("simInit", simInitType);

// declare dso_local void @simPutPixel(i32 noundef %0, i32 noundef %1, i32 noundef %2)
    ArrayRef<Type *> simPutPixelParamTypes = {Type::getInt32Ty(context),
                                              Type::getInt32Ty(context),
                                              Type::getInt32Ty(context)};

    FunctionType *simPutPixelType = FunctionType::get(voidType, simPutPixelParamTypes, false);
    FunctionCallee simPutPixelFunc = module->getOrInsertFunction("simPutPixel", simPutPixelType);

// declare dso_local void @simExit()
    FunctionType *simExitType = FunctionType::get(voidType, noArgs, false);
    FunctionCallee simExitFunc = module->getOrInsertFunction("simExit", simExitType);

// declare dso_local i32 @simRand()
    FunctionType *simRandType = FunctionType::get(i32Type, noArgs, false);
    FunctionCallee simRandFunc = module->getOrInsertFunction("simRand", simRandType);

//    define dso_local void @app() local_unnamed_addr #0
    FunctionType *appFuncType = FunctionType::get(builder.getVoidTy(), false);
    Function *appFunc =
            Function::Create(appFuncType, Function::ExternalLinkage, "app", module);
    {
        BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB1 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB3 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB4 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB11 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB17 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB24 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB33 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB40 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB46 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB49 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB51 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB53 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB59 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB61 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB68 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB74 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB83 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB89 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB91 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB103 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB109 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB116 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB122 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB127 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB131 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB134 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB137 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB143 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB144 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB145 = BasicBlock::Create(context, "", appFunc);

        builder.SetInsertPoint(BB0);
        builder.CreateBr(BB1);
//            br label %1

        builder.SetInsertPoint(BB1);
//        1:                                                ; preds = %0, %131
        PHINode *val2 = builder.CreatePHI(builder.getInt32Ty(), 2);
    
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
        PHINode *val5 = builder.CreatePHI(builder.getInt64Ty(), 2);
        val5->addIncoming(builder.getInt64(0), BB1);
//            %5 = phi i64 [ 0, %1 ], [ %9, %49 ]
        Value *val6 = builder.CreateICmpEQ(val5, builder.getInt64(0));
//            %6 = icmp eq i64 %5, 0
        Value *val7 = builder.CreateAdd(val5, builder.getInt64(4294967295), "", true);
//            %7 = add nuw i64 %5, 4294967295
        Value *val8 = builder.CreateAnd(val7, builder.getInt64(4294967295));
//            %8 = and i64 %7, 4294967295
        Value *val9 = builder.CreateAdd(val5, builder.getInt64(1), "", true, true);
//            %9 = add nuw nsw i64 %5, 1
        val5->addIncoming(val9, BB49);

        Value *val10 = builder.CreateICmpUGT(val5, builder.getInt64(510));
//            %10 = icmp ugt i64 %5, 510
        builder.CreateCondBr(val6, BB17, BB11);
//            br i1 %6, label %17, label %11
//
        builder.SetInsertPoint(BB11);
//        11:                                               ; preds = %4
        Value *val12 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %12 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 0
        LoadInst *load13 = builder.CreateLoad(Type::getInt8Ty(context), val12);
        load13->setAlignment(Align(16));
        Value *val13 = builder.CreateRet(load13);
//            %13 = load i8, i8* %12, align 16, !tbaa !5, !range !9
        Value *val14 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %14 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 1
        LoadInst *load15 = builder.CreateLoad(Type::getInt8Ty(context), val14);
        load15->setAlignment(Align(1));
        Value *val15 = builder.CreateRet(load15);
//            %15 = load i8, i8* %14, align 1, !tbaa !5, !range !9
        Value *val16 = builder.CreateAdd(val13, val15, "", true, true);
//            %16 = add nuw nsw i8 %13, %15
        builder.CreateBr(BB17);
//            br label %17
//
        builder.SetInsertPoint(BB17);
//        17:                                               ; preds = %11, %4
        PHINode *val18 = builder.CreatePHI(builder.getInt8Ty(), 2);
        val18->addIncoming(val16, BB11);
        val18->addIncoming(builder.getInt8(0), BB4);
//            %18 = phi i8 [ %16, %11 ], [ 0, %4 ]
        Value *val19 = builder.CreateZExt(val18, Type::getInt32Ty(context));
//            %19 = zext i8 %18 to i32
        Value *val20 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %20 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 1
        LoadInst *load21 = builder.CreateLoad(builder.getInt8Ty(), val20);
        load21->setAlignment(Align(1));
        Value *val21 = builder.CreateRet(load21);
//            %21 = load i8, i8* %20, align 1, !tbaa !5, !range !9
        Value *val22 = builder.CreateZExt(val21, Type::getInt32Ty(context));
//            %22 = zext i8 %21 to i32
        Value *val23 = builder.CreateAdd(val19, val22, "", true, true);
//            %23 = add nuw nsw i32 %19, %22
        builder.CreateCondBr(val10, BB33, BB24);
//            br i1 %10, label %33, label %24
//
        builder.SetInsertPoint(BB24);
//        24:                                               ; preds = %17
        Value *val25 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %25 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 0
        LoadInst *load26 = builder.CreateLoad(builder.getInt8Ty(), val25);
        load26->setAlignment(Align(16));
        Value *val26 = builder.CreateRet(load26);
//            %26 = load i8, i8* %25, align 16, !tbaa !5, !range !9
        Value *val27 = builder.CreateZExt(val26, Type::getInt32Ty(context));
//            %27 = zext i8 %26 to i32
        Value *val28 = builder.CreateAdd(val23, val27, "", true, true);
//            %28 = add nuw nsw i32 %23, %27
        Value *val29 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %29 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 1
        LoadInst *load30 = builder.CreateLoad(builder.getInt8Ty(), val29);
        load30->setAlignment(Align(1));
        Value *val30 = builder.CreateRet(load30);
//            %30 = load i8, i8* %29, align 1, !tbaa !5, !range !9
        Value *val31 = builder.CreateZExt(val30, Type::getInt32Ty(context));
//            %31 = zext i8 %30 to i32
        Value *val32 = builder.CreateAdd(val28, val31, "", true, true);
//            %32 = add nuw nsw i32 %28, %31
        builder.CreateBr(BB33);
//            br label %33
//
        builder.SetInsertPoint(BB33);
//        33:                                               ; preds = %24, %17
        PHINode *val34 = builder.CreatePHI(builder.getInt32Ty(), 2);
        val34->addIncoming(val32, BB24);
        val34->addIncoming(val23, BB17);
//            %34 = phi i32 [ %32, %24 ], [ %23, %17 ]
        Value *val35 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %35 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 0
        LoadInst *load36 = builder.CreateLoad(builder.getInt8Ty(), val35);
        load36->setAlignment(Align(16));
        Value *val36 = builder.CreateRet(load36);
//            %36 = load i8, i8* %35, align 16, !tbaa !5, !range !9
        Value *val37 = builder.CreateICmpEQ(val36, builder.getInt8(0));
//            %37 = icmp eq i8 %36, 0
        Value *val38 = builder.CreateICmpEQ(val34, builder.getInt32(3));
//            %38 = icmp eq i32 %34, 3
        Value *val39 = builder.CreateSelect(val37, val38,
                                           builder.getInt1(false));
//            %39 = select i1 %37, i1 %38, i1 false
        builder.CreateCondBr(val39, BB46, BB40);
//            br i1 %39, label %46, label %40
//
        builder.SetInsertPoint(BB40);
//        40:                                               ; preds = %33
        Value *val41 = builder.CreateXor(val37, builder.getInt1(true));
//            %41 = xor i1 %37, true
        Value *val42 = builder.CreateAnd(val34, builder.getInt32(-2));
//            %42 = and i32 %34, -2
        Value *val43 = builder.CreateICmpEQ(val42, builder.getInt32(2));
//            %43 = icmp eq i32 %42, 2
        Value *val44 = builder.CreateSelect(val41, val43,
                                           builder.getInt1(false));
//            %44 = select i1 %41, i1 %43, i1 false
        Value *val45 = builder.CreateZExt(val44, Type::getInt8Ty(context));
//            %45 = zext i1 %44 to i8
        builder.CreateBr(BB46);
//            br label %46
//
        builder.SetInsertPoint(BB46);
//        46:                                               ; preds = %40, %33
        PHINode *val47 = builder.CreatePHI(builder.getInt8Ty(), 2);
        val47->addIncoming(builder.getInt8(1), BB33);
        val47->addIncoming(val45, BB40);
//            %47 = phi i8 [ 1, %33 ], [ %45, %40 ]
        Value *val48 = builder.CreateInBoundsGEP(outerArrayType, newStateMatrix, indices);
//            %48 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %5, i64 0
//            store i8 %47, i8* %48, align 16, !tbaa !5
        builder.CreateBr(BB51);
//            br label %51
//
        builder.SetInsertPoint(BB49);
//        49:                                               ; preds = %122
        Value *val50 = builder.CreateICmpEQ(val9, builder.getInt64(512));
//            %50 = icmp eq i64 %9, 512
        builder.CreateCondBr(val50, BB127, BB4);
//            br i1 %50, label %127, label %4, !llvm.loop !10
//
        builder.SetInsertPoint(BB51);
//        51:                                               ; preds = %122, %46
        PHINode *val52 = builder.CreatePHI(builder.getInt64Ty(), 2);
        val52->addIncoming(builder.getInt64(1), BB46);
//            %52 = phi i64 [ 1, %46 ], [ %125, %122 ]
        builder.CreateCondBr(val6, BB59, BB53);
//            br i1 %6, label %59, label %53
//
        builder.SetInsertPoint(BB53);
//        53:                                               ; preds = %51
        Value *val54 = builder.CreateAdd(val52, builder.getInt64(4294967295), "", true, true);
//            %54 = add nuw nsw i64 %52, 4294967295
        Value *val55 = builder.CreateAnd(val54, builder.getInt64(4294967295));
//            %55 = and i64 %54, 4294967295
        Value *val56 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %56 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %55
        LoadInst *load57 = builder.CreateLoad(builder.getInt8Ty(), val56);
        load57->setAlignment(Align(1));
        Value *val57 = builder.CreateRet(load57);
//            %57 = load i8, i8* %56, align 1, !tbaa !5, !range !9
        Value *val58 = builder.CreateZExt(val57, Type::getInt32Ty(context));
//            %58 = zext i8 %57 to i32
        builder.CreateBr(BB59);
//            br label %59
//
        builder.SetInsertPoint(BB59);
//        59:                                               ; preds = %51, %53
        PHINode *val60 = builder.CreatePHI(builder.getInt32Ty(), 2);
        val60->addIncoming(builder.getInt32(0), BB51);
        val60->addIncoming(val58, BB53);
//            %60 = phi i32 [ 0, %51 ], [ %58, %53 ]
        builder.CreateCondBr(val6, BB74, BB61);
//            br i1 %6, label %74, label %61
//
        builder.SetInsertPoint(BB61);
//        61:                                               ; preds = %59
        Value *val62 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %62 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %52
        LoadInst *load63 = builder.CreateLoad(builder.getInt8Ty(), val62);
        load63->setAlignment(Align(1));
        Value *val63 = builder.CreateRet(load63);
//            %63 = load i8, i8* %62, align 1, !tbaa !5, !range !9
        Value *val64 = builder.CreateZExt(val63, Type::getInt32Ty(context));
//            %64 = zext i8 %63 to i32
        Value *val65 = builder.CreateAdd(val60, val64, "", true, true);
//            %65 = add nuw nsw i32 %60, %64
        Value *val66 = builder.CreateICmpUGT(val52, builder.getInt64(254));
//            %66 = icmp ugt i64 %52, 254
        Value *val67 = builder.CreateSelect(val66, builder.getInt1(true),
                                           val6);
//            %67 = select i1 %66, i1 true, i1 %6
        builder.CreateCondBr(val67, BB74, BB68);
//            br i1 %67, label %74, label %68
//
        builder.SetInsertPoint(BB68);
//        68:                                               ; preds = %61
        Value *val69 = builder.CreateAdd(val52, builder.getInt64(1), "", true, true);
//            %69 = add nuw nsw i64 %52, 1
        Value *val70 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %70 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %69
        LoadInst *load71 = builder.CreateLoad(builder.getInt8Ty(), val70);
        load71->setAlignment(Align(1));
        Value *val71 = builder.CreateRet(load71);
//            %71 = load i8, i8* %70, align 1, !tbaa !5, !range !9
        Value *val72 = builder.CreateZExt(val71, Type::getInt32Ty(context));
//            %72 = zext i8 %71 to i32
        Value *val73 = builder.CreateAdd(val65, val72, "", true, true);
//            %73 = add nuw nsw i32 %65, %72
        builder.CreateBr(BB74);
//            br label %74
//
        builder.SetInsertPoint(BB74);
//        74:                                               ; preds = %68, %61, %59
        PHINode *val75 = builder.CreatePHI(builder.getInt32Ty(), 3);
        val75->addIncoming(val65, BB61);
        val75->addIncoming(val73, BB68);
        val75->addIncoming(val60, BB59);
//            %75 = phi i32 [ %65, %61 ], [ %73, %68 ], [ %60, %59 ]
        Value *val76 = builder.CreateAdd(val52, builder.getInt64(4294967295), "", true, true);
//            %76 = add nuw nsw i64 %52, 4294967295
        Value *val77 = builder.CreateAnd(val76, builder.getInt64(4294967295));
//            %77 = and i64 %76, 4294967295
        Value *val78 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %78 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %77
        LoadInst *load79 = builder.CreateLoad(builder.getInt8Ty(), val78);
        load79->setAlignment(Align(1));
        Value *val79 = builder.CreateRet(load79);
//            %79 = load i8, i8* %78, align 1, !tbaa !5, !range !9
        Value *val80 = builder.CreateZExt(val79, Type::getInt32Ty(context));
//            %80 = zext i8 %79 to i32
        Value *val81 = builder.CreateAdd(val75, val80, "", true, true);
//            %81 = add nuw nsw i32 %75, %80
        Value *val82 = builder.CreateICmpUGT(val52, builder.getInt64(254));
//            %82 = icmp ugt i64 %52, 254
        builder.CreateCondBr(val82, BB89, BB83);
//            br i1 %82, label %89, label %83
//
        builder.SetInsertPoint(BB83);
//        83:                                               ; preds = %74
        Value *val84 = builder.CreateAdd(val52, builder.getInt64(1), "", true, true);
//            %84 = add nuw nsw i64 %52, 1
        Value *val85 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %85 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %84
        LoadInst *load86 = builder.CreateLoad(builder.getInt8Ty(), val85);
        load86->setAlignment(Align(1));
        Value *val86 = builder.CreateRet(load86);
//            %86 = load i8, i8* %85, align 1, !tbaa !5, !range !9
        Value *val87 = builder.CreateZExt(val86, Type::getInt32Ty(context));
//            %87 = zext i8 %86 to i32
        Value *val88 = builder.CreateAdd(val81, val87, "", true, true);
//            %88 = add nuw nsw i32 %81, %87
        builder.CreateBr(BB89);
//            br label %89
//
        builder.SetInsertPoint(BB89);
//        89:                                               ; preds = %83, %74
        PHINode *val90 = builder.CreatePHI(builder.getInt32Ty(), 2);
        val90->addIncoming(val81, BB74);
        val90->addIncoming(val88, BB83);
//            %90 = phi i32 [ %81, %74 ], [ %88, %83 ]
        builder.CreateCondBr(val10, BB109, BB91);
//            br i1 %10, label %109, label %91
//
        builder.SetInsertPoint(BB91);
//        91:                                               ; preds = %89
        Value *val92 = builder.CreateAdd(val52, builder.getInt64(4294967295), "", true, true);
//            %92 = add nuw nsw i64 %52, 4294967295
        Value *val93 = builder.CreateAnd(val92, builder.getInt64(4294967295));
//            %93 = and i64 %92, 4294967295
        Value *val94 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %94 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %93
        LoadInst *load95 = builder.CreateLoad(builder.getInt8Ty(), val94);
        load95->setAlignment(Align(1));
        Value *val95 = builder.CreateRet(load95);
//            %95 = load i8, i8* %94, align 1, !tbaa !5, !range !9
        Value *val96 = builder.CreateZExt(val95, Type::getInt32Ty(context));
//            %96 = zext i8 %95 to i32
        Value *val97 = builder.CreateAdd(val90, val96, "", true, true);
//            %97 = add nuw nsw i32 %90, %96
         Value *val98 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %98 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %52
        LoadInst *load99 = builder.CreateLoad(builder.getInt8Ty(), val98);
        load99->setAlignment(Align(1));
        Value *val99 = builder.CreateRet(load99);
//            %99 = load i8, i8* %98, align 1, !tbaa !5, !range !9
        Value *val100 = builder.CreateZExt(val99, Type::getInt32Ty(context));
//            %100 = zext i8 %99 to i32
        Value *val101 = builder.CreateAdd(val97, val100, "", true, true);
//            %101 = add nuw nsw i32 %97, %100
        Value *val102 = builder.CreateICmpUGT(val52, builder.getInt64(254));
//            %102 = icmp ugt i64 %52, 254
        builder.CreateCondBr(val102, BB109, BB103);
//            br i1 %102, label %109, label %103
//
        builder.SetInsertPoint(BB103);
//        103:                                              ; preds = %91
        Value *val104 = builder.CreateAdd(val52, builder.getInt64(1), "", true, true);
//            %104 = add nuw nsw i64 %52, 1
        Value *val105 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %105 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %104
        LoadInst *load106 = builder.CreateLoad(builder.getInt8Ty(), val105);
        load106->setAlignment(Align(1));
        Value *val106 = builder.CreateRet(load106);
//            %106 = load i8, i8* %105, align 1, !tbaa !5, !range !9
        Value *val107 = builder.CreateZExt(val106, Type::getInt32Ty(context));
//            %107 = zext i8 %106 to i32
        Value *val108 = builder.CreateAdd(val101, val107, "", true, true);
//            %108 = add nuw nsw i32 %101, %107
        builder.CreateBr(BB109);
//            br label %109
//
        builder.SetInsertPoint(BB109);
//        109:                                              ; preds = %89, %103, %91
        PHINode *val110 = builder.CreatePHI(builder.getInt32Ty(), 3);
        val110->addIncoming(val101, BB91);
        val110->addIncoming(val108, BB103);
        val110->addIncoming(val90, BB89);
//            %110 = phi i32 [ %101, %91 ], [ %108, %103 ], [ %90, %89 ]
        Value *val111 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %111 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %52
        LoadInst *load112 = builder.CreateLoad(builder.getInt8Ty(), val111);
        load112->setAlignment(Align(1));
        Value *val112 = builder.CreateRet(load112);
//            %112 = load i8, i8* %111, align 1, !tbaa !5, !range !9
        Value *val113 = builder.CreateICmpEQ(val112, builder.getInt8(0));
//            %113 = icmp eq i8 %112, 0
        Value *val114 = builder.CreateICmpEQ(val110, builder.getInt32(3));
//            %114 = icmp eq i32 %110, 3
        Value *val115 = builder.CreateSelect(val113, val114,
                                           builder.getInt1(false));
//            %115 = select i1 %113, i1 %114, i1 false
        builder.CreateCondBr(val115, BB122, BB116);
//            br i1 %115, label %122, label %116
//
        builder.SetInsertPoint(BB116);
//        116:                                              ; preds = %109
        Value *val117 = builder.CreateXor(val113, builder.getInt1(true));
//            %117 = xor i1 %113, true
        Value *val118 = builder.CreateAnd(val110, builder.getInt32(-2));
//            %118 = and i32 %110, -2
        Value *val119 = builder.CreateICmpEQ(val118, builder.getInt32(2));
//            %119 = icmp eq i32 %118, 2
        Value *val120 = builder.CreateSelect(val117, val119,
                                           builder.getInt1(false));
//            %120 = select i1 %117, i1 %119, i1 false
        Value *val121 = builder.CreateZExt(val120, Type::getInt8Ty(context));
//            %121 = zext i1 %120 to i8
        builder.CreateBr(BB122);
//            br label %122
//
        builder.SetInsertPoint(BB122);
//        122:                                              ; preds = %116, %109
        PHINode *val123 = builder.CreatePHI(builder.getInt8Ty(), 2);
        val123->addIncoming(builder.getInt8(1), BB109);
        val123->addIncoming(val121, BB116);
//            %123 = phi i8 [ 1, %109 ], [ %121, %116 ]
        Value *val124 = builder.CreateInBoundsGEP(outerArrayType, newStateMatrix, indices);
//            %124 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %5, i64 %52
//            store i8 %123, i8* %124, align 1, !tbaa !5
        Value *val125 = builder.CreateAdd(val52, builder.getInt64(1), "", true, true);
//            %125 = add nuw nsw i64 %52, 1
        val52->addIncoming(val125, BB122);

        Value *val126 = builder.CreateICmpEQ(val125, builder.getInt64(256));
//            %126 = icmp eq i64 %125, 256
        builder.CreateCondBr(val126, BB49, BB51);
//            br i1 %126, label %49, label %51, !llvm.loop !12
//
        builder.SetInsertPoint(BB127);
//        127:                                              ; preds = %49, %134
        PHINode *val128 = builder.CreatePHI(builder.getInt64Ty(), 2);
        val128->addIncoming(builder.getInt64(0), BB49);
//            %128 = phi i64 [ %135, %134 ], [ 0, %49 ]
        Value *val129 = builder.CreateTrunc(val128, Type::getInt32Ty(context));
//            %129 = trunc i64 %128 to i32
        Value *val130 = builder.CreateTrunc(val128, Type::getInt32Ty(context));
//            %130 = trunc i64 %128 to i32
        builder.CreateBr(BB137);
//            br label %137
//
        builder.SetInsertPoint(BB131);
//        131:                                              ; preds = %134
        builder.CreateCall(simFlushFunc, {});
//            tail call void (...) @simFlush() #2
        Value *val132 = builder.CreateAdd(val2, builder.getInt32(1), "", true, true);
//            %132 = add nuw nsw i32 %2, 1
        val2->addIncoming(val132, BB131);
        Value *val133 = builder.CreateICmpEQ(val132, builder.getInt32(1000));
//            %133 = icmp eq i32 %132, 1000
        builder.CreateCondBr(val133, BB3, BB1);
//            br i1 %133, label %3, label %1, !llvm.loop !14
//
        builder.SetInsertPoint(BB134);
//        134:                                              ; preds = %145
        Value *val135 = builder.CreateAdd(val128, builder.getInt64(1), "", true, true);
//            %135 = add nuw nsw i64 %128, 1
        val128->addIncoming(val135, BB134);
        Value *val136 = builder.CreateICmpEQ(val135, builder.getInt64(512));
//            %136 = icmp eq i64 %135, 512
        builder.CreateCondBr(val136, BB131, BB127);
//            br i1 %136, label %131, label %127, !llvm.loop !15
//
        builder.SetInsertPoint(BB137);
//        137:                                              ; preds = %127, %145
        PHINode *val138 = builder.CreatePHI(builder.getInt64Ty(), 2);
        val138->addIncoming(builder.getInt64(0), BB127);
//            %138 = phi i64 [ 0, %127 ], [ %148, %145 ]
        Value *val139 = builder.CreateInBoundsGEP(outerArrayType, newStateMatrix, indices);
//            %139 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %128, i64 %138
        LoadInst *load140 = builder.CreateLoad(builder.getInt8Ty(), val139);
        load140->setAlignment(Align(1));
        Value *val140 = builder.CreateRet(load140);
//            %140 = load i8, i8* %139, align 1, !tbaa !5, !range !9
        Value *val141 = builder.CreateICmpEQ(val140, builder.getInt8(0));
//            %141 = icmp eq i8 %140, 0
        Value *val142 = builder.CreateTrunc(val138, Type::getInt32Ty(context));
//            %142 = trunc i64 %138 to i32
        builder.CreateCondBr(val141, BB144, BB143);
//            br i1 %141, label %144, label %143
//
        builder.SetInsertPoint(BB143);
//        143:                                              ; preds = %137
        Value *putPixelArgs1[] = {val129, val142, builder.getInt32(16777215)};
        builder.CreateCall(simPutPixelFunc, putPixelArgs1);
//            tail call void @simPutPixel(i32 noundef %129, i32 noundef %142, i32 noundef 16777215) #2
        builder.CreateBr(BB145);
//            br label %145
//
        builder.SetInsertPoint(BB144);
//        144:                                              ; preds = %137
        Value *putPixelArgs2[] = {val130, val142, builder.getInt32(0)};
        builder.CreateCall(simPutPixelFunc, putPixelArgs2);
//            tail call void @simPutPixel(i32 noundef %130, i32 noundef %142, i32 noundef 0) #2
        builder.CreateBr(BB145);
//            br label %145
//
        builder.SetInsertPoint(BB145);
//        145:                                              ; preds = %144, %143
        LoadInst *load146 = builder.CreateLoad(builder.getInt8Ty(), val139);
        load146->setAlignment(Align(1));
        Value *val146 = builder.CreateRet(load146);
//            %146 = load i8, i8* %139, align 1, !tbaa !5, !range !9
        Value *val147 = builder.CreateInBoundsGEP(outerArrayType, stateMatrix, indices);
//            %147 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %128, i64 %138
//            store i8 %146, i8* %147, align 1, !tbaa !5
        Value *val148 = builder.CreateAdd(val138, builder.getInt64(1), "", true, true);
//            %148 = add nuw nsw i64 %138, 1
        val138->addIncoming(val148, BB145);

        Value *val149 = builder.CreateICmpEQ(val148, builder.getInt64(256));
//            %149 = icmp eq i64 %148, 256
        builder.CreateCondBr(val149, BB134, BB137);
//            br i1 %149, label %134, label %137, !llvm.loop !16
    }

// Dump LLVM IR
    module->print(outs(), nullptr);

    // Interpreter of LLVM IR
    outs() << "Building code...\n";
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
        if (fnName == "setDead") {
            return reinterpret_cast<void *>(setDead);
        }
        if (fnName == "setAlive") {
            return reinterpret_cast<void *>(setAlive);
        }
        if (fnName == "simSetRender") {
            return reinterpret_cast<void *>(simSetRender);
        }
        if (fnName == "simExit") {
            return reinterpret_cast<void *>(simExit);
        }
        if (fnName == "simPutPixel") {
            return reinterpret_cast<void *>(simPutPixel);
        }
        if (fnName == "simInit") {
            return reinterpret_cast<void *>(simInit);
        }
        if (fnName == "simFlush") {
            return reinterpret_cast<void *>(simFlush);
        }
        if (fnName == "simRand") {
            return reinterpret_cast<void *>(simRand);
        }
        return nullptr;
    });
    ee->finalizeObject();

    outs() << "Running code...\n";
    simInit();
    ArrayRef<GenericValue> noargs;
    GenericValue v = ee->runFunction(appFunc, noargs);
    simExit();
    outs() << "Code was run.\n";
    return EXIT_SUCCESS;

}
