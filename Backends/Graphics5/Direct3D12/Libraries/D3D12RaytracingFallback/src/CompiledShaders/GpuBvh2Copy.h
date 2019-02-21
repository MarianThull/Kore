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
; cbuffer DispatchWidthConstant
; {
;
;   struct DispatchWidthConstant
;   {
;
;       struct struct.DispatchWidthConstant
;       {
;
;           uint DispatchWidth;                       ; Offset:    0
;       
;       } Constants                                   ; Offset:    0
;
;   
;   } DispatchWidthConstant                           ; Offset:    0 Size:     4
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
; DispatchWidthConstant             cbuffer      NA          NA     CB0            cb0     1
; DestBVH                               UAV    byte         r/w      U0             u0     1
; SourceBVH                             UAV    byte         r/w      U1             u1     1
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%struct.RWByteAddressBuffer = type { i32 }
%DispatchWidthConstant = type { %struct.DispatchWidthConstant }
%struct.DispatchWidthConstant = type { i32 }
%dx.types.Handle = type { i8* }
%dx.types.ResRet.i32 = type { i32, i32, i32, i32, i32 }
%dx.types.CBufRet.i32 = type { i32, i32, i32, i32 }

@"\01?DestBVH@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@"\01?SourceBVH@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@DispatchWidthConstant = external constant %DispatchWidthConstant

define void @main() {
  %SourceBVH_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 1, i32 1, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %DestBVH_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %DispatchWidthConstant_cbuffer = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %1 = call i32 @dx.op.threadId.i32(i32 93, i32 0)  ; ThreadId(component)
  %2 = call %dx.types.ResRet.i32 @dx.op.bufferLoad.i32(i32 68, %dx.types.Handle %SourceBVH_UAV_rawbuf, i32 12, i32 undef)  ; BufferLoad(srv,index,wot)
  %3 = extractvalue %dx.types.ResRet.i32 %2, 0
  %4 = shl i32 %1, 2
  %5 = icmp ult i32 %4, %3
  br i1 %5, label %.lr.ph.preheader, label %._crit_edge

.lr.ph.preheader:                                 ; preds = %0
  br label %.lr.ph

.lr.ph:                                           ; preds = %.lr.ph, %.lr.ph.preheader
  %offsetToCopy.01 = phi i32 [ %11, %.lr.ph ], [ %4, %.lr.ph.preheader ]
  %6 = call %dx.types.ResRet.i32 @dx.op.bufferLoad.i32(i32 68, %dx.types.Handle %SourceBVH_UAV_rawbuf, i32 %offsetToCopy.01, i32 undef)  ; BufferLoad(srv,index,wot)
  %7 = extractvalue %dx.types.ResRet.i32 %6, 0
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %DestBVH_UAV_rawbuf, i32 %offsetToCopy.01, i32 undef, i32 %7, i32 undef, i32 undef, i32 undef, i8 1)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  %8 = call %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32 59, %dx.types.Handle %DispatchWidthConstant_cbuffer, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %9 = extractvalue %dx.types.CBufRet.i32 %8, 0
  %10 = shl i32 %9, 12
  %11 = add i32 %10, %offsetToCopy.01
  %12 = icmp ult i32 %11, %3
  br i1 %12, label %.lr.ph, label %._crit_edge.loopexit

._crit_edge.loopexit:                             ; preds = %.lr.ph
  br label %._crit_edge

._crit_edge:                                      ; preds = %._crit_edge.loopexit, %0
  ret void
}

; Function Attrs: nounwind readnone
declare i32 @dx.op.threadId.i32(i32, i32) #0

; Function Attrs: nounwind readonly
declare %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32, %dx.types.Handle, i32) #1

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #1

; Function Attrs: nounwind readonly
declare %dx.types.ResRet.i32 @dx.op.bufferLoad.i32(i32, %dx.types.Handle, i32, i32) #1

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
!dx.typeAnnotations = !{!10, !17}
!dx.entryPoints = !{!21}

!0 = !{!"dxc 1.2"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 3}
!3 = !{!"cs", i32 6, i32 0}
!4 = !{null, !5, !8, null}
!5 = !{!6, !7}
!6 = !{i32 0, %struct.RWByteAddressBuffer* undef, !"DestBVH", i32 0, i32 0, i32 1, i32 11, i1 false, i1 false, i1 false, null}
!7 = !{i32 1, %struct.RWByteAddressBuffer* undef, !"SourceBVH", i32 0, i32 1, i32 1, i32 11, i1 false, i1 false, i1 false, null}
!8 = !{!9}
!9 = !{i32 0, %DispatchWidthConstant* undef, !"DispatchWidthConstant", i32 0, i32 0, i32 1, i32 4, null}
!10 = !{i32 0, %struct.RWByteAddressBuffer undef, !11, %struct.DispatchWidthConstant undef, !13, %DispatchWidthConstant undef, !15}
!11 = !{i32 4, !12}
!12 = !{i32 6, !"h", i32 3, i32 0, i32 7, i32 4}
!13 = !{i32 4, !14}
!14 = !{i32 6, !"DispatchWidth", i32 3, i32 0, i32 7, i32 5}
!15 = !{i32 4, !16}
!16 = !{i32 6, !"Constants", i32 3, i32 0}
!17 = !{i32 1, void ()* @main, !18}
!18 = !{!19}
!19 = !{i32 0, !20, !20}
!20 = !{}
!21 = !{void ()* @main, !"main", null, !4, !22}
!22 = !{i32 0, i64 16, i32 4, !23}
!23 = !{i32 1024, i32 1, i32 1}

#endif

const unsigned char g_pGpuBvh2Copy[] = {
  0x44, 0x58, 0x42, 0x43, 0x8a, 0x44, 0xf8, 0xc9, 0x1a, 0x85, 0xf0, 0xe0,
  0xe8, 0xef, 0xef, 0xd1, 0x4b, 0x33, 0x08, 0x47, 0x01, 0x00, 0x00, 0x00,
  0x6c, 0x08, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
  0x44, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00,
  0xd8, 0x00, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x4f, 0x53, 0x47, 0x31, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x50, 0x53, 0x56, 0x30, 0x6c, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x8c, 0x07, 0x00, 0x00, 0x60, 0x00, 0x05, 0x00,
  0xe3, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x74, 0x07, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde,
  0x21, 0x0c, 0x00, 0x00, 0xda, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91,
  0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c,
  0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80, 0x14, 0x45, 0x02,
  0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b,
  0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5,
  0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91, 0x22, 0xc4, 0x50,
  0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x29, 0x46, 0x06,
  0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff,
  0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x86, 0xf0, 0xff, 0xff,
  0xff, 0xff, 0x03, 0x20, 0x01, 0xd5, 0x06, 0x62, 0xf8, 0xff, 0xff, 0xff,
  0xff, 0x01, 0x90, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x89, 0x20, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09,
  0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3,
  0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c,
  0x10, 0x70, 0x73, 0x04, 0x60, 0x70, 0x9a, 0x34, 0x45, 0x94, 0x30, 0xf9,
  0x2b, 0xbc, 0x61, 0x13, 0xa1, 0x0d, 0x43, 0x44, 0x48, 0xd2, 0x46, 0x15,
  0x05, 0x11, 0xa1, 0x00, 0x50, 0x38, 0x4e, 0x9a, 0x22, 0x4a, 0x98, 0xfc,
  0x0e, 0x91, 0x1e, 0x60, 0x12, 0x0e, 0x18, 0x19, 0xa6, 0x83, 0x73, 0x1a,
  0x69, 0x02, 0x9a, 0x09, 0x05, 0xe0, 0xaa, 0x0e, 0x91, 0x1e, 0x60, 0x12,
  0x0e, 0x18, 0x19, 0xa6, 0x83, 0x73, 0x1a, 0x69, 0x02, 0x9a, 0x09, 0x05,
  0x83, 0xc8, 0x08, 0x40, 0x09, 0x0c, 0x9d, 0x32, 0x00, 0x00, 0x28, 0x1d,
  0x35, 0x5c, 0xfe, 0x84, 0x3d, 0x84, 0xe4, 0x73, 0x1b, 0x55, 0xac, 0xc4,
  0xe4, 0x23, 0xb7, 0x8d, 0x08, 0x00, 0x00, 0x98, 0x23, 0x40, 0x88, 0xdd,
  0x33, 0x5c, 0xfe, 0x84, 0x3d, 0x84, 0xe4, 0x87, 0x40, 0x33, 0x2c, 0x04,
  0x0a, 0x5a, 0x21, 0x16, 0x70, 0x80, 0xde, 0x1c, 0x41, 0x50, 0x0c, 0x07,
  0x18, 0x00, 0x91, 0xe4, 0x4d, 0xc3, 0xe5, 0x4f, 0xd8, 0x43, 0x48, 0xfe,
  0x4a, 0x48, 0x2b, 0x31, 0xf9, 0xc8, 0x6d, 0xa3, 0x02, 0x00, 0x00, 0x40,
  0x29, 0x28, 0x70, 0x00, 0x50, 0x2d, 0x8a, 0x01, 0x0e, 0x00, 0x00, 0x00,
  0x60, 0x74, 0x07, 0x02, 0xe6, 0x08, 0x40, 0x61, 0x0a, 0x00, 0x00, 0x00,
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
  0x45, 0x44, 0x00, 0x66, 0x00, 0xc0, 0xcc, 0x00, 0x80, 0xc9, 0x01, 0x00,
  0x0c, 0x79, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0xf2, 0x24, 0x40, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x30, 0xe4, 0x79, 0x80, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x60, 0xc8, 0x23, 0x01, 0x01, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0xa7, 0x02, 0x02, 0x40, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x21, 0xcf, 0x05, 0x04, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x20, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90,
  0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x02, 0x25, 0x30, 0x02, 0x50,
  0x06, 0xc5, 0x50, 0x16, 0x85, 0x50, 0x0e, 0xa5, 0x50, 0x80, 0x10, 0xa4,
  0x0b, 0x84, 0xe2, 0x08, 0x00, 0x8d, 0x19, 0x00, 0x22, 0x33, 0x00, 0x54,
  0x66, 0x00, 0x48, 0xcc, 0x00, 0x50, 0x98, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90,
  0x46, 0x02, 0x13, 0xc4, 0x83, 0x0c, 0x6f, 0x0c, 0x24, 0xc6, 0x45, 0x66,
  0x43, 0x10, 0x4c, 0x10, 0x80, 0x64, 0x82, 0x00, 0x28, 0x1b, 0x84, 0x81,
  0x98, 0x20, 0x00, 0xcb, 0x06, 0x61, 0x30, 0x28, 0x8c, 0xcd, 0x4d, 0x10,
  0x00, 0x66, 0xc3, 0x80, 0x24, 0xc4, 0x04, 0x41, 0xb8, 0x78, 0x10, 0x95,
  0xcd, 0xd1, 0x09, 0x59, 0x21, 0x4d, 0x10, 0x80, 0x66, 0x82, 0x10, 0x4d,
  0x1b, 0x16, 0x62, 0x61, 0x08, 0x62, 0x68, 0x1c, 0xc7, 0x01, 0x98, 0x4c,
  0xbd, 0xd5, 0xc9, 0x8d, 0x95, 0x09, 0x59, 0x21, 0x6d, 0x58, 0x86, 0x05,
  0x22, 0x86, 0xa1, 0x71, 0x1c, 0x07, 0xd8, 0x20, 0x3c, 0xd1, 0x04, 0xa1,
  0xb0, 0x58, 0x11, 0xa5, 0xcd, 0xc1, 0x85, 0xd1, 0x8d, 0xa1, 0x5d, 0xa5,
  0x91, 0xd1, 0xa1, 0x0d, 0xbd, 0xb9, 0xcd, 0xd1, 0x85, 0xb9, 0xd1, 0x4d,
  0x10, 0x00, 0x67, 0x03, 0x42, 0x4c, 0x14, 0x41, 0x0c, 0x15, 0xb0, 0x21,
  0xb0, 0x36, 0x10, 0x80, 0x74, 0x01, 0x13, 0x84, 0x00, 0x63, 0x80, 0x36,
  0x41, 0x00, 0x9e, 0x0d, 0x46, 0xa2, 0x19, 0xc4, 0x56, 0x6d, 0x10, 0x2a,
  0x6e, 0x82, 0x30, 0x50, 0x6c, 0x88, 0xd2, 0xe6, 0xe0, 0xc2, 0xe8, 0xc6,
  0xd0, 0xae, 0xd2, 0xc8, 0xe8, 0xd0, 0x26, 0x08, 0x00, 0xb4, 0xc1, 0x48,
  0x3e, 0x83, 0xd8, 0xc0, 0x60, 0x83, 0x50, 0x85, 0xc1, 0x04, 0x81, 0xa8,
  0x98, 0x0c, 0xbd, 0xb9, 0xcd, 0xd1, 0x85, 0xb9, 0xd1, 0xcd, 0x6d, 0x20,
  0x12, 0x32, 0x30, 0x88, 0x0d, 0x42, 0x55, 0x06, 0x1b, 0x0e, 0x22, 0xeb,
  0x3c, 0x31, 0x18, 0x03, 0x33, 0x98, 0x20, 0x20, 0xc3, 0x06, 0x60, 0xc3,
  0x40, 0xa4, 0x41, 0x1a, 0x6c, 0x08, 0xd4, 0x60, 0xc3, 0x30, 0xa0, 0xc1,
  0x1a, 0x90, 0x68, 0x0b, 0x4b, 0x73, 0x9b, 0x20, 0x68, 0xd2, 0x04, 0x01,
  0x88, 0x36, 0x0c, 0x6f, 0x30, 0x0c, 0x1b, 0x08, 0xc2, 0x0d, 0x2a, 0x38,
  0xd8, 0x50, 0xa0, 0x41, 0x1b, 0x00, 0x58, 0x1c, 0x54, 0x61, 0x63, 0xb3,
  0x6b, 0x73, 0x49, 0x23, 0x2b, 0x73, 0xa3, 0x9b, 0x12, 0x04, 0x55, 0xc8,
  0xf0, 0x5c, 0xec, 0xca, 0xe4, 0xe6, 0xd2, 0xde, 0xdc, 0xa6, 0x04, 0x44,
  0x13, 0x32, 0x3c, 0x17, 0xbb, 0x30, 0x36, 0xbb, 0x32, 0xb9, 0x29, 0x81,
  0x51, 0x87, 0x0c, 0xcf, 0x65, 0x0e, 0x2d, 0x8c, 0xac, 0x4c, 0xae, 0xe9,
  0x8d, 0xac, 0x8c, 0x6d, 0x4a, 0x90, 0x94, 0x21, 0xc3, 0x73, 0x91, 0x2b,
  0x9b, 0x7b, 0xab, 0x93, 0x1b, 0x2b, 0x9b, 0x9b, 0x12, 0x5c, 0x95, 0xc8,
  0xf0, 0x5c, 0xe8, 0xf2, 0xe0, 0xca, 0x82, 0xdc, 0xdc, 0xde, 0xe8, 0xc2,
  0xe8, 0xd2, 0xde, 0xdc, 0xe6, 0xa6, 0x08, 0x66, 0xb0, 0x06, 0x75, 0xc8,
  0xf0, 0x5c, 0xca, 0xdc, 0xe8, 0xe4, 0xf2, 0xa0, 0xde, 0xd2, 0xdc, 0xe8,
  0xe6, 0xa6, 0x04, 0x71, 0x00, 0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00,
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
  0x2e, 0x00, 0x00, 0x00, 0x56, 0xb0, 0x0d, 0x97, 0xef, 0x3c, 0xbe, 0x10,
  0x50, 0x45, 0x41, 0x44, 0xa5, 0x03, 0x0c, 0x25, 0x61, 0x00, 0x02, 0xe6,
  0x23, 0xb7, 0x6d, 0x06, 0xd2, 0x70, 0xf9, 0xce, 0xe3, 0x0b, 0x11, 0x01,
  0x4c, 0x44, 0x08, 0x34, 0xc3, 0x42, 0x98, 0x40, 0xd5, 0x21, 0xd2, 0x03,
  0x4c, 0xc2, 0x01, 0x23, 0xc3, 0x74, 0x70, 0x4e, 0x23, 0x4d, 0x40, 0x33,
  0x19, 0x81, 0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0xd3, 0x11, 0x11, 0xc0, 0x20,
  0x0e, 0x3e, 0x72, 0xdb, 0x36, 0x40, 0x30, 0x00, 0xd2, 0xd8, 0x01, 0x35,
  0x5c, 0xbe, 0xf3, 0xf8, 0x01, 0x55, 0x14, 0x44, 0x54, 0x3a, 0xc0, 0xe0,
  0x23, 0xb7, 0x5d, 0x00, 0x63, 0x10, 0xf8, 0x11, 0xcb, 0x73, 0xba, 0xd0,
  0x8a, 0x04, 0x02, 0x67, 0x55, 0xe9, 0x55, 0x98, 0xa7, 0x97, 0x83, 0x64,
  0xb2, 0xbc, 0x3c, 0x9f, 0x0b, 0xeb, 0x66, 0x73, 0x59, 0x0e, 0x04, 0x06,
  0x2b, 0xa0, 0x0c, 0x02, 0xbf, 0xe9, 0xbb, 0x2e, 0x1f, 0x97, 0x85, 0x56,
  0x24, 0x10, 0x38, 0xab, 0x4a, 0xaf, 0xc2, 0x3c, 0xbd, 0x1c, 0x24, 0x93,
  0xe5, 0xe5, 0xf9, 0x5c, 0x58, 0x37, 0x9b, 0xcb, 0x72, 0x20, 0x30, 0x68,
  0x08, 0xd5, 0x70, 0xf9, 0xce, 0xe3, 0x07, 0x54, 0x51, 0x10, 0x11, 0x3b,
  0x39, 0x11, 0xe1, 0x23, 0xb7, 0x0d, 0x00, 0x00, 0x61, 0x20, 0x00, 0x00,
  0x4e, 0x00, 0x00, 0x00, 0x13, 0x04, 0x45, 0x2c, 0x10, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x04, 0x66, 0x00, 0x4a, 0xae, 0x10, 0x03, 0x0a,
  0xa3, 0x74, 0x03, 0x8a, 0xa0, 0x14, 0x03, 0xca, 0x8e, 0x58, 0x09, 0x14,
  0x01, 0x00, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x20, 0x75,
  0x89, 0xa0, 0x69, 0xd0, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x48, 0x9e,
  0x32, 0x68, 0x5a, 0x34, 0x62, 0x90, 0x00, 0x20, 0x08, 0x06, 0xd2, 0xb7,
  0x0c, 0xdb, 0x26, 0x8d, 0x18, 0x18, 0x00, 0x08, 0x82, 0x41, 0x22, 0x06,
  0x09, 0x37, 0x62, 0x80, 0x00, 0x20, 0x08, 0x06, 0x15, 0x18, 0x30, 0xc4,
  0xe2, 0x8c, 0x26, 0x04, 0x40, 0x0d, 0xcb, 0x0d, 0x37, 0x04, 0x02, 0x19,
  0xcc, 0x32, 0x04, 0x44, 0x30, 0x4b, 0x20, 0x0c, 0x54, 0x00, 0x8d, 0x40,
  0x04, 0x23, 0x06, 0x08, 0x00, 0x82, 0x60, 0x50, 0x95, 0x41, 0x94, 0x04,
  0xd3, 0x68, 0x42, 0x00, 0x8c, 0x18, 0x34, 0x00, 0x08, 0x82, 0xc1, 0x65,
  0x06, 0x8f, 0x32, 0x54, 0x41, 0x55, 0x55, 0xcd, 0x88, 0xc1, 0x01, 0x80,
  0x20, 0x18, 0x3c, 0x69, 0xe0, 0x24, 0x64, 0x30, 0x9a, 0x10, 0x00, 0x15,
  0x50, 0x57, 0x81, 0x01, 0xc3, 0x0d, 0x81, 0x42, 0x06, 0xb3, 0x0c, 0xc2,
  0x10, 0xcc, 0x12, 0x10, 0x18, 0x0e, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00,
  0x17, 0x00, 0xf9, 0x4b, 0xe4, 0x3f, 0x87, 0xff, 0x44, 0xc4, 0x41, 0x00,
  0x03, 0x11, 0x19, 0x89, 0xd4, 0x11, 0xd2, 0xb4, 0xbd, 0xe1, 0xef, 0x6a,
  0xef, 0x1f, 0x01, 0x56, 0x40, 0x15, 0x36, 0x42, 0xb1, 0x0e, 0x15, 0x09,
  0xc4, 0xf6, 0x86, 0xbf, 0xab, 0xbd, 0x7f, 0x04, 0x58, 0x01, 0x55, 0x9c,
  0x80, 0xe1, 0x2f, 0x91, 0xff, 0x1c, 0xb6, 0xf2, 0x38, 0x45, 0x21, 0x11,
  0x53, 0xeb, 0x70, 0xce, 0x83, 0xf9, 0x74, 0x7d, 0x03, 0x94, 0xff, 0x0b,
  0x11, 0x32, 0xfd, 0xc4, 0x60, 0x10, 0xfe, 0xe2, 0x38, 0x0f, 0x71, 0x21,
  0x93, 0x95, 0x74, 0x1d, 0x22, 0x3d, 0xc0, 0x24, 0x1c, 0x30, 0x32, 0x4c,
  0x07, 0xe7, 0x34, 0xd2, 0x04, 0x34, 0xd3, 0x2f, 0x04, 0x54, 0x51, 0x10,
  0xd1, 0x11, 0x2c, 0xfe, 0x2f, 0x44, 0xc8, 0xf4, 0x13, 0x83, 0x41, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
