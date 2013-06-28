
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.section .libdsp, code



	.global	_FindFirstBitChangeFromLeft	; export
_FindFirstBitChangeFromLeft:

	FBCL	W0 , W0
	return
