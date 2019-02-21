#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; no parameters
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; no parameters
;
; Pipeline Runtime Information: 
;
;
;
; Buffer Definitions:
;
; cbuffer ConstructHierarchyConstants
; {
;
;   struct ConstructHierarchyConstants
;   {
;
;       struct struct.InputConstants
;       {
;
;           uint NumberOfElements;                    ; Offset:    0
;           uint UpdateFlags;                         ; Offset:    4
;       
;       } Constants                                   ; Offset:    0
;
;   
;   } ConstructHierarchyConstants                     ; Offset:    0 Size:     8
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
; ConstructHierarchyConstants       cbuffer      NA          NA     CB0            cb0     1
; outputBVH                             UAV    byte         r/w      U0             u0     1
; scratchMemory                         UAV    byte         r/w      U1             u1     1
; childNodesProcessedCounter            UAV    byte         r/w      U2             u2     1
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%struct.RWByteAddressBuffer = type { i32 }
%ConstructHierarchyConstants = type { %struct.InputConstants }
%struct.InputConstants = type { i32, i32 }
%dx.types.Handle = type { i8* }
%dx.types.CBufRet.i32 = type { i32, i32, i32, i32 }
%"class.RWStructuredBuffer<HierarchyNode>" = type { %struct.HierarchyNode }
%struct.HierarchyNode = type { i32, i32, i32 }
%"class.RWStructuredBuffer<unsigned int>" = type { i32 }
%struct.BoundingBox = type { <3 x float>, <3 x float> }

@"\01?outputBVH@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@"\01?scratchMemory@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@"\01?childNodesProcessedCounter@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@ConstructHierarchyConstants = external constant %ConstructHierarchyConstants

define void @main() {
  %childNodesProcessedCounter_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 2, i32 2, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %scratchMemory_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 1, i32 1, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %outputBVH_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %ConstructHierarchyConstants_cbuffer = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %1 = call i32 @dx.op.threadId.i32(i32 93, i32 0)  ; ThreadId(component)
  %2 = call %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32 59, %dx.types.Handle %ConstructHierarchyConstants_cbuffer, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %3 = extractvalue %dx.types.CBufRet.i32 %2, 0
  %4 = icmp eq i32 %3, 0
  %5 = icmp uge i32 %1, %3
  %6 = icmp ne i32 %1, 0
  %7 = and i1 %6, %4
  %8 = or i1 %5, %7
  br i1 %8, label %26, label %9

; <label>:9                                       ; preds = %0
  %10 = add i32 %3, -1
  %11 = shl i32 %3, 5
  %12 = add i32 %11, -16
  %13 = add i32 %12, %11
  %14 = icmp eq i32 %1, 0
  br i1 %14, label %15, label %19

; <label>:15                                      ; preds = %9
  %16 = mul i32 %3, 116
  %17 = add i32 %16, %13
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %outputBVH_UAV_rawbuf, i32 0, i32 undef, i32 16, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %outputBVH_UAV_rawbuf, i32 4, i32 undef, i32 %13, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %outputBVH_UAV_rawbuf, i32 12, i32 undef, i32 %17, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  br i1 %4, label %18, label %19

; <label>:18                                      ; preds = %15
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %outputBVH_UAV_rawbuf, i32 16, i32 undef, i32 0, i32 0, i32 0, i32 0, i8 15)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %outputBVH_UAV_rawbuf, i32 32, i32 undef, i32 0, i32 0, i32 0, i32 0, i8 15)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  br label %26

; <label>:19                                      ; preds = %15, %9
  %20 = xor i32 %1, -1
  %21 = add i32 %3, %20
  %22 = add i32 %21, %10
  %23 = shl i32 %1, 2
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %scratchMemory_UAV_rawbuf, i32 %23, i32 undef, i32 %22, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  %24 = icmp ult i32 %1, %10
  br i1 %24, label %25, label %26

; <label>:25                                      ; preds = %19
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %childNodesProcessedCounter_UAV_rawbuf, i32 %23, i32 undef, i32 0, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  br label %26

; <label>:26                                      ; preds = %25, %19, %18, %0
  ret void
}

; Function Attrs: nounwind readnone
declare i32 @dx.op.threadId.i32(i32, i32) #0

; Function Attrs: nounwind readonly
declare %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32, %dx.types.Handle, i32) #1

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #1

; Function Attrs: nounwind
declare void @dx.op.bufferStore.i32(i32, %dx.types.Handle, i32, i32, i32, i32, i32, i32, i8) #2

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind readonly }
attributes #2 = { nounwind }

!llvm.ident = !{!0}
!dx.version = !{!1}
!dx.valver = !{!2}
!dx.shaderModel = !{!3}
!dx.resources = !{!4}
!dx.typeAnnotations = !{!11, !30}
!dx.entryPoints = !{!34}

!0 = !{!"dxc 1.2"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 3}
!3 = !{!"cs", i32 6, i32 0}
!4 = !{null, !5, !9, null}
!5 = !{!6, !7, !8}
!6 = !{i32 0, %struct.RWByteAddressBuffer* undef, !"outputBVH", i32 0, i32 0, i32 1, i32 11, i1 true, i1 false, i1 false, null}
!7 = !{i32 1, %struct.RWByteAddressBuffer* undef, !"scratchMemory", i32 0, i32 1, i32 1, i32 11, i1 false, i1 false, i1 false, null}
!8 = !{i32 2, %struct.RWByteAddressBuffer* undef, !"childNodesProcessedCounter", i32 0, i32 2, i32 1, i32 11, i1 false, i1 false, i1 false, null}
!9 = !{!10}
!10 = !{i32 0, %ConstructHierarchyConstants* undef, !"ConstructHierarchyConstants", i32 0, i32 0, i32 1, i32 8, null}
!11 = !{i32 0, %struct.RWByteAddressBuffer undef, !12, %"class.RWStructuredBuffer<HierarchyNode>" undef, !14, %struct.HierarchyNode undef, !16, %"class.RWStructuredBuffer<unsigned int>" undef, !20, %struct.InputConstants undef, !22, %struct.BoundingBox undef, !25, %ConstructHierarchyConstants undef, !28}
!12 = !{i32 4, !13}
!13 = !{i32 6, !"h", i32 3, i32 0, i32 7, i32 4}
!14 = !{i32 12, !15}
!15 = !{i32 6, !"h", i32 3, i32 0}
!16 = !{i32 12, !17, !18, !19}
!17 = !{i32 6, !"ParentIndex", i32 3, i32 0, i32 7, i32 5}
!18 = !{i32 6, !"LeftChildIndex", i32 3, i32 4, i32 7, i32 5}
!19 = !{i32 6, !"RightChildIndex", i32 3, i32 8, i32 7, i32 5}
!20 = !{i32 4, !21}
!21 = !{i32 6, !"h", i32 3, i32 0, i32 7, i32 5}
!22 = !{i32 8, !23, !24}
!23 = !{i32 6, !"NumberOfElements", i32 3, i32 0, i32 7, i32 5}
!24 = !{i32 6, !"UpdateFlags", i32 3, i32 4, i32 7, i32 5}
!25 = !{i32 28, !26, !27}
!26 = !{i32 6, !"center", i32 3, i32 0, i32 7, i32 9}
!27 = !{i32 6, !"halfDim", i32 3, i32 16, i32 7, i32 9}
!28 = !{i32 8, !29}
!29 = !{i32 6, !"Constants", i32 3, i32 0}
!30 = !{i32 1, void ()* @main, !31}
!31 = !{!32}
!32 = !{i32 0, !33, !33}
!33 = !{}
!34 = !{void ()* @main, !"main", null, !4, !35}
!35 = !{i32 0, i64 16, i32 4, !36}
!36 = !{i32 64, i32 1, i32 1}

#endif

const unsigned char g_pTopLevelPrepareForComputeAABBs[] = {
  0x44, 0x58, 0x42, 0x43, 0x94, 0xf7, 0xb5, 0xdc, 0x05, 0x7f, 0x79, 0x3d,
  0x38, 0x7f, 0x74, 0xcb, 0x90, 0xd2, 0x50, 0xa9, 0x01, 0x00, 0x00, 0x00,
  0xcc, 0x0a, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
  0xe8, 0x00, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x4f, 0x53, 0x47, 0x31, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x50, 0x53, 0x56, 0x30, 0x7c, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0xdc, 0x09, 0x00, 0x00,
  0x60, 0x00, 0x05, 0x00, 0x77, 0x02, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c,
  0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xc4, 0x09, 0x00, 0x00,
  0x42, 0x43, 0xc0, 0xde, 0x21, 0x0c, 0x00, 0x00, 0x6e, 0x02, 0x00, 0x00,
  0x0b, 0x82, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
  0x07, 0x81, 0x23, 0x91, 0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39,
  0x92, 0x01, 0x84, 0x0c, 0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62,
  0x80, 0x14, 0x45, 0x02, 0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14,
  0x38, 0x08, 0x18, 0x4b, 0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20,
  0x43, 0x46, 0x88, 0xa5, 0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90,
  0x91, 0x22, 0xc4, 0x50, 0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a,
  0x04, 0x29, 0x46, 0x06, 0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x1b, 0x8c, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d,
  0x86, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x03, 0x20, 0x01, 0xd5, 0x06, 0x62,
  0xf8, 0xff, 0xff, 0xff, 0xff, 0x01, 0x90, 0x00, 0x49, 0x18, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x89, 0x20, 0x00, 0x00, 0x57, 0x00, 0x00, 0x00,
  0x32, 0x22, 0x48, 0x09, 0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84,
  0x04, 0x93, 0x22, 0xe3, 0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c,
  0x0b, 0x84, 0xa4, 0x4c, 0x10, 0x7c, 0x73, 0x04, 0x60, 0x70, 0x9a, 0x34,
  0x45, 0x94, 0x30, 0xf9, 0x2b, 0xbc, 0x61, 0x13, 0xa1, 0x0d, 0x43, 0x44,
  0x48, 0xd2, 0x46, 0x15, 0x05, 0x11, 0xa1, 0x00, 0x50, 0xb8, 0x4a, 0x9a,
  0x22, 0x4a, 0x98, 0x7c, 0xb1, 0x79, 0xa8, 0x89, 0x73, 0x1a, 0x69, 0x02,
  0x9a, 0x49, 0x42, 0x02, 0x00, 0xb7, 0x71, 0x4e, 0x23, 0x4d, 0x11, 0x25,
  0x4c, 0x21, 0x42, 0x44, 0x40, 0x24, 0x1c, 0x18, 0xe7, 0x34, 0xd2, 0x04,
  0x34, 0x93, 0x84, 0x82, 0x41, 0x64, 0x04, 0xa0, 0x04, 0x86, 0x4e, 0x19,
  0x00, 0x00, 0x94, 0x8e, 0x1a, 0x2e, 0x7f, 0xc2, 0x1e, 0x42, 0xf2, 0xb9,
  0x8d, 0x2a, 0x56, 0x62, 0xf2, 0x91, 0xdb, 0x46, 0x04, 0x00, 0x00, 0xcc,
  0x11, 0x20, 0xc4, 0xee, 0x19, 0x2e, 0x7f, 0xc2, 0x1e, 0x42, 0xf2, 0x43,
  0xa0, 0x19, 0x16, 0x02, 0x05, 0xad, 0x10, 0x0b, 0x38, 0x40, 0x6f, 0x8e,
  0x20, 0x28, 0x86, 0x03, 0x0c, 0x80, 0x48, 0xb2, 0x28, 0x06, 0x38, 0x00,
  0x00, 0x00, 0x80, 0x11, 0x1d, 0x08, 0x38, 0x4a, 0x9a, 0x22, 0x4a, 0x98,
  0xfc, 0x10, 0x21, 0x22, 0x20, 0x12, 0x0e, 0xec, 0x74, 0x06, 0x02, 0x0d,
  0x00, 0x80, 0x99, 0xce, 0x60, 0x1c, 0xd8, 0x21, 0x1c, 0xe6, 0x61, 0x1e,
  0xdc, 0x40, 0x16, 0x6e, 0x61, 0x16, 0xe8, 0x41, 0x1e, 0xea, 0x61, 0x1c,
  0xe8, 0xa1, 0x1e, 0xe4, 0xa1, 0x1c, 0xc8, 0x41, 0x14, 0xea, 0xc1, 0x1c,
  0xcc, 0xa1, 0x1c, 0xe4, 0x81, 0x0f, 0x50, 0x21, 0x1d, 0xca, 0x41, 0x1e,
  0xc2, 0x41, 0x1e, 0xc6, 0x01, 0x1d, 0xf2, 0xc1, 0x15, 0xde, 0x81, 0x1c,
  0xca, 0xc1, 0x0f, 0x50, 0x70, 0x67, 0x32, 0x83, 0x71, 0x60, 0x87, 0x70,
  0x98, 0x87, 0x79, 0x70, 0x03, 0x59, 0xb8, 0x85, 0x59, 0xa0, 0x07, 0x79,
  0xa8, 0x87, 0x71, 0xa0, 0x87, 0x7a, 0x90, 0x87, 0x72, 0x20, 0x07, 0x51,
  0xa8, 0x07, 0x73, 0x30, 0x87, 0x72, 0x90, 0x07, 0x3e, 0xa8, 0x07, 0x77,
  0x98, 0x87, 0x74, 0x38, 0x07, 0x77, 0x28, 0x07, 0x72, 0x00, 0x83, 0x74,
  0x70, 0x07, 0x7a, 0xf0, 0x03, 0x14, 0x80, 0x19, 0x80, 0x61, 0x84, 0x41,
  0x3b, 0x49, 0x9a, 0x22, 0x4a, 0x98, 0xfc, 0xcd, 0xa1, 0x9a, 0x01, 0x69,
  0x8c, 0xcd, 0xb9, 0x90, 0xb0, 0xf7, 0x1c, 0x01, 0x28, 0x4c, 0x01, 0x00,
  0x13, 0x14, 0x72, 0xc0, 0x87, 0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79,
  0x68, 0x03, 0x72, 0xc0, 0x87, 0x0d, 0xaf, 0x50, 0x0e, 0x6d, 0xd0, 0x0e,
  0x7a, 0x50, 0x0e, 0x6d, 0x00, 0x0f, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0xa0, 0x07, 0x73, 0x20, 0x07,
  0x6d, 0x90, 0x0e, 0x78, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e,
  0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x30, 0x07,
  0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x76, 0x40, 0x07,
  0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xe6, 0x10, 0x07, 0x76, 0xa0, 0x07,
  0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07,
  0x72, 0xd0, 0x06, 0xe6, 0x60, 0x07, 0x74, 0xa0, 0x07, 0x76, 0x40, 0x07,
  0x6d, 0xe0, 0x0e, 0x78, 0xa0, 0x07, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07,
  0x72, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x3a, 0x0f, 0x64, 0x90, 0x21, 0x23,
  0x45, 0x44, 0x00, 0x66, 0x00, 0xc0, 0xcc, 0x00, 0x80, 0x99, 0x01, 0x00,
  0x93, 0x03, 0x00, 0x18, 0xf2, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x30, 0xe4, 0x49, 0x80, 0x00, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0xf3, 0x00, 0x01, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0x47, 0x02, 0x02, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x21, 0x0f, 0x05, 0x04,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x20, 0x00,
  0x13, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x18, 0x19, 0x11, 0x4c, 0x90,
  0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x02, 0x25, 0x30, 0x02, 0x50,
  0x06, 0xc5, 0x50, 0x16, 0x45, 0x50, 0x10, 0x85, 0x50, 0x0e, 0x85, 0x51,
  0x0a, 0x85, 0x53, 0x12, 0x05, 0x52, 0x80, 0x01, 0xd4, 0x0b, 0x84, 0xe2,
  0x08, 0x40, 0x0d, 0x10, 0x99, 0x01, 0xa0, 0x32, 0x03, 0x40, 0x63, 0x06,
  0x80, 0xc4, 0x0c, 0x00, 0xdd, 0x19, 0x00, 0xc2, 0x33, 0x00, 0x94, 0x67,
  0x00, 0x88, 0xcf, 0x00, 0x50, 0x98, 0x01, 0x00, 0x79, 0x18, 0x00, 0x00,
  0xa6, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0xc4,
  0x83, 0x0c, 0x6f, 0x0c, 0x24, 0xc6, 0x45, 0x66, 0x43, 0x10, 0x4c, 0x10,
  0x80, 0x64, 0x82, 0x00, 0x28, 0x1b, 0x84, 0x81, 0x98, 0x20, 0x00, 0xcb,
  0x06, 0x61, 0x30, 0x28, 0x8c, 0xcd, 0x4d, 0x10, 0x00, 0x66, 0xc3, 0x80,
  0x24, 0xc4, 0x04, 0x41, 0xf0, 0x98, 0xbc, 0xd5, 0xd1, 0xc1, 0xd5, 0xd1,
  0x09, 0x59, 0x21, 0x4d, 0x10, 0x80, 0x66, 0x82, 0x10, 0x69, 0x13, 0x84,
  0x28, 0xdb, 0xb0, 0x10, 0x0b, 0x43, 0x10, 0x43, 0xe3, 0x3c, 0x0f, 0xc0,
  0x66, 0x6e, 0x4c, 0x2e, 0x8c, 0x6e, 0x0c, 0xad, 0xa9, 0xac, 0xed, 0x4d,
  0x2e, 0x6f, 0xc3, 0x32, 0x2c, 0x11, 0x31, 0x0c, 0xcd, 0xf3, 0x3c, 0xc0,
  0x04, 0x01, 0x70, 0xa8, 0x8d, 0xa1, 0xa5, 0xb1, 0x91, 0x39, 0xbd, 0x91,
  0x95, 0xcd, 0x41, 0xc9, 0xbd, 0x8d, 0x95, 0xcd, 0xcd, 0x95, 0x91, 0x0d,
  0xbd, 0xd5, 0xb9, 0xd1, 0x95, 0xc9, 0x6d, 0x58, 0xa6, 0x85, 0x22, 0xa6,
  0xa1, 0x79, 0x9e, 0x07, 0xd8, 0x30, 0x40, 0x52, 0x35, 0x41, 0x28, 0x38,
  0x6e, 0x43, 0x6f, 0x6e, 0x73, 0x74, 0x72, 0x75, 0x63, 0x74, 0x48, 0x69,
  0x65, 0x72, 0x61, 0x72, 0x63, 0x68, 0x79, 0x43, 0x6f, 0x6e, 0x73, 0x74,
  0x61, 0x6e, 0x74, 0x73, 0x13, 0x04, 0xe0, 0xd9, 0x80, 0x10, 0x17, 0x46,
  0x10, 0x43, 0x06, 0x6c, 0x08, 0xb4, 0x0d, 0x04, 0x60, 0x6d, 0xc0, 0x04,
  0x21, 0x18, 0x83, 0x09, 0x02, 0x00, 0x31, 0x40, 0x9b, 0x20, 0x00, 0xd1,
  0x06, 0x23, 0xf9, 0x0c, 0x02, 0x0c, 0xbc, 0x0d, 0x82, 0x17, 0x06, 0x13,
  0x04, 0x0c, 0x0c, 0x26, 0x08, 0x80, 0xb4, 0x81, 0x48, 0x3e, 0x83, 0xd8,
  0x20, 0x90, 0x41, 0x19, 0x4c, 0x10, 0xae, 0x8f, 0x0b, 0x54, 0x98, 0x5c,
  0x99, 0x1b, 0x5d, 0x92, 0x1b, 0x59, 0x19, 0xde, 0x04, 0x01, 0x98, 0x36,
  0x18, 0x09, 0x1a, 0x18, 0x04, 0x18, 0xa4, 0x01, 0x1d, 0xa6, 0x32, 0x33,
  0xba, 0x21, 0xb4, 0x34, 0x36, 0xb2, 0x24, 0x37, 0xb2, 0x32, 0xbc, 0x0d,
  0x46, 0xb2, 0x06, 0x86, 0x07, 0x06, 0x69, 0xc0, 0x47, 0x2a, 0xed, 0x0c,
  0x8d, 0x6e, 0x08, 0x2d, 0x8d, 0x8d, 0x2c, 0xc9, 0x8d, 0xac, 0x0c, 0x6f,
  0x83, 0x91, 0xb4, 0x81, 0x91, 0x81, 0x41, 0x1a, 0x6c, 0x20, 0xc8, 0x40,
  0x0d, 0xd8, 0xc0, 0x0d, 0x26, 0x08, 0x59, 0x18, 0x6c, 0x30, 0x92, 0xcf,
  0x20, 0xc0, 0x20, 0x0d, 0x36, 0x08, 0x5e, 0x1c, 0x4c, 0x10, 0x86, 0x8e,
  0x90, 0x53, 0x5d, 0x9b, 0x58, 0x99, 0xdc, 0x93, 0x59, 0x11, 0x5b, 0x59,
  0x5b, 0x99, 0x1b, 0xdd, 0xdc, 0x06, 0x23, 0xa1, 0x03, 0x83, 0x00, 0x83,
  0x34, 0xe0, 0x52, 0x05, 0x47, 0x16, 0x46, 0x57, 0x66, 0xc4, 0x16, 0x76,
  0x36, 0xb7, 0xc1, 0x48, 0xec, 0xc0, 0xf0, 0xc0, 0x20, 0x0d, 0x36, 0x0c,
  0x59, 0x1d, 0xdc, 0xc1, 0x04, 0x81, 0x13, 0x83, 0x09, 0x02, 0x40, 0xd1,
  0x18, 0x2b, 0x73, 0xa3, 0x2b, 0x93, 0x9b, 0x20, 0x00, 0xd5, 0x06, 0x23,
  0xd9, 0x03, 0x83, 0x00, 0x03, 0x3e, 0xe0, 0x81, 0x16, 0xc6, 0x66, 0x46,
  0x94, 0xd6, 0x36, 0x41, 0x00, 0xac, 0x0d, 0x46, 0xe2, 0x07, 0xc6, 0x1f,
  0x80, 0x01, 0x1f, 0x6c, 0x18, 0xf4, 0xa0, 0x0f, 0x40, 0x61, 0x82, 0x40,
  0x6c, 0x4c, 0x86, 0xde, 0xdc, 0xe6, 0xe8, 0xc2, 0xdc, 0xe8, 0xe6, 0x36,
  0x10, 0xc9, 0x28, 0x18, 0xc4, 0x06, 0x21, 0x23, 0x85, 0x0d, 0x0f, 0xd1,
  0x89, 0xc1, 0x18, 0x98, 0xc1, 0x19, 0xbc, 0x01, 0x1c, 0xc8, 0xc1, 0x1c,
  0xe0, 0x41, 0x1e, 0x84, 0x82, 0x28, 0x94, 0xc2, 0x04, 0x01, 0x21, 0x36,
  0x00, 0x1b, 0x06, 0x02, 0x15, 0x50, 0x61, 0x43, 0x90, 0x0a, 0x1b, 0x86,
  0xe1, 0x14, 0x54, 0x81, 0x44, 0x5b, 0x58, 0x9a, 0xdb, 0x04, 0xa1, 0xc3,
  0x26, 0x08, 0xc0, 0xb5, 0x61, 0x70, 0x85, 0x61, 0xd8, 0x40, 0x10, 0xad,
  0xe0, 0xbd, 0xc2, 0x86, 0xe2, 0x14, 0x58, 0x01, 0xe0, 0x60, 0xa1, 0x0a,
  0x1b, 0x9b, 0x5d, 0x9b, 0x4b, 0x1a, 0x59, 0x99, 0x1b, 0xdd, 0x94, 0x20,
  0xa8, 0x42, 0x86, 0xe7, 0x62, 0x57, 0x26, 0x37, 0x97, 0xf6, 0xe6, 0x36,
  0x25, 0x20, 0x9a, 0x90, 0xe1, 0xb9, 0xd8, 0x85, 0xb1, 0xd9, 0x95, 0xc9,
  0x4d, 0x09, 0x8c, 0x3a, 0x64, 0x78, 0x2e, 0x73, 0x68, 0x61, 0x64, 0x65,
  0x72, 0x4d, 0x6f, 0x64, 0x65, 0x6c, 0x53, 0x82, 0xa4, 0x0c, 0x19, 0x9e,
  0x8b, 0x5c, 0xd9, 0xdc, 0x5b, 0x9d, 0xdc, 0x58, 0xd9, 0xdc, 0x94, 0x60,
  0xab, 0x44, 0x86, 0xe7, 0x42, 0x97, 0x07, 0x57, 0x16, 0xe4, 0xe6, 0xf6,
  0x46, 0x17, 0x46, 0x97, 0xf6, 0xe6, 0x36, 0x37, 0x45, 0x28, 0x05, 0x55,
  0xa8, 0x43, 0x86, 0xe7, 0x52, 0xe6, 0x46, 0x27, 0x97, 0x07, 0xf5, 0x96,
  0xe6, 0x46, 0x37, 0x37, 0x25, 0x80, 0x05, 0x00, 0x79, 0x18, 0x00, 0x00,
  0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c, 0xc4, 0xe1, 0x1c, 0x66,
  0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3, 0x8c, 0x42, 0x80, 0x07,
  0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6, 0x00, 0x0f, 0xed, 0x10,
  0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e, 0xc2, 0xc1, 0x1d, 0xce,
  0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43, 0x38, 0x84, 0x83, 0x1b,
  0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03, 0x3d, 0xcc, 0x78, 0x8c,
  0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48, 0x87, 0x70, 0x70, 0x07,
  0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20, 0x87, 0x19, 0xcc, 0x11,
  0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e, 0x30, 0x0f, 0xe3, 0xf0,
  0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d, 0xde, 0x21, 0x1c, 0xd8,
  0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89, 0x3b, 0xbc, 0x83, 0x3b,
  0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83, 0x3c, 0x84, 0x03, 0x3b,
  0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68, 0x07, 0x37, 0x68, 0x87,
  0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90, 0x87, 0x70, 0x60, 0x07,
  0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78, 0x87, 0x77, 0x80, 0x87,
  0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98, 0x87, 0x79, 0x98, 0x81,
  0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5, 0xc0, 0x0e, 0xec, 0x30,
  0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xcc, 0xa1, 0x1c, 0xe4,
  0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c, 0xc4, 0x81, 0x1d, 0xca,
  0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43, 0x39, 0x98, 0x43, 0x39,
  0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43, 0x38, 0x88, 0x03, 0x3b,
  0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82, 0x3b, 0xd4, 0x03, 0x3b,
  0xb0, 0xc3, 0x8c, 0xcc, 0x21, 0x07, 0x7c, 0x70, 0x03, 0x74, 0x60, 0x07,
  0x37, 0x90, 0x87, 0x72, 0x98, 0x87, 0x77, 0xa8, 0x07, 0x79, 0x18, 0x87,
  0x72, 0x70, 0x83, 0x70, 0xa0, 0x07, 0x7a, 0x90, 0x87, 0x74, 0x10, 0x87,
  0x7a, 0xa0, 0x87, 0x72, 0x00, 0x00, 0x00, 0x00, 0x71, 0x20, 0x00, 0x00,
  0x39, 0x00, 0x00, 0x00, 0x66, 0xb0, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10,
  0x50, 0x45, 0x41, 0x44, 0xa5, 0x03, 0x0c, 0x25, 0x61, 0x00, 0x02, 0xe6,
  0x23, 0xb7, 0x5d, 0x02, 0x76, 0x10, 0xf8, 0x8d, 0xd1, 0x69, 0x36, 0xd9,
  0xf9, 0x26, 0x97, 0xe7, 0x50, 0xf9, 0x7b, 0x5c, 0x9e, 0xcf, 0xcb, 0xe4,
  0xe1, 0xbb, 0xee, 0xa6, 0x97, 0xe5, 0x40, 0xe0, 0xac, 0x2a, 0xbd, 0x0a,
  0xf3, 0xf4, 0x72, 0x90, 0x4c, 0x96, 0x97, 0xe7, 0x73, 0x61, 0xdd, 0x6c,
  0x2e, 0xcb, 0x81, 0xc0, 0x60, 0x01, 0x94, 0x41, 0xe0, 0xf7, 0xae, 0xd3,
  0xe1, 0x75, 0xba, 0xd0, 0x8a, 0x04, 0x02, 0x67, 0x55, 0xe9, 0x55, 0x98,
  0xa7, 0x97, 0x83, 0x64, 0xb2, 0xbc, 0x3c, 0x9f, 0x0b, 0xeb, 0x66, 0x73,
  0x59, 0x0e, 0x04, 0x06, 0xad, 0x40, 0x1a, 0x2e, 0xdf, 0x79, 0xfc, 0xe9,
  0x88, 0x08, 0x60, 0x10, 0x07, 0x1f, 0xb9, 0x6d, 0x3b, 0x90, 0x86, 0xcb,
  0x77, 0x1e, 0x5f, 0x88, 0x08, 0x60, 0x22, 0x42, 0xa0, 0x19, 0x16, 0xc2,
  0x06, 0x36, 0xce, 0x69, 0xa4, 0x29, 0xa2, 0x84, 0x29, 0x44, 0x88, 0x08,
  0x88, 0x84, 0x03, 0xe3, 0x9c, 0x46, 0x9a, 0x80, 0x66, 0x92, 0x8c, 0x80,
  0x60, 0x00, 0xa4, 0xa9, 0x80, 0x34, 0x08, 0xfc, 0xe6, 0x63, 0x79, 0x98,
  0x3e, 0x46, 0x37, 0xcb, 0xed, 0xb7, 0x3c, 0x0f, 0x04, 0xce, 0xaa, 0xd2,
  0xab, 0x30, 0x4f, 0x2f, 0x07, 0xc9, 0x64, 0x79, 0x79, 0x3e, 0x17, 0xd6,
  0xcd, 0xe6, 0xb2, 0x1c, 0x08, 0x0c, 0x1a, 0x42, 0x35, 0x5c, 0xbe, 0xf3,
  0xf8, 0x01, 0x55, 0x14, 0x44, 0xc4, 0x4e, 0x4e, 0x44, 0xf8, 0xc8, 0x6d,
  0x03, 0x00, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00, 0x6f, 0x00, 0x00, 0x00,
  0x13, 0x04, 0x47, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x04, 0x66, 0x00, 0x4a, 0x31, 0xa0, 0xe4, 0x6a, 0xa0, 0x74, 0x03, 0xca,
  0xae, 0x42, 0x0a, 0x3d, 0xa0, 0x80, 0x88, 0x95, 0x40, 0x79, 0x14, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x20, 0xa5,
  0x81, 0x32, 0x88, 0x81, 0x18, 0x5c, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60,
  0x20, 0xa9, 0xc1, 0x42, 0xa0, 0x01, 0x1a, 0x60, 0x23, 0x06, 0x09, 0x00,
  0x82, 0x60, 0x20, 0xad, 0x01, 0x53, 0xa0, 0x01, 0x1a, 0x64, 0x23, 0x06,
  0x09, 0x00, 0x82, 0x60, 0x20, 0xb1, 0x41, 0x43, 0xa4, 0x41, 0x1a, 0x68,
  0x23, 0x06, 0x06, 0x00, 0x82, 0x60, 0x90, 0xbc, 0x01, 0xa3, 0x06, 0x23,
  0x06, 0x07, 0x00, 0x82, 0x60, 0xf0, 0xbc, 0x01, 0x23, 0xac, 0xc1, 0x68,
  0x42, 0x00, 0x0c, 0x37, 0x04, 0x6d, 0x00, 0x06, 0xc3, 0x0d, 0x84, 0x30,
  0x06, 0xc3, 0x0d, 0xc5, 0x1b, 0x84, 0x41, 0x05, 0x83, 0xd6, 0x10, 0xec,
  0x2c, 0x83, 0x11, 0x04, 0x65, 0x54, 0x50, 0x87, 0x1a, 0x5c, 0x05, 0x14,
  0x54, 0x20, 0xc0, 0x70, 0x03, 0x63, 0x07, 0x60, 0x30, 0xcb, 0x20, 0x10,
  0x41, 0x2d, 0x96, 0x54, 0x30, 0xc0, 0x88, 0x41, 0x03, 0x80, 0x20, 0x18,
  0x50, 0x7b, 0xe0, 0x45, 0x79, 0xf0, 0xb5, 0xc1, 0xf7, 0x7d, 0xd6, 0x88,
  0x41, 0x03, 0x80, 0x20, 0x18, 0x50, 0x7b, 0xe0, 0x45, 0x73, 0xf0, 0x11,
  0xdf, 0xf7, 0x59, 0x23, 0x06, 0x0d, 0x00, 0x82, 0x60, 0x40, 0xed, 0x81,
  0x17, 0xc5, 0xc1, 0x17, 0x7c, 0xdf, 0x67, 0xcd, 0x32, 0x0c, 0x04, 0x33,
  0x62, 0xd0, 0x00, 0x20, 0x08, 0x06, 0xd4, 0x1e, 0x78, 0x51, 0x1b, 0x7c,
  0x79, 0x90, 0x07, 0x79, 0x90, 0x07, 0xd5, 0x88, 0x41, 0x03, 0x80, 0x20,
  0x18, 0x50, 0x7b, 0xe0, 0x45, 0xd7, 0x97, 0x07, 0x79, 0x90, 0x07, 0x79,
  0x50, 0xcd, 0x12, 0x18, 0xf5, 0x70, 0x5c, 0x4e, 0x00, 0x15, 0x24, 0x50,
  0x12, 0x1e, 0xdc, 0x88, 0x41, 0x03, 0x80, 0x20, 0x18, 0x50, 0x7f, 0x20,
  0x06, 0x56, 0x30, 0x06, 0xc2, 0x18, 0x8c, 0xc1, 0x18, 0x68, 0xc3, 0x0d,
  0xd3, 0x42, 0x06, 0xb3, 0x0c, 0x85, 0x11, 0x8c, 0x18, 0x34, 0x00, 0x08,
  0x82, 0x01, 0x05, 0x0a, 0x63, 0x80, 0x09, 0x64, 0xe0, 0x07, 0x64, 0x40,
  0x06, 0x64, 0xb0, 0xcd, 0x12, 0x18, 0x18, 0x0e, 0x04, 0x00, 0x00, 0x00,
  0x19, 0x00, 0x00, 0x00, 0x16, 0x83, 0x49, 0x42, 0x04, 0x4c, 0xc2, 0x61,
  0x12, 0x8c, 0x13, 0x61, 0xbf, 0xab, 0xbd, 0x7f, 0x04, 0x58, 0x01, 0x55,
  0x98, 0x0c, 0xe5, 0x50, 0xd3, 0x43, 0x4d, 0xdb, 0x1b, 0xfe, 0xae, 0xf6,
  0xfe, 0x11, 0x60, 0x05, 0x54, 0x61, 0x30, 0x65, 0x20, 0x1c, 0xc8, 0x32,
  0x9c, 0xce, 0x40, 0x48, 0x69, 0xe4, 0x08, 0x84, 0x24, 0x11, 0x03, 0xe7,
  0x50, 0xcd, 0x44, 0x44, 0xbf, 0xab, 0xbd, 0x7f, 0x04, 0x58, 0x01, 0x55,
  0xd8, 0xcc, 0x18, 0x70, 0x4e, 0x23, 0x4d, 0x11, 0x25, 0x4c, 0x21, 0x42,
  0x44, 0x40, 0x24, 0x1c, 0x18, 0xe7, 0x34, 0xd2, 0x04, 0x34, 0x93, 0xf4,
  0x0b, 0x01, 0x55, 0x14, 0x44, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
