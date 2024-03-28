; ModuleID = '../src/app.c'
source_filename = "../src/app.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx14.0.0"

@state = common global [512 x [256 x i8]] zeroinitializer, align 1

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define void @app() #0 {
  %1 = alloca [512 x [256 x i8]], align 1
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 0, ptr %2, align 4
  br label %10

10:                                               ; preds = %176, %0
  %11 = load i32, ptr %2, align 4
  %12 = icmp slt i32 %11, 1000
  br i1 %12, label %13, label %179

13:                                               ; preds = %10
  store i32 0, ptr %3, align 4
  br label %14

14:                                               ; preds = %126, %13
  %15 = load i32, ptr %3, align 4
  %16 = icmp slt i32 %15, 512
  br i1 %16, label %17, label %129

17:                                               ; preds = %14
  store i32 0, ptr %4, align 4
  br label %18

18:                                               ; preds = %122, %17
  %19 = load i32, ptr %4, align 4
  %20 = icmp slt i32 %19, 256
  br i1 %20, label %21, label %125

21:                                               ; preds = %18
  store i32 0, ptr %5, align 4
  store i32 -1, ptr %6, align 4
  br label %22

22:                                               ; preds = %77, %21
  %23 = load i32, ptr %6, align 4
  %24 = icmp sle i32 %23, 1
  br i1 %24, label %25, label %80

25:                                               ; preds = %22
  store i32 -1, ptr %7, align 4
  br label %26

26:                                               ; preds = %73, %25
  %27 = load i32, ptr %7, align 4
  %28 = icmp sle i32 %27, 1
  br i1 %28, label %29, label %76

29:                                               ; preds = %26
  %30 = load i32, ptr %6, align 4
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %35, label %32

32:                                               ; preds = %29
  %33 = load i32, ptr %7, align 4
  %34 = icmp ne i32 %33, 0
  br i1 %34, label %35, label %55

35:                                               ; preds = %32, %29
  %36 = load i32, ptr %3, align 4
  %37 = load i32, ptr %6, align 4
  %38 = add nsw i32 %36, %37
  %39 = icmp sge i32 %38, 512
  br i1 %39, label %55, label %40

40:                                               ; preds = %35
  %41 = load i32, ptr %4, align 4
  %42 = load i32, ptr %7, align 4
  %43 = add nsw i32 %41, %42
  %44 = icmp sge i32 %43, 256
  br i1 %44, label %55, label %45

45:                                               ; preds = %40
  %46 = load i32, ptr %3, align 4
  %47 = load i32, ptr %6, align 4
  %48 = add nsw i32 %46, %47
  %49 = icmp slt i32 %48, 0
  br i1 %49, label %55, label %50

50:                                               ; preds = %45
  %51 = load i32, ptr %4, align 4
  %52 = load i32, ptr %7, align 4
  %53 = add nsw i32 %51, %52
  %54 = icmp slt i32 %53, 0
  br i1 %54, label %55, label %56

55:                                               ; preds = %50, %45, %40, %35, %32
  br label %73

56:                                               ; preds = %50
  %57 = load i32, ptr %3, align 4
  %58 = load i32, ptr %6, align 4
  %59 = add nsw i32 %57, %58
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %60
  %62 = load i32, ptr %4, align 4
  %63 = load i32, ptr %7, align 4
  %64 = add nsw i32 %62, %63
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds [256 x i8], ptr %61, i64 0, i64 %65
  %67 = load i8, ptr %66, align 1
  %68 = trunc i8 %67 to i1
  br i1 %68, label %69, label %72

69:                                               ; preds = %56
  %70 = load i32, ptr %5, align 4
  %71 = add nsw i32 %70, 1
  store i32 %71, ptr %5, align 4
  br label %72

72:                                               ; preds = %69, %56
  br label %73

73:                                               ; preds = %72, %55
  %74 = load i32, ptr %7, align 4
  %75 = add nsw i32 %74, 1
  store i32 %75, ptr %7, align 4
  br label %26, !llvm.loop !6

76:                                               ; preds = %26
  br label %77

77:                                               ; preds = %76
  %78 = load i32, ptr %6, align 4
  %79 = add nsw i32 %78, 1
  store i32 %79, ptr %6, align 4
  br label %22, !llvm.loop !8

80:                                               ; preds = %22
  %81 = load i32, ptr %3, align 4
  %82 = sext i32 %81 to i64
  %83 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %82
  %84 = load i32, ptr %4, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds [256 x i8], ptr %83, i64 0, i64 %85
  %87 = load i8, ptr %86, align 1
  %88 = trunc i8 %87 to i1
  br i1 %88, label %92, label %89

89:                                               ; preds = %80
  %90 = load i32, ptr %5, align 4
  %91 = icmp eq i32 %90, 3
  br i1 %91, label %107, label %92

92:                                               ; preds = %89, %80
  %93 = load i32, ptr %3, align 4
  %94 = sext i32 %93 to i64
  %95 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %94
  %96 = load i32, ptr %4, align 4
  %97 = sext i32 %96 to i64
  %98 = getelementptr inbounds [256 x i8], ptr %95, i64 0, i64 %97
  %99 = load i8, ptr %98, align 1
  %100 = trunc i8 %99 to i1
  br i1 %100, label %101, label %114

101:                                              ; preds = %92
  %102 = load i32, ptr %5, align 4
  %103 = icmp eq i32 %102, 2
  br i1 %103, label %107, label %104

104:                                              ; preds = %101
  %105 = load i32, ptr %5, align 4
  %106 = icmp eq i32 %105, 3
  br i1 %106, label %107, label %114

107:                                              ; preds = %104, %101, %89
  %108 = load i32, ptr %3, align 4
  %109 = sext i32 %108 to i64
  %110 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %109
  %111 = load i32, ptr %4, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds [256 x i8], ptr %110, i64 0, i64 %112
  store i8 1, ptr %113, align 1
  br label %121

114:                                              ; preds = %104, %92
  %115 = load i32, ptr %3, align 4
  %116 = sext i32 %115 to i64
  %117 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %116
  %118 = load i32, ptr %4, align 4
  %119 = sext i32 %118 to i64
  %120 = getelementptr inbounds [256 x i8], ptr %117, i64 0, i64 %119
  store i8 0, ptr %120, align 1
  br label %121

121:                                              ; preds = %114, %107
  br label %122

122:                                              ; preds = %121
  %123 = load i32, ptr %4, align 4
  %124 = add nsw i32 %123, 1
  store i32 %124, ptr %4, align 4
  br label %18, !llvm.loop !9

125:                                              ; preds = %18
  br label %126

126:                                              ; preds = %125
  %127 = load i32, ptr %3, align 4
  %128 = add nsw i32 %127, 1
  store i32 %128, ptr %3, align 4
  br label %14, !llvm.loop !10

129:                                              ; preds = %14
  store i32 0, ptr %8, align 4
  br label %130

130:                                              ; preds = %172, %129
  %131 = load i32, ptr %8, align 4
  %132 = icmp slt i32 %131, 512
  br i1 %132, label %133, label %175

133:                                              ; preds = %130
  store i32 0, ptr %9, align 4
  br label %134

134:                                              ; preds = %168, %133
  %135 = load i32, ptr %9, align 4
  %136 = icmp slt i32 %135, 256
  br i1 %136, label %137, label %171

137:                                              ; preds = %134
  %138 = load i32, ptr %8, align 4
  %139 = sext i32 %138 to i64
  %140 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %139
  %141 = load i32, ptr %9, align 4
  %142 = sext i32 %141 to i64
  %143 = getelementptr inbounds [256 x i8], ptr %140, i64 0, i64 %142
  %144 = load i8, ptr %143, align 1
  %145 = trunc i8 %144 to i1
  br i1 %145, label %146, label %149

146:                                              ; preds = %137
  %147 = load i32, ptr %8, align 4
  %148 = load i32, ptr %9, align 4
  call void @simPutPixel(i32 noundef %147, i32 noundef %148, i32 noundef 16777215)
  br label %152

149:                                              ; preds = %137
  %150 = load i32, ptr %8, align 4
  %151 = load i32, ptr %9, align 4
  call void @simPutPixel(i32 noundef %150, i32 noundef %151, i32 noundef 0)
  br label %152

152:                                              ; preds = %149, %146
  %153 = load i32, ptr %8, align 4
  %154 = sext i32 %153 to i64
  %155 = getelementptr inbounds [512 x [256 x i8]], ptr %1, i64 0, i64 %154
  %156 = load i32, ptr %9, align 4
  %157 = sext i32 %156 to i64
  %158 = getelementptr inbounds [256 x i8], ptr %155, i64 0, i64 %157
  %159 = load i8, ptr %158, align 1
  %160 = trunc i8 %159 to i1
  %161 = load i32, ptr %8, align 4
  %162 = sext i32 %161 to i64
  %163 = getelementptr inbounds [512 x [256 x i8]], ptr @state, i64 0, i64 %162
  %164 = load i32, ptr %9, align 4
  %165 = sext i32 %164 to i64
  %166 = getelementptr inbounds [256 x i8], ptr %163, i64 0, i64 %165
  %167 = zext i1 %160 to i8
  store i8 %167, ptr %166, align 1
  br label %168

168:                                              ; preds = %152
  %169 = load i32, ptr %9, align 4
  %170 = add nsw i32 %169, 1
  store i32 %170, ptr %9, align 4
  br label %134, !llvm.loop !11

171:                                              ; preds = %134
  br label %172

172:                                              ; preds = %171
  %173 = load i32, ptr %8, align 4
  %174 = add nsw i32 %173, 1
  store i32 %174, ptr %8, align 4
  br label %130, !llvm.loop !12

175:                                              ; preds = %130
  call void @simFlush()
  br label %176

176:                                              ; preds = %175
  %177 = load i32, ptr %2, align 4
  %178 = add nsw i32 %177, 1
  store i32 %178, ptr %2, align 4
  br label %10, !llvm.loop !13

179:                                              ; preds = %10
  ret void
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) #1

declare void @simFlush(...) #1

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+crypto,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+sm4,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }

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
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
!12 = distinct !{!12, !7}
!13 = distinct !{!13, !7}
