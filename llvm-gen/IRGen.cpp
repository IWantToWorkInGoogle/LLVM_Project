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
    FunctionCalle simPutPixelFunc = module->getOrInsertFunction("simPutPixel", simPutPixelType);
// declare dso_local void @simExit()
    FunctionType *simExitType = FunctionType::get(voidType, noArgs, false);
    FunctionCallee simExitFunc = module->getOrInsertFunction("simExit", simExitType);

// declare dso_local i32 @simRand()
    FunctionType *simRandType = FunctionType::get(i32Type, noArgs, false);
    FunctionCallee simRandFunc = module->getOrInsertFunction("simRand", simRandType);

//    define void @app() local_unnamed_addr #0 {
    FunctionType *appType = FunctionType::get(builder.getVoidTy(), false);
    Function *appFunc = Function::Create(appType, Function::ExternalLinkage, "app", module);
    {
        BasicBlock *BB0 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB2 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB4 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB5 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB12 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB14 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB20 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB25 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB26 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB34 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB40 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB42 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB48 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB51 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB57 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB59 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB60 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB66 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB72 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB78 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB85 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB91 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB96 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB99 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB102 = BasicBlock::Create(context, "", appFunc);
        BasicBlock *BB105 = BasicBlock::Create(context, "", appFunc);

        //define void @app() local_unnamed_addr #0 {
        //    %1 = alloca [512 x [256 x i8]], align 1
        //    call void @llvm.lifetime.start.p0(i64 131072, ptr nonnull %1) #3
        //    br label %2
        builder.CreateCondBr(BB2);

//        2:                                                ; preds = %0, %99
        builder.SetInsertPoint(BB2);
//            %3 = phi i32 [ 0, %0 ], [ %100, %99 ]
//            br label %5
        builder.CreateCondBr(BB5);

//        4:                ; preds = %99
        builder.SetInsertPoint(BB4);
//        call void @llvm.lifetime.end.p0(i64 131072, ptr nonnull %1) #3
//        ret void
        builder.CreateRetVoid();

//        5:                                                ; preds = %2, %12
        builder.SetInsertPoint(BB5);
//            %6 = phi i64 [ 0, %2 ], [ %10, %12 ]
        PHINode *val6 = builder.CreateePHI(builder.get64Ty(), 2);
        val6->addIncoming(builder.getInt32(0), BB0);
//            %7 = icmp eq i64 %6, 0
        Value *val7 = builder.CreateICmpEQ(val6, builder.getInt32(0));
//            %8 = add nuw i64 %6, 4294967295
//            %9 = and i64 %8, 4294967295
        Value *val9 = builder.CreateAnd(val8, builder.getInt64(4294967295));
//            %10 = add nuw nsw i64 %6, 1
        Value *val10 = builder.CreateAdd(val6, builder.getInt64(1), "", true, true);
//            %11 = icmp ugt i64 %6, 510
        Value *val11 = builder.CreateICmpUGT(val6, builder.getInt64(510));
//            br label %14
        builder.CreateCondBr(BB14);

//        12:                                               ; preds = %91
        builder.SetInsertPoint(BB12);
//            %13 = icmp eq i64 %10, 512
        Value *val13 = builder.CreateICmpEQ(val10, builder.getInt32(512));
//            br i1 %13, label %96, label %5, !llvm.loop !6
        builder.CreateCondBr(val13, BB96, BB5);
//
//        14:                                               ; preds = %91, %5
        builder.SetInsertPoint(BB14);
//            %15 = phi i64 [ 0, %5 ], [ %94, %91 ]
//            %16 = trunc i64 %15 to i32
        Value *val16 = builder.CreateTrunc(val15, Type::getInt64Ty(context));
//            %17 = add i32 %16, -1
        Value *val17 = builder.CreateAdd(val16, builder.getInt32(-1));
//            %18 = icmp ugt i32 %17, 255
        Value *val18 = builder.CreateICmpUGT(val17, builder.getInt32(255));

//            %19 = select i1 %18, i1 true, i1 %7
        Value *val19 = builder.CreateSelect(val18, builder.getInt1(true),
                                           val7);
//            br i1 %19, label %25, label %20
        builder.CreateCondBr(val19, BB25, BB20);
//
//        20:                                               ; preds = %14
        builder.SetInsertPoint(BB20);
//            %21 = zext i32 %17 to i64
        Value *val21 = builder.CreateZExt(val17, Type::getInt64Ty(context));
//            %22 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %21
//            %23 = load i8, ptr %22, align 1, !tbaa !8, !range !12
        Value *val23 = builder.CreateLoad(ptr, "loaded_value");
//            %24 = zext i8 %23 to i32
        Value *val24 = builder.CreateZExt(val23, Type::getInt32Ty(context));
//            br label %26
        builder.CreateCondBr(BB26);
//
//        25:                                               ; preds = %14
        builder.SetInsertPoint(BB25);
//            br i1 %7, label %40, label %26
        builder.CreateCondBr(val7, BB40, BB26);
//
//        26:                                               ; preds = %25, %20
        builder.SetInsertPoint(BB26);
//            %27 = phi i32 [ %24, %20 ], [ 0, %25 ]
//            %28 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %15
//            %29 = load i8, ptr %28, align 1, !tbaa !8, !range !12
//            %30 = zext i8 %29 to i32
        Value *val30 = builder.CreateZExt(val29, Type::getInt32Ty(context));
//            %31 = add nuw nsw i32 %27, %30
        Value *val31 = builder.CreateAdd(val27, val30, "", true, true);
//            %32 = icmp ugt i64 %15, 254
        Value *val32 = builder.CreateICmpUGT(val15, builder.getInt64(254));
//            %33 = select i1 %32, i1 true, i1 %7
        Value *val33 = builder.CreateSelect(val32, builder.getInt1(true),
                                            val7);
//            br i1 %33, label %40, label %34
        builder.CreateCondBr(val33, BB40, BB34);
//
//        34:                                               ; preds = %26
        builder.SetInsertPoint(BB34);
//            %35 = add nuw nsw i64 %15, 1
        Value *val35 = builder.CreateAdd(val15, builder.getInt64(1), "", true, true);
//            %36 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %35
//            %37 = load i8, ptr %36, align 1, !tbaa !8, !range !12
//            %38 = zext i8 %37 to i32
        Value *val38 = builder.CreateZExt(val37, Type::getInt32Ty(context));
//            %39 = add nuw nsw i32 %31, %38
        Value *val39 = builder.CreateAdd(val31, val38, "", true, true);
//            br label %40
        builder.CreateCondBr(BB40);
//
//        40:                                               ; preds = %25, %26, %34
        builder.SetInsertPoint(BB40);
//            %41 = phi i32 [ %31, %26 ], [ %39, %34 ], [ 0, %25 ]
//            br i1 %18, label %48, label %42
        builder.CreateCondBr(val18, BB48, BB42);
//
//        42:                                               ; preds = %40
        builder.SetInsertPoint(BB42);
//            %43 = zext i32 %17 to i64
//            %44 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %43
//            %45 = load i8, ptr %44, align 1, !tbaa !8, !range !12
//            %46 = zext i8 %45 to i32
        Value *val46 = builder.CreateZExt(val45, Type::getInt32Ty(context));
//            %47 = add nuw nsw i32 %41, %46
        Value *val47 = builder.CreateAdd(val41, val46, "", true, true);
//            br label %48
        builder.CreateCondBr(BB48);
//
//        48:                                               ; preds = %42, %40
        builder.SetInsertPoint(BB48);
//            %49 = phi i32 [ %41, %40 ], [ %47, %42 ]
//            %50 = icmp ugt i64 %15, 254
        Value *val50 = builder.CreateICmpUGT(val15, builder.getInt64(254));

//            br i1 %50, label %57, label %51
        builder.CreateCondBr(val50, BB57, BB51);
//
//        51:                                               ; preds = %48
        builder.SetInsertPoint(BB51);
//            %52 = add nuw nsw i64 %15, 1
        Value *val52 = builder.CreateAdd(val15, builder.getInt64(1), "", true, true);
//            %53 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %52
//            %54 = load i8, ptr %53, align 1, !tbaa !8, !range !12
//            %55 = zext i8 %54 to i32
        Value *val55 = builder.CreateZExt(val54, Type::getInt32Ty(context));
//            %56 = add nuw nsw i32 %49, %55
        Value *val56 = builder.CreateAdd(val49, val55, "", true, true);
//            br label %57
        builder.CreateCondBr(BB57);
//
//        57:                                               ; preds = %51, %48
        builder.SetInsertPoint(BB57);
//            %58 = phi i32 [ %49, %48 ], [ %56, %51 ]
//            br i1 %11, label %78, label %59
        builder.CreateCondBr(val11, BB78, BB59);
//
//        59:                                               ; preds = %57
        builder.SetInsertPoint(BB59);
//            br i1 %18, label %66, label %60
        builder.CreateCondBr(val18, BB66, BB60);
//
//        60:                                               ; preds = %59
        builder.SetInsertPoint(BB60);
//            %61 = zext i32 %17 to i64
        Value *val61 = builder.CreateZExt(val17, Type::getInt64Ty(context));
//            %62 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %61
//            %63 = load i8, ptr %62, align 1, !tbaa !8, !range !12
//            %64 = zext i8 %63 to i32
        Value *val64 = builder.CreateZExt(val63, Type::getInt32Ty(context));
//            %65 = add nuw nsw i32 %58, %64
        Value *val65 = builder.CreateAdd(val58, val64, "", true, true);
//            br label %66
        builder.CreateCondBr(BB66);
//
//        66:                                               ; preds = %59, %60
        builder.SetInsertPoint(BB66);
//            %67 = phi i32 [ %65, %60 ], [ %58, %59 ]
//            %68 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %15
//            %69 = load i8, ptr %68, align 1, !tbaa !8, !range !12
//            %70 = zext i8 %69 to i32
        Value *val70 = builder.CreateZExt(val69, Type::getInt32Ty(context));
//            %71 = add nuw nsw i32 %67, %70
        Value *val71 = builder.CreateAdd(val67, val70, "", true, true);
//            br i1 %50, label %78, label %72
        builder.CreateCondBr(val50, BB78, BB72);
//
//        72:                                               ; preds = %66
        builder.SetInsertPoint(BB72);
//            %73 = add nuw nsw i64 %15, 1
        Value *val73 = builder.CreateAdd(val15, builder.getInt64(1), "", true, true);
//            %74 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %73
//            %75 = load i8, ptr %74, align 1, !tbaa !8, !range !12
//            %76 = zext i8 %75 to i32
        Value *val76 = builder.CreateZExt(val75, Type::getInt32Ty(context));
//            %77 = add nuw nsw i32 %71, %76
        Value *val77 = builder.CreateAdd(val71, val76, "", true, true);
//            br label %78
        builder.CreateCondBr(BB78);
//
//        78:                                               ; preds = %57, %72, %66
        builder.SetInsertPoint(BB78);
//            %79 = phi i32 [ %71, %66 ], [ %77, %72 ], [ %58, %57 ]
//            %80 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %15
//            %81 = load i8, ptr %80, align 1, !tbaa !8, !range !12
//            %82 = icmp eq i8 %81, 0
        Value *val82 = builder.CreateICmpEQ(val81, builder.getInt8(0));

//            %83 = icmp eq i32 %79, 3
        Value *val83 = builder.CreateICmpEQ(val79, builder.getInt32(3));
//            %84 = select i1 %82, i1 %83, i1 false
        Value *val84 = builder.CreateSelect(val82, val83,
                                           builder.getInt1(false));
//            br i1 %84, label %91, label %85
        builder.CreateCondBr(val84, BB91, BB85);
//
//        85:                                               ; preds = %78
        builder.SetInsertPoint(BB85);
//            %86 = xor i1 %82, true
//            %87 = and i32 %79, -2
        Value *val87 = builder.CreateAnd(val79, builder.getInt32(-2));
//            %88 = icmp eq i32 %87, 2
        Value *val88 = builder.CreateICmpEQ(val87, builder.getInt32(2));
//            %89 = select i1 %86, i1 %88, i1 false
        Value *val89 = builder.CreateSelect(val86, val88,
                                           builder.getInt1(false));
//            %90 = zext i1 %89 to i8
        Value *val90 = builder.CreateZExt(val89, Type::getInt8Ty(context));
//            br label %91
        builder.CreateCondBr(BB91);
//
//        91:                                               ; preds = %85, %78
        builder.SetInsertPoint(BB91);
//            %92 = phi i8 [ 1, %78 ], [ %90, %85 ]
//            %93 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %6, i64 %15
//            store i8 %92, ptr %93, align 1, !tbaa !8
//            %94 = add nuw nsw i64 %15, 1
        Value *val94 = builder.CreateAdd(val15, builder.getInt64(1), "", true, true);
//            %95 = icmp eq i64 %94, 256
        Value *val95 = builder.CreateICmpEQ(val94, builder.getInt64(256));
//            br i1 %95, label %12, label %14, !llvm.loop !13
        builder.CreateCondBr(val95, BB12, BB14);
//
//        96:                                               ; preds = %12, %102
        builder.SetInsertPoint(BB91);
//            %97 = phi i64 [ %103, %102 ], [ 0, %12 ]
//            %98 = trunc i64 %97 to i32
        Value *val98 = builder.CreateTrunc(val97, Type::getInt64Ty(context));
//            br label %105
        builder.CreateCondBr(BB105);
//
//        99:                                               ; preds = %102
        builder.SetInsertPoint(BB99);
//            tail call void @simFlush() #3
//            %100 = add nuw nsw i32 %3, 1
        Value *val100 = builder.CreateAdd(val32, builder.getInt32(1), "", true, true);
//            %101 = icmp eq i32 %100, 1000
        Value *val101 = builder.CreateICmpEQ(val100, builder.getInt32(1000));
//            br i1 %101, label %4, label %2, !llvm.loop !14
        builder.CreateCondBr(val101, BB4, BB2);
//
//
        builder.SetInsertPoint(BB102);
//
//        102:                                              ; preds = %105
//            %103 = add nuw nsw i64 %97, 1
        Value *val103 = builder.CreateAdd(val97, builder.getInt64(1), "", true, true);
//            %104 = icmp eq i64 %103, 512
        Value *val104 = builder.CreateICmpEQ(val103, builder.getInt64(512));
//            br i1 %104, label %99, label %96, !llvm.loop !15
        builder.CreateCondBr(val104, BB99, BB96);
//
//        105:                                              ; preds = %96, %105
        builder.SetInsertPoint(BB105);
//            %106 = phi i64 [ 0, %96 ], [ %113, %105 ]
//            %107 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %97, i64 %106
//            %108 = load i8, ptr %107, align 1, !tbaa !8, !range !12
//            %109 = icmp eq i8 %108, 0
        Value *val109 = builder.CreateICmpEQ(val108, builder.getInt8(0));
//            %110 = trunc i64 %106 to i32
        Value *val110 = builder.CreateTrunc(val106, Type::getInt64Ty(context));
//            %111 = select i1 %109, i32 0, i32 16777215
        Value *val111 = builder.CreateSelect(val109, builder.getInt32(0),
                                           builder.getInt32(16777215));
//            tail call void @simPutPixel(i32 noundef %98, i32 noundef %110, i32 noundef %111) #3
//            %112 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %97, i64 %106
//            store i8 %108, ptr %112, align 1, !tbaa !8
//            %113 = add nuw nsw i64 %106, 1
        Value *val113 = builder.CreateAdd(val106, builder.getInt64(1), "", true, true);
//            %114 = icmp eq i64 %113, 256
        Value *val114 = builder.CreateICmpEQ(val113, builder.getInt64(0));
//            br i1 %114, label %102, label %105, !llvm.loop !16
        builder.CreateCondBr(val114, BB102, BB105);
    }


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