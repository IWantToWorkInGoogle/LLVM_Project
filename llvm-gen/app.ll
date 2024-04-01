; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@state = dso_local local_unnamed_addr global [512 x [256 x i8]] zeroinitializer, align 16
@new_state = dso_local local_unnamed_addr global [512 x [256 x i8]] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  br label %1

1:                                                ; preds = %0, %131
  %2 = phi i32 [ 0, %0 ], [ %132, %131 ]
  br label %4

3:                                                ; preds = %131
  ret void

4:                                                ; preds = %1, %49
  %5 = phi i64 [ 0, %1 ], [ %9, %49 ]
  %6 = icmp eq i64 %5, 0
  %7 = add nuw i64 %5, 4294967295
  %8 = and i64 %7, 4294967295
  %9 = add nuw nsw i64 %5, 1
  %10 = icmp ugt i64 %5, 510
  br i1 %6, label %17, label %11

11:                                               ; preds = %4
  %12 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 0
  %13 = load i8, i8* %12, align 16, !tbaa !5, !range !9
  %14 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 1
  %15 = load i8, i8* %14, align 1, !tbaa !5, !range !9
  %16 = add nuw nsw i8 %13, %15
  br label %17

17:                                               ; preds = %11, %4
  %18 = phi i8 [ %16, %11 ], [ 0, %4 ]
  %19 = zext i8 %18 to i32
  %20 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 1
  %21 = load i8, i8* %20, align 1, !tbaa !5, !range !9
  %22 = zext i8 %21 to i32
  %23 = add nuw nsw i32 %19, %22
  br i1 %10, label %33, label %24

24:                                               ; preds = %17
  %25 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 0
  %26 = load i8, i8* %25, align 16, !tbaa !5, !range !9
  %27 = zext i8 %26 to i32
  %28 = add nuw nsw i32 %23, %27
  %29 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 1
  %30 = load i8, i8* %29, align 1, !tbaa !5, !range !9
  %31 = zext i8 %30 to i32
  %32 = add nuw nsw i32 %28, %31
  br label %33

33:                                               ; preds = %24, %17
  %34 = phi i32 [ %32, %24 ], [ %23, %17 ]
  %35 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 0
  %36 = load i8, i8* %35, align 16, !tbaa !5, !range !9
  %37 = icmp eq i8 %36, 0
  %38 = icmp eq i32 %34, 3
  %39 = select i1 %37, i1 %38, i1 false
  br i1 %39, label %46, label %40

40:                                               ; preds = %33
  %41 = xor i1 %37, true
  %42 = and i32 %34, -2
  %43 = icmp eq i32 %42, 2
  %44 = select i1 %41, i1 %43, i1 false
  %45 = zext i1 %44 to i8
  br label %46

46:                                               ; preds = %40, %33
  %47 = phi i8 [ 1, %33 ], [ %45, %40 ]
  %48 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %5, i64 0
  store i8 %47, i8* %48, align 16, !tbaa !5
  br label %51

49:                                               ; preds = %122
  %50 = icmp eq i64 %9, 512
  br i1 %50, label %127, label %4, !llvm.loop !10

51:                                               ; preds = %122, %46
  %52 = phi i64 [ 1, %46 ], [ %125, %122 ]
  br i1 %6, label %59, label %53

53:                                               ; preds = %51
  %54 = add nuw nsw i64 %52, 4294967295
  %55 = and i64 %54, 4294967295
  %56 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %55
  %57 = load i8, i8* %56, align 1, !tbaa !5, !range !9
  %58 = zext i8 %57 to i32
  br label %59

59:                                               ; preds = %51, %53
  %60 = phi i32 [ 0, %51 ], [ %58, %53 ]
  br i1 %6, label %74, label %61

61:                                               ; preds = %59
  %62 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %52
  %63 = load i8, i8* %62, align 1, !tbaa !5, !range !9
  %64 = zext i8 %63 to i32
  %65 = add nuw nsw i32 %60, %64
  %66 = icmp ugt i64 %52, 254
  %67 = select i1 %66, i1 true, i1 %6
  br i1 %67, label %74, label %68

68:                                               ; preds = %61
  %69 = add nuw nsw i64 %52, 1
  %70 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %8, i64 %69
  %71 = load i8, i8* %70, align 1, !tbaa !5, !range !9
  %72 = zext i8 %71 to i32
  %73 = add nuw nsw i32 %65, %72
  br label %74

74:                                               ; preds = %68, %61, %59
  %75 = phi i32 [ %65, %61 ], [ %73, %68 ], [ %60, %59 ]
  %76 = add nuw nsw i64 %52, 4294967295
  %77 = and i64 %76, 4294967295
  %78 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %77
  %79 = load i8, i8* %78, align 1, !tbaa !5, !range !9
  %80 = zext i8 %79 to i32
  %81 = add nuw nsw i32 %75, %80
  %82 = icmp ugt i64 %52, 254
  br i1 %82, label %89, label %83

83:                                               ; preds = %74
  %84 = add nuw nsw i64 %52, 1
  %85 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %84
  %86 = load i8, i8* %85, align 1, !tbaa !5, !range !9
  %87 = zext i8 %86 to i32
  %88 = add nuw nsw i32 %81, %87
  br label %89

89:                                               ; preds = %83, %74
  %90 = phi i32 [ %81, %74 ], [ %88, %83 ]
  br i1 %10, label %109, label %91

91:                                               ; preds = %89
  %92 = add nuw nsw i64 %52, 4294967295
  %93 = and i64 %92, 4294967295
  %94 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %93
  %95 = load i8, i8* %94, align 1, !tbaa !5, !range !9
  %96 = zext i8 %95 to i32
  %97 = add nuw nsw i32 %90, %96
  %98 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %52
  %99 = load i8, i8* %98, align 1, !tbaa !5, !range !9
  %100 = zext i8 %99 to i32
  %101 = add nuw nsw i32 %97, %100
  %102 = icmp ugt i64 %52, 254
  br i1 %102, label %109, label %103

103:                                              ; preds = %91
  %104 = add nuw nsw i64 %52, 1
  %105 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %9, i64 %104
  %106 = load i8, i8* %105, align 1, !tbaa !5, !range !9
  %107 = zext i8 %106 to i32
  %108 = add nuw nsw i32 %101, %107
  br label %109

109:                                              ; preds = %89, %103, %91
  %110 = phi i32 [ %101, %91 ], [ %108, %103 ], [ %90, %89 ]
  %111 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %5, i64 %52
  %112 = load i8, i8* %111, align 1, !tbaa !5, !range !9
  %113 = icmp eq i8 %112, 0
  %114 = icmp eq i32 %110, 3
  %115 = select i1 %113, i1 %114, i1 false
  br i1 %115, label %122, label %116

116:                                              ; preds = %109
  %117 = xor i1 %113, true
  %118 = and i32 %110, -2
  %119 = icmp eq i32 %118, 2
  %120 = select i1 %117, i1 %119, i1 false
  %121 = zext i1 %120 to i8
  br label %122

122:                                              ; preds = %116, %109
  %123 = phi i8 [ 1, %109 ], [ %121, %116 ]
  %124 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %5, i64 %52
  store i8 %123, i8* %124, align 1, !tbaa !5
  %125 = add nuw nsw i64 %52, 1
  %126 = icmp eq i64 %125, 256
  br i1 %126, label %49, label %51, !llvm.loop !12

127:                                              ; preds = %49, %134
  %128 = phi i64 [ %135, %134 ], [ 0, %49 ]
  %129 = trunc i64 %128 to i32
  %130 = trunc i64 %128 to i32
  br label %137

131:                                              ; preds = %134
  tail call void (...) @simFlush() #2
  %132 = add nuw nsw i32 %2, 1
  %133 = icmp eq i32 %132, 1000
  br i1 %133, label %3, label %1, !llvm.loop !14

134:                                              ; preds = %145
  %135 = add nuw nsw i64 %128, 1
  %136 = icmp eq i64 %135, 512
  br i1 %136, label %131, label %127, !llvm.loop !15

137:                                              ; preds = %127, %145
  %138 = phi i64 [ 0, %127 ], [ %148, %145 ]
  %139 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @new_state, i64 0, i64 %128, i64 %138
  %140 = load i8, i8* %139, align 1, !tbaa !5, !range !9
  %141 = icmp eq i8 %140, 0
  %142 = trunc i64 %138 to i32
  br i1 %141, label %144, label %143

143:                                              ; preds = %137
  tail call void @simPutPixel(i32 noundef %129, i32 noundef %142, i32 noundef 16777215) #2
  br label %145

144:                                              ; preds = %137
  tail call void @simPutPixel(i32 noundef %130, i32 noundef %142, i32 noundef 0) #2
  br label %145

145:                                              ; preds = %144, %143
  %146 = load i8, i8* %139, align 1, !tbaa !5, !range !9
  %147 = getelementptr inbounds [512 x [256 x i8]], [512 x [256 x i8]]* @state, i64 0, i64 %128, i64 %138
  store i8 %146, i8* %147, align 1, !tbaa !5
  %148 = add nuw nsw i64 %138, 1
  %149 = icmp eq i64 %148, 256
  br i1 %149, label %134, label %137, !llvm.loop !16
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

declare void @simFlush(...) local_unnamed_addr #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind }

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
