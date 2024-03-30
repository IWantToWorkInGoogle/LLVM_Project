; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

@state = common local_unnamed_addr global [512 x [256 x i8]] zeroinitializer, align 1

; Function Attrs: nounwind ssp uwtable(sync)
define void @app() local_unnamed_addr #0 {
  %1 = alloca [512 x [256 x i8]], align 1
  call void @llvm.lifetime.start.p0(i64 131072, ptr nonnull %1) #3
  br label %2

2:                                                ; preds = %0, %99
  %3 = phi i32 [ 0, %0 ], [ %100, %99 ]
  br label %5

4:                                                ; preds = %99
  call void @llvm.lifetime.end.p0(i64 131072, ptr nonnull %1) #3
  ret void

5:                                                ; preds = %2, %12
  %6 = phi i64 [ 0, %2 ], [ %10, %12 ]
  %7 = icmp eq i64 %6, 0
  %8 = add nuw i64 %6, 4294967295
  %9 = and i64 %8, 4294967295
  %10 = add nuw nsw i64 %6, 1
  %11 = icmp ugt i64 %6, 510
  br label %14

12:                                               ; preds = %91
  %13 = icmp eq i64 %10, 512
  br i1 %13, label %96, label %5, !llvm.loop !6

14:                                               ; preds = %91, %5
  %15 = phi i64 [ 0, %5 ], [ %94, %91 ]
  %16 = trunc i64 %15 to i32
  %17 = add i32 %16, -1
  %18 = icmp ugt i32 %17, 255
  %19 = select i1 %18, i1 true, i1 %7
  br i1 %19, label %25, label %20

20:                                               ; preds = %14
  %21 = zext i32 %17 to i64
  %22 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %21
  %23 = load i8, ptr %22, align 1, !tbaa !8, !range !12
  %24 = zext i8 %23 to i32
  br label %26

25:                                               ; preds = %14
  br i1 %7, label %40, label %26

26:                                               ; preds = %25, %20
  %27 = phi i32 [ %24, %20 ], [ 0, %25 ]
  %28 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %15
  %29 = load i8, ptr %28, align 1, !tbaa !8, !range !12
  %30 = zext i8 %29 to i32
  %31 = add nuw nsw i32 %27, %30
  %32 = icmp ugt i64 %15, 254
  %33 = select i1 %32, i1 true, i1 %7
  br i1 %33, label %40, label %34

34:                                               ; preds = %26
  %35 = add nuw nsw i64 %15, 1
  %36 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %9, i64 %35
  %37 = load i8, ptr %36, align 1, !tbaa !8, !range !12
  %38 = zext i8 %37 to i32
  %39 = add nuw nsw i32 %31, %38
  br label %40

40:                                               ; preds = %25, %26, %34
  %41 = phi i32 [ %31, %26 ], [ %39, %34 ], [ 0, %25 ]
  br i1 %18, label %48, label %42

42:                                               ; preds = %40
  %43 = zext i32 %17 to i64
  %44 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %43
  %45 = load i8, ptr %44, align 1, !tbaa !8, !range !12
  %46 = zext i8 %45 to i32
  %47 = add nuw nsw i32 %41, %46
  br label %48

48:                                               ; preds = %42, %40
  %49 = phi i32 [ %41, %40 ], [ %47, %42 ]
  %50 = icmp ugt i64 %15, 254
  br i1 %50, label %57, label %51

51:                                               ; preds = %48
  %52 = add nuw nsw i64 %15, 1
  %53 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %52
  %54 = load i8, ptr %53, align 1, !tbaa !8, !range !12
  %55 = zext i8 %54 to i32
  %56 = add nuw nsw i32 %49, %55
  br label %57

57:                                               ; preds = %51, %48
  %58 = phi i32 [ %49, %48 ], [ %56, %51 ]
  br i1 %11, label %78, label %59

59:                                               ; preds = %57
  br i1 %18, label %66, label %60

60:                                               ; preds = %59
  %61 = zext i32 %17 to i64
  %62 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %61
  %63 = load i8, ptr %62, align 1, !tbaa !8, !range !12
  %64 = zext i8 %63 to i32
  %65 = add nuw nsw i32 %58, %64
  br label %66

66:                                               ; preds = %59, %60
  %67 = phi i32 [ %65, %60 ], [ %58, %59 ]
  %68 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %15
  %69 = load i8, ptr %68, align 1, !tbaa !8, !range !12
  %70 = zext i8 %69 to i32
  %71 = add nuw nsw i32 %67, %70
  br i1 %50, label %78, label %72

72:                                               ; preds = %66
  %73 = add nuw nsw i64 %15, 1
  %74 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %10, i64 %73
  %75 = load i8, ptr %74, align 1, !tbaa !8, !range !12
  %76 = zext i8 %75 to i32
  %77 = add nuw nsw i32 %71, %76
  br label %78

78:                                               ; preds = %57, %72, %66
  %79 = phi i32 [ %71, %66 ], [ %77, %72 ], [ %58, %57 ]
  %80 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %6, i64 %15
  %81 = load i8, ptr %80, align 1, !tbaa !8, !range !12
  %82 = icmp eq i8 %81, 0
  %83 = icmp eq i32 %79, 3
  %84 = select i1 %82, i1 %83, i1 false
  br i1 %84, label %91, label %85

85:                                               ; preds = %78
  %86 = xor i1 %82, true
  %87 = and i32 %79, -2
  %88 = icmp eq i32 %87, 2
  %89 = select i1 %86, i1 %88, i1 false
  %90 = zext i1 %89 to i8
  br label %91

91:                                               ; preds = %85, %78
  %92 = phi i8 [ 1, %78 ], [ %90, %85 ]
  %93 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %6, i64 %15
  store i8 %92, ptr %93, align 1, !tbaa !8
  %94 = add nuw nsw i64 %15, 1
  %95 = icmp eq i64 %94, 256
  br i1 %95, label %12, label %14, !llvm.loop !13

96:                                               ; preds = %12, %102
  %97 = phi i64 [ %103, %102 ], [ 0, %12 ]
  %98 = trunc i64 %97 to i32
  br label %105

99:                                               ; preds = %102
  tail call void @simFlush() #3
  %100 = add nuw nsw i32 %3, 1
  %101 = icmp eq i32 %100, 1000
  br i1 %101, label %4, label %2, !llvm.loop !14

102:                                              ; preds = %105
  %103 = add nuw nsw i64 %97, 1
  %104 = icmp eq i64 %103, 512
  br i1 %104, label %99, label %96, !llvm.loop !15

105:                                              ; preds = %96, %105
  %106 = phi i64 [ 0, %96 ], [ %113, %105 ]
  %107 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %97, i64 %106
  %108 = load i8, ptr %107, align 1, !tbaa !8, !range !12
  %109 = icmp eq i8 %108, 0
  %110 = trunc i64 %106 to i32
  %111 = select i1 %109, i32 0, i32 16777215
  tail call void @simPutPixel(i32 noundef %98, i32 noundef %110, i32 noundef %111) #3
  %112 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %97, i64 %106
  store i8 %108, ptr %112, align 1, !tbaa !8
  %113 = add nuw nsw i64 %106, 1
  %114 = icmp eq i64 %113, 256
  br i1 %114, label %102, label %105, !llvm.loop !16
}

; Function Attrs: argmemonly mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: argmemonly mustprogress nocallback nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

attributes #0 = { nounwind ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { argmemonly mustprogress nocallback nofree nosync nounwind willreturn }
attributes #2 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #3 = { nounwind }

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
!8 = !{!9, !9, i64 0}
!9 = !{!"_Bool", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
!12 = !{i8 0, i8 2}
!13 = distinct !{!13, !7}
!14 = distinct !{!14, !7}
!15 = distinct !{!15, !7}
!16 = distinct !{!16, !7}
