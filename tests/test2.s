.assume adl=1	
; adl 1
	ld a, i
	ld a, (ix+5)
	ld a, (iy+5)
	ld a, mb
	ld a, ($aabbcc)
	ld a, r
	ld a, (bc)
	ld a, (de)
	ld a, (hl)
	ld hl, i
	ld (hl), ix
	ld (hl), iy
	ld (hl), 5
	ld (hl), a
	ld (hl), b
	ld (hl), c
	ld (hl), d
	ld (hl), e
	ld (hl), h
	ld (hl), l
	ld (hl), bc
	ld (hl), de
	ld (hl), hl
	ld i, hl
	ld i, a
	ld ixh, ixh
	ld ixh, ixl
	ld ixl, ixh
	ld ixl, ixl
	ld iyh, iyh
	ld iyh, iyl
	ld iyl, iyh
	ld iyl, iyl
; vanaf hier
	ld ixh, 5
	ld ixl, 5
	ld iyh, 5
	ld iyl, 5
	ld ixh, a
	ld ixh, b
	ld ixh, c
	ld ixh, d
	ld ixh, e
	ld ixl, a
	ld ixl, b
	ld ixl, c
	ld ixl, d
	ld ixl, e
	ld iyh, a
	ld iyh, b
	ld iyh, c
	ld iyh, d
	ld iyh, e
	ld iyl, a
	ld iyl, b
	ld iyl, c
	ld iyl, d
	ld iyl, e
; vanaf hier
	ld ix, (hl)
	ld iy, (hl)
	ld ix, (ix+5)
	ld iy, (ix+5)
	ld ix, (iy+5)
	ld iy, (iy+5)
	ld ix, $aabbcc
	ld iy, $aabbcc
	ld ix, ($aabbcc)
	ld iy, ($aabbcc)
; vanaf hier
	ld (ix+5), ix
	ld (ix+5), iy
	ld (iy+5), ix
	ld (iy+5), iy
	ld (ix+5), 10
	ld (iy+5), 10
; vanaf hier
	ld (ix+5), a
	ld (ix+5), b
	ld (ix+5), c
	ld (ix+5), d
	ld (ix+5), e
	ld (ix+5), h
	ld (ix+5), l
	ld (iy+5), a
	ld (iy+5), b
	ld (iy+5), c
	ld (iy+5), d
	ld (iy+5), e
	ld (iy+5), h
	ld (iy+5), l
	ld (ix+5), bc
	ld (ix+5), de
	ld (ix+5), hl
	ld (iy+5), bc
	ld (iy+5), de
	ld (iy+5), hl
	ld mb, a
	ld ($aabbcc), a
	ld ($aabbcc), ix
	ld ($aabbcc), iy
	ld ($aabbcc), bc
	ld ($aabbcc), de
	ld ($aabbcc), hl
	ld ($aabbcc), sp
	ld r, a
	ld a, (hl)
	ld b, (hl)
	ld c, (hl)
	ld d, (hl)
	ld e, (hl)
	ld h, (hl)
	ld l, (hl)
	ld a, ixh
	ld a, ixl
	ld a, iyh
	ld a, iyl
	ld b, ixh
	ld b, ixl
	ld b, iyh
	ld b, iyl
	ld c, ixh
	ld c, ixl
	ld c, iyh
	ld c, iyl
	ld d, ixh
	ld d, ixl
	ld d, iyh
	ld d, iyl
	ld e, ixh
	ld e, ixl
	ld e, iyh
	ld e, iyl
	ld a, (ix+5)
	ld b, (ix+5)
	ld c, (ix+5)
	ld d, (ix+5)
	ld e, (ix+5)
	ld h, (ix+5)
	ld l, (ix+5)
	ld a, (iy+5)
	ld b, (iy+5)
	ld c, (iy+5)
	ld d, (iy+5)
	ld e, (iy+5)
	ld h, (iy+5)
	ld l, (iy+5)
	ld a, 5
	ld b, 5
	ld c, 5
	ld d, 5
	ld e, 5
	ld h, 5
	ld l, 5
	ld a, a
	ld bc, (hl)
	ld de, (hl)
	ld hl, (hl)
	ld bc, (ix+5)
	ld de, (ix+5)
	ld hl, (ix+5)
	ld bc, (iy+5)
	ld de, (iy+5)
	ld hl, (iy+5)
	ld bc, $aabbcc
	ld de, $aabbcc
	ld hl, $aabbcc
	ld bc, ($aabbcc)
	ld de, ($aabbcc)
	ld hl, ($aabbcc)
	ld (bc), a
	ld (de), a
	ld (hl), a
	ld sp, hl
	ld sp, ix
	ld sp, iy
	ld sp, $aabbcc
	ld sp, ($aabbcc)
	ldd
	lddr
	ldi
	ldir
	lea ix, ix+5
	lea iy, ix+5
	lea ix, iy+5
	lea iy, iy+5
	lea bc, ix+5
	lea de, ix+5
	lea hl, ix+5
	lea bc, iy+5
	lea de, iy+5
	lea hl, iy+5
	
