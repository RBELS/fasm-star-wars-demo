Stage1.dest1Pos:
.x      dd      -20.0
.y      dd      -10.0
.z      dd      -1000.0

Stage1.dest2Pos:
.x      dd      -60.0
.y      dd      0.0
.z      dd      -1000.0

Stage1.dest3Pos:
.x      dd      15.0
.y      dd      0.0
.z      dd      -1000.0


Stage1.tie1Pos:
.x      dq      30.0
.y      dq      5.0
.z      dq      50.0

Stage1.tie1Rot:
.x      dd      0.0
.y      dd      0.0
.z      dd      0.0

;some data may be used without initialization!

Stage1.dest2Z   dd      -1000.0
Stage1.dest2V   dd      0.2

Stage1.dest3Z   dd      -930.0
Stage1.dest3V   dd      0.0

Stage1.cameraPos:
.x              dq      30.0
.y              dq      5.0
.z              dq      50.0

Stage1.cameraPosF:
.x      dd      30.0
.y      dd      5.0
.z      dd      50.0

Stage1.pointPos:
.x              dq      0.0
.y              dq      0.0
.z              dq      0.0

;Stage1.upVecF:
;.x      dd      0.0
;.y      dd      1.0
;.z      dd      0.0

Stage1.upVecD:
.x      dq      0.0
.y      dq      1.0
.z      dq      0.0

Stage1.pointPosBufVecD:
.x      dq      0.0
.y      dq      0.0
.z      dq      0.0

Stage1.cameraPosBufVecD:
.x      dq      0.0
.y      dq      0.0
.z      dq      0.0


Debug.startTicksAdd     equ      100