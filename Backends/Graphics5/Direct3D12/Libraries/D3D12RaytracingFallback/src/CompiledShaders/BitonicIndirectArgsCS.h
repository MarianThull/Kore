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
; cbuffer CB1
; {
;
;   struct CB1
;   {
;
;       uint NullItem;                                ; Offset:    0
;       uint ListCount;                               ; Offset:    4
;   
;   } CB1                                             ; Offset:    0 Size:     8
;
; }
;
; cbuffer Constants
; {
;
;   struct Constants
;   {
;
;       uint MaxIterations;                           ; Offset:    0
;   
;   } Constants                                       ; Offset:    0 Size:     4
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
; CB1                               cbuffer      NA          NA     CB0            cb1     1
; Constants                         cbuffer      NA          NA     CB1            cb0     1
; g_IndirectArgsBuffer                  UAV    byte         r/w      U0             u0     1
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%struct.RWByteAddressBuffer = type { i32 }
%CB1 = type { i32, i32 }
%Constants = type { i32 }
%dx.types.Handle = type { i8* }
%dx.types.CBufRet.i32 = type { i32, i32, i32, i32 }

@"\01?g_IndirectArgsBuffer@@3URWByteAddressBuffer@@A" = external constant %struct.RWByteAddressBuffer, align 4
@CB1 = external constant %CB1
@Constants = external constant %Constants

define void @main() {
  %g_IndirectArgsBuffer_UAV_rawbuf = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 1, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %Constants_cbuffer = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 1, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %CB1_cbuffer = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 1, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %1 = call i32 @dx.op.flattenedThreadIdInGroup.i32(i32 96)  ; FlattenedThreadIdInGroup()
  %2 = call %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32 59, %dx.types.Handle %Constants_cbuffer, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %3 = extractvalue %dx.types.CBufRet.i32 %2, 0
  %4 = icmp ult i32 %1, %3
  br i1 %4, label %5, label %38

; <label>:5                                       ; preds = %0
  %6 = and i32 %1, 31
  %7 = shl i32 2048, %6
  %8 = call %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32 59, %dx.types.Handle %CB1_cbuffer, i32 0)  ; CBufferLoadLegacy(handle,regIndex)
  %9 = extractvalue %dx.types.CBufRet.i32 %8, 1
  %10 = add i32 %9, 2047
  %11 = and i32 %10, -2048
  %FirstbitHi = call i32 @dx.op.unaryBits.i32(i32 33, i32 %11)  ; FirstbitHi(value)
  %12 = sub i32 31, %FirstbitHi
  %13 = icmp eq i32 %FirstbitHi, -1
  %.op = and i32 %12, 31
  %.op.op = shl i32 1, %.op
  %.op.op.op = add i32 %.op.op, -1
  %14 = select i1 %13, i32 2147483647, i32 %.op.op.op
  %15 = add i32 %14, %11
  %16 = xor i32 %14, -1
  %17 = and i32 %15, %16
  %18 = icmp ugt i32 %7, %17
  %. = select i1 %18, i32 0, i32 %9
  %19 = add i32 %1, 1
  %20 = mul i32 %19, %1
  %21 = lshr i32 %20, 1
  %22 = mul i32 %21, 12
  %23 = icmp ugt i32 %7, 2049
  br i1 %23, label %.lr.ph.preheader, label %._crit_edge

.lr.ph.preheader:                                 ; preds = %5
  br label %.lr.ph

.lr.ph:                                           ; preds = %.lr.ph, %.lr.ph.preheader
  %j.02.in = phi i32 [ %j.02, %.lr.ph ], [ %7, %.lr.ph.preheader ]
  %Offset.01 = phi i32 [ %34, %.lr.ph ], [ %22, %.lr.ph.preheader ]
  %j.02 = lshr i32 %j.02.in, 1
  %24 = shl nuw i32 %j.02, 1
  %25 = sub i32 0, %24
  %26 = and i32 %., %25
  %27 = lshr i32 %26, 11
  %28 = shl nuw i32 %27, 11
  %29 = sub i32 %., %j.02
  %30 = sub i32 %29, %28
  %IMax = call i32 @dx.op.binary.i32(i32 37, i32 %30, i32 0)  ; IMax(a,b)
  %31 = add i32 %IMax, 1023
  %32 = lshr i32 %31, 10
  %33 = add nuw nsw i32 %27, %32
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %g_IndirectArgsBuffer_UAV_rawbuf, i32 %Offset.01, i32 undef, i32 %33, i32 1, i32 1, i32 undef, i8 7)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  %34 = add i32 %Offset.01, 12
  %35 = icmp ugt i32 %j.02.in, 4099
  br i1 %35, label %.lr.ph, label %._crit_edge.loopexit

._crit_edge.loopexit:                             ; preds = %.lr.ph
  %.lcssa = phi i32 [ %34, %.lr.ph ]
  br label %._crit_edge

._crit_edge:                                      ; preds = %._crit_edge.loopexit, %5
  %Offset.0.lcssa = phi i32 [ %22, %5 ], [ %.lcssa, %._crit_edge.loopexit ]
  %36 = add i32 %., 2047
  %37 = lshr i32 %36, 11
  call void @dx.op.bufferStore.i32(i32 69, %dx.types.Handle %g_IndirectArgsBuffer_UAV_rawbuf, i32 %Offset.0.lcssa, i32 undef, i32 %37, i32 1, i32 1, i32 undef, i8 7)  ; BufferStore(uav,coord0,coord1,value0,value1,value2,value3,mask)
  br label %38

; <label>:38                                      ; preds = %._crit_edge, %0
  ret void
}

; Function Attrs: nounwind readnone
declare i32 @dx.op.flattenedThreadIdInGroup.i32(i32) #0

; Function Attrs: nounwind readonly
declare %dx.types.CBufRet.i32 @dx.op.cbufferLoadLegacy.i32(i32, %dx.types.Handle, i32) #1

; Function Attrs: nounwind readnone
declare i32 @dx.op.binary.i32(i32, i32, i32) #0

; Function Attrs: nounwind readnone
declare i32 @dx.op.unaryBits.i32(i32, i32) #0

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
!dx.typeAnnotations = !{!10, !18}
!dx.entryPoints = !{!22}

!0 = !{!"dxc 1.2"}
!1 = !{i32 1, i32 0}
!2 = !{i32 1, i32 3}
!3 = !{!"cs", i32 6, i32 0}
!4 = !{null, !5, !7, null}
!5 = !{!6}
!6 = !{i32 0, %struct.RWByteAddressBuffer* undef, !"g_IndirectArgsBuffer", i32 0, i32 0, i32 1, i32 11, i1 false, i1 false, i1 false, null}
!7 = !{!8, !9}
!8 = !{i32 0, %CB1* undef, !"CB1", i32 0, i32 1, i32 1, i32 8, null}
!9 = !{i32 1, %Constants* undef, !"Constants", i32 0, i32 0, i32 1, i32 4, null}
!10 = !{i32 0, %struct.RWByteAddressBuffer undef, !11, %CB1 undef, !13, %Constants undef, !16}
!11 = !{i32 4, !12}
!12 = !{i32 6, !"h", i32 3, i32 0, i32 7, i32 4}
!13 = !{i32 8, !14, !15}
!14 = !{i32 6, !"NullItem", i32 3, i32 0, i32 7, i32 5}
!15 = !{i32 6, !"ListCount", i32 3, i32 4, i32 7, i32 5}
!16 = !{i32 4, !17}
!17 = !{i32 6, !"MaxIterations", i32 3, i32 0, i32 7, i32 5}
!18 = !{i32 1, void ()* @main, !19}
!19 = !{!20}
!20 = !{i32 0, !21, !21}
!21 = !{}
!22 = !{void ()* @main, !"main", null, !4, !23}
!23 = !{i32 0, i64 16, i32 4, !24}
!24 = !{i32 22, i32 1, i32 1}

#endif

const unsigned char g_pBitonicIndirectArgsCS[] = {
  0x44, 0x58, 0x42, 0x43, 0xe8, 0x3a, 0xcf, 0x05, 0xe9, 0x34, 0x26, 0xea,
  0x5a, 0xf5, 0x75, 0x0d, 0xd5, 0xf4, 0x1d, 0xb1, 0x01, 0x00, 0x00, 0x00,
  0x60, 0x09, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
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
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x44, 0x58, 0x49, 0x4c, 0x80, 0x08, 0x00, 0x00, 0x60, 0x00, 0x05, 0x00,
  0x20, 0x02, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x00, 0x01, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x68, 0x08, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde,
  0x21, 0x0c, 0x00, 0x00, 0x17, 0x02, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00,
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
  0x89, 0x20, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09,
  0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3,
  0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c,
  0x10, 0x78, 0x73, 0x04, 0x60, 0x70, 0x9a, 0x34, 0x45, 0x94, 0x30, 0xf9,
  0x2b, 0xbc, 0x61, 0x13, 0xa1, 0x0d, 0x43, 0x44, 0x48, 0xd2, 0x46, 0x15,
  0x05, 0x11, 0xa1, 0x00, 0x50, 0xb8, 0x81, 0xdb, 0x6a, 0x24, 0x00, 0x40,
  0xe3, 0x12, 0xce, 0x69, 0xa4, 0x09, 0x68, 0x26, 0x09, 0x05, 0x80, 0xca,
  0x08, 0x40, 0x09, 0x0e, 0xa1, 0x22, 0x00, 0x40, 0xea, 0xa8, 0xe1, 0xf2,
  0x27, 0xec, 0x21, 0x24, 0x9f, 0xdb, 0xa8, 0x62, 0x25, 0x26, 0x1f, 0xb9,
  0x6d, 0x44, 0x00, 0x00, 0xc0, 0x1c, 0x01, 0x42, 0xed, 0x9e, 0xe1, 0xf2,
  0x27, 0xec, 0x21, 0x24, 0x3f, 0x04, 0x9a, 0x61, 0x21, 0x50, 0xe0, 0x0a,
  0xc1, 0xc0, 0x03, 0x04, 0x0b, 0x01, 0x00, 0x00, 0x24, 0xcb, 0x00, 0x00,
  0x20, 0x3a, 0x47, 0x10, 0x14, 0xe3, 0x81, 0x06, 0x80, 0xa5, 0x5b, 0x94,
  0x03, 0x1e, 0x00, 0x00, 0x00, 0xd0, 0x28, 0x0f, 0x04, 0xcc, 0x11, 0x80,
  0xc2, 0x14, 0x00, 0x00, 0x13, 0x14, 0x72, 0xc0, 0x87, 0x74, 0x60, 0x87,
  0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0, 0x87, 0x0d, 0xaf, 0x50,
  0x0e, 0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d, 0x00, 0x0f, 0x7a, 0x30,
  0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0xa0,
  0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78, 0xa0, 0x07, 0x73, 0x20,
  0x07, 0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0,
  0x06, 0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90,
  0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74, 0xd0, 0x06, 0xe6, 0x10,
  0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x60, 0x0e, 0x73, 0x20,
  0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6, 0x60, 0x07, 0x74, 0xa0,
  0x07, 0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78, 0xa0, 0x07, 0x71, 0x60,
  0x07, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x3a, 0x0f,
  0x64, 0x90, 0x21, 0x23, 0x45, 0x44, 0x00, 0x66, 0x00, 0xc0, 0xdc, 0x00,
  0x00, 0xd8, 0x01, 0x00, 0x0c, 0x79, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xf2, 0x28, 0x40, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe4, 0x81, 0x80, 0x00, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x23, 0x01, 0x01,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x90, 0x87, 0x02,
  0x02, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x21, 0xcf,
  0x05, 0x04, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43,
  0x9e, 0x0c, 0x08, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xb2, 0x40, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14,
  0x19, 0x11, 0x4c, 0x90, 0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x02,
  0x25, 0x30, 0x02, 0x50, 0x06, 0xc5, 0x50, 0x16, 0x05, 0x51, 0x08, 0xe5,
  0x50, 0x0a, 0xc5, 0x42, 0xbc, 0x40, 0xc8, 0x8e, 0x00, 0xd0, 0x98, 0x01,
  0x20, 0x32, 0x03, 0x40, 0x65, 0x06, 0x80, 0xcc, 0x0c, 0x00, 0x89, 0x19,
  0x00, 0x0a, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x18, 0x00, 0x00,
  0x68, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90, 0x46, 0x02, 0x13, 0xc4,
  0x83, 0x0c, 0x6f, 0x0c, 0x24, 0xc6, 0x45, 0x66, 0x43, 0x10, 0x4c, 0x10,
  0x00, 0x65, 0x82, 0x00, 0x2c, 0x1b, 0x84, 0x81, 0x98, 0x20, 0x00, 0xcc,
  0x06, 0x61, 0x30, 0x28, 0x8c, 0xcd, 0x4d, 0x10, 0x80, 0x66, 0xc3, 0x80,
  0x24, 0xc4, 0x04, 0x41, 0xd0, 0x48, 0x9d, 0x7d, 0x25, 0xb9, 0x91, 0xa5,
  0xc9, 0x95, 0x8d, 0xd1, 0x05, 0xc9, 0x9d, 0xcd, 0x09, 0xd5, 0x99, 0x99,
  0x95, 0xc9, 0x4d, 0x10, 0x00, 0x67, 0x82, 0x60, 0x55, 0x1b, 0x16, 0x62,
  0x61, 0x08, 0x62, 0x68, 0x1c, 0xc7, 0x01, 0x36, 0x04, 0xcf, 0x04, 0x81,
  0xb8, 0x38, 0x0c, 0x09, 0xc5, 0x4c, 0x10, 0x80, 0x67, 0x03, 0x42, 0x44,
  0x12, 0x31, 0x0c, 0x13, 0x30, 0x41, 0x30, 0x32, 0x26, 0x43, 0x6f, 0x6e,
  0x73, 0x74, 0x61, 0x6e, 0x74, 0x73, 0x13, 0x04, 0x00, 0xda, 0x80, 0x0c,
  0x95, 0x45, 0x10, 0xc3, 0x05, 0x6c, 0x10, 0x28, 0x6c, 0x03, 0x01, 0x40,
  0x19, 0x30, 0x41, 0x08, 0x36, 0x06, 0x68, 0x13, 0x04, 0x20, 0xda, 0x60,
  0x24, 0x9c, 0x41, 0x74, 0xd7, 0x06, 0xe1, 0xf2, 0x26, 0x08, 0x83, 0x45,
  0xc4, 0xa9, 0x8e, 0x8d, 0x2d, 0x89, 0xae, 0xac, 0x6d, 0x82, 0x00, 0x48,
  0x1b, 0x8c, 0x24, 0x0c, 0x0c, 0xa2, 0x13, 0x03, 0x26, 0x4c, 0x69, 0x73,
  0x74, 0x43, 0x6f, 0x75, 0x6e, 0x74, 0x1b, 0x8c, 0x84, 0x0c, 0x8c, 0xab,
  0x13, 0x83, 0x0d, 0xc3, 0x34, 0x06, 0x65, 0x30, 0x41, 0x28, 0x30, 0x36,
  0x4d, 0x61, 0x78, 0x49, 0x74, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e,
  0x73, 0x1b, 0x8c, 0x04, 0x0d, 0x0c, 0xa2, 0x13, 0x83, 0x0d, 0xc2, 0x95,
  0x06, 0x1b, 0x0e, 0x62, 0xfb, 0xc0, 0xc0, 0x0c, 0xce, 0x40, 0x0d, 0x26,
  0x08, 0xc9, 0xb0, 0x01, 0xd8, 0x30, 0x10, 0x6d, 0xd0, 0x06, 0x1b, 0x02,
  0x37, 0xd8, 0x30, 0x0c, 0x6c, 0xf0, 0x06, 0x24, 0xda, 0xc2, 0xd2, 0xdc,
  0x26, 0x08, 0x1c, 0x35, 0x41, 0x00, 0xa6, 0x0d, 0xc3, 0x1c, 0x0c, 0xc3,
  0x06, 0x82, 0x90, 0x83, 0x8b, 0x0e, 0x36, 0x14, 0x6c, 0x10, 0x07, 0x80,
  0x56, 0x07, 0x55, 0xd8, 0xd8, 0xec, 0xda, 0x5c, 0xd2, 0xc8, 0xca, 0xdc,
  0xe8, 0xa6, 0x04, 0x41, 0x15, 0x32, 0x3c, 0x17, 0xbb, 0x32, 0xb9, 0xb9,
  0xb4, 0x37, 0xb7, 0x29, 0x01, 0xd1, 0x84, 0x0c, 0xcf, 0xc5, 0x2e, 0x8c,
  0xcd, 0xae, 0x4c, 0x6e, 0x4a, 0x60, 0xd4, 0x21, 0xc3, 0x73, 0x99, 0x43,
  0x0b, 0x23, 0x2b, 0x93, 0x6b, 0x7a, 0x23, 0x2b, 0x63, 0x9b, 0x12, 0x24,
  0x65, 0xc8, 0xf0, 0x5c, 0xe4, 0xca, 0xe6, 0xde, 0xea, 0xe4, 0xc6, 0xca,
  0xe6, 0xa6, 0x04, 0x59, 0x25, 0x32, 0x3c, 0x17, 0xba, 0x3c, 0xb8, 0xb2,
  0x20, 0x37, 0xb7, 0x37, 0xba, 0x30, 0xba, 0xb4, 0x37, 0xb7, 0xb9, 0x29,
  0x82, 0x1a, 0xbc, 0x41, 0x1d, 0x32, 0x3c, 0x97, 0x32, 0x37, 0x3a, 0xb9,
  0x3c, 0xa8, 0xb7, 0x34, 0x37, 0xba, 0xb9, 0x29, 0x41, 0x1d, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c,
  0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3,
  0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6,
  0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e,
  0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43,
  0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03,
  0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48,
  0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20,
  0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e,
  0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d,
  0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89,
  0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83,
  0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68,
  0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90,
  0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78,
  0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98,
  0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5,
  0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c,
  0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c,
  0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43,
  0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43,
  0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82,
  0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x8c, 0xcc, 0x21, 0x07, 0x7c, 0x70,
  0x03, 0x74, 0x60, 0x07, 0x37, 0x90, 0x87, 0x72, 0x98, 0x87, 0x77, 0xa8,
  0x07, 0x79, 0x18, 0x87, 0x72, 0x70, 0x83, 0x70, 0xa0, 0x07, 0x7a, 0x90,
  0x87, 0x74, 0x10, 0x87, 0x7a, 0xa0, 0x87, 0x72, 0x00, 0x00, 0x00, 0x00,
  0x71, 0x20, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x05, 0x00, 0x07, 0x81,
  0xdf, 0xf9, 0x9b, 0x74, 0x93, 0xd3, 0xf2, 0xf2, 0x98, 0x1e, 0x94, 0x9f,
  0xe7, 0xc2, 0xba, 0xd9, 0x5c, 0x96, 0x03, 0x81, 0xb3, 0xaa, 0xf4, 0x2a,
  0xcc, 0xd3, 0xcb, 0x41, 0x32, 0x59, 0x5e, 0x9e, 0xcf, 0x85, 0x75, 0xb3,
  0xb9, 0x2c, 0x07, 0x02, 0x83, 0x36, 0x40, 0x30, 0x00, 0xd2, 0x58, 0xc1,
  0x36, 0x5c, 0xbe, 0xf3, 0xf8, 0x42, 0x40, 0x15, 0x05, 0x11, 0x95, 0x0e,
  0x30, 0x94, 0x84, 0x01, 0x08, 0x98, 0x8f, 0xdc, 0xb6, 0x11, 0x88, 0xc1,
  0x70, 0xf9, 0xce, 0xe3, 0x17, 0x0b, 0x30, 0x4d, 0x44, 0x43, 0x0c, 0xed,
  0x11, 0x11, 0xc0, 0x20, 0x0e, 0x62, 0x03, 0x46, 0x0e, 0xf5, 0xf8, 0xc8,
  0x6d, 0xdb, 0xc1, 0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0x54, 0x03, 0x44, 0xd8,
  0x86, 0x4c, 0x92, 0x8f, 0xdc, 0xb6, 0x05, 0x0c, 0xdc, 0x56, 0x1b, 0x82,
  0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0x42, 0x44, 0x00, 0x13, 0x11, 0x02, 0xcd,
  0xb0, 0x10, 0x66, 0x00, 0x0d, 0x97, 0xef, 0x3c, 0x7e, 0x80, 0x34, 0x40,
  0x84, 0xf9, 0xc8, 0x6d, 0x5b, 0x42, 0x35, 0x5c, 0xbe, 0xf3, 0xf8, 0x01,
  0x55, 0x14, 0x44, 0xc4, 0x4e, 0x4e, 0x44, 0xf8, 0xc8, 0x6d, 0x9b, 0x40,
  0xc2, 0x39, 0x8d, 0x34, 0x01, 0xcd, 0x24, 0x01, 0x61, 0x20, 0x00, 0x00,
  0x8e, 0x00, 0x00, 0x00, 0x13, 0x04, 0x47, 0x2c, 0x10, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x04, 0x66, 0x00, 0x4a, 0xae, 0x7c, 0x6a, 0xa0,
  0xec, 0xca, 0xff, 0xa3, 0x30, 0x4a, 0x31, 0xa0, 0x80, 0x03, 0x0a, 0x10,
  0xa4, 0x02, 0x41, 0x4a, 0xa8, 0xfc, 0xff, 0xff, 0xff, 0x1f, 0x4a, 0x10,
  0xa4, 0x94, 0xca, 0xff, 0xa1, 0x28, 0xca, 0x10, 0x88, 0x5a, 0x11, 0x94,
  0x43, 0x09, 0x00, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x70, 0xa5,
  0x01, 0x15, 0x98, 0x81, 0x19, 0x70, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60,
  0x70, 0xa9, 0x41, 0x45, 0xa0, 0xc1, 0x19, 0x74, 0x23, 0x06, 0x09, 0x00,
  0x82, 0x60, 0x70, 0xad, 0x81, 0x55, 0xa0, 0x41, 0x1a, 0x78, 0x23, 0x06,
  0x05, 0x00, 0x82, 0x60, 0xa0, 0xc0, 0x01, 0x34, 0x62, 0x70, 0x00, 0x20,
  0x08, 0x06, 0x10, 0x1c, 0x54, 0x83, 0x1a, 0x8c, 0x26, 0x04, 0xc0, 0x70,
  0xc3, 0x10, 0x90, 0xc1, 0x2c, 0x43, 0x60, 0x04, 0x45, 0x68, 0x5a, 0x54,
  0x70, 0x23, 0x06, 0x07, 0x00, 0x82, 0x60, 0x00, 0xd5, 0x81, 0x76, 0xbc,
  0xc1, 0x68, 0x42, 0x10, 0x54, 0xb0, 0x41, 0x05, 0x97, 0x8e, 0x18, 0x18,
  0x00, 0x08, 0x82, 0x01, 0x75, 0x07, 0x57, 0x50, 0x61, 0x10, 0xc4, 0x70,
  0x83, 0x10, 0x06, 0x60, 0x50, 0xc2, 0x18, 0x68, 0xe1, 0x41, 0x70, 0x15,
  0x90, 0x01, 0x4c, 0x37, 0x70, 0x01, 0x51, 0x01, 0x02, 0x25, 0x9c, 0x01,
  0x97, 0x10, 0xe8, 0x70, 0xc3, 0x13, 0x88, 0xc1, 0x74, 0x83, 0x1f, 0x38,
  0x41, 0x59, 0xa0, 0x00, 0x15, 0x5c, 0x52, 0x81, 0x28, 0x60, 0x05, 0x6b,
  0x20, 0xc3, 0x0d, 0x55, 0x19, 0x88, 0xc1, 0x2c, 0x83, 0x50, 0x04, 0xb3,
  0x04, 0xc3, 0x40, 0x05, 0x50, 0x0c, 0x6c, 0x20, 0x0c, 0x54, 0x00, 0xdb,
  0x60, 0x08, 0x25, 0x9c, 0x02, 0x5a, 0x80, 0x0a, 0x17, 0x28, 0x54, 0x08,
  0xa2, 0x96, 0x40, 0x2b, 0x38, 0x05, 0xb4, 0x00, 0x15, 0x2e, 0x50, 0x8e,
  0x11, 0x15, 0x08, 0x31, 0x62, 0x70, 0x00, 0x20, 0x08, 0x06, 0xd2, 0x2c,
  0xbc, 0x41, 0xe0, 0x0a, 0x15, 0xbc, 0x01, 0x54, 0xf0, 0x06, 0x68, 0x47,
  0x00, 0x83, 0x11, 0x83, 0x06, 0x00, 0x41, 0x30, 0xc8, 0x68, 0x41, 0x0f,
  0xd8, 0xa0, 0x09, 0x85, 0x60, 0x16, 0x66, 0x21, 0x14, 0xdc, 0xa0, 0x9a,
  0x3d, 0x80, 0xe1, 0x86, 0x27, 0x0e, 0xc4, 0x60, 0x96, 0x61, 0x20, 0x82,
  0x81, 0x06, 0x80, 0x18, 0x66, 0x09, 0x8a, 0x81, 0x0a, 0xc0, 0x0c, 0x02,
  0x81, 0x28, 0x0c, 0x14, 0xa0, 0x02, 0x5a, 0xc0, 0x11, 0x83, 0x06, 0x00,
  0x41, 0x30, 0xc8, 0x74, 0x01, 0x14, 0xe4, 0x60, 0x38, 0x85, 0x20, 0x17,
  0x72, 0xe1, 0x14, 0xe8, 0x60, 0x96, 0xc0, 0xc0, 0x70, 0x20, 0x00, 0x00,
  0x2d, 0x00, 0x00, 0x00, 0xf6, 0x65, 0xf8, 0x8b, 0x20, 0x49, 0x80, 0x0d,
  0x25, 0xbe, 0xf3, 0xf8, 0xce, 0xe3, 0x3b, 0x8f, 0x81, 0x39, 0x68, 0x51,
  0x48, 0xc4, 0xe4, 0xd3, 0xfe, 0x22, 0x48, 0x12, 0x60, 0x41, 0x83, 0xef,
  0x3c, 0x96, 0x14, 0xf8, 0x96, 0x45, 0x88, 0x26, 0x70, 0x59, 0xcc, 0x67,
  0xfc, 0x62, 0x33, 0x20, 0x11, 0x21, 0x4c, 0x5a, 0x64, 0x48, 0x1b, 0x55,
  0x14, 0x44, 0xf4, 0xbb, 0xda, 0xfb, 0x47, 0x80, 0x15, 0x50, 0xc5, 0x09,
  0x40, 0xfe, 0x12, 0xf9, 0xcf, 0xe1, 0x3f, 0x11, 0x71, 0x10, 0xc0, 0x40,
  0x44, 0x36, 0xb3, 0x70, 0x5b, 0xfd, 0x0b, 0x01, 0x55, 0x14, 0x44, 0x74,
  0x03, 0x86, 0xbf, 0x44, 0xfe, 0x73, 0x5c, 0xc1, 0xe2, 0xff, 0x42, 0x84,
  0x4c, 0x3f, 0x31, 0x18, 0xc4, 0x11, 0x50, 0xfe, 0x2f, 0x44, 0xc8, 0xf4,
  0x13, 0x83, 0x41, 0xf8, 0x8b, 0xe3, 0x3c, 0xc4, 0x85, 0x4c, 0x06, 0x95,
  0xa0, 0x45, 0x21, 0x11, 0x93, 0x4f, 0xd7, 0xe6, 0xa3, 0x7c, 0x48, 0x24,
  0x4d, 0x01, 0x32, 0x85, 0x88, 0xc9, 0x44, 0x9c, 0xd3, 0x48, 0x13, 0xd0,
  0x4c, 0xd2, 0x2f, 0x04, 0x54, 0x51, 0x10, 0x91, 0x09, 0x19, 0xbe, 0xf3,
  0xf8, 0xce, 0x63, 0x51, 0x44, 0xe2, 0xd3, 0xb6, 0x3d, 0x1d, 0x89, 0x4f,
  0xdb, 0x3e, 0xd2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
