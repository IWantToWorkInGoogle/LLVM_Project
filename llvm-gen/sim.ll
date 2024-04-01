; ModuleID = 'sim.c'
source_filename = "sim.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.SDL_Window = type opaque
%struct.SDL_Renderer = type opaque
%union.SDL_Event = type { %struct.SDL_TouchFingerEvent, [8 x i8] }
%struct.SDL_TouchFingerEvent = type { i32, i32, i64, i64, float, float, float, float, float, i32 }

@state = dso_local local_unnamed_addr global [512 x [256 x i8]] zeroinitializer, align 16
@Window = internal global %struct.SDL_Window* null, align 8
@Renderer = internal global %struct.SDL_Renderer* null, align 8
@.str.1 = private unnamed_addr constant [60 x i8] c"SDL_TRUE != SDL_HasEvent(SDL_QUIT) && \22User-requested quit\22\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"sim.c\00", align 1
@__PRETTY_FUNCTION__.simFlush = private unnamed_addr constant [16 x i8] c"void simFlush()\00", align 1
@Ticks = internal unnamed_addr global i32 0, align 4
@.str.4 = private unnamed_addr constant [43 x i8] c"0 <= x && x < SIM_X_SIZE && \22Out of range\22\00", align 1
@__PRETTY_FUNCTION__.simPutPixel = private unnamed_addr constant [32 x i8] c"void simPutPixel(int, int, int)\00", align 1
@.str.5 = private unnamed_addr constant [43 x i8] c"0 <= y && y < SIM_Y_SIZE && \22Out of range\22\00", align 1

; Function Attrs: nounwind uwtable
define dso_local void @setDead(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = sext i32 %1 to i64
  %5 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %3, i64 %4
  store i8 0, i8* %5, align 1, !tbaa !5
  %6 = icmp ult i32 %0, 512
  br i1 %6, label %8, label %7

7:                                                ; preds = %2
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 83, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

8:                                                ; preds = %2
  %9 = icmp ult i32 %1, 256
  br i1 %9, label %11, label %10

10:                                               ; preds = %8
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 84, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

11:                                               ; preds = %8
  %12 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %13 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %12, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext -1, i8 noundef zeroext 0) #6
  %14 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %15 = tail call i32 @SDL_RenderDrawPoint(%struct.SDL_Renderer* noundef %14, i32 noundef %0, i32 noundef %1) #6
  %16 = tail call i32 @SDL_GetTicks() #6
  store i32 %16, i32* @Ticks, align 4, !tbaa !11
  ret void
}

; Function Attrs: nounwind uwtable
define dso_local void @simPutPixel(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = icmp ult i32 %0, 512
  br i1 %4, label %6, label %5

5:                                                ; preds = %3
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 83, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

6:                                                ; preds = %3
  %7 = icmp ult i32 %1, 256
  br i1 %7, label %9, label %8

8:                                                ; preds = %6
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 84, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

9:                                                ; preds = %6
  %10 = lshr i32 %2, 24
  %11 = trunc i32 %10 to i8
  %12 = lshr i32 %2, 16
  %13 = trunc i32 %12 to i8
  %14 = lshr i32 %2, 8
  %15 = trunc i32 %14 to i8
  %16 = trunc i32 %2 to i8
  %17 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %18 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %17, i8 noundef zeroext %13, i8 noundef zeroext %15, i8 noundef zeroext %16, i8 noundef zeroext %11) #6
  %19 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %20 = tail call i32 @SDL_RenderDrawPoint(%struct.SDL_Renderer* noundef %19, i32 noundef %0, i32 noundef %1) #6
  %21 = tail call i32 @SDL_GetTicks() #6
  store i32 %21, i32* @Ticks, align 4, !tbaa !11
  ret void
}

; Function Attrs: nounwind uwtable
define dso_local void @setAlive(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = sext i32 %1 to i64
  %5 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %3, i64 %4
  store i8 1, i8* %5, align 1, !tbaa !5
  %6 = icmp ult i32 %0, 512
  br i1 %6, label %8, label %7

7:                                                ; preds = %2
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.4, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 83, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

8:                                                ; preds = %2
  %9 = icmp ult i32 %1, 256
  br i1 %9, label %11, label %10

10:                                               ; preds = %8
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([43 x i8], [43 x i8]* @.str.5, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 84, i8* noundef getelementptr inbounds ([32 x i8], [32 x i8]* @__PRETTY_FUNCTION__.simPutPixel, i64 0, i64 0)) #5
  unreachable

11:                                               ; preds = %8
  %12 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %13 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %12, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0) #6
  %14 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %15 = tail call i32 @SDL_RenderDrawPoint(%struct.SDL_Renderer* noundef %14, i32 noundef %0, i32 noundef %1) #6
  %16 = tail call i32 @SDL_GetTicks() #6
  store i32 %16, i32* @Ticks, align 4, !tbaa !11
  ret void
}

; Function Attrs: nounwind uwtable
define dso_local void @simSetRender() local_unnamed_addr #0 {
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
  br i1 %6, label %3, label %1, !llvm.loop !13

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
  br i1 %16, label %4, label %7, !llvm.loop !15
}

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: nounwind uwtable
define dso_local void @simInit() local_unnamed_addr #0 {
  %1 = tail call i32 @SDL_Init(i32 noundef 32) #6
  %2 = tail call i32 @SDL_CreateWindowAndRenderer(i32 noundef 512, i32 noundef 256, i32 noundef 0, %struct.SDL_Window** noundef nonnull @Window, %struct.SDL_Renderer** noundef nonnull @Renderer) #6
  %3 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %4 = tail call i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef %3, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0, i8 noundef zeroext 0) #6
  %5 = tail call i64 @time(i64* noundef null) #6
  %6 = trunc i64 %5 to i32
  tail call void @srand(i32 noundef %6) #6
  br label %7

7:                                                ; preds = %9, %0
  %8 = phi i32 [ 0, %0 ], [ %10, %9 ]
  br label %12

9:                                                ; preds = %19
  %10 = add nuw nsw i32 %8, 1
  %11 = icmp eq i32 %10, 512
  br i1 %11, label %22, label %7, !llvm.loop !13

12:                                               ; preds = %19, %7
  %13 = phi i32 [ 0, %7 ], [ %20, %19 ]
  %14 = tail call i32 @rand() #6
  %15 = srem i32 %14, 5
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %18, label %17

17:                                               ; preds = %12
  tail call void @setDead(i32 noundef %8, i32 noundef %13) #6
  br label %19

18:                                               ; preds = %12
  tail call void @setAlive(i32 noundef %8, i32 noundef %13) #6
  br label %19

19:                                               ; preds = %18, %17
  %20 = add nuw nsw i32 %13, 1
  %21 = icmp eq i32 %20, 256
  br i1 %21, label %9, label %12, !llvm.loop !15

22:                                               ; preds = %9
  tail call void @simFlush() #6
  %23 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  %24 = tail call i32 @SDL_RenderClear(%struct.SDL_Renderer* noundef %23) #6
  ret void
}

declare i32 @SDL_Init(i32 noundef) local_unnamed_addr #2

declare i32 @SDL_CreateWindowAndRenderer(i32 noundef, i32 noundef, i32 noundef, %struct.SDL_Window** noundef, %struct.SDL_Renderer** noundef) local_unnamed_addr #2

declare i32 @SDL_SetRenderDrawColor(%struct.SDL_Renderer* noundef, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext, i8 noundef zeroext) local_unnamed_addr #2

; Function Attrs: nounwind
declare void @srand(i32 noundef) local_unnamed_addr #3

; Function Attrs: nounwind
declare i64 @time(i64* noundef) local_unnamed_addr #3

declare i32 @SDL_RenderClear(%struct.SDL_Renderer* noundef) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define dso_local void @simExit() local_unnamed_addr #0 {
  %1 = alloca %union.SDL_Event, align 8
  %2 = bitcast %union.SDL_Event* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 56, i8* nonnull %2) #6
  %3 = getelementptr inbounds %union.SDL_Event, %union.SDL_Event* %1, i64 0, i32 0, i32 0
  br label %4

4:                                                ; preds = %4, %0
  %5 = call i32 @SDL_PollEvent(%union.SDL_Event* noundef nonnull %1) #6
  %6 = icmp ne i32 %5, 0
  %7 = load i32, i32* %3, align 8
  %8 = icmp eq i32 %7, 256
  %9 = select i1 %6, i1 %8, i1 false
  br i1 %9, label %10, label %4

10:                                               ; preds = %4
  %11 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  call void @SDL_DestroyRenderer(%struct.SDL_Renderer* noundef %11) #6
  %12 = load %struct.SDL_Window*, %struct.SDL_Window** @Window, align 8, !tbaa !9
  call void @SDL_DestroyWindow(%struct.SDL_Window* noundef %12) #6
  call void @SDL_Quit() #6
  call void @llvm.lifetime.end.p0i8(i64 56, i8* nonnull %2) #6
  ret void
}

declare i32 @SDL_PollEvent(%union.SDL_Event* noundef) local_unnamed_addr #2

declare void @SDL_DestroyRenderer(%struct.SDL_Renderer* noundef) local_unnamed_addr #2

declare void @SDL_DestroyWindow(%struct.SDL_Window* noundef) local_unnamed_addr #2

declare void @SDL_Quit() local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define dso_local i32 @main() local_unnamed_addr #0 {
  %1 = alloca %union.SDL_Event, align 8
  tail call void @simInit()
  tail call void (...) @app() #6
  %2 = bitcast %union.SDL_Event* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 56, i8* nonnull %2) #6
  %3 = getelementptr inbounds %union.SDL_Event, %union.SDL_Event* %1, i64 0, i32 0, i32 0
  br label %4

4:                                                ; preds = %4, %0
  %5 = call i32 @SDL_PollEvent(%union.SDL_Event* noundef nonnull %1) #6
  %6 = icmp ne i32 %5, 0
  %7 = load i32, i32* %3, align 8
  %8 = icmp eq i32 %7, 256
  %9 = select i1 %6, i1 %8, i1 false
  br i1 %9, label %10, label %4

10:                                               ; preds = %4
  %11 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  call void @SDL_DestroyRenderer(%struct.SDL_Renderer* noundef %11) #6
  %12 = load %struct.SDL_Window*, %struct.SDL_Window** @Window, align 8, !tbaa !9
  call void @SDL_DestroyWindow(%struct.SDL_Window* noundef %12) #6
  call void @SDL_Quit() #6
  call void @llvm.lifetime.end.p0i8(i64 56, i8* nonnull %2) #6
  ret i32 0
}

declare void @app(...) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define dso_local void @simFlush() local_unnamed_addr #0 {
  tail call void @SDL_PumpEvents() #6
  %1 = tail call i32 @SDL_HasEvent(i32 noundef 256) #6
  %2 = icmp eq i32 %1, 1
  br i1 %2, label %3, label %4

3:                                                ; preds = %0
  tail call void @__assert_fail(i8* noundef getelementptr inbounds ([60 x i8], [60 x i8]* @.str.1, i64 0, i64 0), i8* noundef getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0), i32 noundef 72, i8* noundef getelementptr inbounds ([16 x i8], [16 x i8]* @__PRETTY_FUNCTION__.simFlush, i64 0, i64 0)) #5
  unreachable

4:                                                ; preds = %0
  %5 = tail call i32 @SDL_GetTicks() #6
  %6 = load i32, i32* @Ticks, align 4, !tbaa !11
  %7 = sub i32 %5, %6
  %8 = icmp ult i32 %7, 50
  br i1 %8, label %9, label %11

9:                                                ; preds = %4
  %10 = sub nuw nsw i32 50, %7
  tail call void @SDL_Delay(i32 noundef %10) #6
  br label %11

11:                                               ; preds = %9, %4
  %12 = load %struct.SDL_Renderer*, %struct.SDL_Renderer** @Renderer, align 8, !tbaa !9
  tail call void @SDL_RenderPresent(%struct.SDL_Renderer* noundef %12) #6
  ret void
}

declare void @SDL_PumpEvents() local_unnamed_addr #2

declare i32 @SDL_HasEvent(i32 noundef) local_unnamed_addr #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8* noundef, i8* noundef, i32 noundef, i8* noundef) local_unnamed_addr #4

declare i32 @SDL_GetTicks() local_unnamed_addr #2

declare void @SDL_Delay(i32 noundef) local_unnamed_addr #2

declare void @SDL_RenderPresent(%struct.SDL_Renderer* noundef) local_unnamed_addr #2

declare i32 @SDL_RenderDrawPoint(%struct.SDL_Renderer* noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: nounwind uwtable
define dso_local i32 @simRand() local_unnamed_addr #0 {
  %1 = tail call i32 @rand() #6
  ret i32 %1
}

; Function Attrs: nounwind
declare i32 @rand() local_unnamed_addr #3

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly mustprogress nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { noreturn nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!5 = !{!6, !6, i64 0}
!6 = !{!"_Bool", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = !{!10, !10, i64 0}
!10 = !{!"any pointer", !7, i64 0}
!11 = !{!12, !12, i64 0}
!12 = !{!"int", !7, i64 0}
!13 = distinct !{!13, !14}
!14 = !{!"llvm.loop.mustprogress"}
!15 = distinct !{!15, !14}
