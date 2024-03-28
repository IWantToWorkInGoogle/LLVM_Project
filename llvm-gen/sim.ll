; ModuleID = '../src/sim.c'
source_filename = "../src/sim.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

%union.SDL_Event = type { %struct.SDL_SensorEvent, [8 x i8] }
%struct.SDL_SensorEvent = type { i32, i32, i32, [6 x float], i64 }

@state = common global [512 x [256 x i8]] zeroinitializer, align 1
@Window = internal global ptr null, align 8
@Renderer = internal global ptr null, align 8
@.str = private unnamed_addr constant [20 x i8] c"User-requested quit\00", align 1
@__func__.simFlush = private unnamed_addr constant [9 x i8] c"simFlush\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"sim.c\00", align 1
@.str.2 = private unnamed_addr constant [60 x i8] c"SDL_TRUE != SDL_HasEvent(SDL_QUIT) && \22User-requested quit\22\00", align 1
@Ticks = internal global i32 0, align 4
@.str.3 = private unnamed_addr constant [13 x i8] c"Out of range\00", align 1
@__func__.simPutPixel = private unnamed_addr constant [12 x i8] c"simPutPixel\00", align 1
@.str.4 = private unnamed_addr constant [43 x i8] c"0 <= x && x < SIM_X_SIZE && \22Out of range\22\00", align 1
@.str.5 = private unnamed_addr constant [43 x i8] c"0 <= y && y < SIM_Y_SIZE && \22Out of range\22\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @setDead(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6
  %8 = load i32, ptr %4, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [256 x i8], ptr %7, i64 0, i64 %9
  store i8 0, ptr %10, align 1
  %11 = load i32, ptr %3, align 4
  %12 = load i32, ptr %4, align 4
  call void @simPutPixel(i32 noundef %11, i32 noundef %12, i32 noundef 16777215)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @simPutPixel(i32 noundef %0, i32 noundef %1, i32 noundef %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i8, align 1
  %8 = alloca i8, align 1
  %9 = alloca i8, align 1
  %10 = alloca i8, align 1
  store i32 %0, ptr %4, align 4
  store i32 %1, ptr %5, align 4
  store i32 %2, ptr %6, align 4
  %11 = load i32, ptr %4, align 4
  %12 = icmp sle i32 0, %11
  br i1 %12, label %13, label %17

13:                                               ; preds = %3
  %14 = load i32, ptr %4, align 4
  %15 = icmp slt i32 %14, 512
  br i1 %15, label %16, label %17

16:                                               ; preds = %13
  br label %17

17:                                               ; preds = %16, %13, %3
  %18 = phi i1 [ false, %13 ], [ false, %3 ], [ true, %16 ]
  %19 = xor i1 %18, true
  %20 = zext i1 %19 to i32
  %21 = sext i32 %20 to i64
  %22 = icmp ne i64 %21, 0
  br i1 %22, label %23, label %25

23:                                               ; preds = %17
  call void @__assert_rtn(ptr noundef @__func__.simPutPixel, ptr noundef @.str.1, i32 noundef 82, ptr noundef @.str.4) #3
  unreachable

24:                                               ; No predecessors!
  br label %26

25:                                               ; preds = %17
  br label %26

26:                                               ; preds = %25, %24
  %27 = load i32, ptr %5, align 4
  %28 = icmp sle i32 0, %27
  br i1 %28, label %29, label %33

29:                                               ; preds = %26
  %30 = load i32, ptr %5, align 4
  %31 = icmp slt i32 %30, 256
  br i1 %31, label %32, label %33

32:                                               ; preds = %29
  br label %33

33:                                               ; preds = %32, %29, %26
  %34 = phi i1 [ false, %29 ], [ false, %26 ], [ true, %32 ]
  %35 = xor i1 %34, true
  %36 = zext i1 %35 to i32
  %37 = sext i32 %36 to i64
  %38 = icmp ne i64 %37, 0
  br i1 %38, label %39, label %41

39:                                               ; preds = %33
  call void @__assert_rtn(ptr noundef @__func__.simPutPixel, ptr noundef @.str.1, i32 noundef 83, ptr noundef @.str.5) #3
  unreachable

40:                                               ; No predecessors!
  br label %42

41:                                               ; preds = %33
  br label %42

42:                                               ; preds = %41, %40
  %43 = load i32, ptr %6, align 4
  %44 = ashr i32 %43, 24
  %45 = trunc i32 %44 to i8
  store i8 %45, ptr %7, align 1
  %46 = load i32, ptr %6, align 4
  %47 = ashr i32 %46, 16
  %48 = and i32 %47, 255
  %49 = trunc i32 %48 to i8
  store i8 %49, ptr %8, align 1
  %50 = load i32, ptr %6, align 4
  %51 = ashr i32 %50, 8
  %52 = and i32 %51, 255
  %53 = trunc i32 %52 to i8
  store i8 %53, ptr %9, align 1
  %54 = load i32, ptr %6, align 4
  %55 = and i32 %54, 255
  %56 = trunc i32 %55 to i8
  store i8 %56, ptr %10, align 1
  %57 = load ptr, ptr @Renderer, align 8
  %58 = load i8, ptr %8, align 1
  %59 = load i8, ptr %9, align 1
  %60 = load i8, ptr %10, align 1
  %61 = load i8, ptr %7, align 1
  %62 = call i32 @SDL_SetRenderDrawColor(ptr noundef %57, i8 noundef zeroext %58, i8 noundef zeroext %59, i8 noundef zeroext %60, i8 noundef zeroext %61)
  %63 = load ptr, ptr @Renderer, align 8
  %64 = load i32, ptr %4, align 4
  %65 = load i32, ptr %5, align 4
  %66 = call i32 @SDL_RenderDrawPoint(ptr noundef %63, i32 noundef %64, i32 noundef %65)
  %67 = call i32 @SDL_GetTicks()
  store i32 %67, ptr @Ticks, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @setAlive(i32 noundef %0, i32 noundef %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  store i32 %1, ptr %4, align 4
  %5 = load i32, ptr %3, align 4
  %6 = sext i32 %5 to i64
  %7 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6
  %8 = load i32, ptr %4, align 4
  %9 = sext i32 %8 to i64
  %10 = getelementptr inbounds [256 x i8], ptr %7, i64 0, i64 %9
  store i8 1, ptr %10, align 1
  %11 = load i32, ptr %3, align 4
  %12 = load i32, ptr %4, align 4
  call void @simPutPixel(i32 noundef %11, i32 noundef %12, i32 noundef 0)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @simSetRender() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  br label %4

4:                                                ; preds = %27, %0
  %5 = load i32, ptr %1, align 4
  %6 = icmp slt i32 %5, 512
  br i1 %6, label %7, label %30

7:                                                ; preds = %4
  store i32 0, ptr %2, align 4
  br label %8

8:                                                ; preds = %23, %7
  %9 = load i32, ptr %2, align 4
  %10 = icmp slt i32 %9, 256
  br i1 %10, label %11, label %26

11:                                               ; preds = %8
  %12 = call i32 @simRand()
  %13 = srem i32 %12, 5
  store i32 %13, ptr %3, align 4
  %14 = load i32, ptr %3, align 4
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %16, label %19

16:                                               ; preds = %11
  %17 = load i32, ptr %1, align 4
  %18 = load i32, ptr %2, align 4
  call void @setDead(i32 noundef %17, i32 noundef %18)
  br label %22

19:                                               ; preds = %11
  %20 = load i32, ptr %1, align 4
  %21 = load i32, ptr %2, align 4
  call void @setAlive(i32 noundef %20, i32 noundef %21)
  br label %22

22:                                               ; preds = %19, %16
  br label %23

23:                                               ; preds = %22
  %24 = load i32, ptr %2, align 4
  %25 = add nsw i32 %24, 1
  store i32 %25, ptr %2, align 4
  br label %8, !llvm.loop !6

26:                                               ; preds = %8
  br label %27

27:                                               ; preds = %26
  %28 = load i32, ptr %1, align 4
  %29 = add nsw i32 %28, 1
  store i32 %29, ptr %1, align 4
  br label %4, !llvm.loop !8

30:                                               ; preds = %4
  call void @simFlush()
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @simInit() #0 {
  %1 = call i32 @SDL_Init(i32 noundef 32)
  %2 = call i32 @SDL_CreateWindowAndRenderer(i32 noundef 512, i32 noundef 256, i32 noundef 0, ptr noundef @Window, ptr noundef @Renderer)
  %3 = load ptr, ptr @Renderer, align 8
  %4 = call i32 @SDL_SetRenderDrawColor(ptr noundef %3, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0)
  %5 = call i64 @time(ptr noundef null)
  %6 = trunc i64 %5 to i32
  call void @srand(i32 noundef %6)
  call void @simSetRender()
  %7 = load ptr, ptr @Renderer, align 8
  %8 = call i32 @SDL_RenderClear(ptr noundef %7)
  ret void
}

declare i32 @SDL_Init(i32 noundef) #1

declare i32 @SDL_CreateWindowAndRenderer(i32 noundef, i32 noundef, i32 noundef, ptr noundef, ptr noundef) #1

declare i32 @SDL_SetRenderDrawColor(ptr noundef, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext) #1

declare void @srand(i32 noundef) #1

declare i64 @time(ptr noundef) #1

declare i32 @SDL_RenderClear(ptr noundef) #1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @simExit() #0 {
  %1 = alloca %union.SDL_Event, align 8
  br label %2

2:                                                ; preds = %0, %9
  %3 = call i32 @SDL_PollEvent(ptr noundef %1)
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %5, label %9

5:                                                ; preds = %2
  %6 = load i32, ptr %1, align 8
  %7 = icmp eq i32 %6, 256
  br i1 %7, label %8, label %9

8:                                                ; preds = %5
  br label %10

9:                                                ; preds = %5, %2
  br label %2

10:                                               ; preds = %8
  %11 = load ptr, ptr @Renderer, align 8
  call void @SDL_DestroyRenderer(ptr noundef %11)
  %12 = load ptr, ptr @Window, align 8
  call void @SDL_DestroyWindow(ptr noundef %12)
  call void @SDL_Quit()
  ret void
}

declare i32 @SDL_PollEvent(ptr noundef) #1

declare void @SDL_DestroyRenderer(ptr noundef) #1

declare void @SDL_DestroyWindow(ptr noundef) #1

declare void @SDL_Quit() #1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  call void @simInit()
  call void @app()
  call void @simExit()
  ret i32 0
}

declare void @app(...) #1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @simFlush() #0 {
  %1 = alloca i32, align 4
  call void @SDL_PumpEvents()
  %2 = call i32 @SDL_HasEvent(i32 noundef 256)
  %3 = icmp ne i32 1, %2
  br i1 %3, label %4, label %5

4:                                                ; preds = %0
  br label %5

5:                                                ; preds = %4, %0
  %6 = phi i1 [ false, %0 ], [ true, %4 ]
  %7 = xor i1 %6, true
  %8 = zext i1 %7 to i32
  %9 = sext i32 %8 to i64
  %10 = icmp ne i64 %9, 0
  br i1 %10, label %11, label %13

11:                                               ; preds = %5
  call void @__assert_rtn(ptr noundef @__func__.simFlush, ptr noundef @.str.1, i32 noundef 71, ptr noundef @.str.2) #3
  unreachable

12:                                               ; No predecessors!
  br label %14

13:                                               ; preds = %5
  br label %14

14:                                               ; preds = %13, %12
  %15 = call i32 @SDL_GetTicks()
  %16 = load i32, ptr @Ticks, align 4
  %17 = sub i32 %15, %16
  store i32 %17, ptr %1, align 4
  %18 = load i32, ptr %1, align 4
  %19 = icmp ult i32 %18, 50
  br i1 %19, label %20, label %23

20:                                               ; preds = %14
  %21 = load i32, ptr %1, align 4
  %22 = sub i32 50, %21
  call void @SDL_Delay(i32 noundef %22)
  br label %23

23:                                               ; preds = %20, %14
  %24 = load ptr, ptr @Renderer, align 8
  call void @SDL_RenderPresent(ptr noundef %24)
  ret void
}

declare void @SDL_PumpEvents() #1

declare i32 @SDL_HasEvent(i32 noundef) #1

; Function Attrs: cold noreturn
declare void @__assert_rtn(ptr noundef, ptr noundef, i32 noundef, ptr noundef) #2

declare i32 @SDL_GetTicks() #1

declare void @SDL_Delay(i32 noundef) #1

declare void @SDL_RenderPresent(ptr noundef) #1

declare i32 @SDL_RenderDrawPoint(ptr noundef, i32 noundef, i32 noundef) #1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @simRand() #0 {
  %1 = call i32 @rand()
  ret i32 %1
}

declare i32 @rand() #1

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #2 = { cold noreturn "disable-tail-calls"="true" "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #3 = { cold noreturn }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 15.0.0 (clang-1500.1.0.2.5)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
