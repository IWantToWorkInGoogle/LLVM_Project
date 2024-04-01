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
    FunctionType appFuncType = FunctionType::get(voidType, noArgs, false);
    Function *appFunc = Function::Create(appFuncType, Function::ExternalLinkage, "app", module);

    BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB3 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB5 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB6 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB13 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB19 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB26 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB35 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB42 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB48 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB51 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB53 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB55 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB61 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB63 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB70 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB76 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB85 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB91 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB93 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB105 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB111 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB118 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB124 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB129 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB133 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB136 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB139 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB145 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB146 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *BB147 = BasicBlock::Create(context, "", appFunc);

    ArrayType *innerArrayType = ArrayType::get(Type::getInt8Ty(context), 256);
    ArrayType *outerArrayType = ArrayType::get(innerArrayType, 512);

    builder.SetInsertPoint(BB0);
//        %1 = alloca [512 x [256 x i8]], align 16
    Value *val1 = builder.CreateAlloca(outerArrayType)->setAlignment(Align(16));
//        %2 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 0, i64 0
//        call void @llvm.lifetime.start.p0i8(i64 131072, i8* nonnull %2) #3
    builder.CreateCall(simPutPixelFunc, simPutPixelParamTypes);


//        br label %3
    builder.CreateBr(BB3);

    builder.SetInsertPoint(BB3);
//        3:                                                ; preds = %0, %133
//        %4 = phi i32 [ 0, %0 ], [ %134, %133 ]
    PHINode *val4 = builder.CreatePHI(builder.getInt64Ty(), 2);
    val4->addIncoming(builder.getInt64(0), BB0);
//        br label %6
    builder.CreateBr(BB6);
//
    builder.SetInsertPoint(BB5);
//        5:                                                ; preds = %133

// TODO
    Function *lifetimeEnd = Intrinsic::getDeclaration(
            module, Intrinsic::lifetime::end, {Type::getVoidTy(context)});
//        call void @llvm.lifetime.end.p0i8(i64 131072, i8* nonnull %2) #3

//        ret void
//
    builder.SetInsertPoint(BB6);
//        6:                                                ; preds = %3, %51
//            %7 = phi i64 [ 0, %3 ], [ %11, %51 ]
    PHINode *val7 = builder.CreatePHI(builder.getInt64Ty(), 2);
    val7->addIncoming(builder.getInt64(0), BB3);
//            %8 = icmp eq i64 %7, 0
    Value *val8 = builder.CreateICmpEQ(val7, builder.getInt64(0));
//            %9 = add nuw i64 %7, 4294967295
    Value *val9 = builder.CreateAdd(val7, builder.getInt64(4294967295), "", true);
//            %10 = and i64 %9, 4294967295
    Value *val10 = builder.CreateAnd(val9, builder.getInt64(4294967295));
//            %11 = add nuw nsw i64 %7, 1
    Value *val11 = builder.CreateAdd(val7, builder.getInt64(1), "", true, true);
    val7->addIncoming(val11, BB51);
//            %12 = icmp ugt i64 %7, 510
    Value *val12 = builder.CreateICmpUGT(val7, builder.getInt64(510));
//            br i1 %8, label %19, label %13
    builder.CreateCondBr(val8, BB19, BB13);
//
    builder.SetInsertPoint(BB13);
//        13:                                               ; preds = %6
//            %14 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 0
//            %15 = load i8, i8* %14, align 16, !tbaa !5, !range !9
    Value *val15 = builder.CreateLoad(builder.getInt8Ty(), val14)->setAlignment(Align(16));
//            %16 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 1
//            %17 = load i8, i8* %16, align 1, !tbaa !5, !range !9
    Value *val17 = builder.CreateLoad(builder.getInt8Ty(), val16)->setAlignment(Align(1));
//            %18 = add nuw nsw i8 %15, %17
    Value *val18 = builder.CreateAdd(val15, val17, "", true, true);

//            br label %19
    builder.CreateBr(BB19);
//
    builder.SetInsertPoint(BB19);
//        19:                                               ; preds = %13, %6
//            %20 = phi i8 [ %18, %13 ], [ 0, %6 ]
    PHINode *val20 = builder.CreatePHI(builder.getInt8Ty(), 2);
    val20->addIncoming(val18, BB13);
    val20->addIncoming(builder.getInt8(0), BB6);
//            %21 = zext i8 %20 to i32
    Value *val21 = builder.CreateZExt(val20, Type::getInt32Ty(context));
//            %22 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 1
//            %23 = load i8, i8* %22, align 1, !tbaa !5, !range !9
    Value *val23 = builder.CreateLoad(builder.getInt8Ty(), val22)->setAlignment(Align(1));

//            %24 = zext i8 %23 to i32
    Value *val24 = builder.CreateZExt(val23, Type::getInt32Ty(context));
//            %25 = add nuw nsw i32 %21, %24
    Value *val25 = builder.CreateAdd(val21, val24, "", true, true);

//            br i1 %12, label %35, label %26
    builder.CreateCondBr(val12, BB35, BB26);
//

    builder.SetInsertPoint(BB26);
//        26:                                               ; preds = %19
//            %27 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 0
//            %28 = load i8, i8* %27, align 16, !tbaa !5, !range !9
    Value *val28 = builder.CreateLoad(builder.getInt8Ty(), val27)->setAlignment(Align(16));

//            %29 = zext i8 %28 to i32
    Value *val29 = builder.CreateZExt(val28, Type::getInt32Ty(context));
//            %30 = add nuw nsw i32 %25, %29
    Value *val30 = builder.CreateAdd(val25, val29, "", true, true);

//            %31 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 1
//            %32 = load i8, i8* %31, align 1, !tbaa !5, !range !9
    Value *val32 = builder.CreateLoad(builder.getInt8Ty(), val31)->setAlignment(Align(1));

//            %33 = zext i8 %32 to i32
    Value *val33 = builder.CreateZExt(val32, Type::getInt32Ty(context));
//            %34 = add nuw nsw i32 %30, %33
    Value *val34 = builder.CreateAdd(val30, val33, "", true, true);

//            br label %35
    builder.CreateBr(BB35);
//
    builder.SetInsertPoint(BB35);
//        35:                                               ; preds = %26, %19
//            %36 = phi i32 [ %34, %26 ], [ %25, %19 ]
    PHINode *val36 = builder.CreatePHI(builder.getInt32Ty(), 2);
    val36->addIncoming(val34, BB26);
    val36->addIncoming(val25, BB19);
//            %37 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 0
//            %38 = load i8, i8* %37, align 16, !tbaa !5, !range !9
    Value *val38 = builder.CreateLoad(builder.getInt8Ty(), val37)->setAlignment(Align(16));
//            %39 = icmp eq i8 %38, 0
    Value *val39 = builder.CreateICmpEQ(val38, builder.getInt8(0));
//            %40 = icmp eq i32 %36, 3
    Value *val40 = builder.CreateICmpEQ(val36, builder.getInt32(3));
//            %41 = select i1 %39, i1 %40, i1 false
    Value *val41 = builder.CreateSelect(val39, val40,
                                       builder.getInt1(false));
//            br i1 %41, label %48, label %42
    builder.CreateCondBr(val41, BB48, BB42);
//
    builder.SetInsertPoint(BB42);
//        42:                                               ; preds = %35
//            %43 = xor i1 %39, true
    Value *val43 = builder.CreateXor(val39, builder.getInt1(true));
//            %44 = and i32 %36, -2
    Value *val44 = builder.CreateAnd(val36, builder.getInt32(-2));

//            %45 = icmp eq i32 %44, 2
    Value *val45 = builder.CreateICmpEQ(val44, builder.getInt32(2));
//            %46 = select i1 %43, i1 %45, i1 false
    Value *val46 = builder.CreateSelect(val43, val45,
                                       builder.getInt1(false));
//            %47 = zext i1 %46 to i8
    Value *val47 = builder.CreateZExt(val46, Type::getInt8Ty(context));
//            br label %48
    builder.CreateBr(BB48);
//
    builder.SetInsertPoint(BB48);

//        48:                                               ; preds = %42, %35
//            %49 = phi i8 [ 1, %35 ], [ %47, %42 ]
    PHINode *val49 = builder.CreatePHI(builder.getInt8Ty(), 2);
    val49->addIncoming(builder.getInt8(1), BB35);
    val49->addIncoming(val47, BB42);
//            %50 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %7, i64 0
//            store i8 %49, i8* %50, align 16, !tbaa !5
    builder.CreateStore(val49, val50)->setAlignment(Align(1));

//            br label %53
    builder.CreateBr(BB53);
//
    builder.SetInsertPoint(BB51);
//        51:                                               ; preds = %124
//            %52 = icmp eq i64 %11, 512
    Value *val52 = builder.CreateICmpEQ(val11, builder.getInt64(512));
//            br i1 %52, label %129, label %6, !llvm.loop !10
    builder.CreateCondBr(val52, BB129, BB6);
//
    builder.SetInsertPoint(BB53);
//        53:                                               ; preds = %124, %48
//            %54 = phi i64 [ 1, %48 ], [ %127, %124 ]
    PHINode *val54 = builder.CreatePHI(builder.getInt64Ty(), 2);
    val54->addIncoming(builder.getInt64(1), BB48);
//            br i1 %8, label %61, label %55
    builder.CreateCondBr(val8, BB61, BB55);
//
    builder.SetInsertPoint(BB55);
//        55:                                               ; preds = %53
//            %56 = add nuw nsw i64 %54, 4294967295
    Value *val56 = builder.CreateAdd(val54, builder.getInt64(4294967295), "", true, true);
//            %57 = and i64 %56, 4294967295
    Value *val57 = builder.CreateAnd(val56, builder.getInt64(4294967295));
//            %58 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %57
//            %59 = load i8, i8* %58, align 1, !tbaa !5, !range !9
    Value *val59 = builder.CreateLoad(builder.getInt8Ty(), val58)->setAlignment(Align(1));
//            %60 = zext i8 %59 to i32
    Value *val60 = builder.CreateZExt(val59, Type::getInt32Ty(context));
//            br label %61
    builder.CreateBr(BB61);
//
    builder.SetInsertPoint(BB61);
//        61:                                               ; preds = %53, %55
//            %62 = phi i32 [ 0, %53 ], [ %60, %55 ]
    PHINode *val62 = builder.CreatePHI(builder.getInt32Ty(), 2);
    val62->addIncoming(builder.getInt32(0), BB93);
    val62->addIncoming(val60, BB105);
//            br i1 %8, label %76, label %63
    builder.CreateCondBr(val8, BB76, BB63);
//
    builder.SetInsertPoint(BB63);
//        63:                                               ; preds = %61
//            %64 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %54
//            %65 = load i8, i8* %64, align 1, !tbaa !5, !range !9
    Value *val65 = builder.CreateLoad(builder.getInt8Ty(), val64)->setAlignment(Align(1));

//            %66 = zext i8 %65 to i32
    Value *val66 = builder.CreateZExt(val65, Type::getInt32Ty(context));
//            %67 = add nuw nsw i32 %62, %66
    Value *val67 = builder.CreateAdd(val62, val66, "", true, true);

//            %68 = icmp ugt i64 %54, 254
    Value *val68 = builder.CreateICmpUGT(val54, builder.getInt64(254));
//            %69 = select i1 %68, i1 true, i1 %8
    Value *val69 = builder.CreateSelect(val68, builder.getInt1(true),
                                       val8);
//            br i1 %69, label %76, label %70
    builder.CreateCondBr(val69, BB76, BB70);
//
    builder.SetInsertPoint(BB70);
//        70:                                               ; preds = %63
//            %71 = add nuw nsw i64 %54, 1
    Value *val71 = builder.CreateAdd(val54, builder.getInt64(1), "", true, true);

//            %72 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %71
//            %73 = load i8, i8* %72, align 1, !tbaa !5, !range !9
    Value *val73 = builder.CreateLoad(builder.getInt8Ty(), val72)->setAlignment(Align(1));
//            %74 = zext i8 %73 to i32
    Value *val74 = builder.CreateZExt(val73, Type::getInt32Ty(context));
//            %75 = add nuw nsw i32 %67, %74
    Value *val75 = builder.CreateAdd(val67, val74, "", true, true);
//            br label %76
    builder.CreateBr(BB76);
//
    builder.SetInsertPoint(BB76);
//        76:                                               ; preds = %70, %63, %61
//            %77 = phi i32 [ %67, %63 ], [ %75, %70 ], [ %62, %61 ]
    PHINode *val77 = builder.CreatePHI(builder.getInt32Ty(), 3);
    val77->addIncoming(val67, BB63);
    val77->addIncoming(val75, BB70);
    val77->addIncoming(val62, BB61);
//            %78 = add nuw nsw i64 %54, 4294967295
    Value *val78 = builder.CreateAdd(val54, builder.getInt64(4294967295), "", true, true);
//            %79 = and i64 %78, 4294967295
    Value *val79 = builder.CreateAnd(val78, builder.getInt64(4294967295));
//            %80 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %79
//            %81 = load i8, i8* %80, align 1, !tbaa !5, !range !9
    Value *val81 = builder.CreateLoad(builder.getInt8Ty(), val80)->setAlignment(Align(1));
//            %82 = zext i8 %81 to i32
    Value *val82 = builder.CreateZExt(val81, Type::getInt32Ty(context));
//            %83 = add nuw nsw i32 %77, %82
    Value *val83 = builder.CreateAdd(val77, val82, "", true, true);
//            %84 = icmp ugt i64 %54, 254
    Value *val84 = builder.CreateICmpUGT(val54, builder.getInt64(254));
//            br i1 %84, label %91, label %85
    builder.CreateCondBr(val84, BB91, BB85);
//
    builder.SetInsertPoint(BB85);
//        85:                                               ; preds = %76
//            %86 = add nuw nsw i64 %54, 1
    Value *val86 = builder.CreateAdd(val54, builder.getInt64(1), "", true, true);

//            %87 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %86
//            %88 = load i8, i8* %87, align 1, !tbaa !5, !range !9
    Value *val88 = builder.CreateLoad(builder.getInt8Ty(), val87)->setAlignment(Align(1));
//            %89 = zext i8 %88 to i32
    Value *val89 = builder.CreateZExt(val88, Type::getInt32Ty(context));
//            %90 = add nuw nsw i32 %83, %89
    Value *val90 = builder.CreateAdd(val83, val89, "", true, true);
//            br label %91
    builder.CreateBr(BB91);
//
    builder.SetInsertPoint(BB91);
//        91:                                               ; preds = %85, %76
//            %92 = phi i32 [ %83, %76 ], [ %90, %85 ]
    PHINode *val92 = builder.CreatePHI(builder.getInt32Ty(), 2);
    val92->addIncoming(val83, BB76);
    val92->addIncoming(val90, BB85);
//            br i1 %12, label %111, label %93
    builder.CreateBr(val12, BB111, BB93);
//
    builder.SetInsertPoint(BB93);
//        93:                                               ; preds = %91
//            %94 = add nuw nsw i64 %54, 4294967295
    Value *val94 = builder.CreateAdd(val54, builder.getInt64(4294967295), "", true, true);
//            %95 = and i64 %94, 4294967295
    Value *val95 = builder.CreateAnd(val94, builder.getInt64(4294967295));
//            %96 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %95
//            %97 = load i8, i8* %96, align 1, !tbaa !5, !range !9
    Value *val97 = builder.CreateLoad(builder.getInt8Ty(), val96)->setAlignment(Align(1));
//            %98 = zext i8 %97 to i32
    Value *val98 = builder.CreateZExt(val97, Type::getInt32Ty(context));
//            %99 = add nuw nsw i32 %92, %98
    Value *val99 = builder.CreateAdd(val92, val98, "", true, true);

//            %100 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %54
//            %101 = load i8, i8* %100, align 1, !tbaa !5, !range !9
    Value *val101 = builder.CreateLoad(builder.getInt8Ty(), val100)->setAlignment(Align(1));

//            %102 = zext i8 %101 to i32
    Value *val102 = builder.CreateZExt(val101, Type::getInt32Ty(context));
//            %103 = add nuw nsw i32 %99, %102
    Value *val103 = builder.CreateAdd(val99, val102, "", true, true);

//            %104 = icmp ugt i64 %54, 254
    Value *val104 = builder.CreateICmpUGT(val54, builder.getInt64(254));
//            br i1 %104, label %111, label %105
    builder.CreateCondBr(val104, BB111, BB105);
//
    builder.SetInsertPoint(BB105);
//        105:                                              ; preds = %93
//            %106 = add nuw nsw i64 %54, 1
    Value *val106 = builder.CreateAdd(val54, builder.getInt64(1), "", true, true);
//            %107 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %106
//            %108 = load i8, i8* %107, align 1, !tbaa !5, !range !9
    Value *val108 = builder.CreateLoad(builder.getInt8Ty(), val107)->setAlignment(Align(1));
//            %109 = zext i8 %108 to i32
    Value *val109 = builder.CreateZExt(val108, Type::getInt32Ty(context));
//            %110 = add nuw nsw i32 %103, %109
    Value *val110 = builder.CreateAdd(val103, val109, "", true, true);
//            br label %111
    builder.CreateBr(BB111);
//
    builder.SetInsertPoint(BB111);
//        111:                                              ; preds = %91, %105, %93
//            %112 = phi i32 [ %103, %93 ], [ %110, %105 ], [ %92, %91 ]
    PHINode *val112 = builder.CreatePHI(builder.getInt32Ty(), 3);
    val112->addIncoming(val103, BB93);
    val112->addIncoming(val110, BB105);
    val112->addIncoming(val92, BB91);

//            %113 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %54
//            %114 = load i8, i8* %113, align 1, !tbaa !5, !range !9
    Value *val114 = builder.CreateLoad(builder.getInt8Ty(), val113)->setAlignment(Align(1));

//            %115 = icmp eq i8 %114, 0
    Value *val115 = builder.CreateICmpEQ(val114, builder.getInt8(0));
//            %116 = icmp eq i32 %112, 3
    Value *val116 = builder.CreateICmpEQ(val112, builder.getInt32(3));
//            %117 = select i1 %115, i1 %116, i1 false
    Value *val117 = builder.CreateSelect(val115, val116,
                                       builder.getInt1(false));
//            br i1 %117, label %124, label %118
    builder.CreateCondBr(val117, BB124, BB118);
//
    builder.SetInsertPoint(BB118);
//        118:                                              ; preds = %111
//            %119 = xor i1 %115, true
    Value *value119 = builder.CreateXor(val115, builder.getInt1(true));
//            %120 = and i32 %112, -2
    Value *val120 = builder.CreateAnd(val112, builder.getInt32(-2));
//            %121 = icmp eq i32 %120, 2
    Value *val121 = builder.CreateICmpEQ(val120, builder.getInt32(2));
//            %122 = select i1 %119, i1 %121, i1 false
    Value *val122 = builder.CreateSelect(val119, val121,
                                       builder.getInt1(false));
//            %123 = zext i1 %122 to i8
    Value *val123 = builder.CreateZExt(val122, Type::getInt8Ty(context));
//            br label %124
    builder.CreateBr(BB124);
//
    builder.SetInsertPoint(BB124);
//        124:                                              ; preds = %118, %111
//            %125 = phi i8 [ 1, %111 ], [ %123, %118 ]
    PHINode *val125 = builder.CreatePHI(builder.getInt8Ty(), 2);
    val125->addIncoming(builder.getInt8(1), BB111);
    val125->addIncoming(val123, BB111);

//            %126 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %7, i64 %54
//            store i8 %125, i8* %126, align 1, !tbaa !5
    builder.CreateStore(val125, val126)->setAlignment(Align(1));
//            %127 = add nuw nsw i64 %54, 1
    Value *val127 = builder.CreateAdd(val54, builder.getInt64(1), "", true, true);
    val54->addIncoming(val127, BB124);

//            %128 = icmp eq i64 %127, 256
    Value *val128 = builder.CreateICmpEQ(val127, builder.getInt64(256));
//            br i1 %128, label %51, label %53, !llvm.loop !12
    builder.CreateCondBr(val128, BB51, BB53);
//
    builder.SetInsertPoint(BB129);
//        129:                                              ; preds = %51, %136
//            %130 = phi i64 [ %137, %136 ], [ 0, %51 ]
    PHINode *val130 = builder.CreatePHI(builder.getInt32Ty(), 2);
    val130->addIncoming(builder.getInt64(0), BB51);
//            %131 = trunc i64 %130 to i32
    Value *val131 = builder.CreateTrunc(val130, Type::getInt32Ty(context));
//            %132 = trunc i64 %130 to i32
    Value *val132 = builder.CreateTrunc(val130, Type::getInt32Ty(context));
//            br label %139
    builder.CreateBr(BB139);
//
    builder.SetInsertPoint(BB133);
//        133:                                              ; preds = %136
//            tail call void (...) @simFlush() #3
    builder.CreateCall(simFlushFunc, noArgs);
//            %134 = add nuw nsw i32 %4, 1
    Value *val134 = builder.CreateAdd(val4, builder.getInt32(1), "", true, true);
    val4->addIncoming(val134, BB133);
//            %135 = icmp eq i32 %134, 1000
    Value *val135 = builder.CreateICmpEQ(val134, builder.getInt32(1000));
//            br i1 %135, label %5, label %3, !llvm.loop !14
    builder.CreateCondBr(val135, BB5, BB3);
//
    builder.SetInsertPoint(BB136);
//        136:                                              ; preds = %147
//            %137 = add nuw nsw i64 %130, 1
    Value *val137 = builder.CreateAdd(val130, builder.getInt64(1), "", true, true);
    val130->addIncoming(val137, BB136);

//            %138 = icmp eq i64 %137, 512
    Value *val138 = builder.CreateICmpEQ(val137, builder.getInt64(512));
//            br i1 %138, label %133, label %129, !llvm.loop !15
    builder.CreateCondBr(val138, BB133, BB129);
//
    builder.SetInsertPoint(BB139);
//        139:                                              ; preds = %129, %147
//            %140 = phi i64 [ 0, %129 ], [ %149, %147 ]
    PHINode *val140 = builder.CreatePHI(builder.getInt64Ty(), 2);
    val140->addIncoming(builder.getInt64(0), BB129);
//            %141 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %130, i64 %140
//            %142 = load i8, i8* %141, align 1, !tbaa !5, !range !9
    Value *val142 = builder.CreateLoad(builder.getInt8Ty(), val141)->setAlignment(Align(1));
//            %143 = icmp eq i8 %142, 0
    Value *val143 = builder.CreateICmpEQ(val142, builder.getInt8(0));
//            %144 = trunc i64 %140 to i32
    Value *val144 = builder.CreateTrunc(val140, Type::getInt32Ty(context));
//            br i1 %143, label %146, label %145
    builder.CreateCondBr(val143, BB146, BB145);
//
    builder.SetInsertPoint(BB145);
//        145:                                              ; preds = %139
//            tail call void @simPutPixel(i32 noundef %131, i32 noundef %144, i32 noundef 16777215) #3
    Value *simPutPixelParams1[] = {val131, val144, builder.getInt32(16777215)};
    builder.CreateCall(simPutPixelFunc, simPutPixelParams1);
//            br label %147
    builder.CreateBr(BB147);
//
    builder.SetInsertPoint(BB146);
//        146:                                              ; preds = %139
//            tail call void @simPutPixel(i32 noundef %132, i32 noundef %144, i32 noundef 0) #3
    builder.CreateCall(simPutPixelFunc, simPutPixelParamTypes);
//            br label %147
    builder.CreateBr(BB147);
//
    builder.SetInsertPoint(BB147);
//        147:                                              ; preds = %146, %145
//            %148 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %130, i64 %140
//            store i8 %142, i8* %148, align 1, !tbaa !5
    builder.CreateStore(val142, val148)->setAlignment(Align(1));
//            %149 = add nuw nsw i64 %140, 1
    Value *val149 = builder.CreateAdd(val140, builder.getInt64(1), "", true, true);
    val140->addIncoming(val149, BB147);

//            %150 = icmp eq i64 %149, 256
    Value *val150 = builder.CreateICmpEQ(val149, builder.getInt64(256));
//        br i1 %150, label %136, label %139, !llvm.loop !16
    builder.CreateCondBr(val150, BB136, BB139);

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