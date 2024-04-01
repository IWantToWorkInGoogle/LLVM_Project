; ModuleID = 'src/app.c'
source_filename = "src/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@state = external local_unnamed_addr global [512 x [256 x i8]], align 16

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [512 x [256 x i8]], align 16
  %2 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 131072, i8* nonnull %2) #3
  br label %3

3:                                                ; preds = %0, %133
  %4 = phi i32 [ 0, %0 ], [ %134, %133 ]
  br label %6

5:                                                ; preds = %133
  call void @llvm.lifetime.end.p0i8(i64 131072, i8* nonnull %2) #3
  ret void

6:                                                ; preds = %3, %51
  %7 = phi i64 [ 0, %3 ], [ %11, %51 ]
  %8 = icmp eq i64 %7, 0
  %9 = add nuw i64 %7, 4294967295
  %10 = and i64 %9, 4294967295
  %11 = add nuw nsw i64 %7, 1
  %12 = icmp ugt i64 %7, 510
  br i1 %8, label %19, label %13

13:                                               ; preds = %6
  %14 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 0
  %15 = load i8, i8* %14, align 16, !tbaa !5, !range !9
  %16 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 1
  %17 = load i8, i8* %16, align 1, !tbaa !5, !range !9
  %18 = add nuw nsw i8 %15, %17
  br label %19

19:                                               ; preds = %13, %6
  %20 = phi i8 [ %18, %13 ], [ 0, %6 ]
  %21 = zext i8 %20 to i32
  %22 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 1
  %23 = load i8, i8* %22, align 1, !tbaa !5, !range !9
  %24 = zext i8 %23 to i32
  %25 = add nuw nsw i32 %21, %24
  br i1 %12, label %35, label %26

26:                                               ; preds = %19
  %27 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 0
  %28 = load i8, i8* %27, align 16, !tbaa !5, !range !9
  %29 = zext i8 %28 to i32
  %30 = add nuw nsw i32 %25, %29
  %31 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 1
  %32 = load i8, i8* %31, align 1, !tbaa !5, !range !9
  %33 = zext i8 %32 to i32
  %34 = add nuw nsw i32 %30, %33
  br label %35

35:                                               ; preds = %26, %19
  %36 = phi i32 [ %34, %26 ], [ %25, %19 ]
  %37 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 0
  %38 = load i8, i8* %37, align 16, !tbaa !5, !range !9
  %39 = icmp eq i8 %38, 0
  %40 = icmp eq i32 %36, 3
  %41 = select i1 %39, i1 %40, i1 false
  br i1 %41, label %48, label %42

42:                                               ; preds = %35
  %43 = xor i1 %39, true
  %44 = and i32 %36, -2
  %45 = icmp eq i32 %44, 2
  %46 = select i1 %43, i1 %45, i1 false
  %47 = zext i1 %46 to i8
  br label %48

48:                                               ; preds = %42, %35
  %49 = phi i8 [ 1, %35 ], [ %47, %42 ]
  %50 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %7, i64 0
  store i8 %49, i8* %50, align 16, !tbaa !5
  br label %53

51:                                               ; preds = %124
  %52 = icmp eq i64 %11, 512
  br i1 %52, label %129, label %6, !llvm.loop !10

53:                                               ; preds = %124, %48
  %54 = phi i64 [ 1, %48 ], [ %127, %124 ]
  br i1 %8, label %61, label %55

55:                                               ; preds = %53
  %56 = add nuw nsw i64 %54, 4294967295
  %57 = and i64 %56, 4294967295
  %58 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %57
  %59 = load i8, i8* %58, align 1, !tbaa !5, !range !9
  %60 = zext i8 %59 to i32
  br label %61

61:                                               ; preds = %53, %55
  %62 = phi i32 [ 0, %53 ], [ %60, %55 ]
  br i1 %8, label %76, label %63

63:                                               ; preds = %61
  %64 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %54
  %65 = load i8, i8* %64, align 1, !tbaa !5, !range !9
  %66 = zext i8 %65 to i32
  %67 = add nuw nsw i32 %62, %66
  %68 = icmp ugt i64 %54, 254
  %69 = select i1 %68, i1 true, i1 %8
  br i1 %69, label %76, label %70

70:                                               ; preds = %63
  %71 = add nuw nsw i64 %54, 1
  %72 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %10, i64 %71
  %73 = load i8, i8* %72, align 1, !tbaa !5, !range !9
  %74 = zext i8 %73 to i32
  %75 = add nuw nsw i32 %67, %74
  br label %76

76:                                               ; preds = %70, %63, %61
  %77 = phi i32 [ %67, %63 ], [ %75, %70 ], [ %62, %61 ]
  %78 = add nuw nsw i64 %54, 4294967295
  %79 = and i64 %78, 4294967295
  %80 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %79
  %81 = load i8, i8* %80, align 1, !tbaa !5, !range !9
  %82 = zext i8 %81 to i32
  %83 = add nuw nsw i32 %77, %82
  %84 = icmp ugt i64 %54, 254
  br i1 %84, label %91, label %85

85:                                               ; preds = %76
  %86 = add nuw nsw i64 %54, 1
  %87 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %86
  %88 = load i8, i8* %87, align 1, !tbaa !5, !range !9
  %89 = zext i8 %88 to i32
  %90 = add nuw nsw i32 %83, %89
  br label %91

91:                                               ; preds = %85, %76
  %92 = phi i32 [ %83, %76 ], [ %90, %85 ]
  br i1 %12, label %111, label %93

93:                                               ; preds = %91
  %94 = add nuw nsw i64 %54, 4294967295
  %95 = and i64 %94, 4294967295
  %96 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %95
  %97 = load i8, i8* %96, align 1, !tbaa !5, !range !9
  %98 = zext i8 %97 to i32
  %99 = add nuw nsw i32 %92, %98
  %100 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %54
  %101 = load i8, i8* %100, align 1, !tbaa !5, !range !9
  %102 = zext i8 %101 to i32
  %103 = add nuw nsw i32 %99, %102
  %104 = icmp ugt i64 %54, 254
  br i1 %104, label %111, label %105

105:                                              ; preds = %93
  %106 = add nuw nsw i64 %54, 1
  %107 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %11, i64 %106
  %108 = load i8, i8* %107, align 1, !tbaa !5, !range !9
  %109 = zext i8 %108 to i32
  %110 = add nuw nsw i32 %103, %109
  br label %111

111:                                              ; preds = %91, %105, %93
  %112 = phi i32 [ %103, %93 ], [ %110, %105 ], [ %92, %91 ]
  %113 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %7, i64 %54
  %114 = load i8, i8* %113, align 1, !tbaa !5, !range !9
  %115 = icmp eq i8 %114, 0
  %116 = icmp eq i32 %112, 3
  %117 = select i1 %115, i1 %116, i1 false
  br i1 %117, label %124, label %118

118:                                              ; preds = %111
  %119 = xor i1 %115, true
  %120 = and i32 %112, -2
  %121 = icmp eq i32 %120, 2
  %122 = select i1 %119, i1 %121, i1 false
  %123 = zext i1 %122 to i8
  br label %124

124:                                              ; preds = %118, %111
  %125 = phi i8 [ 1, %111 ], [ %123, %118 ]
  %126 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %7, i64 %54
  store i8 %125, i8* %126, align 1, !tbaa !5
  %127 = add nuw nsw i64 %54, 1
  %128 = icmp eq i64 %127, 256
  br i1 %128, label %51, label %53, !llvm.loop !12

129:                                              ; preds = %51, %136
  %130 = phi i64 [ %137, %136 ], [ 0, %51 ]
  %131 = trunc i64 %130 to i32
  %132 = trunc i64 %130 to i32
  br label %139

133:                                              ; preds = %136
  tail call void (...) @simFlush() #3
  %134 = add nuw nsw i32 %4, 1
  %135 = icmp eq i32 %134, 1000
  br i1 %135, label %5, label %3, !llvm.loop !14

136:                                              ; preds = %147
  %137 = add nuw nsw i64 %130, 1
  %138 = icmp eq i64 %137, 512
  br i1 %138, label %133, label %129, !llvm.loop !15

139:                                              ; preds = %129, %147
  %140 = phi i64 [ 0, %129 ], [ %149, %147 ]
  %141 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* %1, i64 0, i64 %130, i64 %140
  %142 = load i8, i8* %141, align 1, !tbaa !5, !range !9
  %143 = icmp eq i8 %142, 0
  %144 = trunc i64 %140 to i32
  br i1 %143, label %146, label %145

145:                                              ; preds = %139
  tail call void @simPutPixel(i32 noundef %131, i32 noundef %144, i32 noundef 16777215) #3
  br label %147

146:                                              ; preds = %139
  tail call void @simPutPixel(i32 noundef %132, i32 noundef %144, i32 noundef 0) #3
  br label %147

147:                                              ; preds = %146, %145
  %148 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %130, i64 %140
  store i8 %142, i8* %148, align 1, !tbaa !5
  %149 = add nuw nsw i64 %140, 1
  %150 = icmp eq i64 %149, 256
  br i1 %150, label %136, label %139, !llvm.loop !16
}

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly mustprogress nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly mustprogress nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

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
!9 = !{i8 0, i8 2}
!10 = distinct !{!10, !11}
!11 = !{!"llvm.loop.mustprogress"}
!12 = distinct !{!12, !11, !13}
!13 = !{!"llvm.loop.peeled.count", i32 1}
!14 = distinct !{!14, !11}
!15 = distinct !{!15, !11}
!16 = distinct !{!16, !11}
