; ModuleID = 'sim.c'
source_filename = "sim.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

%union.SDL_Event = type { %struct.SDL_SensorEvent, [8 x i8] }
%struct.SDL_SensorEvent = type { i32, i32, i32, [6 x float], i64 }

@state = common local_unnamed_addr global [512 x [256 x i8]] zeroinitializer, align 1
@Window = internal global ptr null, align 8
@Renderer = internal global ptr null, align 8
@__func__.simFlush = private unnamed_addr constant [9 x i8] c"simFlush\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"sim.c\00", align 1
@.str.2 = private unnamed_addr constant [60 x i8] c"SDL_TRUE != SDL_HasEvent(SDL_QUIT) && \22User-requested quit\22\00", align 1
@Ticks = internal unnamed_addr global i32 0, align 4
@__func__.simPutPixel = private unnamed_addr constant [12 x i8] c"simPutPixel\00", align 1
@.str.4 = private unnamed_addr constant [43 x i8] c"0 <= x && x < SIM_X_SIZE && \22Out of range\22\00", align 1
@.str.5 = private unnamed_addr constant [43 x i8] c"0 <= y && y < SIM_Y_SIZE && \22Out of range\22\00", align 1

; Function Attrs: nounwind ssp uwtable(sync)
define void @setDead(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = sext i32 %1 to i64
  %5 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %3, i64 %4
  store i8 0, ptr %5, align 1, !tbaa !6
  %6 = icmp ugt i32 %0, 511
  br i1 %6, label %7, label %8, !prof !10

7:                                                ; preds = %2
  call void @setDead.cold.1() #5
  ret void

8:                                                ; preds = %2
  %9 = icmp ugt i32 %1, 255
  br i1 %9, label %10, label %11, !prof !10

10:                                               ; preds = %8
  call void @setDead.cold.2() #5
  ret void

11:                                               ; preds = %8
  %12 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %13 = tail call i32 @SDL_SetRenderDrawColor(ptr noundef %12, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext 0) #6
  %14 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %15 = tail call i32 @SDL_RenderDrawPoint(ptr noundef %14, i32 noundef %0, i32 noundef %1) #6
  %16 = tail call i32 @SDL_GetTicks() #6
  store i32 %16, ptr @Ticks, align 4, !tbaa !13
  ret void
}

; Function Attrs: nounwind ssp uwtable(sync)
define void @simPutPixel(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = icmp ugt i32 %0, 511
  br i1 %4, label %5, label %6, !prof !10

5:                                                ; preds = %3
  call void @simPutPixel.cold.1() #5
  ret void

6:                                                ; preds = %3
  %7 = icmp ugt i32 %1, 255
  br i1 %7, label %8, label %9, !prof !10

8:                                                ; preds = %6
  call void @simPutPixel.cold.2() #5
  ret void

9:                                                ; preds = %6
  %10 = lshr i32 %2, 24
  %11 = trunc i32 %10 to i8
  %12 = lshr i32 %2, 16
  %13 = trunc i32 %12 to i8
  %14 = lshr i32 %2, 8
  %15 = trunc i32 %14 to i8
  %16 = trunc i32 %2 to i8
  %17 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %18 = tail call i32 @SDL_SetRenderDrawColor(ptr noundef %17, i8 noundef zeroext %13, i8 noundef zeroext %15, i8 noundef zeroext %16, i8 noundef zeroext %11) #6
  %19 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %20 = tail call i32 @SDL_RenderDrawPoint(ptr noundef %19, i32 noundef %0, i32 noundef %1) #6
  %21 = tail call i32 @SDL_GetTicks() #6
  store i32 %21, ptr @Ticks, align 4, !tbaa !13
  ret void
}

; Function Attrs: nounwind ssp uwtable(sync)
define void @setAlive(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = sext i32 %1 to i64
  %5 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %3, i64 %4
  store i8 1, ptr %5, align 1, !tbaa !6
  %6 = icmp ugt i32 %0, 511
  br i1 %6, label %7, label %8, !prof !10

7:                                                ; preds = %2
  call void @setAlive.cold.1() #5
  ret void

8:                                                ; preds = %2
  %9 = icmp ugt i32 %1, 255
  br i1 %9, label %10, label %11, !prof !10

10:                                               ; preds = %8
  call void @setAlive.cold.2() #5
  ret void

11:                                               ; preds = %8
  %12 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %13 = tail call i32 @SDL_SetRenderDrawColor(ptr noundef %12, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0) #6
  %14 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %15 = tail call i32 @SDL_RenderDrawPoint(ptr noundef %14, i32 noundef %0, i32 noundef %1) #6
  %16 = tail call i32 @SDL_GetTicks() #6
  store i32 %16, ptr @Ticks, align 4, !tbaa !13
  ret void
}

; Function Attrs: nounwind ssp uwtable(sync)
define void @simSetRender() local_unnamed_addr #0 {
  br label %1

1:                                                ; preds = %0, %4
  %2 = phi i32 [ 0, %0 ], [ %5, %4 ]
  br label %7

3:                                                ; preds = %4
  tail call void @simFlush()
  ret void

4:                                                ; preds = %14
  %5 = add nuw nsw i32 %2, 1
  %6 = icmp eq i32 %5, 512
  br i1 %6, label %3, label %1, !llvm.loop !15

7:                                                ; preds = %1, %14
  %8 = phi i32 [ 0, %1 ], [ %15, %14 ]
  %9 = tail call i32 @rand() #6
  %10 = srem i32 %9, 5
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %13, label %12

12:                                               ; preds = %7
  tail call void @setDead(i32 noundef %2, i32 noundef %8)
  br label %14

13:                                               ; preds = %7
  tail call void @setAlive(i32 noundef %2, i32 noundef %8)
  br label %14

14:                                               ; preds = %13, %12
  %15 = add nuw nsw i32 %8, 1
  %16 = icmp eq i32 %15, 256
  br i1 %16, label %4, label %7, !llvm.loop !17
}

; Function Attrs: argmemonly mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: argmemonly mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nounwind ssp uwtable(sync)
define void @simInit() local_unnamed_addr #0 {
  %1 = tail call i32 @SDL_Init(i32 noundef 32) #6
  %2 = tail call i32 @SDL_CreateWindowAndRenderer(i32 noundef 512, i32 noundef 256, i32 noundef 0, ptr noundef nonnull @Window, ptr noundef nonnull @Renderer) #6
  %3 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %4 = tail call i32 @SDL_SetRenderDrawColor(ptr noundef %3, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0) #6
  %5 = tail call i64 @time(ptr noundef null) #6
  %6 = trunc i64 %5 to i32
  tail call void @srand(i32 noundef %6) #6
  br label %7

7:                                                ; preds = %9, %0
  %8 = phi i32 [ 0, %0 ], [ %10, %9 ]
  br label %12

9:                                                ; preds = %19
  %10 = add nuw nsw i32 %8, 1
  %11 = icmp eq i32 %10, 512
  br i1 %11, label %22, label %7, !llvm.loop !15

12:                                               ; preds = %19, %7
  %13 = phi i32 [ 0, %7 ], [ %20, %19 ]
  %14 = tail call i32 @rand() #6
  %15 = srem i32 %14, 5
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %18, label %17

17:                                               ; preds = %12
  tail call void @setDead(i32 noundef %8, i32 noundef %13)
  br label %19

18:                                               ; preds = %12
  tail call void @setAlive(i32 noundef %8, i32 noundef %13)
  br label %19

19:                                               ; preds = %18, %17
  %20 = add nuw nsw i32 %13, 1
  %21 = icmp eq i32 %20, 256
  br i1 %21, label %9, label %12, !llvm.loop !17

22:                                               ; preds = %9
  tail call void @simFlush()
  %23 = load ptr, ptr @Renderer, align 8, !tbaa !11
  %24 = tail call i32 @SDL_RenderClear(ptr noundef %23) #6
  ret void
}

declare i32 @SDL_Init(i32 noundef) local_unnamed_addr #2

declare i32 @SDL_CreateWindowAndRenderer(i32 noundef, i32 noundef, i32 noundef, ptr noundef, ptr noundef) local_unnamed_addr #2

declare i32 @SDL_SetRenderDrawColor(ptr noundef, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext) local_unnamed_addr #2

declare void @srand(i32 noundef) local_unnamed_addr #2

declare i64 @time(ptr noundef) local_unnamed_addr #2

declare i32 @SDL_RenderClear(ptr noundef) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable(sync)
define void @simExit() local_unnamed_addr #0 {
  %1 = alloca %union.SDL_Event, align 8
  call void @llvm.lifetime.start.p0(i64 56, ptr nonnull %1) #6
  br label %2

2:                                                ; preds = %2, %0
  %3 = call i32 @SDL_PollEvent(ptr noundef nonnull %1) #6
  %4 = icmp ne i32 %3, 0
  %5 = load i32, ptr %1, align 8
  %6 = icmp eq i32 %5, 256
  %7 = select i1 %4, i1 %6, i1 false
  br i1 %7, label %8, label %2

8:                                                ; preds = %2
  %9 = load ptr, ptr @Renderer, align 8, !tbaa !11
  call void @SDL_DestroyRenderer(ptr noundef %9) #6
  %10 = load ptr, ptr @Window, align 8, !tbaa !11
  call void @SDL_DestroyWindow(ptr noundef %10) #6
  call void @SDL_Quit() #6
  call void @llvm.lifetime.end.p0(i64 56, ptr nonnull %1) #6
  ret void
}

declare i32 @SDL_PollEvent(ptr noundef) local_unnamed_addr #2

declare void @SDL_DestroyRenderer(ptr noundef) local_unnamed_addr #2

declare void @SDL_DestroyWindow(ptr noundef) local_unnamed_addr #2

declare void @SDL_Quit() local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable(sync)
define i32 @main() local_unnamed_addr #0 {
  %1 = alloca %union.SDL_Event, align 8
  tail call void @simInit()
  tail call void @app() #6
  call void @llvm.lifetime.start.p0(i64 56, ptr nonnull %1) #6
  br label %2

2:                                                ; preds = %2, %0
  %3 = call i32 @SDL_PollEvent(ptr noundef nonnull %1) #6
  %4 = icmp ne i32 %3, 0
  %5 = load i32, ptr %1, align 8
  %6 = icmp eq i32 %5, 256
  %7 = select i1 %4, i1 %6, i1 false
  br i1 %7, label %8, label %2

8:                                                ; preds = %2
  %9 = load ptr, ptr @Renderer, align 8, !tbaa !11
  call void @SDL_DestroyRenderer(ptr noundef %9) #6
  %10 = load ptr, ptr @Window, align 8, !tbaa !11
  call void @SDL_DestroyWindow(ptr noundef %10) #6
  call void @SDL_Quit() #6
  call void @llvm.lifetime.end.p0(i64 56, ptr nonnull %1) #6
  ret i32 0
}

declare void @app(...) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable(sync)
define void @simFlush() local_unnamed_addr #0 {
  tail call void @SDL_PumpEvents() #6
  %1 = tail call i32 @SDL_HasEvent(i32 noundef 256) #6
  %2 = icmp eq i32 %1, 1
  br i1 %2, label %3, label %4, !prof !10

3:                                                ; preds = %0
  call void @simFlush.cold.1() #5
  ret void

4:                                                ; preds = %0
  %5 = tail call i32 @SDL_GetTicks() #6
  %6 = load i32, ptr @Ticks, align 4, !tbaa !13
  %7 = sub i32 %5, %6
  %8 = icmp ult i32 %7, 50
  br i1 %8, label %9, label %11

9:                                                ; preds = %4
  %10 = sub nuw nsw i32 50, %7
  tail call void @SDL_Delay(i32 noundef %10) #6
  br label %11

11:                                               ; preds = %9, %4
  %12 = load ptr, ptr @Renderer, align 8, !tbaa !11
  tail call void @SDL_RenderPresent(ptr noundef %12) #6
  ret void
}

declare void @SDL_PumpEvents() local_unnamed_addr #2

declare i32 @SDL_HasEvent(i32 noundef) local_unnamed_addr #2

; Function Attrs: cold noreturn
declare void @__assert_rtn(ptr noundef, ptr noundef, i32 noundef, ptr noundef) local_unnamed_addr #3

declare i32 @SDL_GetTicks() local_unnamed_addr #2

declare void @SDL_Delay(i32 noundef) local_unnamed_addr #2

declare void @SDL_RenderPresent(ptr noundef) local_unnamed_addr #2

declare i32 @SDL_RenderDrawPoint(ptr noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable(sync)
define i32 @simRand() local_unnamed_addr #0 {
  %1 = tail call i32 @rand() #6
  ret i32 %1
}

declare i32 @rand() local_unnamed_addr #2

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @setDead.cold.1() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 82, ptr noundef nonnull @.str.4) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @setDead.cold.2() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 83, ptr noundef nonnull @.str.5) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @simPutPixel.cold.1() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 82, ptr noundef nonnull @.str.4) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @simPutPixel.cold.2() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 83, ptr noundef nonnull @.str.5) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @setAlive.cold.1() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 82, ptr noundef nonnull @.str.4) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @setAlive.cold.2() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simPutPixel, ptr noundef nonnull @.str.1, i32 noundef 83, ptr noundef nonnull @.str.5) #7
  unreachable
}

; Function Attrs: cold minsize noreturn nounwind ssp uwtable(sync)
define internal void @simFlush.cold.1() #4 {
  br label %1

1:                                                ; preds = %0
  tail call void @__assert_rtn(ptr noundef nonnull @__func__.simFlush, ptr noundef nonnull @.str.1, i32 noundef 71, ptr noundef nonnull @.str.2) #7
  unreachable
}

attributes #0 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { argmemonly mustprogress nocallback nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #3 = { cold noreturn "disable-tail-calls"="true" "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #4 = { cold minsize noreturn nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #5 = { noinline }
attributes #6 = { nounwind }
attributes #7 = { cold noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 14, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 15.0.0 (clang-1500.1.0.2.5)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"_Bool", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C/C++ TBAA"}
!10 = !{!"branch_weights", i32 1, i32 2000}
!11 = !{!12, !12, i64 0}
!12 = !{!"any pointer", !8, i64 0}
!13 = !{!14, !14, i64 0}
!14 = !{!"int", !8, i64 0}
!15 = distinct !{!15, !16}
!16 = !{!"llvm.loop.mustprogress"}
!17 = distinct !{!17, !16}
